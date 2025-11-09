#ifndef TIMER_H
#define TIMER_H

#include "Menu.h"

typedef struct {
  Difficulty difficulty;
  char name[21];
  int time;  // in second
} Record;

// char* time_to_string(int time);

#endif