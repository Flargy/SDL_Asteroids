#pragma once
#include "CollidableObject.h"
#include "Player.h"

class Alien : public CollidableObject
{
public:
	Alien(Player* player);
	~Alien();

	void CreatePoints();
	void Collide();
	void Update();
	void Instantiate(Vector2 spawnposition);
	void CalculateDirectionToPlayer();

private:
	Player* _player; // pointer to player for chasing purposes
	double _speed = 2;
};