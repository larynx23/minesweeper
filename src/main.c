#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/Board.h"
#include "../include/Cursor.h"
#include "../include/Display.h"
#include "../include/File.h"
#include "../include/Menu.h"
#include "../include/Tile.h"
#include "../include/debugmalloc.h"

void start_game(Options options) {
  bool running = true;
  Board* board = create_board(options);
  Cursor cursor = {.x = 0, .y = 0, .tile = &board->tiles[0][0]};

  bool is_first = true;
  int ch;
  time_t start_time, end_time;
  time(&start_time);
  printf(RESTOREPOS);
  print_controls();
  printf(SAVEPOS);
  do {
    running = !draw_board(board, cursor);

    if (!running) {
      printf("YOU LOST");
      continue;
    }
    if (board->remaining_tiles == board->options.mine_count) {
      running = false;
      time(&end_time);
      int result = (int)(end_time - start_time);
      color_printf("YOU WON", MINE, NO_COLOR);
      printf("\nYour time is: ");
      print_formatted_time(result);
      if (board->options.difficulty == Custom) {
        printf("Your time wont be saved in custom mode.");
      } else {
        Record current;
        printf("Whats your name? : ");
        scanf("%20s", current.name);
        current.time = result;
        current.difficulty = board->options.difficulty;
        append_toplist("data/highscore.csv", current);
      }
      continue;
    }

    ch = getch();
#ifdef _WIN32
    if (ch == 224) {
      int key = getch();
      switch (key) {
        case 72:
          cursor.y = cursor.y == 0 ? options.N - 1 : (cursor.y - 1) % options.N;
          break;
        case 80:
          cursor.y = cursor.y == options.N - 1 ? 0 : (cursor.y + 1) % options.N;
          break;
        case 77:
          cursor.x = cursor.x == options.M - 1 ? 0 : (cursor.x + 1) % options.M;
          break;
        case 75:
          cursor.x = cursor.x == 0 ? options.M - 1 : (cursor.x - 1) % options.M;
          break;
      }
      cursor.tile = &board->tiles[cursor.y][cursor.x];
    }
#else
    if (ch == '\033') {
      getch();
      switch (getch()) {
        case 'A':
          cursor.y = cursor.y == 0 ? options.N - 1 : (cursor.y - 1) % options.N;
          break;
        case 'B':
          cursor.y = cursor.y == options.N - 1 ? 0 : (cursor.y + 1) % options.N;
          break;
        case 'C':
          cursor.x = cursor.x == options.M - 1 ? 0 : (cursor.x + 1) % options.M;
          break;
        case 'D':
          cursor.x = cursor.x == 0 ? options.M - 1 : (cursor.x - 1) % options.M;
          break;
      }
      cursor.tile = &board->tiles[cursor.y][cursor.x];
    }
#endif
    else {
      switch (ch) {
        case 'q':
          running = false;
          break;
        case '1':
          if (is_first) {
            is_first = false;
            fill_board(board, (int[2]){cursor.x, cursor.y});
          }
          reveal(cursor.tile, &board->remaining_tiles);
          break;
        case '2':
          flag(cursor.tile, &board->flagged_tiles);
          break;
      }
    }
  } while (running);
  int height = board->options.M;
  destroy_board(board);
  printf("\npress any key to quit...\n");
  getch();
  clear_lines_above(height + 10); // 10 is the Controls height
}

int main() {
  while (1) {
    printf(SAVEPOS);
    start_game(menu());
    printf(RESTOREPOS);
    printf("\033[7A");
  }
}