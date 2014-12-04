#include "syscalls.h"


int main(int argc, char const *argv[])
{
	char buf[BUFSIZ];

	while((n = read(0, buf, BUFSIZ)) > 0)
		write(1, buf, n);
	return 0;
}