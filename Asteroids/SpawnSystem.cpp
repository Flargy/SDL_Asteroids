#include "SpawnSystem.h"
#include <cassert>

SpawnSystem::SpawnSystem(GameObjectBuffer<Asteroid, 32>& asteroids,
	GameObjectBuffer<Projectile, 16>& projectiles, Alien& alien, Player& player)
	: _asteroids(asteroids), _projectiles(projectiles), _alien(alien), _player(player)	
{	
	_asteroids.for_each([this](Asteroid& a) { a._spawnSystem = this; });
	_projectiles.for_each([this](Projectile& a) { a._spawnSystem = this; });
	_alien._spawnSystem = this;
}

void SpawnSystem::SpawnAsteroids()
{
	_asteroids.reset();
	for (size_t i = 0; i < _asteroidSpawnAmount; i++)
	{
		_asteroids.increase_active_size();
		_asteroids[i].Instantiate(_spawnPoints[i], _asteroidSpeed, i, _startingSplits); // todo set spawn positions according to some perimeter
	}
}

void SpawnSystem::DestroyAsteroid(const int entity_id, int split) 
{	
 	if (split == 0)
	{
		_asteroids[entity_id] = _asteroids[_asteroids.active_size() - 1];
		_asteroids[entity_id].collisionFunction = std::bind(&Asteroid::Collide, &_asteroids[entity_id]);
		_asteroids[entity_id].entity_id = entity_id;
		_asteroids.decrease_active_size();
	}
	else if (split == 1)
	{
		//overwrite old with new asteroid info
		Vector2 pos = _asteroids[entity_id].transform.GetPosition();
		_asteroids[entity_id].Instantiate(pos, _asteroidSpeed * _smallMultiplier, entity_id, split - 1);

		_asteroids.increase_active_size();
		_asteroids.get_last().Instantiate(pos, _asteroidSpeed * _smallMultiplier, _asteroids.active_size() - 1, split - 1);
	}
	else if (split == 2)
	{
		Vector2 pos = _asteroids[entity_id].transform.GetPosition();
		_asteroids[entity_id].Instantiate(pos, _asteroidSpeed * _mediumMultiplier, entity_id, split - 1);

		_asteroids.increase_active_size();
		_asteroids.get_last().Instantiate(pos, _asteroidSpeed * _mediumMultiplier, _asteroids.active_size() - 1, split - 1);
	}
}

void SpawnSystem::DestroyProjectile(const int entity_id) {
	_projectiles[entity_id] = _projectiles[_projectiles.active_size() - 1];
	_projectiles[entity_id].collisionFunction = std::bind(&Projectile::Collide, &_projectiles[entity_id]);
	_projectiles[entity_id].entity_id = entity_id;
	_projectiles.decrease_active_size();
}

void SpawnSystem::SpawnProjectile(Vector2 position, Matrix2D rotation) {
	_projectiles.increase_active_size();
	_projectiles.get_last().Instantiate(position, rotation, _projectiles.active_size() - 1);
}

void SpawnSystem::SpawnProjectile(Vector2 position, Vector2 velocityDirection)
{
	_projectiles.increase_active_size();
	_projectiles.get_last().Instantiate(position, velocityDirection, _projectiles.active_size() - 1);
}

void SpawnSystem::Reset()
{
	SpawnAsteroids();
	_projectiles.reset();
	_player.Reset();
	_alien.Reset();
}

void SpawnSystem::AlienTimeCounter(double currentTime)
{
	if (!_alien.alive && currentTime >= alienSpawnTime)
	{
		_alien.alive = true;
		int randomPoint = rand() % _spawnPointsMaxIndex;
		_alien.transform.SetPosition(_spawnPoints[randomPoint].x, _spawnPoints[randomPoint].y);
	}
}

void SpawnSystem::AlienKilled(double timeOfDeath)
{
	alienSpawnTime = timeOfDeath + alienDelay;
}

