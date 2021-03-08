#include "Asteroid.h"

Asteroid::Asteroid()
{
}

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
	active = false;
	// collision code here
	// activate function in spawn system that takes ints between 1-3 as input to spawn new asteroids
}

void Asteroid::Update() // Updates the objects behaviour
{
	transform.Move();
}

void Asteroid::ChangeShape(std::vector<Vector2>& newShape) // changes its current shape to a new one
{
	_points = newShape;
}

void Asteroid::Instantiate(Vector2 spawnPosition, double speed, int entity_id) // activates the object at a new position
{
	transform.SetPosition(spawnPosition);
	transform.SetVelocity(speed, 0);
	active = true;

	int rotation = rand() % 359; // Rand is expensive as heck, remake this to another randomizer later
	transform.Rotate(rotation);
}