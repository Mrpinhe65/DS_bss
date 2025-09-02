#include "../include/bintree.hpp"
#include "../include/linkedqueue.hpp"
#include "../include/seqstack.hpp"
#include <string.h>

int main(int argc, char *argv[]) {
  // char *str="ABC##DE##F##G#H##";
  char str1[] = "ABC##DE##F##G#H##";
  char str2[] = "ABC1##2##DE##F##G#H#ij##k##";
  BinTree mytree;
  InitBinTree(&mytree, '#');
  // CreateBinTree_1(&mytree); // ABC##DE##F##G#H##
  //  CreateBinTree_2(&mytree); // ABC##DE##F##G#H##
  //  CreateBinTree_3(&mytree);      // ABC##DE##F##G#H##
  CreateBinTree_4(&mytree, str1); // ABC##DE##F##G#H##
  PreOrder(&mytree);
  printf("\n");

  InOrder(&mytree);
  printf("\n");

  PostOrder(&mytree);
  printf("\n");

  LevelOrder(&mytree);
  printf("\n");

  printf("Size = %d\n", TreeSize(&mytree));

  printf("Height = %d\n", Height(&mytree));

  BinTreeNode *p = Search(&mytree, 'B');
  printf("Search result = %p\n", p);

  BinTreeNode *parent = Parent(&mytree, p);
  printf("[%c/%p]'s Parent = %c, Parent's Address= %p\n", p->data, p,
         parent->data, parent);

  BinTree youtree;
  InitBinTree(&youtree, '#');
  CopyBinTree(&youtree, &mytree);

  LevelOrder(&youtree);
  printf("\n");

  BinTreeClear(&youtree);
  // BinTreeClear(&mytree);

  printf("非递归方式后序访问二叉树\n");

  PostOrder_nr(&mytree);
  printf("\n");

  char VLR[] = "ABCDEFGH";
  char LVR[] = "CBEDFAGH";
  char LRV[] = "CEFDBHGA";
  int n = strlen(VLR);

  BinTree restonetree;
  InitBinTree(&restonetree, '#');

  RestoneBinTree(&restonetree, VLR, LVR, n);

  printf("根据先序和中序恢复出来的二叉树\n");
  PreOrder(&restonetree);
  printf("\n");

  return 0;
}
///////////////////////////////////////////////////////////
/// 根据先序中序后序恢复二叉树
// void RestoneBinTree(BinTree*bt,char*VLR,char*LVR,int n);
// void RestoneBinTree_f(BinTreeNode*&t,char*VLR,char*LVR,int n);
