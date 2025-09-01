#ifndef __LINKEDQUEUE_H__
#define __LINKEDQUEUE_H__

#include <assert.h>
#include <malloc.h>
#include <stdio.h>

#define ElemType int

typedef struct QueueNode {
  ElemType data;
  struct QueueNode *next;
} QueueNode;

typedef struct LinkedQueue {
  QueueNode *front;
  QueueNode *tail;
} LinkedQueue;

void initLinkedQueue(LinkedQueue *q);
void enQueue(LinkedQueue *lq, ElemType data);
void showQueue(LinkedQueue *lq);
void DeQueue(LinkedQueue *lq);
void clear_lq(LinkedQueue *lq);
void desroy_lq(LinkedQueue *lq);

#endif // __LINKEDQUEUE_H__

int main() {
  LinkedQueue lq;
  initLinkedQueue(&lq);

  for (int i = 0; i < 10; i++) {
    enQueue(&lq, i);
  }
  showQueue(&lq);
  for (int i = 0; i < 10; i++)
    DeQueue(&lq);
  clear_lq(&lq);
  desroy_lq(&lq);
  return 0;
}
void initLinkedQueue(LinkedQueue *q) {
  QueueNode *s = (QueueNode *)malloc(sizeof(QueueNode));
  assert(s != NULL);
  q->front = s;
  q->tail = s;
  q->front->next = NULL;
}
void enQueue(LinkedQueue *lq, ElemType data) {
  QueueNode *s = (QueueNode *)malloc(sizeof(QueueNode));
  assert(s != NULL);
  s->data = data;
  s->next = NULL;
  lq->tail->next = s;
  lq->tail = s;
}
void showQueue(LinkedQueue *lq) {
  QueueNode *p = lq->front->next;
  while (p != NULL) {
    printf("%d->", p->data);
    p = p->next;
  }
  printf("null\n");
}
void DeQueue(LinkedQueue *lq) {
  if (lq->front == lq->tail)
    return;
  QueueNode *p = lq->front->next;
  lq->front->next = p->next;
  if (p == lq->tail)
    lq->tail = lq->front;
  printf("%d\n", p->data);
  free(p);
}
void clear_lq(LinkedQueue *lq) {
  if (lq->front == lq->tail)
    return;
  QueueNode *p = lq->front->next;
  while (p != NULL) {
    lq->front->next = p->next;
    free(p);
    p = lq->front->next;
  }
  lq->front = lq->tail;
}
void desroy_lq(LinkedQueue *lq) {
  clear_lq(lq);
  free(lq->front);
  lq->front = lq->tail = NULL;
}
