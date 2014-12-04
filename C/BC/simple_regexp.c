int match(const char *regexp, const char *text);
int matchhere(const char *regexp, const char *text);
int matchstar(int c, const char *regexp, const char *text);
int matchstarL(int c, const char *regexp, const char *text);

int main(int argc, char const *argv[])
{
	match(argv[1],argv[2]);
	return 0;
}

// match: 在text中匹配regexp
int match(const char *regexp, const char *text)
{
	if (regexp[0] == '^')
		matchhere(regexp + 1, text);
	do {
		if (matchhere(regexp, text))
			return 1;
	} while (*text++ != '\0');
	return 0;
}

// matchhere: 在text的开头查找regexp
int matchhere(const char *regexp, const char *text)
{
	if (regexp[0] == '\0')
		return 1;
	if (regexp[0] == '$' && regexp[1] == '\0')
		return *text == '\0';
	if (regexp[1] == '*')
		return matchstar(regexp[0], regexp + 2, text);
	if (*text != '\0' && (regexp[0] == '.' || regexp[0] == text[0]))
		return matchhere(regexp + 1, text + 1);
	return 0;
}

// 在text开头查找C＊regexp
int matchstar(int c, const char *regexp, const char *text)
{
	do {
		if (matchhere(regexp,text))
			return 1;
	} while (*text != '\0' && (*text++ == c || c == '.'));
	return 0;
}

// 查找C＊regexp最左最长匹配
int matchstarL(int c, const char *regexp, const char *text)
{
	const char *t = text;
	while (*t != '\0' && (*t++ == c || c == '.'))
		;
	do {
		if (matchhere(regexp, t))
			return 1;
	} while (t-- > text);
	return 0;
}