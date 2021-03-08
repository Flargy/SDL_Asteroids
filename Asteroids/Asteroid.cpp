#include "Asteroid.h"

Asteroid::Asteroid(double halfSided)
{
	CreatePoints(halfSided);
	collisionFunction = std::bind(&Asteroid::Collide, this); //this seems to work, it binds a member function to a function variable
}

Asteroid::Asteroid(double halfSided, int entity_id)
{
	CreatePoints(halfSided);
	collisionFunction = std::bind(&Asteroid::Collide, this); 
	this->entity_id = entity_id;
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
	// activate function in spawn system that takes ints between 1-3 as input to spawn new asteroids
}

void Asteroid::Update()
{
	transform.Move();
}

void Asteroid::ChangeShape(std::vector<Vector2>& newShape)
{
	_points = newShape;
}

void Asteroid::Instantiate()
{

}