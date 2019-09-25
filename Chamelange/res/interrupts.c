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

char key_ck()
{
	int key;
	keypad(stdscr, TRUE);
	cbreak();
	nonl();
	key = getch();		//if you want to get ch from specific window then use wgetch(WINDOW* )
	switch (key)
	{
		case ctrl('s'):
			save_cur_line();
			exit(0);
		case ctrl('x'):
			save_n_exit();
			exit(0);
		case ctrl('b'):
			create_bookmark();
		default:	//when input was normal character
			return key;
		
	}
	return 0;
}

void menu_Select(char cmd)
{
	switch (cmd)
	{
	case 'N':
		erase();
		new_File();

		break;
	case 'O':
		//erase();
		open_File();
		break;
	case 'F':
		erase();
		find_File();
		break;
	case 'M':
		erase();
		file_Manager();
		break;
	case 'E':
		printf("\n");
		getchar();
		printf("종료하시겠습니까? (Y/N)"); //중간에 팝업창처럼 해놓자
		cmd = getchar();
		switch (cmd)
		{
		case 'Y': {
			exit(0);
		}
		case 'N': {
			erase();
			getchar();
			exit(0);
			break;
		}
		default:
			break;
		}
		break;
	default:
		gotoxy(stdscr, 50, 26);
		////dye(0, COLOR_WHITE, COLOR_BLACK, "잘못 입력하셨습니다.");
		sleep(500);
		erase();
		exit(0);
	}
	exit(0);
}