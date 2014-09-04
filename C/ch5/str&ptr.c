#include <stdio.h>
// #include <string.h>
#include <stdlib.h>

/* length of the string s */
size_t mystrlen(char *s) 
{
	char *p = s;
	while(*p != '\0') 
		p++;
	return p - s;
}

/* strcpy: 将指针t指向的字符串的前n个字符复制到指针s指向的位置 */
char* strnncpy(char *s, char *t, int n)
{
	char *ptr = s; 
	while((n-- > 0) && (*s++ = *t++))
		;
	return ptr;
}

// char* strcpy(char *s, char *t)
// {
// 	while(*s++ = *t++)
// 		;
// 	return s;
// }

// /* strcmp */
// int strcmp(char *s, char *t)
// {
// 	for(; *s == *t, s++, t++)
// 		if(*s == '\0')
// 			return 0
// 	return *s - *t;
// }

// /* strcat */
// void strcat(char *s, char *t)
// {
// 	while(*s++)
// 		;
// 	while(*s++ = *t++)
// 		;
// }

int strend(char *s, char *t) 
{
	char *ps = s;
	char *pt = t;
	while(*s++)
		;
	while(*t++)
		;
	s--;
	t--;
	while((*s-- == *t--) && (*ps != '\0') && (*pt != '\0')) {
		printf("%s\t%s\t%s\t%s\n", s,t,ps,pt);
		ps++;
		pt++;
	}
	if (*pt == '\0')
		return 1;
	return 0;
}

int main()
{
	char *t = "bbb";
	char *s = malloc(mystrlen(t) + 1);

	printf("s0: %s\n", strnncpy(s, t, 1));
	// strncpy(s, t, 1);	
	// printf("s1: %s\n", ptr);
	// strncpy(s, t, 2);	
	// printf("s2: %s\n", ptr);
	// strncpy(s, t, 3);	
	// printf("s3: %s\n", ptr);
	// strncpy(s, t, 4);	
	// printf("s4: %s\n", ptr);
}