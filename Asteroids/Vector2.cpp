#include "Vector2.h"
#include "Matrix2D.h"

void Vector2::Rotate(Matrix2D rotation)
{
	double tempX, tempY;

	tempX = (rotation.m00 * x + rotation.m01 * y) * -1;
	tempY = (rotation.m10 * x + rotation.m11 * y);

	x = tempX;
	y = tempY;
}


Vector2 Vector2::Normalized()
{
	double magnitude = sqrt(pow(x, 2) + pow(y, 2));

	return Vector2( x / magnitude , y / magnitude );
}

Vector2 Vector2::operator-(Vector2 other)
{
	return Vector2( x - other.x, y - other.y );
}

Vector2 Vector2::operator+(Vector2 other)
{
	return Vector2( x + other.x, y + other.y );
}

Vector2 Vector2::operator*(Matrix2D matrix) // vector and matrix multiplication
{
	return Vector2( matrix.m00 * x +  matrix.m01 * y,  matrix.m10 * x  + matrix.m11 * y);
}

double Vector2::operator*(Vector2 other)
{
	return (x * other.x + y * other.y);
}

Vector2 Vector2::operator*(double d)
{
	return Vector2(x * d, y * d);
}

