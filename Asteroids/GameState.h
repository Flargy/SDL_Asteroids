#pragma once


#include "tuple_element_index.h"
#include "for_each_in_tuple.h"

#include "PlayState.h"
#include "MenuState.h"

#include <typeinfo>

class GameState
{

public:

	class State
	{
	public:
		GameState& stateMachine;
		
		State(GameState& stateMachine)
			: stateMachine(stateMachine)
		{
		}

		virtual void Prepare() = 0;
		virtual void Execute() = 0;
		virtual void End() = 0;
	};
private:

	std::tuple<PlayState<GameState>, MenuState<GameState>> states_tuple =
	{ {*this}, {*this} };

	
	
public:

	template<typename TState>
	TState& getState() {
		constexpr int indexOfType = tuple_element_index_v<TState, decltype(states_tuple)>;
		return std::get<indexOfType>(states_tuple);
	}

	

};

