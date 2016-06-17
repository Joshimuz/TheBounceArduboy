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
		xVelocity *= 0.93f;
	}

	if (arduboy.pressed(A_BUTTON))
	{
		if (canJump)
		{
			if (gravity >= 0)
			{
				yVelocity = -2.5;
			}
			else
			{
				yVelocity = 2.5;
			}
			canJump = false;
		}

	}


	//PhysX
	// Add gravity
	yVelocity += gravity;

	if (botCol)
	{
		yVelocity = fabsf(yVelocity) * -1.1f;
		if (gravity >= 0)
		{
			canJump = true;
		}
		botCol = false;
		arduboy.tunes.tone(400 + (fabsf(yVelocity) * 50), 10);
	}
	else if (topCol)
	{
		yVelocity = fabsf(yVelocity) * 1.1f;
		if (gravity <= 0)
		{
			canJump = true;
		}
		topCol = false;
		arduboy.tunes.tone(400 + (fabsf(yVelocity) * 50), 10);
	}

	if (rightCol)
	{
		xVelocity = fabsf(xVelocity) * -1.5f;
		canJump = true;
		rightCol = false;
		arduboy.tunes.tone(400 + (fabsf(xVelocity) * 50), 10);
	}
	else if (leftCol)
	{
		xVelocity = fabsf(xVelocity) * 1.5f;
		canJump = true;
		leftCol = false;
		arduboy.tunes.tone(400 + (fabsf(xVelocity) * 50), 10);
	}

	// Add drag
	yVelocity *= 0.995f; 

	xVelocity *= 0.98f;

	// Limit speed
	if (yVelocity >= 2.2f && gravity >= 0)
	{
		yVelocity = 2.2f;
	}
	else if (yVelocity <= -2.2f && gravity <= 0)
	{
		yVelocity = -2.2f;
	}

	if (xVelocity > 4)
	{
		xVelocity = 4;
	}
	else if (xVelocity < -4)
	{
		xVelocity = -4;
	}

	// Apply Velocity
	y += yVelocity;
	x += xVelocity;

	if (!canInteract)
	{
		interactTimer--;

		if (interactTimer <= 0)
		{
			canInteract = true;
		}
	}
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

	interactTimer = 0;
	canInteract = true;
}

void PlayerClass::hitInteractable()
{
	interactTimer = 15;
	canInteract = false;
}

PlayerClass player;

