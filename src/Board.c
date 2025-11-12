#include "../include/Board.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/Cursor.h"
#include "../include/Menu.h"
#include "../include/Tile.h"
#include "../include/debugmalloc.h"

Board* create_board(Options options) {
  Board* b = malloc(sizeof(Board));
  b->options = options;
  b->remaining_tiles = options.M * options.N;
  b->flagged_tiles = 0;
  b->tiles = malloc(sizeof(Tile*) * options.N);
  for (int i = 0; i < options.N; i++) {
    b->tiles[i] = malloc(sizeof(Tile) * options.M);
  }

  for (int y = 0; y < options.N; y++) {
    for (int x = 0; x < options.M; x++) {
      Tile* t = &b->tiles[y][x];
      t->value = 0;
      t->is_flagged = false;
      t->is_revealed = false;

      int ni = 0;
      for (int offy = -1; offy <= 1; offy++) {
        for (int offx = -1; offx <= 1; offx++) {
          if (offy == 0 && offx == 0)
            continue;
          int ny = y + offy;
          int nx = x + offx;
          if (ny < 0 || ny >= options.N || nx < 0 || nx >= options.M) {
            t->neighbors[ni++] = NULL;
          } else {
            t->neighbors[ni++] = &b->tiles[ny][nx];
          }
        }
      }
    }
  }

  return b;
}

void fill_board(Board* board, int first_tile[2]) {
  int total = board->options.N * board->options.M;
  int* available = (int*)malloc(total * sizeof(int));
  for (int i = 0; i < total; i++)
    available[i] = i;

  available[board->options.M * first_tile[1] + first_tile[0]] = available[total - 1];

  srand(time(0));

  for (int i = 0; i < board->options.mine_count; i++) {
    int remaining = total - i;
    int idx = rand() % remaining;
    int chosen = available[idx];
    available[idx] = available[remaining - 1];

    int row = chosen / board->options.M;
    int col = chosen % board->options.M;
    board->tiles[row][col].value = 9;

    for (int n = 0; n < 8; n++) {
      Tile* neighbor = board->tiles[row][col].neighbors[n];
      if (neighbor && neighbor->value != 9)
        neighbor->value++;
    }
  }
  free(available);
}

void destroy_board(Board* board) {
  for (int i = 0; i < board->options.N; ++i) {
    free(board->tiles[i]);
  }
  free(board->tiles);
  board->tiles = NULL;
  free(board);
}

bool draw_board(Board* board, Cursor cursor) {
  Tile *tile_under_cursor = &board->tiles[cursor.y][cursor.x];
  bool is_mine_revealed = tile_under_cursor->value == 9 && tile_under_cursor->is_revealed;

  printf(RESTOREPOS);
  printf("Remaining mines: %02d\n", board->options.mine_count - board->flagged_tiles);
  for (int i = 0; i < board->options.N; i++) {
    for (int j = 0; j < board->options.M; j++) {
      char out[] = "  ";
      int bg = NO_COLOR, fg = NO_COLOR;
      Tile current_tile = board->tiles[i][j];

      if (!current_tile.is_revealed) {

        if (is_mine_revealed && current_tile.value == 9) {
          out[0] = 'X';
          bg = MINE;
        } else {
          out[0] = '#';
          bg = UNREVEALED;
          fg = NO_COLOR;
        }
      } else {
        out[0] = '0' + current_tile.value;
        fg = fgcolors[current_tile.value];

        if (current_tile.value == 0) {
          out[0] = '.';
        }

        if (current_tile.value == 9) {
          out[0] = 'X';
          bg = MINE;
        }
      }

      if (i == cursor.y && j == cursor.x)
        bg = bg == MINE ? MINE : USER;

      if (board->tiles[i][j].is_flagged) {
        out[0] = 'f';
        fg = FLAGGED;
      }

      color_printf(out, bg, fg);
    }
    printf("\n");
  }
  return is_mine_revealed;
}