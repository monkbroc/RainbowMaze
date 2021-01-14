/*
 * Project RainbowMaze
 * Description:
 * Inspired from http://compform.net/index_mess.js
 * Author:
 * Date:
 */

#include <vector>
#include <array>
#include <algorithm>
#include "RGBmatrixPanel.h"

SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

const int16_t SIZE = 32;
const uint16_t DOT_DELAY = 50;
const uint16_t DONE_DELAY = 10*1000;
const uint16_t HUE_CHANGE = 7;
const uint16_t MAX_HUE = 1536;
const uint8_t SATURATION = 223;
const uint8_t VALUE = 255;


struct CellInfo {
  uint16_t hue;
  int8_t x;
  int8_t y;
};

std::vector<CellInfo> path;

CellInfo currentCell = { 0 };

bool grid[SIZE][SIZE] = { false };

// RGB shield
	#define CLK	D6
	#define OE	D7
	#define LAT	TX
	#define A  	A0
	#define B  	A1
	#define C  	A2
	#define D	RX
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

void colorCell(CellInfo cell);

void setup() {
  setupRandom();
  setupHardware();
  clearPanel();
  emptyGrid();
}

void setupRandom() {
  uint16_t seed;
  EEPROM.get(0, seed);
  randomSeed(seed);
  seed = random();
  EEPROM.put(0, seed);
}

void emptyGrid() {
  currentCell = {
    hue: (uint16_t) (random() % MAX_HUE),
    x: (int8_t) (random() % SIZE),
    y: (int8_t) (random() % SIZE)
  };

  for (auto i = 0; i < SIZE; i++) {
    for (auto j = 0; j < SIZE; j++) {
      grid[i][j] = false;
    }
  }
}

void loop() {
  step();
}

void step() {
  // try to find open direction

  enum { LEFT, RIGHT, UP, DOWN };
  // bias directions towards left
  std::array<int,5> directions { LEFT, LEFT, RIGHT, UP, DOWN };

  std::random_shuffle(directions.begin(), directions.end());

  bool foundEmpty = false;
  int8_t x, y;
  for (auto it = directions.begin(); it != directions.end(); ++it) {
    auto direction = *it;
    x = currentCell.x;
    y = currentCell.y;

    switch (direction) {
      case LEFT: x--; break;
      case RIGHT: x++; break;
      case UP: y--; break;
      case DOWN: y++; break;
    }

    if (x < 0 || x > SIZE - 1 || y < 0 || y > SIZE - 1) {
      continue;
    }

    if (!grid[x][y]) {
      foundEmpty = true;
      break;
    }
  }

  // if we found a cell, move forth, otherwise move back
  if (foundEmpty) {
    currentCell.hue += HUE_CHANGE;
    currentCell.hue %= MAX_HUE;
    currentCell.x = x;
    currentCell.y = y;

    path.push_back(currentCell);

    grid[x][y] = true;

    colorCell(currentCell);
    
    delay(DOT_DELAY);
  } else {
    if (path.empty()) {
      // done!
      emptyGrid();
      delay(DONE_DELAY);
      clearPanel();
    } else {
      currentCell = path.back();
      path.pop_back();
    }
  }
}

void setupHardware() {
  matrix.begin();
}

void clearPanel() {
  matrix.fillScreen(0);
  matrix.updateDisplay();
}

void colorCell(CellInfo cell) {
  auto color = matrix.ColorHSV(cell.hue, SATURATION, VALUE, true);
  matrix.drawPixel(cell.x, cell.y, color);
  matrix.updateDisplay();
}