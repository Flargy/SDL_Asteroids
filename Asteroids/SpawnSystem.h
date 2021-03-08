#pragma once
#include <vector>
#include "Asteroid.h"
#include "Projectile.h"
#include "Alien.h"
#include "Player.h"
//resource pool

class SpawnSystem
{
public:

	SpawnSystem(std::vector<Asteroid>& asteroids, std::vector<Projectile>& projectile, std::vector<Alien>& aliens, std::vector<Player>& player);

	/*
	asteroid spawn perimeter
	
	*/

	//SpawnAsteroids()

	std::vector<Asteroid>& _asteroids;
	std::vector<Projectile>& _projectiles;
	std::vector<Alien>& _aliens;
	std::vector<Player>& _player;
};
