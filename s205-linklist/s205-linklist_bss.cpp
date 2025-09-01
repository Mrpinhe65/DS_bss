// 预处理
#include<stdio.h>
#include<assert.h>
#include<malloc.h>

#define ElemType int

// 结构体定义

typedef struct ListNode
{
    ElemType data;
    struct ListNode *next;
}ListNode;

typedef ListNode* List;

// 函数声明

void InitList(List*head) // ListNode **head;
{
    (*head)=NULL;
}

// 此法为尾插法
void CreateList_back(List*head)
{
    *head=(ListNode*)malloc(sizeof(ListNode));
    assert(*head !=NULL);
    (*head)->data=1;
    (*head)->next=NULL;
    
    ListNode*p=*head;
    for(int i=2;i<=10;i++)
    {
        ListNode*s=(ListNode*)malloc(sizeof(ListNode));
        assert(s!=NULL);
        s->data=i;
        s->next=NULL;

        p->next=s;
        p=s;
    }
    // hwd:malloc（堆区内存块 / 结点）应得到释放 指针和堆区内存块应分清楚。
}   

void CreateList_front(List *head)
{
    *head=(ListNode*)malloc(sizeof(ListNode));
    assert(*head!=NULL);
    (*head)->data=1;
    (*head)->next=NULL;

    for(int i=2;i<=10;i++){
        ListNode*s=(ListNode*)malloc(sizeof(ListNode));
        assert(s!=NULL);
        s->data=i;
        s->next=*head;
        *head=s;
    }
}

void ShowList(List head)
{
    ListNode*p=head;
    while(p!=NULL)
    {
        printf("|%d| -> ",p->data);
        p=p->next; 
    }
    printf("|null|\n");
    //hwd 应释放free指针p
}

int main()
{
    // 定义一个链表
    List myList;
    InitList(&myList);
    //CreateList_back(&myList);
    CreateList_front(&myList);
    ShowList(myList); // 不改变链表 不需传地址



    return 0;
}
