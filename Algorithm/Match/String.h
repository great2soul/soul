const int maxLen = 128;	// Max length of String

/*
 * Limited sequence of chars
 */

class String
{
public:
	String(const &ob);	// Copy constructor.
	String(const char *init); //Construct a string initiated as init
	String();
	~String() { delete [] ch; }

	int length() const { return curLen; } // return current length of the String.

	String &operator () (int pos, int len); // return child string, start at pos, length is len
	bool operator == (const String &ob) const { return strcmp(ch, ob.ch) == 0; } // Is equal
	bool operator != (const String &ob) const { return strcmp(ch, ob.ch) != 0; } // Is not equal
	bool operator ! () const { return curLen == 0; } // Is null
	String &operator = (const String &ob);
	String &operator += (const String &ob);
	char &operator [] (int i);

	int Match(String &pat) const; // Match pattern string, return match position or -1
private:
	int curLen;
	char *ch;
};