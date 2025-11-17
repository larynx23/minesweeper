#ifndef FILE_H
#define FILE_H

#include "Menu.h"

// Egy bejegyzés adatai
typedef struct {
  Difficulty difficulty;
  char name[21];
  int time;  // in second
} Record;

// A megadott útvonalról kiolvassa az összes bejegyzést a megadott nehézség szerint
// Az utolsó pointerbe kerül a kiolvassot, majd vissza adott lista hossza
Record* read_file_to_toplist(char* filename, Difficulty difficulty, int* count);
// A megadott útvonalra feljegyez egy nyereséget nehézség, idő és név alapján
void append_toplist(char* filename, Record record);
// qsort függvényhez hasonlító
int compare_records(const void* record1, const void* record2);
#ifdef _WIN32
// Windowson nem beépített függvény, file sorait kiolvassa
size_t getline(char** lineptr, size_t* n, FILE* stream);
#endif

#endif