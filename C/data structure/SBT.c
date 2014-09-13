/****************************************
*          SBT.cc
*
*    Mon Jun 14 16:57:48 2007
*    Copyright  2007  巨菜逆铭
* 
******************************************/
 
//————BST的储存结构————
typedef struct SBTNode{
  SBTNode *left,*right;
  long key;  //这里省略了卫星数据域
  unsigned long size;
  SBTNode(long _key){  //构造函数：未考虑卫星数据
    left=right=NULL;
    size=1;
    key=_key;
  }
}SBTNode, *SBTree;
 
//————SBT基本操作函数原型说明————
SBTNode *SBT_Search(SBTree T,long key);
  //在T中中寻找关键字为key的结点
  //若能找到则返回指向它的指针，否则返回NULL
void SBT_Insert(SBTree &T, SBTNode *x);
  //将节点x插入树中
  //初始要求x的left和right域为NULL，size域为1
SBTNode *SBT_Delete(SBTree &T, long key);
  //从以T为根的SBT中删除一个关键字为v的结点并返回其指针
  //如果树中没有一个这样的结点，删除搜索到的最后一个结点并返回其指针
SBTNode *SBT_Pred(SBTree T, long key);
  //返回指向关键字为key的节点在T的中序遍历中的直接前趋的指针
  //要求T中必须有关键字为key的节点
SBTNode *SBT_Succ(SBTree T,long key);
  //返回指向关键字为key的节点在T的中序遍历中的直接后继的指针
  //要求T中必须有关键字为key的节点
SBTNode *SBT_Select(SBTree T, unsigned long i);
  //从树T中找到关键字第i小的结点并返回其指针
unsigned long SBT_Rank(SBTree T, long key);
  //返回关键字为key的节点在树T中的秩
  //若不存在此节点则返回0
 
//————SBT的修复操作————
inline void SBT_LeftRotate(SBTree &x){
  //左旋
  SBTNode *y=x->right;
  assert(y!=NULL);
  x->right=y->left;
  y->left=x;
  y->size=x->size;
  x->size=(!x->left?0:x->left->size)
    +(!x->right?0:x->right->size)+1;
  x=y;
}
inline void SBT_RightRotate(SBTree &x){
  //右旋
  SBTNode *y = x->left;
  assert(y!=NULL);
  x->left=y->right;
  y->right=x;
  y->size=x->size;
  x->size=(!x->left?0:x->left->size)
    +(!x->right?0:x->right->size)+1;
  x=y;
}
void SBT_Maintain(SBTree &T,bool flag){
  //维护操作的核心：保持
  if(!T)  return;  //空树无需Maintain
  if(!flag){
    if( T->left&&T->left->left
      &&(!T->right||T->left->left->size > T->right->size) )  //情况1
      SBT_RightRotate(T);
    else if( T->left&&T->left->right
      &&(!T->right||T->left->right->size > T->right->size) ){  //情况2
      SBT_LeftRotate(T->left);
      SBT_RightRotate(T);
    }
    else return;  //无需修复
  }
  else{
    if( T->right&&T->right->right
      &&(!T->left||T->right->right->size > T->left->size) )  //情况1'
      SBT_LeftRotate(T);
    else if( T->right && T->right->left
      &&(!T->left||T->right->left->size > T->left->size) ){  //情况2'
      SBT_RightRotate(T->right);
      SBT_LeftRotate(T);
    }
    else return;//无需修复
  }
  SBT_Maintain(T->left,0);  //修复左子树
  SBT_Maintain(T->right,1);  //修复右子树
  SBT_Maintain(T,0);  //修复整棵树
  SBT_Maintain(T,1);
}
 
//————SBT基本操作的算法描述————
SBTNode *SBT_Search(SBTree T,long key){
  //在T中中寻找关键字为key的结点
  //若能找到则返回指向它的指针，否则返回NULL
  return !T||T->key==key?T:SBT_Search(key<T->key?T->left:T->right,key);
}
void SBT_Insert(SBTree &T, SBTNode *x){
  //将节点x插入树中
  if(!T)  T=x;
  else{
    T->size++;
    SBT_Insert(x->key<=T->key?T->left:T->right,x);
    SBT_Maintain(T,x->key>T->key);
  }
}
SBTNode *SBT_Delete(SBTree &T, long key){
  //从以T为根的SBT中删除一个关键字为key的结点并返回“实际”被删除结点的指针
  //如果树中没有一个这样的结点，删除搜索到的最后一个结点并返回其指针
  if(!T)  return NULL;
  T->size--;
  if(key==T->key||key<T->key&&!T->left||key>T->key&&!T->right)
  {
    SBTNode *del;
    if(!T->left||!T->right){
      del=T;
      T=(T->left?T->left:T->right);
    }
    else{
      del=SBT_Delete(T->right,key-1);
      T->key=del->key;  //若有卫星数据也需复制
    }
    return del;
  }
  else return SBT_Delete(key<T->key?T->left:T->right,key);
}
SBTNode *SBT_Pred(SBTree T, long key){
  //返回指向拥有比key小的最大关键字的节点的指针
  if(!T)  return NULL;
  if(key<=T->key)  return SBT_Pred(T->left,key);
  else{
    SBTNode *pred=SBT_Pred(T->right,key);
    return (!pred?T:pred);
  }
}
SBTNode *SBT_Succ(SBTree T,long key){
  //返回指向拥有比key大的最小关键字的节点的指针
  if(!T)  return NULL;
  if(key>=T->key)  return SBT_Succ(T->right,key);
  else{
    SBTNode *succ= SBT_Succ(T->left,key);
    return(!succ?T:succ);
  }
}
SBTNode *SBT_Select(SBTree T, unsigned long i){
  //从树T中找到关键字第i小的结点并返回其指针
  if(!T||i>T->size)  return NULL;
  unsigned long r = (!T->left?0:T->left->size)+1;
  if(i==r)  return T;
  else if(i<r)  return SBT_Select(T->left,i);
  else return SBT_Select(T->right,i-r);
}
unsigned long SBT_Rank(SBTree T, long key){
  //返回关键字为key的节点在树T中的秩
  //若不存在此节点则返回0
  if(!T)  return 0;
  if(T->key==key)  return (!T->left?0:T->left->size)+1;
  else if(key<T->key)  return SBT_Rank(T->left,key);
  else{
    unsigned long r=SBT_Rank(T->right,key);
    return r==0?0:r+(!T->left?0:T->left->size)+1;
  }
}
下面是一个根据上面的版本修改得来的更简练的版本，代码实际长度约90行：
/****************************************
*              SBT.cc
*
*      Mon Jun 18 12:17:48 2007
*     Copyright  2007  巨菜逆铭
* 
******************************************/
 
//————SBT的储存结构————
struct SBTNode{
   SBTNode *ch[2],*p;   //ch[0]、ch[1]分别为左右孩子，p为双亲
   long key;   //这里省略了卫星数据域
   unsigned long size;
   SBTNode(long _key,unsigned long _size);
}NIL=SBTNode(0,0);
typedef SBTNode *SBTree;
SBTNode::SBTNode(long _key,unsigned long _size=1){ //构造函数：未考虑卫星数据
   ch[0]=ch[1]=p=&NIL;
   size=_size;
   key=_key;
} 
 
//————SBT基本操作函数原型说明————
SBTNode *SBT_Search(SBTree T,long key);
   //在T中中寻找关键字为key的结点
   //若能找到则返回指向它的指针，否则返回NULL
void SBT_Insert(SBTree &T, SBTNode* x);
   //将节点x插入树中
SBTNode *SBT_Delete(SBTree &T, long key);
   //从以T为根的SBT中删除一个关键字为key的结点并返回“实际”被删除结点的指针
   //如果树中没有一个这样的结点，删除搜索到的最后一个结点并返回其指针
SBTNode *SBT_Pred(SBTree T, long key);
   //返回指向关键字为key的节点在T的中序遍历中的直接前趋的指针
   //要求T中必须有关键字为key的节点
SBTNode *SBT_Succ(SBTree T,long key);
   //返回指向关键字为key的节点在T的中序遍历中的直接后继的指针
   //要求T中必须有关键字为key的节点
SBTNode *SBT_Select(SBTree T, unsigned long i);
   //从树T中找到关键字第i小的结点并返回其指针
unsigned long SBT_Rank(SBTree T, long key);
   //返回关键字为key的节点在树T中的秩
   //若不存在此节点则返回0
 
 
//————SBT的修复操作————
inline void SBT_Rotate(SBTree &x, bool flag){
   //旋转：flag==0为左旋，否则为右旋
   SBTNode *y=x->ch[!flag];
   x->ch[!flag]=y->ch[flag];
   if(y->ch[flag]!=&NIL)   y->ch[flag]->p=x;   //维护p
   y->ch[flag]=x;
   y->p=x->p;   //维护p
   x->p=y;   //维护p
   y->size=x->size;
   x->size=x->ch[0]->size+x->ch[1]->size+1;
   x=y;
}
 
 
void SBT_Maintain(SBTree &T,bool flag){
   //维护操作的核心：保持
   if(T->ch[flag]->ch[flag]->size>T->ch[!flag]->size)   //情况1
      SBT_Rotate(T,!flag);
   else if(T->ch[flag]->ch[!flag]->size>T->ch[!flag]->size){ //情况2
      SBT_Rotate(T->ch[flag],flag);
      SBT_Rotate(T,!flag);
   }
   else return;   //无需修复
   SBT_Maintain(T->ch[0],0);   //修复左子树
   SBT_Maintain(T->ch[1],1);   //修复右子树
   SBT_Maintain(T,0);   //修复整棵树
   SBT_Maintain(T,1);
}
 
 
//————SBT基本操作的算法描述————
SBTNode *SBT_Search(SBTree T,long key){
   //在T中中寻找关键字为key的结点
   //若能找到则返回指向它的指针，否则返回NULL
   return T==&NIL||T->key==key?T:SBT_Search(T->ch[key>T->key],key);
}
 
void SBT_Insert(SBTree &T, SBTNode* x){
   //将节点x插入树中
   if(T==&NIL)   T=x;
   else{
      T->size++;
      x->p=T;   //维护p
      SBT_Insert(T->ch[x->key>T->key],x);
      SBT_Maintain(T,x->key>T->key);
   }
}
SBTNode *SBT_Delete(SBTree &T, long key){
   //从以T为根的SBT中删除一个关键字为key的结点并返回“实际”被删除结点的指针
   //如果树中没有一个这样的结点，删除搜索到的最后一个结点并返回其指针
   if(T==&NIL)   return &NIL;
   T->size--;
   if(key==T->key||T->ch[T->key<key]==&NIL){
      SBTNode *toDel;
      if(T->ch[0]==&NIL||T->ch[1]==&NIL){
         toDel=T;
         SBTNode *ch = T->ch[T->ch[1]!=&NIL];
         if(ch!=&NIL)   ch->p=T->p;   //维护p
         T=ch;
      }
      else{
         toDel=SBT_Delete(T->ch[1],key-1);
         T->key=toDel->key;   //若有卫星数据也需复制
      }
      return toDel;
   }
   else return SBT_Delete(T->ch[key>T->key],key);
}
SBTNode *SBT_Pred(SBTree T, long key){
   //返回指向拥有比key小的最大关键字的节点的指针
   if(T==&NIL)   return &NIL;
   if(key<=T->key)   return SBT_Pred(T->ch[0],key);
   else{
      SBTNode *pred=SBT_Pred(T->ch[1],key);
      return (pred!=&NIL?pred:T);
   }
}
SBTNode *SBT_Succ(SBTree T,long key){
   //返回指向拥有比key大的最小关键字的节点的指针
   if(T==&NIL)   return &NIL;
   if(key>=T->key)   return SBT_Succ(T->ch[1],key);
   else{
      SBTNode *succ= SBT_Succ(T->ch[0],key);
      return(succ!=&NIL?succ:T);
   }
}
SBTNode *SBT_Select(SBTree T, unsigned long i){
   //从树T中找到关键字第i小的结点并返回其指针
   if(i>T->size)   return &NIL;
   unsigned long r = T->ch[0]->size+1;
   if(i==r)   return T;
   else return SBT_Select(T->ch[i>r],i>r?i-r:i);
}
unsigned long SBT_Rank(SBTree T, long key){
   //返回关键字为key的节点在树T中的秩
   //若不存在此节点则返回0
   if(T==&NIL)   return 0;
   if(T->key==key)   return T->ch[0]->size+1;
   else if(key<T->key)   return SBT_Rank(T->ch[0],key);
   else{
      unsigned long r=SBT_Rank(T->ch[1],key);
      return r==0?0:r+T->ch[0]->size+1;
   }
}
下面是一个根据上面的版本修改得来的版本，代码实际长度未统计：
/****************************************
*              SBT.cpp
*
*     2008-11-17 17:06:02 Fixed a bug in function SBT_Delete, it's now be test.
*     2008-11-15 16:34:19 Give a new versin SBT_Delete that we don't need to using key-1.
*     Any problem contact yonggangluo@hotmail.com
*     Copyright  2008  Yonggang Luo base on 巨菜逆铭
*
******************************************/
#include <string.h>
#include <iostream>
typedef int32_t key_t;
struct SBTNode {
    SBTNode *p,*ch[2]; ///ch[0]、ch[1]分别为左右孩子，p为双亲
    size_t size;
    key_t key;///这里省略了卫星数据域
    SBTNode(key_t _key,size_t _size);///构造函数：未考虑卫星数据
}NULL_NODE(0,0);
typedef SBTNode *SBTree;
SBTree NULL_TREE = &NULL_NODE;
SBTNode::SBTNode(key_t _key, size_t _size=1) {
    p=ch[0]=ch[1]= NULL_TREE;
    key=_key, size=_size;
}
 
bool cmp(key_t x, key_t y);
 
//————SBT的旋转操作————
inline void SBT_Rotate(SBTree &x, bool flag) {
    //flag: 0为将左子节点移到根, 1为将右子节点移到根
    SBTree sub=x->ch[flag], &leaf = sub->ch[!flag];
    x->ch[flag] = leaf;
    if (leaf!=NULL_TREE) leaf->p = x; /*设置双亲p*/
    sub->p = x->p; /*设置双亲p*/
    x->p = sub; /*设置双亲p*/
    leaf = x;
    sub->size = x->size;
    x->size = x->ch[0]->size + x->ch[1]->size +1;
    x = sub;
}
 
//————SBT的维护操作————
void SBT_Maintain(SBTree &T,bool flag) {
    if (T->ch[flag]->ch[!flag]->size > T->ch[!flag]->size) SBT_Rotate(T->ch[flag], !flag);
    else if (T->ch[flag]->ch[flag]->size <= T->ch[!flag]->size) return;
    SBT_Rotate(T, flag);
    SBT_Maintain(T->ch[0],0);   //修复左子树
    SBT_Maintain(T->ch[1],1);   //修复右子树
    SBT_Maintain(T,0);          //修复整棵树
    SBT_Maintain(T,1);
}
 
//————SBT的插入操作————
void SBT_Insert(SBTree &T, SBTNode* x) {
    //将节点x插入树中
    if (T!=NULL_TREE) {
        ++T->size;
        x->p =T; /*设置双亲p*/
        SBT_Insert(T->ch[cmp(T->key, x->key)], x);
        SBT_Maintain(T, cmp(T->key, x->key));  /* here  must be verify*/
    } else T=x;
}
 
//————SBT的查找————
SBTree &SBT_Search(SBTree *T, key_t key, int resize=0) {
    //在T中中寻找关键字为key的结点
    //若能找到则返回指向它的指针，否则返回NULL_TREE
    while (*T!=NULL_TREE && (*T)->key!=key) {
        (*T)->size += resize;
        T=&((*T)->ch[cmp((*T)->key, key)]);
    }
    return *T;
}
 
//————SBT的极值————
SBTree &SBT_Extremum(SBTree *T, bool maximum = true, int resize=0) { /*返回一棵树的极值 */
    while ((*T)->ch[maximum]!=NULL_TREE) {
        (*T)->size += resize;
        T=&(*T)->ch[maximum];
    }
    return *T;
}
 
/*删除一棵树的根节点，并返回被删节点*/
SBTNode *SBT_Delete(SBTree &T){
    --T->size; ///维护size
    int flag = T->ch[0]==NULL_TREE || T->ch[1]==NULL_TREE;
    SBTree *P = flag ? &T:&SBT_Extremum(&T->ch[1] , 0, -1); ///如果T有两棵子树，那么我们就先删T的后继
    SBTree D=*P;///D用来保存 真正 被删的节点
    *P=D->ch[D->ch[0]==NULL_TREE]; ///把被删节点设为此节点的其中一个儿子
    if (*P!=NULL_TREE) (*P)->p = D->p; //设置双亲p
    if (flag) return D; ///如果 flag，则T是真正应当被删的节点，故直接返回D，否则继续处理D
    T->key = D->key;///简单替换
    /*std::swap(T, D);///本质替换
    memcpy(T, D, sizeof(*T)-sizeof(T->key)); //把关系复制过去
    if (T->ch[0]!=NULL_TREE) T->ch[0]->p = T; //设置双亲p
    if (T->ch[1]!=NULL_TREE) T->ch[1]->p = T; //设置双亲p
    */
    return D;
}
 
//————SBT的删除————
SBTNode *SBT_Delete(SBTree &T, key_t key) {
    //如果树中没有一个这样的结点，则返回 NULL_TREE
    if (SBT_Search(&T, key) == NULL_TREE) return NULL_TREE; /*表示key不在树中**/
    return SBT_Delete(SBT_Search(&T, key, -1)); /*RP 就是指向待删子树的指针*/
}
 
SBTree &SBT_Near(SBTree &T, key_t key, bool flag) {
	///flag: 0 前驱 ;  1 后继
    if (T==NULL_TREE)  return T;
    if (key==T->key || cmp(T->key, key)==flag ) return SBT_Near(T->ch[flag],key, flag);
    SBTree &near=SBT_Near(T->ch[!flag],key, flag);
    return near!=NULL_TREE ? near:T;
}
 
//————SBT的选取第i个元素————
SBTree SBT_Select(SBTree T, size_t i) {
    ///从树T中找到关键字第i的结点并返回其指针,从1开始计数，如果没有就返回NULL_TREE
    if (i > T->size) return NULL_TREE;
    size_t r = T->ch[0]->size+1;
    return i==r ? T:SBT_Select(T->ch[i>r], i>r?i-r:i);
}
 
//————SBT的给定节点是第几个元素————
size_t SBT_Rank(SBTree T, key_t key) {
    ///此功能不完善，如果同一个key有两个不同的rank,那么返回值是其中的任意一个的rank。
    ///可以考虑用二分法加 SBT_Select实现
    ///若不存在此节点则返回0
    if (T==NULL_TREE) return 0;
    if (key==T->key) return T->ch[0]->size+1;
    if (cmp(key, T->key)) return SBT_Rank(T->ch[0],key);
    size_t r=SBT_Rank(T->ch[1],key);
    return r==0?0:r+T->ch[0]->size+1;
}
 
inline void SBT_Free(SBTNode *t) {
    if (t!=NULL_TREE) delete t;
}
 
/**下面是一些测试代码**/
 
bool cmp(key_t x, key_t y)
{
    return x<y;
}
 
#include <stdlib.h>
#include <time.h>
 
int deep;
size_t count;
SBTree root=NULL_TREE;
 
void SBT_Print(SBTree T, int d) {
    if (T==NULL_TREE) return;
    SBT_Print(T->ch[0], d+1);
    static size_t r;
    key_t value;
    printf("Rank = %d\n", r=SBT_Rank(root, T->key));
    printf("value = %d\n", value = SBT_Select(root, r)->key);
    if (value!=T->key)
    {
        printf("Error!");
        exit(1);
    }
    for (int i=0; i<d; ++i) printf("  ");
    printf("%d\n", T->key);
    if ( (T->ch[0]->p!=NULL_TREE && T->ch[0]->p!=T) || (T->ch[1]->p!=NULL_TREE && T->ch[1]->p!=T) ) {
        printf("Error parent!\n");
        exit(0);
    }
    SBT_Print(T->ch[1], d+1);
}
 
void show() {
    if (root->p!=NULL_TREE) printf("Error!\n");
    printf("The size of the tree is %d\n", root->size);
    printf("The tree is\n");
    count = 0;
    SBT_Print(root,0);
    if (root->size != count) {
        printf("root->size = %u\n count = %u \n Error size!\n", root->size, count);
    }
    printf("End of the tree!\n\n");
}
 
int main() {
 
    srand(time(NULL));
    size_t n=3000000;
    key_t x;
    freopen("output.txt","w",stdout);
//#define READFILE
#ifdef READFILE
    char order;
    freopen("input.txt","r",stdin);
    scanf("%d\n",&n);
    for (size_t i=0; i<n; ++i) {
        printf("i=%u\n", i);
        scanf("%c %d\n", &order, &x);
        printf("x=%d\n", x);
        if (order=='I')
            SBT_Insert(root, new SBTNode(x));
        else
            SBT_Free(SBT_Delete(root, x));
        show();
        if (NULL_TREE->key !=0) printf("Error NULL");
 
    }
#else
    for (size_t i=0; i<n; ++i) {
 
        if (i%3==0)
            //printf("D %ld\n", x), SBT_Free(SBT_Delete(&root, x));
            SBT_Free(SBT_Delete(root, x));
        else
            //printf("I %ld\n",x = rand()),SBT_Insert(root, new SBTNode(x));
            SBT_Insert(root, new SBTNode(x=rand()));
        //show();
 
        if (NULL_TREE->key !=0) printf("Error NULL");
    }
  //  show();
    SBTNode *pre, *suc;
    FILE* compare=fopen("compare.txt","w");
    for (int i=0; i<32767; ++i)
    {
        pre = SBT_Near(root, i, 0);
        suc = SBT_Near(root, i, 1);
//        fprintf(compare,"pre=%d i=%d suc=%d\n",pre->key, i, suc->key);
    }
 
#endif
 
    return 0;
}
给出一个更加简洁的版本，对maintain操作的使用提出了简化（事实上分拆了maintain,省略相当一部分没有必要的判断，主要用leftBalance和rightBalance替换maintain的操作），使用了一些编程技巧（主要是哨兵技巧）
/**********************************************************************
     Size Balance Tree的精简实现
     2012.02.11   汪子逸 Copyright Reserved.
     转载请注明.
 
     代码与注释一起给出，以对部分技巧进行说明
     重点是使用哨兵结点简化NULL判断
     Insert操作带入平衡，省略maintain操作
     Delete操作给出一个略微复杂的实现
     Search Select Rank操作都十分简单
***********************************************************************/
 
/*基本存储结构*/
struct SBTNode 
{
	int data;
	int size;
	struct SBTNode *lchild;
	struct SBTNode *rchild;
};
 
/*Nil哨兵结点，用来代替NULL表示空，可以极大地简化NULL判断*/
SBTNode Nil={0,0,&Nil,&Nil};
 
/*左旋操作，两个平衡树基本操作之一*/
void lRotate(SBTNode* &t)
{
	/*交接*/
	SBTNode *p = t->rchild;
	t->rchild  = p->lchild;
	p->lchild  = t;
 
	/*调整*/
	p->size = t->size;
	t->size = t->lchild->size + t->rchild->size + 1;
 
	/*返回*/
	t = p;
}
 
/*右旋操作，两个平衡树基本操作之二*/
void rRotate(SBTNode *t)
{
	/*交接*/
	SBTNode *p = t->lchild;
	t->lchild  = p->rchild;
	p->rchild  = t;
 
	/*调整*/
	p->size = t->size;
	t->size = t->lchild->size + t->rchild->size +1;
 
	/*返回*/
	t = p;
}
 
/*左平衡操作，用于平衡LL型和LR型*/
void leftBalance(SBTNode *&t)
{
	if(t->lchild->lchild->size > t->rchild->size)
		rRotate(t);
	else if(t->lchild->rchild->size > t->rchild->size)
		lRotate(t->lchild),rRotate(t);
}
 
/*右平衡操作，用于平衡RR型和RL型*/
void rightBalance(SBTNode *&t)
{
	if(t->rchild->rchild->size > t->lchild->size)
		lRotate(t);
	else if(t->rchild->lchild->size > t->lchild->size)
		rRotate(t->rchild),lRotate(t);
}
 
/*插入操作，注意可以这里使用leftBalance和rightBalance,省略maintain操作*/
void insert(SBTNode *&t,int x)
{
	if(t== &Nil)
	{
		SBTNode *p = new SBTNode ;
		p->data = x;
		p->size = 1;
		p->lchild = &Nil;
		p->rchild = &Nil;
		t = p;	
	}
	else
	{
		if(x<t->data){t->size++; insert(t->lchild,x); leftBalance(t) ;}
		else         {t->size++; insert(t->rchild,x); rightBalance(t);}	
	}
}
/********************************************************************
   删除操作，也是最难正确实现的操作了，但其实一般题目中很少用，
   如果直接假设int x在树中是存在的，那么将简单很多，但这并不十分合理
   删除的总体是思路是这样的：
 
   如果比当前结点值小，到左树上面去删除
   如果比当前结点值大，到右树上面去删除
   如果等于当前结点值，那么应该删除本结点，但直接删除可能会破坏树的结构
       如果左子树为空，返回右子树
       如果右子树为空，返回左子树
       如果左右子树都不为空，应该找到其中序前驱，或者后继来替换这个结点
 
   在不考虑size域的情况下，自此应该可以写出递归版本的删除了
   但考虑size域呢，如果假设int x一定存在，那么只需要沿路径size--就可以
   但如果还可能int x不存在呢，能直接沿路size--吗？这是不可以的
   那么只有先尝试递归向下删除，查看删除结果，再判断是否size--，那么一些
   简洁的写法不得不变的略复杂一下
 
   如果不需要Delete操作，那么数组静态实现是更好的选择，因为简单很多
*********************************************************************/
 
SBTNode* Delete(SBTNode *&t,int x)/*删除t为根的树中，第一个含x的结点*/
{                                           /*t被修改为新的根*/
	/*空树不需要删除*/
	if(t==&Nil) return &Nil;
 
	SBTNode *p = &Nil;/*记录被删除的结点，并返回*/
	/*应该到左子树上寻找删除结点*/
	if     (x<t->data){	p = Delete(t->lchild,x);}
 
	/*应该到右子树上寻找删除结点*/
	else if(x>t->data){	p = Delete(t->rchild,x);}
 
	/*删除本结点*/
	else/* x==t->data */
	{	
		/*如果左右子树都不为空*/
		if(t->lchild !=&Nil && t->rchild != &Nil)
		{
			/*找到中序的前驱，左子树的最右结点*/
			SBTNode *f = t;
			p = f->lchild;
			while(p->rchild != &Nil)
			{	f=p; p=p->rchild;  }
 
			/*p为用来替换根的结点，f是其父结点*/
			if  (p==f->rchild)	{f->rchild = p->lchild;}
			else/*p==f->lchild*/{f->lchild = p->lchild;}
 
			/*t和p互换数据*/
			t->data ^= p->data;
			p->data ^= t->data;
			t->data ^= p->data;
		}
		/*如果左子树为空*/
		else if(t->lchild==&Nil)
		{	p = t; t = t->rchild;}
		/*如果右子树为空*/
		else
		{	p = t; t = t->lchild;}
	}
	/*调整大小,删除后t可能是Nil*/
	if(t!=&Nil) t->size = t->lchild->size + t->rchild->size +1;
	return p;
}
 
SBTNode * Search(SBTNode *t,int x)
{
	if(t==&Nil || t->data == x)
		return t;
	else
		Search(x<t->data? t->lchild:t->rchild,x);
}
 
/*返回第k大的结点,返回最小值Select(t,1)即可*/
SBTNode* Select(SBTNode *t,int k)
{
	if(t==&Nil || k>t->size) return &Nil;
 
	int off = k - t->lchild->size-1;/*off表示比根大多少个位置*/
	if     (off==0) return t;
	else if(off<0)  return Select(t->lchild,k);
	else            return Select(t->rchild,off);
}
 
/*返回x如果插入t，排在第多少的位置,x可以目前还不在t中*/
int Rank(SBTNode *t,int x)
{
	if(t==&Nil) return 1;/*空树，插入即是最大*/
 
	if     (x< t->data) return Rank(t->lchild,x);
	else if(x> t->data) return t->lchild->size+1 + Rank(t->rchild,x);
	else /*x==t->data)*/return t->lchild->size+1;
}
 
/*中序遍历，方便调试用的*/
void InOrder(SBTNode *t)
{
	if(t!=&Nil)
	{
		InOrder(t->lchild);
		printf("%d\n",t->data);
		InOrder(t->rchild);
	}
}
 
/*测试树的高度，方便测试树的形态*/
int height(SBTNode *t)/*返回树的高度*/
{
	if(t==&Nil) return 0;
	return
	height(t->lchild) >= height(t->rchild) ? 
	height(t->lchild) +1:
	height(t->rchild) +1;
}
 
/*下面是测试用的主函数，因为使用了时间测试，请include<time.h>*/
int main()
{
	SBTNode *root = &Nil;
 
	const int n = 10000;	
	clock_t start = clock();
	/*********************/
	for(int i=0; i<n; ++i)
	{	insert(root,i);	}
 
	/*********************/
	clock_t end = clock();
	printf("insert %d data time used is %d ms\n",n,end-start);
 
	for(int i=4000; i<n; ++i)
	{	Delete(root,i); 	}
 
	/*求height的函数会遍历整棵树，所以比较耗时*/
	printf("the size of left  SBTree is %d\n",root->lchild->size);
	printf("the size of right SBTree is %d\n",root->rchild->size);
	printf("the height of left  SBTree is %d\n",height(root->lchild));
	printf("the height of right SBTree is %d\n",height(root->rchild));
	printf("the height of SBTree is %d\n",height(root));
 
	printf("the rank of 15 is %d \n",Rank(root,15));
 
	system("pause");
	return 0;
}