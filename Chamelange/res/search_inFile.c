#include <stdio.h>
//#include <conio.h>
#include <unistd.h>

#include "search_inFile.h"

long* search_Words(FILE* fp)
{
	int word_len=0, i=0, word_idx= 0;
	char tmp, word[30];
	long cur_fp;
	scanf("%s", word);

	while (word[word_len] != '\0') //�Էµ� �ܾ� ���� ã��
	{
		word_len++;
	}

	while (!feof(fp)) //���� ������ Ž��
	{
		tmp = fgetc(fp);
		if (tmp == word[i]) {
			i++;
		}
		else
		{
			i = 0;		//�ٸ� �ܾ� ã���� ��
		}
		if (i == word_len)	//�ܾ ã�� ���
		{
			match_fp[word_idx++] = ftell(fp)- word_len;	//�� �ܾ��� ù ��ġ�� ���, ���� �ε�����
			i = 0;		//�ٸ� �ܾ� ã���� ��
		}
	}
	return match_fp;
}