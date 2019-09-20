#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

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