#pragma once

template<typename TStateMachine>
class MenuState : TStateMachine::State
{
public:
	MenuState(TStateMachine& m);	
	
	void Init();
	
	void Prepare();	

	void Execute();
	
	void End();
	
};

