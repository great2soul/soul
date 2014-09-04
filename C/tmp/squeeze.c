/* func squeese: get rid of string s's char appeared in string t */
void squeeze(char s[], char t[])
{
	int i, j, k;
	i = 0;

	while (t[i] != '\0') {
		j = k = 0;
		while (s[j] != '\0') {
			if (s[j] != t[i])
				s[k++] = s[j];
		++j;
		}	
		s[k] = '\0';
		++i;
	}
}
