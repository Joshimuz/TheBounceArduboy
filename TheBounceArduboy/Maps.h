// Joshimuz 2016

#ifndef _MAPS_h
#define _MAPS_h

#include <Arduboy2.h>

// The struct for the objects in the level
struct MapObject
{
	short x; short y;
	byte w; byte h;
	byte type;  // 0 = block, 1 = spike(4w7h), 2 = endlevel(10w25h), 3 = checkpoint(5w20h), 4 = Portal One, 5 = Portal Two, 6 = Removal Button(16w4h), 7 = Add Button, 8 = Gravity Button
				// 11 = Upsidedown Spike(4w7h), 15 = 5 spikes(44w8h), 16 = 5 upsidedown spikes(44w8h), 17 End Game Rocket(36w53h)
				// 99 = Pressed Button, 100 = BlockToAdd, 117 = End game trigger
};

#define LEVEL1ARRAYSIZE   22
#define LEVEL2ARRAYSIZE   13
#define LEVEL3ARRAYSIZE   14
#define LEVEL4ARRAYSIZE   18
#define LEVEL5ARRAYSIZE   35
#define LEVEL6ARRAYSIZE   47
#define LEVEL7ARRAYSIZE   24
#define LEVEL8ARRAYSIZE   53
#define LEVEL9ARRAYSIZE   44
#define LEVEL10ARRAYSIZE  52
#define LEVEL11ARRAYSIZE  74
#define LEVEL12ARRAYSIZE  74
#define LEVEL13ARRAYSIZE  87
#define LEVEL14ARRAYSIZE  32
#define LARGESTARRAYSIZE  87

#define TOTALNUMBEROFLEVELS 14

extern const MapObject level1[LEVEL1ARRAYSIZE];
extern const MapObject level2[LEVEL2ARRAYSIZE];
extern const MapObject level3[LEVEL3ARRAYSIZE];
extern const MapObject level4[LEVEL4ARRAYSIZE];
extern const MapObject level5[LEVEL5ARRAYSIZE];
extern const MapObject level6[LEVEL6ARRAYSIZE];
extern const MapObject level7[LEVEL7ARRAYSIZE];
extern const MapObject level8[LEVEL8ARRAYSIZE];
extern const MapObject level9[LEVEL9ARRAYSIZE];
extern const MapObject level10[LEVEL10ARRAYSIZE];
extern const MapObject level11[LEVEL11ARRAYSIZE];
extern const MapObject level12[LEVEL12ARRAYSIZE];
extern const MapObject level13[LEVEL13ARRAYSIZE];
extern const MapObject level14[LEVEL14ARRAYSIZE];

#endif

