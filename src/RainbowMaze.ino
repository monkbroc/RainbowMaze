/*
 * Project RainbowMaze
 * Description:
 * Inspired from http://compform.net/index_mess.js
 * Author:
 * Date:
 */

#include "hsv.h"
#include <vector>
#include <array>
#include <algorithm>

const int16_t SIZE = 16;
const uint16_t DOT_DELAY = 100;
const uint16_t DONE_DELAY = 10*1000;

struct CellInfo {
  uint8_t hue;
  int8_t x;
  int8_t y;
};

std::vector<CellInfo> path;

CellInfo currentCell = {
  hue: 0,
  x: 0,
  y: 0
};

bool grid[SIZE][SIZE] = { false };

void colorCell(CellInfo cell);

void setup() {
  setupRandom();
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
    hue: 0,
    x: 0,
    y: 0
  };

  for (auto i = 0; i < SIZE; i++) {
    for (auto j = 0; j < SIZE; j++) {
      grid[i][j] = false;
    }
  }

  // TODO: clear grid
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

    if (x < 0 && x > SIZE - 1 && y < 0 && y > SIZE - 1) {
      continue;
    }

    if (grid[x][y] < 0) {
      foundEmpty = true;
    }
  }

  // if we found a cell, move forth, otherwise move back
  if (foundEmpty) {
    currentCell.hue++;
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
    } else {
      path.pop_back();
    }
  }
}

void colorCell(CellInfo cell) {

}