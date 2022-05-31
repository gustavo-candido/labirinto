#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#ifdef _WIN32
WORD GetConsoleTextAttribute (HANDLE hCon);
#endif

void wait( double seconds );
void clean_screen();
void change_colour(char *colour);
void print(char maze[][100], int n);
void reprint(char maze[][100], ii a, int n);


#endif // SCREEN_H_INCLUDED
