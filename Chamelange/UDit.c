#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>
#include <time.h>
#include <io.h>

#define BLACK 0 
#define BLUE 1 
#define GREEN 2 
#define CYAN 3 
#define RED 4 
#define MAGENTA 5 
#define BROWN 6 
#define LIGHTGRAY 7 
#define DARKGRAY 8 
#define LIGHTBLUE 9 
#define LIGHTGREEN 10 
#define LIGHTCYAN 11 
#define LIGHTRED 12 
#define LIGHTMAGENTA 13 
#define YELLOW 14 
#define WHITE 15

//int bmkn = 0;
void gotoxy(int x, int y);
int dye(int n, int f_color, int b_color, char* ch);
int now_x();
int now_y();
int key_ck(char ch);
int now_Line(int n);
void print_whole_file(FILE *fp, int line);
void edit_Interface();
void edit_sClr(FILE *fp, int x, int y);
void edit_menu(FILE *fp, int x, int y);
void GetfileList(char* path);
int file_size(FILE *fp);

void save_File();
void copy_file(FILE *in, FILE *out);
int open_File();
int open_e_File(FILE *in);
int editor();
int new_File();
int find_File();
int file_Manager();

typedef struct _finddata_t FILE_SEARCH;

int main()
{
	int i, x = 0, y = 0;
	int today_notice = 0;
	char command;
	struct tm *t;
	time_t timer; //시간 측정
	timer = time(NULL); // 현재 시간을 초단위로 얻기
	t = localtime(&timer); //초 단위의 시간 분리해서 구조체로
	char loc[60];

	gotoxy(47, 3);
	dye(0, LIGHTBLUE, BLACK, "UDiT - Ultra eDiTor");
	gotoxy(108, 1);
	dye(0, WHITE, BLACK, "");
	printf("%d-%d-%d\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday); // 첫줄 오른쪽 상단 날짜-월-일
	gotoxy(75, 29);
	dye(0, WHITE, BLACK, "Copyright ⓒ 2018 RuBi. All Rights Reserved.");	//밑에 있는 것들은 나중에 위치 조정하자
	gotoxy(28, 6);
	dye(0, LIGHTGRAY, BLACK, "type   : ");
	gotoxy(40, 6);
	dye(0, LIGHTCYAN, BLACK, "N");
	gotoxy(now_x() + 3, 6);
	dye(0, LIGHTBLUE, BLACK, "<Enter>");
	gotoxy(58, 6);
	dye(0, LIGHTGRAY, BLACK, "for  새 파일 만들기");
	gotoxy(28, 7);
	dye(0, LIGHTGRAY, BLACK, "type   : ");
	gotoxy(40, 7);
	dye(0, LIGHTCYAN, BLACK, "O");
	gotoxy(now_x() + 3, 7);
	dye(0, LIGHTBLUE, BLACK, "<Enter>");
	gotoxy(58, 7);
	dye(0, LIGHTGRAY, BLACK, "for  파일 열기");
	gotoxy(28, 8);
	dye(0, LIGHTGRAY, BLACK, "type   : ");
	gotoxy(40, 8);
	dye(0, LIGHTCYAN, BLACK, "F");
	gotoxy(now_x() + 3, 8);
	dye(0, LIGHTBLUE, BLACK, "<Enter>");
	gotoxy(58, 8);
	dye(0, LIGHTGRAY, BLACK, "for  파일 찾기");
	gotoxy(28, 9);
	dye(0, LIGHTGRAY, BLACK, "type   : ");
	gotoxy(40, 9);
	dye(0, LIGHTCYAN, BLACK, "M");
	gotoxy(now_x() + 3, 9);
	dye(0, LIGHTBLUE, BLACK, "<Enter>");
	gotoxy(58, 9);
	dye(0, LIGHTGRAY, BLACK, "for  파일 관리자");
	gotoxy(28, 10);
	dye(0, LIGHTGRAY, BLACK, "type   : ");
	gotoxy(40, 10);
	dye(0, LIGHTCYAN, BLACK, "E");
	gotoxy(now_x() + 3, 10);
	dye(0, LIGHTBLUE, BLACK, "<Enter>");
	gotoxy(58, 10);
	dye(0, LIGHTGRAY, BLACK, "for  프로그램 종료");
	FILE *bmk = fopen("C://UDiT//bookmarks.txt", "r+");
	FILE *ref = fopen("C://UDiT//recentfiles.txt", "r+");
	gotoxy(17, 12);
	dye(0, LIGHTGRAY, BLACK, "Recent Files");
	gotoxy(7, 14);
	fseek(ref, 0, SEEK_SET);
	while (fscanf(ref, "%s", loc) != EOF)
	{
		
		printf("%s\n", loc);
		gotoxy(7, now_y() + 1);
		
	}
	fclose(ref);
	//fflush(ref);
	gotoxy(74, 12);
	dye(0, LIGHTGRAY, BLACK, "Recent Bookmarks");
	gotoxy(64, 14);
	fseek(bmk, 0, SEEK_CUR);
	while (fscanf(bmk, "%d %d", &x, &y) != EOF)
	{
	printf("%d, %d", x, y);
	gotoxy(64, now_y() + 1);
	}
	//fflush(bmk);
	for (i = 0; i < 12; i++)
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

	command = getchar(); 
	switch (command)
	{
	case 'N':
		system("cls");
		new_File();

		break;
	case 'O':
		system("cls");
		open_File();
		break;
	case 'F':
		system("cls");
		find_File();
		break;
	case 'M':
		system("cls");
		file_Manager();
		break;
	case 'E':
		printf("\n");
		getchar();
		printf("종료하시겠습니까? (Y/N)"); //중간에 팝업창처럼 해놓자
		command = getchar();
		switch (command)
		{
		case 'Y': {
			exit(0);
		}
		case 'N': {
			system("cls");
			getchar();
			main();
			break;
		}
		default:
			break;
		}
		break;
	default:
		gotoxy(50, 26);
		dye(0, LIGHTCYAN, BLACK, "잘못 입력하셨습니다.");
		_sleep(500);
		system("cls");
		main();
	}
	return 0;
}
void gotoxy(int x, int y) //커서 위치 옮기기
{							//좌상단은 (0,0)이지만 (1,1)로 사용함
	COORD Cur;
	Cur.X = x; Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}
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
int now_Line(int n) //현재 줄 수 확인
{
	int now_x_point, now_y_point; //현재 커서 위치 저장
	now_x_point = now_x();
	now_y_point = now_y();
	gotoxy(53, 29);
	dye(0, LIGHTGRAY, BLACK, "");
	printf("[%d]", n); //라인 위치 바꿔줌
	dye(0, LIGHTGRAY, BLACK, " Line");
	gotoxy(now_x_point, now_y_point); //원래 위치로 다시 돌아감
	return 0;
}
void edit_sClr(FILE *fp, int x, int y) //x랑 y는 각각 화면 클리어 할 당시의 포인터, 라인 위치
{
	int now_x_pointer = now_x();
	int now_y_pointer = now_y();
	system("cls");
	edit_Interface();
	gotoxy(0, 1);
	print_whole_file(fp, y);
}
void print_whole_file(FILE *fp, int line) //수정된 파일을 다시 표시해줌
{
	int now_x_pointer = now_x(); //원래 있던 좌표값 받아옴
	int now_y_pointer = now_y();
	int now_pointer = ftell(fp); //현재 파일 포인터 
	char b;
	fseek(fp, 0, SEEK_SET); //파일의 처음  포인터로 넘어감
	system("cls");
	edit_Interface();
	now_Line(line); //라인 수 다시 표시
	
	gotoxy(0, 1);
	while (1)
	{
		if (feof(fp)) //파일 끝에 도달하면 중지
		{
			break;
		}
		b = fgetc(fp); //읽을때마다 포인터가 뒤로 가는듯 하다
		printf("%c", b);
	}
	fseek(fp, now_pointer, SEEK_SET);
	gotoxy(now_x_pointer, now_y_pointer); //원래 있던 좌표값으로 되돌아감
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
void edit_menu(FILE *fp, int x, int y)
{
	if (1)
	{
		char key; //일단은 단순히 보여주는 것으로만
		int menu = 1;
		again:

		key = getch();
		while (1)
		{
		
			if (key == 244)  //키 입력에 따른 메뉴
			{
				key = getch();
				switch (key)
				{
					//case 72: { //up
					//	
					//}
				case 75: { //left
					menu--;
					edit_sClr(fp, x, y);
					edit_menu(fp, x, y);
					getch();
					break;
				}
				case 77: { //right
					menu++;
					edit_sClr(fp, x, y);
					edit_menu(fp, x, y);
					getch();
					break;
				}
						 //case 80: { //down

						 //}
				default: {
					break;
				}
				}
				if (menu < 1)
				{
					menu = 5 - menu;
				}
				if (menu > 5)
				{
					menu = menu - 5;;
				}
			}

			switch (menu)
			{
				dye(0, LIGHTGREEN, BROWN, ""); //색상 바꾸고
			case 1: {
				dye(0, LIGHTGREEN, BROWN, "");
				gotoxy(6, 0); //끝나는 좌료가 11
				printf(" File ");
				gotoxy(6, 1);
				printf(" New  ");
				gotoxy(6, 2);
				printf(" Open ");
				gotoxy(6, 3);
				printf(" Save ");
				gotoxy(6, 4);
				printf(" eXit ");
				goto again;
				break;
			}
			case 2: {
				dye(0, LIGHTGREEN, BROWN, "");
				gotoxy(14, 0); //끝나는 좌료가 19
				printf(" Edit ");
				gotoxy(14, 1);
				printf(" Book \n mark ");
				
				goto again;
				break;
			}
			case 3: {
				dye(0, LIGHTGREEN, BROWN, "");
				gotoxy(22, 0); //끝나는 좌료가 29
				printf(" Search ");
				gotoxy(22, 0);
				printf(" fInd ");
				goto again;
				break;
			}
			case 4: {
				dye(0, LIGHTGREEN, BROWN, "");
				gotoxy(32, 0); //끝나는 좌료가 39
				printf(" Options ");
				gotoxy(32, 1);
				printf(" Color   ");
				goto again;
				break;
			}
			case 5: {
				dye(0, LIGHTGREEN, BROWN, "");
				gotoxy(42, 0); //끝나는 좌료가 47
				printf(" Help ");
				goto again;
				break;
			}
			default: {

			}
			}
			if (GetAsyncKeyState(VK_F10) & 0x8000) //F10이 다시 눌리면 
			{
				edit_sClr(fp, x, y); //현재 에디팅 하던 상태 그대로 화면만 클리어함
			}
		}

	}
}
void GetfileList(char* path) //해당 위치에 있는 파일들 보여주는 함수 -> path에 따라 다르게
{
	FILE_SEARCH fd;
	char loc[100];
	long handle;
	int result = 1;
	sprintf(loc, "%s*.*", path);
	//handle = _findfirst(".\\*.*", &fd);  //현재 폴더 내 모든 파일을 찾는다.
	handle = _findfirst(loc, &fd); //여기서 찾고싶은 경로 조작해야되는듯
	if (handle == -1)
	{
		printf("!!파일이 없습니다!!\n");
		return;
	}

	while (result != -1)
	{
		printf("File: %s\n", fd.name);
		result = _findnext(handle, &fd);
	}

	_findclose(handle);
	return;
}
int file_size(FILE *fp) //0이면 처음 연 파일 아니면 이미 있던 파일
{
	fseek(fp, 0, SEEK_END); //끝으로
	int pos = ftell(fp); //파일 크기
	rewind(fp);
	return pos; //파일 크기 리턴
}
void save_Line(FILE *fp, char *buffer) //해당 라인 저장
{
	int n_pointer = ftell(fp); //맨 앞자리 포인터
	int last_line = 0;
	while (1)
	{
		if (fgetc(fp) == '\n')
		{
			last_line = 1; //뒤에도 뭔가 있음
			fseek(fp, 1, SEEK_CUR);
			break; //원래 있던 라인의 맨 끝으로 파일 포인터 이동후 다음 라인으로 넘어감
		}
		if (feof(fp))
		{
			last_line = 0; //뒤에 없음
			fseek(fp, 1, SEEK_CUR);
			break; //원래 있던 라인의 맨 끝으로 파일 포인터 이동후 다음 라인으로 넘어감
		}

	}
	int j_x = now_x();
	int i_y = now_y();

	FILE *tmp = fopen("C://UDiT//line_temp.txt", "w+"); //읽기모드로 임시파일 접근
	if (last_line = 1) //뒤에 뭔가 있을때만
	{
		copy_file(fp, tmp); //원래 파일의 다음 라인부터 끝까지 복사

	}


	fseek(fp, n_pointer, SEEK_SET); //아까 수정하려는 라인의 맨 앞자리 포인터로 접근함
	fputs(buffer, fp); //수정한 라인 파일에 저장
	fflush(fp); //현재 시스템 입력 버퍼 비워줌



	_chsize(_fileno(fp), ftell(fp)); //버퍼의 마지막 이후를 싹 다 없앰 (\0부터 끝까지)
	int l_pointer = ftell(fp);//맨 마지막 포인터를 저장함



	fflush(tmp); //현재 시스템 입력 버퍼 비워줌
	fseek(fp, 0, SEEK_END); //혹시 모르니까 파일 제일 끝으로 보냄
	int last_pointer = ftell(fp);//맨 마지막 포인터를 저장함
	fseek(tmp, 0, SEEK_SET); //아까 복사했던 파일의 포인터를 맨 앞으로

	if (last_line = 1) //뒤에 뭔가 있을때만
	{
		copy_file(tmp, fp); //tmp에서 받아와서 fp로 추가함 (아까 복사했던 파일)
	}
	fclose(tmp);
	fseek(fp, l_pointer+1, SEEK_SET); //수정한 라인의 맨 끝 다음으로 (다음줄) 파일 포인터 보냄
}

void save_File() //Save_as
{
	int fail;
	int b;
	char loc[100] = { "C://UDiT//" }; //파일 저장 경로
	char temp_loc[20] = { "C://UDiT//temp.txt" }; //임시 파일 저장 경로
	FILE *in = fopen("C://UDiT//temp.txt", "rb");
	FILE *out = NULL;
	char name[50];

	char loca[100];
	char folder[100];
	dye(0, LIGHTBLUE, BLACK, "");
	gotoxy(39, 26);
	printf("파일을 저장할 위치: ");
	scanf("%s", name); //이름
	getchar();
	strcat(name, ".txt"); //확장자
	strcat(loc, name); //합성

					   //FILE *bmk = fopen("C://UDiT//bookmarks.txt", "r+");
	FILE *ref = fopen("C://UDiT//recentfiles.txt", "r+");
	/*if (bmkn == 1)
	{
	fprintf(bmk, " %s\n", loc);
	}*/
	fseek(ref, 0, SEEK_END);

	fprintf(ref, "%s\n", loc);

	//fflush(bmk);
	fflush(ref);
	//fclose(bmk);
	fclose(ref);
	sprintf(loca, "%s", loc); //변수로 사용할 수 있게 함

	out = fopen(loca, "wb"); //파일포인터 읽기, 쓰기로 접근

	copy_file(in, out); // in에서 out으로 복사

	fclose(in); // 파일 닫기
	fclose(out);
	//bmkn = 1;

	system("cls");
	main();
	
	return 0;
}
void copy_file(FILE *in, FILE *out) //미리 입출력 fopen해줘야되고 out의 파일 포인터부터 들어감
{
	char b;
	while (1) //파일 복사
	{
		if (feof(in)) //파일 끝에 도달하면 중지
		{
			break;
		}
		b = fgetc(in); //읽을때마다 포인터가 뒤로 가는듯 하다
		fputc(b, out);
	}
}
int open_File()
{
	int i;
	int t;
	char b;
	char temp_path[100] = { "C://UDiT//" };//찾으려는 경로
	char file_path[100];
	char temp[50];
	char load[1000];	
	//파일 이름 받기
	gotoxy(30, 15);
	dye(0, WHITE, BLACK, "오픈하려는 파일 위치 : ");
	scanf("%s", temp);
	strcat(temp, ".txt"); //확장자
	strcat(temp_path, temp); //합성
	sprintf(file_path, "%s", temp_path);					//temp_path를 file_path로 sprintf
	FILE *in = fopen(file_path, "rb");
	if (in == NULL)
	{ //파일 없으면
		printf("파일이 없습니다!\n");
		_sleep(500);
		system("cls");
		main();
	}
	FILE *tmp = fopen("C://UDiT//temp.txt", "wb");

	while (1) //파일 복사
	{
		if (feof(in)) //파일 끝에 도달하면 중지
		{
			break;
		}
		b = fgetc(in); //읽을때마다 포인터가 뒤로 가는듯 하다
		fputc(b, tmp);
	}
	//while ((t = fgetc(in)) != EOF) // 원본 1바이트를 얻는다.
	//{
	//	fputc(t, tmp); // 그 1바이트를 사본에 쓴다.
	//}
	fclose(in); // 수정하려는 파일 복사 완료 => 닫기
	fclose(tmp); // 다른 모드로 열려고 함
	system("cls");
	FILE *tmpa = fopen("C://UDiT//temp.txt", "r+");
	gotoxy(0, 1);

	//시연때 에러난 부분
	//while (1)
	//{
	//	if (feof(tmpa) != 0) break;
	//	b = fgetc(tmpa);
	//	printf("%c", b);

	//	edit_Interface();

	//	fclose(tmpa);
	//	editor();


	//	return 0;
	//}

	while (1)
	{
		if (feof(tmpa) != 0) break;
		b = fgetc(tmpa);
		printf("%c", b);
		
	}

	edit_Interface();

	fclose(tmpa);
	editor();
	return 0;
}
int open_e_File(FILE *in)
{
	char b;
	FILE *out = fopen("C://UDiT//temp.txt", "wb");

	while (1) //파일 복사
	{
		if (feof(in)) //파일 끝에 도달하면 중지
		{
			break;
		}
		b = fgetc(in); //읽을때마다 포인터가 뒤로 가는듯 하다
		fputc(b, out);
	}
	fclose(in); // 수정하려는 파일 복사 완료 => 닫기
	fclose(out); // 다른 모드로 열려고 함
	system("cls");
	FILE *tmpa = fopen("C://UDiT//temp.txt", "r+");
	gotoxy(0, 1);
	while (1) //파일 옮기기, 뿌리기
	{
		if (feof(tmpa) != 0) break;
		b = fgetc(tmpa);
		printf("%c", b);
	}
	rewind(tmpa);
	fclose(tmpa);
	edit_Interface();

	editor();


	return 0;
}
int editor() //에디팅 끝난 다음에 fclose()
{
	int i;
	char ch;
	char line_buffer[123]; //입력 120칸, 나머지는 엔터용 \n\n\0 or 라인 저장용 \n\0
	int line = 1;
	int pointer = 0;
	int t_point;
	int last_ch = -1;

	FILE *tmp = fopen("C://UDiT//temp.txt", "r+"); //에디터는 무조건 temp 파일에서만

	now_Line(line); //현재 줄 수 확인

	gotoxy(0, 1);

	if (file_size(tmp) != 0) //파일이 원래 있던 파일이면
	{
		fseek(tmp, 0, SEEK_SET);
		while (1) //파일 복사 //첫줄 복사
		{
			ch = fgetc(tmp);
			if ((ch == '\n') || (feof(tmp) != 0)) //엔터 있을때까지 (버퍼 크기는 120)
			{
				line_buffer[pointer] = '\0'; // 마지막 \n 문자 null로 초기화
				break;
			}
			line_buffer[pointer] = ch; //첫줄 문자들 버퍼로 저장					
			pointer++; //다음 포인터
			last_ch++; // 문자 길이 늘어남

		}
		fseek(tmp, 0, SEEK_SET); //파일 포인터 앞으로 넘겨둠

	//	pointer = 0;
	}
	//디버깅용
	//i = now_y();
	//gotoxy(10, 14);
	//printf("main %d = pointer, %d is last_ch", pointer, file_size(tmp));
	//gotoxy(pointer, i); //거기로 콘솔 커서 옮기기
	//system("pause");
	gotoxy(pointer, now_y()); //확실히 하려고
	while (1) //실제로 에디팅 시작
	{
		while ((ch = getch()) != '\n')
		{
			if (key_ck(ch) != 0)  //입력 가능한 문자일때만
			{
				if ((pointer > last_ch) && (pointer != 121)) //맨 오른쪽이거나 다음 쓸 곳이 \n자리가 아닐때, 다음 가리키는 곳이 255가 아닐때
				{

					line_buffer[pointer] = ch;
					printf("%c", ch);
					pointer++;
					last_ch++;
				}
				else if ((last_ch != 121) && (pointer <= last_ch)) //중간에 편집할때 -> 이때 마지막 문자가 255로 x
				{
					for (i = last_ch; i >= pointer; i--)
					{
						line_buffer[i + 1] = line_buffer[i]; //오른쪽으로 옮기고
					}
					last_ch++;
					line_buffer[pointer] = ch; //그 자리에 문자 넣고
					for (i = pointer; i <= last_ch; i++)
					{
						printf("%c", line_buffer[i]);
						//printf("\n%c, %d\n", line_buffer[i], i); //넣은 자리부터 끝까지 다시 출력
					}
					pointer++;
					gotoxy(pointer, now_y());//원래 자리로 돌아감
				}

			}
			if (((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(0x4C) & 0x8000))) //ctrl 이랑 l키 눌릴때
			{
				if (pointer > 0)
				{
					pointer--; //포인터를 왼쪽으로
					i = now_y();	
					gotoxy(pointer, i); //거기로 콘솔 커서 옮기기
				}
			}
			if (((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(0x52) & 0x8000))) //ctrl 이랑 r키 눌릴때
			{
				if (pointer <= last_ch )
				{
					pointer++; //포인터를 오른쪽으로
					i = now_y();
					gotoxy(pointer, i); //거기로 콘솔 커서 옮기기
				}
			}
			
			if ((GetAsyncKeyState(VK_BACK) & 0x8000) && (pointer > 0))//백스페이스 
			{
				pointer--;
				i = now_y();
				gotoxy(10, 12);
				//printf("back %d = pointer, %d is last_ch", pointer, last_ch);
				gotoxy(pointer, i); //거기로 콘솔 커서 옮기기
				if (last_ch < pointer) //제일 오른쪽일때
				{
					gotoxy(last_ch, now_y());
					printf(" ");
					gotoxy(last_ch, now_y());
					last_ch--;
					i = now_y();
					gotoxy(10, 16);
					//printf("back1 %d = pointer, %d is last_ch", pointer, last_ch);
					gotoxy(pointer, i); //거기로 콘솔 커서 옮기기
				}
				else
				{

					gotoxy(pointer, now_y());
					for (i = pointer; i <= last_ch; i++)
					{
						printf(" ");
					}
					for (i = pointer + 1; i <= last_ch; i++)
					{
						line_buffer[i - 1] = line_buffer[i];
					}
					last_ch--;
					gotoxy(pointer, now_y());
					for (i = pointer; i <= last_ch; i++)
					{
						printf("%c", line_buffer[i]);
					}
					gotoxy(pointer, now_y());
					i = now_y();
					gotoxy(10, 18);
					//printf("back2 %d = pointer, %d is last_ch", pointer, last_ch);
					gotoxy(pointer, i); //거기로 콘솔 커서 옮기기
				}
			}
			if (GetAsyncKeyState(VK_HOME) & 0x8000) //홈키
			{
				getchar();
				
				pointer = 0;
				gotoxy(pointer, now_y());
			}
			if (GetAsyncKeyState(VK_END) & 0x8000) //엔드키
			{
				getchar();
				pointer = last_ch + 1;
				gotoxy(pointer, now_y());
			}

			//if (GetAsyncKeyState(VK_LEFT) & 0x8000)  //키보드 방향키 왼쪽->두칸감
			//{
			//	getchar();
			//	getch();
			//	if (pointer > 0)
			//	{
			//		pointer--;
			//		gotoxy(pointer, now_y());
			//	}
			//}
			//if (GetAsyncKeyState(VK_RIGHT) & 0x8000) //키보드 방향키 오른쪽 ->값 입력됨
			//{
			//	getchar();
			//	if ((last_ch - pointer) >= -1)
			//	{
			//		pointer++;
			//		gotoxy(pointer, now_y());
			//	}
			//}

			if ((GetAsyncKeyState(VK_RETURN) & 0x8000)) //엔터 입력
			{					//중간에 편집한거는 끝에 \n \0있으니까 확인

				int y_point = now_y();//현재 좌표값 저장
				line_buffer[last_ch + 1] = '\n';
				//line_buffer[last_ch + 2] = '\n'; //엔터니까 다음 줄 처음으로 감
				line_buffer[last_ch + 2] = '\0';
				save_Line(tmp, line_buffer); // 라인 저장
				pointer = 0;
				last_ch = -1;
				line++; //라인 추가
				print_whole_file(tmp, line);
				gotoxy(pointer, y_point + 1); //커서를 다음 첫줄로		 
			}
			if (((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_RETURN) & 0x8000))) //중간에 라인 추가해주는 엔터 입력
			{					

				int y_point = now_y();//현재 좌표값 저장
				line_buffer[last_ch + 1] = '\n';
				line_buffer[last_ch + 2] = '\n'; //다음 줄 처음으로 감
				line_buffer[last_ch + 3] = '\0';
				save_Line(tmp, line_buffer); // 라인 저장
				pointer = 0;
				last_ch = -1;
				line++; //라인 추가
				print_whole_file(tmp, line);
				gotoxy(pointer, y_point + 1); //커서를 다음 첫줄로		 
			}
			if (((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(0x53) & 0x8000))) //ctrl+s
			{
				char end_sel;
				int k = now_y();
				gotoxy(70, 0);
				dye(0, RED, BLUE, "저장하시겠습니까? (Y/N) >>");
				getchar();
				end_sel = getchar();
				line_buffer[pointer] = '\0';
				switch (end_sel)
				{
				case 'Y': { //현재 파일 포인터는 그 라인 제일 앞
					line_buffer[last_ch] = '\n';
					line_buffer[last_ch + 1] = '\0';

					save_Line(tmp, line_buffer);
					
					save_File();
				}
				case 'y': {
					line_buffer[last_ch] = '\n';
					line_buffer[last_ch + 1] = '\0';

					save_Line(tmp, line_buffer);

					save_File();
				}
				case 'N': {
					gotoxy(70, 0);
					dye(0, RED, BLUE, "종료하시겠습니까? (Y/N) >>");
					getchar();
					end_sel = getchar();
					switch (end_sel)
					{
					case 'Y': {
						system("cls");
						main();
					}
					case 'y': {
						system("cls");
						main();
					}
					case 'N': {
						edit_sClr(tmp, pointer, k);
						break;
					}
					case 'n': {
						edit_sClr(tmp, pointer, k);
						break;
					}
					}
					break;
				}
				case 'n': {
					gotoxy(70, 0);
					dye(0, RED, BLUE, "종료하시겠습니까? (Y/N) >>");
					getchar();
					end_sel = getchar();
					switch (end_sel)
					{
					case 'Y': {
						system("cls");
						main();
					}
					case 'y': {
						system("cls");
						main();
					}
					case 'N': {
						edit_sClr(tmp, pointer, k);
						break;
					}
					case 'n': {
						edit_sClr(tmp, pointer, k);
						break;
					}
					}
					break;
				}
				default:
					
					break;
				}
			}
			
			if (((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(0x55) & 0x8000))) //ctrl+u 윗 화살표
			{
				pointer--;
				gotoxy(pointer, now_y());
				//line--;
				//now_Line(line);
				//line_buffer[last_ch + 1] = '\n';
				//line_buffer[last_ch + 2] = '\0';
				//fputs(line_buffer, tmp); //입력 받은거 파일에 저장
				//fflush(tmp); //현재 시스템 입력 버퍼 비워줌
				//last_ch = 0;
				//int count = 0;
				//while (i <= line) //윗 라인 찾아서 버퍼에 저장
				//{

				//	while (1)
				//	{
				//		count++; //최종적으로 line번째 라인의 끝(\n 전) 까지의 크기
				//		if (ch = fgetc(tmp) == '\n')
				//		{
				//			fseek(tmp, 2, SEEK_CUR);//파일 말단에 \N 있어서 다음줄 앞으로
				//			count = count + 1;//\N 있어서
				//			break;
				//		}
				//		if (i == 3)
				//		{
				//			last_ch++; //최종적으로 line번째 라인의 문자 수
				//		}
				//	}
				//	i++;
				//}
				//fseek(tmp, count - (last_ch - 1), SEEK_SET); //line 번째 라인의 첫번째 지점
				//for (i = 0; i <= last_ch - 1; i++)
				//{
				//	line_buffer[i] = fgetc(tmp); //그 라인 받아오기
				//}
				//fseek(tmp, -(last_ch - 1), SEEK_CUR); //그 줄의 첫 포인터로 옮기기 => 그래서 나중에 사용할 수 있도록


				//pointer = 0;
			}
			if (GetAsyncKeyState(VK_F10) & 0x8000)
			{
				edit_menu(tmp, pointer, now_y());
			}

			if (((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(0x42) & 0x8000)))//ctrl+b
			{
				i = now_y();
				
				gotoxy(60, 0);
				//getch();
				dye(0, RED, BLUE, "현재 구간을 북마크로 저장하시겠습니까? (Y/N) >>");

				ch = getchar();
				switch (ch)
				{
				case 'Y':
				{
					//bmkn = 1;
					FILE *bmk = fopen("C://UDiT//bookmarks.txt", "r+");
					fseek(bmk, 0, SEEK_END);
					fprintf(bmk, "%d %d\n", pointer, line);
					fflush(bmk);
					fclose(bmk);
					gotoxy(60, 0);
					dye(0, DARKGRAY, LIGHTBLUE, ' ');
					printf("                            ");
					getch();
					dye(0, LIGHTGRAY, BLACK, ' ');
					gotoxy(pointer, i);
					
					break;
				}
				case 'X':
				{
					gotoxy(60, 0);
					dye(0, DARKGRAY, LIGHTBLUE, ' ');
					printf("                            ");
					getch();
					dye(0, LIGHTGRAY, BLACK, ' ');
					gotoxy(pointer, i);
					break;
				}
				default: break;
				}

				gotoxy(pointer, i); //거기로 콘솔 커서 옮기기

			}
		}
	}
	return 0;
}
int new_File() //newFile은 단순히 경로 없으면 경로 만드는걸로 하면 안될까?
{
	FILE *tmp = NULL;
	tmp = fopen("C://UDiT//temp.txt", "w+"); //이전에 사용하던거 있으면 지우고 새로 열기
	edit_Interface();
	editor();

	return 0;
}
int find_File() //시간 되면 리스트 출력 다른 경로에서도 찾자
{
	int i;
	char loc[100] = { "C://UDiT//" }; //찾으려는 파일 경로
	char temp[50];//파일이름
	char loca[100];
	char sel_o;
	gotoxy(4, 4);
	printf("검색:");
	scanf("%s", temp);
	getchar();
	strcat(temp, ".txt"); //파일 확장자
	strcat(loc, temp);
	sprintf(loca, "%s", loc); //변수로 사용할 수 있게 함
	FILE *fr = fopen(loca, "r+");
	if (fr == NULL)
	{ //파일 없으면
		printf("파일이 없습니다!\n");
		_sleep(500);
		system("cls");
		main();
	}
	printf("파일을 여시겠습니까? (Y/N) ");
	sel_o = getchar();
	switch (sel_o)
	{
	case 'Y': {
		open_e_File(fr);
	}
	case 'N': {
		fclose(fr);
		system("cls");
		main();
		break;
	}
	default:
		break;
	}
}
int file_Manager()
{
	char path[100] = "C://UDiT//";
	GetfileList(path);
	system("pause");
	main();
}