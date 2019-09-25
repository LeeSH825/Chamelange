#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>
//#include <io.h>
//#include <conio.h>


#include "interfaces.h"
#include "cursor.h"
#include "interrupts.h"
#include "fileManage.h"
#include "textEditor.h"

void init_scr() //initialize screen
{
	initscr();
	start_color();
	return;
}



int main()
{
	int i, x = 0, y = 0;
	char command;
	char loc[60]; //file location
	//default window: stdscr
	//WINDOW* main_win;

	//change options later!!!!!!!!!!!!!!!11
	FILE* bmk = fopen("./bookmarks.txt", "w+");
	FILE* ref = fopen("./recentfiles.txt", "w+");
	
	//init_scr();
	init_scr();
	/*
	fseek(ref, 0, SEEK_SET);
	while (fscanf(ref, "%s", loc) != EOF)
	{

		printf("%s\n", loc);
		gotoxy(stdscr, 7, now_y(stdscr) + 1);

	}
	fclose(ref);
	//fflush(ref);
	
	fseek(bmk, 0, SEEK_CUR);
	while (fscanf(bmk, "%d %d", &x, &y) != EOF)
	{
		printf("%d, %d", x, y);
		gotoxy(stdscr, 64, now_y(stdscr) + 1);
	}
	//fflush(bmk);
	fclose(bmk);
	*/
while(1){
	clear();
	//erase();
	main_Screen();

	command = getchar();
	
	menu_Select(command);
}
	return 0;
}