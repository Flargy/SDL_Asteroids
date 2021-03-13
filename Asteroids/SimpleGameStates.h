#pragma once


#include "Game.h"
#include "GameStateEnum.h"



class SimpleGameStates
{
	Game playState;
	Game menuState; //change this type
public:

	bool gameActive = true;

	SimpleGameStates();

	state currentState;

	void SetGameState(state newState);

	void Execute();

	void Draw(Window& window);

};

