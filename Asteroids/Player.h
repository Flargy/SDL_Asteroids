#pragma once
#include "CollidableObject.h"

class Player : public CollidableObject
{ 
public:
	Player(int xPos, int yPos, int width, int height);
	~Player();

	void CreatePoints();
	void Rotate(int direction);
	void Move();
	void Accelerate();
	void Collide();

private:
	double _width;
	double _height;
};