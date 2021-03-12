#pragma once

#include <iostream>

template<typename TStateMachine>
class PlayState : TStateMachine::State
{
	

public:
	PlayState(TStateMachine& m)
		: TStateMachine::State(m)
	{
		Init();
	}
	
	void Init() {
		std::cout << typeid(PlayState).name() << std::endl;
	}

	void Prepare() {};
	void Execute() {};
	void End() {};

};

