#include <stdio.h>
#include <Windows.h>
#include "interfaces.h"
#include "cursor.h"

//#define COLORS

void gotoxy(int x, int y) //Ŀ�� ��ġ �ű��
{							//�»���� (0,0)������ (1,1)�� �����
	COORD Cur;
	Cur.X = x; Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

int now_x() //���� xĿ�� ��ġ
{								//�»���� (1,1)�� �ٲ�������� �����������
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BufInfo);
	return BufInfo.dwCursorPosition.X;
}

int now_y() // ���� yĿ�� ��ġ
{
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BufInfo);
	return BufInfo.dwCursorPosition.Y;
}

