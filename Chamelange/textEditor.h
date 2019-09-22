#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <stdio.h>

//#define COLORS

int editor();
void save_Line(FILE* fp, char* buffer);
void print_whole_file(FILE* fp, int line);
void edit_sClr(FILE* fp, int x, int y);
void edit_menu(FILE* fp, int x, int y);

#endif // !TEXTEDITOR_H
