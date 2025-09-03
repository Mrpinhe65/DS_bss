#include "../include/bintree.hpp"
#include "../include/linkedqueue.hpp"
#include "../include/seqstack.hpp"

void InitBinTree(BinTree *bt, bintree::ElemType ref) {
  bt->root = NULL;
  bt->refvalue = ref;
}
//////////////////////////////////////////////////////////////////////////
/// 1
void CreateBinTree_1(BinTree *bt) { CreateBinTree_1(bt, &(bt->root)); }

void CreateBinTree_1(BinTree *bt, BinTreeNode **t) {
  bintree::ElemType Item;
  scanf("%c", &Item);
  if (Item == bt->refvalue) {
    (*t) = NULL;
  } else {
    (*t) = (BinTreeNode *)malloc(sizeof(BinTreeNode));
    assert((*t) != NULL);
    (*t)->data = Item;
    CreateBinTree_1(bt, &((*t)->leftchild));
    CreateBinTree_1(bt, &((*t)->rightchild));
  }
}

void CreateBinTree_2(BinTree *bt) { CreateBinTree_2(bt, bt->root); }

void CreateBinTree_2(BinTree *bt, BinTreeNode *&t) {
  bintree::ElemType Item;
  scanf("%c", &Item);
  if (Item == bt->refvalue) {
    t = NULL;
  } else {
    t = (BinTreeNode *)malloc(sizeof(BinTreeNode));
    assert(t != NULL);
    t->data = Item;
    CreateBinTree_2(bt, t->leftchild);
    CreateBinTree_2(bt, t->rightchild);
  }
}

void CreateBinTree_3(BinTree *bt) { bt->root = CreateBinTree_3_(bt); }
BinTreeNode *CreateBinTree_3_(BinTree *bt) {
  bintree::ElemType Item;
  scanf("%c", &Item);
  if (Item == bt->refvalue) {
    return NULL;
  } else {
    BinTreeNode *t = (BinTreeNode *)malloc(sizeof(BinTreeNode));
    t->data = Item;
    t->leftchild = CreateBinTree_3_(bt);
    t->rightchild = CreateBinTree_3_(bt);
    return t;
  }
}
void CreateBinTree_4(BinTree *bt, char *str) {
  CreateBinTree_4(bt, bt->root, str);
}

void CreateBinTree_4(BinTree *bt, BinTreeNode *&t, char *&str) {
  if (*str == bt->refvalue) {
    t = NULL;
  } else {
    t = (BinTreeNode *)malloc(sizeof(BinTreeNode));
    assert(t != NULL);
    t->data = *str;
    CreateBinTree_4(bt, t->leftchild, ++str);
    CreateBinTree_4(bt, t->rightchild, ++str);
  }
}
//////////////////////////////////////////////////////////////////////
/// 2
// 先序/根遍历
void PreOrder(BinTree *bt) { PreOrder(bt->root); }

void PreOrder(BinTreeNode *t) {
  if (t != NULL) {
    printf("%c ", t->data);
    PreOrder(t->leftchild);
    PreOrder(t->rightchild);
  }
}

// 中序/根遍历
void InOrder(BinTree *bt) { InOrder(bt->root); }
void InOrder(BinTreeNode *t) {
  if (t != NULL) {
    InOrder(t->leftchild);
    printf("%c ", t->data);
    InOrder(t->rightchild);
  }
}

// 后序/根遍历
void PostOrder(BinTree *bt) { PostOrder(bt->root); }
void PostOrder(BinTreeNode *t) {
  if (t != NULL) {
    PostOrder(t->leftchild);
    PostOrder(t->rightchild);
    printf("%c ", t->data);
  }
}

// 逐层遍历
void LevelOrder(BinTree *bt) { LevelOrder(bt->root); }

void LevelOrder(BinTreeNode *t) {
  if (t != NULL) {
    LinkedQueue Q;
    initLinkedQueue(&Q);
    enQueue(&Q, t);
    BinTreeNode *v;
    while (!QueueIsEmpty(&Q)) {
      GetHead(&Q, &v);
      DeQueue(&Q);
      printf("%c ", v->data);
      if (v->leftchild != NULL)
        enQueue(&Q, v->leftchild);
      if (v->rightchild != NULL)
        enQueue(&Q, v->rightchild);
    }
  }
}
///////////////////////////////////////////////////
/// 3
int TreeSize(BinTree *bt) { return NodeSize(bt->root); }
int NodeSize(BinTreeNode *t) {
  if (t == NULL)
    return 0;
  else
    return NodeSize(t->leftchild) + NodeSize(t->rightchild) + 1;
}

int Height(BinTree *bt) { return Height_(bt->root); }
int Height_(BinTreeNode *t) {
  if (t == NULL)
    return 0;
  else {
    int left_height = Height_(t->leftchild);
    int right_height = Height_(t->rightchild);
    return 1 + (left_height > right_height ? left_height : right_height);
  }
}

BinTreeNode *Search(BinTree *bt, bintree::ElemType key) {
  return Search_(bt->root, key);
}
BinTreeNode *Search_(BinTreeNode *t, bintree::ElemType key) {
  if (t == NULL)
    return NULL;
  if (t->data == key)
    return t;
  BinTreeNode *p = Search_(t->leftchild, key);
  if (p != NULL)
    return p;
  return Search_(t->rightchild, key);
}

BinTreeNode *Parent(BinTree *bt, BinTreeNode *p) {
  return Parent_(bt->root, p);
}

BinTreeNode *Parent_(BinTreeNode *t, BinTreeNode *p) {
  if (t == NULL || p == NULL)
    return NULL;
  if (t->leftchild == p || t->rightchild == p)
    return t;
  BinTreeNode *q = Parent_(t->leftchild, p);
  if (q != NULL)
    return q;
  return Parent_(t->rightchild, p);
}

BinTreeNode *leftchild_p(BinTreeNode *p) {
  if (p == NULL)
    return NULL;
  return p->leftchild;
}
BinTreeNode *rightchild_p(BinTreeNode *p) {
  if (p == NULL)
    return NULL;
  return p->rightchild;
}

bool BinTreeIsEmpty(BinTree *bt) { return bt->root == NULL; }

void CopyBinTree(BinTree *bt1, BinTree *bt2) {
  CopyBinTree_(bt1->root, bt2->root);
}

void CopyBinTree_(BinTreeNode *&t1, BinTreeNode *t2) {
  if (t2 == NULL)
    t1 = NULL;
  else {
    t1 = (BinTreeNode *)malloc(sizeof(BinTreeNode));
    assert(t1 != NULL);
    t1->data = t2->data;
    CopyBinTree_(t1->leftchild, t2->leftchild);
    CopyBinTree_(t1->rightchild, t2->rightchild);
  }
}

void BinTreeClear(BinTree *bt) {
  if (bt == NULL)
    return;
  BinTreeClear_(bt->root);
}
void BinTreeClear_(BinTreeNode *t) {
  if (t != NULL) {
    BinTreeClear_(t->leftchild);
    BinTreeClear_(t->rightchild);
    free(t);
    t = NULL;
  }
}
//////////////////////////////////
/// 4 非递归的方式后序访问二叉树
void PostOrder_nr(BinTree *bt) {
  if (bt->root == NULL)
    return;
  PostOrder_nr_f(bt->root);
}

void PostOrder_nr_f(BinTreeNode *t) {
  if (t != NULL) {
    SeqStack st;
    InitStack(&st);
    BinTreeNode *p;
    StkNode sn;
    do {
      while (t != NULL) {
        sn.ptr = t;
        sn.tag = L;
        push_st(&st, sn);
        t = t->leftchild;
      }
      bool flag = true;
      while (flag && !empty_st(&st)) {
        getTop(&st, &sn);
        pop_st(&st);
        p = sn.ptr;
        switch (sn.tag) {
        case L:
          sn.tag = R;
          push_st(&st, sn);
          flag = false;
          t = p->rightchild;
          break;
        case R:
          printf("%c ", p->data);
          break;
        }
      }
    } while (!empty_st(&st));
  }
}
///////////////////////////////////////////////////////////
/// 根据先序中序后序恢复二叉树
void RestoreBinTree(BinTree *bt, char *VLR, char *LVR, int n) {
  RestoreBinTree_f(bt->root, VLR, LVR, n);
}
void RestoreBinTree_f(BinTreeNode *&t, char *VLR, char *LVR, int n) {
  if (n == 0) {
    t = NULL;
  } else {
    int k = 0;
    while (VLR[0] != LVR[k])
      k++;
    if (k > n)
      return;
    t = (BinTreeNode *)malloc(sizeof(BinTreeNode));
    assert(t != NULL);
    t->data = LVR[k];
    RestoreBinTree_f(t->leftchild, VLR + 1, LVR, k);
    RestoreBinTree_f(t->rightchild, VLR + k + 1, LVR + k + 1, n - k - 1);
  }
}
////////////////////////////////////////////////////////////
/// 根据中序后序恢复二叉树
void RestoreByInPost(BinTree *bt, char *LVR, char *LRV, int n) {
  RestoreByInPost_f(bt->root, LVR, LRV, n);
}
void RestoreByInPost_f(BinTreeNode *&t, char *LVR, char *LRV, int n) {
  if (n == 0) {
    t = NULL;
  } else {
    int k = 0;
    while (LRV[n - 1] != LVR[k])
      k++;
    if (k > n)
      return;
    t = (BinTreeNode *)malloc(sizeof(BinTreeNode));
    assert(t != NULL);
    t->data = LVR[k];
    RestoreByInPost_f(t->rightchild, LVR + k + 1, LRV + k, n - k - 1);
    RestoreByInPost_f(t->leftchild, LVR, LRV, k);
  }
}
