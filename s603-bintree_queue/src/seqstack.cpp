#include "../include/seqstack.hpp"

// Implementation
bool full_st(SeqStack *s) { return s->top >= s->capacity; }

bool empty_st(SeqStack *s) { return s->top == 0; }

void InitStack(SeqStack *s) {
  s->base =
      (stack::ElemType *)malloc(sizeof(stack::ElemType) * STACK_INIT_SIZE);
  assert(s != NULL);
  s->capacity = STACK_INIT_SIZE;
  s->top = 0;
}

void push_st(SeqStack *s, stack::ElemType data) {
  if (full_st(s) && !inc_st(s)) { // 栈满后，inc_st(s) realloc 新的增量后的空间
    printf("stack full,can't push %p\n", data);
    return;
  }
  s->base[s->top++] = data;
  // s->top++;
}

void show_st(SeqStack *s) {
  for (int i = s->top - 1; i >= 0; i--) {
    printf("%p ", s->base[i]);
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
bool getTop(SeqStack *s, stack::ElemType *val) { // 只取栈顶元素，不出栈
  if (empty_st(s)) {
    printf("stack empty,can't get data!\n");
    return false;
  }
  *val = s->base[s->top - 1];
  return true;
}
int length_st(SeqStack *s) { return s->top; }

bool inc_st(SeqStack *s) {
  stack::ElemType *newbase = (stack::ElemType *)realloc(
      s->base, sizeof(stack::ElemType) * (s->capacity + STACK_INC_SIZE));
  if (newbase == NULL) {
    printf("out of memory,can't realloc!\n");
    return false;
  }
  s->base = newbase;
  s->capacity += STACK_INC_SIZE;
  return true;
}
