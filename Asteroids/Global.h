#pragma once
#include <array>

extern int windowHeight, windowWidth;

template<typename T, int X, int Y>
using array2D = std::array<std::array<T, X>, Y>;


struct Vector2
{
	double x, y;

	void Rotate(array2D<double, 2, 2> rotation)
	{
		double tempX, tempY;

		tempX = (rotation[0][0] * x + rotation[0][1] * y) * -1;
		tempY = (rotation[1][0] * x + rotation[1][1] * y);

		x = tempX;
		y = tempY;
	}

	Vector2 Normalized()
	{
		double magnitude = sqrt(pow(x, 2) + pow(y, 2));

		return Vector2 { x / magnitude , y / magnitude };
	}

	Vector2 operator-(Vector2 other)
	{
		return Vector2{x - other.x, y - other.y};
	}
	
	Vector2 operator+(Vector2 other)
	{
		return Vector2{ x + other.x, y + other.y };
	}
	
};


