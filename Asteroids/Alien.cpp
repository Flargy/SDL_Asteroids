#include "Alien.h"

Alien::Alien()
{
}



Alien::Alien(Player* player) : _player(player)
{
	collisionFunction = std::bind(&Alien::Collide, this);
	transform.SetVelocity(_speed,0);
	CreatePoints();
}

Alien::~Alien()
{

}

void Alien::CreatePoints()
{
	_points = ResourceManager::getInstance()._shapes["alien"];
}

void Alien::Collide()
{
	collisionActive = false;
	// collision functionality here
}

void Alien::Update()
{
	CalculateDirectionToPlayer();
	transform.Move();
}

void Alien::CalculateDirectionToPlayer()
{
	Vector2 playerPos = _player->transform.GetPosition();
	Vector2 currentPosition = transform.GetPosition();
	
	directionToPlayer = { playerPos.x - currentPosition.x, playerPos.y - currentPosition.y };

	double currentMagnitude = sqrt(pow(directionToPlayer.x, 2) + pow(directionToPlayer.y, 2));
	if (currentMagnitude > _speed)
	{
		double reductionValue = fmin(currentMagnitude, _speed) / currentMagnitude;
		directionToPlayer.x *= reductionValue;
		directionToPlayer.y *= reductionValue;
	}

	transform.SetVelocity(directionToPlayer.x * _speed, directionToPlayer.y * _speed);
}

void Alien::Shoot()
{
	// fetch projectile to spawn
	// projectile.transform.SetPosition(zeroRotation);
	// Vector2 spawnLocation = transform.GetPosition();
	// spawnLocation.x += directionToPlayer.x * shotSpawnOffset;
	// spawnLocation.y += directionToPlayer.y * shotSpawnOffset;
	// projectile.Instantiate(spawnLocation, directionToPlayer);
}

void Alien::Instantiate(Vector2 spawnPosition)
{
	transform.SetPosition(spawnPosition);
	collisionActive = true;
}

