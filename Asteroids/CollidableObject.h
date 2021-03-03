#pragma once
#include "Transform.h"
#include <vector>
#include <functional>

class CollidableObject
{
public:
	Transform transform;
	
	struct AABB
	{
		int yMin;
		int yMax;
		int xMin;
		int xMax;
	} boundingBox;

	void SetBoundingBox(int points[4])
	{
		boundingBox = { points[0], points[1], points[2], points[3] };
	}

	void Collision()
	{
		collisionFunction(); // think it works, needs to be tested
	}

	std::vector<double>* drawPoints;
	std::function<void()> collisionFunction;

};