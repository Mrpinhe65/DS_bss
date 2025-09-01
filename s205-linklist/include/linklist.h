#include <assert.h>
#include <malloc.h>
#include <stdio.h>

typedef struct ElemType {
  int num;
  char name[20];
  float score;
} ElemType;

typedef struct LinkNode {
  ElemType data;
  struct LinkNode* next;
} LinkNode, *LinkHead;
