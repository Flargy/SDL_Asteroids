#include "Player.h"
#include <math.h>
#include <iostream>

// creates a new function for calling sin and cos with degrees instead of radians
#define SIN(x) sin(x * 3.141592653589 / 180) 
#define COS(x) cos(x * 3.141592653589 / 180)

/*
* Sets starting values
*/
Player::Player(int xPos, int yPos, int width, int height) :
	_width(width), _height(height) {
	CreatePoints();

	double rotation[4]{ 0,-1,1,0 };
	double movement[2]{ 0,0 };
	int position[2]{ xPos, yPos };
	collisionFunction = std::bind(&Player::Collide, this); 
	

	transform = new Transform(rotation, movement, position);
	transform->SetDeceleration(0.98);
}
/*
* Destructor for the player, clears out the 2d array
*/
Player::~Player() 
{
	delete transform;
}

/*
* Sets up the relative points for drawing the player ship
*/
void Player::CreatePoints() 
{
	_points.push_back(std::array<double, 2> {-_width, _height});
	_points.push_back(std::array<double, 2> {0, -_height});
	_points.push_back(std::array<double, 2> {_width, _height});
}


/*
* Rotates the player by "degrees"
*/
void Player::Rotate(int degrees) 
{
	double rotationMatrix[2][2];

	// remakes the rotation in degrees into a 2d rotation matrix
	double cosValue = COS(degrees);
	double sinValue = SIN(degrees);

	rotationMatrix[0][0] = cosValue;
	rotationMatrix[1][0] = sinValue;

	rotationMatrix[0][1] = -sinValue;
	rotationMatrix[1][1] = cosValue;

	transform->Rotate(degrees);

	// applies the rotation to the draw points for redenering
	for (int i = 0; i < 3; i++)
	{
		double x = _points[i][0];
		double y = _points[i][1];

		_points[i][0] = rotationMatrix[0][0] * x + rotationMatrix[1][0] * y;
		_points[i][1] = rotationMatrix[0][1] * x + rotationMatrix[1][1] * y;
	}
}

/*
* moves the player "forwards" * rotation
*/
void Player::Move() 
{
	transform->Move();
}

void Player::Accelerate()
{
	transform->AccelerateForward();
}

void Player::Collide()
{
	std::cout << "collision" << std::endl;
	// collision code here
}

