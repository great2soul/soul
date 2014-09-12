#include "stdio.h"

int main(int argc, char const *argv[])
{
	int c;

	while ((c = getchar()) != EOF) {
		putchar(c);
		printf("%d\n", c);
	}
	if (c == EOF) 
		putchar(c);
	return 0;
}