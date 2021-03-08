#include "SpawnSystem.h"
#include <cassert>

SpawnSystem::SpawnSystem(GameObjectBuffer<Asteroid, 32>& asteroids,
	GameObjectBuffer<Projectile, 16>& projectiles, Alien& alien, Player& player)
	: _asteroids(asteroids), _projectiles(projectiles), _alien(alien), _player(player)	
{	

}

void SpawnSystem::SpawnAsteroids()
{
	_asteroids.reset();
	for (size_t i = 0; i < 8; i++) 
	{
		_asteroids.increase_active_size();
		_asteroids[i].Instantiate(Vector2{100,100}, 5.0, i); // todo set spawn positions according to some perimeter
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
		_asteroids[entity_id].Instantiate(pos, 15, entity_id);	

		_asteroids.increase_active_size();
		_asteroids.get_last().Instantiate(pos, 15, entity_id);
	}
	else if (split == 2)
	{
		Vector2 pos = _asteroids[entity_id].transform.GetPosition();
		_asteroids[entity_id].Instantiate(pos, 10, entity_id);

		_asteroids.increase_active_size();
		_asteroids.get_last().Instantiate(pos, 10, entity_id);
	}
}

void SpawnSystem::DestroyProjectile(const int entity_id) {
	OverwriteWithLast(_projectiles, entity_id);
}

void SpawnSystem::SpawnProjectile(Vector2 pos, array2D<double,2,2> rotation) {
	_projectiles.increase_active_size();
	_projectiles.get_last().Instantiate(pos, rotation);
}