#include <stdio.h>
#include <unistd.h>
#include "./interfaces.h"
#include "./cursor.h"
#include "./fileManage.h"
#include "./textEditor.h"
#include "interrupts.h"
#include "bookmaark.h"
//#include "main.c"

//#define COLORS




int editor() //에디팅 끝난 다음에 fclose()
{
	/*
	int i;
	char ch;
	char line_buffer[max_line_buffer_size]; //입력 max칸, 나머지는 엔터용 \n\n\0 or 라인 저장용 \n\0
	int line = 1;
	int pointer = 0;
	int cur_point;
	int last_ch = -1;
	*/

	int ch;
	e_Infos cur_info;	//contains editor's info
	cur_info.last_ch = 0;
	cur_info.pointer = 0;
	cur_info.last_line = 0;
	cur_info.cur_line = 1;
	
	///////INITIALIZEING/////////////
	//editor를 열기 전에 파일 포인터 열고나서 뭘 해야되지 않을까
	FILE* tmp = fopen("./temp.txt", "r+"); //에디터는 무조건 temp 파일에서만

	//cur_Line(line, COLOR_WHITE, COLOR_BLACK); //check current line

	gotoxy(stdscr, 0, 1);

	if (file_size(tmp) != 0) //if file exsists
	{
		fseek(tmp, 0, SEEK_SET);
		while (1) //copy the file's first line to line buffer -> need to be changed to get every lines
		{
			ch = fgetc(tmp);
			if ((ch == '\n') || (feof(tmp) != 0)) //while fp meets enter or end of file
			{
				cur_info.line_buffer[cur_info.pointer] = '\0'; // initialize last char with NULL -> why?????????
				break;
			}
			cur_info.line_buffer[cur_info.pointer] = ch; //첫줄 문자들 버퍼로 저장					
			cur_info.pointer++; //set pointer to last of line
			cur_info.last_ch++; // count the size of the line

		}
		fseek(tmp, 0, SEEK_SET); //move file pointer to the first of line
		cur_info.pointer = 0;	//points to first of line
		print_whole_file(tmp, cur_info.cur_line);
	}
	//for baremetal debug******
	//i = now_y();
	//gotoxy(10, 14);
	//printf("main %d = pointer, %d is last_ch", pointer, file_size(tmp));
	//gotoxy(pointer, i); //거기로 콘솔 커서 옮기기
	//system("pause");
	gotoxy(stdscr,cur_info.pointer, 1); //move cursor to first of file

	//////////INITIALIZING FINISHED///////////////////////



/*
	//////////ACTUAL EDITING STARTS FROM HERE///////////////
	while (1)
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
					gotoxy(stdscr, pointer, now_y(stdscr));//원래 자리로 돌아감
				}

			}

			//////////BELOW ONES ARE SPECIAL CASES/////////////////
			/////////CAN BE REPLACED AS interrupts/key_ck()  ///////////
			if (ch == KEY_F(0)) //ctrl 이랑 l키 눌릴때
			{
				if (pointer > 0)
				{
					pointer--; //포인터를 왼쪽으로
					i = now_y(stdscr);
					gotoxy(stdscr, pointer, i); //거기로 콘솔 커서 옮기기
				}
			}
			if (ch == KEY_F(1)) //ctrl 이랑 r키 눌릴때
			{
				if (pointer <= last_ch)
				{
					pointer++; //포인터를 오른쪽으로
					i = now_y(stdscr);
					gotoxy(stdscr,pointer, i); //거기로 콘솔 커서 옮기기
				}
			}

			if (ch == KEY_F(2))//백스페이스 
			{
				pointer--;
				i = now_y(stdscr);
				gotoxy(stdscr, 10, 12);
				//printf("back %d = pointer, %d is last_ch", pointer, last_ch);
				gotoxy(stdscr, pointer, i); //거기로 콘솔 커서 옮기기
				if (last_ch < pointer) //제일 오른쪽일때
				{
					gotoxy(stdscr,last_ch, now_y(stdscr));
					printf(" ");
					gotoxy(stdscr,last_ch, now_y(stdscr));
					last_ch--;
					i = now_y(stdscr);
					gotoxy(stdscr, 10, 16);
					//printf("back1 %d = pointer, %d is last_ch", pointer, last_ch);
					gotoxy(stdscr, pointer, i); //거기로 콘솔 커서 옮기기
				}
				else
				{

					gotoxy(stdscr,pointer, now_y(stdscr));
					for (i = pointer; i <= last_ch; i++)
					{
						printf(" ");
					}
					for (i = pointer + 1; i <= last_ch; i++)
					{
						line_buffer[i - 1] = line_buffer[i];
					}
					last_ch--;
					gotoxy(stdscr,pointer, now_y(stdscr));
					for (i = pointer; i <= last_ch; i++)
					{
						printf("%c", line_buffer[i]);
					}
					gotoxy(stdscr,pointer, now_y(stdscr));
					i = now_y(stdscr);
					gotoxy(stdscr, 10, 18);
					//printf("back2 %d = pointer, %d is last_ch", pointer, last_ch);
					gotoxy(stdscr, pointer, i); //거기로 콘솔 커서 옮기기
				}
			}
			if (ch == KEY_F(3)) //홈키
			{
				getchar();

				pointer = 0;
				gotoxy(stdscr, pointer, now_y(stdscr));
			}
			if (ch == KEY_F(4)) //엔드키
			{
				getchar();
				pointer = last_ch + 1;
				gotoxy(stdscr, pointer, now_y(stdscr));
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

			if (ch == KEY_F(5)) //엔터 입력
			{					//중간에 편집한거는 끝에 \n \0있으니까 확인

				int y_point = now_y(stdscr);//현재 좌표값 저장
				line_buffer[last_ch + 1] = '\n';
				//line_buffer[last_ch + 2] = '\n'; //엔터니까 다음 줄 처음으로 감
				line_buffer[last_ch + 2] = '\0';
				save_Line(tmp, line_buffer); // 라인 저장
				pointer = 0;
				last_ch = -1;
				line++; //라인 추가
				print_whole_file(tmp, line);
				gotoxy(stdscr, pointer, y_point + 1); //커서를 다음 첫줄로		 
			}
			if (ch == KEY_F(6)) //중간에 라인 추가해주는 엔터 입력
			{

				int y_point = now_y(stdscr);//현재 좌표값 저장
				line_buffer[last_ch + 1] = '\n';
				line_buffer[last_ch + 2] = '\n'; //다음 줄 처음으로 감
				line_buffer[last_ch + 3] = '\0';
				save_Line(tmp, line_buffer); // 라인 저장
				pointer = 0;
				last_ch = -1;
				line++; //라인 추가
				print_whole_file(tmp, line);
				gotoxy(stdscr, pointer, y_point + 1); //커서를 다음 첫줄로		 
			}
			if (ch == KEY_F(7)) //ctrl+s
			{
				char end_sel;
				int k = now_y(stdscr);
				gotoxy(stdscr, 70, 0);
				//dye(0, COLOR_WHITE, COLOR_BLACK, "저장하시겠습니까? (Y/N) >>");
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
					gotoxy(stdscr, 70, 0);
					//dye(0, COLOR_WHITE, COLOR_BLACK, "종료하시겠습니까? (Y/N) >>");
					getchar();
					end_sel = getchar();
					switch (end_sel)
					{
					case 'Y': {
						system("cls");
						exit(1);
					}
					case 'y': {
						system("cls");
						exit(1);
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
					gotoxy(stdscr, 70, 0);
					//dye(0, COLOR_WHITE, COLOR_BLACK, "종료하시겠습니까? (Y/N) >>");
					getchar();
					end_sel = getchar();
					switch (end_sel)
					{
					case 'Y': {
						system("cls");
						exit(1);
					}
					case 'y': {
						system("cls");
						exit(1);
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

			if (ch == KEY_F(8)) //ctrl+u 윗 화살표
			{
				pointer--;
				gotoxy(stdscr, pointer, now_y(stdscr));
				//line--;
				//cur_Line(line);
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
			if (KEY_F(9))
			{
				edit_menu(tmp, pointer, now_y(stdscr));
			}

			if (ch == KEY_F(10))//ctrl+b
			{
				i = now_y(stdscr);

				gotoxy(stdscr, 60, 0);
				//getch();
				//dye(0, COLOR_WHITE, COLOR_BLACK, "현재 구간을 북마크로 저장하시겠습니까? (Y/N) >>");

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
					gotoxy(stdscr, 60, 0);
					//dye(0, COLOR_WHITE, COLOR_BLACK, ' ');
					printf("                            ");
					getch();
					//dye(0, COLOR_WHITE,COLOR_BLACK, ' ');
					gotoxy(stdscr, pointer, i);

					break;
				}
				case 'X':
				{
					gotoxy(stdscr, 60, 0);
					//dye(0, COLOR_WHITE, COLOR_BLACK, ' ');
					printf("                            ");
					getch();
					//dye(0, COLOR_WHITE,COLOR_BLACK, ' ');
					gotoxy(stdscr, pointer, i);
					break;
				}
				default: break;
				}

				gotoxy(stdscr, pointer, i); //거기로 콘솔 커서 옮기기

			}
		}
	}
*/
	while (1)
	{
		ch = editor_key_ck(&cur_info);
		if(ch != 0){	//if it gets normal character -> input
			if(cur_info.last_ch < max_line_buffer_size-2)	// # of total character in under max line buffer
			{
				//fputc(ch, tmp);
				//return 0;
				//exit(0);
				if (cur_info.pointer == cur_info.last_ch)
				{
					addch(ch);	//print character to screen  ---->>> refresh() to print in screen
					cur_info.line_buffer[cur_info.pointer++] = ch;
					cur_info.last_ch++;
					gotoxy(stdscr, cur_info.pointer, cur_info.cur_line);
				}
				if((cur_info.pointer < cur_info.last_ch))	//edit in middle of line
				{
					for(int i= cur_info.last_ch; i > cur_info.pointer-1; i--)	//shift to right matrix
						cur_info.line_buffer[i+1] = cur_info.line_buffer[i];
					cur_info.line_buffer[cur_info.pointer] = ch;
					cur_info.last_ch++;
					for(int j=cur_info.pointer; j <cur_info.last_ch+1; j++)	//print new char~ last char
						{
							addch(cur_info.line_buffer[j]);
							gotoxy(stdscr, j, now_y(stdscr));	//moveto right side
						}
					cur_info.pointer++;	//move to next point
					gotoxy(stdscr, cur_info.pointer, now_y(stdscr));		//back to where it was
				}
				
			}
			refresh();
		}
		
	}
	return 0;
}

void save_Line(FILE* fp, char* buffer) //해당 라인 저장
{
	int n_pointer = ftell(fp); //맨 앞자리 포인터 (2019.9.22)왜냐면 마지막으로 원본 파일에 저장한 위치이기 때문
	int end_of_line = 0;
	while (1)				//move file pointer to end of line
	{
		if (fgetc(fp) == '\n')
		{
			end_of_line = 1; //ther is something in the back
			break; 
		}
		if (feof(fp))
		{
			end_of_line = 0; //there is nothing in the back
			break; 
		}
		fseek(fp, 1, SEEK_CUR);		
	}

	int j_x = now_x(stdscr);
	int i_y = now_y(stdscr);

	FILE* tmp = fopen("./line_temp.txt", "w+"); //access to line_temp file with write permission
	if (end_of_line = 1) 
	{
		fseek(fp, 1, SEEK_CUR);	//move to next pointer
		copy_file(fp, tmp); //copy (end of current line) ; since fp's file pointer is at end of current line
	}

	fseek(fp, n_pointer, SEEK_SET); //아까 수정하려는 라인의 맨 앞자리 포인터로 접근함
	fputs(buffer, fp); //수정한 라인 파일에 저장
	//fflush(fp); //현재 시스템 입력 버퍼 비워줌



	//_chsize(_fileno(fp), ftell(fp)); //버퍼의 마지막 이후를 싹 다 없앰 (\0부터 끝까지)
	int l_pointer = ftell(fp);//맨 마지막 포인터를 저장함



	fflush(tmp); //현재 시스템 입력 버퍼 비워줌
	fseek(fp, 0, SEEK_END); //혹시 모르니까 파일 제일 끝으로 보냄
	int last_pointer = ftell(fp);//맨 마지막 포인터를 저장함
	fseek(tmp, 0, SEEK_SET); //아까 복사했던 파일의 포인터를 맨 앞으로

	if (end_of_line = 1) //뒤에 뭔가 있을때만
	{
		copy_file(tmp, fp); //tmp에서 받아와서 fp로 추가함 (아까 복사했던 파일)
	}
	fclose(tmp);
	fseek(fp, l_pointer + 1, SEEK_SET); //수정한 라인의 맨 끝 다음으로 (다음줄) 파일 포인터 보냄
}

void print_whole_file(FILE* fp, int line) //수정된 파일을 다시 표시해줌
{
	int now_x_pointer = now_x(stdscr); //원래 있던 좌표 받아옴
	int now_y_pointer = now_y(stdscr);
	int now_pointer = ftell(fp); //현재 파일 포인터 
	char b;
	fseek(fp, 0, SEEK_SET); //파일의 처음  포인터로 넘어감
	clear();
	edit_Interface();
	cur_Line(line, COLOR_WHITE, COLOR_BLACK); //라인 수 다시 표시
	gotoxy(stdscr, 0, 1);
	while (1)
	{
		if (feof(fp)) //파일 끝에 도달하면 중지
			break;
		b = fgetc(fp); //읽을때마다 포인터가 뒤로 가는듯 하다
		addch(b);
	}
	fseek(fp, now_pointer, SEEK_SET);
	gotoxy(stdscr, now_x_pointer, now_y_pointer); //원래 있던 좌표값으로 되돌아감
}

void edit_sClr(FILE* fp, int x, int y) //x랑 y는 각각 화면 클리어 할 당시의 포인터, 라인 위치
{
	int now_x_pointer = now_x(stdscr);
	int now_y_pointer = now_y(stdscr);
	system("cls");
	edit_Interface();
	gotoxy(stdscr,0, 1);
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
				//dye(0, COLOR_WHITE, COLOR_BLACK, ""); //색상 바꾸고
			case 1: {
				//dye(0, COLOR_WHITE, COLOR_BLACK, "");
				gotoxy(stdscr,6, 0); //끝나는 좌료가 11
				printf(" File ");
				gotoxy(stdscr,6, 1);
				printf(" New  ");
				gotoxy(stdscr,6, 2);
				printf(" Open ");
				gotoxy(stdscr,6, 3);
				printf(" Save ");
				gotoxy(stdscr,6, 4);
				printf(" eXit ");
				goto again;
				break;
			}
			case 2: {
				//dye(0, COLOR_WHITE, COLOR_BLACK, "");
				gotoxy(stdscr,14, 0); //끝나는 좌료가 19
				printf(" Edit ");
				gotoxy(stdscr,14, 1);
				printf(" Book \n mark ");

				goto again;
				break;
			}
			case 3: {
				////dye(0, COLOR_WHITE, COLOR_BLACK, "");
				gotoxy(stdscr,22, 0); //끝나는 좌료가 29
				printf(" Search ");
				gotoxy(stdscr,22, 0);
				printf(" fInd ");
				goto again;
				break;
			}
			case 4: {
				//dye(0, COLOR_WHITE, COLOR_BLACK, "");
				gotoxy(stdscr, 32, 0); //끝나는 좌료가 39
				printf(" Options ");
				gotoxy(stdscr,32, 1);
				printf(" Color   ");
				goto again;
				break;
			}
			case 5: {
				//dye(0, COLOR_WHITE, COLOR_BLACK, "");
				gotoxy(stdscr,42, 0); //끝나는 좌료가 47
				printf(" Help ");
				goto again;
				break;
			}
			default: {

			}
			}
			if (KEY_F(10) == menu) //F10이 다시 눌리면 
			{
				edit_sClr(fp, x, y); //현재 에디팅 하던 상태 그대로 화면만 클리어함
			}
		}

	}
}

void editor_LEFT(e_Infos* cur_info)
{
	if(cur_info->pointer > 0)
	{
		cur_info->pointer--;
		gotoxy(stdscr, cur_info->pointer, cur_info->cur_line);
	}
}

void editor_RIGHT(e_Infos* cur_info)
{
	if(cur_info->pointer < cur_info->last_ch)
	{
		cur_info->pointer++;
		gotoxy(stdscr, cur_info->pointer, cur_info->cur_line);
	}
}

void editor_DOWN(e_Infos* cur_info)
{
	
}
void editor_UP(e_Infos* cur_info)
{

}

void editor_HOME(e_Infos* cur_info)
{

}
void editor_BACKSP(e_Infos* cur_info)
{
	/* //sudo code
	if (line buffer's index > 0)
		delete current character
		move to left side and delete character
		lin buffer --
	else
		return 
	
	*/
}
void editor_ENTER(e_Infos* cur_info)
{
	/* //sudo code
	if (line buffer's index != line's last index)
		save '\n' to cur_index+1
		for cur_index ~ line's last index
			copy matrix
		save cur_line & next line (cur_index become first index of new line)
	else (cur_index == last index)
		save cur_line
	*/
}
void editor_DEL(e_Infos* cur_info)
{

}
void editor_END(e_Infos* cur_info)
{

}

int editor_key_ck(e_Infos* cur_info)		//only for editor
{
	int key;
	nonl();
	
	key = getch();			//if you want to get ch from specific window then use wgetch(WINDOW* )
	
	switch (key)
	{
		case ctrl('s'):		//crtl+s: save current state
			save_cur_line();
			return 0;
		case ctrl('x'):		// save and exit
			save_n_exit();
			return 0;
		case ctrl('b'):		//add bookmark
			create_bookmark();
			return 0;
		case KEY_BACKSPACE:
			editor_BACKSP(cur_info);
			return 0;
		case KEY_ENTER:	
			editor_ENTER(cur_info);
			return 0;
		case KEY_LEFT:
			editor_LEFT(cur_info);
			return 0;
		case KEY_RIGHT:
			editor_RIGHT(cur_info);
			return 0;
		case KEY_UP:
			editor_UP(cur_info);
			return 0;
		case KEY_DOWN:
			editor_DOWN(cur_info);
			return 0;
		case KEY_HOME:
			editor_HOME(cur_info);
			return 0;
		case KEY_DL:
			editor_DEL(cur_info);
			return 0;
		case KEY_END:
			editor_END(cur_info);
			return 0;					
		default:			//when input was normal character
			return key;
		
	}
	
	return key;
}