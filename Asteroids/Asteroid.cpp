#include "Asteroid.h"

Asteroid::Asteroid(double halfSided)
{
	CreatePoints(halfSided);
	collisionFunction = std::bind(&Asteroid::Collide, this); //this seems to work, it binds a member function to a function variable
}

Asteroid::~Asteroid()
{
}

void Asteroid::CreatePoints(double halfSide)
{
	_points.push_back(Vector2 {-halfSide, halfSide});
	_points.push_back(Vector2 {halfSide, -halfSide});
	_points.push_back(Vector2 {halfSide, halfSide});

	int asteroidBounds[4] = { -halfSide, halfSide, -halfSide, halfSide };

	SetBoundingBox(asteroidBounds);
}

void Asteroid::Collide()
{
	// collision code here
}