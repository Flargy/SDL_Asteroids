#include "SimpleGameStates.h"

SimpleGameStates::SimpleGameStates()
	: playState(*this), menuState(*this)
{
}

void SimpleGameStates::SetGameState(state newState) {
	currentState = newState;
}

void SimpleGameStates::Execute() {

	switch (currentState)
	{
	case eMenuState:
		menuState.Input();
		break;
	case ePlayState:
		playState.Execute();
		break;
	default:
		break;
	}

}

void SimpleGameStates::Draw(Window& window) {

	switch (currentState)
	{
	case eMenuState:
		menuState.Draw(window);
		break;
	case ePlayState:
		playState.Draw(window);
		break;
	default:
		break;
	}

}
