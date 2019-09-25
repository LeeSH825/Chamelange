#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>

#include "./interfaces.h"
#include "./cursor.h"
/*
int dye(int n, short f_color, short b_color, char* ch)
{													
	int i = 0;
	init_pair(1, f_color, b_color);	//set color match to input
	attron(COLOR_PAIR(1));			//color activate
	
	if ((n > 0) && (sizeof(ch) == sizeof(char)))
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
*/
void edit_Interface()
{
	gotoxy(stdscr, 1, 27); //UI
	//dye(0, COLOR_WHITE, COLOR_BLACK, "Chamelange");
	printf("Chamelange");
	gotoxy(stdscr,97, 29);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "ESC or crtl + @: Menu"); //��Ʈ�� Ű ������ ���� �ߵ���
	printf("ESC or crtl + @: Menu");
	gotoxy(stdscr,0, 0);
	//dye(120, COLOR_WHITE, COLOR_BLACK, ' ');
	gotoxy(stdscr,7, 0);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "F");
	//dye(0, COLOR_WHITE, COLOR_BLACK, "ile");
	printf("File");
	gotoxy(stdscr,now_x(stdscr) + 4, 0);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "E");
	//dye(0, COLOR_WHITE, COLOR_BLACK, "dit");
	printf("Edit");
	gotoxy(stdscr,now_x(stdscr) + 4, 0);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "S");
	//dye(0, COLOR_WHITE, COLOR_BLACK, "earch");
	printf("Search");
	gotoxy(stdscr,now_x(stdscr) + 4, 0);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "O");
	//dye(0, COLOR_WHITE, COLOR_BLACK, "ptions");
	printf("options");
	gotoxy(stdscr,now_x(stdscr) + 4, 0);
	printf("help");
	//dye(0, COLOR_WHITE, COLOR_BLACK, "H");
	//dye(0, COLOR_WHITE, COLOR_BLACK, "elp");
	//dye(0, COLOR_WHITE, COLOR_BLACK, ""); //�� �ٲ���
	refresh();
}

int cur_Line(int n, int ft_color, int bg_color) //get current line of file
{
	int cur_x_point, cur_y_point; 
	cur_x_point = now_x(stdscr);
	cur_y_point = now_y(stdscr);
	
	//where Line indicator places
	gotoxy(stdscr, 53, 29);
	
	////dye(0, LIGHTGRAY, BLACK, "");
	printf("[%d]", n);
	
	//dye(0, ft_color, bg_color, " Line");
	gotoxy(stdscr, cur_x_point, cur_y_point); //back to what it placed
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

	gotoxy(stdscr, 47, 3);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "UDiT - Ultra eDiTor");
	printf("Chamelange");
	gotoxy(stdscr,108, 1);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "");

	////////////�ǽð����� ���� �� �ִ� �����餩�� main���� ������
	printf("%d-%d-%d\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday); // ù�� ������ ��� ��¥-��-��
	
	
	gotoxy(stdscr,75, 29);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "Copyright �� 2018-2019 RuBi. All Rights Reserved.");	//�ؿ� �ִ� �͵��� ���߿� ��ġ ��������
	printf("Copyright �� 2018-2019 RuBi. All Rights Reserved.");
	gotoxy(stdscr,28, 6);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "type   : ");
	printf("type : ");
	gotoxy(stdscr,40, 6);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "N");
	printf("N");
	gotoxy(stdscr,now_x(stdscr) + 3, 6);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "<Enter>");
	printf("<Enter>");
	gotoxy(stdscr,58, 6);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "for  �� ���� �����");
	printf("New File");
	gotoxy(stdscr,28, 7);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "type   : ");
	printf("type : ");
	gotoxy(stdscr,40, 7);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "O");
	printf("O");
	gotoxy(stdscr,now_x(stdscr) + 3, 7);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "<Enter>");
	printf("<Enter>");
	gotoxy(stdscr,58, 7);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "for  ���� ����");
	printf("for option");
	gotoxy(stdscr,28, 8);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "type   : ");
	printf("type : ");
	gotoxy(stdscr,40, 8);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "F");
	printf("F");
	gotoxy(stdscr,now_x(stdscr) + 3, 8);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "<Enter>");
	printf("<Enter>");
	gotoxy(stdscr,58, 8);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "for  ���� ã��");
	printf("for find files");
	gotoxy(stdscr,28, 9);
	printf("type : ");
	//dye(0, COLOR_WHITE, COLOR_BLACK, "type   : ");
	gotoxy(stdscr,40, 9);
	printf("M");
	//dye(0, COLOR_WHITE, COLOR_BLACK, "M");
	gotoxy(stdscr,now_x(stdscr) + 3, 9);
	printf("<Enter>");
	//dye(0, COLOR_WHITE, COLOR_BLACK, "<Enter>");
	gotoxy(stdscr,58, 9);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "for  ���� ������");
	gotoxy(stdscr,28, 10);
	printf("type : ");
	//dye(0, COLOR_WHITE, COLOR_BLACK, "type   : ");
	gotoxy(stdscr,40, 10);
	printf("E");
	//dye(0, COLOR_WHITE, COLOR_BLACK, "E");
	gotoxy(stdscr,now_x(stdscr) + 3, 10);
	printf("<Enter>");
	//dye(0, COLOR_WHITE, COLOR_BLACK, "<Enter>");
	gotoxy(stdscr,58, 10);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "for  ���α׷� ����");

	gotoxy(stdscr,17, 12);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "Recent Files");
	gotoxy(stdscr,7, 14);
	gotoxy(stdscr,74, 12);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "Recent Bookmarks");
	gotoxy(stdscr,64, 14);

	for (int i = 0; i < 12; i++)
	{
		gotoxy(stdscr,1, i + 12);
		//dye(0, COLOR_WHITE, COLOR_BLACK, "~//");
		gotoxy(stdscr,57, i + 12);
		//dye(0, COLOR_WHITE, COLOR_BLACK, "~//");
	}

	gotoxy(stdscr,23, 27);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "* Main * ");
	//dye(0, COLOR_WHITE, COLOR_BLACK, "");
	printf("[%d] ", today_notice);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "Notices >>  ");
	gotoxy(stdscr,now_x(stdscr) + 4, 27);

	//dye(0, COLOR_WHITE, COLOR_BLACK, "");
}