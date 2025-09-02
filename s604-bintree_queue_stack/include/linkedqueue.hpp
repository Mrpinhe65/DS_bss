#ifndef __LINKEDQUEUE_H__
#define __LINKEDQUEUE_H__

#include <assert.h>
#include <malloc.h>
#include <stdio.h>

struct BinTreeNode;
// #define queue::ElemType BinTreeNode*;
namespace queue {
typedef BinTreeNode *ElemType;
}
typedef struct QueueNode {
  queue::ElemType data;
  struct QueueNode *next;
} QueueNode;

typedef struct LinkedQueue {
  QueueNode *front;
  QueueNode *tail;
} LinkedQueue;

void initLinkedQueue(LinkedQueue *q);
bool QueueIsEmpty(LinkedQueue *q);
bool QueueIsEmpty(LinkedQueue *q);
void enQueue(LinkedQueue *lq, queue::ElemType data);
void showQueue(LinkedQueue *lq);
void DeQueue(LinkedQueue *lq);
void GetHead(LinkedQueue *lq, queue::ElemType *v);
void clear_lq(LinkedQueue *lq);
void desroy_lq(LinkedQueue *lq);

#endif // __LINKEDQUEUE_H__
