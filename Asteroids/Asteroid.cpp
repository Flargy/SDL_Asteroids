#include "Asteroid.h"
#include "SpawnSystem.h"

Asteroid::Asteroid()
{
	GetShape();
	collisionFunction = std::bind(&Asteroid::Collide, this);
}

Asteroid::Asteroid(double halfSided)
{
	GetShape();
	collisionFunction = std::bind(&Asteroid::Collide, this); //this seems to work, it binds a member function to a function variable
}

void Asteroid::Steroid(Asteroid& roid) // todo remove
{
	entity_id = roid.entity_id;
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
	int asteroidBounds[4] = { -t * _asteroidBoundsValue, t * _asteroidBoundsValue, -t * _asteroidBoundsValue, t * _asteroidBoundsValue };

	SetBoundingBox(asteroidBounds);
}

void Asteroid::Collide()
{
	alive = false; 
	_spawnSystem->DestroyAsteroid(entity_id, _split);
}

void Asteroid::Update() // Updates the objects behaviour
{
	transform.Move();
}


void Asteroid::Instantiate(Vector2 spawnPosition, double speed, int entity_ID, int splits) 
{
	Vector2 vel = { 0, speed };
	int rotation = rand() % 359; // Rand is expensive as heck, remake this to another randomizer later
	transform.Rotate(rotation);
	vel.Rotate(transform.GetRotation());
	transform.SetPosition(spawnPosition);
	transform.SetVelocity(vel.x, vel.y);
	alive = true;
	_split = splits;
	entity_id = entity_ID;
	GetShape();

}