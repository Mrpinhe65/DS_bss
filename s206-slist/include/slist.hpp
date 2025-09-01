#ifndef __SLIST_H__
#define __SLIST_H__

#include <assert.h>
#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FILENAME "../datafile/slist.dat"

// 存储文件头
typedef struct {
  char program[30];      // 程序名
  char author[20];       // 作者
  char create_date[15];  // 创建日期
  size_t num_elem;       // 数据个数
} File_Format;

typedef struct ElemType {
  int num;
  char name[20];
  float score;
} ElemType;

typedef struct Node {
  ElemType data;
  struct Node *next;
} Node, *PNode;

typedef struct List {
  PNode first;
  PNode last;
  size_t size;
} List;

int menu();
void InitList(List *ist);
void inputElem(ElemType *data);
void readFile(List *list);
void saveFile(List *list);
void show_List(List *list);
void push_back(List *list);
void push_front(List *list);
void pop_back(List *list);
void pop_front(List *list);
void insert_pos(List *list);
void find_score(List *list);
void delete_score(List *list);
void sort_score(List *list);
void sort_bbs(List *list);

void destory_list(List *list);

#endif  //__SLIST_H__

/*TODO
// 元素数据输入

TODO
*/
