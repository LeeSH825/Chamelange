#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <stdio.h>
#include "./interfaces.h"
#include "./cursor.h"
#include "./fileManage.h"
#include "./textEditor.h"
#include "interrupts.h"
//#define COLORS

#define max_line_buffer_size 256

typedef struct editor_Infos
{
    FILE* cur_file;
    int pointer;
    int line_buffer[max_line_buffer_size];
    int last_ch;
    int cur_line;
    int last_line;
} e_Infos;

int editor();
void save_Line(FILE* fp, int* buffer);
void print_whole_file(FILE* fp, int line);
void print_file(FILE* fp);
void edit_sClr(FILE* fp, int x, int y);
void edit_menu(FILE* fp, int x, int y);

void editor_LEFT(e_Infos* cur_info);
void editor_RIGHT(e_Infos* cur_info);
void editor_DOWN(e_Infos* cur_info);
void editor_UP(e_Infos* cur_info);

void editor_HOME(e_Infos* cur_info);
void editor_BACKSP(e_Infos* cur_info);
void editor_ENTER(e_Infos* cur_info);
void editor_DEL(e_Infos* cur_info);
void editor_END(e_Infos* cur_info);
int editor_key_ck(e_Infos* cur_info);          //right now, it is written for editor environments



#endif // !TEXTEDITOR_H
