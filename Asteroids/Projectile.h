#pragma once
#include "CollidableObject.h"
#include <chrono>


class Projectile : public CollidableObject
{
public:
	Projectile();
	~Projectile(){}

	void Collide();
	void CreateDrawPoints();

	void Update();
	void Instantiate(Vector2 spawnPosition, Matrix2D fireRotation, int entity_ID);
	void Instantiate(Vector2 spawnPosition, Vector2 velocityDirection, int entity_ID);
	


private:
	double _timeFired = 0;
	double _timeAlive = 0;
	double _lifeDuration = 2;
	double speed = 360;
	double _projectileBoundsValue = 4;
};