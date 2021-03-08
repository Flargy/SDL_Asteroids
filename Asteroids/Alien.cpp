#include "Alien.h"

Alien::Alien()
{
}



Alien::Alien(Player* player) : _player(player)
{
	collisionFunction = std::bind(&Alien::Collide, this);
	transform.SetVelocity(_speed,0);
}

Alien::~Alien()
{

}

void Alien::CreatePoints()
{
	// set up alien shape here
}

void Alien::Collide()
{
	// collision functionality here
}

void Alien::Update()
{

	transform.Move();
}

void Alien::CalculateDirectionToPlayer()
{
	Vector2 playerPos = _player->transform.GetPosition();
	Vector2 currentPosition = transform.GetPosition();
	
	Vector2 directionToPlayer = { playerPos.x - currentPosition.x, playerPos.y - currentPosition.y };

	double currentMagnitude = sqrt(pow(directionToPlayer.x, 2) + pow(directionToPlayer.y, 2));
	if (currentMagnitude > _speed)
	{
		double reductionValue = fmin(currentMagnitude, _speed) / currentMagnitude;
		directionToPlayer.x *= reductionValue;
		directionToPlayer.y *= reductionValue;
	}

	transform.SetVelocity(directionToPlayer.x, directionToPlayer.y);
}

void Alien::Instantiate(Vector2 spawnPosition)
{
	transform.SetPosition(spawnPosition);
	active = true;
}

