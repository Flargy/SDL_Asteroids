#pragma once

#include <iostream>


template<typename TStateMachine>
class MenuState : TStateMachine::State
{
	

public:
	MenuState(TStateMachine& m)
		: TStateMachine::State(m)
	{
		Init();
	}
	
	void Init() {
		std::cout << typeid(MenuState).name() << std::endl;
	}

	void Prepare() {};
	void Execute() {};
	void End() {};

};

