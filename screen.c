#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pair.h"
#include "screen.h"

void wait( double seconds ){
    #ifdef _WIN32
        Sleep( 1000 * seconds );
    #else
    fflush(stdout);
        usleep(1000000*seconds);
    #endif
}

void clean_screen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

#ifdef _WIN32
WORD GetConsoleTextAttribute (HANDLE hCon)
{
  CONSOLE_SCREEN_BUFFER_INFO con_info;
  GetConsoleScreenBufferInfo(hCon, &con_info);
  return con_info.wAttributes;
}
#endif

void change_colour(char *colour) {
    #ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if(strcmp(colour, "blue") == 0) SetConsoleTextAttribute(hConsole, 9);
    else if(strcmp(colour, "red") == 0) SetConsoleTextAttribute(hConsole, 12);
    else if(strcmp(colour, "white") == 0) SetConsoleTextAttribute(hConsole, 15);
    else if(strcmp(colour, "yellow") == 0) SetConsoleTextAttribute(hConsole, 14);
    #else
    if(strcmp(colour, "blue") == 0) printf("\x1B[34m");
    else if(strcmp(colour, "red") == 0) printf("\x1B[31m");
    else if(strcmp(colour, "white") == 0) printf("\x1B[37m");
    else if(strcmp(colour, "yellow") == 0) printf("\x1B[33m");
    #endif
}


void print(char maze[][100], int n){
    int i, j;
    for(i=0; i<n; i++) {
        for(j=0; j<strlen(maze[i]); j++) {
            if(maze[i][j] == '@') {
                change_colour("blue");
                printf("%c", maze[i][j]);
                change_colour("white");
            }
            else if(maze[i][j] == 'F'){
                change_colour("red");
                printf("%c", maze[i][j]);
                change_colour("white");
            }
            else if(maze[i][j] == '-' || maze[i][j] == '|' || maze[i][j] == 'o') {
                change_colour("yellow");
                printf("%c", maze[i][j]);
                change_colour("white");
            }
            else printf("%c", maze[i][j]);
        }
        puts("");
    }
}

void reprint(char maze[][100], ii a, int n) {
  #ifdef _WIN32
        COORD Coord;
        Coord.Y = a.first;
        Coord.X = a.second;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Coord);
         if(maze[a.first][a.second] == '@') {
                change_colour("blue");
                printf("%c", maze[a.first][a.second]);
                change_colour("white");
            }
            else if(maze[a.first][a.second] == 'F'){
                change_colour("red");
                printf("%c", maze[a.first][a.second]);
                change_colour("white");
            }
            else if(maze[a.first][a.second] == '-' || maze[a.first][a.second] == '|' || maze[a.first][a.second] == 'o') {
                change_colour("yellow");
                printf("%c", maze[a.first][a.second]);
                change_colour("white");
            }
            else printf("%c", maze[a.first][a.second]);
        Coord.Y = 0;
        Coord.X = 0;
    #else
	    printf("\033[%d;%dH", a.first+1, a.second+1);
	     if(maze[a.first][a.second] == '@') {
	                change_colour("blue");
	                printf("%c", maze[a.first][a.second]);
	                change_colour("white");
	            }
	            else if(maze[a.first][a.second] == 'F'){
	                change_colour("red");
	                printf("%c", maze[a.first][a.second]);
	                change_colour("white");
	            }
	            else if(maze[a.first][a.second] == '-' || maze[a.first][a.second] == '|' || maze[a.first][a.second] == 'o') {
	                change_colour("yellow");
	                printf("%c", maze[a.first][a.second]);
	                change_colour("white");
	            }
	            else printf("%c", maze[a.first][a.second]);
	    printf("\033[%d;%dH", 1, 1);
    #endif

}
