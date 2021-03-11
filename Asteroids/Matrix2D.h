#pragma once
#include "Vector2.h"

struct Matrix2D
{
	Matrix2D(double x1, double y1, double x2, double y2)
	{
		m00 = x1;
		m10 = y1;
		m01 = x2;
		m11 = y2;
	}

	Matrix2D()
	{
		m00 = 0;
		m10 = 0;
		m01 = 0;
		m11 = 0;
	}
	Matrix2D(Vector2 v1, Vector2 v2)
	{
		m00 = v1.x;
		m10 = v1.y;
		m01 = v2.x;
		m11 = v2.y;
	}

	double m00, m10, m01, m11;

	Matrix2D operator*(Matrix2D other);
};

