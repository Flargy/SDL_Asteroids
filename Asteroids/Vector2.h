#pragma once
#include <array>


class Matrix2D;

struct Vector2
{
	double x, y;

	Vector2(double xValue, double yValue)
	{
		x = xValue;
		y = yValue;
	}

	Vector2()
	{
		x = 0;
		y = 0;
	}

	void Rotate(Matrix2D rotation);


	Vector2 Normalized();

	Vector2 operator-(Vector2 other);

	Vector2 operator+(Vector2 other);

	Vector2 operator*(Matrix2D matrix);

	double operator*(Vector2 other);


};

