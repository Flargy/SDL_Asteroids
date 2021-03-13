#pragma once

#include <iostream>

template<typename TStateMachine>
PlayState<TStateMachine>::PlayState(TStateMachine& m)
	: TStateMachine::State(m)
{
};

template<typename TStateMachine>
void PlayState<TStateMachine>::Init() {
	std::cout << typeid(PlayState).name() << std::endl;
};

template<typename TStateMachine>
void PlayState<TStateMachine>::Prepare() {
	std::cout << "PREPARE " << typeid(PlayState).name() << std::endl;
};

template<typename TStateMachine>
void PlayState<TStateMachine>::Execute() {
	std::cout << "EXECUTE " << typeid(PlayState).name() << std::endl;
};

template<typename TStateMachine>
void PlayState<TStateMachine>::End() {
	std::cout << "END " << typeid(PlayState).name() << std::endl;
};