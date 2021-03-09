#pragma once
#include <vector>
#include "CollidableObject.h"


class Asteroid : public CollidableObject
{
public:
	Asteroid();
	Asteroid(double length);
	Asteroid(double length, int entity_id);
	~Asteroid();

	void GetShape();

	void Collided();
	void Update();
	void ChangeShape(std::vector<Vector2>& newShape); //This method will be used to change the shape of asteroids when instantiated or when shot
	int GetSplits(){ return _split; }
	void AddToSplits(int value) { _split += value; }
	void Instantiate(Vector2 spawnPosition, double speed, int entity_id, int splits);
	
	//enum ShapeID
	//{
	//	smallAsteroid1,
	//	smallAsteroid2,
	//	smallAsteroid3,
	//	smallAsteroid4
	//};



private:
	int _split = 2;
	constexpr static Vector2 _smallShape[] = { Vector2{4,4}, Vector2{4,4} };
};