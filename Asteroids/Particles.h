#pragma once
#include "Global.h"
#include "Vector2.h"
#include <vector>
#include <SDL.h>

class SpawnSystem;

class Particles
{
public:
	Particles();


	void Instantiate(int numberOfParticles, int speed, Vector2 spawnPos,
		int lifeTime, double variance, int entity_ID);
	void Update();
	void Draw(SDL_Renderer* renderer);

	int entity_id = 0;
	SpawnSystem* _spawnSystem;
private:

	struct Particle {
		Vector2 position = { 0,0 };
		Vector2 velocity = { 0,0 };
		double drag = 1;
		double deathTime = 0;
	};

	double RandVariance(double variance);

	std::vector<Particle>::iterator end;
	std::vector<Particle> particles = {};

};

