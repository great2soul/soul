#include <stdio.h>

#define IN 1	/* inside a word */
#define OUT 0	/* outside a word */

/* print input one word per line */
main ()
{
	int c, state;
	
	state = OUT;

	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\t' || c == '\n') {
			if (state == IN) {
				state = OUT;	/* finish the word */
				putchar('\n');
			}
		} else if (state == OUT) {
			state = IN;	/* beginning of a word */
			putchar(c);
		} else 
			putchar(c);	/* inside a word */
	}
}
