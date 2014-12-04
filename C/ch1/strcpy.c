#include "stdio.h"

void strcpy1(char *, char *);
char *strcpy2(char *, char *);
char *inter();

int main(int argc, char const *argv[])
{
	char *p = inter();
	printf("%s\n", p);
	char s[] = "";
	char *t = "hello";

	strcpy1(s, t);
	// char *p = strcpy2(s, t);

	printf("%s\n", s);
	// printf("%s\n", p);
	return 0;
}

void strcpy1(char* s, char *t)
{
	while((*s++ = *t++) != '\0')
		;
}

char *strcpy2(char* s, char *t)
{
	char *p = s;
	while(*s++ = *t++)
		;

	return s-2;
}

char *inter()
{
	char p[] = "test";
	return p;
}