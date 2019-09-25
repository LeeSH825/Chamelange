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

char key_ck()
{
	unsigned int key;
	keypad(stdscr, TRUE);
	cbreak();
	nonl();
	key = getch();			//if you want to get ch from specific window then use wgetch(WINDOW* )
	switch (key)
	{
		case ctrl('s'):		//crtl+s: save current state
			save_cur_line();
			exit(0);
		case ctrl('x'):		// save and exit
			save_n_exit();
			exit(0);
		case ctrl('b'):		//add bookmark
			create_bookmark();
			exit(0);
		case KEY_BACKSPACE:
			editor_backspace();
			exit(0);
		case KEY_ENTER:
			editor_enter();
			exit(0);
		default:			//when input was normal character
			return key;
		
	}
	return 0;
}

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
		printf("\n");
		getch();
		printf("Exit the Program?? (Y/N)"); //�߰��� �˾�âó�� �س���
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
		printf("You've entered wrong command");
		erase();
		return;
	}
}