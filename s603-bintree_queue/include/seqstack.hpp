#ifndef __SEQSTACK_H__
#define __SEQSTACK_H__

#include <assert.h>
#include <malloc.h>
#include <stdio.h>

// #define ElemType in
#define STACK_INIT_SIZE 8
#define STACK_INC_SIZE 3

struct BinTreeNode;

namespace stack {
typedef BinTreeNode *ElemType;
};

typedef struct SeqStack {
  stack::ElemType *base;
  int capacity;
  int top;
} SeqStack;

#endif //__SEQSTACK_H__

// Declaration
bool full_st(SeqStack *s);
bool empty_st(SeqStack *s);

void InitStack(SeqStack *s);
void push_st(SeqStack *s, stack::ElemType data);
void show_st(SeqStack *s);
void pop_st(SeqStack *s);
bool getTop(SeqStack *s, stack::ElemType *val);
int length_st(SeqStack *s);

bool inc_st(SeqStack *s);
