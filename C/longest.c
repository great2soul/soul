#include <stdio.h>

#define MAXLINE 100

int getLine(char line[], int lim);
void copy(char to[], char from[]);
void reverse(char s[]);

int main()
{
	int len;
	int max = 0;
	char line[MAXLINE];
	char longest[MAXLINE];

	while ((len = getLine(line, MAXLINE)) > 0){
		reverse(line);
		printf("%s", line);
	}

		/*if (len > max){
			copy(longest, line);
			max = len;
		}*/

	/*if (max > 0)
		printf("%s", longest);*/
	return 0;
}

int getLine(char s[], int lim)
{
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n'){
		s[i] = c;
		++i;
	}

	s[i] = '\0';

	return i;
}

void copy(char to[], char from[])
{
	int i = 0;

	while ((to[i] = from[i]) != '\0')
		++i;
}

void reverse(char s[])
{
	int i = 0;
	char temp[MAXLINE];
	while((temp[i] = s[i]) != '\0')
		++i;
	int j;
	for (j = 0; j <= i; ++j)
		s[j] = temp[i - j];
	s[j + 1] = '\0';
}
	
