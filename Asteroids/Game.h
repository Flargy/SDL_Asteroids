#pragma once

#include <vector>

#include "Asteroid.h"
#include "Player.h"
#include "Projectile.h"
#include "SpawnSystem.h"
#include "Alien.h"
#include <chrono>
#include "Renderer.h"
#include "CollisionHandler.h"


/*
this class represents the game state, in this game there is only one state.
*/
class Game
{
public:
	void PlayerInput();
	void GameLoop();
	Game(Window& window);

private:
	double _shotDelay = 0.7;
	std::chrono::steady_clock::time_point _lastShot = std::chrono::steady_clock::now();
	
	std::vector<Asteroid> _asteroids = std::vector<Asteroid>();
	std::vector<Projectile> _projectiles = std::vector<Projectile>();
	std::vector<Alien> _aliens = std::vector<Alien>();
	std::vector<Player> _player = std::vector<Player>();
	
	//Player* _player;
	//Alien* _alien;

	SpawnSystem _spawnSystem;
	Window& _renderer;
	CollisionHandler _collisionHandler;

	//space partition	
	//quad tree for asteroids.

	
	
	

	void Update();

	
	


};