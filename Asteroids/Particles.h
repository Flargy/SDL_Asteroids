#pragma once
#include "Global.h"
#include "Vector2.h"
#include <vector>
#include <SDL.h>

class Particles
{

	struct Particle {
		Vector2 position = { 0,0 };
		Vector2 velocity = { 0,0 };
		double drag = 1;
		double deathTime = 0;
	};


	std::vector<Particle>::iterator end;

	std::vector<Particle> particles = {};



	bool particleLifetimeOrder(Particle particle1, Particle particle2);

	Particles(int numberOfParticles, int speed, Vector2 spawnPos,
		int lifeTime, double variance, double spawnTime);

	double RandVariance(double variance);

	void Update(double time);
	
	void Draw(SDL_Renderer* renderer) {
		SDL_Rect rect;
		rect.w = 2;
		rect.h = 2;
		auto it = particles.begin();
		while (it != end) // todo get time from static or update?
		{
			rect.x = it->position.x - (rect.w >> 1);
			rect.y = it->position.y - (rect.h >> 1);
			
		}
		SDL_RenderDrawRect(renderer, &rect);
	}

};

