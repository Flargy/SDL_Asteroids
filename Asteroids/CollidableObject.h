#pragma once
#include "Transform.h"
#include <functional>
#include <iostream>
#include "GameObjectBuffer.h"
#include "ResourceManager.h"

class SpawnSystem;

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
		if(collisionActive)
			collisionFunction(); // think it works, needs to be tested
	}

	std::shared_ptr<std::vector<Vector2>> GetPoints() { return _points; }


	bool collisionActive = true; 
	int entity_id = 0;

	std::shared_ptr<std::vector<Vector2>> _points;

	//std::vector<Vector2>* _points;
	std::function<void()> collisionFunction;
	SpawnSystem* _spawnSystem;
};