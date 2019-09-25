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




int editor() //������ ���� ������ fclose()
{
	/*
	int i;
	char ch;
	char line_buffer[max_line_buffer_size]; //�Է� maxĭ, �������� ���Ϳ� \n\n\0 or ���� ����� \n\0
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
	//editor�� ���� ���� ���� ������ ������ �� �ؾߵ��� ������
	FILE* tmp = fopen("./temp.txt", "r+"); //�����ʹ� ������ temp ���Ͽ�����

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
			cur_info.line_buffer[cur_info.pointer] = ch; //ù�� ���ڵ� ���۷� ����					
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
	//gotoxy(pointer, i); //�ű�� �ܼ� Ŀ�� �ű��
	//system("pause");
	gotoxy(stdscr,cur_info.pointer, 1); //move cursor to first of file

	//////////INITIALIZING FINISHED///////////////////////



/*
	//////////ACTUAL EDITING STARTS FROM HERE///////////////
	while (1)
	{
		while ((ch = getch()) != '\n')
		{
			if (key_ck(ch) != 0)  //�Է� ������ �����϶���
			{
				if ((pointer > last_ch) && (pointer != 121)) //�� �������̰ų� ���� �� ���� \n�ڸ��� �ƴҶ�, ���� ����Ű�� ���� 255�� �ƴҶ�
				{

					line_buffer[pointer] = ch;
					printf("%c", ch);
					pointer++;
					last_ch++;
				}
				else if ((last_ch != 121) && (pointer <= last_ch)) //�߰��� �����Ҷ� -> �̶� ������ ���ڰ� 255�� x
				{
					for (i = last_ch; i >= pointer; i--)
					{
						line_buffer[i + 1] = line_buffer[i]; //���������� �ű��
					}
					last_ch++;
					line_buffer[pointer] = ch; //�� �ڸ��� ���� �ְ�
					for (i = pointer; i <= last_ch; i++)
					{
						printf("%c", line_buffer[i]);
						//printf("\n%c, %d\n", line_buffer[i], i); //���� �ڸ����� ������ �ٽ� ���
					}
					pointer++;
					gotoxy(stdscr, pointer, now_y(stdscr));//���� �ڸ��� ���ư�
				}

			}

			//////////BELOW ONES ARE SPECIAL CASES/////////////////
			/////////CAN BE REPLACED AS interrupts/key_ck()  ///////////
			if (ch == KEY_F(0)) //ctrl �̶� lŰ ������
			{
				if (pointer > 0)
				{
					pointer--; //�����͸� ��������
					i = now_y(stdscr);
					gotoxy(stdscr, pointer, i); //�ű�� �ܼ� Ŀ�� �ű��
				}
			}
			if (ch == KEY_F(1)) //ctrl �̶� rŰ ������
			{
				if (pointer <= last_ch)
				{
					pointer++; //�����͸� ����������
					i = now_y(stdscr);
					gotoxy(stdscr,pointer, i); //�ű�� �ܼ� Ŀ�� �ű��
				}
			}

			if (ch == KEY_F(2))//�齺���̽� 
			{
				pointer--;
				i = now_y(stdscr);
				gotoxy(stdscr, 10, 12);
				//printf("back %d = pointer, %d is last_ch", pointer, last_ch);
				gotoxy(stdscr, pointer, i); //�ű�� �ܼ� Ŀ�� �ű��
				if (last_ch < pointer) //���� �������϶�
				{
					gotoxy(stdscr,last_ch, now_y(stdscr));
					printf(" ");
					gotoxy(stdscr,last_ch, now_y(stdscr));
					last_ch--;
					i = now_y(stdscr);
					gotoxy(stdscr, 10, 16);
					//printf("back1 %d = pointer, %d is last_ch", pointer, last_ch);
					gotoxy(stdscr, pointer, i); //�ű�� �ܼ� Ŀ�� �ű��
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
					gotoxy(stdscr, pointer, i); //�ű�� �ܼ� Ŀ�� �ű��
				}
			}
			if (ch == KEY_F(3)) //ȨŰ
			{
				getchar();

				pointer = 0;
				gotoxy(stdscr, pointer, now_y(stdscr));
			}
			if (ch == KEY_F(4)) //����Ű
			{
				getchar();
				pointer = last_ch + 1;
				gotoxy(stdscr, pointer, now_y(stdscr));
			}

			//if (GetAsyncKeyState(VK_LEFT) & 0x8000)  //Ű���� ����Ű ����->��ĭ��
			//{
			//	getchar();
			//	getch();
			//	if (pointer > 0)
			//	{
			//		pointer--;
			//		gotoxy(pointer, now_y());
			//	}
			//}
			//if (GetAsyncKeyState(VK_RIGHT) & 0x8000) //Ű���� ����Ű ������ ->�� �Էµ�
			//{
			//	getchar();
			//	if ((last_ch - pointer) >= -1)
			//	{
			//		pointer++;
			//		gotoxy(pointer, now_y());
			//	}
			//}

			if (ch == KEY_F(5)) //���� �Է�
			{					//�߰��� �����ѰŴ� ���� \n \0�����ϱ� Ȯ��

				int y_point = now_y(stdscr);//���� ��ǥ�� ����
				line_buffer[last_ch + 1] = '\n';
				//line_buffer[last_ch + 2] = '\n'; //���ʹϱ� ���� �� ó������ ��
				line_buffer[last_ch + 2] = '\0';
				save_Line(tmp, line_buffer); // ���� ����
				pointer = 0;
				last_ch = -1;
				line++; //���� �߰�
				print_whole_file(tmp, line);
				gotoxy(stdscr, pointer, y_point + 1); //Ŀ���� ���� ù�ٷ�		 
			}
			if (ch == KEY_F(6)) //�߰��� ���� �߰����ִ� ���� �Է�
			{

				int y_point = now_y(stdscr);//���� ��ǥ�� ����
				line_buffer[last_ch + 1] = '\n';
				line_buffer[last_ch + 2] = '\n'; //���� �� ó������ ��
				line_buffer[last_ch + 3] = '\0';
				save_Line(tmp, line_buffer); // ���� ����
				pointer = 0;
				last_ch = -1;
				line++; //���� �߰�
				print_whole_file(tmp, line);
				gotoxy(stdscr, pointer, y_point + 1); //Ŀ���� ���� ù�ٷ�		 
			}
			if (ch == KEY_F(7)) //ctrl+s
			{
				char end_sel;
				int k = now_y(stdscr);
				gotoxy(stdscr, 70, 0);
				//dye(0, COLOR_WHITE, COLOR_BLACK, "�����Ͻðڽ��ϱ�? (Y/N) >>");
				getchar();
				end_sel = getchar();
				line_buffer[pointer] = '\0';
				switch (end_sel)
				{
				case 'Y': { //���� ���� �����ʹ� �� ���� ���� ��
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
					//dye(0, COLOR_WHITE, COLOR_BLACK, "�����Ͻðڽ��ϱ�? (Y/N) >>");
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
					//dye(0, COLOR_WHITE, COLOR_BLACK, "�����Ͻðڽ��ϱ�? (Y/N) >>");
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

			if (ch == KEY_F(8)) //ctrl+u �� ȭ��ǥ
			{
				pointer--;
				gotoxy(stdscr, pointer, now_y(stdscr));
				//line--;
				//cur_Line(line);
				//line_buffer[last_ch + 1] = '\n';
				//line_buffer[last_ch + 2] = '\0';
				//fputs(line_buffer, tmp); //�Է� ������ ���Ͽ� ����
				//fflush(tmp); //���� �ý��� �Է� ���� �����
				//last_ch = 0;
				//int count = 0;
				//while (i <= line) //�� ���� ã�Ƽ� ���ۿ� ����
				//{

				//	while (1)
				//	{
				//		count++; //���������� line��° ������ ��(\n ��) ������ ũ��
				//		if (ch = fgetc(tmp) == '\n')
				//		{
				//			fseek(tmp, 2, SEEK_CUR);//���� ���ܿ� \N �־ ������ ������
				//			count = count + 1;//\N �־
				//			break;
				//		}
				//		if (i == 3)
				//		{
				//			last_ch++; //���������� line��° ������ ���� ��
				//		}
				//	}
				//	i++;
				//}
				//fseek(tmp, count - (last_ch - 1), SEEK_SET); //line ��° ������ ù��° ����
				//for (i = 0; i <= last_ch - 1; i++)
				//{
				//	line_buffer[i] = fgetc(tmp); //�� ���� �޾ƿ���
				//}
				//fseek(tmp, -(last_ch - 1), SEEK_CUR); //�� ���� ù �����ͷ� �ű�� => �׷��� ���߿� ����� �� �ֵ���


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
				//dye(0, COLOR_WHITE, COLOR_BLACK, "���� ������ �ϸ�ũ�� �����Ͻðڽ��ϱ�? (Y/N) >>");

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

				gotoxy(stdscr, pointer, i); //�ű�� �ܼ� Ŀ�� �ű��

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

void save_Line(FILE* fp, char* buffer) //�ش� ���� ����
{
	int n_pointer = ftell(fp); //�� ���ڸ� ������ (2019.9.22)�ֳĸ� ���������� ���� ���Ͽ� ������ ��ġ�̱� ����
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

	fseek(fp, n_pointer, SEEK_SET); //�Ʊ� �����Ϸ��� ������ �� ���ڸ� �����ͷ� ������
	fputs(buffer, fp); //������ ���� ���Ͽ� ����
	//fflush(fp); //���� �ý��� �Է� ���� �����



	//_chsize(_fileno(fp), ftell(fp)); //������ ������ ���ĸ� �� �� ���� (\0���� ������)
	int l_pointer = ftell(fp);//�� ������ �����͸� ������



	fflush(tmp); //���� �ý��� �Է� ���� �����
	fseek(fp, 0, SEEK_END); //Ȥ�� �𸣴ϱ� ���� ���� ������ ����
	int last_pointer = ftell(fp);//�� ������ �����͸� ������
	fseek(tmp, 0, SEEK_SET); //�Ʊ� �����ߴ� ������ �����͸� �� ������

	if (end_of_line = 1) //�ڿ� ���� ��������
	{
		copy_file(tmp, fp); //tmp���� �޾ƿͼ� fp�� �߰��� (�Ʊ� �����ߴ� ����)
	}
	fclose(tmp);
	fseek(fp, l_pointer + 1, SEEK_SET); //������ ������ �� �� �������� (������) ���� ������ ����
}

void print_whole_file(FILE* fp, int line) //������ ������ �ٽ� ǥ������
{
	int now_x_pointer = now_x(stdscr); //���� �ִ� ��ǥ �޾ƿ�
	int now_y_pointer = now_y(stdscr);
	int now_pointer = ftell(fp); //���� ���� ������ 
	char b;
	fseek(fp, 0, SEEK_SET); //������ ó��  �����ͷ� �Ѿ
	clear();
	edit_Interface();
	cur_Line(line, COLOR_WHITE, COLOR_BLACK); //���� �� �ٽ� ǥ��
	gotoxy(stdscr, 0, 1);
	while (1)
	{
		if (feof(fp)) //���� ���� �����ϸ� ����
			break;
		b = fgetc(fp); //���������� �����Ͱ� �ڷ� ���µ� �ϴ�
		addch(b);
	}
	fseek(fp, now_pointer, SEEK_SET);
	gotoxy(stdscr, now_x_pointer, now_y_pointer); //���� �ִ� ��ǥ������ �ǵ��ư�
}

void edit_sClr(FILE* fp, int x, int y) //x�� y�� ���� ȭ�� Ŭ���� �� ����� ������, ���� ��ġ
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
		char key; //�ϴ��� �ܼ��� �����ִ� �����θ�
		int menu = 1;
	again:

		key = getch();
		while (1)
		{

			if (key == 244)  //Ű �Է¿� ���� �޴�
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
				//dye(0, COLOR_WHITE, COLOR_BLACK, ""); //���� �ٲٰ�
			case 1: {
				//dye(0, COLOR_WHITE, COLOR_BLACK, "");
				gotoxy(stdscr,6, 0); //������ �·ᰡ 11
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
				gotoxy(stdscr,14, 0); //������ �·ᰡ 19
				printf(" Edit ");
				gotoxy(stdscr,14, 1);
				printf(" Book \n mark ");

				goto again;
				break;
			}
			case 3: {
				////dye(0, COLOR_WHITE, COLOR_BLACK, "");
				gotoxy(stdscr,22, 0); //������ �·ᰡ 29
				printf(" Search ");
				gotoxy(stdscr,22, 0);
				printf(" fInd ");
				goto again;
				break;
			}
			case 4: {
				//dye(0, COLOR_WHITE, COLOR_BLACK, "");
				gotoxy(stdscr, 32, 0); //������ �·ᰡ 39
				printf(" Options ");
				gotoxy(stdscr,32, 1);
				printf(" Color   ");
				goto again;
				break;
			}
			case 5: {
				//dye(0, COLOR_WHITE, COLOR_BLACK, "");
				gotoxy(stdscr,42, 0); //������ �·ᰡ 47
				printf(" Help ");
				goto again;
				break;
			}
			default: {

			}
			}
			if (KEY_F(10) == menu) //F10�� �ٽ� ������ 
			{
				edit_sClr(fp, x, y); //���� ������ �ϴ� ���� �״�� ȭ�鸸 Ŭ������
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