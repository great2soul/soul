#include "stdio.h"
#include "simarr.h"

int getelem(struct simarr *A, int pos)
{
	if (pos < A->sp)
		return A->val[pos];
	printf("error, access exceed the array bounds!\n"); 
	return -1;
}

void delete(struct simarr *A, int pos)
{
	if (pos < 0 || pos > (A->sp - 1)) {
		printf("error, access exceed the array bounds!\n");
		return;
	}
	while (pos++ < A->sp) 
		A->val[pos] = A->val[pos + 1];
	A->val[--A->sp] = '\0';
}

void insert(struct simarr *A, int pos, int elem)
{
	if (A->sp == MAXNUM) {
		printf("error, array is full\n");
		return;
	}
	else if (pos < 0) {
		printf("error, access exceed the array bounds!\n");
		return;
	}
	else {
		int end = A->sp;
		while(pos < end--)
			A->val[end + 1] = A->val[end];
		A->val[pos] = elem;
		++A->sp;
	}
}