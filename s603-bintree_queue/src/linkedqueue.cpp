#include "../include/bintree.hpp"
#include "../include/linkedqueue.hpp"
#include "../include/seqstack.hpp"

void initLinkedQueue(LinkedQueue *q) {
  QueueNode *s = (QueueNode *)malloc(sizeof(QueueNode));
  assert(s != NULL);
  q->front = s;
  q->tail = s;
  q->front->next = NULL;
}

bool QueueIsEmpty(LinkedQueue *q) { return q->front == q->tail; }

void enQueue(LinkedQueue *lq, queue::ElemType data) {
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
    printf("%p->", p->data);
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
  // printf("%p\n", p->data);
  free(p);
}
void GetHead(LinkedQueue *lq, queue::ElemType *v) {
  if (lq->front == lq->tail)
    return;
  *v = lq->front->next->data;
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
