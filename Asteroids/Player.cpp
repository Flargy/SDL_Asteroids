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
	_width(width), _height(height) {
	CreatePoints();

	double rotation[4]{ 0,-1,1,0 };
	double movement[2]{ 1,0 };
	int position[2]{ xPos, yPos };
	

	transform = new Transform(rotation, movement, position, 1);
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
	return transform->GetPosition()[0];
}

/*
* Returns the Y position of the player
*/
double Player::GetYPosition() {
	return transform->GetPosition()[1];
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

	transform->Rotate(degrees);

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
	double x = transform->GetMovementVector()[0];
	double y = transform->GetMovementVector()[1];

	double addX = transform->GetRotation()[0][0] * x + transform->GetRotation()[1][0] * y;
	double addY = transform->GetRotation()[0][1] * x + transform->GetRotation()[1][1] * y;

	double newPos[2]{ addX,addY };
	transform->AddToPosition(newPos);
}