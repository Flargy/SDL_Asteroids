#pragma once

#include <iostream>

template<typename TStateMachine>
MenuState<TStateMachine>::MenuState(TStateMachine& m)
	: TStateMachine::State(m)
{
	//std::cout << TStateMachine::State::s << std::endl;
};

template<typename TStateMachine>
void MenuState<TStateMachine>::Init() {
	std::cout << typeid(MenuState).name() << std::endl;
};

template<typename TStateMachine>
void MenuState<TStateMachine>::Prepare()
{
	std::cout << "PREPARE " << typeid(MenuState).name() << std::endl;
};

template<typename TStateMachine>
void MenuState<TStateMachine>::Execute()
{
	using type = PlayState<TStateMachine>;
	std::cout << "EXECUTE " << typeid(MenuState).name() << std::endl;
	std::cout << TStateMachine::State::s.size() << std::endl;

	TStateMachine::State::stateMachine
		.ChangeState<PlayState<GameState>>();

	std::cout << typeid(TStateMachine::State::stateMachine).name() << std::endl;
};

template<typename TStateMachine>
void MenuState<TStateMachine>::End()
{
	std::cout << "END " << typeid(MenuState).name() << std::endl;
};