#ifndef INTERFACES_H
#define	INTERFACES_H

#include <stdio.h>
#include <Windows.h>
#include <time.h>

//#ifdef COLORS

//default colors
#define BLACK 0 
#define BLUE 1 
#define GREEN 2 
#define CYAN 3 
#define RED 4 
#define MAGENTA 5 
#define BROWN 6 
#define LIGHTGRAY 7 
#define DARKGRAY 8 
#define LIGHTBLUE 9 
#define LIGHTGREEN 10 
#define LIGHTCYAN 11 
#define LIGHTRED 12 
#define LIGHTMAGENTA 13 
#define YELLOW 14 
#define WHITE 15

//#endif // !COLORS


//functions
int dye(int n, int f_color, int b_color, char* ch);
void edit_Interface();
int cur_Line(int n, int bg_color, int ft_color);
void main_Screen();

#endif // !INTERFACES_H