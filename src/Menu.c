#include "../include/Menu.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Options menu() {
  char* options[] = {"Easy", "Normal", "Hard", "Custom", "Quit"};
  int selected = 0;
  Options option;
  printf(SAVEPOS);
  while (1) {
    printf(RESTOREPOS);
    printf("\nMenu:\n\n");
    for (int i = 0; i < 5; i++) {
      if (i == selected) {
        color_printf("> ", 30, USER);
        color_printf(options[i], 30, USER);
        color_printf("\n", 30, USER);
      } else {
        printf("  %s\n", options[i]);
      }
    }
    char c = getch();
    if (c == '\033') {
      getch();
      switch (getch()) {
        case 'A':
          selected = (selected == 0) ? 4 : selected - 1;
          break;
        case 'B':
          selected = (selected == 4) ? 0 : selected + 1;
          break;
      }
    } else if (c == '\n' || c == '\r') {
      if (selected == 4)
        exit(0);
      option.difficulty = (Difficulty)selected;
      if (selected == 0) {
        option.N = 9;
        option.M = 9;
        option.mine_count = 10;
      } else if (selected == 1) {
        option.N = 16;
        option.M = 16;
        option.mine_count = 40;
      } else if (selected == 2) {
        option.N = 16;
        option.M = 30;
        option.mine_count = 99;
      } else {
        printf("Enter rows (N): ");
        scanf("%d", &option.N);
        printf("Enter columns (M): ");
        scanf("%d", &option.M);
        printf("Enter mine count: ");
        scanf("%d", &option.mine_count);
      }
      printf(RESTOREPOS);
      return option;
    }
  }
}
