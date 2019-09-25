#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "fileManage.h"
#include "interfaces.h"

#define MSIZE 104857600

char path[200] = " ", movefile[100] = " ";
int flag = 0;

void copy_file(FILE* in, FILE* out)
{
	int b;
	while (1) //Copy file
	{
		b = fgetc(in); //i think pointer backing when read
		if (feof(in)) //if EOF, break
			break;
		else
			fputc(b, out);
	}
}

void Changepath()	//function select
{
	char wantp[100] = " ";
	printf("\n");
	printf("Now path is %s \n\n", path);
	if (flag == 1)	//when type mov
	{
		printf("Select directory, and type'mov'.\n");
		scanf("%s", wantp);
		if (!strcmp(wantp, ".."))
		{
			if (strlen(path) == 3)
			{
				printf("Parent folder does not exist. \n");
				Sleep(500);
				system("cls");
				GetfileList(path);
			}
			else
			{
				for (int i = 199; i > 0; i--)
				{
					if (path[i] == '/')
					{
						path[i] = NULL;
						for (int j = i - 1; j > 0; j--)
						{
							if (path[j] == '/')
								break;
							path[j] = NULL;
						}
						break;
					}
				}
				system("cls");
				GetfileList(path);
			}
		}
		else if (!strcmp(wantp, "mov"))	//selected move directory
		{
			if (strlen(path) == 3)
			{
				printf("access error.(Can't move C:/) \n");
				Sleep(500);
				system("cls");
				GetfileList(path);
			}
			flag = 0;
			system("cls");
			return;	//Move function when type 'mov'
		}
		else
		{
			strcat(path, wantp);
			strcat(path, "/");
			system("cls");
			GetfileList(path);
		}
	}
	else
	{
		printf("Delete: del /  Move: mov / Copy: cpy \n");
		printf("Parent folder: .. / Exit: exit: ");
		scanf("%s", wantp);
		if (!strcmp(wantp, " "))
			return;
		else if (!strcmp(wantp, "exit"))
			return;
		else if (!strcmp(wantp, "del"))
		{
			char delfile[100] = " ";
			scanf("%s", delfile);
			strcat(path, delfile);
			if (!remove(path))
			{
				printf("Delete complete.\n");
				for (int i = 199; i > 0; i--)
				{
					if (path[i] == '/')
						break;
					path[i] = NULL;
				}
				Sleep(500);
				system("cls");
				GetfileList(path);
			}
			else
			{
				printf("File does not exist! \n");
				for (int i = 199; i > 0; i--)
				{
					if (path[i] == '/')
						break;
					path[i] = NULL;
				}
				Sleep(500);
				system("cls");
				GetfileList(path);
			}
		}
		else if (!strcmp(wantp, "mov")|| !strcmp(wantp, "cpy"))
		{
			int k = 0, temp = 0;
			scanf("%s", movefile);	//file name

			char filedir[200] = " ";
			strcpy(filedir, path);
			strcat(filedir, movefile);	//now file location
			flag = 1;
			system("cls");
			char dest[200] = " ";
			GetfileList(path);	//location select
			strcpy(dest, path);
			strcat(dest, movefile);	//destination locate get
			if(!strcmp(wantp, "mov"))
				printf("moving file... \n");
			else
				printf("copying file... \n");
			FILE* in = fopen(filedir, "rb");
			FILE* out = fopen(dest, "wb");
			copy_file(in, out);
			fclose(in);
			fclose(out);
			if (!strcmp(wantp, "mov")&&!remove(filedir))
				printf("Move complete. \n");
			else if(!strcmp(wantp, "mov"))
				printf("Error. \n");
			else if (!strcmp(wantp, "cpy"))
				printf("Copy complete. \n");
			Sleep(1000);
			system("cls");
			GetfileList(path);
		}
		else if (!strcmp(wantp, ".."))
		{
			if (strlen(path) == 3)
			{
				printf("Parent folder does not exist. \n");
				Sleep(500);
				system("cls");
				GetfileList(path);
			}
			else
			{
				for (int i = 199; i > 0; i--)
				{
					if (path[i] == '/')
					{
						path[i] = NULL;
						for (int j = i - 1; j > 0; j--)
						{
							if (path[j] == '/')
								break;
							path[j] = NULL;
						}
						break;
					}
				}
				system("cls");
				GetfileList(path);
			}
		}
		else
		{
			strcat(path, wantp);
			strcat(path, "/");
			system("cls");
			GetfileList(path);
		}
	}
}

void GetfileList(char* path) //�ش� ��ġ�� �ִ� ���ϵ� �����ִ� �Լ� -> path�� ���� �ٸ���
{
	FILE_SEARCH fd;
	char loc[100];
	long handle;
	int result = 1;
	sprintf(loc, "%s*.*", path);
	//handle = _findfirst(".\\*.*", &fd);  //���� ���� �� ��� ������ ã�´�.
	handle = _findfirst(loc, &fd); //���⼭ ã����� ��� �����ؾߵǴµ�
	if (handle == -1)
	{
		printf("File does not exist! \n");
		return;
	}

	while (result != -1)
	{
		printf("File: %s\n", fd.name);
		result = _findnext(handle, &fd);
	}

	_findclose(handle);
	Changepath();
}

int file_size(FILE* fp) //0�̸� ó�� �� ���� �ƴϸ� �̹� �ִ� ����
{
	fseek(fp, 0, SEEK_END); //������
	int pos = ftell(fp); //���� ũ��
	rewind(fp);
	return pos; //���� ũ�� ����
}

void save_File() //Save_as
{
	int fail;
	int b;
	char loc[100] = { "./" }; //���� ���� ���
	char temp_loc[20] = { "./temp.txt" }; //�ӽ� ���� ���� ���
	FILE* in = fopen("./temp.txt", "rb");
	FILE* out = NULL;
	char name[50];

	char loca[100];
	char folder[100];
	dye(0, LIGHTBLUE, BLACK, "");
	gotoxy(39, 26);
	printf("Where to save the file: ");
	scanf("%s", name); //�̸�
	getchar();
	strcat(name, ".txt"); //Ȯ����
	strcat(loc, name); //�ռ�

					   //FILE *bmk = fopen("C://UDiT//bookmarks.txt", "r+");
	FILE* ref = fopen("./recentfiles.txt", "r+");
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
	sprintf(loca, "%s", loc); //������ ����� �� �ְ� ��

	out = fopen(loca, "wb"); //���������� �б�, ����� ����

	copy_file(in, out); // in���� out���� ����

	fclose(in); // ���� �ݱ�
	fclose(out);
	//bmkn = 1;

	system("cls");
	main();

	return 0;
}

int open_File()
{
	int i;
	int t;
	char b;
	char temp_path[100] = { "" };//ã������ ���
	char file_path[100];
	char temp[50];
	char load[1000];
	//���� �̸� �ޱ�
	gotoxy(30, 15);
	dye(0, WHITE, BLACK, "File Location to Open : ");
	scanf("%s", temp);
	strcat(temp, ".txt"); //Ȯ����
	strcat(temp_path, temp); //�ռ�
	sprintf(file_path, "%s", temp_path);					//temp_path�� file_path�� sprintf
	FILE* in = fopen(file_path, "rb");
	printf("%s\n", temp_path);
	if (in == NULL)
	{ //���� ������
		printf("File does not exist!\n");
		_sleep(5000);
		system("cls");
		main();
	}
	FILE* tmp = fopen("./temp.txt", "wb");

	while (1) //���� ����
	{
		if (feof(in)) //���� ���� �����ϸ� ����
		{
			break;
		}
		b = fgetc(in); //���������� �����Ͱ� �ڷ� ���µ� �ϴ�
		fputc(b, tmp);
	}
	//while ((t = fgetc(in)) != EOF) // ���� 1����Ʈ�� ��´�.
	//{
	//	fputc(t, tmp); // �� 1����Ʈ�� �纻�� ����.
	//}
	fclose(in); // �����Ϸ��� ���� ���� �Ϸ� => �ݱ�
	fclose(tmp); // �ٸ� ���� ������ ��
	system("cls");
	FILE* tmpa = fopen("./temp.txt", "r+");
	gotoxy(0, 1);

	//�ÿ��� ������ �κ�
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

int open_e_File(FILE* in)
{
	char b;
	FILE* out = fopen("./temp.txt", "wb");

	while (1) //���� ����
	{
		if (feof(in)) //���� ���� �����ϸ� ����
		{
			break;
		}
		b = fgetc(in); //���������� �����Ͱ� �ڷ� ���µ� �ϴ�
		fputc(b, out);
	}
	fclose(in); // �����Ϸ��� ���� ���� �Ϸ� => �ݱ�
	fclose(out); // �ٸ� ���� ������ ��
	system("cls");
	FILE* tmpa = fopen("./temp.txt", "r+");
	gotoxy(0, 1);
	while (1) //���� �ű��, �Ѹ���
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


int find_File() //�ð� �Ǹ� ����Ʈ ��� �ٸ� ��ο����� ã��
{
	int i;
	char loc[100] = { "./" }; //ã������ ���� ���
	char temp[50];//�����̸�
	char loca[100];
	char sel_o;
	gotoxy(4, 4);
	printf("Search:");
	scanf("%s", temp);
	getchar();
	strcat(temp, ".txt"); //���� Ȯ����
	strcat(loc, temp);
	sprintf(loca, "%s", loc); //������ ����� �� �ְ� ��
	FILE* fr = fopen(loca, "r+");
	if (fr == NULL)
	{ //���� ������
		printf("%s\n", loca);
		printf("File does not exist!\n");
		_sleep(5000);
		system("cls");
		main();
	}
	printf("Do you want to open the file? (Y/N) ");
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
	strcpy(path, "C:/");
	GetfileList(path);
	system("pause");
	main();
}