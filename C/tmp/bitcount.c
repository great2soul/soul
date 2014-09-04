/* bitcount: count 1 bits in x */
int bitcount(unsigned x)
{
	int b = 0;
	while (x != 0) {
		x &= x - 1;
		b++;
 	}

	return b;
}
