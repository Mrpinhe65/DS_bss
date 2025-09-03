#include "../include/threadbintree.hpp"

void InitBinTree(BinTree *bt, ElemType ref) {
  bt->root = NULL;
  bt->refvalue = ref;
}

void CreateBinTree(BinTree *bt, char *str) {
  CreateBinTree_i(bt, bt->root, str);
}

void CreateBinTree_i(BinTree *&bt, BinTreeNode *&t, char *&str) {
  if (*str == bt->refvalue) {
    t = NULL;
  } else {
    t = _BuildNodeBymalloc(*str);
    CreateBinTree_i(bt, t->leftchild, ++str);
    CreateBinTree_i(bt, t->rightchild, ++str);
  }
}
// 按中序进行线索化
void CreateInThread(BinTree *bt) {
  BinTreeNode *pre = NULL;
  CreateInThread_i(bt->root, pre);
  pre->rightchild = NULL;
  pre->rtag = THREAD;
}
void CreateInThread_i(BinTreeNode *&t, BinTreeNode *&pre) {
  if (t == NULL)
    return;
  CreateInThread_i(t->leftchild, pre);
  if (t->leftchild == NULL) {
    t->ltag = THREAD;
    t->leftchild = pre;
  }
  if (pre != NULL && pre->rightchild == NULL) {
    pre->rtag = THREAD;
    pre->rightchild = t;
  }
  pre = t;
  CreateInThread_i(t->rightchild, pre);
}

/////////////////////////////////////////////////////
/// 辅助函数
BinTreeNode *_BuildNodeBymalloc(ElemType data) {
  BinTreeNode *s = (BinTreeNode *)malloc(sizeof(BinTreeNode));
  assert(s != NULL);
  s->data = data;
  s->leftchild = NULL;
  s->rightchild = NULL;
  s->ltag = LINK;
  s->rtag = LINK;
  return s;
}
//////////////////////////////////////////////////////////////////////
/// s602函数
void PreOrder(BinTree *bt) { PreOrder(bt->root); }

void PreOrder(BinTreeNode *t) {
  if (t != NULL) {
    printf("%c ", t->data);
    PreOrder(t->leftchild);
    PreOrder(t->rightchild);
  }
}

void InOrder(BinTree *bt) { InOrder(bt->root); }
void InOrder(BinTreeNode *t) {
  if (t != NULL) {
    InOrder(t->leftchild);
    printf("%c ", t->data);
    InOrder(t->rightchild);
  }
}

void PostOrder(BinTree *bt) { PostOrder(bt->root); }
void PostOrder(BinTreeNode *t) {
  if (t != NULL) {
    PostOrder(t->leftchild);
    PostOrder(t->rightchild);
    printf("%c ", t->data);
  }
}
