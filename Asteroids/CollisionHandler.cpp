#include "CollisionHandler.h"


bool BoundsTestLineSegment(float t) { return t >= 0 && t <= 1; };

const float PARALLEL_DETERMINANT_THRESHOLD = 0.00001f;

float Determinant /*or Cross*/(Vector2 a, Vector2 b) { return a.x * b.y - a.y * b.x; } // 2D "cross product"
bool GetLineLineTValues(Vector2 aToB, Vector2 aDir, Vector2 bDir, float& tA, float& tB)
{
	float d = Determinant(aDir, bDir);
	if (fabsf(d) < PARALLEL_DETERMINANT_THRESHOLD)
	{
		tA = tB = 0.0;
		return false;
	}

	tA = Determinant(aToB, bDir) / d;
	tB = Determinant(aToB, aDir) / d;
	return true;
}

/*
* Returns whether two lines intersect or not
*/
bool IntersectLineSegments(Vector2 aStart, Vector2 aEnd, Vector2 bStart, Vector2 bEnd)
{
	float tA, tB;
	return (GetLineLineTValues(bStart - aStart, aEnd - aStart, bEnd - bStart, tA, tB)
		&& BoundsTestLineSegment(tA)
		&& BoundsTestLineSegment(tB));
}




using grid_cell = std::pair<int, int>;
using grid_map = std::map<grid_cell, std::vector<CollidableObject*>>;

template<typename T>
struct DeferredFunctions {
	std::vector<T> callables;

	void push_back(T callable) {
		callables.push_back(callable);
	}

	void invoke() {
		for (auto& item : callables)
		{
			item();
		}
	}
};


std::array<double, 2> operator+(std::array<double, 2> left, std::array<double, 2> right) {
	return std::array<double, 2>{ left[0]+right[0], left[1]+right[1] };
}

std::array<double, 2> operator-(std::array<double, 2> left, std::array<double, 2> right) {
	return std::array<double, 2>{ left[0]-right[0], left[1]-right[1] };
}

double dot(std::array<double, 2> left, std::array<double, 2> right) 
{	
	return left[0] * right[0] + left[1] * right[1];
}

bool CollisionHandler::CheckCollisionV2(CollidableObject* obj, CollidableObject* otherObj) {
	//todo should returns true if the objects intersect, fine grained collision algorithm here.
	//Algorithm is in place, just needs to be tested now

	std::vector<Vector2>& a = *obj->GetPoints(); //todo why is this returning a pointer?
	std::vector<Vector2>& b = *otherObj->GetPoints();

	Vector2 position_a = obj->transform.GetPosition();
	Vector2 position_b = otherObj->transform.GetPosition();


	int size_a = a.size();
	int size_b = b.size();
	
	for (int i = 0; i < size_a; ++i) {

		auto current_a = a[i];
		auto next_a = a[(i + 1) % size_a];

		Vector2 aStart{ current_a.x + position_a.x, current_a.y + position_a.y };
		Vector2 aEnd{ next_a.x + position_a.x, next_a.y + position_a.y };

		for (int i = 0; i < size_b; i++)
		{
			auto current_b = b[i];
			auto next_b = b[(i + 1) % size_b];

			Vector2 bStart{ current_b.x + position_b.x, current_b.y + position_b.y };
			Vector2 bEnd{ next_b.x + position_b.x, next_b.y + position_b.y };

			if (IntersectLineSegments(aStart, aEnd, bStart, bEnd))
			{
				return true;
			}

		}
	}
	
	return false;
	
}



void CollisionHandler::FindAllCollisions(
	GameObjectBuffer<Asteroid, 32>& asteroids,
	GameObjectBuffer<Projectile, 16>& bullets,
	Player& player, Alien& alien, int gridSize) 
{
	map.clear();
	
	auto addToMap = [this, gridSize](CollidableObject& object, grid_cell cell)
	{

		auto mapIterator = map.find(cell);
		if (mapIterator == map.end())
			map.emplace(cell, std::vector<CollidableObject*>{ &object });
		else
			mapIterator->second.push_back(&object); 
	};

	auto collide = [this](CollidableObject& object, grid_cell cell) {
		auto mapIterator = map.find(cell);
		if (mapIterator != map.end())
		{
			
			for (CollidableObject* otherObject : mapIterator->second)
			{
				if ((object.alive && otherObject->alive)
					&& CheckCollisionV2(&object, otherObject))
				{
					otherObject->Collision();//todo ugly pointers?
					object.Collision();
				}
			}
		}
	};

	for (size_t i = 0; i < asteroids.active_size(); i++)
	{
		for_each_occupied_grid_cell(asteroids[i], gridSize, addToMap);
	}
	if(alien.alive)
		for_each_occupied_grid_cell(alien, gridSize, addToMap); 
	
	//---------------------- collide bullets with the asteroids&alien in the map, then put the bullets into the map	
	DeferredFunctions<std::function<void()>> deferredMapInserts;	
	auto collideAndDeferAddToMap = [&collide, &addToMap, &deferredMapInserts](CollidableObject& object, grid_cell cell)
	{
		collide(object, cell);
		deferredMapInserts.push_back(
			[&addToMap, &object, cell]() {
				addToMap(object, cell);
			});		
	};
	for (size_t i = 0; i < bullets.active_size(); i++)
	{
		for_each_occupied_grid_cell(bullets[i], gridSize, collideAndDeferAddToMap);
	}
	deferredMapInserts.invoke();

	//---------------------- collide the player against everything in the map (asteroids, alien, bullets)	
	if (player.alive)
	{
		for_each_occupied_grid_cell(player, gridSize, collide);
	}
};