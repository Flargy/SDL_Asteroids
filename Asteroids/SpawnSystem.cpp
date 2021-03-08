#include "SpawnSystem.h"
#include <cassert>

SpawnSystem::SpawnSystem(std::vector<Asteroid>& asteroids, std::vector<Projectile>& projectiles,
 
	std::vector<Alien>& aliens,
 std::vector<Player>& player)
	: _asteroids(asteroids), _projectiles(projectiles), _aliens(aliens), _player(player)
	
{	
	memorySanityCheck = asteroids.data();
}

void SpawnSystem::SpawnAsteroids()
{
	assert(_asteroids.capacity() == 32 && memorySanityCheck == _asteroids.data());	

	_asteroids.resize(8, Asteroid(50));
	for (size_t i = 0; i < 8; i++) 
	{
		_asteroids[i].entity_id = i; //todo asteroid setup
	}

	assert(_asteroids.capacity() == 32 && memorySanityCheck == _asteroids.data());
}

void SpawnSystem::DestroyAsteroid(const int entity_id, int split) 
{
	assert(_asteroids.capacity() == 32 && memorySanityCheck == _asteroids.data());
	
	int size = _asteroids.size();

	if (split == 0)
	{
		_asteroids[entity_id] = _asteroids[--size];
		_asteroids[entity_id].entity_id = entity_id;
		_asteroids.pop_back();
	}
	else if (split == 1)
	{
		//todo choose a way to create the new asteroids
		_asteroids[entity_id] = Asteroid(15, entity_id);
		_asteroids.push_back(Asteroid(15, entity_id));
	}
	else if (split == 2)
	{
		//todo choose a way to create the new asteroids
		_asteroids[entity_id] = Asteroid(30, entity_id);
		_asteroids.push_back(Asteroid(30, entity_id));
	}
	assert(_asteroids.capacity() == 32 && memorySanityCheck == _asteroids.data());
	
}


