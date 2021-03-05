#include <memory>
#include <map>
#include <chrono>
#include <vector>
#include "Renderer.h"
#include "Transform.h"
#include "CollisionHandler.h"
#include "Global.h"

int windowHeight, windowWidth;

int main(int args, char** argv) {
	windowHeight = 800;
	windowWidth = 800;

	Player* player = new Player(400, 400, 6, 10);
	Window window("Asteroids", windowWidth, windowHeight);

	Asteroid* debugAsteroid = new Asteroid(50);
	debugAsteroid->transform->SetPosition(100, 100); // change their positions here

	window.SetDebugAsteroid(debugAsteroid);
	window.Setplayer(player);
	CollisionHandler collisionHandler(window);

	
	int PlayerBounds[4] = { -10, 10, -6, 6 };
	player->SetBoundingBox(PlayerBounds);
	

	using namespace std::chrono;
	bool quit = false;
	bool play = false;
	double t = 0.0;
	double dt = 1.0 / 60.0;
	double accumulator = 0.0;
	steady_clock::time_point currentTime = steady_clock::now();

	std::vector<CollidableObject> debugAsteroids = {*debugAsteroid};
	std::vector<CollidableObject> debugplayer = { *player };
	std::vector<CollidableObject> alien = { };
	std::vector<CollidableObject> bullets = { };


	while (!window.IsClosed()) {

		steady_clock::time_point newTime = steady_clock::now();
		double frameTime = duration_cast<duration<double>>(newTime - currentTime).count();
		currentTime = newTime;

		accumulator += frameTime;
		window.SetBackground();

		while (accumulator >= dt) {
			//Do physics here
			player->Move();

			if (window.PollEvents()) {
				play = !play;
			}
			t += dt;
			accumulator -= dt;

		}
		// draw call here
		collisionHandler.FindAllCollisions(debugAsteroids, bullets, *player, 20);

		window.DrawPlayer();
		window.RenderDebugCube();
		window.PresentRenderer();
	}

	return 0;
}