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

#include "StateMachine.h"
#include "MenuState.h"
#include "PlayState.h"

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
	
	GameState a;
	a.getState<MenuState<GameState>>().Init();
	a.getState<PlayState<GameState>>().Init();


	init();
	windowHeight = 800;
	windowWidth = 800;
	Window window = Window("Asteroids", windowWidth, windowHeight);
	Game session(window);
	session.GameLoop();

	return 0;
}