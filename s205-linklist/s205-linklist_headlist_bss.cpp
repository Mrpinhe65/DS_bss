// 预处理
#include<stdio.h>
#include<assert.h>
#include<malloc.h>

#define ElemType int

// 带头结点的的链表
//
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
    *head=(ListNode*)malloc(sizeof(ListNode));
    (*head)->next=NULL;
}

// 带头结点的链表
// 头插法
void CreateList_front_head(List*head)
{
    for(int i=1;i<=10;i++ )
    {
        ListNode* s=(ListNode*)malloc(sizeof(ListNode));
        s->data=i;

        // 调整原来链接 在头结点和首数据节点之间插入新结点
        s->next=(*head)->next; // 插入结点指向原首数据节点
        (*head)->next=s; // 头结点指向插入结点
    }
}

void CreateList_back_head(List *head)
{
    ListNode*p=*head;
    for(int i=1;i<=10;i++)
    {
        p=p->next=(ListNode*)malloc(sizeof(ListNode));
        p->data=i;
        p->next=NULL;
    }
}

void ShowList(List head)
{
    ListNode*p=head->next;
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
    //CreateList_front_head(&myList);
    CreateList_back_head(&myList);
    ShowList(myList); // 不改变链表 不需传地址



    return 0;
}
