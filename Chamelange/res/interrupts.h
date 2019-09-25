#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <ncurses.h>
#include "interfaces.h"
#include "interrupts.h"
#include "cursor.h"

#define ctrl(x) ((x) & 0x1f)

//functions


void menu_Select(char cmd);


#endif // !INTERRUPTS_H