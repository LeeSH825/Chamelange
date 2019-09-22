#include <stdio.h>
#include <Windows.h>
#include "interfaces.h"
#include "cursor.h"

//#define COLORS

void gotoxy(int x, int y) //커서 위치 옮기기
{							//좌상단은 (0,0)이지만 (1,1)로 사용함
	COORD Cur;
	Cur.X = x; Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

int now_x() //현재 x커서 위치
{								//좌상단이 (1,1)로 바뀌었을때의 정보를출력함
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BufInfo);
	return BufInfo.dwCursorPosition.X;
}

int now_y() // 현재 y커서 위치
{
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BufInfo);
	return BufInfo.dwCursorPosition.Y;
}

