#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "fileManage.h"
#include "interfaces.h"

char path[200] = " ";

void Changepath()
{
	char wantp[100] = " ";
	printf("\n");
	printf("���� ��δ� %s �Դϴ�. \n", path);
	printf("�̵��ϰ� ���� ����(���������ΰ����� ..) : ");
	scanf("%s", wantp);
	if (!strcmp(wantp, " "))
		return;
	else if (!strcmp(wantp, ".."))
	{
		if (strlen(path) == 3)
		{
			printf("�ֻ��� ����Դϴ�. \n");
			Sleep(500);
			system("cls");
			GetfileList(path);
		}
		else
		{
			for (int i = 200; i > 0; i--)
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
		printf("!!������ �����ϴ�!!\n");
		return;
	}

	while (result != -1)
	{
		printf("File: %s\n", fd.name);
		result = _findnext(handle, &fd);
	}

	_findclose(handle);
	Changepath();
	return;
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
	printf("������ ������ ��ġ: ");
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

void copy_file(FILE* in, FILE* out) //�̸� ����� fopen����ߵǰ� out�� ���� �����ͺ��� ��
{
	char b;
	while (1) //���� ����
	{
		if (feof(in)) //���� ���� �����ϸ� ����
		{
			break;
		}
		b = fgetc(in); //���������� �����Ͱ� �ڷ� ���µ� �ϴ�
		fputc(b, out);
	}
}

int open_File()
{
	int i;
	int t;
	char b;
	char temp_path[100] = { "./" };//ã������ ���
	char file_path[100];
	char temp[50];
	char load[1000];
	//���� �̸� �ޱ�
	gotoxy(30, 15);
	dye(0, WHITE, BLACK, "�����Ϸ��� ���� ��ġ : ");
	scanf("%s", temp);
	strcat(temp, ".txt"); //Ȯ����
	strcat(temp_path, temp); //�ռ�
	sprintf(file_path, "%s", temp_path);					//temp_path�� file_path�� sprintf
	FILE* in = fopen(file_path, "rb");
	if (in == NULL)
	{ //���� ������
		printf("������ �����ϴ�!\n");
		_sleep(500);
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
	printf("�˻�:");
	scanf("%s", temp);
	getchar();
	strcat(temp, ".txt"); //���� Ȯ����
	strcat(loc, temp);
	sprintf(loca, "%s", loc); //������ ����� �� �ְ� ��
	FILE* fr = fopen(loca, "r+");
	if (fr == NULL)
	{ //���� ������
		printf("������ �����ϴ�!\n");
		_sleep(500);
		system("cls");
		main();
	}
	printf("������ ���ðڽ��ϱ�? (Y/N) ");
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