#include "simarr.h"
#include "stdio.h"

void min_sum(struct simarr*, struct simarr*);
void transfer(struct simarr*, struct simarr*);
void qsort(int, int, int *);
void merge(struct simarr *, struct simarr *, struct simarr *);


int main ()
{
	// 初始化A，B；
	// struct simarr A = {6, {1,2,20,24,50,60, '\0'}};
	// struct simarr B = {4, {60,80,100,170, '\0'}};

	// struct simarr A = {4, {1,3,4,6, '\0'}};
	// struct simarr B = {4, {2,8,3,2, '\0'}};

	// struct simarr A = {7, {3,5,7,10,15,50,60, '\0'}};
	// struct simarr B = {4, {60,80,100,170, '\0'}};

	struct simarr A = {1, {5, '\0'}};
	struct simarr B = {4, {4,3,3,3, '\0'}};


	// 调用min_sum；
	min_sum(&A, &B);

	// 打印结果；	
	int i = 0;
	for(; i < A.sp; i++)
		printf("%d\t", A.val[i]);
	printf("\n");
	int j = 0;
	for(; j < B.sp; j++)
		printf("%d\t", B.val[j]);
	printf("\n");
}

void min_sum(struct simarr *A, struct simarr *B)
{
	struct simarr C = {0, {'\0'}};
	merge(A, B, &C);
	qsort(0, C.sp - 1, C.val);

	int d = 0;
	while (C.sp > 0) {
		if (d > 0) {
			d -= C.val[C.sp - 1];
			transfer(&C, B);
		}
		else {
			d += C.val[C.sp - 1];
			transfer(&C, A);
		}
	}
}

void merge(struct simarr *A, struct simarr *B, struct simarr *C)
{
	while (A->sp > 0) 
		transfer(A, C);
	while (B->sp > 0)
		transfer(B, C);
}

void transfer(struct simarr *src, struct simarr *dest)
{
	int elem = getelem(src, src->sp - 1);
	delete(src, src->sp - 1);

	insert(dest, dest->sp, elem);
}

int partition(int, int, int *);
void qsort(int left, int right, int val[])
{
	if (left < 0 || right > MAXNUM - 1)
		printf("error, access exceed the array bounds!\n");
	else if (left >= right)
		return;
	int pos = partition(left, right, val);
	qsort(left, pos - 1, val);
	qsort(pos + 1, right, val);
}

void swap(int, int, int*);
int partition(int left, int right, int *val)
{
	int i;
	int pivot = left;
	for(i = left + 1; i <= right; ++i) 
		if (val[i] < val[pivot])
			swap(++pivot, i, val);
	swap(left, pivot, val);
	return pivot;
}

void swap(int left, int right, int* val)
{
	if (left == right)
		return;
	int tmp = val[left];
	val[left] = val[right];
	val[right] = tmp;
}