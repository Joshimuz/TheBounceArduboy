// Joshimuz 2016

#include "Maps.h"
#include "Sprites.h"
#include "Player.h"
#include "Arduboy.h"
Arduboy arduboy;

bool introSelection = 1;
bool introChanged;
short gameState = 1;
short currentLevel = 1;

short camX;
short camY;

short spawnX = 32;
short spawnY = 32;

#define MAPFLOOR	300
short currentLevelArraySize = 22;

struct MapObject
{
	short x;
	short y;
	short w;
	short h;
	short type;
};

const MapObject level1[22] =
{
	{ 0, 64, 64, 4, 0 },
	{ 60, 68, 4, 32, 0 },
	{ 0, 16, 4, 48, 0 },
	{ 0, 12, 86, 4, 0 },
	{ 86, 12, 4, 32, 0 },
	{ 60, 100, 170, 4, 0 },
	{ 86, 44, 100, 4, 0 },
	{ 120, 90, 10, 10, 0 },
	{ 155, 85, 15, 15, 0 },
	{ 200, 85, 15, 15, 0 },
	{ 215, 85, 15, 15, 0 },
	{ 220, 75, 10, 10, 0 },
	{ 230, 75, 100, 4, 0 },
	{ 300, 45, 30, 30, 0 },
	{ 330, 15, 30, 30, 0 },
	{ 360, 15, 70, 4, 0 },
	{ 186, 24, 4, 24, 0 },
	{ 186, 20, 80, 4, 0 },
	{ 266, -30, 4, 54, 0 },
	{ 270, -30, 160, 4, 0 },
	{ 426, -26, 4, 41, 0 },
	{ 406, -10, 10, 25, 2 }
};

const MapObject level2[1] =
{
	{ 0, 64, 64, 4, 0 }
};

const MapObject*  currentMapData = level1;

void setup() 
{
	arduboy.begin();
	arduboy.setFrameRate(30);

	player.respawn(spawnX, spawnY);

	//arduboy.setRGBled(0, 0, 255); God damn flipped LED Q___Q
}

void loop() 
{
	if (!(arduboy.nextFrame()))
		return;
	arduboy.clear();

	// Intro
	if (gameState == 1)
	{
		arduboy.drawBitmap(0, 0, titleScreen, 128, 42, 1);
		if (introSelection)
		{
			arduboy.drawBitmap(12, 48, playButton, 31, 16, 1);
			arduboy.drawBitmap(85, 52, configButton, 31, 16, 1);
		}
		else
		{
			arduboy.drawBitmap(12, 52, playButton, 31, 16, 1);
			arduboy.drawBitmap(85, 48, configButton, 31, 16, 1);
		}
		
		if (arduboy.pressed(A_BUTTON))
		{
			if (introSelection)
			{
				gameState = 2;
				arduboy.initRandomSeed();
			}
		}
		if (arduboy.pressed(LEFT_BUTTON) || arduboy.pressed(RIGHT_BUTTON))
		{
			if (!introChanged)
			{
				introSelection = !introSelection;
				introChanged = true;
			}
		}
		else if (introChanged)
		{
			introChanged = false;
		}
	} // Intro
	// Gameplay
	else if (gameState == 2)
	{
		//// Update ////
		if (arduboy.pressed(UP_BUTTON))
		{
			gameState = 1;
		}

		player.update(arduboy);

		if (player.y > MAPFLOOR)
		{
			player.respawn(spawnX, spawnY);
		}

		// Collisions!
		for (short i = 0; i < currentLevelArraySize; i++)
		{
			if (player.x >= currentMapData[i].x - 5
				&& player.x <= currentMapData[i].x + currentMapData[i].w + 5
				&& player.y >= currentMapData[i].y - 5
				&& player.y <= currentMapData[i].y + currentMapData[i].h + 5)
			{
				//arduboy.print("NEAR");
				if (player.x >= currentMapData[i].x
					&& player.x <= currentMapData[i].x + currentMapData[i].w
					&& player.y + 4 >= currentMapData[i].y
					&& player.y + 4 <= currentMapData[i].y + currentMapData[i].h)
				{
					if (currentMapData[i].type != 2)
					{
						player.botCol = true;
					}
					else
					{
						gameState = 3;
						spawnY = 2;
					}
				}
				else if (player.x >= currentMapData[i].x
					&& player.x <= currentMapData[i].x + currentMapData[i].w
					&& player.y - 3 >= currentMapData[i].y
					&& player.y - 3 <= currentMapData[i].y + currentMapData[i].h)
				{
					if (currentMapData[i].type != 2)
					{
						player.topCol = true;
					}
				}
				if (player.x + 3 >= currentMapData[i].x
					&& player.x + 3 <= currentMapData[i].x + currentMapData[i].w
					&& player.y >= currentMapData[i].y
					&& player.y <= currentMapData[i].y + currentMapData[i].h)
				{
					if (currentMapData[i].type != 2)
					{
						player.rightCol = true;
					}
				}
				else if (player.x - 3 >= currentMapData[i].x
					&& player.x - 3 <= currentMapData[i].x + currentMapData[i].w
					&& player.y >= currentMapData[i].y
					&& player.y <= currentMapData[i].y + currentMapData[i].h)
				{
					if (currentMapData[i].type != 2)
					{
						player.leftCol = true;
					}
				}

				if (player.topCol || player.botCol || player.leftCol || player.rightCol)
				{
					switch (currentMapData[i].type)
					{
					default:
						break;

					case 1: // Spike
						player.respawn(spawnX, spawnY);
						break;
					}
				}
			}
		}

		camX = camX + 0.07f * ((player.x - 64) - camX);
		camY = camY + 0.07f * ((player.y - 32) - camY);
	}
	// Hit lever marker
	else if (gameState == 3)
	{
		if (arduboy.everyXFrames(2))
		{
			player.y--;
			spawnY += 2;
		}

		if (spawnY > 128)
		{
			gameState = 2;
			spawnY = 32;
			if (currentLevel == 1)
			{
				currentLevel = 2;
				currentLevelArraySize = 1;
				currentMapData = level2;
				player.respawn(spawnX, spawnY);
			}
		}
		arduboy.tunes.tone(5000, 10);
	}
	// Gameplay Draw
	if (gameState == 2 || gameState == 3)
	{
		//// Draw ////
		arduboy.setCursor(0, 0);
		arduboy.print(arduboy.cpuLoad());
		//arduboy.print("X:");
		//arduboy.print(player.x);
		//arduboy.print(" Y:");
		//arduboy.print(player.y);

		for (short i = 0; i < currentLevelArraySize; i++)
		{
			//arduboy.fillRect(currentMapData[i].x - camX, currentMapData[i].y - camY, currentMapData[i].w, currentMapData[i].h, 1);
			switch (currentMapData[i].type)
			{
			default:
				arduboy.drawRect(currentMapData[i].x - camX, currentMapData[i].y - camY, currentMapData[i].w, currentMapData[i].h, 1);
				break;
			case 1: // Spike
				arduboy.drawTriangle(currentMapData[i].x - camX, currentMapData[i].y + currentMapData[i].h - camY, currentMapData[i].x + (currentMapData[i].w / 2) - camX, currentMapData[i].y - camY,
					currentMapData[i].x + currentMapData[i].w - camX, currentMapData[i].y + currentMapData[i].h - camY, 1);
				break;
			case 2: // Next Level
				//arduboy.drawRoundRect(currentMapData[i].x - camX, currentMapData[i].y - camY, currentMapData[i].w, currentMapData[i].h, 5, 1);
				arduboy.drawRect(currentMapData[i].x - camX, currentMapData[i].y - camY, currentMapData[i].w, currentMapData[i].h, 1);
				arduboy.drawFastVLine(random(currentMapData[i].x - camX, currentMapData[i].x - camX + currentMapData[i].w), currentMapData[i].y - camY, currentMapData[i].h, 1);
				break;
			}
		}

		if (currentLevel == 1) // Draw A button tutorial
		{
			arduboy.drawBitmap(305 - camX, 53 - camY, abButtons, 20, 14, 1);
			arduboy.fillRect(318 - camX, 55 - camY, 4, 6, 1);
		}

		if (gameState == 2)
		{
			arduboy.fillCircle((int)player.x - camX, (int)player.y - camY, 1, 1);
		}
		else
		{
			//arduboy.drawFastVLine((int)player.x - camX, (int)player.y - camY, spawnY, 1);
			arduboy.drawRect((int)player.x - camX, (int)player.y - camY, 2, spawnY, 1);
		}
		
	}

	arduboy.display();
}
