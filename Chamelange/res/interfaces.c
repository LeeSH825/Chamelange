#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

#include "interfaces.h"

int dye(int n, int f_color, int b_color, char* ch) // ���� �� �������� ����!!
{													//n=0�̸� ����, ���ڿ� ��� n>0�̸� �׸�ŭ �ݺ� ���
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
	gotoxy(1, 27); //UI
	dye(0, LIGHTGRAY, BLACK, "Chamelange");
	gotoxy(97, 29);
	dye(0, LIGHTGRAY, BLACK, "ESC or crtl + @: Menu"); //��Ʈ�� Ű ������ ���� �ߵ���
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
	dye(0, LIGHTGRAY, BLACK, ""); //�� �ٲ���
}

int cur_Line(int n, int ft_color, int bg_color) //���� �� �� Ȯ��
{
	int cur_x_point, cur_y_point; //���� Ŀ�� ��ġ ����
	cur_x_point = now_x();
	cur_y_point = now_y();
	
	//�̰� cur_Line�Լ� �θ��� ������ ȣ���ؾ� �� ��
	gotoxy(53, 29);
	
	//dye(0, LIGHTGRAY, BLACK, "");
	printf("[%d]", n); //���� ��ġ �ٲ���
	
	dye(0, ft_color, bg_color, " Line");
	gotoxy(cur_x_point, cur_y_point); //���� ��ġ�� �ٽ� ���ư�
	return 0;
}

void main_Screen()
{
	int today_notice = 0;

	

	///////////////�ð�
	struct tm* t;
	time_t timer; //�ð� ����
	timer = time(NULL); // ���� �ð��� �ʴ����� ���
	t = localtime(&timer); //�� ������ �ð� �и��ؼ� ����ü��
	////////////////////

	gotoxy(47, 3);
	dye(0, LIGHTBLUE, BLACK, "UDiT - Ultra eDiTor");
	gotoxy(108, 1);
	dye(0, WHITE, BLACK, "");

	////////////�ǽð����� ���� �� �ִ� �����餩�� main���� ������
	printf("%d-%d-%d\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday); // ù�� ������ ��� ��¥-��-��
	
	
	gotoxy(75, 29);
	dye(0, WHITE, BLACK, "Copyright �� 2018-2019 RuBi. All Rights Reserved.");	//�ؿ� �ִ� �͵��� ���߿� ��ġ ��������
	gotoxy(28, 6);
	dye(0, LIGHTGRAY, BLACK, "type   : ");
	gotoxy(40, 6);
	dye(0, LIGHTCYAN, BLACK, "N");
	gotoxy(now_x() + 3, 6);
	dye(0, LIGHTBLUE, BLACK, "<Enter>");
	gotoxy(58, 6);
	dye(0, LIGHTGRAY, BLACK, "for  �� ���� �����");
	gotoxy(28, 7);
	dye(0, LIGHTGRAY, BLACK, "type   : ");
	gotoxy(40, 7);
	dye(0, LIGHTCYAN, BLACK, "O");
	gotoxy(now_x() + 3, 7);
	dye(0, LIGHTBLUE, BLACK, "<Enter>");
	gotoxy(58, 7);
	dye(0, LIGHTGRAY, BLACK, "for  ���� ����");
	gotoxy(28, 8);
	dye(0, LIGHTGRAY, BLACK, "type   : ");
	gotoxy(40, 8);
	dye(0, LIGHTCYAN, BLACK, "F");
	gotoxy(now_x() + 3, 8);
	dye(0, LIGHTBLUE, BLACK, "<Enter>");
	gotoxy(58, 8);
	dye(0, LIGHTGRAY, BLACK, "for  ���� ã��");
	gotoxy(28, 9);
	dye(0, LIGHTGRAY, BLACK, "type   : ");
	gotoxy(40, 9);
	dye(0, LIGHTCYAN, BLACK, "M");
	gotoxy(now_x() + 3, 9);
	dye(0, LIGHTBLUE, BLACK, "<Enter>");
	gotoxy(58, 9);
	dye(0, LIGHTGRAY, BLACK, "for  ���� ������");
	gotoxy(28, 10);
	dye(0, LIGHTGRAY, BLACK, "type   : ");
	gotoxy(40, 10);
	dye(0, LIGHTCYAN, BLACK, "E");
	gotoxy(now_x() + 3, 10);
	dye(0, LIGHTBLUE, BLACK, "<Enter>");
	gotoxy(58, 10);
	dye(0, LIGHTGRAY, BLACK, "for  ���α׷� ����");

	gotoxy(17, 12);
	dye(0, LIGHTGRAY, BLACK, "Recent Files");
	gotoxy(7, 14);
	gotoxy(74, 12);
	dye(0, LIGHTGRAY, BLACK, "Recent Bookmarks");
	gotoxy(64, 14);

	for (int i = 0; i < 12; i++)
	{
		gotoxy(1, i + 12);
		dye(0, LIGHTGRAY, BLACK, "~//");
		gotoxy(57, i + 12);
		dye(0, LIGHTGRAY, BLACK, "~//");
	}

	gotoxy(23, 27);
	dye(0, LIGHTCYAN, BLACK, "* Main * ");
	dye(0, CYAN, BLACK, "");
	printf("[%d] ", today_notice);
	dye(0, LIGHTCYAN, BLACK, "Notices >>  ");
	gotoxy(now_x() + 4, 27);

	dye(0, GREEN, BLACK, "");
}