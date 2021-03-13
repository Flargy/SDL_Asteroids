#include "Menu.h"
#include "SimpleGameStates.h"


Menu::Menu(SimpleGameStates& statemachine) : _statemachine(statemachine)
{

}

void Menu::Draw(Window& window)
{
	std::vector<std::string> highscoreList = _highscoreSystem.GetHighscores();

	window.DrawText(_highscoreMessage, _highscoreTextXPos, _highscoreTextYPos);
	window.DrawText(_playMessage, _playTextXPos, _playTextYPos);


	for (int i = 0; i < highscoreList.size(); i++)
	{
		window.DrawText(highscoreList[i], _scorePosX, _scorePosY + _scoreSpacing * (i + 1));
	}

}

void Menu::Input()
{
	SDL_Event event;

	SDL_PumpEvents();
	const Uint8* state = SDL_GetKeyboardState(NULL);
	
	if (state[SDL_SCANCODE_SPACE])
	{
		_statemachine.SetGameState(ePlayState);
	}

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			_statemachine.gameActive = false;
			break;
		default:
			break;
		}
	}
}