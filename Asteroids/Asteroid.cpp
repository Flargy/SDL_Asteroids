#include "Asteroid.h"
#include "SpawnSystem.h"

Asteroid::Asteroid()
{
}

Asteroid::Asteroid(double halfSided)
{
	GetShape();
	collisionFunction = std::bind(&Asteroid::Collided, this); //this seems to work, it binds a member function to a function variable
}

Asteroid::~Asteroid()
{
}

void Asteroid::GetShape()
{
	std::string key;
	switch (_split)
	{
	case 2:
		key = "largeAsteroid";
		break;
	case 1:
		key = "mediumAsteroid";
		break;
	case 0:
		key = "smallAsteroid";
		break;
	default:
		break;
	}

	_points = ResourceManager::getInstance()._shapes[key];

	auto t = _split + 1;
	int asteroidBounds[4] = { -t * 5, t * 5, -t * 5, t * 5};

	SetBoundingBox(asteroidBounds);
}

void Asteroid::Collided()
{
	collisionActive = false;
	_spawnSystem->DestroyAsteroid(entity_id, _split);
}

void Asteroid::Update() // Updates the objects behaviour
{
	transform.Move();
}

void Asteroid::ChangeShape(std::vector<Vector2>& newShape) // changes its current shape to a new one
{
	//_points = newShape;
}

void Asteroid::Instantiate(Vector2 spawnPosition, double speed, int entity_id, int splits) // activates the object at a new position
{
	transform.SetPosition(spawnPosition);
	transform.SetVelocity(speed, 0);
	collisionActive = true;

	int rotation = rand() % 359; // Rand is expensive as heck, remake this to another randomizer later
	transform.Rotate(rotation);
}