#include "Transform.h"
#include <math.h>
#include <iostream>



Transform::Transform(double rotation[4], double movementDirection[2], int position[2]) {

	_position.x = position[0];
	_position.y = position[1];
	_velocity.x = movementDirection[0];
	_velocity.y = movementDirection[1];
	// x1 & x2
	_currentRotation.m00 = rotation[0];
	_currentRotation.m01 = rotation[1];
	// y1 & y2
	_currentRotation.m10 = rotation[2];
	_currentRotation.m11 = rotation[3];
}

Transform::~Transform() {
	
}

void Transform::Rotate(int degrees) {

	double deltaRotation = degrees;
	// remakes the rotation in degrees into a 2d rotation matrix
	double cosValue = COS(deltaRotation);
	double sinValue = SIN(deltaRotation);

	Matrix2D rotationMatrix(cosValue, sinValue, -sinValue, cosValue);

	// creates a new matrix which is the (players current rotation * rotation matrix from degrees)
	Matrix2D product;

	product = (_currentRotation * rotationMatrix);


	_currentRotation = product;
}


void Transform::Move() { 
	
	_position.x += _velocity.x * Time::deltaTime;
	_position.y += _velocity.y * Time::deltaTime;

	if (_position.x < 0) 
	{
		_position.x = windowWidth;
	}
	else if (_position.x > windowWidth)
	{
		_position.x = 0;
	}

	if (_position.y < 0) 
	{
		_position.y = windowHeight;
	}
	else if (_position.y > windowHeight)
	{
		_position.y = 0;
	}

	if(_deceleration != _originalDrag)
		Decelerate();
}

void Transform::AccelerateForward()
{
	Vector2 accelerationDirection;

	accelerationDirection.x = -_currentRotation.m01; // no need to multiply X component of matrix as the ship moves in x = 1, y = 0
	accelerationDirection.y = _currentRotation.m11;


	_velocity.x += accelerationDirection.x * _acceleration * Time::deltaTime;
	_velocity.y += accelerationDirection.y * _acceleration * Time::deltaTime;

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
	_velocity.x *= 1 - _deceleration * Time::deltaTime;
	_velocity.y *= 1 - _deceleration * Time::deltaTime;
}

void Transform::VelocityFromRotation(Matrix2D newRotation)
{
	_currentRotation = newRotation;
	_velocity = _velocity * _currentRotation;
	_velocity.x *= -1;

}



void Transform::SetRotation(Matrix2D rotation)
{
	_currentRotation = rotation;
}


