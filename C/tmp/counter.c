#include <stdio.h>

#define IN 1
#define OUT 0
main ()
{
	int c, state;

	while((c = getchar()) != EOF){
		if(c != ' ' && c != '\t' && c != '\n'){
			putchar(c);
		}else
			printf("\n");
	}
}
