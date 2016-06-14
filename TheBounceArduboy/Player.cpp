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

	if (botCol)
	{
		yVelocity = fabsf(yVelocity) * -1.1f;
		canJump = true;
		//y--;
		botCol = false;
		arduboy.tunes.tone(400 + (fabsf(yVelocity) * 50), 10);
	}
	else if (topCol)
	{
		yVelocity = fabsf(yVelocity) * 1.1f;
		//y++;
		topCol = false;
		arduboy.tunes.tone(400 + (fabsf(yVelocity) * 50), 10);
	}

	if (rightCol)
	{
		xVelocity = fabsf(xVelocity) * -1.5f;
		canJump = true;
		//x--;
		rightCol = false;
		arduboy.tunes.tone(400 + (fabsf(xVelocity) * 50), 10);
	}
	else if (leftCol)
	{
		xVelocity = fabsf(xVelocity) * 1.5f;
		canJump = true;
		//x++;
		leftCol = false;
		arduboy.tunes.tone(400 + (fabsf(xVelocity) * 50), 10);
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

