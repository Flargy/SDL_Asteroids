#pragma once
#include "CollidableObject.h"
#include <cmath>
#include <map>
#include <utility>
#include <array>
#include "Renderer.h"

class CollisionHandler
{
public:
	CollisionHandler(Window& w) 
		:debugRenderer(w) 
	{
		
	};

	void FindAllCollisions(
		std::vector<CollidableObject>& asteroids,
		std::vector<CollidableObject>& bullets,
		CollidableObject& player, 
		int gridSize);

private:
	using grid_cell = std::pair<int, int>;
	using grid_map = std::map<grid_cell, std::vector<CollidableObject*>>;

	grid_map map;
	Window& debugRenderer;


	bool CheckCollision(CollidableObject* obj, CollidableObject* otherObj, int iteration, bool looped);


	//Loops through each grid cell that `object` occupies
	template<typename T>
	void for_each_occupied_grid_cell(CollidableObject& object, int& gridSize, T func)
	{
		grid_cell currentCell;
		int x = object.transform->GetPosition()[0];
		int y = object.transform->GetPosition()[1];

		for (currentCell.first = std::floor(object.boundingBox.xMin + x / gridSize)
			; currentCell.first <= std::ceil(object.boundingBox.xMax + x / gridSize)
			; ++currentCell.first)
		{
			for (currentCell.second = std::floor(object.boundingBox.yMin + y / gridSize)
				; currentCell.second <= std::ceil(object.boundingBox.yMax + y / gridSize)
				; ++currentCell.second)
			{
				func(object, currentCell);
			}
		}
	}


};