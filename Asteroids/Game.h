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
#include "Time.h"


class SimpleGameStates;

class Game
{
public:
	Game(SimpleGameStates& statemachine);
	//void PlayerInput();
	void GameLoop();
	void Execute();
	void Draw(Window& window);
	

private:
	double _shotDelay = 0.1;
	bool gameActive = true;
	double deltaRotation = 180 * Time::deltaTime;
	std::chrono::steady_clock::time_point _lastShot = std::chrono::steady_clock::now();

	GameObjectBuffer<Asteroid, 32> _asteroids;
	GameObjectBuffer<Projectile,16> _projectiles;
	GameObjectBuffer<Particles, 16> _particles;
	Alien _alien;
	Player _player;

	SimpleGameStates& statemachine;
	SpawnSystem _spawnSystem;
	CollisionHandler _collisionHandler;

	void Update();

	void Input();


};