#pragma once
#include "CollidableObject.h"

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
	void Init(int xPos, int yPos, int width, int height);

private:
	double _width;
	double _height;
	Vector2 startPosition;
};