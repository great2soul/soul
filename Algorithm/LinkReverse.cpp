list_p reverse(list_p *lp)      /*反转列表*/
{
 list_p f=*lp,m=NULL,l=NULL;
 while (f) {
   m=f->next ;
   f->next=l;
   l=f;
   f=m;
  }

 return *lp=l;
}

/*调用示例*/
//---------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

typedef struct List{
int data;
struct List *next;
} list,*list_p;

list_p init(int *s,int n) /*构建链表*/
{
 list_p rh=NULL,p,np;
 int i;
 for (i = 0; i<n; i++) {
  np=(list_p)malloc(sizeof(list));
  if (!rh) {
   rh=p=np;
   p->next=NULL;
  }
  else{
     np->next =NULL;
     p->next=np;
     p=np;
  }
  np->data=s[i];
 }
 return rh;
}

list_p reverse(list_p *lp)      /*反转列表*/
{
 list_p f=*lp,m=NULL,l=NULL;
 while (f)
  {
   m=f->next ;
   f->next=l;
   l=f;
   f=m;
  }

 return *lp=l;
}

void prt(list_p f)/*输出链表*/
{
 while (f)
  {
  printf("%d\t",f->data);
  f=f->next ;
  }
 putchar('\n');
}

void FREE(list_p f) /*释放空间*/
{
  if (f->next) {
   FREE(f->next);
  }
  free(f);
}

int main(void)
{
 int d[]={1,2,3,4};
 list_p fs;
 fs=init(d,4);
 prt(fs);
 reverse(&fs);
 prt(fs);
        FREE(fs);
 return 0;
}
