#pragma once
#include <vector>
#include "CollidableObject.h"


class Asteroid : public CollidableObject
{
public:
	Asteroid();
	Asteroid(double length);
	~Asteroid();

	void GetShape();

	void Collide();
	void Update();
	int GetSplits(){ return _split; }
	void AddToSplits(int value) { _split += value; }
	void Instantiate(Vector2 spawnPosition, double speed, int entity_id, int splits);


private:
	int _split = 2;
	constexpr static Vector2 _smallShape[] = { Vector2{4,4}, Vector2{4,4} };
};