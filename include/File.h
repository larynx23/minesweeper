#ifndef FILE_H
#define FILE_H

#include "Menu.h"

typedef struct {
  Difficulty difficulty;
  char name[21];
  int time;  // in second
} Record;

Record* read_file_to_toplist(char* filename, Difficulty difficulty, int* count);
void append_toplist(char* filename, Record record);

#endif