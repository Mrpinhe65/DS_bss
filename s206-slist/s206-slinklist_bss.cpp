#include<stdio.h>
#include<assert.h>
#include<malloc.h>
#include<stdlib.h>

#define ElemType int

//定义结点结构
typedef struct Node
{
    ElemType data;
    struct Node*next;
}Node,*PNode;

// 定义链表管理的结构体
typedef struct List{
    PNode first;
    PNode last;
    size_t size;
}List;

void InitList(List*list);
void push_back(List*list,ElemType x);
void push_front(List*list,ElemType x);
void show_list(List*list);
void pop_back(List*list);
void pop_front(List*list);
void insert_val(List*list,ElemType x);
Node* find_val(List*list,ElemType key);
size_t length(List*list);
void delete_val(List*list,ElemType key);
void delete_another(List*list,ElemType key);
void sort(List*list);
void reverse(List*list);
void clear(List*list);
void destroy(List*list);


int main()
{
    ElemType Item;
    Node*p=NULL;
    List mylist;
    InitList(&mylist);

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
            destroy(&mylist);
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
                printf("Please input delete data:>");
                scanf("%d",&Item);
                //delete_val(&mylist,Item);
                delete_another(&mylist,Item);
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

void InitList(List*list){
    // 创建头结点
    list->first=list->last=(Node*)malloc(sizeof(Node));
    assert(list->first != NULL);
    list->first->next=NULL;
    list->size=0;  
}

void push_back(List*list,ElemType x)
{
    Node*s=(Node*)malloc(sizeof(Node));
    assert(s != NULL);
    s->data=x;
    s->next=NULL;

    list->last->next=s;
    list->last=s;
    list->size++;
}
void push_front(List*list,ElemType x)
{
    Node*s=(Node*)malloc(sizeof(Node));
    assert(s != NULL);
    s->data = x;
    s->next = list->first -> next;
    list->first->next = s;
    if(list->size==0)list->last=s;
    list->size++;
}

void show_list(List*list)
{
    Node *p=list->first->next;
    while(p != NULL)
    {
        printf("|%d|-->",p->data);
        p = p->next;
    }
    printf("Nul\n");
}

void pop_back(List*list)
{
    if(list->size == 0) 
    {
        printf("linked list empty! can't pop!\n");
        return;
    }
    Node*p=list->first;
    //遍历链表，找出倒第二的结点
    while(p->next != list->last) 
    {
        p=p->next;
    }

    //释放最后一个结点
    free(list->last->next);
    //设置last指向
    list->last=p;
    //现在的最后一个结点next赋空
    list->last->next=NULL;
    list->size--;
}
void pop_front(List*list)
{
    if(list->size == 0) 
    {
        printf("linked list empty! can't pop!\n");
        return;
    }
    // 指针指向要pop的结点
    Node*p=list->first->next;
    list->first->next=p->next;
    free(p);
    if(list->size ==1) list->last=list->first;
    list->size--;
    
}

// 按值插入需要有序的链表序列
// 假定插入位置 其值比左大，比右小 
// 也可以先进行排序--待排序函数编制
void insert_val(List*list,ElemType x)
{
    Node*s=(Node*)malloc(sizeof(Node));
    assert(s != NULL);
    s->data=x;
    s->next=NULL;

    Node*p=list->first;
    while(p->next !=NULL && p->next->data<x)
    {
        p=p->next;
    }
    if(p->next == NULL)list->last = s;

    s->next=p->next;
    p->next=s;
    list->size++;
}
Node*find_val(List*list,ElemType key)
{
    Node*p=list->first->next;
    while(p != NULL && p->data != key)
    {
        p=p->next;
    }
    return p;
}
size_t length(List*list)
{
    return list->size;
}

void delete_val(List*list,ElemType key)
{
    if(list->size==0){
        printf("Linked list empty, can't delete!\n");
        return;
    }
    Node*p=find_val(list,key);
    if(p==NULL){
        printf("No delete data!\n");
        return;
    }

    if(p==list->last){
        pop_back(list);
    }
    else
    {
        Node*q=p->next;
        p->data=q->data;
        p->next=q->next;
        free(q);
        list->size--;
    }
}

void delete_another(List*list,ElemType key){
    if(list->size == 0)return;
    if(list->first->next->data==key){
        pop_front(list);
        return;
    }
    if(list->last->data==key){
        pop_back(list);
        return;
    }
    Node*p=list->first->next;
    Node*q=p->next;
    while(q->next!=NULL)
    {
        if(q->data==key)
        {
            p->next=q->next;
            free(q);
            list->size--;
            return;
        }
        p=q;
        q=q->next;
    }
    printf("No data to delete!\n");
}
void sort(List*list)
{
    if(list->size==0 || list->size ==1)return;

    //记录链表第一结点
    Node*s=list->first->next;
    //记录链表第二节点
    Node*q=s->next;

    // 断开链表第一结点和第二结点
    list->last=s;
    list->last->next=NULL;
    //这个操作不造成size变化，可不编制size相关的操作
    //为保证操作完整性而已
    list->size=1;

    while(q!=NULL)
    {
        s=q;
        q=q->next;

        Node*p=list->first;
        while(p->next !=NULL && p->next->data < s->data) // >为降序 <为升序
        {
            p=p->next;
        }
        if(p->next == NULL)list->last = s;

        s->next=p->next;
        p->next=s;

        //这个操作不造成size变化，可不编制size相关的操作
        //为保证操作完整性而已
        list->size++;
        }

}
void reverse(List*list)
{
    if(list->size==1 || list->size==1)return;

    //记录第一个结点
    Node*p=list->first->next;
    //记录第二个接点
    Node*q=p->next;

    //切断原链表
    list->last=p;
    p->next=NULL;
    //这个操作不造成size变化，可不编制size相关的操作
    //为保证操作完整性而已
    list->size=1;
    
    //第二节点及其后节点逐个前插
    while(q!=NULL)
    {

        p=q;
        q=q->next;
        p->next=list->first->next;
        list->first->next=p;
        //这个操作不造成size变化，可不编制size相关的操作
        //为保证操作完整性而已
        list->size++;

    }
}

                
void clear(List*list)
{
    if(list->size==0)return;

    Node*p=list->first->next;

    while(p!=NULL)
    {
        list->first->next=p->next;
        free(p);
        p=list->first->next;
    }
    list->last=list->first->next;
    list->size=0;
}

void destroy(List*list)
{
    clear(list);
    free(list->first);
    list->first=list->last=NULL;
    exit(0);
}
