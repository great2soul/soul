#include "ctype.h"
#include "stdio.h"
#include "string.h"

#define MAXWORD 100

struct tnode
{
	char *word;
	int	count;
	struct tnode *left;
	struct tnode *right;
	struct tnode *parent;
};

struct tnode *
addtree(struct tnode*, char *);
void
treeprint(struct tnode*);
int
getword(char *, int);

int 
main(int argc, char const *argv[])
{
	struct tnode *root;
	char word[MAXWORD];

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);
	treeprint(root);
	return 0;
}

struct tnode *
addtree(struct tnode *root, char *word)
{
	int cond;
	// check if root is null
	if (root == NULL) {
		root = talloc();
		root->word = strdup(word);
		root->left = NULL;
		root->right = NULL;
		root->parent = NULL;
		return root;
	}

	// find node store word
	struct tnode* pnode = root;
	while (pnode != NULL) {
		if ((cond = strcmp(word, pnode->word)) < 0)
			pnode = pnode->left;
		else if (cond > 0)
			pnode = pnode->right;
		else {
			++pnode->count;
			reutrn root;
		}
	}

	// insert new word
	pnode = pnode->parent;
	p = talloc();
	p->word = strdup(word);
	p->left = NULL;
	p->right = NULL;
	p->parent = &pnode;
	if (strcmp(word, pnode->word) < 0) 
		pnode->left = &p;
	else
		pnode->right = &p;
	return root;
}
// recursive alg
struct tnode *
addtreeR(struct tnode *p, char *w)
{
	int cond;

	if (p == NULL) {
		p = talloc();
		p->word = strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0)
		p->count++;
	else if (cond < 0)
		p->left = addtreeR(p->left, w);
	else
		p->right = addtreeR(p->right, w);
	return p;
}

void
treeprint(struct tnode *root)
{
	if (root != NULL) {
		treeprint(root->left);
		printf("%4d\t%s\n", root->count, root->word);
		treeprint(root->right);
	}
}

struct tnode *
tmalloc()
{
	return (struct tnode*)malloc(sizeof(struct tnode));
}
char * 
strdup(char *s)
{
	char* p = (char *)malloc(strlen(w) + 1);
	if (p != NULL)
		strcpy(p, s);
	return p;
}
