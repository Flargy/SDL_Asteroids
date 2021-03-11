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

	Matrix2D rotationMatrix;

	// remakes the rotation in degrees into a 2d rotation matrix
	double cosValue = COS(degrees);
	double sinValue = SIN(degrees);

	rotationMatrix.m00 = cosValue;
	rotationMatrix.m10 = sinValue;

	rotationMatrix.m01 = -sinValue;
	rotationMatrix.m11 = cosValue;

	// creates a new matrix which is the (players current rotation * rotation matrix from degrees)
	Matrix2D product;

	product = (_matrixRotation * rotationMatrix);

	// overwrites the current rotation with the previously created rotation matrix
	//std::cout << product.vec1.x << " " << product.vec1.y << " " << product.vec2.x << " " << product.vec2.y << " " << std::endl;
	_matrixRotation = product;


	_currentRotation[0][0] = _matrixRotation.m00;
	_currentRotation[1][0] = _matrixRotation.m10;
	_currentRotation[0][1] = _matrixRotation.m01;
	_currentRotation[1][1] = _matrixRotation.m11;
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

void Transform::VelocityFromRotation(array2D<double, 2, 2> newRotation)
{
	_currentRotation = newRotation;

	double xDirection = (_currentRotation[0][0] * _velocity.x + _currentRotation[0][1] * _velocity.y) * -1;
	double yDirection = _currentRotation[1][0] * _velocity.x + _currentRotation[1][1] * _velocity.y;

	_velocity.x = xDirection;
	_velocity.y = yDirection;

}



void Transform::SetRotation(array2D<double, 2, 2> rotation)
{
	_currentRotation = rotation;
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

