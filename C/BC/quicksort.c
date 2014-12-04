static int comps = 0;
int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}

void quicksort(int l, int u)
{
	int i, m;
	if (l > u)
		return;
	swap(1, randint(l, u));
	m = 1;
	for (i = l + 1; i <= u; i++)
		if (x[i] < x[1])
			swap(++m, i);
	swap(1, m);
	quicksort(l, m - 1);
	quicksort(m + 1, u);
}

// 统计比较次数
void quickcount(int l,  int u)
{
	int m;
	if (l > u)
		return;
	m = randint(l, u);
	comps += u - l;	
	quicksort(l, m - 1);
	quicksort(m + 1, u);
}
void qc(n)
{
	int m;
	if (n <= 1)
		return;
	m = randint(1,n);
	comps += n - 1;
	qc(m - 1);
	qc(n - m);
}

int cc(n)
{
	int m;
	if (n <= 1)
		return;
	m = randint(1,n);
	return n - 1 + cc(m - 1) + cc(n - m);
}

// average compare
int sum;
float c(int n)
{
	int m;
	if (n <= 1)
		return;
	sum = 0;
	for (m = 1; m <= n; m++)
		sum += n - 1 + c(m - 1) + c(n - m);
	return sum/n;
}

// N is length of array to sort
float c2(int n) 
{
	float *t;
	for (n = 1; n <= N; n++) {
		int sum = 0;
		for (i = 1; i <= n; i++)
			sum += n - 1 + t[i-1] + t[n-i];
		t[n] = sum/n
	}
}
float c3(int n) 
{
	float *t;
	for (n = 1; n <= N; n++) {
		int sum = 0;
		for (i = 1; i < n; i++)
			sum += 2 * t[i];
		t[n] = n - 1 + sum/n
	}
}
float c4(int n) 
{
	float *t;
	int sum = 0;
	for (n = 1; n <= N; n++) {
		sum += 2 * t[n-1];
		t[n] = n - 1 + sum/n
	}
}

float final_cc(int n) 
{
	float t = 0;
	int sum = 0;
	for (n = 1; n <= N; n++) {
		sum += 2 * t;
		t = n - 1 + sum/n
	}
}
