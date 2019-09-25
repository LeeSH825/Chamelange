#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include "interfaces.h"
#include "interrupts.h"
#include "cursor.h"
//#include "main.c"
#include "fileManage.h"

int key_ck()
{
	int key = getch();		//if you want to get ch from specific window then use wgetch(WINDOW* )
	
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
		printf("�����Ͻðڽ��ϱ�? (Y/N)"); //�߰��� �˾�âó�� �س���
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
		////dye(0, COLOR_WHITE, COLOR_BLACK, "�߸� �Է��ϼ̽��ϴ�.");
		sleep(500);
		erase();
		exit(0);
	}
	exit(0);
}