#include <stdio.h>

#define MAXLINE 1000

int getLine(char line[], int max);
int strindex(char src[], char searchfor[]);

char pattern[] = "ould";

main()
{
	char line[MAXLINE];

	while (getLine(line, MAXLINE) != EOF) {
		if (strindex(line, pattern)) {
			printf("%s", line);
		}
	}
}

int getLine(char s[], int lim)
{
	int c, i;
	i = 0;

	while (--lim && (c = getchar()) != EOF && c != '\n') 
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;	
}

int strindex(char s[], char t[])
{
	int i, j, k;

	for (i = 0; s[i] != '\0'; i++) {
		for (j = i, k = 0; t[k] != '\n' && s[j] == t[k]; j++, k++)
			;
		if(k > 0 && t[k] == '\0') 
			return i;
	}
	return -1;
}
