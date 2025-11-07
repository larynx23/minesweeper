#ifndef TILE_H
#define TILE_H

#include <stdbool.h>

typedef struct Tile Tile;

struct Tile {
  int value;  // 0-8: numbers, 9: mine
  bool is_flagged;
  bool is_revealed;
  Tile* neighbors[8];
};

void reveal(Tile* tile, int* counter);
void flag(Tile* tile, int* counter);

#endif