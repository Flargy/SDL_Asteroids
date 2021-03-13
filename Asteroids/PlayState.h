#pragma once

#include "GameObjectBuffer.h"
#include "Asteroid.h"
#include "Projectile.h"
#include "Particles.h"
#include <vector>

template<typename TStateMachine>
class PlayState : TStateMachine::State
{
	

public:
	PlayState(TStateMachine& m);
	
	void Init();

	void Prepare();

	void Execute();

	void End();

	void Draw(Window& window);
	
	double _shotDelay = 0.1;
	bool gameActive = true;
	double deltaRotation = 180 * Time::deltaTime;
	std::chrono::steady_clock::time_point _lastShot = std::chrono::steady_clock::now();


private:

	void Input();

	void Update();
	
	GameObjectBuffer<Asteroid, 32> _asteroids;
	GameObjectBuffer<Projectile, 16> _projectiles;
	GameObjectBuffer<Particles, 16> _particles;
	Alien _alien;
	Player _player;

	SpawnSystem _spawnSystem;
	//Window& _renderer;
	CollisionHandler _collisionHandler;

};

