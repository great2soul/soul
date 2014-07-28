#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

/* find函数：打印与第一个参数模式匹配的行 */
int main(int argc, char const *argv[])
{
	char line[MAXLINE];
	int found = 0;

	if (argc != 2)
	{
		printf("Usage: find pattern\n");
	} else 
		while (getline(line, MAXLINE) > 0) 
			if (strstr(line, argv[1]) != NULL)
			{
				printf("%s", line);
				found++
			}
	return found;
}