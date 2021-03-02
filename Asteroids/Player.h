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

private:
	//double _xPosition;
	//double _yPosition;
	int _width;
	int _height;
	double** _drawPoints;
	//double _currentRotation[2][2]{ {0,-1},{1,0} };
	//double _movementVector[2]{ 1,0 };
	Transform* transform;
};