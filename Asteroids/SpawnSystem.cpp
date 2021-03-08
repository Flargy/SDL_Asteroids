#include "SpawnSystem.h"
#include <cassert>

SpawnSystem::SpawnSystem(std::vector<Asteroid>& asteroids, std::vector<Projectile>& projectiles, 
	std::vector<Alien>& aliens, std::vector<Player>& player,
	std::vector<Asteroid>::iterator& asteroidIterator, std::vector<Projectile>::iterator& projectileIterator)
	: _asteroids(asteroids), _projectiles(projectiles), _aliens(aliens), _player(player),
	_asteroidsEnd(asteroidIterator), _projectilesEnd(projectileIterator)
{	
	memorySanityCheck = asteroids.data();
}

void SpawnSystem::SpawnAsteroids()
{
	assert(_asteroids.capacity() == 32 && memorySanityCheck == _asteroids.data());	
	_asteroidsEnd = _asteroids.begin(); 
	for (size_t i = 0; i < 8; i++)
	{
		*(_asteroidsEnd++) = Asteroid(50); //todo
	}
	assert(_asteroids.capacity() == 32 && memorySanityCheck == _asteroids.data());
}

void SpawnSystem::DestroyAsteroid(const int entity_id, int split) 
{
	assert(_asteroids.capacity() == 32 
		&& memorySanityCheck == _asteroids.data());
	
	if (split == 0)
	{
		_asteroids[entity_id] = *(--_asteroidsEnd);		
	}
	else if (split == 1)
	{
		//todo choose a way to create the new asteroids
		_asteroids[entity_id] = Asteroid(15);
		*(_asteroidsEnd++) = Asteroid(15);		
	}
	else if (split == 2)
	{
		//todo choose a way to create the new asteroids
		_asteroids[entity_id] = Asteroid(30);
		*(_asteroidsEnd++) = Asteroid(30);
	}
	assert(_asteroids.capacity() == 32 && memorySanityCheck == _asteroids.data());
	
}


