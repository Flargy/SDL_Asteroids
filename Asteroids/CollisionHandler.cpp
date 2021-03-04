#include "CollisionHandler.h"
#include "CollidableObject.h"
#include <vector>
#include <cmath>
#include <map>
#include <utility>


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

bool checkCollision(CollidableObject* obj, CollidableObject* otherObj) {
	//todo should returns true if the objects intersect, fine grained collision algorithm here.
	return false;
}

//Loops through each grid cell that `object` occupies
template<typename T>
void for_each_occupied_grid_cell(CollidableObject& object, float& gridSize, T func)
{
	grid_cell currentCell;
	for (currentCell.first = std::floor(object.boundingBox.xMin / gridSize)
		; currentCell.first <= std::ceil(object.boundingBox.xMax / gridSize)
		; ++currentCell.first)
	{
		for (currentCell.second = std::floor(object.boundingBox.yMin / gridSize)
			; currentCell.second <= std::ceil(object.boundingBox.xMax / gridSize)
			; ++currentCell.second)
		{
			func(currentCell, object);
		}
	}
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
void findAllCollisions(std::vector<CollidableObject>& asteroids,
	std::vector<CollidableObject>& bullets,
	CollidableObject& alien,
	CollidableObject& player,
	float gridSize) //todo gridsize int or float?
{
	grid_cell currentCell; //grid square, key to map
	grid_map map; //maps grid squares to lists of colliders in those squares
	
	/* old code for reference
	for (CollidableObject& asteroid : asteroids)
	{
		for (currentCell.first = std::floor(asteroid.boundingBox.xMin / gridSize)
			; currentCell.first <= std::ceil(asteroid.boundingBox.xMax / gridSize)
			; ++currentCell.first)
		{
			for (currentCell.second = std::floor(asteroid.boundingBox.yMin / gridSize)
				; currentCell.second <= std::ceil(asteroid.boundingBox.xMax / gridSize)
				; ++currentCell.second)
			{
				auto it = map.find(currentCell);
				if (it == map.end())
				{
					map.emplace(currentCell, std::vector<CollidableObject*>{ &asteroid });//(currentCell, { &box }); //create list of contents
				}
				else
					it->second.push_back(&asteroid); //add to list of contents
			}
		}
	}
	*/

	auto addToMap = [&map](CollidableObject& object, grid_cell cell)
	{
		auto mapIterator = map.find(cell);
		if (mapIterator == map.end())
			map.emplace(cell, std::vector<CollidableObject*>{ &object });//(currentCell, { &box }); //create list of contents
		else
			mapIterator->second.push_back(&object); //add to list of contents
	};

	auto collide = [&map](CollidableObject& object, grid_cell cell) {
		auto mapIterator = map.find(cell);
		if (mapIterator != map.end())
		{
			//there is something to collide with, 
			for (CollidableObject* otherObject : mapIterator->second)
			{
				if (checkCollision(&object, otherObject))
				{
					object.Collision();
					otherObject->Collision();//todo ugly pointers?
				}
			}
		}
	};

	for (CollidableObject& asteroid : asteroids)
		for_each_occupied_grid_cell(asteroid, gridSize, addToMap);
	for_each_occupied_grid_cell(alien, gridSize, addToMap);
	
	//---------------------- collide bullets with the asteroids&alien in the map, then put the bullets into the map	
	DeferredFunctions<std::function<void()>> deferredMapInserts;	
	auto collideAndDeferAddToMap = [&collide, &addToMap, &deferredMapInserts, &map](CollidableObject& object, grid_cell cell)
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
	for_each_occupied_grid_cell(player, gridSize, collide);
};