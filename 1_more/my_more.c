/* my_more.c - version 0.1
 * read and print 24 lines then pause for a few special commands
 */
#include <stdio.h>
#include <stdlib.h>
#define PAGELEN 24
#define LINELEN 512

void do_more(FILE* fp);
int see_more();

int main(int argc, char* argv[])
{
	FILE* fp;
	if(argc == 1)
	{
		do_more(stdin);
	}else
	{
		while(--argc)
		{
			if((fp = fopen(*++argv, "r")) != NULL)
			{
				do_more(fp);
				fclose(fp);
			}else
			{
				exit(1);
			}
		}
	}

	return 0;
}

void do_more(FILE* fp)
/*
 * print PAGELEN lines and call see_more for further infomation
 */
{
	char line[LINELEN];
	int line_cnt = 0;
	int reply;

	while(fgets(line, LINELEN, fp))
	{
		if(line_cnt == PAGELEN)
		{
			int reply = see_more();
			if(reply == 0)
			{
				break;
			} 
			line_cnt -= reply;
		}
		
		if(fputs(line, stdout) == EOF)
		{
			exit(1);
		}
		line_cnt ++;
	}
}

int see_more()
/*
 * print message, wait for response, return # of lines to advance
 * q - 0, space - one more page, CR - one more line
 */
{
	int c;
	printf("\033[7m more? \033[m");
	while((c = getchar()) != EOF)
	{
		if(c == 'q')
			return 0;

		if(c == '\n')
			return 1;

		if(c == ' ')
			return PAGELEN;
	}

	return 0;
}
