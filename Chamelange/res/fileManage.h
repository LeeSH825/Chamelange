#ifndef FILEMANAGE_H
#define FILEMANAGE_H

#include <stdio.h>
#include <stdlib.h>
//#include <io.h>
//#include <conio.h>
#include <ncurses.h>

typedef struct _finddata_t FILE_SEARCH;

//functions
void changePath();
void GetfileList(char* path);
int file_size(FILE* fp);
int new_File();
void save_File();
void copy_file(FILE* in, FILE* out);
int open_file(FILE* fp);

void show_file(FILE* tmp, int x, int y);

int open_File();
int open_e_File(FILE* in);

int find_File();
int file_Manager();

#endif // !FILEMANAGE_H
