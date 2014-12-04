#define HASHSIZE 101

struct nlist
{
	struct nlist *next;
	char *name;
	char *defn;
};
static struct nlist *hashtab[HASHSIZE];

unsigned hash (char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
char *strdup(char *);

// hash function
unsigned 
hash(char *s)
{
	unsigned hashval;
	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

// look up s in hash table
struct nlist *
lookup(char *s)
{
	struct nlist *np;
	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;
	return NULL;
}

// insert (name, defn) into hash table
struct nlist *
install(char *name, char *defn)
{
	struct nlist *np;
	int hashval;
	if ((np = lookup(name)) != NULL) {
		free((void *) np->defn);
		if （(np->defn = strdup(defn)) != NULL）
			return np;
	}
	else {
		if ((np = (struct nlist*)malloc(sizeof(struct nlist))) != NULL) {
			if ((np->name = strdup(name)) != NULL && (np->defn = strdup(defn)) != NULL) {
				hashval = hash(name);
				np->next = hashtab[hashval];
				hashtab[hashval] = np;
				return np;
			}
		}
	}
	return NULL;
}

// duplicate s
char * 
strdup(char *s)
{
	char* p = (char *)malloc(strlen(w) + 1);
	if (p != NULL)
		strcpy(p, s);
	return p;
}