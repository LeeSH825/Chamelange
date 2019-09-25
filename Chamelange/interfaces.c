#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

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

int cur_Line(int n, int ft_color, int bg_color) //현재 줄 수 확인
{
	int cur_x_point, cur_y_point; //현재 커서 위치 저장
	cur_x_point = now_x();
	cur_y_point = now_y();
	
	//이건 cur_Line함수 부르기 이전에 호출해야 될 듯
	gotoxy(53, 29);
	
	//dye(0, LIGHTGRAY, BLACK, "");
	printf("[%d]", n); //라인 위치 바꿔줌
	
	dye(0, ft_color, bg_color, " Line");
	gotoxy(cur_x_point, cur_y_point); //원래 위치로 다시 돌아감
	return 0;
}

void main_Screen()
{
	int today_notice = 0;
	///////////////시간
	struct tm* t;
	time_t timer; //시간 측정
	timer = time(NULL); // 현재 시간을 초단위로 얻기
	t = localtime(&timer); //초 단위의 시간 분리해서 구조체로
	////////////////////

	/*gotoxy(56, 3);
	dye(0, LIGHTBLUE, BLACK, " ┌  UDiT - Ultra eDiTor ─────────────────────────────┐");
	for (int i = 4; i < 11; i++)
	{
		gotoxy(57, i);
		dye(0, LIGHTBLUE, BLACK, "│");
		gotoxy(109, i);
		dye(0, LIGHTBLUE, BLACK, "│");
	}
	gotoxy(56, 11);
	dye(0, LIGHTBLUE, BLACK, " └───────────────────────────────────────────────────┘");*/
	
	gotoxy(108, 1);
	dye(0, WHITE, BLACK, "");

	////////////실시간으로 변할 수 있는 변수들은 main으로 빼놓자
	printf("%d-%d-%d\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday); // 첫줄 오른쪽 상단 날짜-월-일
	
	
	gotoxy(31, 3);
	dye(0, GREEN, BLACK, "                     _.....---..._\n");
	gotoxy(31, 4);
	dye(0, GREEN, BLACK, "      _..-'-.   _.--'             '--.._\n");
	gotoxy(31, 5);
	dye(0, GREEN, BLACK, "  _.-' (  0) Y''  C h a m e l a n g e   ''-.._\n");
	gotoxy(31, 6);
	dye(0, GREEN, BLACK, " (---.._,                                     '-._\n");
	gotoxy(31, 7);
	dye(0, GREEN, BLACK, "  `---.,___.-\  \----......./  /..------...____   '-.\n");
	gotoxy(31, 8);
	dye(0, GREEN, BLACK, "     _/  /  _/  /       __\\  \\   __\\  \\      `-.   \\\n");
	gotoxy(31, 9);
	dye(0, GREEN, BLACK, "    (((-'  (((-'        (((---'  (((---`        )  /\n");
	gotoxy(31, 10);
	dye(0, GREEN, BLACK, "                                              .-'.-'\n");
	gotoxy(31, 11);
	dye(0, GREEN, BLACK, "                                              (__`-,\n");
	gotoxy(31, 12);
	dye(0, GREEN, BLACK, "                                                 ``");

	gotoxy(70, 29);
	//dye(0, WHITE, BLACK, "Copyright ⓒ 2018-2019 RuBi. All Rights Reserved.");	//밑에 있는 것들은 나중에 위치 조정하자
	dye(0, WHITE, BLACK, "Copyright ⓒ 2019 Chamelange. All Rights Reserved.");
	/*gotoxy(59, 6);
	dye(0, LIGHTGRAY, BLACK, "type   : ");
	gotoxy(71, 6);
	dye(0, LIGHTCYAN, BLACK, "N");
	gotoxy(now_x() + 3, 6);
	dye(0, LIGHTBLUE, BLACK, "<Enter>");
	gotoxy(89, 6);
	dye(0, LIGHTGRAY, BLACK, "for  새 파일 만들기");
	gotoxy(59, 7);
	dye(0, LIGHTGRAY, BLACK, "type   : ");
	gotoxy(71, 7);
	dye(0, LIGHTCYAN, BLACK, "O");
	gotoxy(now_x() + 3, 7);
	dye(0, LIGHTBLUE, BLACK, "<Enter>");
	gotoxy(89, 7);
	dye(0, LIGHTGRAY, BLACK, "for  파일 열기");
	gotoxy(59, 8);
	dye(0, LIGHTGRAY, BLACK, "type   : ");
	gotoxy(71, 8);
	dye(0, LIGHTCYAN, BLACK, "F");
	gotoxy(now_x() + 3, 8);
	dye(0, LIGHTBLUE, BLACK, "<Enter>");
	gotoxy(89, 8);
	dye(0, LIGHTGRAY, BLACK, "for  파일 찾기");
	gotoxy(59, 9);
	dye(0, LIGHTGRAY, BLACK, "type   : ");
	gotoxy(71, 9);
	dye(0, LIGHTCYAN, BLACK, "M");
	gotoxy(now_x() + 3, 9);
	dye(0, LIGHTBLUE, BLACK, "<Enter>");
	gotoxy(89, 9);
	dye(0, LIGHTGRAY, BLACK, "for  파일 관리자");
	gotoxy(59, 10);
	dye(0, LIGHTGRAY, BLACK, "type   : ");
	gotoxy(71, 10);
	dye(0, LIGHTCYAN, BLACK, "E");
	gotoxy(now_x() + 3, 10);
	dye(0, LIGHTBLUE, BLACK, "<Enter>");
	gotoxy(89, 10);
	dye(0, LIGHTGRAY, BLACK, "for  프로그램 종료");*/

	gotoxy(10, 14);
	dye(0, YELLOW, BLACK, "##########\n"
		"          #  #######\n"
		"          #   ######\n"
		"          #  #######\n"
		"          #  #######\n"
		"          #  ########\n"
		"          #  ########\n"
		"          #  ########\n"
		"          ###");
	gotoxy(14, 23);
	dye(0, LIGHTGRAY, BLACK, "NEW");

	gotoxy(31, 14);
	dye(0, DARKGRAY, BLACK, "############\n");
	gotoxy(31, 15);
	dye(0, LIGHTGRAY, BLACK, "#          #\n");
	gotoxy(31, 16);
	dye(0, LIGHTGRAY, BLACK, "#          #\n");
	gotoxy(31, 17);
	dye(0, LIGHTGRAY, BLACK, "#          #\n");
	gotoxy(31, 18);
	dye(0, LIGHTGRAY, BLACK, "#          #\n");
	gotoxy(31, 19);
	dye(0, LIGHTGRAY, BLACK, "#          #\n");
	gotoxy(31, 20);
	dye(0, LIGHTGRAY, BLACK, "#          #\n");
	gotoxy(31, 21);
	dye(0, LIGHTGRAY, BLACK, "############\n");
	gotoxy(34, 15);
	dye(0, CYAN, BLACK, "#####\n");
	gotoxy(34, 16);
	dye(0, CYAN, BLACK, "#####\n");
	gotoxy(34, 17);
	dye(0, CYAN, BLACK, "#####\n");
	gotoxy(34, 18);
	dye(0, CYAN, BLACK, "#####\n");
	gotoxy(34, 19);
	dye(0, CYAN, BLACK, "#####\n");

	gotoxy(35, 23);
	dye(0, LIGHTGRAY, BLACK, "OPEN");

	gotoxy(52, 14);
	dye(0, LIGHTGRAY, BLACK, "  #####\n");
	gotoxy(52, 15);
	dye(0, LIGHTGRAY, BLACK, " #     #\n");
	gotoxy(52, 16);
	dye(0, LIGHTGRAY, BLACK, "#       #\n");
	gotoxy(52, 17);
	dye(0, LIGHTGRAY, BLACK, " #     #\n");
	gotoxy(52, 18);
	dye(0, LIGHTGRAY, BLACK, "  ######\n");
	gotoxy(52, 19);
	dye(0, LIGHTGRAY, BLACK, "       ##\n");
	gotoxy(52, 20);
	dye(0, LIGHTGRAY, BLACK, "         ##\n");
	gotoxy(52, 21);
	dye(0, LIGHTGRAY, BLACK, "          ##\n");

	gotoxy(56, 23);
	dye(0, LIGHTGRAY, BLACK, "FIND");

	gotoxy(73, 14);
	dye(0, YELLOW, BLACK, "#####      \n");
	gotoxy(73, 15);
	dye(0, YELLOW, BLACK, "############\n");
	gotoxy(73, 16);
	dye(0, YELLOW, BLACK, "############\n");
	gotoxy(73, 17);
	dye(0, YELLOW, BLACK, "##        ##\n");
	gotoxy(73, 18);
	dye(0, YELLOW, BLACK, "##  ####  ##\n");
	gotoxy(73, 19);
	dye(0, YELLOW, BLACK, "##  ####  ##\n");
	gotoxy(73, 20);
	dye(0, YELLOW, BLACK, "##  ####  ##\n");

	gotoxy(73, 23);
	dye(0, LIGHTGRAY, BLACK, "FILE MANAGER");

	gotoxy(95, 14);
	dye(0, GREEN, BLACK, "############\n");
	gotoxy(95, 15);
	dye(0, GREEN, BLACK, "##  ##    ##\n");
	gotoxy(95, 16);
	dye(0, GREEN, BLACK, "##  ####  ##\n");
	gotoxy(95, 17);
	dye(0, GREEN, BLACK, "#### ## # ##\n");
	gotoxy(95, 18);
	dye(0, GREEN, BLACK, "##   ##   ##\n");
	gotoxy(95, 19);
	dye(0, GREEN, BLACK, "##  #  #####\n");
	gotoxy(95, 20);
	dye(0, GREEN, BLACK, "## #      ##\n");

	gotoxy(99, 23);
	dye(0, LIGHTGRAY, BLACK, "EXIT");



	/*gotoxy(1, 13);
	dye(0, LIGHTGRAY, BLACK, "─────────────────────Recent Files─────────────────────");
	gotoxy(7, 14);
	gotoxy(60, 13);
	dye(0, LIGHTGRAY, BLACK, "───────────────────Recent Bookmarks───────────────────");
	gotoxy(64, 14);

	for (int i = 0; i < 12; i++)
	{
		gotoxy(1, i + 14);
		dye(0, LIGHTGRAY, BLACK, "~//");
		gotoxy(60, i + 14);
		dye(0, LIGHTGRAY, BLACK, "~//");
	}*/
	gotoxy(54, 27);
	dye(0, LIGHTGRAY, BLACK, ">>");
	/*gotoxy(23, 27);
	dye(0, LIGHTCYAN, BLACK, "* Main * ");
	dye(0, CYAN, BLACK, "");
	printf("[%d] ", today_notice);
	dye(0, LIGHTCYAN, BLACK, "Notices >>  ");
	gotoxy(now_x() + 4, 27);*/
}