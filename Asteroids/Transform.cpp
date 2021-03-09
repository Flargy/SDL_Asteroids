#include "Transform.h"
#include <math.h>
#include <iostream>

#define SIN(x) sin(x * 3.141592653589 / 180) 
#define COS(x) cos(x * 3.141592653589 / 180)

Transform::Transform(double rotation[4], double movementDirection[2], int position[2]) {

	_position.x = position[0];
	_position.y = position[1];
	_velocity.x = movementDirection[0];
	_velocity.y = movementDirection[1];
	// x1 & x2
	_currentRotation[0][0] = rotation[0];
	_currentRotation[0][1] = rotation[1];
	// y1 & y2
	_currentRotation[1][0] = rotation[2];
	_currentRotation[1][1] = rotation[3];
}

Transform::~Transform() {
	
}

void Transform::Rotate(int degrees) {

	double rotationMatrix[2][2];

	// remakes the rotation in degrees into a 2d rotation matrix
	double cosValue = COS(degrees);
	double sinValue = SIN(degrees);

	rotationMatrix[0][0] = cosValue;
	rotationMatrix[1][0] = sinValue;

	rotationMatrix[0][1] = -sinValue;
	rotationMatrix[1][1] = cosValue;

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
}


void Transform::Move() { //ToDo Make the objects loop back around when exiting the view of the window
	
	_position.x += _velocity.x;
	_position.y += _velocity.y;

	if (_position.x < 0) //Basic functionality that is non dynamic,
	{
		_position.x = windowWidth;
	}
	else if (_position.x > windowWidth)
	{
		_position.x = 0;
	}

	if (_position.y < 0) //Basic functionality that is non dynamic,
	{
		_position.y = windowHeight;
	}
	else if (_position.y > windowHeight)
	{
		_position.y = 0;
	}

	if(_deceleration != 1)
		Decelerate();
}

void Transform::AccelerateForward()
{
	Vector2 accelerationDirection;

	accelerationDirection.x = -_currentRotation[0][1]; // no need to multiply X component of matrix as the ship moves in x = 1, y = 0
	accelerationDirection.y = _currentRotation[1][1];


	_velocity.x += accelerationDirection.x * _acceleration;
	_velocity.y += accelerationDirection.y * _acceleration;

	// Clamps the magnitude to _maxMagnitude
	double currentMagnitude = sqrt(pow(_velocity.x, 2) + pow(_velocity.y, 2));
	if (currentMagnitude > _maxMagnitude)
	{
		double reductionValue = fmin(currentMagnitude, _maxMagnitude) / currentMagnitude;
		
		_velocity.x *= reductionValue;
		_velocity.y *= reductionValue;
	}
}

void Transform::Decelerate() {
	_velocity.x *= _deceleration;
	_velocity.y *= _deceleration;
}

void Transform::SetRotation(array2D<double, 2, 2> newRotation)
{
	_currentRotation = newRotation;

	double xDirection = _currentRotation[0][0] * _velocity.x + _currentRotation[0][1] * _velocity.y;
	double yDirection = (_currentRotation[1][0] * _velocity.x + _currentRotation[1][1] * _velocity.y) * -1;

	_velocity.x = xDirection;
	_velocity.y = yDirection;

}

array2D <double, 2, 2> Transform::ConvertRotationToMatrix(double degrees)
{
	array2D<double, 2, 2> rotationMatrix;

	// remakes the rotation in degrees into a 2d rotation matrix
	double cosValue = COS(degrees);
	double sinValue = SIN(degrees);

	rotationMatrix[0][0] = cosValue;
	rotationMatrix[1][0] = sinValue;

	rotationMatrix[0][1] = -sinValue;
	rotationMatrix[1][1] = cosValue;

	return rotationMatrix;
}

