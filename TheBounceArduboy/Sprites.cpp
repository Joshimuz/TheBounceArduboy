// Joshimuz 2016

#include "Sprites.h"

PROGMEM const unsigned char titleScreen[] =
{
	0x00, 0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
	0x04, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x18, 0x18, 0xe8, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
	0x88, 0x08, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
	0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xe0, 0x40, 0x40, 0x40, 0x80,
	0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9f,
	0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x1f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x1f, 0xe0, 0x00, 0x00,
	0x00, 0x10, 0x30, 0x51, 0x89, 0x0a, 0x0a, 0x04,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x30, 0x0f,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x80, 0xff, 0x20, 0x20, 0x20, 0x20, 0x20, 0x40,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x40,
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf8, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x01, 0x06, 0x38, 0xc0,
	0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40,
	0x40, 0x80, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x80, 0x40, 0x40, 0x40, 0x80, 0x80, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xe0, 0x18, 0x07, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
	0xe0, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xff, 0x00, 0x00, 0x00, 0xfe, 0x09, 0x08,
	0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x18,
	0x0d, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf8,
	0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x30, 0x0f,
	0x00, 0x00, 0x3e, 0xc1, 0x00, 0x00, 0x80, 0xe0,
	0x1f, 0x00, 0x00, 0x00, 0x3f, 0xc0, 0x80, 0x80,
	0x40, 0x40, 0x30, 0x0c, 0x02, 0x80, 0xf0, 0x1f,
	0x04, 0x02, 0x02, 0xfe, 0x00, 0x00, 0x3c, 0xc2,
	0x01, 0x00, 0x1e, 0x61, 0x41, 0x88, 0x88, 0x09,
	0x09, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x7e, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f,
	0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02,
	0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
	0x00, 0x06, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x01, 0x00,
	0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

};

PROGMEM const unsigned char playButton[] =
{
	0xff, 0xff, 0xff, 0xff, 0x01, 0xed, 0xed, 0xed,
	0xe1, 0xff, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff,
	0x03, 0xdd, 0xdd, 0xdd, 0x03, 0xff, 0xf1, 0xcf,
	0x3f, 0xcf, 0xf1, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xfc, 0xfd, 0xfd, 0xfd, 0xfd, 0xff, 0xfc,
	0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xfc,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

PROGMEM const unsigned char configButton[] = 
{
	0xff, 0xff, 0xff, 0xff, 0x01, 0xfd, 0xfd, 0xfd,
	0xfd, 0xff, 0x01, 0xfd, 0xfd, 0xfd, 0x01, 0xff,
	0x01, 0xfd, 0xfd, 0xfd, 0x01, 0xff, 0x01, 0xed,
	0xed, 0xed, 0xed, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xfc, 0xfd, 0xfd, 0xfd, 0xfd,
	0xff, 0xfc, 0xfd, 0xfd, 0xfd, 0xfc, 0xff, 0xfc,
	0xff, 0xff, 0xff, 0xfc, 0xff, 0xfc, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

PROGMEM const unsigned char abButtons[] = 
{
	0x80, 0xc0, 0xe0, 0x30, 0xb0, 0xb0, 0x30, 0xe0,
	0xc0, 0x80, 0x78, 0xfc, 0xfe, 0x03, 0x6b, 0x6b,
	0x87, 0xfe, 0xfc, 0x78, 0x07, 0x0f, 0x1f, 0x30,
	0x3d, 0x3d, 0x30, 0x1f, 0x0f, 0x07, 0x00, 0x00,
	0x01, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00
};
