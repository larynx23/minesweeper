#ifndef BOARD_H
#define BOARD_H

#include "Cursor.h"
#include "Menu.h"
#include "Tile.h"

typedef struct {
  Tile** tiles;
  int remaining_tiles;
  int flagged_tiles;
  Options options;
} Board;

Board* create_board(Options options);
void fill_board(Board* board, int first_tile[2]);
void destroy_board(Board* board);
bool draw_board(Board* board, Cursor cursor);

#endif