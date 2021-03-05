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

	std::array<double, 2>& GetPosition() { return _position; }
	array2D<double, 2,2>& GetRotation() { return _currentRotation; }
	std::array<double, 2> GetVelocity() { return _velocity; }
	void Rotate(int degrees);
	void Move();
	void AccelerateForward();
	void Decelerate();
	void SetPosition(int x, int y) { _position[0] = x, _position[1] = y; }
	void SetAcceleration(double accel) { _acceleration = accel; }
	void SetDeceleration(double decel) { _deceleration = decel; }


private:
	std::array<double, 2> _position = {50,50};
	array2D<double, 2, 2> _currentRotation = {0,0,0,0};
	std::array<double, 2> _velocity = {0,0};
	double _acceleration = 0.07;
	double _maxMagnitude = 3;
	double _deceleration = 1;
};