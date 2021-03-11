#include "Matrix2D.h"
#include "Vector2.h"


Matrix2D Matrix2D::operator*(Matrix2D other)
{
	double new00, new10, new01, new11;

	new00 = other.m00 * m00 + other.m01 * m10;

	new10 = other.m10 * m00 + other.m11 * m10;

	new01 = other.m00 * m01 + other.m01 * m11;

	new11 = other.m10 * m01 + other.m11 * m11;

	return Matrix2D(new00, new10, new01, new11 );
}

Matrix2D::Matrix2D(Vector2 v1, Vector2 v2)
{
	m00 = v1.x;
	m10 = v1.y;
	m01 = v2.x;
	m11 = v2.y;
}