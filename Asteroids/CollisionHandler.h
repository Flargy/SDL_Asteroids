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

	struct Vec2 {
		int x, y;
	};

	//Loops through each grid cell that `object` occupies
	template<typename T>
	void for_each_occupied_grid_cell(CollidableObject& object, int& gridSize, T func)
	{
		grid_cell currentCell;
		int x = object.transform->GetPosition()[0];
		int y = object.transform->GetPosition()[1];

		auto width = object.boundingBox.xMax - object.boundingBox.xMin;
		auto height = object.boundingBox.yMax - object.boundingBox.yMin;
		//debugRenderer.DrawRect(width, height, x - (width / 2), y - (height / 2));

		for (currentCell.first = std::floor(object.boundingBox.xMin + x / gridSize)
			; currentCell.first <= std::ceil(object.boundingBox.xMax + x / gridSize)
			; ++currentCell.first)
		{
			for (currentCell.second = std::floor(object.boundingBox.yMin + y / gridSize)
				; currentCell.second <= std::ceil(object.boundingBox.yMax + y / gridSize)
				; ++currentCell.second)
			{
				//debugRenderer.DrawRect(gridSize, gridSize, std::floor(object.boundingBox.xMin + x / gridSize), std::floor(object.boundingBox.yMin + y / gridSize));
				Vec2 topLeft = { std::floor(object.boundingBox.xMin + x / gridSize) , std::floor(object.boundingBox.yMin + y / gridSize) }; 
				Vec2 topRight = { std::ceil(object.boundingBox.xMax + x / gridSize) , std::floor(object.boundingBox.yMin + y / gridSize) };
				Vec2 bottomLeft= { std::floor(object.boundingBox.xMin + x / gridSize) , std::ceil(object.boundingBox.yMax + y / gridSize) };
				Vec2 bottomRight = { std::ceil(object.boundingBox.xMax + x / gridSize) , std::ceil(object.boundingBox.yMax + y / gridSize) };
				debugRenderer.DrawLine(topLeft.x, topLeft.y, topRight.x, topRight.y);
				debugRenderer.DrawLine(topRight.x, topRight.y, bottomRight.x, bottomRight.y);
				debugRenderer.DrawLine(bottomRight.x, bottomRight.y, bottomLeft.x, bottomLeft.y);
				debugRenderer.DrawLine(bottomLeft.x, bottomLeft.y, topLeft.x, topLeft.y);
				func(object, currentCell);
			}
		}
	}


};