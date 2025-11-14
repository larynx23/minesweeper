#include "../include/Menu.h"

#include <../include/File.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Options menu() {
  char* options[] = {"Easy", "Normal", "Hard", "Custom", "Toplist", "Quit"};
  int options_len = 6;
  int selected = 0;
  Options option;
  while (1) {
    printf(RESTOREPOS);
    printf("<------>\nMenu:\n\n");
    for (int i = 0; i < options_len; i++) {
      if (i == selected) {
        color_printf("> ", 30, USER);
        color_printf(options[i], 30, USER);
        color_printf("\n", 30, USER);
      } else {
        printf("  %s\n", options[i]);
      }
    }
    int ch = getch();
#ifdef _WIN32
    if (ch == 224) {
      int key = getch();
      switch (key) {
        case 72:
          selected = (selected == 0) ? options_len - 1 : selected - 1;
          break;
        case 80:
          selected = (selected == options_len - 1) ? 0 : selected + 1;
          break;
      }
    }
#else
    if (ch == '\033') {
      getch();
      switch (getch()) {
        case 'A':
          selected = (selected == 0) ? options_len - 1 : selected - 1;
          break;
        case 'B':
          selected = (selected == options_len - 1) ? 0 : selected + 1;
          break;
      }
    }
#endif
    else if (ch == '\n' || ch == '\r') {
      if (selected == 5) exit(0);
      if (selected == 4) {
        clear_lines_above(options_len + 3);
        toplist_menu();
        continue;
      }
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
        bool valid;
        do {
          valid = true;
          printf("Enter rows (N): ");
          scanf("%d", &option.N);
          clear_lines_above(1);
          printf("Enter columns (M): ");
          scanf("%d", &option.M);
          clear_lines_above(1);
          printf("Enter mine count: ");
          scanf("%d", &option.mine_count);
          clear_lines_above(1);

          double density = ((double)option.mine_count / (double)(option.N * option.M));
          if (option.M > 40 || option.N > 40 || option.M < 10 || option.N < 10) {
            valid = false;
            printf("Board sizes must be between 10 and 40!\npress anything to retry\n");
            getch();
            getch();
            clear_lines_above(2);
          } else if (density > 1.0) {
            valid = false;
            printf("Your density is over 100%% (%.2f%%)\npress anything to retry\n", density * 100);
            getch();
            getch();
            clear_lines_above(2);
          } else if (density > 0.20) {
            char answer;
            do {
              printf("Your density is over 20%% (%.2f%%), are you sure? (y/n)\n", density * 100);
              scanf(" %c", &answer);
              clear_lines_above(2);
            } while (answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N');
            if (answer == 'n' || answer == 'N') {
              valid = false;
            }
          }
        } while (!valid);
      }
      clear_lines_above(options_len + 3);
      return option;
    }
  }
}

void toplist_menu() {
  char* options[] = {"Easy", "Normal", "Hard", "Back"};
  int options_len = 4;
  int selected = 0;
  while (1) {
    printf(RESTOREPOS);
    printf("<------>\nToplist:\n\n");
    for (int i = 0; i < options_len; i++) {
      if (i == selected) {
        color_printf("> ", 30, USER);
        color_printf(options[i], 30, USER);
        color_printf("\n", 30, USER);
      } else {
        printf("  %s\n", options[i]);
      }
    }
    int ch = getch();
#ifdef _WIN32
    if (ch == 224) {
      int key = getch();
      switch (key) {
        case 72:
          selected = (selected == 0) ? options_len - 1 : selected - 1;
          break;
        case 80:
          selected = (selected == options_len - 1) ? 0 : selected + 1;
          break;
      }
    }
#else
    if (ch == '\033') {
      getch();
      switch (getch()) {
        case 'A':
          selected = (selected == 0) ? options_len - 1 : selected - 1;
          break;
        case 'B':
          selected = (selected == options_len - 1) ? 0 : selected + 1;
          break;
      }
    }
#endif
    else if (ch == '\n' || ch == '\r') {
      clear_lines_above(options_len + 3);
      if (selected == 3) return;

      Difficulty selected_diff = (Difficulty)selected;
      int toplist_len;
      Record* toplist = read_file_to_toplist("data/highscore.csv", selected_diff, &toplist_len);

      qsort(toplist, toplist_len, sizeof(Record), compare_records);

      printf("\nTOP 10 %s records:\n", options[selected]);

      if (toplist_len == 0) {
        printf("No records yet!\n");
        toplist_len = 1;
      } else {
        for (int i = 0; i < (toplist_len > 10 ? 10 : toplist_len); i++) {
          printf("%20s | ", toplist[i].name);
          print_formatted_time(toplist[i].time);
        }
      }

      free(toplist);
      printf("press anything to close...\n");
      getch();
      clear_lines_above(toplist_len + 3);
    }
  }
}