#include <stdio.h>

#define IN 	1
#define OUT 0

int main(int argc, char const *argv[]) 
{
	int c, nl, nw, nc, state;
	state = OUT;
	while ((c = getchar()) != EOF) 
	{
		++nc;
		if (c == '\n')
		{
			++nl;
		}
		if (c == ' ' || c == '\n' || c == '\t')
		{
			if (state == OUT)
			{
				state = IN;
				++nw;
			}
		} else {
			state = OUT;
		}
	}
	printf("%d, %d, %d\n", nl, nw, nc);
	return 0;
}