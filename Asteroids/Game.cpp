#include "Game.h"
#include <SDL.h>
#include "Global.h"


Game::Game(Window& window)
	: _renderer(window), 
	_spawnSystem(_asteroids, _projectiles, _alien, _player),
	_collisionHandler(_renderer)
{
	_spawnSystem.SpawnAsteroids();

	_player.Init(400, 400, 10, 10);
	_alien.ReceivePlayer(&_player);
}

void Game::GameLoop()
{
	
	using namespace std::chrono;
	bool quit = false;
	bool play = false;
	double t = 0.0;
	double dt = 1.0 / 60.0;
	double accumulator = 0.0;
	steady_clock::time_point startTime = steady_clock::now();
	steady_clock::time_point currentTime = startTime;


	while (!_renderer.IsClosed())
	{

		steady_clock::time_point newTime = steady_clock::now();
		double frameTime = duration_cast<duration<double>>(newTime - currentTime).count();
		currentTime = newTime;

		accumulator += frameTime;
		_renderer.SetBackground();

		while (accumulator >= dt)
		{
			double time = duration_cast<duration<double>>(currentTime - startTime).count();
			//Do physics here
			_player.Move();

			for (size_t i = 0; i < _projectiles.active_size(); i++)
			{
				_projectiles[i].Update();
			}
			for (size_t i = 0; i < _asteroids.active_size(); i++)
			{
				_asteroids[i].Update();
			}
			if (_alien.alive == true)
			{
				_alien.Update(time);
			}
			_spawnSystem.AlienTimeCounter(time);

			PlayerInput();
			_collisionHandler.FindAllCollisions(_asteroids, _projectiles, _player, _alien, 20);
			
			t += dt;
			accumulator -= dt;

		}
		// draw call here

		for (size_t i = 0; i < _asteroids.active_size(); i++)
		{
			_renderer.DrawObject(_asteroids[i]);
		}
		for (size_t i = 0; i < _projectiles.active_size(); i++)
		{
			_renderer.DrawObject(_projectiles[i]);
		}
		if(_player.alive)
			_renderer.DrawObject(_player);

		if(_alien.alive)
			_renderer.DrawObject(_alien);
		_renderer.PresentRenderer();
	}
}

void Game::PlayerInput()
{
	SDL_Event event;

	//std::vector<int> positions;

	SDL_PumpEvents();
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (_player.alive)
	{
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
				_spawnSystem.SpawnProjectile(_player.transform.GetPosition(), _player.transform.GetRotation());
				_lastShot = currentTime;
			}
		}
	}
	if (state[SDL_SCANCODE_R])
	{
		_spawnSystem.Reset();
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