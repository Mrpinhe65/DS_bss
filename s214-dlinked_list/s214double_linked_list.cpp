#ifndef __DLIST_H__
#define __DLIST_H__

#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include<stdlib.h>

#define ElemType int

typedef struct Node {
  ElemType data;
  struct Node* prio;
  struct Node* next;
} Node, *PNode;

typedef struct List {
  PNode first;
  PNode last;
  size_t size;
} List;

// Declaration
Node* _node_malloc(ElemType x);
void initDList(List* list);
void push_back(List* list, ElemType x);
void push_front(List* list, ElemType x);
void show_list(List* list);
void pop_back(List* list);
void pop_front(List* list);
void insert_val(List* list, ElemType x);
Node* find_val(List* list, ElemType key);
size_t length(List* list);
void delete_val(List* list, ElemType key);
void delete_another(List* list, ElemType key);
void sort(List* list);
void reverse(List* list);
void clear(List* list);
void destroy(List* list);

#endif  //__DLIST_H__

int main() {
  // 创建链表对象
  List mylist;
  initDList(&mylist);

  ElemType Item;
  Node* p = NULL;
  int select = 1;
  while (select) {
    printf("*************************************\n");
    printf("*  [1] push_back    [2] push_front  *\n");
    printf("*  [3] show_list    [4] pop_back    *\n");
    printf("*  [5] pop_front    [6] insert_val  *\n");
    printf("*  [7] find         [8] length      *\n");
    printf("*  [9] delete_val   [10] sort       *\n");
    printf("*  [11] reverse     [12] clear      *\n");
    printf("*  [13] destroy     [0] quit_system *\n");
    printf("*************************************\n");
    printf("Please select:>");
    scanf("%d", &select);
    if (select == 0) {
      // destroy(&mylist);
      return 0;
    }
    switch (select) {
      case 1:
        printf("please input insert data(-1 to end):>");
        while (scanf("%d", &Item), Item != -1) {
          push_back(&mylist, Item);
        }
        break;
      case 2:
        printf("please input insert data(-1 to end):>");
        while (scanf("%d", &Item), Item != -1) {
          push_front(&mylist, Item);
        }
        break;
      case 3:
        show_list(&mylist);
        break;
      case 4:
        pop_back(&mylist);
        break;
      case 5:
        pop_front(&mylist);
        break;
      case 6:
        printf("Please input insert data:>");
        scanf("%d", &Item);
        insert_val(&mylist, Item);
        break;
      case 7:
        printf("Please input find data:>");
        scanf("%d", &Item);
        p = find_val(&mylist, Item);
        if (p == NULL) {
          printf("data no found!\n");
          break;
        } else {
          printf("p = %p, p->next = %p, Item= %d\n", p, p->next, Item);
        }
        break;
      case 8:
        printf("Linked list length = %lu\n", length(&mylist));
        printf("Linked list length = %lu\n", mylist.size);
        break;
      case 9:
        printf("Please input delete data:>");
        scanf("%d", &Item);
        delete_val(&mylist, Item);
        // delete_another(&mylist,Item);
        break;
      case 10:
        sort(&mylist);
        break;
      case 11:
        reverse(&mylist);
        break;
      case 12:
        clear(&mylist);
        break;
      case 13:
        destroy(&mylist);
        break;
      default:
        printf("wrong selete,please again!\n");
        break;
    }
  }
  return 0;
}

// Implemention of the function

Node* _node_malloc(ElemType x) {
  Node* p = (Node*)malloc(sizeof(Node));
  assert(p != NULL);
  p->data = x;
  p->prio = NULL;
  p->next = NULL;
  return p;
}

void initDList(List* list) {
  Node* s = _node_malloc(sizeof(Node));
  list->first = s;
  list->last = s;
  list->first->prio = NULL;
  list->last->next = NULL;
  list->size = 0;
}

void push_back(List* list, ElemType x) {
  Node* s = _node_malloc(x);
  s->prio = list->last;
  list->last->next = s;
  list->last = s;
  list->size++;
}

void show_list(List* list) {
  if (list->size == 0) {
    printf("nul\n");
    return;
  }
  Node* p = list->first->next;
  while (p != NULL) {
    printf("%d-->", p->data);
    p = p->next;
  }
  printf("nul\n");
}

void push_front(List* list, ElemType x) {
  Node* s = _node_malloc(x);
  if (list->size == 0) {
    list->last = s;
  } else {
    s->next = list->first->next;
    s->next->prio = s;
  }
  s->prio = list->first;
  list->first->next = s;
  list->size++;
}

void pop_back(List* list) {
  if (list->size == 0) return;

  list->last = list->last->prio;
  free(list->last->next);
  list->last->next = NULL;
  list->size--;
}

void pop_front(List* list) {
  if (list->size == 0) return;
  // 记住被删除结点的指针
  Node* p = list->first->next;

  if (list->size == 1)  // if（list->first==list->last）
  {
    free(p);
    list->last = list->first;
    list->first->next = NULL;
    list->size = 0;
    return;
  }

  list->first->next = p->next;
  p->next->prio = list->first;
  free(p);
  list->size--;
}

void insert_val(List* list, ElemType x) {
  Node* p = list->first;

  while (p->next != NULL && p->next->data < x) {
    p = p->next;
  }
  if (p->next == NULL) {
    push_back(list, x);
  } else {
    Node* s = _node_malloc(x);
    // 插入结点的后趋
    s->next = p->next;
    // 被插入结点的前趋
    s->next->prio = p;
    // 插入结点的前趋
    s->prio = s;
    //
    p->next = s;
    list->size++;
  }
}

Node* find_val(List* list, ElemType key) {
  if (list->size == 0) return NULL;
  Node* p = list->first;
  while (p != NULL) {
    if (p->data == key) return p;
    p = p->next;
  }
  return NULL;
}
size_t length(List* list) { return list->size; }
void delete_val(List* list, ElemType key) {
  if (list->size == 0) return;

  Node* p = list->first->next;

  while (p != NULL) {
    if (p->data == key) {
      p->prio->next = p->next;

      if (p == list->last) {
        list->last = p->prio;
      } else {
        p->next->prio = p->prio;
      }

      free(p);

      list->size--;
    }
    p = p->next;
  }
}

void sort(List* list)
{
  if(list->size==0 || list->size==1)return;

  Node*s=list->first->next;
  Node*q=s->next;
  
  list->last=s;
  list->last->next=NULL;

  while(q !=NULL)
  {
    s=q;
    q=q->next;
    Node* p = list->first;

    while (p->next != NULL && p->next->data < s->data) {
      p = p->next;
    }
    if (p->next == NULL) {
      s->next=NULL;
      s->prio=list->last;
      list->last->next=s;
      list->last=s;

    } else {
      s->next = p->next;
      s->next->prio = p;
      s->prio = s;
      p->next = s;
    }
  }
}

void reverse(List* list)
{
  if(list->size==0 || list->size==1)return;

  Node*p=list->first->next;
  Node*q=p->next;
  
  list->last=p;
  list->last->next=NULL;
  
  while(q !=NULL)
  {
    p=q;
    q=q->next;

    p->next=list->first->next;
    p->next->prio=p;
    p->prio=list->first;
    list->first->next=p;
  }
}

void clear(List* list)
{
  if(list->size==0)return;
  // 除保留头结点外 其余结点一律free
  Node *p=list->first->next;
  while(p!=NULL)
{
    if(p==list->last)
  {
      list->last=list->first;
      list->last->next=NULL;
    }else
  {
      p->next->prio=list->first;
      list->first->next=p->next;
    } 
    free(p);
    p=list->first->next;
  }
  list->size=0;
}

void destroy(List* list)
{
  clear(list);
  free(list->first);
  list->first=list->last=NULL;
  exit(0);
}
