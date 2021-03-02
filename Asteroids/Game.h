#pragma once

#include <vector>

#include "Asteroid.h"
#include "Player.h"
#include "Projectile.h"
#include "SpawnSystem.h"
#include "Alien.h"


/*
this class represents the game state, in this game there is only one state.
*/
class Game
{
private:
	std::vector<Asteroid> _asteroids = std::vector<Asteroid>();
	std::vector<Projectile> _projectiles = std::vector<Projectile>();
	
	Player* _player;
	//Alien* _alien;

	SpawnSystem _spawnSystem;

	//space partition	
	//quad tree for asteroids.

	
	
	Game() 
	{
		_asteroids.reserve(32);
		projectiles.reserve(10);
	}

	void Update();

	
	


};