#define BUFSIZE 100
char buf[BUFSIZE]; // 用于ungetch的缓冲区
int bufp = 0;

int getch(void) // 取一个字符
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) // 将字符压回到输入
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}