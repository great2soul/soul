link reverse(link x)
{
	link t, y = x, r = 0;
	while(y != 0){
		t = y->next;
		y->next = r;
		r = y;
		y = t;
	}

	return r;
}
