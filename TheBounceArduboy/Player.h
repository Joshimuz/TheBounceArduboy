// Joshimuz 2016

#ifndef _PLAYER_h
#define _PLAYER_h

#include "Arduboy.h"

class PlayerClass
{
 protected:
	 float xVelocity;
	 float yVelocity;

	 bool canJump;
 public:
	float x;
	float y;

	//byte collisions;

	bool leftCol;
	bool rightCol;
	bool topCol;
	bool botCol;

	void update(Arduboy& arduboy);
	void respawn(byte spawnX, byte spawnY);
};

extern PlayerClass player;

#endif

