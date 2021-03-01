#include "Player.h"
#include <math.h>
#include <iostream>

// creates a new function for calling sin and cos with degrees instead of radians
#define SIN(x) sin(x * 3.141592653589 / 180) 
#define COS(x) cos(x * 3.141592653589 / 180)

/*
* Sets starting values
*/
Player::Player(int xPos, int yPos, int width, int height) :
	_xPosition(xPos), _yPosition(yPos), _width(width), _height(height) {
	CreatePoints();

}
/*
* Destructor for the player, clears out the 2d array
*/
Player::~Player() {
	for (int i = 0; i < 2; i++)
	{
		delete _drawPoints[i];
	}

	delete[] _drawPoints;
}

/*
* Sets up the relative points for drawing the player ship
*/
void Player::CreatePoints() {
	_drawPoints = new double* [2];

	for (int i = 0; i < 2; i++)
	{
		_drawPoints[i] = new double[3];
	}

	_drawPoints[0][0] = -_width;
	_drawPoints[0][1] = 0;
	_drawPoints[0][2] = _width;

	_drawPoints[1][0] = _height;
	_drawPoints[1][1] = -_height;
	_drawPoints[1][2] = _height;
}

double** Player::GetPoints() {
	return _drawPoints;
}

/*
* Returns the X position of the player
*/
double Player::GetXPosition() {
	return _xPosition;
}

/*
* Returns the Y position of the player
*/
double Player::GetYPosition() {
	return _yPosition;
}

/*
* Rotates the player by "degrees"
*/
void Player::Rotate(int degrees) {

	double rotationMatrix[2][2];

	// remakes the rotation in degrees into a 2d rotation matrix
	double cosValue = COS(degrees);
	double sinValue = SIN(degrees);

	rotationMatrix[0][0] = cosValue;
	rotationMatrix[1][0] = sinValue;

	rotationMatrix[0][1] = -sinValue;
	rotationMatrix[1][1] = cosValue;


	/*double multiplication[2][2];

	multiplication[0][0] = rotationMatrix[0][0] * _currentRotation[0][0] + rotationMatrix[0][1] * _currentRotation[1][0];
	multiplication[1][0] = rotationMatrix[1][0] * _currentRotation[0][0] + rotationMatrix[1][1] * _currentRotation[1][0];

	multiplication[0][1] = rotationMatrix[0][0] * _currentRotation[0][1] + rotationMatrix[0][1] * _currentRotation[1][1];
	multiplication[1][1] = rotationMatrix[1][0] * _currentRotation[0][1] + rotationMatrix[1][1] * _currentRotation[1][1];

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			_currentRotation[i][j] = multiplication[i][j];
		}

	}*/

	// creates a new matrix which is the (players current rotation * rotation matrix from degrees)
	double product[2][2];

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			product[i][j] = 0;

			for (int k = 0; k < 2; k++)
				product[i][j] = product[i][j] + (_currentRotation[i][k] * rotationMatrix[k][j]);
		}
	}

	// overwrites the current rotation with the previously created rotation matrix
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			_currentRotation[i][j] = product[i][j];
		}
	}


	// applies the rotation to the draw points for redenering
	for (int i = 0; i < 3; i++)
	{
		double x = _drawPoints[0][i];
		double y = _drawPoints[1][i];

		_drawPoints[0][i] = rotationMatrix[0][0] * x + rotationMatrix[1][0] * y;
		_drawPoints[1][i] = rotationMatrix[0][1] * x + rotationMatrix[1][1] * y;
	}

}

/*
* moves the player "forwards" * rotation
*/
void Player::Move() {
	double x = _movementVector[0];
	double y = _movementVector[1];

	_xPosition += _currentRotation[0][0] * x + _currentRotation[1][0] * y;
	_yPosition += _currentRotation[0][1] * x + _currentRotation[1][1] * y;
}