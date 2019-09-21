#include <stdio.h>
#include "interfaces.h"
#include "cursor.h"
#include "fileManage.h"

//#define COLORS

int editor() //에디팅 끝난 다음에 fclose()
{
	int i;
	char ch;
	char line_buffer[123]; //입력 120칸, 나머지는 엔터용 \n\n\0 or 라인 저장용 \n\0
	int line = 1;
	int pointer = 0;
	int t_point;
	int last_ch = -1;

	FILE* tmp = fopen("C://UDiT//temp.txt", "r+"); //에디터는 무조건 temp 파일에서만

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
					FILE* bmk = fopen("C://UDiT//bookmarks.txt", "r+");
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