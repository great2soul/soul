#include "simarr.h"
#include "stdio.h"

void min_sum(struct simarr*, struct simarr*);
void adjust(struct simarr*, struct simarr*, int);
int transfer(struct simarr*, struct simarr*, int);
int sum(int *);
int binsearch(int *A, int, int, int);
void qsort(int, int, int *);
int abs(int);


int main ()
{
	// 初始化A，B；
	struct simarr A = {6, {1,2,20,24,50,60, '\0'}};
	struct simarr B = {4, {60,80,100,170, '\0'}};

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
	int d;
	int sumA = sum(A->val);
	int sumB = sum(B->val);
	if (sumA == sumB)
		return;

	qsort(0, A->sp - 1, A->val);
	qsort(0, B->sp - 1, B->val);
	if ((d = sumA - sumB) > 0)
		adjust(A,B,d);
	else
		adjust(B,A,-d);
}

void adjust(struct simarr *A, struct simarr *B, int d)
{
	while (d >= 2 * A->val[A->sp - 1]) 
		d = transfer(A, B, d);
	if (A->val[A->sp - 1] <= B->val[B->sp - 1])
		return;
	else {
		d = transfer(A, B, d);
		while(d >= 2 * B->val[B->sp - 1])
			d = transfer(B, A, d);
	}
}

int transfer(struct simarr *src, struct simarr *dest, int d)
{
	// delete min in src
	int min = getelem(src, src->sp - 1); /* the array is sorted */
	delete(src, src->sp - 1);

	// add min of from to dest
	int pos  = binsearch(dest->val, 0, dest->sp - 1, min);
	insert(dest, pos, min);

	return abs(d -= 2 * min);
}

int sum(int *A)
{
	int sum = 0;
	for (; *A != '\0'; A++)
		sum += *A;
	return sum;
}

int binsearch(int *val, int low, int high, int elem)
{
	int mid;

	while (high - low > 1) {
		mid = low + (high - low)/2;
		if (elem > val[mid])
			high = mid - 1;
		else if (elem < val[mid])
			low = mid + 1;
		else
			return mid;
	}

	if (elem > val[low])
		return low;
	else if (elem < val[high])
		return high + 1;
	else
		return high;
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
		if (val[i] > val[pivot])
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

int abs(int val)
{
	return val > 0 ? val : -val;
}
