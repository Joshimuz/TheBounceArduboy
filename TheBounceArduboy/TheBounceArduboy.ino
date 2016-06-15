// Joshimuz 2016

#include "Maps.h"
#include "Sprites.h"
#include "Player.h"
#include "Arduboy.h"

Arduboy arduboy;

// The current state of the game
byte gameState = 1; // 1 = MainMenu, 2 = Gameplay, 3 = End level transion

// The selection in the menu
bool introSelection = 1; 
// If the menu selection was changed the previous frame
bool introChanged; 

#define LEVEL1ARRAYSIZE		22

#define LEVEL2ARRAYSIZE		13

// The currently used level
byte currentLevel = 2;
// The size of the array for the current level
byte currentLevelArraySize = LEVEL2ARRAYSIZE;

// Position of the camera used for drawing
short camX;
short camY;

// The respawn position for the player
byte spawnX = 32;
byte spawnY = 32;

// The kill plane at the bottom of the level
#define MAPFLOOR	300

// The struct for the objects in the level
struct MapObject
{
	short x;
	short y;
	byte w;
	byte h;
	byte type;
};

// The levels which are an array holding the MapObject struct for every object in the level
const MapObject level1[LEVEL1ARRAYSIZE] =
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
const MapObject level2[LEVEL2ARRAYSIZE] =
{
//	   X    Y   W    H  type
	{ -84, 64, 148, 4, 0 },
	{ 64, 28, 4, 40, 0 },
	{ 0, 28, 64, 4, 0 },
	{ -32, 28, 32, 14, 0 },
	{ -64, 28, 32, 20, 0 },
	{ -96, 28, 32, 24, 0 },
	{ -192, 128, 108, 4, 0 },
	{ -84, 68, 4, 64, 0},
	{ -160, 95, 32, 23, 0},
	{ -132, 63, 4, 32, 0},
	{ -192, 64, 4, 64, 0},
	{ -192, 60, 64, 4, 0},
	{ -150, 70, 10, 25, 2}
};

// Pointer to the current level that is being used
const MapObject*  currentMapData = level2;

void setup() 
{
	// Start arduboy stuff
	arduboy.begin();
	// Framerate to 30 due to console peasntry
	arduboy.setFrameRate(30);

	// Basically setup() for the player but also functions as respawning
	player.respawn(spawnX, spawnY);

	//arduboy.setRGBled(255, 255, 255); //God damn flipped LED Q___Q
}

void loop() 
{
	// Wait for the next frame
	if (!(arduboy.nextFrame()))
		return;
	// Remove everything currently drawn to the screen
	arduboy.clear();
	

	// Intro
	if (gameState == 1)
	{
			
		if (arduboy.pressed(A_BUTTON))
		{
			if (introSelection)
			{
				// Start the game when PLAY button pressed
				gameState = 2;
				// Now that something sudo-random has happened (user input) init the random seed
				arduboy.initRandomSeed();
			}
		}
		if (arduboy.pressed(LEFT_BUTTON) || arduboy.pressed(RIGHT_BUTTON))
		{
			// If the selection didn't change last frame
			if (!introChanged)
			{
				// Change it
				introSelection = !introSelection;
				introChanged = true;
			}
		}
		else if (introChanged)
		{
			// A frame has passed so reset the value
			introChanged = false;
		}

		// Draw the menu
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
				currentLevelArraySize = LEVEL2ARRAYSIZE;
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
		else if (currentLevel == 2) // Draw B button tutorial
		{
			arduboy.drawBitmap(-155 - camX, 98 - camY, abButtons, 20, 14, 1);
			arduboy.fillRect(-152 - camX, 104 - camY, 4, 6, 1);
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