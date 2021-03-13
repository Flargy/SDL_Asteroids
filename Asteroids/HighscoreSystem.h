#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

class HighscoreSystem
{
public:
	HighscoreSystem()
	{
		scores.reserve(6);
	}
	~HighscoreSystem(){}

	void SetScore(int latestScore);

private:
	std::vector<int> scores;
	std::ifstream fromFile;
	std::ofstream toFile;
	std::string path = "res/highscoreList";
};

