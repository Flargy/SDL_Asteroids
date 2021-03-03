#pragma once
#include <vector>
#include "Transform.h"
#include "CollidableObject.h"


class Asteroid : CollidableObject
{
public:

	Asteroid()
	{
		collisionFunction = std::bind(&Asteroid::Collide, this); //this seems to work, it binds a member function to a function variable
	}

	void Collide();

};