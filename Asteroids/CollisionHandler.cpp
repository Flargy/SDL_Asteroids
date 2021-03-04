#include "CollisionHandler.h"

#include <iostream>

#define DOT(x1,y1,x2,y2)(x1 * x2 + y1 * y2) 

/*
js code for grid intersection
//boxes are list of d intervals
// H is the side length for the grid

function gridIntersect2D(boxes, H) {
  var grid = {}, result = [], x = [0,0]
  boxes.forEach(function(b, id) {
	for(x[0]=Math.floor(b[0][0]/H); x[0]<=Math.ceil(b[0][1]/H); ++x[0])
	for(x[1]=Math.floor(b[1][0]/H); x[1]<=Math.ceil(b[1][1]/H); ++x[1]) {
	  var list = grid[x]
	  if(list) {
		list.forEach(function(otherId) {
		  var a = boxes[otherId]
		  for(var i=0; i<2; ++i) {
			var s = Math.max(a[i][0], b[i][0]),
				t = Math.min(a[i][1], b[i][1])
			if(t < s || Math.floor(s/H) !== x[i])
			  return
		  }
		  result.push([id, otherId])
		})
		list.push(id)
	  } else grid[x] = [id]
	}
  })
  return result
}
*/
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

	std::array<double, 2> targetAxis;
	int j = iteration + 1;
	// gets reocurring values to avoid calling the Get functions multiple times.
	std::vector<std::array<double, 2>>& points1 = *obj->GetPoints();
	std::vector<std::array<double, 2>>& points2 = *otherObj->GetPoints();
	int size1 = points1.size();
	int size2 = points2.size();

	/*if (j >= size1) // replaced by j % size1
	{
		j = 0;
	}*/

	// calculates the axis which we will test, this is perpendicular to a side of the polygon
	targetAxis[0] = -(points1[j % size1][1] - points1[iteration][1]);
	targetAxis[1] = (points1[j % size1][0] - points1[iteration][0]);

	double currentMagnitude = sqrt(pow(targetAxis[0], 2) + pow(targetAxis[1], 2));

	targetAxis[0] *= 1 / currentMagnitude;
	targetAxis[1] *= 1 / currentMagnitude;


	double p1min = DOT(targetAxis[0], targetAxis[1], points1[0][0], points1[0][1]);
	double p1max = p1min;

	for (int i = 0; i < size1; i++)
	{
		double dot = DOT(targetAxis[0], targetAxis[1], points1[i][0], points1[i][1]);
		p1min = fmin(p1min, dot);
		p1max = fmax(p1max, dot);
	}

	std::array<double, 2> offset{ (obj->transform->GetPosition()[0] - otherObj->transform->GetPosition()[0]),  (obj->transform->GetPosition()[1] - otherObj->transform->GetPosition()[1]) };
	double polyOffset = DOT(targetAxis[0], targetAxis[1], offset[0], offset[1]);
	p1min += polyOffset;
	p1max += polyOffset;
	//---------------Correct-----------


	double p2min = DOT(targetAxis[0], targetAxis[1], points2[0][0], points2[0][1]);
	double p2max = p1min;

	for (int i = 0; i < size2; i++)
	{
		double dot = DOT(targetAxis[0], targetAxis[1], points2[i][0], points2[i][1]);
		p2min = fmin(p2min, dot);
		p2max = fmax(p2max, dot);
	}


	if (p1min - p2max > 0 || p2min - p1max > 0)
	{
		return false;
	}
	if (iteration + 1 < size1)
	{
		return CheckCollision(obj, otherObj, iteration + 1, looped);
	}
	if (iteration == size1 && looped == false)
	{
		return CheckCollision(otherObj, obj, 0, true);
	}

	return true;
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
	std::vector<CollidableObject>& asteroids,
	std::vector<CollidableObject>& bullets,
	CollidableObject& player, int gridSize) //todo gridsize int or float?
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
				if ((object.active || otherObject->active)
					&& CheckCollision(&object, otherObject))
				{
					object.Collision();
					otherObject->Collision();//todo ugly pointers?
				}
			}
		}
	};

	std::cout << "begin asteroids" << std::endl;
	for (CollidableObject& asteroid : asteroids)
		for_each_occupied_grid_cell(asteroid, gridSize, addToMap);
	//for_each_occupied_grid_cell(alien, gridSize, addToMap);
	
	//---------------------- collide bullets with the asteroids&alien in the map, then put the bullets into the map	
	std::cout << "begin bullets" << std::endl;
	DeferredFunctions<std::function<void()>> deferredMapInserts;	
	auto collideAndDeferAddToMap = [&collide, &addToMap, &deferredMapInserts](CollidableObject& object, grid_cell cell)
	{
		collide(object, cell);
		deferredMapInserts.push_back(
			[&addToMap, &object, cell]() {
				addToMap(object, cell);
			});		
	};
	for (CollidableObject& bullet : bullets)
	{
		for_each_occupied_grid_cell(bullet, gridSize, collideAndDeferAddToMap);
	}
	deferredMapInserts.invoke();

	//---------------------- collide the player against everything in the map (asteroids, alien, bullets)		
	std::cout << "begin player" << std::endl;
	for_each_occupied_grid_cell(player, gridSize, collide);
};