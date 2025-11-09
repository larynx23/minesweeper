#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

#define SAVEPOS "\0337"
#define RESTOREPOS "\0338"
#define DELLINE "\033[2K"

#define USER 107        // white bg
#define MINE 41         // red bg
#define FLAGGED 91      // red fg
#define UNREVEALED 100  // gray bg
#define NO_COLOR -1

extern const int fgcolors[];

#ifndef _WIN32
char getch();
#endif
void color_printf(char* text, int color1, int color2);
void print_controls(void);

#endif