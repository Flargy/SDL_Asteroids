#include "Game.h"
#include <SDL.h>
#include "Global.h"

#include "SimpleGameStates.h"

Game::Game(SimpleGameStates& statemachine)
	: _spawnSystem(_asteroids, _projectiles, _alien, _player, _particles),
	statemachine(statemachine)
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
	double accumulator = 0.0;
	steady_clock::time_point currentTime = steady_clock::now();


	while (gameActive)
	{

		steady_clock::time_point newTime = steady_clock::now();
		double frameTime = duration_cast<duration<double>>(newTime - currentTime).count();
		currentTime = newTime;

		accumulator += frameTime;
		//_renderer.SetBackground();

		while (accumulator >= Time::deltaTime)
		{
			
			
			Time::time += Time::deltaTime;
			accumulator -= Time::deltaTime;
		}
		
	}
}

void Game::Execute() {
	Input();
	Update();
}

void Game::Update() {
	//---------------------- update ------------------------------- 
	
	_player.Update();
	
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
		_alien.Update();
	}
	for (size_t i = 0; i < _particles.active_size(); i++)
	{
		_particles[i].Update();
	}
	_spawnSystem.AlienTimeCounter();
	
	_collisionHandler.FindAllCollisions(_asteroids, _projectiles, _player, _alien, 20);
}

void Game::Input()
{
	SDL_Event event;
	
	SDL_PumpEvents();
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (_player.alive)
	{
		if (state[SDL_SCANCODE_LEFT])
		{
			_player.Rotate(deltaRotation);
		}
		if (state[SDL_SCANCODE_RIGHT])
		{
			_player.Rotate(-deltaRotation);
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
			statemachine.gameActive = false;
			break;
		default:
			break;
		}
	}
}

void Game::Draw(Window& window) {
	// ---------------------- draw call ------------------------------- 
	for (size_t i = 0; i < _asteroids.active_size(); i++)
	{
		window.DrawObject(_asteroids[i]);
	}
	for (size_t i = 0; i < _projectiles.active_size(); i++)
	{
		window.DrawObject(_projectiles[i]);
	}
	for (size_t i = 0; i < _particles.active_size(); i++)
	{
		_particles[i].Draw(window._renderer);
	}
	if(_player.alive)
		window.DrawObject(_player);
	if(_alien.alive)
		window.DrawObject(_alien);
	window.PresentRenderer();
}

