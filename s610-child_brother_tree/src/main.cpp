#include "cstree.hpp"

int main(int argc, char *argv[]) {
  Tree tree;
  InitTree(&tree, '#');

  char str[] = "RAD#E##B#CFG#H#K#####"; // 图：孩子兄弟树.PNG
  CreateTree(&tree, str);
  TreeNode *root = Root(&tree);
  printf("root = %p\n", root);

  TreeNode *p = Find(&tree, 'C');
  if (p != NULL)
    printf("&[%c] = %p\n", p->data, p);
  else
    printf("%p\n", p);
  TreeNode *parent = Parent(&tree, p);
  if (parent != NULL)
    printf("[%c] parent = %c\n", p->data, parent->data);
  else
    printf("No Parent!\n");
  return 0;
}
