#include <stdio.h>
#define MAXLINE 100	/* maximum input line length*/

int Getline(char line[], int maxline);
void copy(char to[], char from[]);

/* print the longest input line*/
int main()
{
	int len, max;
	char line[MAXLINE];
	char longest[MAXLINE];
	
	while (len = Getline(line, MAXLINE) > 0){
		if (len > max){
			max = len;
			copy(longest, line);
		}
	}
	if (max > 0)
		printf("%s", longest);
	return 0;
}

/* Getline: read a line into s, return length */
int Getline(char s[], int lim)
{
	int c, i;
	for (i = 0; i < lim -1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
	int i = 0;

	while ((to[i] = from [i]) != '\0')
		++i;
}

/* reverse: reverse a string s */
void reverse(char s[])
{
	int i, j;
	char temp;

	i = 0;
	while (s[i] != '\0')
		++i;		/* find the end of the line*/
	--i;			/* back off from '\0' */

	if (s[i] == '\n')
		--i;		/* check if line end with '\n' */

	j = 0;
	while (j < i) {
		temp = s[i];	/* swap front and end char */
		s[i] = s[j];
		s[j] = temp;

		++j;
		--i;
	}
}
