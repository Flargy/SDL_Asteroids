#pragma once
#include <vector>
#include <array>
#include "Global.h"
#include "MathExtension.h"

class Transform {
public:
	Transform(double rotation[4], double movementDirection[2], int position[2]);
	Transform(){}
	~Transform();

	Vector2& GetPosition() { return _position; }
	Matrix2D& GetRotation() { return _currentRotation; }
	Vector2 GetVelocity() { return _velocity; }
	void SetVelocity(double x, double y) { _velocity.x = x, _velocity.y = y; }
	void Rotate(int degrees);
	void VelocityFromRotation(Matrix2D newRotation);
	void Move();
	void AccelerateForward();
	void Decelerate();
	void SetPosition(Vector2 newPosition) { _position = newPosition; }
	void SetPosition(int x, int y) { _position.x = x, _position.y = y; }
	void SetAcceleration(double accel) { _acceleration = accel; }
	void SetDeceleration(double decel) { _deceleration = decel; }
	void SetRotation(Matrix2D rotation);


private:
	Vector2 _position = {50,50};
	Matrix2D _currentRotation = {1,0,0,1};
	Vector2 _velocity = {0,0};
	double _acceleration = 0.07;
	double _maxMagnitude = 3;
	double _deceleration = 1;
};