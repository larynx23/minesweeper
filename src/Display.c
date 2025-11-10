#include <stdio.h>

#include "../include/Display.h"

// 1: bright blue fg
// 2: green fg
// 3: red fg
// 4: blue fg
// 5: yellow fg
// 6: cyan fg
// 7: black fg
// 8: bright green fg
const int fgcolors[] = {-1, 96, 32, 91, 34, 31, 36, 30, 92, -1};

#ifndef _WIN32
char getch() {
  struct termios oldattr, newattr;
  char ch;

  // Get current terminal attributes
  tcgetattr(STDIN_FILENO, &oldattr);
  newattr = oldattr;

  // Disable canonical mode and echo
  newattr.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

  // Read one character
  ch = getchar();

  // Restore old terminal attributes
  tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

  return ch;
}
#endif

void color_printf(char* text, int color1, int color2) {
  if (color1 >= 0 && color2 >= 0) {
    printf("\033[%d;%dm%s\033[0m", color1, color2, text);
  } else if (color1 >= 0) {
    printf("\033[%dm%s\033[0m", color1, text);
  } else if (color2 >= 0) {
    printf("\033[%dm%s\033[0m", color2, text);
  } else {
    printf("%s", text);
  }
}

void print_controls(void) {
  printf("\n%s", DELLINE);
  printf("Controls:\n");
  printf("  Arrow keys  : Move cursor\n");
  printf("  1           : Reveal tile\n");
  printf("  2           : Toggle flag\n");
  printf("  q           : Quit\n");
  printf("%s\n", DELLINE);
}

void print_formatted_time(int time) {
  printf("%20d:%20d", time / 60, time % 60);
}