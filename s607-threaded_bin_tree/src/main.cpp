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

  return 0;
}
