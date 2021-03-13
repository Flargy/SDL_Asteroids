#pragma once
#include <vector>
#include <chrono>
#include "Asteroid.h"
#include "Projectile.h"
#include "Alien.h"
#include "Player.h"
#include "GameObjectBuffer.h"
#include "Particles.h"
#include "HighscoreSystem.h"

class SpawnSystem
{
public:

	SpawnSystem(GameObjectBuffer<Asteroid, 32>& asteroids,
		GameObjectBuffer<Projectile, 16>& projectiles,
		Alien& alien, Player& player, GameObjectBuffer<Particles, 16>& particles,
		HighscoreSystem* highscoreSystem);


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
	void AlienTimeCounter();
	void AlienKilled(double timeOfDeath);
	void SpawnParticles(int numberOfParticles, int speed, Vector2 position, int lifeTime, double variance);
	void DestroyParticle(const int entity_id);

	void Reset();


	GameObjectBuffer<Asteroid, 32>& _asteroids;
	GameObjectBuffer<Projectile, 16>& _projectiles;
	GameObjectBuffer<Particles, 16>& _particles;
	Alien& _alien;
	Player& _player;
	HighscoreSystem* _highscoreSystem;
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
	int _pointsPerAlien = 200;

	double _asteroidSpeed = 60;
	double _mediumMultiplier = 1.3;
	double _smallMultiplier = 1.5;
	int _startingSplits = 2;
	int _spawnPointsMaxIndex = 7;
	int _asteroidSpawnAmount = 8;
	int _pointsPerAsteroid = 50;

	int _particleAmount = 3;
	int _particleSpeed = 120;
	int _particleLifeTime = 1;
	double _particleVariance = 0.2;
};
