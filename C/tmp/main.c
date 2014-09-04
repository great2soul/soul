#include <stdio.h>

void squeeze(char s[], char t[]);
int atoi(char s[]);

int main()
{
	char s[] = "asdfghbc";
	char t[] = "abf";

	squeeze(s, t);

	printf("%s\n", s);

	return 0;
}	
