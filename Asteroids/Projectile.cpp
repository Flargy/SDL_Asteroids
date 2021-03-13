#include "Projectile.h"
#include "SpawnSystem.h"


Projectile::Projectile()
{
	CreateDrawPoints();
	transform.SetVelocity(0, speed);
	collisionFunction = std::bind(&Projectile::Collide, this);
}

void Projectile::Collide()
{
	alive = false;

	_spawnSystem->DestroyProjectile(entity_id);
}

void Projectile::CreateDrawPoints() 
{
	_points = ResourceManager::getInstance()._shapes["projectile"];

	int projectileBounds[4] = {-_projectileBoundsValue, _projectileBoundsValue, -_projectileBoundsValue, _projectileBoundsValue };
	SetBoundingBox(projectileBounds);
}

void Projectile::Update()
{
	_timeAlive = Time::time;
	double diff = _timeAlive - _timeFired;
	if (diff > _lifeDuration)
	{
		alive = false;
		_spawnSystem->DestroyProjectile(entity_id);
		return;
	}

	transform.Move();
}

void Projectile::Instantiate(Vector2 position, Matrix2D fireRotation, int entity_ID)
{
	Vector2 dir;

	dir.x = -fireRotation.m01; // no need to multiply X component of matrix as the ship moves in x = 1, y = 0
	dir.y = fireRotation.m11;
	Instantiate(position, dir, entity_ID);

}

void Projectile::Instantiate(Vector2 position, Vector2 velocityDirection, int entity_ID)
{
	Vector2 spawnLocation = { velocityDirection.x * 20, velocityDirection.y * 20 };

	spawnLocation.x += position.x;
	spawnLocation.y += position.y;
	_timeFired = Time::time;
	transform.SetPosition(spawnLocation);
	transform.SetVelocity(velocityDirection.x * speed, velocityDirection.y * speed);
	entity_id = entity_ID;
	alive = true;
}