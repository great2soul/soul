#include "String.h"
#include <stdlib>
#include <iostream>

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

String& String::operator [] (int i)
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
			if(*p++ == *s++) {
				if(!*p) return i;	// finish scanning pattern, *p = 0, success
			} else {
				i++;				// failed, i + 1			
				s = ch + i; 		// s step forward 1
				p = pat.ch;			// p step back to start point
			}
		}
	}

	return -1;	// failed
}