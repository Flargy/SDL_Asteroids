#include "HighscoreSystem.h"

HighscoreSystem::HighscoreSystem()
{
	scores.reserve(6);
}


void HighscoreSystem::SetScore()
{
	fromFile.open(path);
	int temp = 0;

	while (fromFile >> temp)
	{
		scores.push_back(temp);
	}
	scores.push_back(currentScore);

	std::sort(scores.begin(), scores.end(), std::greater<int>());
	fromFile.close();

	toFile.open(path);

	int lowest = fmin(scores.size(), 5);

	for (int i = 0; i < lowest; i++)
	{
		toFile << scores[i] << "\n";
	}
	scores.clear();
	toFile.close();
}

void HighscoreSystem::IncreaseCurrentScore(int value)
{
	currentScore += value;
}

std::vector<std::string> HighscoreSystem::GetHighscores()
{
	std::vector<std::string> highscoreList;

	fromFile.open(path);
	std::string temp;

	while (fromFile >> temp)
	{
		highscoreList.push_back(temp);
	}

	fromFile.close();
	return highscoreList;
}

void HighscoreSystem::Reset()
{
	currentScore = 0;
}
