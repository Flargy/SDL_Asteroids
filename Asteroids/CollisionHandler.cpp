#include "CollisionHandler.h"
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

//placeholder
struct Box
{
	int xMin, xMax, yMin, yMax, id;
};


//put asteroids in grid_map
//put alien in grid map
//collide bullets with asteroids&alien -> insert bullets in map
//collide player with entire map


//todo redo so that this function takes a list of collidable object (pointers?)
bool playerCollide(std::vector<Box>& boxes, float gridSize)
{
	using grid_cell = std::pair<int, int>;
	using grid_map = std::map<grid_cell, std::vector<Box*>>;

	grid_cell currentCell; //grid square, key to map
	grid_map map; //maps grid squares to lists of colliders in those squares

	//step 1 fill boxes into grid_map	
	for (Box& box : boxes)
	{
		for (currentCell.first = std::floor(box.xMin / gridSize)
			; currentCell.first <= std::ceil(box.xMax / gridSize)
			; ++currentCell.first)
		{
			for (currentCell.second = std::floor(box.yMin / gridSize)
				; currentCell.second <= std::ceil(box.xMax / gridSize)
				; ++currentCell.second)
			{
				std::vector<Box*>& cellContents;
				auto it = map.find(currentCell);
				if (it == map::end())
					map.emplace(currentCell, { &box }); //create list of contents
				else
					*it.push_back(&box) //add to list of contents
			}
		}
	}




	//step 2 check grid_squares of player against the filled grid_map
	Box& box; //player box
	for (currentCell.first = std::floor(box.xMin / gridSize)
		; currentCell.first <= std::ceil(box.xMax / gridSize)
		; ++currentCell.first)
	{
		for (currentCell.second = std::floor(box.yMin / gridSize)
			; currentCell.second <= std::ceil(box.xMax / gridSize)
			; ++currentCell.second)
		{
			auto it = map.find(currentCell);
			if (it != map.end()) 
			{
				//detect collision 
				//return true;
			}
		}

	}
	return false;
};