#pragma once
#include "CollidableObject.h"
#include <chrono>

class Projectile : public CollidableObject
{
public:
	Projectile(int ID);
	Projectile();
	~Projectile(){}

	void Collide();
	void CreateDrawPoints();

	void Update();
	void Instantiate(Vector2 spawnPosition, array2D<double, 2, 2> fireRotation);
	void Instantiate(Vector2 spawnPosition, Vector2 velocityDirection );


private:
	std::chrono::steady_clock::time_point _timeFired = std::chrono::steady_clock::now(); // can be removed if we we dont want projectiles to have a fixed lifetime
	std::chrono::steady_clock::time_point _timeAlive = std::chrono::steady_clock::now();
	double _lifeDuration = 1.5;
	double speed = 4;
	array2D<double, 2, 2> zeroRotation = { 0,0,0,0 };
};