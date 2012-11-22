/* func strcat: plus string t to the end of string s, s has enough space */
void strcat(char s[], char t[])
{
	int i, j;

	i = j = 0;
	while (s[i] != '0')
		i++;
	while ((s[i++] = t[j++]) != '0')
		;
}
