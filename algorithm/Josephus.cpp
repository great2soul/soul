#include <iostream>
#include <stdlib.h>

struct node 
{
	int item;
	node* next;

	node ( int i, node* t) 
	{
		item = i;
		next = t;
	}
};

typedef node* link;

int main (int argc, char *argv[])
{
	int i, N = argv[1], M = argv[2];

	// init link list
	link t = new node(1,0);
	t->next = t;
	link x = t;
	for (i = 2; i <= N; ++i){
		x = (x->next = new node(i, t));
	}

	// josephus method
	while (x != x->next) {
		for (i = 1; i <= M; ++i){
			x->next = x->next->next;
		}
	}

	cout<<x->item<<endl;
}
