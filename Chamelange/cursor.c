#include <stdio.h>
#include <Windows.h>
#include "interfaces.h"

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

int now_Line(int n) //현재 줄 수 확인
{
	int now_x_point, now_y_point; //현재 커서 위치 저장
	now_x_point = now_x();
	now_y_point = now_y();
	gotoxy(53, 29);
	//dye(0, LIGHTGRAY, BLACK, "");
	printf("[%d]", n); //라인 위치 바꿔줌
	dye(0, LIGHTGRAY, BLACK, " Line");
	gotoxy(now_x_point, now_y_point); //원래 위치로 다시 돌아감
	return 0;
}