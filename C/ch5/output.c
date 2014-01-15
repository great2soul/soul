#include <stdio.h>

#define IN 	1
#define OUT 0

int main(int argc, char const *argv[])
{
	int c, state;
	state = OUT;
	while((c = getchar()) != EOF)
	{
		if (c == '\t' || c == ' ')
		{
			if (!state)
			{
				putchar(c);
				state = IN;
			} 
		} else {
			putchar(c);
			state = OUT;
		}
	}
	return 0;
}