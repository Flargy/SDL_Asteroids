#include "Projectile.h"

Projectile::Projectile()
{
	CreatePoints();
	collisionFunction = std::bind(&Projectile::Collide, this);
}

void Projectile::Collide()
{
	active = false;
}

void Projectile::CreatePoints() // sets a shot to be 2x2 pixels
{
	_points.push_back(Vector2{ -1,1 });
	_points.push_back(Vector2{ -1,-1 });
	_points.push_back(Vector2{ 1,-1 });
	_points.push_back(Vector2{ 1,1 });

	int projectileBounds[4] = {-1, 1, -1, 1};
	SetBoundingBox(projectileBounds);
}

void Projectile::Update()
{
	_timeAlive = std::chrono::steady_clock::now();
	double diff = std::chrono::duration_cast<std::chrono::duration<double>>(_timeAlive - _timeFired).count();
	if (diff > _lifeDuration)
	{
		active = false;
		return;
	}

	transform.Move();
}

void Projectile::Instantiate(Vector2 position, array2D<double, 2, 2> fireRotation)
{
	_timeFired = std::chrono::steady_clock::now();
	transform.SetVelocity(4, 0);
	transform.SetPosition(position);
	transform.SetRotation(fireRotation);
	active = true;
}