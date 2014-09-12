#include "ctype.h"
#include "stdio.h"

double atof(char s[])
{
	double val;
	double power = 1.0;
	int i = 0, sign = 0;

	for (; isspace(s[i]); i++)
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}

	return sign * val / power;		
}

int main(int argc, char const *argv[])
{
	double d = atof("11.2");
	printf("%.2f\n", d);

	return 0;
}