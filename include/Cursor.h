#ifndef CURSOR_H
#define CURSOR_H

#include "Tile.h"

typedef struct {
  int x, y;
  Tile* tile;
} Cursor;

#endif