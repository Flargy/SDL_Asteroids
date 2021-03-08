#pragma once
#include "CollidableObject.h"
#include <chrono>

class Projectile : public CollidableObject
{
public:
	Projectile();
	~Projectile(){}

	void Collide();
	void CreatePoints();

	void Update();
	void Instantiate();


private:
	std::chrono::steady_clock::time_point _timeFired = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point _timeAlive = std::chrono::steady_clock::now();
	double _lifeDuration = 1.5;
};