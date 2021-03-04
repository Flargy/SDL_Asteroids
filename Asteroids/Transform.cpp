#include "Transform.h"
#include <math.h>
#include <iostream>

#define SIN(x) sin(x * 3.141592653589 / 180) 
#define COS(x) cos(x * 3.141592653589 / 180)

Transform::Transform(double rotation[4], double movementDirection[2], int position[2]) {

	_position[0] = position[0];
	_position[1] = position[1];
	_velocity[0] = movementDirection[0];
	_velocity[1] = movementDirection[1];
	_currentRotation[0][0] = rotation[0];
	_currentRotation[0][1] = rotation[1];
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
	for (int i = 0; i < 2; i++)
	{
		_position[i] += _velocity[i];
	}

	if(_deceleration != 1)
		Decelerate();
}

void Transform::AccelerateForward()
{
	double accelerationDirection[2];

	accelerationDirection[0] = _currentRotation[0][0] * 1 + _currentRotation[0][1] * 0;
	accelerationDirection[1] = (_currentRotation[1][0] * 1 + _currentRotation[1][1] * 0) * -1;

	for (int i = 0; i < 2; i++)
	{
		_velocity[i] += accelerationDirection[i] * _acceleration;
	}

	// Clamps the magnitude to _maxMagnitude
	double currentMagnitude = sqrt(pow(_velocity[0], 2) + pow(_velocity[1], 2));
	if (currentMagnitude > _maxMagnitude)
	{
		double reductionValue = fmin(currentMagnitude, _maxMagnitude) / currentMagnitude;
		for (int i = 0; i < 2; i++)
		{
			_velocity[i] *= reductionValue;
		}
	}
}

void Transform::Decelerate() {
	for (int i = 0; i < 2; i++)
	{
		_velocity[i] *=  _deceleration;
	}
}

