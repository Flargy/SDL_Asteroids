#pragma once


template<typename TStateMachine>
class PlayState : TStateMachine::State
{
	

public:
	PlayState(TStateMachine& m);
	
	void Init();

	void Prepare();

	void Execute();

	void End();

private:
		int lol = 0;

};

