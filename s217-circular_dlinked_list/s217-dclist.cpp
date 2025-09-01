#ifndef __DCLIST_H__
#define __DCLIST_H__

#include<stdio.h>
#include<malloc.h>
#include<assert.h>
#include<stdlib.h>

#define ElemType int

typedef struct Node{
  ElemType data;
  struct Node *prio;
  struct Node *next; 
}Node,*PNode;

typedef struct List{
  PNode first;
  PNode last;
  size_t size;
}List;



void InitDCList(List*list);   

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

//
Node* _node_malloc(ElemType x);

#endif //__DCLIST_H__

int main(int argc, char *argv[]) {
  List mylist;
  InitDCList(&mylist);
  ElemType Item;
  Node*p = NULL;
  int select = 1;

  while(select){
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
      scanf("%d",&select);
      if(select == 0)
      {
          //destroy(&mylist);
          return 0;
      }
      switch(select)
      {
          case 1:
              printf("please input insert data(-1 to end):>");
              while(scanf("%d",&Item),Item!=-1)
              {
                  push_back(&mylist,Item);

              }
              break;
          case 2:
              printf("please input insert data(-1 to end):>");
              while(scanf("%d",&Item),Item!=-1)
              {
                  push_front(&mylist,Item);
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
              scanf("%d",&Item);
              insert_val(&mylist,Item);
              break;
          case 7:
              printf("Please input find data:>");
              scanf("%d",&Item);
              p=find_val(&mylist,Item);
              if(p ==NULL)
              {
                  printf("data no found!\n");
                  break;
              }else
              {
                  printf("p = %p, p->next = %p, Item= %d\n",p,p->next,Item);
              }
              break;
          case 8:
              
              printf("Circularly Double Linked list length = %lu\n",length(&mylist));
              printf("Circularly Double Linked list length = %lu\n",mylist.size);
              break;
          case 9:
              printf("Please input delete data:>");
              scanf("%d",&Item);
              delete_val(&mylist,Item);
              //delete_another(&mylist,Item);
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

void InitDCList(List*list)
{
  Node*s=(Node*)malloc(sizeof(Node));
  assert(s!=NULL);
  list->first=list->last=s;
  list->first->prio=list->last;
  list->last->next=list->first;
  list->size=0;
}
Node* _node_malloc(ElemType data)
{
    Node*s=(Node*)malloc(sizeof(Node));
    assert(s!=NULL);
    s->data=data;
    s->prio=NULL;
    s->next=NULL;
    return s;
}
void push_back(List* list, ElemType data) {
  Node* s = _node_malloc(data);
  s->next=list->last->next; // s->next=list-first;
  s->next->prio=s;
  s->prio=list->last;

  list->last->next=s;
  list->last=s;
  list->size++;
}

void show_list(List* list) {
  if (list->size == 0) {
    printf("nul\n");
    return;
  }
  Node* p = list->first->next;
  while (p != list->first) {
    printf("%d-->", p->data);
    p = p->next;
  }
  printf("nul\n");
}

void push_front(List* list, ElemType data) {
  Node* s = _node_malloc(data);
  s->next = list->first->next;
  s->next->prio = s;
  s->prio = list->first;
  list->first->next = s;
  if (list->size == 0) {
    list->last = s;
  }
  list->size++;
}

void pop_back(List* list) {
  if (list->size == 0) return;
  Node* p=list->last;
  list->last = p->prio;
  p->next->prio = p->prio;
  p->prio->next=p->next;
  free(p);
  list->size--;
}

void pop_front(List* list) {
  if (list->size == 0) 
    return;
  // 记住被删除结点的指针
  Node* p = list->first->next;
  p->next->prio=p->prio;
  p->prio->next=p->next;
  if (list->size == 1)  // if（list->first==list->last）
    list->last = list->first;
  free(p);
  list->size--;
}

void insert_val(List* list, ElemType data) {
  Node* p = list->first;

  while (p->next != list->last && p->next->data < data) {
    p = p->next;
  }
  if (p->next == list->last && p->next->data<data) {
    push_back(list, data);
  } else {
    Node* s = _node_malloc(data);
    // 插入结点的后趋
    s->next = p->next;
    // 被插入结点的前趋
    s->next->prio = s;
    // 插入结点的前趋
    s->prio = p;
    //
    p->next = s;
    list->size++;
  }
}

Node* find_val(List* list, ElemType key) {
  if (list->size == 0) return NULL;
  Node* p = list->first->next;
  while (p != list->first && p->data != key) 
    p = p->next;
  if(p==list->first)
      return NULL;
  return p;
}

size_t length(List* list) 
{ 
    return list->size; 
}

void delete_val(List* list, ElemType key) {
  if (list->size == 0) return;

  Node* p = list->first->next;

  while (p != list->first) {
    if (p->data == key) {
      p->prio->next = p->next;

      if (p == list->last) {
        list->last = p->prio;
      } else {
        p->next->prio = p->prio;
      }
      free(p);
      list->size--;
      return;
    }
    p = p->next;
  }
}

void sort(List* list)
{
  if(list->size==0 || list->size==1)
      return;

  Node*s=list->first->next;
  Node*q=s->next;
  list->last->next=NULL;
  list->last=s;
  list->last->next=list->first;
  list->first->prio=list->last;

  while(q !=NULL)
  {
    s=q;
    q=q->next;
    Node* p = list->first;
    while (p->next != list->last && p->next->data < s->data) {
      p = p->next;
    }
    if (p->next == list->last && p->next->data<s->data) {
     s->next=list->last->next;
     s->next->prio=s;
     s->prio=list->last;
     list->last->next=s;
     list->last=s;
    } else {
      s->next = p->next;
      s->next->prio = s;
      s->prio = p;
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
  list->last->next=list->first;
  
  while(q !=list->first)
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
  while(p!=list->first)
{
    if(p==list->last)
  {
      list->last=list->first;
      list->last->next=list->first;
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

