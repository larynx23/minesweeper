#ifndef MENU_H
#define MENU_H

#include "Display.h"

typedef enum {
  Easy,
  Normal,
  Hard,
  Custom
} Difficulty;

typedef struct {
  Difficulty difficulty;
  int N, M, mine_count;
} Options;

Options menu();

#endif