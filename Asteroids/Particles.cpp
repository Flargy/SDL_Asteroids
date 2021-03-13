#include "Particles.h"
#include <algorithm>
#include <math.h>
#include "SpawnSystem.h"
#include "Time.h"
#define TAU 6.28318530718


Particles::Particles() 
{

}

//todo remove
//Particles& Particles::operator=(Particles&& src)
//{
//	int iteratorIndex = std::distance(src.particles.begin(), src.end);
//
//	// TODO: insert return statement here
//	particles = std::move(src.particles);
//	end = particles.begin() + iteratorIndex;
//	return *this;
//}

void Particles::Replace(Particles&& src) {
	int iteratorIndex = std::distance(src.particles.begin(), src.end);

	// TODO: insert return statement here
	particles = std::move(src.particles);
	end = particles.begin() + iteratorIndex;
};


void Particles::Instantiate(int numberOfParticles, int speed, Vector2 spawnPos, int lifeTime, double variance, int entity_ID)
{	
	// get time from static function
	entity_id = entity_ID;
	particles.resize(fmax(numberOfParticles, 1));
	for (auto& particle : particles)
	{
		particle.position = spawnPos;
		double randTau = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / TAU));
		particle.velocity = { cos(randTau), sin(randTau) };
		particle.velocity = particle.velocity * speed ;
		particle.deathTime = Time::time + (lifeTime);
	}	
	end = particles.end();
	std::sort(particles.begin(), end, [](Particle particle1, Particle particle2) -> bool { return (particle1.deathTime > particle2.deathTime); });
}

//This will generate a number from -variance to +variance:
double Particles::RandVariance(double variance)
{
	return (static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (2 * variance)))) - variance;
}

void Particles::Update()
{
	auto it = particles.begin();

	if (it->deathTime < Time::time)
	{
		_spawnSystem->DestroyParticle(entity_id);
		return;
	}
	

	while (it != end && it->deathTime > Time::time) // todo get time from static or update?
	{
		it->position = it->position + (it->velocity * Time::deltaTime);
		it->velocity = it->velocity * it->drag;
		it++;
	}
	end = it;
		
}

void Particles::Draw(SDL_Renderer* renderer)
{
	SDL_Rect rect;
	rect.w = _particleSize;
	rect.h = _particleSize;

	double currentTime = Time::time;
	auto it = particles.begin();
	while (it != end) // todo get time from static or update?
	{
		rect.x = it->position.x - (rect.w >> 1);
		rect.y = it->position.y - (rect.h >> 1);
		SDL_RenderFillRect(renderer, &rect);
		it++;
	}
}