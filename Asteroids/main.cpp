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
#include <SDL_ttf.h>

int windowHeight, windowWidth;


void initResources()
{
	if (TTF_Init() == -1)
	{
		printf("TTF_Init: %s\n", TTF_GetError());
	}

	auto& resources = ResourceManager::getInstance();
		
	resources.AddShape("smallAsteroid", smallAsteroid);
	resources.AddShape("mediumAsteroid", mediumAsteroid);
	resources.AddShape("largeAsteroid", largeAsteroid);
	resources.AddShape("player", player);
	resources.AddShape("alien", alien);
	resources.AddShape("projectile", projectile);
	resources.AddFont("arial", "res/arial.ttf", 20);

}

int main(int args, char** argv) {
	
	initResources();
	
	windowHeight = 800;
	windowWidth = 800;
	Window window = Window("Asteroids", windowWidth, windowHeight);

	SimpleGameStates gameState;

	using namespace std::chrono;
	double accumulator = 0.0;
	steady_clock::time_point currentTime = steady_clock::now();

	while (gameState.gameActive)
	{
		window.SetBackground();
		steady_clock::time_point newTime = steady_clock::now();
		double frameTime = duration_cast<duration<double>>(newTime - currentTime).count();
		currentTime = newTime;

		accumulator += frameTime;

		while (accumulator >= Time::deltaTime)
		{			
			gameState.Execute();

			Time::time += Time::deltaTime;
			accumulator -= Time::deltaTime;
		}		
		gameState.Draw(window);
		window.PresentRenderer();

	}

	return 0;
}