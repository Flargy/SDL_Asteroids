#include "Player.h"
#include <math.h>
#include <iostream>

// creates a new function for calling sin and cos with degrees instead of radians
#define SIN(x) sin(x * 3.141592653589 / 180) 
#define COS(x) cos(x * 3.141592653589 / 180)

Player::Player()
{
}



void Player::Init(int xPos, int yPos, int width, int height)
{
	_width = width;
	_height = height;
	CreatePoints();
	startPosition.x = xPos;
	startPosition.y = yPos;
	double rotation[4]{ 1,0,0,1 };
	double movement[2]{ 0,0 };
	int position[2]{ xPos, yPos };
	collisionFunction = std::bind(&Player::Collide, this);


	transform = Transform(rotation, movement, position);
	transform.SetDeceleration(0.98);

	int PlayerBounds[4] = { -height, height, -height, height };
	SetBoundingBox(PlayerBounds);
}

/*
* Destructor for the player, clears out the 2d array
*/
Player::~Player() 
{
}

void Player::Reset()
{
	alive = true;
	transform.SetPosition(startPosition.x, startPosition.y);
	transform.SetRotation(array2D<double, 2, 2>{1,0,0,1});
	transform.SetVelocity(0,0);
}

/*
* Sets up the relative points for drawing the player ship
*/
void Player::CreatePoints() 
{
	_points = ResourceManager::getInstance()._shapes["player"];
}


/*
* Rotates the player by "degrees"
*/
void Player::Rotate(int degrees) 
{
	transform.Rotate(degrees);

}

/*
* moves the player "forwards" * rotation
*/
void Player::Move() 
{
	transform.Move();
}

void Player::Accelerate()
{
	transform.AccelerateForward();
}

void Player::Collide()
{
	alive = false;
}

