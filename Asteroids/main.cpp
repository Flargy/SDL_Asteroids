#include <memory>
#include <map>
#include <chrono>
#include <vector>
#include "Renderer.h"
#include "Transform.h"
#include "CollisionHandler.h"
#include "Global.h"
#include "Game.h"
int windowHeight, windowWidth;


int main(int args, char** argv) {
	windowHeight = 800;
	windowWidth = 800;
	Window window = Window("Asteroids", windowWidth, windowHeight);
	Game session = Game(window);
	session.GameLoop();

	return 0;
}