#include <stdio.h>
#include "interfaces.h"
#include "interrupts.h"s

int key_ck(char ch)
{
	int checker;
	checker = ch;
	if ((checker == 224) || (checker == 0))
	{
		checker = getch();
		return 0;
	}
	if ((GetAsyncKeyState(VK_HANGUL) & 0x8000)) //�ѿ� ��ȯŰ �ԷµǸ� -2 ���� ���۷� ����
	{
		return -2;
	}
	else if ((GetAsyncKeyState(VK_LEFT) & 0x8000))
	{
		return 0;
	}
	else if ((checker >= 48) && (checker <= 57))
	{
		return 1;  //���ڸ� 1 ��ȯ
	}
	else if ((checker >= 65) && (checker <= 90))
	{
		return 2; //�빮�� ���ĺ��̸� 2 ��ȯ
	}
	else if ((checker >= 97) && (checker <= 122))
	{
		return 3; //���ĺ� �ҹ��ڸ� 3 ��ȯ
	}
	else if ((checker >= 32) && (checker <= 126))
	{
		return 4; //������ ���ڵ�(����ڳ� �ٸ� ����)�̸� 4 ��ȯ
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

void menu_Select(char cmd)
{
	switch (cmd)
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
		printf("�����Ͻðڽ��ϱ�? (Y/N)"); //�߰��� �˾�âó�� �س���
		cmd = getchar();
		switch (cmd)
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
		dye(0, LIGHTCYAN, BLACK, "�߸� �Է��ϼ̽��ϴ�.");
		_sleep(100);
		system("cls");
		main();
	}
}