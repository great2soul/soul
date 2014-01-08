#include<ctype.h>

int getch(coid);
void ungetch(int);

// getint: 将输入中的下一个整型赋值给＊pn
int getint(int *pn)
{
	int c, sign;

	while (isspace(c = getch())) // skip space 
		;
	if (!(isdigit(c) || c == EOF || c == '+' || c == '-'))
	{
		ungetch(c); // nan
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
	{
		c = getch();
	}
	for (*pn = 0; isdigit(c); c = getch())
	{
		*pn = 10 * (*pn) + (c - '0');
	}
	if (c != EOF)
	{
		ungetch(c)
	}
	return c;
}