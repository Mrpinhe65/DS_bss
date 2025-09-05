#include "cstree.hpp"

void InitTree(Tree *tree, ElemType ref) {
  tree->root = NULL;
  tree->refvalue = ref;
}
void CreateTree(Tree *tree, char *str) {
  CreateTree_func(tree, tree->root, str);
}

void CreateTree_func(Tree *tree, TreeNode *&t, char *&str) {
  if (*str == tree->refvalue) {
    t = NULL;
  } else {
    t = (TreeNode *)malloc(sizeof(TreeNode));
    assert(t != NULL);
    t->data = *str;
    CreateTree_func(tree, t->firstChild, ++str);
    CreateTree_func(tree, t->nextSibling, ++str);
  }
}

TreeNode *Root(Tree *tree) { return tree->root; }

TreeNode *FirstChild(Tree *tree) { return FirstChild_func(tree->root); }
TreeNode *FirstChild_func(TreeNode *t) {
  if (t == NULL)
    return NULL;
  return t->firstChild;
}
TreeNode *NextSibling(Tree *tree) { return NextSibling_func(tree->root); }
TreeNode *NextSibling_func(TreeNode *t) {
  if (t == NULL)
    return NULL;
  return t->nextSibling;
}

TreeNode *Find(Tree *tree, ElemType data) {
  return Find_func(tree->root, data);
}
TreeNode *Find_func(TreeNode *t, ElemType data) {
  if (t == NULL)
    return NULL;
  if (t->data == data)
    return t;
  TreeNode *p = Find_func(t->firstChild, data);
  if (p != NULL)
    return p;
  return Find_func(t->nextSibling, data);
}
TreeNode *Parent(Tree *tree, TreeNode *cur) {
  return Parent_func(tree->root, cur);
}
TreeNode *Parent_func(TreeNode *t, TreeNode *cur) {
  if (t == NULL || cur == NULL || t == cur)
    return NULL;

  TreeNode *q = t->firstChild;
  TreeNode *parent;
  while (q != NULL && q != cur) {
    parent = Parent_func(q, cur);
    if (parent != NULL)
      return parent;
    q = q->nextSibling;
  }
  if (q != NULL && q == cur)
    return t;
  return NULL;
}
