#include <stdio.h>
#include <conio.h>

#include "search_inFile.h"

long* search_Words(FILE* fp)
{
	int word_len=0, i=0, word_idx= 0;
	char tmp, word[30];
	long cur_fp, match_fp[100];
	scanf("%s", word);

	while (word[word_len] != '\0') //입력된 단어 길이 찾기
	{
		word_len++;
	}

	while (!feof(fp)) //파일 끝까지 탐색
	{
		tmp = fgetc(fp);
		if (tmp == word[i]) {
			i++;
		}
		else
		{
			i = 0;		//다른 단어 찾으러 감
		}
		if (i == word_len)	//단어를 찾은 경우
		{
			match_fp[word_idx++] = ftell(fp)- word_len;	//그 단어의 첫 위치를 기록, 다음 인덱스로
			i = 0;		//다른 단어 찾으러 감
		}
	}
	return match_fp;
}