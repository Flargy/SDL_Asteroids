#include "Game.h"
#include <SDL.h>
#include "Global.h"

void Game::Update() 
{
    // input
    // player set acceleration
    // player generate bullet spawn event OR immediate spawn?


    //create objects
        //(spawn bullet)
        //spawn alien
        //(spawn split asteroids)
        //spawn new asteroid swarm

    //update velocity
        //player
        //alien

    //move all objects

    //collisions:
    // player checks against asteroids in tree
	// player checks against bullets 
	// player checks against aliens
    // ->destroy player   


	// bullets check against asteroids
    // -> generate spawn event? OR immediate spawn
    // -> generate destroy event? OR immediate destroy

    //destroy objects
    // -> consume destroy events

}

Game::Game(Window& window)
	: _renderer(window), 
	_spawnSystem(_asteroids, _projectiles, _aliens, _player),
	_collisionHandler(_renderer)
{
	Asteroid* debugAsteroid = new Asteroid(50);
	debugAsteroid->transform.SetPosition(100, 100); // change their positions here
		
	_asteroids.reserve(32);
	_projectiles.reserve(16);

	_asteroids = { *debugAsteroid };

	_player.push_back(Player(400, 400, 6, 10));
	
}

void Game::GameLoop()
{
	
	using namespace std::chrono;
	bool quit = false;
	bool play = false;
	double t = 0.0;
	double dt = 1.0 / 60.0;
	double accumulator = 0.0;
	steady_clock::time_point currentTime = steady_clock::now();

	while (!_renderer.IsClosed())
	{

		steady_clock::time_point newTime = steady_clock::now();
		double frameTime = duration_cast<duration<double>>(newTime - currentTime).count();
		currentTime = newTime;

		accumulator += frameTime;
		_renderer.SetBackground();

		while (accumulator >= dt)
		{
			//Do physics here
			_player[0].Move();

			PlayerInput();
			t += dt;
			accumulator -= dt;

		}
		// draw call here
		_collisionHandler.FindAllCollisions(_asteroids, _projectiles, _player[0], 20);

		//_renderer.DrawPlayer();
		_renderer.DrawObject(_asteroids[0]);
		_renderer.DrawObject(_player[0]);
		_renderer.PresentRenderer();
	}
}

void Game::PlayerInput()
{
	SDL_Event event;

	//std::vector<int> positions;

	SDL_PumpEvents();
	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_LEFT])
	{
		_player[0].Rotate(3);
	}
	if (state[SDL_SCANCODE_RIGHT])
	{
		_player[0].Rotate(-3);
	}
	if (state[SDL_SCANCODE_UP])
	{
		_player[0].Accelerate();
	}
	if (state[SDL_SCANCODE_SPACE])
	{
		std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
		double timeSinceShot = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - _lastShot).count();
		if (timeSinceShot > _shotDelay)
		{
			// shoot projectile
			_lastShot = currentTime;
		}
	}


	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			//_closed = true;
			break;
		default:
			break;
		}
	}
}