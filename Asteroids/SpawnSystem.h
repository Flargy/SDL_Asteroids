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

	SpawnSystem(std::vector<Asteroid>& asteroids, std::vector<Projectile>& projectile, 
		std::vector<Alien>& aliens, std::vector<Player>& player,
		std::vector<Asteroid>::iterator& asteroidIterator, 
		std::vector<Projectile>::iterator& projectileIterator);

	/*
	asteroid spawn perimeter	
	*/

	void SpawnAsteroids();

	void DestroyAsteroid(const int entity_id, int split);

	Asteroid* memorySanityCheck;

	std::vector<Asteroid>& _asteroids;
	std::vector<Projectile>& _projectiles;
	std::vector<Alien>& _aliens;
	std::vector<Player>& _player;

	std::vector<Asteroid>::iterator& _asteroidsEnd;
	std::vector<Projectile>::iterator& _projectilesEnd;
	//std::vector<Alien>::iterator _aliensEnd;
	//std::vector<Player>::iterator _playerEnd;
};
