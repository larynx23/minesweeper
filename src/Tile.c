#include "../include/Tile.h"

void reveal(Tile* tile, int* counter) {
  if (tile->is_flagged || tile->is_revealed) return;

  tile->is_revealed = true;
  *(counter) -= 1;
  if (tile->value == 0) {
    for (int n = 0; n < 8; n++) {
      if (tile->neighbors[n]) {
        reveal(tile->neighbors[n], counter);
      }
    }
  }
}

void flag(Tile* tile, int* counter) {
  if (tile->is_revealed) return;
  if (tile->is_flagged) {
    *(counter) -= 1;
  } else {
    *(counter) += 1;
  }
  tile->is_flagged = !tile->is_flagged;
}
