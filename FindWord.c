#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char c;
FILE *ptr_to_file;
void get_the_char();
int FindWord(char *search_for_string)
{
	int i;
	ptr_to_file = fopen("words.txt", "r");
	get_the_char();
	while (!feof(ptr_to_file))
	{
		for (i = 0; search_for_string[i] != '\0'; i++)
		{
			if (search_for_string[i] == c)
			{
				putchar(c);
				get_the_char();
			}
			else
			{
				i = -1;
				putchar(c);
				get_the_char();
			}
		}
		getch();
		return 1;
	}
	fclose(ptr_to_file);
	return 0;
}

void get_the_char()
{
	c = fgetc(ptr_to_file);
	if (feof(ptr_to_file))
	{
		printf("end of file");
		exit(EXIT_FAILURE);
	}
}
