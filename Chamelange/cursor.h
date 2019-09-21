#ifndef CURSOR_H
#define CURSOR_H

#include <Windows.h>

//functions
void gotoxy(int x, int y);
int now_x();
int now_y();
int now_Line(int n);

#endif // !CURSOR_H