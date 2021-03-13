#include "CollidableObject.h"

CollidableObject::CollidableObject() : transform()
{

}

void CollidableObject::SetBoundingBox(int points[4])
{
	boundingBox = { points[0], points[1], points[2], points[3] };
}

void CollidableObject::Collision()
{
	if (alive)
		collisionFunction(); // think it works, needs to be tested
}
