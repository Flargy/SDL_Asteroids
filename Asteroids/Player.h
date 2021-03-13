#pragma once
#include "CollidableObject.h"
#include "HighscoreSystem.h"

class Player : public CollidableObject
{ 
public:
	Player();
	~Player();

	void Reset();

	void CreatePoints();
	void Rotate(int direction);
	void Update();
	void Accelerate();
	void Collide();
	void Init(int xPos, int yPos, int width, int height, HighscoreSystem* highscoreSystem);

private:
	double _width;
	double _height;
	Vector2 startPosition;
	HighscoreSystem* _highscoreSystem;
};