// Joshimuz 2016

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
#define LEVEL3ARRAYSIZE		14
#define LEVEL4ARRAYSIZE		35
#define LEVEL5ARRAYSIZE		47
#define LEVEL6ARRAYSIZE		24
#define LEVEL7ARRAYSIZE		55
#define LARGESTARRAYSIZE	55

// The currently used level
byte currentLevel;
// The size of the array for the current level
byte currentLevelArraySize;

// Position of the camera used for drawing
short camX; short camY;

// The respawn position for the player
short spawnX; short spawnY;

// The kill plane at the bottom of the level
#define MAPFLOOR			300
#define MAPCEILING			-300

float menuBallY = -15;
float menuBallVelo;

// The struct for the objects in the level
struct MapObject
{
	short x; short y;
	byte w; byte h;
	byte type;	// 0 = block, 1 = spike(6w10h), 2 = endlevel(10w25h), 3 = checkpoint(2w20h), 4 = Portal One, 5 = Portal Two, 6 = Removal Button(16w4h), 7 = Add Button, 8 = Gravity Button
				// 11 = Upsidedown Spike, 15 = 5 spikes(46w10h), 16 = 5 upsidedown spikes
				// 99 = Pressed Button, 100 = BlockToAdd
};

// Levels stored in Flash to save RAM, copied to currentMapData when needed
PROGMEM static const MapObject level1[LEVEL1ARRAYSIZE] =
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
PROGMEM static const MapObject level2[LEVEL2ARRAYSIZE] =
{
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
PROGMEM static const MapObject level3[LEVEL3ARRAYSIZE] =
{
	{ 0, 64, 224, 4, 0 },
	{ 64, 40, 32, 4, 0 },
	{ 96, 16, 30, 4, 0 },
	{ 128, -12, 28, 4, 0 },
	{ 160, -36, 224, 4, 0 },
	{ 224, -60, 20, 4, 0 },
	{ 256, -84, 18, 4, 0 },
	{ 288, -108, 16, 4, 0 },
	{ 320, -132, 128, 4, 0 },
	{ 352, -156, 20, 4, 0 },
	{ 384, -180, 18, 4, 0 },
	{ 352, -204, 16, 4, 0 },
	{ 384, -228, 64, 4, 0 },
	{ 410, -253, 10, 25, 2 }
};
PROGMEM static const MapObject level4[LEVEL4ARRAYSIZE] =
{
	{ 0, 64, 255, 4, 0 },
	{ 0, 0, 4, 64, 0 },
	{ 64, 54, 6, 10, 1},
	{ 128, 54, 6, 10, 1},
	{ 138, 54, 6, 10, 1},
	{ 148, 54, 6, 10, 1},
	{ 212, 54, 6, 10, 1},
	{ 222, 54, 6, 10, 1 },
	{ 247, 54, 6, 10, 1},
	{ 257, 54, 6, 10, 1 },
	{ 254, 64, 192, 4, 0},
	{ 311, 54, 46, 10, 15},
	{ 361, 54, 6, 10, 1 },
	{ 333, 44, 14, 4, 0 },
	{ 393, 44, 2, 20, 3 },
	{ 446, 64, 4, 14, 0 },
	{ 446, 78, 64, 4, 0 },
	{ 506, 64, 4, 14, 0 },
	{ 450, 68, 6, 10, 1 },
	{ 462, 68, 6, 10, 1 },
	{ 474, 68, 6, 10, 1 },
	{ 486, 68, 6, 10, 1 },
	{ 498, 68, 6, 10, 1 },
	{ 510, 64, 200, 4, 0 },
	{ 520, 54, 46, 10, 15 },
	{ 629, 54, 6, 10, 1 },
	{ 637, 54, 11, 10, 0 },
	{ 639, 44, 6, 10, 1 },
	{ 647, 44, 11, 10, 0 },
	{ 647, 54, 11, 10, 0},
	{ 649, 34, 6, 10, 1 },
	{ 657, 54, 11, 10, 0 },
	{ 659, 44, 6, 10, 1 },
	{ 669, 54, 6, 10, 1 },
	{ 690, 39, 10, 25, 2 }
};
PROGMEM static const MapObject level5[LEVEL5ARRAYSIZE] =
{
	{ 0, 64, 255, 4, 0 },
	{ 0, 0, 255, 4, 0 },
	{ 0, 4, 4, 60, 0},
	{ 64, 8, 6, 10, 11 },
	{ 64, 49, 6, 10, 1 },
	{ 62, 4, 11, 4, 0 },
	{ 62, 60, 11, 4, 0 },
	{ 128, 12, 6, 10, 11 },
	{ 128, 45, 6, 10, 1 },
	{ 126, 4, 11, 8, 0 },
	{ 126, 56, 11, 8, 0 },
	{ 192, 8, 6, 10, 11 },
	{ 192, 41, 6, 10, 1 },
	{ 190, 4, 11, 4, 0 },
	{ 190, 52, 11, 12, 0 },
	{ 240, 44, 2, 20, 3 },
	{ 290, 64, 20, 4, 0},
	{ 320, 8, 6, 10, 11 },
	{ 320, 49, 6, 10, 1 },
	{ 330, 8, 6, 10, 11 },
	{ 330, 49, 6, 10, 1 },
	{ 350, 44, 20, 4, 0 },
	{ 380, -12, 6, 10, 11 },
	{ 380, 29, 6, 10, 1 },
	{ 390, -12, 6, 10, 11 },
	{ 390, 29, 6, 10, 1 },
	{ 410, 175, 130, 4, 0},
	{ 500, 155, 2, 20, 3 },
	{ 510, 130, 160, 4, 0},
	{ 510, 190, 160, 4, 0 },
	{ 512, 180, 46, 10, 15},
	{ 512, 134, 46, 10, 16},
	{ 562, 180, 46, 10, 15 },
	{ 562, 134, 46, 10, 16 },
	{ 612, 180, 46, 10, 15 },
	{ 612, 134, 46, 10, 16 },
	{ 662, 180, 6, 10, 1 },
	{ 662, 134, 6, 10, 11 },
	{ 557, 160, 30, 4, 0 },
	{ 600, 175, 30, 4, 0 },
	{ 635, 155, 30, 4, 0 },
	{ 660, 175, 96, 4, 0 },
	{ 700, 155, 2, 20, 3 },
	{ 775, 155, 6, 10, 11 },
	{ 773, 105, 11, 50, 0 },
	{ 800, 175, 30, 4, 0 },
	{ 815, 150, 10, 25, 2}
};
PROGMEM static const MapObject level6[LEVEL6ARRAYSIZE] =
{
	{ -50, 64, 105, 4, 0 },
	{ -20, 16, 4, 48, 0 },
	{ -10, 60, 16, 4, 6 },
	{ 51, 16, 4, 48, 0 },
	{ -125, 12, 180, 4, 0 },
	{ -50, 68, 4, 64, 0 },
	{ -255, 132, 209, 4, 0 },
	{ -155, 68, 4, 64, 0 },
	{ -125, 16, 4, 116, 100 },
	{ -146, 128, 16, 4, 7 },
	{ -225, 0, 4, 74, 0},
	{ -285, 68, 4, 64, 0 },
	{ -255, 128, 16, 4, 106},
	{ -275, 128, 16, 4, 7},
	{ -510, 132, 255, 4, 0},
	{ -417, 107, 10, 25, 102 },
	{ -460, 104, 16, 4, 107 },
	{ -340, 80, 16, 4, 107 },
	{ -500, 116, 16, 4, 107 },
	{ -420, 92, 16, 4, 107 },
	{ -380, 104, 16, 4, 107 },
	{ -500, 80, 16, 4, 107 },
	{ -340, 116, 16, 4, 7},
	{ -510, 0, 4, 132, 0}
};
PROGMEM static const MapObject level7[LEVEL7ARRAYSIZE] =
{
	{ 48, -20, 10, 20, 2 },
	{ 40, 0, 24, 4, 0 },
	{ 0, -24, 64, 4, 0 },
	{ 0, 64, 255, 4, 0 },
	{ 0, -64, 4, 128, 0 },
	{ 64, -96, 4, 128, 0 },
	{ 128, -28, 4, 92, 0 },
	{ 255, 64, 255, 4, 0 },
	{ 98, 32, 30, 4, 0 },
	{ 118, 21, 6, 10, 1 },
	{ 114, 36, 6, 10, 11 },
	{ 68, 0, 30, 4, 0 },
	{ 71, -11, 6, 10, 1 },
	{ 75, 4, 6, 10, 11 },
	{ 98, -32, 188, 4, 0 },
	{ 120, -52, 20, 20, 0 },
	{ 72, -68, 16, 4, 6 },
	{ 114, -28, 6, 10, 11 },
	{ 68, -64, 30, 4, 0 },
	{ 64, -100, 68, 4, 0 },
	{ 128, -96, 4, 44, 0 },
	{ 256, -28, 4, 72, 0 },
	{ 132, -56, 32, 4, 0 },
	{ 164, -88, 4, 36, 0 },
	{ 168, -88, 88, 4, 0 },
	{ 170, -84, 6, 10, 11 },
	{ 180, -84, 6, 10, 11 },
	{ 203, -43, 6, 10, 1 },
	{ 213, -43, 6, 10, 1 },
	{ 236, -84, 6, 10, 11 },
	{ 246, -84, 6, 10, 11 },
	{ 256, -88, 4, 32, 0 },
	{ 260, -60, 64, 4, 0 },
	{ 324, -90, 4, 98, 0 },
	{ 315, -56, 6, 10, 11 },
	{ 277, -28, 6, 10, 11 },
	{ 294, 8, 70, 4, 0 },
	{ 296, 12, 6, 10, 11 },
	{ 356, 44, 20, 20, 0 },
	{ 140, 60, 16, 4, 6 },
	{ 324, 44, 2, 20, 3 },
	{ 364, -60, 4, 104, 0 },
	{ 192, 8, 4, 56, 0 },
	{ 191, -3, 6, 10, 1 },
	{ 196, 40, 30, 4, 0 },
	{ 162, 40, 30, 4, 0 },
	{ 226, 8, 30, 4, 0 },
	{ 132, 8, 30, 4, 0 },
	{ 394, -90, 4, 154, 0 },
	{ 328, -90, 66, 4, 0 },
	{ 338, 4, 16, 4, 8 },
	{ 90, -84, 2, 20, 3 },
};

// Copy in RAM of the current level that is being used. Must be at least the size of the largest level
MapObject currentMapData[LARGESTARRAYSIZE];

void setup() 
{
	// Start arduboy stuff
	arduboy.beginNoLogo();

	// Framerate to 30 due to console peasntry
	arduboy.setFrameRate(30);

	LoadLevel(1);

	// Basically setup() for the player but also functions as respawning
	player.respawn(spawnX, spawnY);
	//player.respawn(250, -50);

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
			if (!introChanged)
			{
				if (introSelection)
				{
					// Start the game when PLAY button pressed
					gameState = 2;
					// Now that something sudo-random has happened (user input) init the random seed
					arduboy.initRandomSeed();
				}
				else
				{
					if (arduboy.audio.enabled())
					{
						arduboy.audio.off();
						arduboy.audio.saveOnOff();
					}
					else
					{
						arduboy.audio.on();
						arduboy.audio.saveOnOff();
					}
				}

				introChanged = true;
			}
		}
		else if (arduboy.pressed(LEFT_BUTTON) || arduboy.pressed(RIGHT_BUTTON))
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

		menuBallVelo += 0.15f;

		if (menuBallY >= 32)
		{
			menuBallVelo = fabsf(menuBallVelo) * -0.94f;
		}
		
		menuBallY += menuBallVelo;

		// Draw the menu
		arduboy.drawBitmap(0, 0, titleScreen, 128, 64, 1);
		if (introSelection)
		{
			arduboy.drawBitmap(15, 47, playButton, 31, 14, 1);
			arduboy.drawBitmap(82, 49, configButton, 31, 10, 1);
		}
		else
		{
			arduboy.drawBitmap(15, 49, playButton, 31, 10, 1);
			arduboy.drawBitmap(82, 47, configButton, 31, 14, 1);
		}

		arduboy.drawBitmap(29, (int)menuBallY, menuBall, 16, 16, 1);
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
		else if (player.y < MAPCEILING)
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
					switch (currentMapData[i].type)
					{
						default:
							player.botCol = true;
							break;
						case 2:
							gameState = 3;
							spawnY = 2;
							break;
						case 3:
							if (spawnX != currentMapData[i].x)
							{
								arduboy.tunes.tone(4000, 100);
								spawnX = currentMapData[i].x;
								spawnY = currentMapData[i].y - 12;
							}
							break;
						case 4:
							if (player.canInteract)
							{
								player.x = (float)(currentMapData[i + 1].x + currentMapData[i + 1].w / 2);
								player.y = (float)(currentMapData[i + 1].y + currentMapData[i + 1].h / 2);
							}

							player.hitInteractable();
							break;
						case 5:
							if (player.canInteract)
							{
								player.x = (float)(currentMapData[i - 1].x + currentMapData[i - 1].w / 2);
								player.y = (float)(currentMapData[i - 1].y + currentMapData[i - 1].h / 2);
							}

							player.hitInteractable();
							break;
						case 6:
							player.botCol = true;
							currentMapData[i].type = 99;
							arduboy.tunes.tone(2000, 100);
							currentMapData[i - 1] = { 0,0,0,0,0 };
							break;
						case 7:
							player.botCol = true;
							currentMapData[i].type = 99;
							arduboy.tunes.tone(2000, 100);
							currentMapData[i - 1].type -= 100;
							break;
						case 8:
							player.botCol = true;
							if (player.canInteract && player.gravity >= 0)
							{
								player.gravity *= -1;
								arduboy.tunes.tone(2000, 100);
							}
							player.hitInteractable();
							break;
						case 100:
							break;
					}
				}
				else if (player.x >= currentMapData[i].x
					&& player.x <= currentMapData[i].x + currentMapData[i].w
					&& player.y - 3 >= currentMapData[i].y
					&& player.y - 3 <= currentMapData[i].y + currentMapData[i].h)
				{
					if (currentMapData[i].type != 2 && currentMapData[i].type != 3 && currentMapData[i].type != 4 && currentMapData[i].type != 5 && currentMapData[i].type != 100)
					{
						player.topCol = true;
					}
					if (currentMapData[i].type == 8)
					{
						if (player.canInteract && player.gravity <= 0)
						{
							player.gravity *= -1;
							arduboy.tunes.tone(2000, 100);
						}
						player.hitInteractable();
					}
				}
				if (player.x + 3 >= currentMapData[i].x
					&& player.x + 3 <= currentMapData[i].x + currentMapData[i].w
					&& player.y >= currentMapData[i].y
					&& player.y <= currentMapData[i].y + currentMapData[i].h)
				{
					if (currentMapData[i].type != 2 && currentMapData[i].type != 3 && currentMapData[i].type != 4 && currentMapData[i].type != 5 && currentMapData[i].type != 100)
					{
						player.rightCol = true;
					}
				}
				else if (player.x - 3 >= currentMapData[i].x
					&& player.x - 3 <= currentMapData[i].x + currentMapData[i].w
					&& player.y >= currentMapData[i].y
					&& player.y <= currentMapData[i].y + currentMapData[i].h)
				{
					if (currentMapData[i].type != 2 && currentMapData[i].type != 3 && currentMapData[i].type != 4 && currentMapData[i].type != 5 && currentMapData[i].type != 100)
					{
						player.leftCol = true;
					}
				}

				if (player.topCol || player.botCol || player.leftCol || player.rightCol)
				{
					//switch (currentMapData[i].type)
					//{
					//default:
					//	break;

					//case 1: // Spike
					//	player.respawn(spawnX, spawnY);
					//	break;
					//case 11: // Upsidedown Spike
					//	player.respawn(spawnX, spawnY);
					//	break;
					//}

					if (currentMapData[i].type == 1 || currentMapData[i].type == 11 || currentMapData[i].type == 15 || currentMapData[i].type == 16)
					{
						player.respawn(spawnX, spawnY);
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
		if (arduboy.everyXFrames(5))
		{
			if (currentLevelArraySize > 0)
			{
				currentLevelArraySize--;
			}
		}

		if (spawnY > 128)
		{
			gameState = 2;

			LoadLevel(currentLevel + 1);

			//currentLevel++;
			player.respawn(spawnX, spawnY);
		}
		arduboy.tunes.tone(5000, 10);
	}
	// Gameplay Draw
	if (gameState == 2 || gameState == 3)
	{
		//// Draw ////
		//arduboy.setCursor(0, 0);
		//arduboy.print(arduboy.cpuLoad());
		//arduboy.print(player.x);
		//arduboy.print(" ");
		//arduboy.print(player.y);

		for (byte i = 0; i < currentLevelArraySize; i++)
		{
			//arduboy.fillRect(currentMapData[i].x - camX, currentMapData[i].y - camY, currentMapData[i].w, currentMapData[i].h, 1);
			switch (currentMapData[i].type)
			{
			default:
				arduboy.drawRect(currentMapData[i].x - camX, currentMapData[i].y - camY, currentMapData[i].w, currentMapData[i].h, 1);
				break;
			case 1: // Spike
				arduboy.drawTriangle(currentMapData[i].x - camX - 2, currentMapData[i].y + currentMapData[i].h - camY, currentMapData[i].x + (currentMapData[i].w / 2) - camX, currentMapData[i].y - camY,
					currentMapData[i].x + currentMapData[i].w - camX + 2, currentMapData[i].y + currentMapData[i].h - camY, 1);
				break;
			case 2: // Next Level
				//arduboy.drawRoundRect(currentMapData[i].x - camX, currentMapData[i].y - camY, currentMapData[i].w, currentMapData[i].h, 5, 1);
				arduboy.drawRect(currentMapData[i].x - camX, currentMapData[i].y - camY, currentMapData[i].w, currentMapData[i].h, 1);
				arduboy.drawFastVLine(random(currentMapData[i].x - camX, currentMapData[i].x - camX + currentMapData[i].w), currentMapData[i].y - camY, currentMapData[i].h, 1);
				break;
			case 3:
				arduboy.drawRect(currentMapData[i].x - camX, currentMapData[i].y - camY, currentMapData[i].w, currentMapData[i].h, 1);
				if (spawnX == currentMapData[i].x)
				{
					arduboy.drawRect(currentMapData[i].x - camX + currentMapData[i].w, currentMapData[i].y - camY, 8, 5, 1);
				}
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				if (player.gravity >= 0)
				{
					arduboy.drawRect(currentMapData[i].x - camX + 4, currentMapData[i].y - camY - 2, 8, 3, 1);
				}
				else
				{
					arduboy.drawRect(currentMapData[i].x - camX + 4, currentMapData[i].y - camY + 3, 8, 3, 1);
				}
				
				arduboy.drawRect(currentMapData[i].x - camX, currentMapData[i].y - camY, 16, 4, 1);
				break;
			case 11: // Upsidedown Spike
				arduboy.drawTriangle(currentMapData[i].x - camX - 2, currentMapData[i].y - camY, currentMapData[i].x + (currentMapData[i].w / 2) - camX, currentMapData[i].y + currentMapData[i].h - camY,
					currentMapData[i].x + currentMapData[i].w - camX + 2, currentMapData[i].y - camY, 1);
				break;
			case 15: // 5 Spikes
				for (byte z = 0; z < 5; z++)
				{
					arduboy.drawTriangle(currentMapData[i].x - camX - 2 + (z * 10), currentMapData[i].y + currentMapData[i].h - camY, currentMapData[i].x + 3 - camX + (z * 10), currentMapData[i].y - camY,
						currentMapData[i].x + 8 - camX + (z * 10), currentMapData[i].y + currentMapData[i].h - camY, 1);
				}
				break;
			case 16: // 5 Upsidedown Spikes
				for (byte z = 0; z < 5; z++)
				{
					arduboy.drawTriangle(currentMapData[i].x - camX - 2 + (z * 10), currentMapData[i].y - camY, currentMapData[i].x + 3 - camX + (z * 10), currentMapData[i].y + currentMapData[i].h - camY,
						currentMapData[i].x + 8 - camX + (z * 10), currentMapData[i].y - camY, 1);
				}
				break;
			case 99:
				arduboy.drawBitmap(currentMapData[i].x - camX, currentMapData[i].y - camY, buttonBase, 16, 4, 1);
				break;
			case 100:
				break;
			}

			// Saves Flash if check for duplicate types outside of switch with same if statement
			if (currentMapData[i].type == 4 || currentMapData[i].type == 5)
			{
				arduboy.drawRoundRect(currentMapData[i].x - camX, currentMapData[i].y - camY, currentMapData[i].w, currentMapData[i].h, 5, 1);
				//arduboy.drawLine(currentMapData[i].x + (currentMapData[i].w / 2) - camX, currentMapData[i].y + (currentMapData[i].h / 2) - camY,
				//	random(currentMapData[i].x, currentMapData[i].x + currentMapData[i].w) - camX, random(currentMapData[i].y, currentMapData[i].y + currentMapData[i].h) - camY, 1);
				for (byte z = 0; z < 2; z++)
				{
					arduboy.drawPixel(random(currentMapData[i].x + 2, currentMapData[i].x + currentMapData[i].w - 2) - camX, random(currentMapData[i].y + 2, currentMapData[i].y + currentMapData[i].h - 1) - camY, 1);
				}
			}
			else if (currentMapData[i].type == 6 || currentMapData[i].type == 7)
			{
				arduboy.drawBitmap(currentMapData[i].x - camX, currentMapData[i].y - camY, buttonBase, 16, 4, 1);
				arduboy.drawRect(currentMapData[i].x - camX + 4, currentMapData[i].y - camY - 2, 8, 3, 1);
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

void LoadLevel(byte levelNumber)
{
	byte i;

	switch (levelNumber)
	{
	case 1:
		for (i = 0; i < LEVEL1ARRAYSIZE; i++)
		{
			// Copy the value of level1[i] to currentMapData[i] from Flash to RAM using the memory address and size of the struct
			memcpy_P(&currentMapData[i], &level1[i], sizeof(level1[i]));
		}
		break;
	case 2:
		for (i = 0; i < LEVEL2ARRAYSIZE; i++)
		{
			memcpy_P(&currentMapData[i], &level2[i], sizeof(level2[i]));
		}
		break;
	case 3:
		for (i = 0; i < LEVEL3ARRAYSIZE; i++)
		{
			memcpy_P(&currentMapData[i], &level3[i], sizeof(level3[i]));
		}
		break;
	case 4:
		for (i = 0; i < LEVEL4ARRAYSIZE; i++)
		{
			memcpy_P(&currentMapData[i], &level4[i], sizeof(level4[i]));
		}
		break;
	case 5:
		for (i = 0; i < LEVEL5ARRAYSIZE; i++)
		{
			memcpy_P(&currentMapData[i], &level5[i], sizeof(level5[i]));
		}
		break;
	case 6:
		for (i = 0; i < LEVEL6ARRAYSIZE; i++)
		{
			memcpy_P(&currentMapData[i], &level6[i], sizeof(level6[i]));
		}
		break;
	case 7:
		for (i = 0; i < LEVEL7ARRAYSIZE; i++)
		{
			memcpy_P(&currentMapData[i], &level7[i], sizeof(level7[i]));
		}
		break;
	}

	currentLevelArraySize = i;
	currentLevel = levelNumber;
	spawnX = 32;
	spawnY = 32;
	player.gravity = DEFAULTGRAVITY;
}
