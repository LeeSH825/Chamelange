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
			printw("%c", ch);
		}
		return 0;
	}
	else if ((n == 0) && (sizeof(ch) == sizeof(char)))
	{
		printw("%c", ch);
		return 0;
	}
	else if ((n == 0) && (sizeof(ch) != sizeof(char)))
	{
		printw("%s", ch);
		return 0;
	}
	return 0;
}
*/
void edit_Interface()
{
	gotoxy(stdscr, 1, 27); //UI
	//dye(0, COLOR_WHITE, COLOR_BLACK, "Chamelange");
	printw("Chamenage");
	
	gotoxy(stdscr,97, 29);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "ESC or crtl + @: Menu"); //��Ʈ�� Ű ������ ���� �ߵ���
	printw("ESC or crtl + @: Menu");
	gotoxy(stdscr,0, 0);
	//dye(120, COLOR_WHITE, COLOR_BLACK, ' ');
	gotoxy(stdscr,7, 0);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "F");
	//dye(0, COLOR_WHITE, COLOR_BLACK, "ile");
	printw("File");
	gotoxy(stdscr,now_x(stdscr) + 4, 0);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "E");
	//dye(0, COLOR_WHITE, COLOR_BLACK, "dit");
	printw("Edit");
	gotoxy(stdscr,now_x(stdscr) + 4, 0);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "S");
	//dye(0, COLOR_WHITE, COLOR_BLACK, "earch");
	printw("Search");
	gotoxy(stdscr,now_x(stdscr) + 4, 0);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "O");
	//dye(0, COLOR_WHITE, COLOR_BLACK, "ptions");
	printw("options");
	gotoxy(stdscr,now_x(stdscr) + 4, 0);
	printw("help");
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
	printw("[%d]", n);
	
	//dye(0, ft_color, bg_color, " Line");
	gotoxy(stdscr, cur_x_point, cur_y_point); //back to what it placed
	return 0;
}

void main_Screen()
{
	int today_notice = 0;

	///////////////for time
	struct tm* t;
	time_t timer; //�ð� ����
	timer = time(NULL); // ���� �ð��� �ʴ����� ���
	t = localtime(&timer); //�� ������ �ð� �и��ؼ� ����ü��
	////////////////////
	erase();
	gotoxy(stdscr, 47, 3);
	printw("Chamelange");
	gotoxy(stdscr,120, 1); 

	////////////�ǽð����� ���� �� �ִ� �����餩�� main���� ������
	printw("%d-%d-%d\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday); // ù�� ������ ��� ��¥-��-��
	
	
	gotoxy(stdscr,75, 29);
	printw("Copyright @ 2018-2019 RuBi. All Rights Reserved.");
	gotoxy(stdscr,28, 6);
	printw("type : ");
	gotoxy(stdscr,40, 6);
	printw("N");
	gotoxy(stdscr,now_x(stdscr) + 3, 6);
	printw("<Enter>");
	gotoxy(stdscr,58, 6);
	printw("New File");
	gotoxy(stdscr,28, 7);
	printw("type : ");
	gotoxy(stdscr,40, 7);
	printw("O");
	gotoxy(stdscr,now_x(stdscr) + 3, 7);
	printw("<Enter>");
	gotoxy(stdscr,58, 7);
	printw("for option");
	gotoxy(stdscr,28, 8);
	printw("type : ");
	gotoxy(stdscr,40, 8);
	printw("F");
	gotoxy(stdscr,now_x(stdscr) + 3, 8);
	printw("<Enter>");
	gotoxy(stdscr,58, 8);
	printw("for find files");
	gotoxy(stdscr,28, 9);
	printw("type : ");
	gotoxy(stdscr,40, 9);
	printw("M");
	gotoxy(stdscr,now_x(stdscr) + 3, 9);
	printw("<Enter>");
	gotoxy(stdscr,58, 9);
	gotoxy(stdscr,28, 10);
	printw("type : ");
	gotoxy(stdscr,40, 10);
	printw("E");
	gotoxy(stdscr,now_x(stdscr) + 3, 10);
	printw("<Enter>");
	gotoxy(stdscr,58, 10);

	gotoxy(stdscr,17, 12);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "Recent Files");
	gotoxy(stdscr,7, 14);
	gotoxy(stdscr,74, 12);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "Recent Bookmarks");
	gotoxy(stdscr,64, 14);
	/*
	for (int i = 0; i < 12; i++)
	{
		gotoxy(stdscr,1, i + 12);
		//dye(0, COLOR_WHITE, COLOR_BLACK, "~//");
		gotoxy(stdscr,57, i + 12);
		//dye(0, COLOR_WHITE, COLOR_BLACK, "~//");
	}
	*/
	gotoxy(stdscr,23, 27);
	printw("* Main * ");
	//dye(0, COLOR_WHITE, COLOR_BLACK, "* Main * ");
	//dye(0, COLOR_WHITE, COLOR_BLACK, "");
	printw("[%d] ", today_notice);
	//dye(0, COLOR_WHITE, COLOR_BLACK, "Notices >>  ");
	gotoxy(stdscr,now_x(stdscr) + 4, 27);

	//dye(0, COLOR_WHITE, COLOR_BLACK, "");
}