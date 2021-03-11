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
	
	init();
	windowHeight = 800;
	windowWidth = 800;
	Window window = Window("Asteroids", windowWidth, windowHeight);
	Game session = Game(window);
	session.GameLoop();

	return 0;
}