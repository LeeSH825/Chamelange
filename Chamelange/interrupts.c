#include <stdio.h>
#include "interfaces.h"

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