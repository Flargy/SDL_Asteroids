#pragma once

#include <vector>

#include "Asteroid.h"
#include "Player.h"
#include "Projectile.h"
#include "SpawnSystem.h"
#include "Alien.h"
#include <chrono>


/*
this class represents the game state, in this game there is only one state.
*/
class Game
{
public:
	void PlayerInput();


private:
	double _shotDelay = 0.7;
	std::chrono::steady_clock::time_point _lastShot = std::chrono::steady_clock::now();
	
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
		//projectiles.reserve(10);
	}

	void Update();

	
	


};