#ifndef __SEQSTACK_H__
#define __SEQSTACK_H__

#include <algorithm>
#include <assert.h>
#include <iterator>
#include <malloc.h>
#include <stdio.h>

#define ElemType int

#define STACK_INIT_SIZE 8
#define STACK_INC_SIZE 3

typedef struct SeqStack {
  ElemType *base;
  int capacity;
  int top;
} SeqStack;

#endif //__SEQSTACK_H__

// Declaration
bool full_st(SeqStack *s);
bool empty_st(SeqStack *s);

void InitStack(SeqStack *s);
void push_st(SeqStack *s, ElemType data);
void show_st(SeqStack *s);
void pop_st(SeqStack *s);
bool getTop(SeqStack *s, ElemType *val);
int length_st(SeqStack *s);

bool inc_st(SeqStack *s);

void convert_8(int val);

int main() {
  int val = 47183;
  convert_8(val);

  return 0;
}

// Implementation
bool full_st(SeqStack *s) { return s->top >= s->capacity; }

bool empty_st(SeqStack *s) { return s->top == 0; }

void InitStack(SeqStack *s) {
  s->base = (ElemType *)malloc(sizeof(ElemType) * STACK_INIT_SIZE);
  assert(s != NULL);
  s->capacity = STACK_INIT_SIZE;
  s->top = 0;
}

void push_st(SeqStack *s, ElemType data) {
  if (full_st(s) && !inc_st(s)) { // 栈满后，inc_st(s) realloc 新的增量后的空间
    printf("stack full,can't push %d\n", data);
    return;
  }
  s->base[s->top++] = data;
  // s->top++;
}

void show_st(SeqStack *s) {
  for (int i = s->top - 1; i >= 0; i--) {
    printf("%d ", s->base[i]);
  }
  printf("\n");
}
void pop_st(SeqStack *s) {
  if (empty_st(s)) {
    printf("stack empty,can't pop\n");
    return;
  }
  s->top--;
}
bool getTop(SeqStack *s, ElemType *val) { // 只取栈顶元素，不出栈
  if (empty_st(s)) {
    printf("stack empty,can't get data!\n");
    return false;
  }
  *val = s->base[s->top - 1];
  return true;
}
int length_st(SeqStack *s) { return s->top; }

bool inc_st(SeqStack *s) {
  ElemType *newbase = (ElemType *)realloc(
      s->base, sizeof(ElemType) * (s->capacity + STACK_INC_SIZE));
  if (newbase == NULL) {
    printf("out of memory,can't realloc!\n");
    return false;
  }
  s->base = newbase;
  s->capacity += STACK_INC_SIZE;
  return true;
}
void convert_8(int value) {
  SeqStack st;
  InitStack(&st);
  while (value) {
    push_st(&st, value % 8);
    value /= 8;
  }
  show_st(&st);
  int result;
  while (!empty_st(&st)) {
    getTop(&st, &result);
    pop_st(&st);
    printf("%d", result);
  }
  printf("\n");
}
