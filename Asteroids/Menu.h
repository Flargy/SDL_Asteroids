#pragma once
#include "Renderer.h"
#include "HighscoreSystem.h"
#include "SDL.h"
#include <string>

class SimpleGameStates;


class Menu
{
public:

	Menu(SimpleGameStates& statemachine);
	void Draw(Window& window);
	void Input();


private:
	int _scorePosX = 380;
	int _scorePosY = 250;
	int _scoreSpacing = 30;
	int _highscoreTextXPos = 350;
	int _highscoreTextYPos = 230;
	int _playTextXPos = 170;
	int _playTextYPos = 580;
	std::string _highscoreMessage = "Highscores:";
	std::string _playMessage = "Press space to play. R to restart. ESC to return to menu";
	HighscoreSystem _highscoreSystem;
	SimpleGameStates& _statemachine;
};

