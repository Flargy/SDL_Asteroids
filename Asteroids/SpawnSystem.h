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
	void SpawnProjectile(Vector2 pos, array2D<double, 2, 2> rotation);


	GameObjectBuffer<Asteroid, 32>& _asteroids;
	GameObjectBuffer<Projectile, 16>& _projectiles;
	Alien& _alien;
	Player& _player;

};
