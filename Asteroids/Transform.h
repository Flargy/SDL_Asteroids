#pragma once

class Transform {
public:
	Transform(double rotation[4], double movementDirection[2], int position[2], double velocity);
	~Transform();

	double* GetPosition() { return _position; }
	double** GetRotation() { return _currentRotation; }
	double* GetMovementVector() { return _movementVector; }
	double GetVelocity() { return _velocity; }
	void Rotate(int degrees);
	void ChangeVelocity(double speed);
	void AddToPosition(double addition[2]);


private:
	double _position[2]{0,0};
	double** _currentRotation;
	double _movementVector[2]{1,0};
	double _velocity = 1;
};