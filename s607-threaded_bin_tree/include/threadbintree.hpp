#pragma once
#include <assert.h>
#include <malloc.h>
#include <stdio.h>

typedef char ElemType;

typedef enum { LINK, THREAD } Tag_Type;

typedef struct BinTreeNode {
  ElemType data;                  // 数据域
  struct BinTreeNode *leftchild;  // 左孩子指针
  struct BinTreeNode *rightchild; // 右孩子指针
  Tag_Type ltag; // 左指针标志 0/LINK--左孩子指针  1/THREAD--前驱指针
  Tag_Type rtag; // 右指针标志 0/LINK--右孩子指针  1/THREAD--后继指针
} BinTreeNode;

typedef struct BinTree {
  BinTreeNode *root; // 根指针
  ElemType refvalue; // 停止标志
} BinTree;

BinTreeNode *_BuildNodeBymalloc(ElemType data);

void InitBinTree(BinTree *bt, ElemType ref);
void CreateBinTree(BinTree *bt, char *str);
void CreateBinTree_i(BinTree *&bt, BinTreeNode *&t, char *&str);
void CreateInThread(BinTree *bt);
void CreateInThread_i(BinTreeNode *&t, BinTreeNode *&pre);

void PreOrder(BinTree *bt);
void PreOrder(BinTreeNode *t);
void InOrder(BinTree *bt);
void InOrder(BinTreeNode *t);
void PostOrder(BinTree *bt);
void PostOrder(BinTreeNode *t);
