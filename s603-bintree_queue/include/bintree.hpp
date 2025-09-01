#ifndef __BINTREE_H__
#define __BINTREE_H__

#include <assert.h>
#include <malloc.h>
#include <stdio.h>

// #define ElemType char
namespace bintree {
typedef char ElemType;
}
typedef struct BinTreeNode {
  bintree::ElemType data;
  BinTreeNode *leftchild;
  BinTreeNode *rightchild;
} BinTreeNode;

typedef struct BinTree {
  BinTreeNode *root;
  bintree::ElemType refvalue; // stop flag
} BinTree;

void InitBinTree(BinTree *bt, bintree::ElemType ref);
/////////////////////////////////////////////////////////
/// 1
// 几种方法
// 方法一：C语言
void CreateBinTree_1(BinTree *bt);
void CreateBinTree_1(BinTree *bt, BinTreeNode **t);
// 方法二：c++引用方法
void CreateBinTree_2(BinTree *bt);                  // c语言
void CreateBinTree_2(BinTree *bt, BinTreeNode *&t); // c++
                                                    // 方法三：返回指针的形式
void CreateBinTree_3(BinTree *bt);                  // c语言
BinTreeNode *CreateBinTree_3_(BinTree *bt);
// 方法四
void CreateBinTree_4(BinTree *bt, char *str);                   // c语言
void CreateBinTree_4(BinTree *bt, BinTreeNode *&t, char *&str); // c++
//////////////////////////////////////////////////////////
/// 2 递归方式访问二叉树
void PreOrder(BinTree *bt);
void PreOrder(BinTreeNode *t);
void InOrder(BinTree *bt);
void InOrder(BinTreeNode *t);
void PostOrder(BinTree *bt);
void PostOrder(BinTreeNode *t);
void LevelOrder(BinTree *bt);
void LevelOrder(BinTreeNode *t);
////////////////////////////////////////////////////////////
/// 3
int TreeSize(BinTree *bt);
int NodeSize(BinTreeNode *t);

int Height(BinTree *bt);
int Height_(BinTreeNode *t);

BinTreeNode *Search(BinTree *bt, bintree::ElemType key);
BinTreeNode *Search_(BinTreeNode *t, bintree::ElemType key);

BinTreeNode *Parent(BinTree *bt, BinTreeNode *p);
BinTreeNode *Parent_(BinTreeNode *t, BinTreeNode *p);

BinTreeNode *leftchild_p(BinTreeNode *p);

BinTreeNode *rightchild_p(BinTreeNode *p);

bool BinTreeEmpty(BinTree *bt);

void CopyBinTree(BinTree *bt1, BinTree *bt2);
void CopyBinTree_(BinTreeNode *&t1, BinTreeNode *t2);
void BinTreeClear(BinTree *bt);
void BinTreeClear_(BinTreeNode *t);
////////////////////////////////////////////////////////
/// 4 非递归的方式访问二叉树
void PreOrder_nr(BinTree *bt);
void PreOrder_nr_f(BinTreeNode *t);
// void InOrder_nr(BinTree *bt);
// void InOrder_nr(BinTreeNode *t);
// void PostOrder_nr(BinTree *bt);
// void PostOrder_nr(BinTreeNode *t);

#endif //__BINTREE_H__
