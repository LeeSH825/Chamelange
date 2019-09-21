#include <stdio.h>
#include "fileManage.h"

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

int file_size(FILE* fp) //0이면 처음 연 파일 아니면 이미 있던 파일
{
	fseek(fp, 0, SEEK_END); //끝으로
	int pos = ftell(fp); //파일 크기
	rewind(fp);
	return pos; //파일 크기 리턴
}

void save_File() //Save_as
{
	int fail;
	int b;
	char loc[100] = { "C://UDiT//" }; //파일 저장 경로
	char temp_loc[20] = { "C://UDiT//temp.txt" }; //임시 파일 저장 경로
	FILE* in = fopen("C://UDiT//temp.txt", "rb");
	FILE* out = NULL;
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
	FILE* ref = fopen("C://UDiT//recentfiles.txt", "r+");
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

void copy_file(FILE* in, FILE* out) //미리 입출력 fopen해줘야되고 out의 파일 포인터부터 들어감
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
	FILE* in = fopen(file_path, "rb");
	if (in == NULL)
	{ //파일 없으면
		printf("파일이 없습니다!\n");
		_sleep(500);
		system("cls");
		main();
	}
	FILE* tmp = fopen("C://UDiT//temp.txt", "wb");

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
	FILE* tmpa = fopen("C://UDiT//temp.txt", "r+");
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

int open_e_File(FILE* in)
{
	char b;
	FILE* out = fopen("C://UDiT//temp.txt", "wb");

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
	FILE* tmpa = fopen("C://UDiT//temp.txt", "r+");
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

int new_File() //newFile은 단순히 경로 없으면 경로 만드는걸로 하면 안될까?
{
	FILE* tmp = NULL;
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
	FILE* fr = fopen(loca, "r+");
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