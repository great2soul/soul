#include <stdio.h>

/* strlen: return length of the string */
int strlen(char *s)
{
	char *p = s;
	while(*p != '\0') {
		p++;
	}

	return p - s;
}

/* strcpy: copy t to s */
void *strcpy(char *s, char *t)
{
	while(*s++ = *t++)
		;
}

/* strcmp: compare s and t, return <0 if s < t, 0 if s = t, and >0 if s > t */
int strcmp(char *s, char *t)
{
	for (;*s++ == *t++; s++, t++)
		if (*s == '\0')
			return 0;
	return *s - *t;
}

void strcat (char *s, char *t)
{
	while(*s++ != '\0')
		;
	while(*s++ = *t++ != '\0')
		;
}

int main()
{
	int a = strcmp("a", "ab");
	printf("a is %d", a);
}
