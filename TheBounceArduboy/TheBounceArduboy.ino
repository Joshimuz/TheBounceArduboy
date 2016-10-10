// Joshimuz 2016
#define DEBUG 0

#include "Maps.h"
#include "Sprites.h"
#include "Player.h"
#include "Arduboy.h"

Arduboy arduboy;

// The current state of the game
byte gameState = 1; // 1 = MainMenu, 2 = Gameplay, 3 = End level transion, 4 = Options Menu, 5 = Level Select

// The selection in the menu
byte menuSelection = 1; 
// If the menu selection was changed the previous frame
bool selectionChanged; 

// The currently used level
byte currentLevel;
// The size of the array for the current level
byte currentLevelArraySize;

// Position of the camera used for drawing
short camX; short camY;

#define DEFAULTSPAWNX 32
#define DEFAULTSPAWNY 32

// The respawn position for the player
short spawnX; short spawnY;

// The kill plane at the bottom of the level
#define MAPFLOOR			300
#define MAPCEILING			-350

#if DEBUG == 0 // Don't draw title screen in debug mode to same ROM for text rendering
float menuBallY = -15;
float menuBallVelo;
#endif

// Copy in RAM of the current level that is being used. Must be at least the size of the largest level
MapObject currentMapData[LARGESTARRAYSIZE];

byte levelUnlocked;

void setup() 
{
	// Start arduboy stuff
	arduboy.beginNoLogo();

	// Framerate to 30
	arduboy.setFrameRate(30);

	// Read to see if there is any levels unlocked
	levelUnlocked = EEPROM.read(450);

	// Check if variable is within normal ranges
	if (levelUnlocked > 0 && levelUnlocked < TOTALNUMBEROFLEVELS)
	{
		LoadLevel(levelUnlocked);
	}
	else if (levelUnlocked == TOTALNUMBEROFLEVELS)
	{
		//gameState = 5;
		LoadLevel(1);
	}
	else
	{
		// If no valid save file found, create a new one
		EEPROM.write(450, 1);
		// Load first level
		LoadLevel(1);
		levelUnlocked = 1;
	}
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
			if (!selectionChanged)
			{
				if (menuSelection == 1)
				{
					// Start the game when PLAY button pressed
					gameState = 2;
					// Now that something sudo-random has happened (user input) init the random seed
					arduboy.initRandomSeed();
				}
				else
				{
					gameState = 4;

					arduboy.initRandomSeed();
				}

				selectionChanged = true;
			}
		}
		else if (arduboy.pressed(LEFT_BUTTON) || arduboy.pressed(RIGHT_BUTTON))
		{
			// If the selection didn't change last frame
			if (!selectionChanged)
			{
				// Change it
				if (menuSelection == 1)
				{
					menuSelection = 0;
				}
				else
				{
					menuSelection = 1;
				}

				selectionChanged = true;
			}
		}
		else
		{
			// A frame has passed so reset the value
			selectionChanged = false;
		}

#if DEBUG == 0 // Don't draw title screen in debug mode to same ROM for text rendering
		menuBallVelo += 0.15f;

		if (menuBallY >= 32)
		{
			menuBallVelo = fabsf(menuBallVelo) * -0.94f;
		}
		
		menuBallY += menuBallVelo;
#endif

		// Draw the menu		
		if (menuSelection == 1)
		{
			arduboy.drawBitmap(15, 47, playButton, 31, 14, 1);
			arduboy.drawBitmap(82, 49, configButton, 31, 10, 1);
		}
		else
		{
			arduboy.drawBitmap(15, 49, playButton, 31, 10, 1);
			arduboy.drawBitmap(82, 47, configButton, 31, 14, 1);
		}

#if DEBUG == 0 // Don't draw title screen in debug mode to same ROM for text rendering
		arduboy.drawBitmap(0, 0, titleScreen, 128, 64, 1);
		arduboy.drawBitmap(29, menuBallY, menuBall, 16, 16, 1);
#endif
	}
	// Gameplay Update
	else if (gameState == 2)
	{
		if (arduboy.pressed(UP_BUTTON))
		{
			gameState = 1;
		}

		player.update(arduboy);

		if (player.y > MAPFLOOR)
		{
			// Play death sound
			arduboy.tunes.tone(700, 100);

			// Respawn the player as they have died
			player.respawn(spawnX, spawnY);
		}
		else if (player.y < MAPCEILING && !(currentLevel == 8 || currentLevel == 11))
		{
			// Play death sound
			arduboy.tunes.tone(700, 100);

			// Respawn the player as they have died
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
				if (player.x >= currentMapData[i].x
					&& player.x <= currentMapData[i].x + currentMapData[i].w
					&& player.y + 3 >= currentMapData[i].y
					&& player.y + 3 <= currentMapData[i].y + currentMapData[i].h)
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
								spawnY = currentMapData[i].y - 8;
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
					if (currentMapData[i].type == 2)
					{
						gameState = 3;
						spawnY = 2;
					}
					else if (currentMapData[i].type == 8)
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
					if (currentMapData[i].type == 1 || currentMapData[i].type == 11 || currentMapData[i].type == 15 || currentMapData[i].type == 16)
					{
						// Play death sound
						arduboy.tunes.tone(1000, 100);

						// Respawn the player as they have died
						player.respawn(spawnX, spawnY);

						// Delay this frame for a bit so player can see they hit a spike
						delay(200);
					}
				}
			}
		}

		camX = camX + 0.08f * ((player.x - 64) - camX);
		if (player.gravity > 0)
		{
			camY = camY + 0.08f * ((player.y - 32) - camY);
		}
		else
		{
			camY = camY + 0.08f * ((player.y - 48) - camY);
		}
	}
	// End level portal animation Update
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

			// If the save file has unlocked a level lower than the level just reached
			if (EEPROM.read(450) < currentLevel && currentLevel <= TOTALNUMBEROFLEVELS)
			{
				// Write the new level
				EEPROM.write(450, currentLevel);
				levelUnlocked = currentLevel;
			}

			//currentLevel++;
			//player.respawn(spawnX, spawnY);

			
		}
		arduboy.tunes.tone(5000, 10);
	}
	// Options Menu
	else if (gameState == 4)
	{
		arduboy.setCursor(0, 0);
		arduboy.print(F("Options Menu\n\n"));

		arduboy.print(F("  Audio: "));
		if (arduboy.audio.enabled())
		{
			arduboy.print(F("ON"));
		}
		else
		{
			arduboy.print(F("OFF"));
		}

		arduboy.print(F("\n  Level Select"));
		arduboy.print(F("\n  Delete save file"));

		if (arduboy.pressed(A_BUTTON))
		{
			if (!selectionChanged)
			{
				switch (menuSelection)
				{
					case 0:
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
						break;
					case 1:
						gameState++;
						break;
					case 2:
						EEPROM.write(450, 1);
						levelUnlocked = 1;
						arduboy.print(F("\n\n  Save file deleted!"));
						arduboy.display();
						delay(2000);
						break;
				}
				

				selectionChanged = true;
			}
		}
		else if (arduboy.pressed(B_BUTTON))
		{
			if (!selectionChanged)
			{
				gameState = 1;

				selectionChanged = true;
			}
		}
		else if (arduboy.pressed(UP_BUTTON))
		{
			if (!selectionChanged)
			{
				menuSelection--;
				selectionChanged = true;

				if (menuSelection >= 200)
				{
					menuSelection = 0;
				}
			}
		}
		else if (arduboy.pressed(DOWN_BUTTON))
		{
			if (!selectionChanged)
			{
				menuSelection++;
				selectionChanged = true;

				if (menuSelection > 2)
				{
					menuSelection = 2;
				}
			}
		}
		else
		{
			selectionChanged = false;
		}

		//arduboy.drawChar(16, 16, '<', 1, 0, 1);
		arduboy.drawFastHLine(0, 19 + (menuSelection * 8), 8, 1);

		arduboy.print(F("\n\n  UP/DOWN=Choose"));
		arduboy.print(F("\n  A=Select B=Back"));
	}
	// Level Select
	else if (gameState == 5)
	{
		arduboy.setCursor(0, 0);
		arduboy.print(F("Level Select\n\n"));
		arduboy.print(F(" Choose level to play\n\n"));

		if (arduboy.pressed(UP_BUTTON))
		{
			if (!selectionChanged)
			{
				menuSelection++;
				selectionChanged = true;

				if (menuSelection > levelUnlocked)
				{
					menuSelection = levelUnlocked;
				}
			}
		}
		else if (arduboy.pressed(DOWN_BUTTON))
		{
			if (!selectionChanged)
			{
				menuSelection--;
				selectionChanged = true;

				if (menuSelection < 1)
				{
					menuSelection = 1;
				}
			}
		}
		else if (arduboy.pressed(A_BUTTON))
		{
			if (!selectionChanged)
			{
				LoadLevel(menuSelection);
				gameState = 2;

				selectionChanged = true;
				menuSelection = 0;
			}
		}
		else if (arduboy.pressed(B_BUTTON))
		{
			if (!selectionChanged)
			{
				gameState--;
				menuSelection = 1;

				selectionChanged = true;
			}
		}
		else
		{
			selectionChanged = false;
		}

		arduboy.print("  Level: ");
		arduboy.print(menuSelection);

		arduboy.print(F("\n\n  UP/DOWN=Choose"));
		arduboy.print(F("\n  A=Select B=Back"));
	}

	// Gameplay/End level portal animation Draw
	if (gameState == 2 || gameState == 3)
	{
#if DEBUG == 1
		arduboy.setCursor(0, 0);
		arduboy.print(arduboy.cpuLoad());
		arduboy.print(" ");
		arduboy.print(player.x);
		arduboy.print(" ");
		arduboy.print(player.y);
#endif

		for (byte i = 0; i < currentLevelArraySize; i++)
		{
			//arduboy.fillRect(currentMapData[i].x - camX, currentMapData[i].y - camY, currentMapData[i].w, currentMapData[i].h, 1);
			switch (currentMapData[i].type)
			{
			default:
				arduboy.drawRect(currentMapData[i].x - camX, currentMapData[i].y - camY, currentMapData[i].w, currentMapData[i].h, 1);
				break;
			case 1: // Spike
				arduboy.drawTriangle(currentMapData[i].x - camX - 4, currentMapData[i].y + currentMapData[i].h - camY, 
					currentMapData[i].x + (currentMapData[i].w / 2) - camX - 1, currentMapData[i].y - camY - 3,
					currentMapData[i].x + currentMapData[i].w - camX + 2, currentMapData[i].y + currentMapData[i].h - camY, 1);

#if DEBUG == 1
				arduboy.drawRect(currentMapData[i].x - camX, currentMapData[i].y - camY, currentMapData[i].w, currentMapData[i].h, 1);
#endif
				break;
			case 2: // Next Level
				//arduboy.drawRoundRect(currentMapData[i].x - camX, currentMapData[i].y - camY, currentMapData[i].w, currentMapData[i].h, 5, 1);
				arduboy.drawRect(currentMapData[i].x - camX, currentMapData[i].y - camY, currentMapData[i].w, currentMapData[i].h, 1);
				arduboy.drawFastVLine(random(currentMapData[i].x - camX, currentMapData[i].x - camX + currentMapData[i].w), currentMapData[i].y - camY, currentMapData[i].h, 1);
				break;
			case 3:
				arduboy.drawRect(currentMapData[i].x - camX, currentMapData[i].y - camY, 2, currentMapData[i].h, 1);
				if (spawnX == currentMapData[i].x)
				{
					arduboy.drawRect(currentMapData[i].x - camX + 2, currentMapData[i].y - camY, 8, 5, 1);
				}

#if DEBUG == 1
				arduboy.drawRect(currentMapData[i].x - camX, currentMapData[i].y - camY, currentMapData[i].w, currentMapData[i].h, 1);
#endif
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
				arduboy.drawTriangle(currentMapData[i].x - camX - 4, currentMapData[i].y - camY - 1,
					currentMapData[i].x + (currentMapData[i].w / 2) - camX - 1, currentMapData[i].y + currentMapData[i].h - camY + 2,
					currentMapData[i].x + currentMapData[i].w - camX + 2, currentMapData[i].y - camY - 1, 1);

#if DEBUG == 1
				arduboy.drawRect(currentMapData[i].x - camX, currentMapData[i].y - camY, currentMapData[i].w, currentMapData[i].h, 1);
#endif
				break;
			case 15: // 5 Spikes
				for (byte z = 0; z < 5; z++)
				{
					arduboy.drawTriangle(currentMapData[i].x - camX - 4 + (z * 10), currentMapData[i].y + currentMapData[i].h - camY,
						currentMapData[i].x + 1 - camX + (z * 10), currentMapData[i].y - camY - 2,
						currentMapData[i].x + 6 - camX + (z * 10), currentMapData[i].y + currentMapData[i].h - camY, 1);
				}
#if DEBUG == 1
				arduboy.drawRect(currentMapData[i].x - camX, currentMapData[i].y - camY, currentMapData[i].w, currentMapData[i].h, 1);
#endif

				break;
			case 16: // 5 Upsidedown Spikes
				for (byte z = 0; z < 5; z++)
				{
					arduboy.drawTriangle(currentMapData[i].x - camX - 3 + (z * 10), currentMapData[i].y - camY,
						currentMapData[i].x + 2 - camX + (z * 10), currentMapData[i].y + currentMapData[i].h - camY + 2,
						currentMapData[i].x + 7 - camX + (z * 10), currentMapData[i].y - camY, 1);
				}
#if DEBUG == 1
				arduboy.drawRect(currentMapData[i].x - camX, currentMapData[i].y - camY, currentMapData[i].w, currentMapData[i].h, 1);
#endif

				break;
			case 99:
				arduboy.drawBitmap(currentMapData[i].x - camX, currentMapData[i].y - camY, buttonBase, 16, 4, 1);
				break;
			case 100:
				break;
				}

				// Saves ROM if check for duplicate types outside of switch with same if statement
				if (currentMapData[i].type == 4 || currentMapData[i].type == 5)
				{
					arduboy.drawRoundRect(currentMapData[i].x - camX, currentMapData[i].y - camY, currentMapData[i].w, currentMapData[i].h, 5, 1);

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

#if DEBUG == 0 // Saving ROM for debug mode

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
#endif

				if (gameState == 2)
				{
#if DEBUG == 1 // Draw player hitboxes
					arduboy.drawPixel(player.x - camX, player.y + 3 - camY, 1);
					arduboy.drawPixel(player.x - camX, player.y - 3 - camY, 1);
					arduboy.drawPixel(player.x + 3 - camX, player.y - camY, 1);
					arduboy.drawPixel(player.x - 3 - camX, player.y - camY, 1);
#endif

					arduboy.fillCircle(player.x - camX, player.y - camY, 1, 1);
		}
				else
				{
					//arduboy.drawFastVLine(player.x - camX, player.y - camY, spawnY, 1);
					arduboy.drawRect(player.x - camX, player.y - camY, 2, spawnY, 1);
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
	case 8:
		for (i = 0; i < LEVEL8ARRAYSIZE; i++)
		{
			memcpy_P(&currentMapData[i], &level8[i], sizeof(level8[i]));
		}
		break;
	case 9:
		for (i = 0; i < LEVEL9ARRAYSIZE; i++)
		{
			memcpy_P(&currentMapData[i], &level9[i], sizeof(level9[i]));
		}
		break;
	case 10:
		for (i = 0; i < LEVEL10ARRAYSIZE; i++)
		{
			memcpy_P(&currentMapData[i], &level10[i], sizeof(level10[i]));
		}
		break;
	case 11:
		for (i = 0; i < LEVEL11ARRAYSIZE; i++)
		{
			memcpy_P(&currentMapData[i], &level11[i], sizeof(level11[i]));
		}
		break;
	case 12:
		for (i = 0; i < LEVEL12ARRAYSIZE; i++)
		{
			memcpy_P(&currentMapData[i], &level12[i], sizeof(level12[i]));
		}
		break;
	case 13:
		for (i = 0; i < LEVEL13ARRAYSIZE; i++)
		{
			memcpy_P(&currentMapData[i], &level13[i], sizeof(level13[i]));
		}
		break;
	}

	currentLevelArraySize = i;
	currentLevel = levelNumber;
	spawnX = DEFAULTSPAWNX;
	spawnY = DEFAULTSPAWNY;
	player.gravity = DEFAULTGRAVITY;

	player.respawn(spawnX, spawnY);
}
