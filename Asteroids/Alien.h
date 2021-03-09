#pragma once
#include "CollidableObject.h"
#include "Player.h"

class Alien : public CollidableObject
{
public:

	Alien();

	Alien(Player* player);
	~Alien();

	void CreatePoints();
	void Collide();
	void Update();
	void Instantiate(Vector2 spawnposition);
	void CalculateDirectionToPlayer();
	void Shoot();

private:
	Player* _player; // pointer to player for chasing purposes
	double _speed = 2;
	array2D<double, 2, 2> zeroRotation = { 0,0,0,0 };
	Vector2 directionToPlayer;
	double shotSpawnOffset = 2;
	double _height = 6;
	double _width = 10;
};