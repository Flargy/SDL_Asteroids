#pragma once
#include <vector>
#include "CollidableObject.h"


class Asteroid : public CollidableObject
{
public:

	Asteroid(double length);
	Asteroid(double length, int entity_id);
	~Asteroid();

	void CreatePoints(double length);

	void Collide();
	void Update();
	void ChangeShape(std::vector<Vector2>& newShape); //This method will be used to change the shape of asteroids when instantiated or when shot
	int GetSize(){ return _size; }
	void AddToSize(int value) { _size += value; }
	void Instantiate(Vector2 spawnPosition, double speed);


private:
	int _size = 3;

};