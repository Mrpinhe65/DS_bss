#include "../include/threadbintree.hpp"

int main(int argc, char *argv[]) {
  printf("ThreadBinTree\n");

  char str[] = "ABC##DE##F##G#H##";

  BinTree mytree;
  InitBinTree(&mytree, '#');

  CreateBinTree(&mytree, str);

  PreOrder(&mytree);
  printf("\n");

  InOrder(&mytree);
  printf("\n");

  PostOrder(&mytree);
  printf("\n");

  CreateInThread(&mytree);

  BinTreeNode *p;
  p = First(&mytree);
  printf("First p = %p, p->data = %c\n", p, p->data);
  p = Last(&mytree);
  printf("Last = p = %p, p->data = %c\n", p, p->data);

  InOrderThread(&mytree);

  BinTreeNode *s = Search(&mytree, 'B');
  printf("s[&%c] = %p\n", s->data, s);

  BinTreeNode *parent = Parent(&mytree, s);
  printf("Parent = %c\n", parent->data);
  return 0;
}
