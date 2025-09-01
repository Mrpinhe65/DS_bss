#ifndef __SEQLIST_H__
#define __SEQLIST_H__

#include <assert.h>
#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define SEQLIST_INIT_SIZE 8
#define INC_SIZE 3

#define FILENAME "seqlist.dat"

typedef struct ElemType {
  int num;
  char name[20];
  float score;
} ElemType;

typedef struct SeqList {
  ElemType *base;
  int capacity;
  int size;
} SeqList;

// 函数声明
// 顺序表初始化 开辟顺序表内存 确定容量 实际大小
void InitSeqList(SeqList *list);

// 菜单显示和选择
int menu();

// 顺序表元素数据输入
void inputElemData(ElemType *item);

// case 1
void push_back(SeqList *list, ElemType data);

// case 2
void push_front(SeqList *list, ElemType data);
// case 3
void showList(SeqList list);

// case 4 pop_back

void pop_back(SeqList *list, ElemType *data);

// case 5 pop_front

void pop_front(SeqList *list, ElemType *data);

// case 6 insert_pos
void insert_pos(SeqList *list, ElemType data, int pos);

// case 7 find by score
void find_by_score(SeqList *list, float score, ElemType *data);

// case 9 delete by postion
void delete_pos(SeqList *list, ElemType *data, int pos);

void delete_score(SeqList *list, ElemType *data, float score);

// case 11 sort by pfun

void sort_by_pfun(void *list, int n, int width,
                  int (*fun)(const void *e1, const void *e2));

// TODO int compare(const );

// void wait_for_any_key();

int cmp_score(const void *a, const void *b);

void sort_bubble(SeqList *list);

void resver(SeqList *list);

void wait_for_any_key();

bool Inc(SeqList *list);

#endif
