#include "String.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	
	String *d = new String(argv[1]);
	cout<<"************************Dest info***********************"<<endl;
	d->fail();
	d->display();

	//String *p = new String(argv[2]);
	cout<<"************************Pattern info***********************"<<endl;
	//p->fail();
	//p->display();

	cout<<"************************Result***********************"<<endl;
	//if (d->Match(*p)) cout<<"Match success!"<<endl;
	//else cout<<"Match failed!"<<endl;
	//if (d->KMPMatch(*p)) cout<<"Match success!"<<endl;
	//else cout<<"Match failed!"<<endl;
}