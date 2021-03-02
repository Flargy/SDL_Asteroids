#include "Transform.h"
#include <math.h>

#define SIN(x) sin(x * 3.141592653589 / 180) 
#define COS(x) cos(x * 3.141592653589 / 180)

Transform::Transform(double rotation[4], double movementDirection[2], int position[2], double velocity) {

	_velocity = velocity;
	_position[0] = position[0];
	_position[1] = position[1];
	_movementVector[0] = movementDirection[0];
	_movementVector[1] = movementDirection[1];
	_currentRotation = new double* [2]; 
	for (int i = 0; i < 2; i++)
	{
		_currentRotation[i] = new double[2];
	}
	_currentRotation[0][0] = rotation[0];
	_currentRotation[0][1] = rotation[1];
	_currentRotation[1][0] = rotation[2];
	_currentRotation[1][1] = rotation[3];
}

Transform::~Transform() {
	for (int i = 0; i < 2; i++)
	{
		delete _currentRotation[i];
	}

	delete[] _currentRotation;
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

void Transform::ChangeVelocity(double speed) {
	_velocity = fmin(0, _velocity + speed);
}

void Transform::AddToPosition(double AddToPosition[2]) {
	_position[0] += AddToPosition[0];
	_position[1] += AddToPosition[1];
}