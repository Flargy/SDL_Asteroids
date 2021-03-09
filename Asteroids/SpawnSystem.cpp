#include "SpawnSystem.h"
#include <cassert>

SpawnSystem::SpawnSystem(GameObjectBuffer<Asteroid, 32>& asteroids,
	GameObjectBuffer<Projectile, 16>& projectiles, Alien& alien, Player& player)
	: _asteroids(asteroids), _projectiles(projectiles), _alien(alien), _player(player)	
{	
	_asteroids.for_each([this](Asteroid& a) { a._spawnSystem = this; });
	_projectiles.for_each([this](Projectile& a) { a._spawnSystem = this; });
}

void SpawnSystem::SpawnAsteroids()
{
	_asteroids.reset();
	for (size_t i = 0; i < 8; i++) 
	{
		_asteroids.increase_active_size();
		_asteroids[i].Instantiate(_spawnPoints[i], 5.0, i, 2); // todo set spawn positions according to some perimeter
	}
}

void SpawnSystem::DestroyAsteroid(const int entity_id, int split) 
{	
	if (split == 0)
	{
		OverwriteWithLast(_asteroids, entity_id);
	}
	else if (split == 1)
	{
		//overwrite old with new asteroid info
		Vector2 pos = _asteroids[entity_id].transform.GetPosition();
		_asteroids[entity_id].Instantiate(pos, 15, entity_id, split - 1);	

		_asteroids.increase_active_size();
		_asteroids.get_last().Instantiate(pos, 15, entity_id, split - 1);
	}
	else if (split == 2)
	{
		Vector2 pos = _asteroids[entity_id].transform.GetPosition();
		_asteroids[entity_id].Instantiate(pos, 10, entity_id, split - 1);

		_asteroids.increase_active_size();
		_asteroids.get_last().Instantiate(pos, 10, entity_id, split - 1);
	}
}

void SpawnSystem::DestroyProjectile(const int entity_id) {
	//OverwriteWithLast(_projectiles, entity_id);
	_projectiles[entity_id] = _projectiles[_projectiles.active_size() - 1];
	_projectiles[entity_id].entity_id = entity_id;
	_projectiles.decrease_active_size();
}

Projectile& SpawnSystem::SpawnProjectile() {
	_projectiles.increase_active_size();
	return _projectiles.get_last();
}

