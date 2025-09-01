#ifndef __LINKEDSTACK_H__
#define __LINKEDSTACK_H__

#include <assert.h>
#include <malloc.h>
#include <stdio.h>

#define ElemType int

typedef struct StackNode {
  ElemType data;
  struct StackNode *next;
} StackNode;

typedef StackNode *LinkStack;

#endif // __LINKEDSTACK_H__

void InitStack(LinkStack *s);
void push_st(LinkStack *s, ElemType data);
void show_st(LinkStack *s);

int main() {
  LinkStack st;
  InitStack(&st);
  for (int i = 1; i <= 5; i++) {
    push_st(&st, i);
  }
  show_st(&st);
  return 0;
}
void InitStack(LinkStack *s) {
  *s = NULL;
  //(*s)->next = NULL;
}
void push_st(LinkStack *s, ElemType data) {
  StackNode *t = (StackNode *)malloc(sizeof(StackNode));
  t->data = data;
  if (*s == NULL) {
    *s = t;
    t->next = NULL;
  } else {
    t->next = *s;
    *s = t;
  }
}
void show_st(LinkStack *s) {
  StackNode *p = *s;
  while (p != NULL) {
    printf("%d \n", p->data);
    p = p->next;
  }
}
