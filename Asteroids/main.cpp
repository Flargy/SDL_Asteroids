#include <memory>
#include <map>
#include <chrono>
#include <vector>
#include "Renderer.h"
#include "Transform.h"
#include "CollisionHandler.h"
#include "Global.h"
#include "Game.h"

#include "ResourceManager.h"
#include <string>

#include "ShapeData.h"

#include "SimpleGameStates.h"

int windowHeight, windowWidth;


void init()
{
	auto& resources = ResourceManager::getInstance();
		
	resources.AddShape("smallAsteroid", smallAsteroid);
	resources.AddShape("mediumAsteroid", mediumAsteroid);
	resources.AddShape("largeAsteroid", largeAsteroid);
	resources.AddShape("player", player);
	resources.AddShape("alien", alien);
	resources.AddShape("projectile", projectile);
}

int main(int args, char** argv) {
	
	//resources todo rename this
	init();
	
	windowHeight = 800;
	windowWidth = 800;
	Window window = Window("Asteroids", windowWidth, windowHeight);

	SimpleGameStates gameState;
	//a.Execute();

	using namespace std::chrono;
	bool quit = false;
	bool play = false;
	double t = 0.0;
	double accumulator = 0.0;
	steady_clock::time_point currentTime = steady_clock::now();

	while (gameState.gameActive)
	{
		steady_clock::time_point newTime = steady_clock::now();
		double frameTime = duration_cast<duration<double>>(newTime - currentTime).count();
		currentTime = newTime;

		accumulator += frameTime;
		window.SetBackground();

		while (accumulator >= Time::deltaTime)
		{			
			gameState.Execute();

			Time::time += Time::deltaTime;
			accumulator -= Time::deltaTime;
		}		
		gameState.Draw(window);
	}

	return 0;
}