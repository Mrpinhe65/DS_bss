#ifndef __SEQQUEUE_H__
#define __SEQQUEUE_H__

#include <assert.h>
#include <malloc.h>
#include <stdio.h>

#define ElemType int

#define MAXSIZE 8

typedef struct Queue {
  ElemType *base;
  int front;
  int rear;
} Queue;

void InitQueue(Queue *q);
void EnQueue(Queue *q, ElemType data);
void ShowQueue(Queue *q);
void DeQueue(Queue *q);
int Length(Queue *q);
void GetHead(Queue *q, ElemType *value);
void ClearQueue(Queue *q);
void DestroyQueue(Queue *q);

#endif //__SEQQUEUE_H__

int main() {
  Queue Q;
  InitQueue(&Q);
  for (int i = 1; i <= 8; i++) {
    EnQueue(&Q, i);
  }
  ShowQueue(&Q);
  DeQueue(&Q);
  ShowQueue(&Q);
  EnQueue(&Q, 10);
  DeQueue(&Q);
  EnQueue(&Q, 20);
  DeQueue(&Q);
  EnQueue(&Q, 30);
  DeQueue(&Q);
  EnQueue(&Q, 40);
  DeQueue(&Q);
  EnQueue(&Q, 50);
  DeQueue(&Q);
  EnQueue(&Q, 60);
  DeQueue(&Q);
  EnQueue(&Q, 70);
  DeQueue(&Q);
  EnQueue(&Q, 80);

  ShowQueue(&Q);
  printf("Queue length = %d\n", Length(&Q));
  ElemType value;
  GetHead(&Q, &value);
  printf("Head data = %d\n", value);
  ClearQueue(&Q);
  DestroyQueue(&Q);
  return 0;
}
void InitQueue(Queue *q) {
  q->base = (ElemType *)malloc(sizeof(ElemType) * MAXSIZE);
  assert(q->base != NULL);
  q->front = 0;
  q->rear = 0;
}
void EnQueue(Queue *q, ElemType data) {
  if ((q->rear + 1) % MAXSIZE == q->front)
    return;
  q->base[q->rear] = data;
  q->rear = (q->rear + 1) % MAXSIZE;
}
void ShowQueue(Queue *q) {
  if (q->rear == q->front)
    return;
  for (int i = q->front; i != q->rear;) {
    printf("%d->", q->base[i]);
    i = (i + 1) % MAXSIZE;
  }
  printf("null\n");
}
void DeQueue(Queue *q) {
  if (q->front == q->rear)
    return;
  q->front = (q->front + 1) % MAXSIZE;
}
int Length(Queue *q) { return q->rear - q->front; }
void GetHead(Queue *q, ElemType *value) { *value = q->base[q->front]; }
void ClearQueue(Queue *q) { q->rear = q->front = 0; }
void DestroyQueue(Queue *q) {
  q->front = q->rear = 0;
  free(q->base);
  if (q->base != NULL)
    q->base = NULL;
}
