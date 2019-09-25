#ifndef CURSOR_H
#define CURSOR_H

#include <ncurses.h>

//functions
void gotoxy(WINDOW* cur_win, int x, int y);
int now_x(WINDOW* cur_win);
int now_y(WINDOW* cur_win);


#endif // !CURSOR_H