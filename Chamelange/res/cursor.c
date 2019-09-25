#include <stdio.h>
#include <ncurses.h>
#include "interfaces.h"
#include "cursor.h"

//#define COLORS

void gotoxy(WINDOW* cur_win, int x, int y) 
{							
	move(y, x);

}

int now_x(WINDOW* cur_win) //get x coordinate
{	
	int x,y;
	getyx(cur_win, y,x);
	return x;
}

int now_y(WINDOW* cur_win) //get y coordinate
{
	int x,y;
	getyx(cur_win, y,x);
	return y;
}
