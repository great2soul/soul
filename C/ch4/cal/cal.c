#include <stdio.h>
#include <stdlib.h>
#include "cal.h"

#define MAXOP 100

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
