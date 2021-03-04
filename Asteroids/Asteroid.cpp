#include "Asteroid.h"

Asteroid::Asteroid(double halfSided)
{
	transform = new Transform();
	CreatePoints(halfSided);

}

Asteroid::~Asteroid()
{
	delete transform;
}

void Asteroid::CreatePoints(double halfSide)
{
	_points.push_back(std::array<double, 2> {-halfSide, halfSide});
	_points.push_back(std::array<double, 2> {halfSide, -halfSide});
	_points.push_back(std::array<double, 2> {halfSide, halfSide});

	int asteroidBounds[4] = { -halfSide, halfSide, -halfSide, halfSide };

	SetBoundingBox(asteroidBounds);
}