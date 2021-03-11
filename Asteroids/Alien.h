#pragma once
#include "CollidableObject.h"
#include "Player.h"

class Alien : public CollidableObject
{
public:

	Alien();

	Alien(Player* player);
	~Alien();

	void Reset();

	void CreatePoints();
	void Collide();
	void Update(double currentTime);
	void Instantiate(Vector2 spawnposition);
	void CalculateDirectionToPlayer();
	void Shoot();
	void ReceivePlayer(Player* player);


private:
	Player* _player; // pointer to player for chasing purposes
	double _speed = 1.5;
	Vector2 directionToPlayer;
	double shotSpawnOffset = 2;
	double _height = 6;
	double _width = 10;

	double shotDelay = 5;
	double nextShotTime = 0;
	double time;
	int _alienBoundsValue = 15;

};