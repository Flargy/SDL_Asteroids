#pragma once
#include <vector>
#include "Transform.h"
#include "CollidableObject.h"


class Asteroid : public CollidableObject
{
public:

	Asteroid(double length);
		//collisionFunction = std::bind(&Asteroid::Collide, this); //this seems to work, it binds a member function to a function variable
	~Asteroid();

	void CreatePoints(double length);

	void Collide();

};