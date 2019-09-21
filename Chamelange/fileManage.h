#ifndef FILEMANAGE_H
#define FILEMANAGE_H

#include <stdio.h>
//#include <stdlib.h>
#include <io.h>
#include <conio.h>
#include <Windows.h>

typedef struct _finddata_t FILE_SEARCH;

//functions
void GetfileList(char* path);
int file_size(FILE* fp);
void save_File();
void copy_file(FILE* in, FILE* out);
int open_File();
int open_e_File(FILE* in);
int new_File();
int find_File();


#endif // !FILEMANAGE_H
