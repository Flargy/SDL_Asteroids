#pragma once
#include "Transform.h"

class Player {
public:
	Player(int xPos, int yPos, int width, int height);
	~Player();

	double** GetPoints();
	void CreatePoints();
	double GetXPosition();
	double GetYPosition();
	void Rotate(int direction);
	void Move();
	void Accelerate();
	void Drag();

private:
	int _width;
	int _height;
	double** _drawPoints;
	Transform* _transform;
};