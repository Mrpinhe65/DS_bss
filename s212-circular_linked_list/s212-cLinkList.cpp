/*
 单循环链表的实现
*/

#ifndef __SCLIST_H__
#define __SCLIST_H__

#include<stdio.h>
#include<assert.h>
#include<malloc.h>


#define ElemType int

typedef struct Node
{
    ElemType data;
    struct Node *next;
}Node,*PNode;

typedef struct List
{
    PNode first;
    PNode last;
    size_t size;
}List;

//Declaration of the function
void InitSClist(List*list);

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
Node* _createnode(ElemType x);

#endif // __SCLIST_H__

int main()
{
    List mylist;
    InitSClist(&mylist);

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
                
                printf("Linked list length = %lu\n",length(&mylist));
                printf("Linked list length = %lu\n",mylist.size);
                break;
            case 9:
                /*
                printf("Please input delete data:>");
                scanf("%d",&Item);
                //delete_val(&mylist,Item);
                delete_another(&mylist,Item);
                */
                break;
            case 10:
                //sort(&mylist);
                break;
            case 11:
                //reverse(&mylist);
                break;
            case 12:
                //clear(&mylist);
                break;
            case 13:
                //destroy(&mylist);
                break;
            default:
                printf("wrong selete,please again!\n");
                break;
        }
    }
    return 0;
}

//Implementation of function 
void InitSClist(List*list)
{
   Node*s=(Node*)malloc(sizeof(Node));
   assert(s!=NULL);
   list->first=list->last=s;
   list->last->next=list->first;
   list->size=0;
   printf("first = %p, last = %p\n",list->first,list->last);
}

Node* _createnode(ElemType x)
{
    Node*s=(Node*)malloc(sizeof(Node));
    assert(s!=NULL);
    s->data=x;
    s->next=NULL;
    return s;
}

void push_back(List* list, ElemType x)
{
    Node *s=_createnode(x);
    list->last->next=s;
    list->last=s;
    list->last->next=list->first;
    list->size++;
}

void push_front(List* list, ElemType x)
{
    Node *s=_createnode(x);
    s->next=list->first->next;
    list->first->next=s;
    if(list->first==list->last)list->last=s;
    list->size++;
    
}


void show_list(List* list)
{
    Node *p=list->first->next;
    while(p != list->first)
    {
        printf("%d -->",p->data);
        p=p->next;
    }
    printf("nul\n");
}

void pop_back(List* list)
{
    if(list->size==0)return;
    Node*p = list->first;
    while(p->next != list->last)
    {
        p=p->next;
    }
    free(list->last);
    list->last=p;
    p->next=list->first;
    list->size--;
}

void pop_front(List* list)
{
    if(list->size ==0)return;

    Node *p=list->first->next;
    list->first->next = p->next;
    free(p);
    if(list->size ==1)
    {
        list->last=list->first;
    }
    list->size--;
}

void insert_val(List* list, ElemType x)
{
    Node *p=list->first;
    while(p->next != list->last && p->next->data<x)
    {
        p=p->next;
    }

    if(p->next == list->last && p->next->data<x)
    {
        push_back(list,x);
    }else
    {
        Node *s=_createnode(x);
        s->next=p->next;
        p->next=s;
        list->size++;
    }
}

Node* find_val(List* list, ElemType key)
{
    if(list->size == 0) return NULL;

    Node*p=list->first->next;
    while(p != list->first &&p->data != key)
    {
        p=p->next;
    }
    if(p==list->first)return NULL;
    return p;

}

size_t length(List* list)
{
    return list->size;
}
