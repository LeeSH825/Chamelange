#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <io.h>
#include <conio.h>


#include "interfaces.h"
#include "cursor.h"
#include "interrupts.h"
#include "fileManage.h"
#include "textEditor.h"

//int main(int argc, char* argv[])
int main()
{
	int i, x = 0, y = 0;
	char command;
	
	char loc[60]; 
	
	FILE* bmk = fopen("./bookmarks.txt", "a");
	FILE* ref = fopen("./recentfiles.txt", "a");
	
	fseek(ref, 0, SEEK_SET);
	while (fscanf(ref, "%s", loc) != EOF)
	{

		printf("%s\n", loc);
		gotoxy(7, now_y() + 1);

	}
	fclose(ref);
	//fflush(ref);
	
	fseek(bmk, 0, SEEK_CUR);
	while (fscanf(bmk, "%d %d", &x, &y) != EOF)
	{
		printf("%d, %d", x, y);
		gotoxy(64, now_y() + 1);
	}
	//fflush(bmk);
	fclose(bmk);

	main_Screen();

	command = getchar();
	
	menu_Select(command);
	return 0;
}