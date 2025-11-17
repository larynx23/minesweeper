#ifndef MENU_H
#define MENU_H

#include "Display.h"

// Nehézségek
typedef enum {
  Easy,
  Normal,
  Hard,
  Custom
} Difficulty;

// Beállítások
typedef struct {
  Difficulty difficulty;
  int N, M, mine_count;
} Options;

// Kirajzolja a menüt, és választás után vissza tér a megfeleő beállításokkal
Options menu();
// Kirajzolja a dicsőséglistát
void toplist_menu();

#endif