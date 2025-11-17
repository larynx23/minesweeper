#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

// ANSI karakter kódok egyértelműsítése
// kurzor mozgatása a terminálban
#define SAVEPOS "\0337"
#define RESTOREPOS "\0338"
#define DELLINE "\033[2K"
#define MOVEUP "\033[1A"

// színek
#define USER 107        // white bg
#define MINE 41         // red bg
#define FLAGGED 91      // red fg
#define UNREVEALED 100  // gray bg
#define NO_COLOR -1

// színek
extern const int fgcolors[];

#ifndef _WIN32
// Linux-on nem beépített függvény
char getch();
#endif
// Megadott szöveget színesen kiírja a terminálra 
// A két szín külön a háttér-/szöveg- színnek van
// Azt hogy háttér-/szöveg- szín-e, a megadott szám dönti el
void color_printf(char* text, int color1, int color2);
void print_controls(void);
void print_formatted_time(int time);
// terminálban a kurzor helyzetéhez képest felfele megadott menyíségí sort töröl ki
void clear_lines_above(int n);

#endif