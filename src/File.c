#include "File.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
size_t getline(char** lineptr, size_t* n, FILE* stream) {
  char* bufptr = NULL;
  char* p = bufptr;
  size_t size;
  int c;
  
  if (lineptr == NULL) {
    return -1;
  }
  if (stream == NULL) {
    return -1;
  }
  if (n == NULL) {
    return -1;
  }
  bufptr = *lineptr;
  size = *n;
  
  c = fgetc(stream);
  if (c == EOF) {
    return -1;
  }
  if (bufptr == NULL) {
    bufptr = malloc(128);
    if (bufptr == NULL) {
      return -1;
    }
    size = 128;
  }
  p = bufptr;
  while (c != EOF) {
    if ((p - bufptr) > (size - 1)) {
      size = size + 128;
      bufptr = realloc(bufptr, size);
      if (bufptr == NULL) {
        return -1;
      }
    }
    *p++ = c;
    if (c == '\n') {
      break;
    }
    c = fgetc(stream);
  }
  
  *p++ = '\0';
  *lineptr = bufptr;
  *n = size;
  
  return p - bufptr - 1;
}
#endif

Record* read_file_to_toplist(char* filename, Difficulty difficulty, int* count) {
  FILE* file = fopen(filename, "r");
  char* line = NULL;
  size_t line_len = 0;
  int toplist_len = 0;
  int capacity = 10;
  Record* toplist = (Record*)malloc(sizeof(Record) * capacity);

  if (file == NULL) {
    *count = 0;
    return toplist;
  }

  while ((getline(&line, &line_len, file)) != -1) {
    Record record;

    char* difficulty_str = strtok(line, ";");
    char* name_str = strtok(NULL, ";");
    char* time_str = strtok(NULL, ";\n");

    if (difficulty_str && name_str && time_str) {
      if (strcmp(difficulty_str, "easy") == 0) {
        record.difficulty = Easy;
      } else if (strcmp(difficulty_str, "normal") == 0) {
        record.difficulty = Normal;
      } else if (strcmp(difficulty_str, "hard") == 0) {
        record.difficulty = Hard;
      }

      if (record.difficulty != difficulty) {
        continue;
      }

      if (toplist_len >= capacity) {
        capacity *= 2;
        Record* temp = (Record*)realloc(toplist, sizeof(Record) * capacity);
        if (temp == NULL) {
          free(toplist);
          free(line);
          fclose(file);
          *count = 0;
          return NULL;
        }
        toplist = temp;
      }

      strncpy(record.name, name_str, 20);
      record.name[20] = '\0';
      record.time = atoi(time_str);

      toplist[toplist_len++] = record;
    }
  }
  free(line);
  fclose(file);
  *count = toplist_len;
  return toplist;
}

void append_toplist(char* filename, Record record) {
  FILE* file = fopen(filename, "a");
  if (file != NULL) {
    const char* difficulty_str;
    if (record.difficulty == Easy) {
      difficulty_str = "easy";
    } else if (record.difficulty == Normal) {
      difficulty_str = "normal";
    } else if (record.difficulty == Hard) {
      difficulty_str = "hard";
    }

    fprintf(file, "%s;%s;%d\n", difficulty_str, record.name, record.time);
    fclose(file);
  }
}

int compare_records(const void* record1, const void* record2) {
  Record* r1 = (Record*)record1;
  Record* r2 = (Record*)record2;

  if (r1->time < r2->time) return -1;
  if (r1->time > r2->time) return 1;
  return 0;
}