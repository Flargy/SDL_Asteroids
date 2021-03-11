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
#include "GameObjectBuffer.h"
#include "Particles.h"

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
	double _shotDelay = 0.1;
	bool gameActive = true;
	std::chrono::steady_clock::time_point _lastShot = std::chrono::steady_clock::now();

	GameObjectBuffer<Asteroid, 32> _asteroids;
	GameObjectBuffer<Projectile,16> _projectiles;
	GameObjectBuffer<Particles, 16> _particles;
	Alien _alien;
	Player _player;

	SpawnSystem _spawnSystem;
	Window& _renderer;
	CollisionHandler _collisionHandler;

	void Update();

};