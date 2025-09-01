#ifndef __BINTREE_H__
#define __BINTREE_H__

#include <assert.h>
#include <malloc.h>
#include <stdio.h>

#define ElemType char

typedef struct BinTreeNode {
  ElemType data;
  BinTreeNode *leftchild;
  BinTreeNode *rightchild;
} BinTreeNode;

typedef struct BinTree {
  BinTreeNode *root;
  ElemType refvalue;  // stop flag
} BinTree;

void InitBinTree(BinTree *bt, ElemType ref);
/////////////////////////////////////////////////////////
/// 1
// 几种方法
// 方法一：C语言
void CreateBinTree_1(BinTree *bt);
void CreateBinTree_1_sub(BinTree *bt, BinTreeNode **t);
// 方法二：c++引用方法
void CreateBinTree_2(BinTree *bt);                       // c语言
void CreateBinTree_2_sub(BinTree *bt, BinTreeNode *&t);  // c++
// 方法三：返回指针的形式
void CreateBinTree_3(BinTree *bt);  // c语言
BinTreeNode *CreateBinTree_3_sub(BinTree *bt);
// 方法四
void CreateBinTree_4(BinTree *bt, char *str);                        // c语言
void CreateBinTree_4_sub(BinTree *bt, BinTreeNode *&t, char *&str);  // c++
//////////////////////////////////////////////////////////
/// 2
void PreOrder(BinTree *bt);
void PreOrder(BinTreeNode *t);
void InOrder(BinTree *bt);
void InOrder(BinTreeNode *t);
void PostOrder(BinTree *bt);
void PostOrder(BinTreeNode *t);

#endif  //__BINTREE_H__

int main(int argc, char *argv[]) {
  // char *str="ABC##DE##F##G#H##";
  char str1[] = "ABC##DE##F##G#H##";
  char str2[] = "ABC1##2##DE##F##G#H#ij##k##";
  BinTree mytree;
  InitBinTree(&mytree, '#');
  // CreateBinTree_1(&mytree);  // ABC##DE##F##G#H##
  //  CreateBinTree_2(&mytree); // ABC##DE##F##G#H##
  //  CreateBinTree_3(&mytree);      // ABC##DE##F##G#H##
  CreateBinTree_4(&mytree, str2);  // ABC##DE##F##G#H##
  PreOrder(&mytree);
  printf("\n");

  InOrder(&mytree);
  printf("\n");

  PostOrder(&mytree);
  printf("\n");

  return 0;
}

void InitBinTree(BinTree *bt, ElemType ref) {
  bt->root = NULL;
  bt->refvalue = ref;
}
//////////////////////////////////////////////////////////////////////////
/// 1
void CreateBinTree_1(BinTree *bt) { CreateBinTree_1_sub(bt, &(bt->root)); }

void CreateBinTree_1_sub(BinTree *bt, BinTreeNode **t) {
  ElemType Item;
  scanf("%c", &Item);
  if (Item == bt->refvalue) {
    (*t) = NULL;
  } else {
    (*t) = (BinTreeNode *)malloc(sizeof(BinTreeNode));
    assert((*t) != NULL);
    (*t)->data = Item;
    CreateBinTree_1_sub(bt, &((*t)->leftchild));
    CreateBinTree_1_sub(bt, &((*t)->rightchild));
  }
}

void CreateBinTree_2(BinTree *bt) { CreateBinTree_2_sub(bt, bt->root); }

void CreateBinTree_2_sub(BinTree *bt, BinTreeNode *&t) {
  ElemType Item;
  scanf("%c", &Item);
  if (Item == bt->refvalue) {
    t = NULL;
  } else {
    t = (BinTreeNode *)malloc(sizeof(BinTreeNode));
    assert(t != NULL);
    t->data = Item;
    CreateBinTree_2_sub(bt, t->leftchild);
    CreateBinTree_2_sub(bt, t->rightchild);
  }
}

void CreateBinTree_3(BinTree *bt) { bt->root = CreateBinTree_3_sub(bt); }

BinTreeNode *CreateBinTree_3_sub(BinTree *bt) {
  ElemType Item;
  scanf("%c", &Item);
  if (Item == bt->refvalue) {
    return NULL;
  } else {
    BinTreeNode *t = (BinTreeNode *)malloc(sizeof(BinTreeNode));
    t->data = Item;
    t->leftchild = CreateBinTree_3_sub(bt);
    t->rightchild = CreateBinTree_3_sub(bt);
    return t;
  }
}
void CreateBinTree_4(BinTree *bt, char *str) {
  CreateBinTree_4_sub(bt, bt->root, str);
}

void CreateBinTree_4_sub(BinTree *bt, BinTreeNode *&t, char *&str) {
  if (*str == bt->refvalue) {
    t = NULL;
  } else {
    t = (BinTreeNode *)malloc(sizeof(BinTreeNode));
    assert(t != NULL);
    t->data = *str;
    CreateBinTree_4_sub(bt, t->leftchild, ++str);
    CreateBinTree_4_sub(bt, t->rightchild, ++str);
  }
}
//////////////////////////////////////////////////////////////////////
/// 2
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
