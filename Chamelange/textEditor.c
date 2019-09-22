#include <stdio.h>
#include "interfaces.h"
#include "cursor.h"
#include "fileManage.h"
#include "textEditor.h"

//#define COLORS


int new_File() //newFile은 단순히 경로 없으면 경로 만드는걸로 하면 안될까?
{
	FILE* tmp = NULL;
	tmp = fopen("./temp.txt", "w+"); //이전에 사용하던거 있으면 지우고 새로 열기
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

	FILE* tmp = fopen("./temp.txt", "r+"); //에디터는 무조건 temp 파일에서만

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
				if (pointer <= last_ch)
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
					FILE* bmk = fopen("./bookmarks.txt", "r+");
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

void save_Line(FILE* fp, char* buffer) //해당 라인 저장
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

	FILE* tmp = fopen("./line_temp.txt", "w+"); //읽기모드로 임시파일 접근
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
	fseek(fp, l_pointer + 1, SEEK_SET); //수정한 라인의 맨 끝 다음으로 (다음줄) 파일 포인터 보냄
}

void print_whole_file(FILE* fp, int line) //수정된 파일을 다시 표시해줌
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

void edit_sClr(FILE* fp, int x, int y) //x랑 y는 각각 화면 클리어 할 당시의 포인터, 라인 위치
{
	int now_x_pointer = now_x();
	int now_y_pointer = now_y();
	system("cls");
	edit_Interface();
	gotoxy(0, 1);
	print_whole_file(fp, y);
}

void edit_menu(FILE* fp, int x, int y)
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