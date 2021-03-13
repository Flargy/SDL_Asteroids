#pragma once

#include <cassert>


void GameState::Execute()
{
	assert(currentState != nullptr,
		"statemachine was not set to a state before executing");
	currentState->Execute();
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