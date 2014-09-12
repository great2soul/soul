#include "stdio.h"
#include "ctype.h"
#include "string.h"

#define MAXWORD 100
struct key
{
	char *key;
	int count;
} keystab[] = {
	{"auto", 0},
	{"break", 0},
	{"case", 0},
	{"char", 0},
	...
};

#define NKEYS (sizeof keystab / sizeof keystab[0])

int getword(char*, int);
int binsearch(char*, struct key*, int);

int main(int argc, char const *argv[])
{
	int n;
	char word[MAXWORD];

	
	while(getword(word, MAXWORD) != EOF)	// input
		if (isalpha(word[0]))
			if ((n = binsearch(word, keystab, NKEYS)) >= 0)	// search
				keystab[n].count++;

	for (n = 0; n < NKEYS; n++)
		if (keystab[n].count > 0)
			printf("%4d: %s\n", keystab[n].count, keystab[n].key);

	return 0;
}

int getword(char* word, int n)
{
	int c, getch(void);
	void ungetch(int c);
	char *w = word;

	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for (; --lim > 0; w++)
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return w[0];
}

int binsearch(char* word, struct key* tab, int n)
{
	int cond, low, high, mid;
	
	low = 0;
	high = n - 1;
	while(low <= high) {
		mid = (low + high) / 2;
		if (cond = strcmp(word, tab[mid].key) < 0)
			high = mid - 1;
		else if (cond = strcmp(word, tab[mid].key) > 0)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}