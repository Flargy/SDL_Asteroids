#pragma once

#include <cassert>


void GameState::Execute()
{
	assert(currentState != nullptr);
	currentState->Execute();
}

void GameState::Draw(Window& window)
{
	assert(currentState != nullptr);
	currentState->Draw(window);
}

template<typename TState>
TState& GameState::getState() {
	constexpr int indexOfType = tuple_element_index_v<TState, decltype(states_tuple)>;
	return std::get<indexOfType>(states_tuple);
};

template<typename TState>
void GameState::ChangeState()
{
	if (currentState != nullptr)
		currentState->End();
	currentState = (State*)(&getState<TState>());
	currentState->Prepare();
};