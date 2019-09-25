#include <stdio.h>
#include "interfaces.h"
#include "interrupts.h"s

int key_ck(char ch)
{
	int checker;
	checker = ch;
	if ((checker == 224) || (checker == 0))
	{
		checker = getch();
		return 0;
	}
	if ((GetAsyncKeyState(VK_HANGUL) & 0x8000)) //한영 변환키 입력되면 -2 송출 버퍼로 들어가게
	{
		return -2;
	}
	else if ((GetAsyncKeyState(VK_LEFT) & 0x8000))
	{
		return 0;
	}
	else if ((checker >= 48) && (checker <= 57))
	{
		return 1;  //숫자면 1 반환
	}
	else if ((checker >= 65) && (checker <= 90))
	{
		return 2; //대문자 알파벳이면 2 반환
	}
	else if ((checker >= 97) && (checker <= 122))
	{
		return 3; //알파벳 소문자면 3 반환
	}
	else if ((checker >= 32) && (checker <= 126))
	{
		return 4; //나머지 문자들(제어문자나 다른 문자)이면 4 반환
	}
	else if ((checker >= 0) && (checker <= 127))
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

void menu_Select(char cmd)
{
	switch (cmd)
	{
	case 'N':
		system("cls");
		new_File();

		break;
	case 'O':
		system("cls");
		open_File();
		break;
	case 'F':
		system("cls");
		find_File();
		break;
	case 'M':
		system("cls");
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
			system("cls");
			getchar();
			main();
			break;
		}
		default:
			break;
		}
		break;
	default:
		gotoxy(50, 26);
		dye(0, LIGHTCYAN, BLACK, "잘못 입력하셨습니다.");
		_sleep(100);
		system("cls");
		main();
	}
}