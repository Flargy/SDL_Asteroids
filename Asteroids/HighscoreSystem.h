#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

class HighscoreSystem
{
public:
	HighscoreSystem();

	void SetScore();

	void IncreaseCurrentScore(int value);

	std::vector<std::string> GetHighscores();

	void Reset();

	int currentScore = 0;
private:
	std::vector<int> scores;
	std::ifstream fromFile;
	std::ofstream toFile;
	std::string path = "res/highscoreList.txt";
};

