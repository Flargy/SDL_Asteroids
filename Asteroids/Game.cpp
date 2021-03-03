#include "Game.h"
#include <SDL.h>

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

void Game::PlayerInput()
{
	SDL_Event event;

	//std::vector<int> positions;

	SDL_PumpEvents();
	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_LEFT])
	{
		_player->Rotate(3);
	}
	if (state[SDL_SCANCODE_RIGHT])
	{
		_player->Rotate(-3);
	}
	if (state[SDL_SCANCODE_UP])
	{
		_player->Accelerate();
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