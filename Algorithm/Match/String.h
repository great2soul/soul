#ifndef STRING_H
#define STRING_H
const int maxLen = 128;	// Max length of String

/*
 * Limited sequence of chars
 */

#include <string.h>
class String
{
public:
	String(const String &ob);	// Copy constructor.
	String(const char *init); //Construct a string initiated as init
	String();
	~String() { delete [] ch; delete [] f; }

	int length() const { return curLen; } // return current length of the String.

	String &operator () (int pos, int len); // return child string, start at pos, length is len
	bool operator == (const String &ob) const { return strcmp(ch, ob.ch) == 0; } // Is equal
	bool operator != (const String &ob) const { return strcmp(ch, ob.ch) != 0; } // Is not equal
	bool operator ! () const { return curLen == 0; } // Is null
	String &operator = (const String &ob);
	String &operator += (const String &ob);
	char &operator [] (int i);

	int Match(String &pat); // Match pattern string, return match position or -1
	int KMPMatch(String &pat);
	void fail();

	void display();	// test function
private:
	int curLen;	//	length of string
	char *ch;	//	string container, c-style string
	int *f;		//	f array
	int count;
	int KMPCount;
};

#endif