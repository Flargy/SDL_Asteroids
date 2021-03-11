#include "Alien.h"
#include <chrono>
#include "SpawnSystem.h"

Alien::Alien()
{
	CreatePoints();
	alive = false;
	transform.SetVelocity(_speed, 0);
	collisionFunction = std::bind(&Alien::Collide, this);
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

void Alien::Reset()
{
	alive = false;
	_spawnSystem->AlienKilled(time);
}

void Alien::CreatePoints()
{
	_points = ResourceManager::getInstance()._shapes["alien"];
	int alienBounds[4] = { -_alienBoundsValue, _alienBoundsValue, -_alienBoundsValue, _alienBoundsValue };
	SetBoundingBox(alienBounds);
}

void Alien::Collide()
{
	alive = false;
	_spawnSystem->AlienKilled(time);
}

void Alien::Update(double currentTime)
{
	if (_player->alive == false)
	{
		return;
	}
	time = currentTime;
	CalculateDirectionToPlayer();
	transform.Move();

	if (currentTime >= nextShotTime)
	{
		nextShotTime = currentTime + shotDelay;
		Shoot();
	}
}

void Alien::CalculateDirectionToPlayer()
{
	Vector2 playerPos = _player->transform.GetPosition();
	Vector2 currentPosition = transform.GetPosition();
	
	directionToPlayer = (playerPos - currentPosition).Normalized();

	transform.SetVelocity(directionToPlayer.x * _speed, directionToPlayer.y * _speed);
}

void Alien::Shoot()
{

	 Vector2 spawnLocation = transform.GetPosition();
	 spawnLocation.x += directionToPlayer.x * shotSpawnOffset;
	 spawnLocation.y += directionToPlayer.y * shotSpawnOffset;
	 _spawnSystem->SpawnProjectile(spawnLocation, directionToPlayer);
}

void Alien::Instantiate(Vector2 spawnPosition)
{
	transform.SetPosition(spawnPosition);
	alive = true;
}

void Alien::ReceivePlayer(Player* player)
{
	_player = player;
}

