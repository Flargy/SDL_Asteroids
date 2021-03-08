#include "SpawnSystem.h"

SpawnSystem::SpawnSystem(std::vector<Asteroid>& asteroids, std::vector<Projectile>& projectiles, std::vector<Alien>& aliens, std::vector<Player>& player)
	: _asteroids(asteroids), _projectiles(projectiles), _aliens(aliens), _player(player)
{
}
