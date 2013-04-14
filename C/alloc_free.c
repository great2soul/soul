#define ALLOCSIZE 10000 /* size of alloc buf */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* next alloc position */

char *alloc(int n) /* return pointer to n chracters */
{
	if (allocbuf + ALLOCSIZE - allocp >= n) { /* check if there's enough room */
		allocp += n;
		return allocp - n;
	} else {
		return 0;
	}
}

void afree(char* p) /* free storage pointed by p */
{
	if (p >= allocbuf && p <= allocbuf + ALLOCSIZE) {
		allocp = p;
	}
}
