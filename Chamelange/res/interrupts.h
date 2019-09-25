#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <ncurses.h>

#define ctrl(x) ((x) & 0x1f)

//functions
char key_ck();          //right now, it is written for editor environments

void menu_Select(char cmd);


#endif // !INTERRUPTS_H