#pragma once
#include <vector>
#include <array>
#include "Global.h"

template<typename T ,int X, int Y>
using array2D = std::array<std::array<T, X>, Y>;

class Transform {
public:
	Transform(double rotation[4], double movementDirection[2], int position[2]);
	Transform(){}
	~Transform();

	Vector2& GetPosition() { return _position; }
	array2D<double, 2,2>& GetRotation() { return _currentRotation; }
	Vector2 GetVelocity() { return _velocity; }
	void Rotate(int degrees);
	void Move();
	void AccelerateForward();
	void Decelerate();
	void SetPosition(int x, int y) { _position.x = x, _position.y = y; }
	void SetAcceleration(double accel) { _acceleration = accel; }
	void SetDeceleration(double decel) { _deceleration = decel; }


private:
	Vector2 _position = {50,50};
	array2D<double, 2, 2> _currentRotation = {0,0,0,0};
	Vector2 _velocity = {0,0};
	double _acceleration = 0.07;
	double _maxMagnitude = 3;
	double _deceleration = 1;
};