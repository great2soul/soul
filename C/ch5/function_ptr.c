#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define MAXLINES 5000
char *lineptr[MAXLINES];

int getLine(char s[], int lim);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qqsort(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int nnumcomp(char *, char *);
int sstrcmp(char*,  char *);
void swap(void *v[], int i, int j);

int main(int argc, char const *argv[])
{
	int nlines, numeric = 0;

	if (argc > 1 && strcmp(argv[1], "-n") == 0)
		numeric = 1;
	if ((nlines = readlines(lineptr, MAXLINES)) > 0)
	{
		qqsort((void**)lineptr, 0, nlines - 1, 
			(int(*)(void*, void*))(numeric ? nnumcomp : sstrcmp));
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("Input overflow\n");
		return 1;
	}
}

int getLine(char s[], int lim)
{
        int c, i;
        for ( i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
	        s[i] = c;
		++i;
	}
        s[i] = '\0';
        return i;
}

int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLINES];
	
	nlines = 0;
	while ((len = getLine(line, MAXLINES)) > 0) {
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}
	return nlines;
}

void writelines(char *lineptr[], int nlines)
{
	while (nlines--)
		printf("%s\n", *lineptr++);
}

void qqsort(void *v[], int left, int right, int (*comp)(void *, void *))
{
	int i, last;
	if (left >= right)
		return;

	swap(v, left, (left + right)/2);
	last = left;
	for (int i = left + 1; i < right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qqsort(v, left, last - 1, comp);
	qqsort(v, last + 1, right, comp);
}

int nnumcomp(char *s1, char *s2)
{
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);

	if (v1 < v2)
		return -1;
	else if (v1 > v2) 
		return 1;
	else
		return 0;
}

int sstrcmp(char *s1, char *s2)
{
	for (; *s1 == *s2; s1++, s2++)
		if (*s1 == '\0')
			return 0;
	return *s1 - *s2;/* code */	
}

void swap(void *v[], int i, int j)
{
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
