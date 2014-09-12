#include "stdio.h"
#include "ctype.h"
#include "stdlib.h"

#define MAXOP 100
#define NUMBER  '0'

void push(double c);
double pop(void);
double getop(char *);

int main()
{
	int type, op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER:
				push(atof(type));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '*':
				push(pop() * pop());
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0)
					push(pop() / op2);
				else
					printf("error, zero divisor!\n");
				break;
			case '\n'
				printf("\t%.8g\n", pop());
				break;
			default:
				printf("error, unknown command!\n");
			}

		}
	}
}

/* get operator */
#define BUFSIZE 1000

char buf[BUFSIZE]; /* unget char buffer */
int bufp = 0;	/* next spare position */

int getch(void);
void ungetch(int);

double getop(char *s)
{
	int i,c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.' )
		return c;
	i = 0;
	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

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

/* stack */

double val[MAXOP]; // value stack

