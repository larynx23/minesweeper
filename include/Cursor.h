#ifndef CURSOR_H
#define CURSOR_H

#include "Tile.h"

// jelenlegi helyzetet tároló struktúra, a jelenlegi mezővel együtt
typedef struct {
  int x, y;
  Tile* tile;
} Cursor;

#endif