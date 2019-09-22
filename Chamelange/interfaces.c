#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "interfaces.h"

int dye(int n, int f_color, int b_color, char* ch) // 이전 색 뭐였는지 유의!!
{													//n=0이면 문자, 문자열 출력 n>0이면 그만큼 반복 출력
	int i = 0;
	int color = f_color + b_color * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	if (n > 0)
	{
		for (i = 0; i < n; i++)
		{
			printf("%c", ch);
		}
		return 0;
	}
	else if ((n == 0) && (sizeof(ch) == sizeof(char)))
	{
		printf("%c", ch);
		return 0;
	}
	else if ((n == 0) && (sizeof(ch) != sizeof(char)))
	{
		printf("%s", ch);
		return 0;
	}
	return 0;
}

void edit_Interface()
{
	gotoxy(1, 29); //UI
	dye(0, LIGHTGRAY, BLACK, "UDiT");
	gotoxy(97, 29);
	dye(0, LIGHTGRAY, BLACK, "ESC or crtl + @: Menu"); //컨트롤 키 눌리면 설명 뜨도록
	gotoxy(0, 0);
	dye(120, DARKGRAY, LIGHTBLUE, ' ');
	gotoxy(7, 0);
	dye(0, YELLOW, LIGHTBLUE, "F");
	dye(0, LIGHTGRAY, LIGHTBLUE, "ile");
	gotoxy(now_x() + 4, 0);
	dye(0, YELLOW, LIGHTBLUE, "E");
	dye(0, LIGHTGRAY, LIGHTBLUE, "dit");
	gotoxy(now_x() + 4, 0);
	dye(0, YELLOW, LIGHTBLUE, "S");
	dye(0, LIGHTGRAY, LIGHTBLUE, "earch");
	gotoxy(now_x() + 4, 0);
	dye(0, YELLOW, LIGHTBLUE, "O");
	dye(0, LIGHTGRAY, LIGHTBLUE, "ptions");
	gotoxy(now_x() + 4, 0);
	dye(0, YELLOW, LIGHTBLUE, "H");
	dye(0, LIGHTGRAY, LIGHTBLUE, "elp");
	dye(0, LIGHTGRAY, BLACK, ""); //색 바꿔줌
}