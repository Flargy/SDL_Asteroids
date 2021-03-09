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
	_spawnSystem(_asteroids, _projectiles, _alien, _player),
	_collisionHandler(_renderer)
{
	Asteroid* debugAsteroid = new Asteroid(50);
	debugAsteroid->transform.SetPosition(100, 100); // change their positions here
		
	
	_asteroids.push_back(*debugAsteroid);
	//_asteroids = { *debugAsteroid };

	_player = Player(400, 400, 10, 10);
	
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
			_player.Move();

			for (size_t i = 0; i < _projectiles.active_size(); i++)
			{
				_projectiles[i].Update();
			}

			PlayerInput();
			t += dt;
			accumulator -= dt;

			_collisionHandler.FindAllCollisions(_asteroids, _projectiles, _player, 20);
		}
		// draw call here

		//_renderer.DrawPlayer();
		for (size_t i = 0; i < _asteroids.active_size(); i++)
		{
			_renderer.DrawObject(_asteroids[i]);
		}
		for (size_t i = 0; i < _projectiles.active_size(); i++)
		{
			_renderer.DrawObject(_projectiles[i]);
		}
		_renderer.DrawObject(_player);
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
		_player.Rotate(3);
	}
	if (state[SDL_SCANCODE_RIGHT])
	{
		_player.Rotate(-3);
	}
	if (state[SDL_SCANCODE_UP])
	{
		_player.Accelerate();
	}
	if (state[SDL_SCANCODE_SPACE])
	{
		std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
		double timeSinceShot = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - _lastShot).count();
		if (timeSinceShot > _shotDelay)
		{
			// shoot projectile
			_spawnSystem.SpawnProjectile().Instantiate(_player.transform.GetPosition(), _player.transform.GetRotation(), _projectiles.active_size() - 1);
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