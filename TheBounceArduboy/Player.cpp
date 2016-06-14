// Joshimuz 2016

#include "Player.h"

void PlayerClass::update(Arduboy& arduboy)
{
	if (arduboy.pressed(RIGHT_BUTTON))
	{
		if (xVelocity < 1.2f)
		{
			xVelocity += 0.03f;
		}
	}
	else if (arduboy.pressed(LEFT_BUTTON))
	{
		if (xVelocity > -1.2f)
		{
			xVelocity -= 0.03f;
		}
	}

	if (arduboy.pressed(DOWN_BUTTON) || arduboy.pressed(B_BUTTON))
	{
		if (yVelocity < -1)
		{
			yVelocity = -1;
		}
		xVelocity *= 0.8f;
	}

	if (arduboy.pressed(A_BUTTON))
	{
		if (canJump)
		{
			yVelocity = -2.5;
			canJump = false;
		}

	}


	//PhysX
	// Add gravity
	yVelocity += 0.15f; 

	//if (collisions == 1 || collisions == 11 || collisions == 21)// bottom
	//{
	//	yVelocity = fabsf(yVelocity) * -1.1f;
	//	canJump = true;
	//	y--;
	//	botCol = false;
	//}
	//else if (collisions == 2 || collisions == 12 || collisions == 22)// top
	//{
	//	yVelocity = fabsf(yVelocity) * 1.1f;
	//	y++;
	//	topCol = false;
	//}
	//if (collisions >= 10 && collisions < 20)// left
	//{
	//	xVelocity = fabsf(xVelocity) * 1.5f;
	//	canJump = true;
	//	x++;
	//	leftCol = false;
	//}
	//else if (collisions >= 20)// right
	//{
	//	xVelocity = fabsf(xVelocity) * -1.5f;
	//	canJump = true;
	//	x--;
	//	rightCol = false;
	//}

	if (botCol)
	{
		yVelocity = fabsf(yVelocity) * -1.1f;
		canJump = true;
		//y--;
		botCol = false;
	}
	else if (topCol)
	{
		yVelocity = fabsf(yVelocity) * 1.1f;
		//y++;
		topCol = false;
	}

	if (rightCol)
	{
		xVelocity = fabsf(xVelocity) * -1.5f;
		canJump = true;
		//x--;
		rightCol = false;
	}
	else if (leftCol)
	{
		xVelocity = fabsf(xVelocity) * 1.5f;
		canJump = true;
		//x++;
		leftCol = false;
	}

	// Add drag
	yVelocity *= 0.995f; 

	xVelocity *= 0.98f;

	// Limit speed
	if (yVelocity >= 2.2f)
	{
		yVelocity = 2.2f;
	}

	// Apply Velocity
	y += yVelocity;
	x += xVelocity;
}
void PlayerClass::respawn(short spawnX, short spawnY)
{
	x = spawnX;
	y = spawnY;

	yVelocity = 0;
	xVelocity = 0; 

	canJump = false;

	leftCol = false;
	rightCol = false;
	topCol = false;
	botCol = false;
}

PlayerClass player;

