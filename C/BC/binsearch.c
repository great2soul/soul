#include "stdlib.h"
#include "stdio.h"

int main(int argc, char const *argv[])
{
	int a = 1000000000;
	int b = 500000000;

	int c = (a + b) >> 1;
	printf("%d\n%d\n", c, a+b);
	return 0;
}

int binsearch(char *x, char target)
{
	int l = -1;
	int u = strlen(x);
	int probe;

	while (u - l > 1) {
		probe = (u + l) >> 1;
		if (target < x[probe])
			u = probe;
		else 
			l = probe;
	}
	if (l == -1 || target > x[l])
		return -1;
	else
		return l;
}