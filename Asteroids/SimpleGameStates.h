#pragma once
#include "Game.h"
#include "GameStateEnum.h"
#include "Menu.h"



class SimpleGameStates
{
	Game playState;
	Menu menuState; 
public:

	bool gameActive = true;

	SimpleGameStates();

	state currentState;

	void SetGameState(state newState);

	void Execute();

	void Draw(Window& window);

};

