#include "CollisionHandler.h"
#include "Global.h"

#define DOT(x1,y1,x2,y2)((x1 * x2) + (y1 * y2)) 



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

bool CollisionHandler::CheckCollision(CollidableObject* obj, CollidableObject* otherObj, int iteration = 0, bool looped = false) {
	//todo should returns true if the objects intersect, fine grained collision algorithm here.
	//Algorithm is in place, just needs to be tested now

	std::vector<Vector2>& points1 = *obj->GetPoints();
	std::vector<Vector2>& points2 = *otherObj->GetPoints();
	int size1 = points1.size();
	int size2 = points2.size();
	for (int i = 0; i < size1; i++)
	{


	Vector2 targetAxis;
	int j = i + 1;
	// gets reocurring values to avoid calling the Get functions multiple times.

	

	// calculates the axis which we will test, this is perpendicular to a side of the polygon
	targetAxis.x = -(points1[j % size1].y - points1[i].y);
	targetAxis.y = (points1[j % size1].x - points1[i].x);

	double currentMagnitude = sqrt(pow(targetAxis.x, 2) + pow(targetAxis.y, 2));

	if (currentMagnitude != 0)
	{
		targetAxis.x *= 1 / currentMagnitude;
		targetAxis.y *= 1 / currentMagnitude;
	}


	double p1min = DOT(targetAxis.x, targetAxis.y, points1[0].x, points1[0].y);
	double p1max = p1min;

	for (int i = 0; i < size1; i++)
	{
		double dot = DOT(targetAxis.x, targetAxis.y, points1[i].x, points1[i].y);
		p1min = fmin(p1min, dot);
		p1max = fmax(p1max, dot);
	}

	std::array<double, 2> offset{ (obj->transform.GetPosition().x - otherObj->transform.GetPosition().x),  (obj->transform.GetPosition().y - otherObj->transform.GetPosition().y) };
	double polyOffset = DOT(targetAxis.x, targetAxis.y, offset[0], offset[1]);
	p1min += polyOffset;
	p1max += polyOffset;
	//---------------Correct-----------


	double p2min = DOT(targetAxis.x, targetAxis.y, points2[0].x, points2[0].y);
	double p2max = p1min;

	for (int i = 0; i < size2; i++)
	{
		double dot = DOT(targetAxis.x, targetAxis.y, points2[i].x, points2[i].y);
		p2min = fmin(p2min, dot);
		p2max = fmax(p2max, dot);
	}

	if (p2max < p1min || p1max < p2min)
	{
		std::cout << "false" << std::endl;
		return false;
	}
	}
	
	

	return true;
}

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


/*
findAllCollisions(...)
put asteroids in grid_map
put alien in grid map
collide bullets with asteroids&alien -> insert bullets in map
collide player with entire map

todo IMPORTANT??: handle duplicate collision callbacks!
should keep a record of which objects have collided 
and make sure checkCollision(...) returns false if already handled?
*/
void CollisionHandler::FindAllCollisions(
	GameObjectBuffer<Asteroid, 32>& asteroids,
	GameObjectBuffer<Projectile, 16>& bullets,
	Player& player, Alien& alien, int gridSize) 
	// think the gridsize should be an int as the size of the window is calculated in ints(pixels)
{
	map.clear();
	
	auto addToMap = [this, gridSize](CollidableObject& object, grid_cell cell)
	{
		//debugRenderer.DrawRect(gridSize, gridSize, gridSize * cell.first, gridSize * cell.second);


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
					object.Collision();
					otherObject->Collision();//todo ugly pointers?
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