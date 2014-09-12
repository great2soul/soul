#ifndef __SIMARR_H
#define __SIMARR_H

#define MAXNUM 100

struct simarr {
	int sp;
	int val[MAXNUM];
};

int getelem(struct simarr *, int);
void delete(struct simarr *, int);
void insert(struct simarr *, int, int);

#endif