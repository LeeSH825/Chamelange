#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include "interfaces.h"
#include "interrupts.h"
#include "cursor.h"
//#include "main.c"
#include "fileManage.h"
#include "bookmaark.h"
#include "textEditor.h"



void menu_Select(char cmd)
{
	switch (cmd)
	{
	case 'N':
		//erase();
		new_File();

		break;
	case 'O':
		//erase();
		open_File();
		break;
	case 'F':
		//erase();
		find_File();
		break;
	case 'M':
		//erase();
		file_Manager();
		break;
	case 'E':
		printw("\n");
		getch();
		printw("Exit the Program?? (Y/N)"); //중간에 팝업창처럼 해놓자
		cmd = getchar();
		switch (cmd)
		{
		case 'Y': 
			exit(0);
		
		case 'N': 
			erase();
			return;
		/*case KEY_EXIT :
			erase();
			return;*/
		default:
			erase();
			break;
		}
		break;
	default:
		gotoxy(stdscr, 50, 26);
		printw("You've entered wrong command");
		erase();
		return;
	}
}