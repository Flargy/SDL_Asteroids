#pragma once

#include <array>

template<typename T ,int X, int Y>
using array2D = std::array<std::array<T, X>, Y>;

class Transform {
public:
	Transform(double rotation[4], double movementDirection[2], int position[2]);
	~Transform();

	std::array<double, 2>& GetPosition() { return _position; }
	array2D<double, 2,2>& GetRotation() { return _currentRotation; }
	std::array<double, 2> GetVelocity() { return _velocity; }
	//double GetVelocity() { return _velocity; }
	void Rotate(int degrees);
	void AddToPosition();
	void AccelerateForward();


private:
	std::array<double, 2> _position;
	array2D<double,2,2> _currentRotation;
	std::array<double, 2> _velocity;
	double _acceleration = 0.05;
	double _maxMagnitude = 3;
};