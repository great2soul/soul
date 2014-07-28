#include<string.h>

/* length of the string s */
size_t strlen(char *s) 
{
	char *p = s;
	while(*p != '\0') 
		p++;
	return p - s;
}

/* strcpy: 将指针t指向的字符串复制到指针s指向的位置 */
void strcpy(char *s, char *t)
{
	int i = 0;

	while((s[i] = t[i]) != '\0')
		i++;
}
char* strcpy(char *s, char *t)
{
	while(*s++ = *t++)
		;
	return s;
}

/* strcmp */
int strcmp(char *s, char *t)
{
	for(; *s == *t, s++, t++)
		if(*s == '\0')
			return 0
	return *s - *t;
}

/* strcat */
void strcat(char *s, char *t)
{
	while(*s++)
		;
	while(*s++ = *t++)
		;
}

bool strend(char *s, char *t) 
{
	char *ptr = t;
	while(s++)
		;
	while(t++)
		;
	while(*s-- == *t--)
		ptr++;
	if (*ptr == '\0')
		return 0;
	return -1;
}