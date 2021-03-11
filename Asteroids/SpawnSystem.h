#pragma once
#include <vector>
#include <chrono>
#include "Asteroid.h"
#include "Projectile.h"
#include "Alien.h"
#include "Player.h"
#include "GameObjectBuffer.h"
//resource pool

class SpawnSystem
{
public:

	SpawnSystem(GameObjectBuffer<Asteroid, 32>& asteroids,
		GameObjectBuffer<Projectile, 16>& projectiles,
		Alien& alien, Player& player);

	/*
	todo asteroid spawn perimeter	
	*/

	template<typename TGOBuffer>
	void OverwriteWithLast(TGOBuffer buffer, int id) {
		buffer[id] = buffer[buffer.active_size() - 1];
		buffer[id].entity_id = id;
		buffer.decrease_active_size();
	}

	void SpawnAsteroids();
	void DestroyAsteroid(const int entity_id, int split);
	void DestroyProjectile(const int entity_id);
	void SpawnProjectile(Vector2 position, Matrix2D rotation);
	void SpawnProjectile(Vector2 position, Vector2 velocityDirection);
	void AlienTimeCounter(double currentTime);
	void AlienKilled(double timeOfDeath);

	void Reset();


	GameObjectBuffer<Asteroid, 32>& _asteroids;
	GameObjectBuffer<Projectile, 16>& _projectiles;
	Alien& _alien;
	Player& _player;
	std::array<Vector2, 8> _spawnPoints = {
		Vector2{20, 20},
		Vector2{400, 20},
		Vector2{780, 20,},
		Vector2{20, 780},
		Vector2{400, 780},
		Vector2{780, 780},
		Vector2{20, 400},
		Vector2{780, 400}
	};
	const int alienDelay = 30;
	int alienSpawnTime = 30;

	double _asteroidSpeed = 1;
	double _mediumMultiplier = 1.3;
	double _smallMultiplier = 1.5;
	int _startingSplits = 2;
	int _spawnPointsMaxIndex = 7;
	int _asteroidSpawnAmount = 8;
};
