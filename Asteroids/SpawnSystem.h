#pragma once
#include <vector>
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
	Projectile& SpawnProjectile();


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

};
