#pragma once

#include <array>

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
	//double GetVelocity() { return _velocity; }
	void Rotate(int degrees);
	void AddToPosition();
	void AccelerateForward();
	void Decelerate();


private:
	std::array<double, 2> _position = {0,0};
	array2D<double, 2, 2> _currentRotation = {0,0,0,0};
	std::array<double, 2> _velocity = {0,0};
	double _acceleration = 0.07;
	double _maxMagnitude = 3;
	double _deceleration = 0.98;
};