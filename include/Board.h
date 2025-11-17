#ifndef BOARD_H
#define BOARD_H

#include "Cursor.h"
#include "Menu.h"
#include "Tile.h"

// Tábla struktúra, 2D-s tömbbel a mezőkhöz
typedef struct {
  Tile** tiles;
  int remaining_tiles;
  int flagged_tiles;
  Options options;
} Board;

// A bekért opciók alapján létrehoz és visszadja a megfelelő tábla pointerét
// A visszaadott táblát később fel kell szabadítani
Board* create_board(Options options);
// A megadott táblának a mezőit véletlenszerűen megtölti aknákkal, az első mezőt figyelembe véve
void fill_board(Board* board, int first_tile[2]);
// A megadott táblát felszabadítja, az összes hozzátartozó tulajdonsággal
void destroy_board(Board* board);
// A megadott táblát a képernyőre kirajzolja színekkel, a jelenlegi pozíciót is figyelembe véve
// visszatérési értéke azt jelzi hogy felfedett-e aknát
bool draw_board(Board* board, Cursor cursor);

#endif