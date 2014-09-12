#include "stdio.h"

#define BUFSIZE 1000

char buf[BUFSIZE]; /* unget char buffer */
int bufp = 0;	/* next spare position */

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

int main(int argc, char const *argv[])
{
	while((c = getchar()) != EOF)
		ungetch(c);

	return 0;
}