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

	CollidableObject();

	
	struct AABB
	{
		int yMin;
		int yMax;
		int xMin;
		int xMax;
	} boundingBox;

	

	void SetBoundingBox(int points[4]);

	void Collision();

	std::shared_ptr<std::vector<Vector2>> GetPoints() { return _points; }


	bool alive = true; 
	int entity_id = 0;

	std::shared_ptr<std::vector<Vector2>> _points;

	//std::vector<Vector2>* _points;
	std::function<void()> collisionFunction;
	SpawnSystem* _spawnSystem;
};