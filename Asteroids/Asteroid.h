#pragma once
#include <vector>
#include "CollidableObject.h"


class Asteroid : public CollidableObject
{
public:

	Asteroid(double length);
	~Asteroid();

	void CreatePoints(double length);

	void Collide();

};