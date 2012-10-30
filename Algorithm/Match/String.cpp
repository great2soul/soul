#include "String.h"
#include <iostream> 
#include <string> 
#include <cstdlib>

using namespace std; 

String::String(const String &ob)
{
	ch = new char[maxLen + 1];
	if(!ch) {
		cerr<<"Allocation error \n";
		exit(1);
	}

	curLen = ob.curLen;
	strcpy(ch, ob.ch);

	f = '\0';
}

String::String(const char *init)
{
	ch = new char[maxLen + 1];
	if(!ch) {
		cerr<<"Allocation error \n";
		exit(1);
	}
	curLen = strlen(init);
	strcpy(ch, init);

	f = '\0';
	count = 0;
	KMPCount = 0;
}

String::String()
{
	ch = new char[maxLen + 1];
	if(!ch) {
		cerr<<"Allocation error \n";
		exit(1);
	}
	curLen = 0;
	ch[0] = '\0';

	f = '\0';
}

String& String::operator() (int pos, int len) 
{
	String *temp = new String;
	if(pos < 0 || pos + len - 1 >= maxLen || len < 0) {
		temp->curLen = 0;
		temp->ch[0] = '\0';
	} else {
		if (pos + len - 1 >= curLen) len = curLen - pos;
		temp->curLen = len;
		for (int i = 0, j = pos; i < len; i++, j++) temp->ch[i] = ch[j];
		temp->ch[len] = '\0'; 
	}

	return *temp;
}

String& String::operator = (const String &ob)
{
	if(&ob != this) {
		delete [] ch;
		ch = new char[maxLen + 1];
		if(!ch) {
			cerr<<"Allocation error \n";
			exit(1);
		}

		curLen = ob.curLen;
		strcpy(ch, ob.ch);
	} else {
		cout<<"Attempted assignment of a String to itself! \n";
	}

	return *this;
}

String& String::operator += (const String &ob)
{
	char *temp = ch;
	curLen += ob.curLen;

	ch = new char[maxLen + 1];
	if(!ch) {
		cerr<<"Allocation error \n";
		exit(1);
	}

	strcpy(ch, temp);
	strcat(ch, ob.ch);

	delete [] temp;
	return *this;
}

char& String::operator [] (int i)
{
	if(i < 0 || i > curLen) {
		cout<<"Out of boundary! \n";
		exit(1);
	}

	return ch[i];
}

// ordinary method
int String::Match(String &pat)
{
	char *p = pat.ch, *s = ch; 
	int i = 0;

	if(*p && *s) {
		while(i <= curLen - pat.curLen) {
			
			while(*p++ == *s++) { 
				count++;
				if(!*p) {
					cout<<"Count: "<<count<<endl;
					return i;	// finish scanning pattern, *p = 0, success
				}			
			}

			count++;	
			i++;				// failed, i + 1			
			s = ch + i; 		// s step forward 1
			p = pat.ch;			// p step back to start point
		}
	}

	cout<<"Count: "<<count<<endl;
	return -1;	// failed
}
 
int String::KMPMatch(String &pat)
{
	int posP = 0, posT = 0;
	int lengthP = pat.curLen, lengthT = curLen;
	pat.fail();

	while(posP < lengthP && posT < lengthT) {
		KMPCount++;
		if (pat.ch[posP] == ch[posT]){
			posP++, posT++;
		} else if (posP == 0){
			posT++;
		} else {
			posP = pat.f[posP - 1] + 1;
		}
	}

	if (posP < lengthP) { 
		cout<<"KMPCount: "<<KMPCount<<endl;
		return -1;	// failed
	}else {
		cout<<"KMPCount: "<<KMPCount<<endl;
		return posT - lengthP;
	}


}

void String::fail()
{
	int lengthP = curLen;

	f = new int[lengthP];
	if(!f) {
		cerr<<"Allocation error!\n";
		exit(1);
	}

	f[0] = -1;
	for (int j = 1; j < lengthP; j++) {
		KMPCount++;
		int i = f[j - 1];
		while (*(ch + j) != *(ch + i + 1) && i >= 0) {
			KMPCount++;
			i = f[i];
		}

		if (*(ch + j) == *(ch + i + 1)) {
			f[j] = i + 1;
		}else {
			f[j] = -1;
		}		
	}	
}

void String::display()
{	
	for (int i = 0; i < curLen; i++) {
		cout<<ch[i];
	}

	cout<<endl;

	for (int i = 0; i < curLen; i++) {
		
		cout<<f[i];
	}

	cout<<endl;
	
}
