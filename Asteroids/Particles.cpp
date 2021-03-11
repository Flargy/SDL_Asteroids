#include "Particles.h"
#include <algorithm>
#include <math.h>
#define TAU 6.28318530718


bool Particles::particleLifetimeOrder(Particle particle1, Particle particle2) { return (particle1.deathTime < particle2.deathTime); }

Particles::Particles(int numberOfParticles, int speed, Vector2 spawnPos, int lifeTime, double variance, double spawnTime)
{	
	particles.resize(numberOfParticles * RandVariance(variance), { spawnPos, { 0,0 }, 1, 0 } );
	for (auto& particle : particles)
	{
		double randTau = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / TAU));
		particle.velocity = { cos(randTau), sin(randTau) };
		particle.velocity = particle.velocity * speed * RandVariance(variance);
		particle.deathTime = spawnTime + (lifeTime* RandVariance(variance));
	}	
	end = particles.end();
	std::sort(particles.begin(), end, particleLifetimeOrder);
}

//This will generate a number from -variance to +variance:
double Particles::RandVariance(double variance)
{
	return (static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (2 * variance)))) - variance;
}

void Particles::Update(double time)
{
	auto it = particles.begin();
	while (it->deathTime < time) // todo get time from static or update?
	{
		it->position = it->position + it->velocity;
	}
	end = it;
}
