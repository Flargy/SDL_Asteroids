#include "Projectile.h"

#include "SpawnSystem.h"

Projectile::Projectile(int ID)
{
	CreateDrawPoints();
	transform.SetVelocity(speed, 0);
	collisionFunction = std::bind(&Projectile::Collide, this);
}

Projectile::Projectile()
{
	CreateDrawPoints();
	transform.SetVelocity(speed, 0);
	collisionFunction = std::bind(&Projectile::Collide, this);
}

void Projectile::Collide()
{
	collisionActive = false;
}

void Projectile::CreateDrawPoints() // sets a shot to be 2x2 pixels
{
	_points = ResourceManager::getInstance()._shapes["projectile"];

	int projectileBounds[4] = {-1, 1, -1, 1};
	SetBoundingBox(projectileBounds);
}

void Projectile::Update()
{
	_timeAlive = std::chrono::steady_clock::now();
	double diff = std::chrono::duration_cast<std::chrono::duration<double>>(_timeAlive - _timeFired).count();
	if (diff > _lifeDuration)
	{
		
		_spawnSystem->DestroyProjectile(entity_id);
		return;
	}

	transform.Move();
}

void Projectile::Instantiate(Vector2 position, array2D<double, 2, 2> fireRotation, int entity_ID)
{
	_timeFired = std::chrono::steady_clock::now();
	transform.SetVelocity(4, 0);
	Vector2 offset = { 20,0 };
	offset.Rotate(fireRotation);
	offset.x += position.x;
	offset.y += position.y;
	transform.SetPosition(offset);
	transform.SetRotation(fireRotation);
}

void Projectile::Instantiate(Vector2 position, Vector2 velocityDirection, int entity_ID)
{
	transform.SetVelocity(4, 0);
	_timeFired = std::chrono::steady_clock::now();
	transform.SetPosition(position);
	transform.SetRotation(zeroRotation);
	transform.SetVelocity(velocityDirection.x * speed, velocityDirection.y * speed);
}