#pragma once
#include "Transform.h"
#include <functional>
#include <iostream>

//todo move implementations to cpp
class CollidableObject
{
public:
	Transform transform;

	CollidableObject() : transform()
	{

	}

	
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
		if(active)
			collisionFunction(); // think it works, needs to be tested
		//std::cout << "i have collided" << std::endl;
	}

	std::vector<Vector2>* GetPoints() { return &_points; }

	//placeholder name, this is currently  used to determine if collision checks 
	//	and reactions should be done for this object
	bool active = true; 
	int entity_id = 0;

	std::vector<Vector2> _points;
	std::function<void()> collisionFunction;
};