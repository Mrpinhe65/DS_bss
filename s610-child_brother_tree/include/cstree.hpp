#pragma once

#include <assert.h>
#include <malloc.h>
#include <stdio.h>

typedef char ElemType;

typedef struct TreeNode {
  ElemType data;
  struct TreeNode *firstChild;  // leftchild
  struct TreeNode *nextSibling; // rightchild
} TreeNode;

typedef struct Tree {
  TreeNode *root;
  ElemType refvalue;
} Tree;

////////////////////////////////////////
/// 函数声明

void InitTree(Tree *tree, ElemType ref);
void CreateTree(Tree *tree, char *str);
void CreateTree_func(Tree *tree, TreeNode *&t, char *&str);
TreeNode *Root(Tree *tree);
TreeNode *FirstChild(Tree *tree);
TreeNode *FirstChild_func(TreeNode *t);
TreeNode *NextSibling(Tree *tree);
TreeNode *NextSibling_func(TreeNode *t);
TreeNode *Find(Tree *tree, ElemType data);
TreeNode *Find_func(TreeNode *t, ElemType data);
TreeNode *Parent(Tree *tree, TreeNode *cur);
TreeNode *Parent_func(TreeNode *t, TreeNode *cur);
