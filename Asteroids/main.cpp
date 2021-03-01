#include <memory>
#include <map>
#include <chrono>
#include "Renderer.h"



int main(int args, char** argv) {
	Player* player = new Player(400, 400, 6, 10);
	Window window("Conway's game of life", 800, 800);
	window.Setplayer(player);
	using namespace std::chrono;
	bool quit = false;
	bool play = false;
	double t = 0.0;
	double dt = 1.0 / 60.0;
	double accumulator = 0.0;
	steady_clock::time_point currentTime = steady_clock::now();


	while (!window.IsClosed()) {

		steady_clock::time_point newTime = steady_clock::now();
		double frameTime = duration_cast<duration<double>>(newTime - currentTime).count();
		currentTime = newTime;

		accumulator += frameTime;
		window.SetBackground();

		while (accumulator >= dt) { // TODO: make player move and rotate
			//Do physics here

			if (window.PollEvents()) {
				play = !play;
			}
			t += dt;
			accumulator -= dt;

		}
		// draw call here

		window.DrawPlayer();

		window.PresentRenderer();
	}

	return 0;
}