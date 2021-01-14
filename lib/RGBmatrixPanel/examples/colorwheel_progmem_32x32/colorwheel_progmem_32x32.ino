// colorwheel_progmem demo for Adafruit RGBmatrixPanel library.
// Renders a nice circle of hues on our 32x32 RGB LED matrix:
// http://www.adafruit.com/products/607

// This version uses precomputed image data stored in PROGMEM
// rather than calculating each pixel.  Nearly instantaneous!  Woo!

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.


#include "Adafruit_mfGFX.h"   // Core graphics library
#include "RGBmatrixPanel.h" // Hardware-specific library
#include "math.h"

// Modify for version of RGBShieldMatrix that you have
// HINT: Maker Faire 2016 Kit and later have shield version 4 (3 prior to that)
//
// NOTE: Version 4 of the RGBMatrix Shield only works with Photon and Electron (not Core)
#define RGBSHIELDVERSION		4

/** Define RGB matrix panel GPIO pins **/
#if (RGBSHIELDVERSION == 4)		// Newest shield with SD socket onboard
	#warning "new shield"
	#define CLK	D6
	#define OE	D7
	#define LAT	TX
	#define A  	A0
	#define B  	A1
	#define C  	A2
	#define D	RX
#else
	#warning "old shield"
	#define CLK	D6
	#define OE 	D7
	#define LAT	A4
	#define A  	A0
	#define B  	A1
	#define C  	A2
	#define D	A3
#endif
/****************************************/

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

// Generated by colorwheel_32x32 and matrix.dumpMatrix()
const uint8_t img[] = {
  0xC2,0xC2,0xC2,0xC2,0xC2,0xC2,0xC2,0xE2,
  0xE2,0xC2,0xC2,0xE2,0xC2,0xE2,0xE2,0xCE,
  0xAF,0x65,0xE4,0x26,0xE2,0xA1,0x20,0xE3,
  0xE0,0xA1,0x23,0x23,0x20,0x20,0x20,0x20,
  0xC0,0xC0,0xC0,0xC0,0xC2,0xC2,0xC2,0xC0,
  0xC2,0xE0,0xE2,0xE0,0xC8,0xC0,0xCA,0xEA,
  0xEA,0xAA,0x22,0x2A,0xE2,0xE2,0xE2,0x22,
  0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,
  0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
  0xC0,0xC0,0xC0,0xC2,0xE0,0xEB,0xE9,0xEA,
  0xEB,0xE9,0xEB,0xE0,0x23,0x20,0x20,0x20,
  0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
  0x40,0x82,0x82,0x82,0x82,0x82,0x82,0xA2,
  0xA2,0x82,0x8A,0xAA,0xAA,0x8A,0xEF,0xCF,
  0xEB,0xE8,0x2D,0xED,0x68,0xAF,0x26,0x61,
  0xE2,0xA1,0xA1,0x22,0x22,0x20,0x20,0x00,
  0x80,0xC0,0xC0,0xC0,0xC0,0xC2,0xC2,0xC0,
  0xC2,0xE8,0xEA,0xE8,0xEA,0xCA,0x88,0xA8,
  0xAC,0xAE,0xAE,0x6E,0x6A,0xEA,0xEA,0xA2,
  0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x20,
  0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
  0xC0,0xC0,0xCA,0xCA,0xCB,0xEB,0xEA,0xEB,
  0xEA,0xEB,0xEA,0xAB,0xAE,0x2E,0x21,0x20,
  0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
  0x42,0xC2,0xC2,0xC2,0xC2,0xC2,0xC2,0xEA,
  0xEA,0xEA,0xCA,0xCA,0xEA,0x8F,0x8F,0xEE,
  0xCA,0xAB,0x2E,0xEB,0x2B,0x2C,0xE9,0x6F,
  0x6C,0xA3,0xA1,0x22,0x22,0x22,0x20,0x00,
  0x40,0x80,0x80,0x80,0x80,0x82,0x82,0x80,
  0x8A,0x8A,0xA8,0xAA,0xAA,0x88,0x8A,0x8A,
  0xAE,0xAE,0xAE,0x6A,0x6A,0x6A,0xAE,0xAE,
  0xA2,0x22,0x22,0x22,0x22,0x22,0x22,0x02,
  0x80,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC2,
  0xCA,0xCA,0xCA,0xCB,0xCB,0xEA,0xEA,0xEB,
  0xEA,0xEB,0xEA,0xAE,0xAF,0xAF,0x2F,0x2F,
  0x23,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
  0x40,0x82,0x82,0x82,0x82,0x82,0x82,0xAA,
  0xAA,0xAA,0x8A,0x8A,0xAA,0xEF,0xCF,0xAA,
  0x8A,0xEF,0xED,0x68,0xAD,0x2A,0xEF,0xEC,
  0x66,0x29,0xA3,0xA0,0x22,0x22,0x20,0x00,
  0x80,0x80,0x80,0x80,0x80,0x82,0x82,0x88,
  0x88,0x8A,0xA8,0xAA,0xA8,0xEA,0xC8,0x8C,
  0xAC,0xEC,0xEE,0xEA,0x6A,0x6E,0xAE,0xAE,
  0xAE,0xAA,0x22,0x22,0x22,0x22,0x22,0x20,
  0x00,0xC0,0xC0,0xC0,0xC0,0xC0,0xCA,0xCA,
  0xCA,0xCA,0xCA,0xCB,0xCB,0x8A,0xAB,0xEA,
  0xEB,0xAA,0xAB,0xAF,0xAE,0xAE,0x2E,0x2F,
  0x2F,0x25,0x20,0x20,0x20,0x20,0x20,0x00,
  0x03,0xC3,0xC3,0xC3,0xC3,0xC3,0xCA,0xCA,
  0xEA,0xEA,0xEA,0xCA,0xCA,0xAF,0xEE,0xCA,
  0xEA,0xCE,0xAB,0x2F,0xAE,0xE9,0x6D,0xE6,
  0xA5,0x2D,0xAB,0xA2,0xA0,0x22,0x22,0x00,
  0x00,0xC0,0xC0,0xC0,0xC0,0xCA,0xCA,0xCA,
  0xC8,0xCA,0xCA,0xE8,0xEA,0xE8,0xEA,0xCF,
  0xCF,0xEE,0xEA,0xEA,0x6A,0x2E,0x2E,0xAE,
  0xAE,0xA6,0x2E,0x22,0x22,0x22,0x22,0x02,
  0x00,0x80,0x80,0x80,0x80,0x88,0x8A,0x8A,
  0x8A,0x8A,0x8A,0x8B,0x8B,0x8A,0x8B,0xAA,
  0xAB,0xAB,0xAE,0xAE,0xAF,0xAF,0xAF,0x2F,
  0x2D,0x2D,0x26,0x20,0x20,0x20,0x20,0x00,
  0x00,0x83,0x83,0x83,0x83,0x8B,0x8B,0x8B,
  0xAB,0xAB,0xAB,0xAA,0x8E,0x8E,0xAB,0x8B,
  0xAF,0x8F,0xAA,0xAC,0x6B,0xEF,0x6E,0x64,
  0xAD,0x27,0x24,0xA2,0xA0,0xA0,0x22,0x00,
  0x00,0xC0,0xC0,0xC0,0xC9,0xC9,0xCB,0xCB,
  0xC8,0xC8,0xCA,0xCB,0xE9,0xEB,0xEF,0xCD,
  0xCD,0xED,0xE9,0xEB,0xAF,0x2E,0x2E,0x2E,
  0xA6,0xA6,0xA6,0x2E,0x22,0x22,0x22,0x00,
  0x00,0x80,0x80,0x80,0x88,0x8A,0x8A,0x8A,
  0x8A,0x8A,0x8B,0x8B,0x8A,0x8B,0x8A,0xAB,
  0xAA,0xAB,0xAF,0xAE,0xAE,0xAE,0xAD,0xAD,
  0x2F,0x2F,0x2D,0x26,0x20,0x20,0x20,0x00,
  0x00,0x01,0x82,0x82,0x8A,0x8A,0x8A,0x8A,
  0x8A,0xEB,0xEB,0xEB,0xEF,0xCF,0xAA,0x8A,
  0x8E,0xAA,0xCF,0xEF,0xE9,0x6C,0xE4,0x2F,
  0xAF,0xA5,0x2E,0x2C,0xAA,0xA0,0x00,0x00,
  0x00,0x80,0xC0,0xC1,0xC9,0xC9,0xCB,0xCB,
  0xCB,0x89,0x89,0x8B,0x8B,0xA9,0xED,0xCD,
  0xCF,0xCB,0xAB,0xAB,0xAF,0xAF,0x2F,0x26,
  0xA6,0xA6,0xAE,0xAE,0x22,0x22,0x20,0x00,
  0x00,0x00,0x80,0x8A,0x8A,0x8A,0x8A,0x8A,
  0x8A,0x8B,0x8B,0x8B,0x8A,0x8B,0x8A,0xAB,
  0xAB,0xAE,0xAE,0xAF,0xAF,0xAF,0xAF,0xAF,
  0x2D,0x2D,0x27,0x25,0x27,0x20,0x00,0x00,
  0x00,0x00,0xCB,0xDB,0xDB,0xDB,0xDB,0xDB,
  0xDA,0xCA,0xEA,0xEE,0xFE,0xDF,0xDB,0xFF,
  0xDF,0xFB,0xDF,0xDA,0xEE,0x6E,0xA7,0x2F,
  0x25,0xAE,0x2E,0x24,0xA6,0xA4,0x00,0x00,
  0x00,0x00,0x80,0x88,0x88,0x88,0x88,0x8A,
  0x8A,0x8B,0x89,0x89,0x8A,0xA8,0xAE,0xAE,
  0x8C,0x88,0xA8,0xAE,0xAF,0xAF,0x2F,0x27,
  0x26,0xAE,0xAE,0xAE,0x2E,0x22,0x00,0x00,
  0x00,0x00,0x82,0x8A,0x8A,0x8A,0x8A,0x8A,
  0x8B,0x8B,0x8B,0x8A,0x8A,0x8B,0x8B,0x8A,
  0xAB,0xAF,0xAF,0xAE,0xAE,0xAD,0xAD,0xAD,
  0xAF,0x27,0x25,0x27,0x25,0x23,0x00,0x00,
  0x00,0x00,0x9A,0xDA,0xDA,0xDA,0xDA,0xDA,
  0xDA,0x9B,0x9F,0xBF,0xFE,0xFA,0xDA,0xFE,
  0xFA,0xDE,0xFA,0xDA,0xBF,0xB5,0x2D,0xA5,
  0x26,0xAE,0xA4,0x26,0x2C,0x2E,0x00,0x00,
  0x00,0x00,0x09,0x89,0x89,0x89,0x89,0x89,
  0x8B,0x8A,0x8A,0x88,0x88,0x8F,0xAF,0xAD,
  0xAB,0x8B,0x8F,0xAC,0xAC,0xAE,0xA7,0x27,
  0x27,0xAE,0xAE,0xAE,0xA6,0x06,0x00,0x00,
  0x00,0x00,0x0A,0x8A,0x8A,0x8A,0x8A,0x8B,
  0x8B,0x8B,0x8A,0x8A,0x8B,0x8A,0x8B,0x8B,
  0x8E,0xAE,0xAE,0xAF,0xAF,0xAF,0xAF,0xAF,
  0xAD,0x27,0x27,0x25,0x27,0x05,0x00,0x00,
  0x00,0x00,0x08,0x0B,0x8B,0x8B,0x8B,0x8B,
  0x8B,0x9F,0x9F,0x9F,0xBF,0xBB,0x8F,0x8B,
  0xAB,0x8F,0xBB,0xBF,0x9F,0xB7,0x3F,0xA6,
  0xAC,0x2C,0xA6,0xA4,0x8E,0x0C,0x00,0x00,
  0x00,0x09,0x18,0x18,0x98,0x98,0x98,0x98,
  0x98,0x8B,0x8B,0x8B,0x89,0x8F,0xBC,0xBA,
  0xBA,0x98,0x8D,0x8F,0xAF,0xAE,0xA6,0x27,
  0x2F,0x2F,0xAE,0xAE,0x06,0x04,0x04,0x00,
  0x00,0x00,0x0A,0x8A,0x8A,0x8A,0x8B,0x8B,
  0x8B,0x8A,0x8A,0x8B,0x8B,0x8A,0x8A,0x8E,
  0x8F,0xAF,0xAF,0xAF,0xAD,0xAD,0xAD,0xAF,
  0xA7,0xA5,0x27,0x25,0x27,0x05,0x00,0x00,
  0x00,0x08,0x08,0x08,0x09,0x8B,0x8B,0x8B,
  0x8E,0x8E,0x8E,0x8F,0xAB,0xAB,0x8F,0x8B,
  0xAF,0xAB,0x8F,0xAF,0x97,0xBE,0xB4,0x34,
  0xAE,0x26,0x24,0x0E,0x0C,0x0C,0x04,0x00,
  0x00,0x19,0x19,0x19,0x99,0x99,0x99,0x99,
  0x99,0x99,0x9B,0x9A,0x9C,0x9E,0xBD,0xBB,
  0xB9,0xBF,0x9E,0x9C,0xAD,0xA5,0xA6,0xA6,
  0x2F,0x2F,0x2E,0xA4,0x04,0x04,0x04,0x00,
  0x00,0x0A,0x0A,0x0A,0x8A,0x8A,0x8B,0x8B,
  0x8A,0x8A,0x8B,0x8B,0x8A,0x8B,0x8B,0x8E,
  0x8E,0x8E,0xAE,0xAD,0xAF,0xAF,0xAF,0xAD,
  0xA5,0xA7,0xA5,0x27,0x05,0x05,0x07,0x00,
  0x00,0x18,0x18,0x18,0x18,0x18,0x9A,0x9A,
  0x9E,0x9E,0x9E,0x9A,0x9A,0xAE,0xBE,0x9B,
  0x9F,0xBA,0x8E,0xA6,0xAE,0x9E,0xB6,0x3E,
  0x2C,0xA4,0x8E,0x0C,0x0C,0x04,0x04,0x00,
  0x01,0x19,0x19,0x19,0x19,0x99,0x98,0x98,
  0x98,0x98,0x98,0x9E,0x9E,0x9D,0x9E,0xB8,
  0xBA,0xBE,0x9D,0x9D,0x96,0xA7,0xA7,0xAE,
  0xAF,0x2F,0xA5,0x04,0x04,0x04,0x04,0x00,
  0x02,0x0A,0x0A,0x0A,0x0A,0x8B,0x8B,0x8B,
  0x8A,0x8B,0x8B,0x8A,0x8B,0x8A,0x8B,0x8F,
  0x8F,0x8F,0xAF,0xAF,0xAF,0xAD,0xAD,0xA7,
  0xA5,0xA5,0x27,0x07,0x05,0x07,0x07,0x01,
  0x10,0x08,0x08,0x08,0x08,0x08,0x0A,0x8E,
  0x8E,0x8E,0x8A,0x8A,0x8E,0xBE,0xBA,0x8E,
  0x8A,0xBE,0xBE,0x96,0xAE,0x86,0xBE,0xBE,
  0x36,0x84,0x0C,0x0C,0x04,0x04,0x04,0x00,
  0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x88,
  0x88,0x88,0x8C,0x8E,0x8E,0x9D,0x9B,0xA8,
  0xAE,0xBD,0xBF,0x9E,0x95,0xB4,0xAD,0xAE,
  0xAE,0x8F,0x05,0x04,0x04,0x04,0x04,0x04,
  0x00,0x1A,0x1A,0x1A,0x1A,0x1B,0x9B,0x9A,
  0x9A,0x9B,0x9A,0x9B,0x9A,0x8B,0x8E,0x9E,
  0x9E,0x8E,0x8D,0xAD,0xAD,0xAF,0xA7,0xA5,
  0xA7,0x25,0x07,0x05,0x07,0x07,0x05,0x00,
  0x10,0x18,0x18,0x18,0x18,0x18,0x18,0x9E,
  0x9E,0x9E,0x9A,0x9A,0x9E,0xAA,0xAA,0xBE,
  0x9A,0x8E,0xA6,0x9E,0x86,0xA6,0x9E,0xB6,
  0xB6,0x0C,0x0C,0x04,0x04,0x04,0x04,0x00,
  0x10,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
  0x88,0x88,0x8C,0x8E,0x8E,0x89,0x89,0x8A,
  0xAC,0xAF,0xAC,0x95,0x97,0x96,0xAF,0xAF,
  0x0E,0x05,0x05,0x04,0x04,0x04,0x04,0x00,
  0x0A,0x1A,0x1A,0x1A,0x1A,0x1B,0x1B,0x1A,
  0x9B,0x9B,0x9A,0x9B,0x9B,0x9E,0x9F,0x9F,
  0x9F,0x9F,0x9F,0xAF,0xAF,0xAD,0xA5,0xA7,
  0x05,0x07,0x05,0x07,0x07,0x07,0x05,0x05,
  0x10,0x08,0x08,0x08,0x08,0x08,0x08,0x0C,
  0x0C,0x08,0x8A,0x8E,0x8E,0x8A,0xBE,0xBA,
  0x9E,0x9E,0xA6,0xBE,0x96,0xAE,0x24,0x14,
  0x1C,0x0C,0x0C,0x04,0x04,0x04,0x04,0x00,
  0x08,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
  0x18,0x9C,0x9C,0x9C,0x9E,0x9A,0x89,0x8F,
  0xAD,0xAE,0xAD,0xB7,0x94,0x9D,0x9E,0x0D,
  0x04,0x05,0x05,0x04,0x04,0x04,0x04,0x04,
  0x18,0x1A,0x1A,0x1A,0x1A,0x1B,0x1B,0x1A,
  0x1B,0x1A,0x9B,0x9A,0x9B,0x9F,0x9E,0x9E,
  0x9E,0x9D,0x9D,0x8D,0xAD,0xA7,0x07,0x05,
  0x07,0x05,0x05,0x07,0x07,0x05,0x05,0x04,
  0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x1C,
  0x1C,0x18,0x18,0x1E,0x18,0x1E,0x1C,0xBA,
  0xAE,0x34,0x3E,0x24,0x1E,0x0C,0x04,0x1C,
  0x1C,0x0C,0x04,0x04,0x04,0x04,0x04,0x04,
  0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
  0x18,0x1C,0x1C,0x1C,0x98,0x1A,0x9A,0x9C,
  0x9F,0x8F,0x06,0x84,0x1E,0x1D,0x1C,0x05,
  0x04,0x05,0x05,0x05,0x04,0x04,0x04,0x04,
  0x1A,0x1A,0x1A,0x1A,0x1B,0x1B,0x1B,0x1A,
  0x1B,0x1A,0x1B,0x1A,0x1E,0x9E,0x9F,0x9F,
  0x9F,0x9D,0x9D,0x1F,0x07,0x05,0x05,0x07,
  0x05,0x05,0x07,0x07,0x05,0x05,0x05,0x05
};


void setup() {
  int     i, len;
  uint8_t *ptr = matrix.backBuffer(); // Get address of matrix data

  // Copy image from image to matrix buffer:
  memcpy(ptr, img, sizeof(img));

  // Start up matrix AFTER data is copied.  The RGBmatrixPanel
  // interrupt code ties up about 40% of the CPU time, so starting
  // it now allows the prior drawing code to run even faster!
  matrix.begin();
}

void loop() {
  // do nothing
}
