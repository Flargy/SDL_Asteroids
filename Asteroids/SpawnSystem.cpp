#include "SpawnSystem.h"
#include <cassert>
#include "Time.h"


SpawnSystem::SpawnSystem(GameObjectBuffer<Asteroid, 32>& asteroids,
	GameObjectBuffer<Projectile, 16>& projectiles, Alien& alien, Player& player,
	GameObjectBuffer<Particles, 16>& particles)
	: _asteroids(asteroids), _projectiles(projectiles), _alien(alien), _player(player), _particles(particles)
{	
	_asteroids.for_each([this](Asteroid& a) { a._spawnSystem = this; });
	_projectiles.for_each([this](Projectile& a) { a._spawnSystem = this; });
	_particles.for_each([this](Particles& a) { a._spawnSystem = this; });
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
	Vector2 pos = _asteroids[entity_id].transform.GetPosition();

 	if (split == 0)
	{
		SpawnParticles(_particleAmount * split, _particleSpeed, pos, _particleLifeTime, _particleVariance);

		_asteroids[entity_id] = _asteroids[_asteroids.active_size() - 1];
		_asteroids[entity_id].collisionFunction = std::bind(&Asteroid::Collide, &_asteroids[entity_id]);
		_asteroids[entity_id].entity_id = entity_id;
		_asteroids.decrease_active_size();
		/*if (_asteroids.active_size() <= 0)
		{
			SpawnAsteroids();
		}*/
	}
	else if (split == 1)
	{
		SpawnParticles(_particleAmount * split, _particleSpeed, pos, _particleLifeTime, _particleVariance);
		//overwrite old with new asteroid info
		_asteroids[entity_id].Instantiate(pos, _asteroidSpeed * _smallMultiplier, entity_id, split - 1);

		_asteroids.increase_active_size();
		_asteroids.get_last().Instantiate(pos, _asteroidSpeed * _smallMultiplier, _asteroids.active_size() - 1, split - 1);
	}
	else if (split == 2)
	{
		SpawnParticles(_particleAmount * split, _particleSpeed, pos, _particleLifeTime, _particleVariance);
		
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
	_particles.reset();
	_player.Reset();
	_alien.Reset();
}

void SpawnSystem::AlienTimeCounter()
{
	if (!_alien.alive && Time::time >= alienSpawnTime)
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

void SpawnSystem::SpawnParticles(int numberOfParticles, int speed, Vector2 position, int lifeTime, double variance)
{
	_particles.increase_active_size();
	_particles.get_last().Instantiate(numberOfParticles, speed, 
		position, lifeTime, variance, _particles.active_size() - 1);
}

void SpawnSystem::DestroyParticle(const int entity_id)
{
	assert(_particles[_particles.active_size() - 1].entity_id == _particles.active_size() - 1);
	_particles[entity_id] = std::move(_particles[_particles.active_size() - 1]);
	_particles[entity_id].entity_id = entity_id;
	_particles.decrease_active_size();
}