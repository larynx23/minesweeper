#ifndef TILE_H
#define TILE_H

#include <stdbool.h>

// Egy mezőnek strukúrája, mivel önmagára is hivatkozik, előtte iniciálni kell
typedef struct Tile Tile;
struct Tile {
  int value;  // 0-8: numbers, 9: mine
  bool is_flagged;
  bool is_revealed;
  Tile* neighbors[8];
};

// felfedi az adott mezőt, a beadott számlálót növeli, nyomon követi a már felfedett mezőket
// ha már fel van fedve/be van zászlózva ne csináljon semmit
// ha nulla, körülötte is felfed rekurzívan
void reveal(Tile* tile, int* counter);
// meg-/ki- zászlózza az adott mezőt,a beadott számlálót növeli, nyomon követi a már zászlózott mezőket
// ha már fel van fedve nem csinál semmit
void flag(Tile* tile, int* counter);

#endif