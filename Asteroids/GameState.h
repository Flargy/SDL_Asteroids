#pragma once


#include "tuple_element_index.h"


#include <typeinfo>

#include <string>

//template<typename TStateMachine>
//class MenuState;
//
//template<typename TStateMachine>
//class PlayState;

#include "PlayState.h"
#include "MenuState.h"

class GameState
{
public:

	

	class State
	{
	public:
		GameState& stateMachine;
		std::string s = "sss";
		
		State(GameState& stateMachine)
			: stateMachine(stateMachine)
		{
			//std::cout << s << std::endl;
		}

		virtual void Prepare() = 0;
		virtual void Execute() = 0;
		virtual void End() = 0;
		virtual void Draw(Window& window) = 0;
	};
private:

	std::tuple<PlayState<GameState>, MenuState<GameState>>
		states_tuple = std::make_tuple(PlayState<GameState>(*this), MenuState<GameState>( *this ) );
	

	State* currentState = nullptr;
	
public:

	template<typename TState>
	TState& getState();
	//{
	//	constexpr int indexOfType = tuple_element_index_v<TState, decltype(states_tuple)>;
	//	return std::get<indexOfType>(states_tuple);
	//}

	template<typename TState>
	void ChangeState();
	//{
	//	if (currentState != nullptr)
	//		currentState->End();
	//	currentState = (State*)(&getState<TState>());
	//	currentState->Prepare();
	//}

	void Execute();
	void Draw(Window& window);

};

#include "GameState.inl"
#include "MenuState.inl"
#include "PlayState.inl"