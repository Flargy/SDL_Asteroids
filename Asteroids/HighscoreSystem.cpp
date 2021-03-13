#include "HighscoreSystem.h"

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
	toFile.close();
}