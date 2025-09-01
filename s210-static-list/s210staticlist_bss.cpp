#include<stdio.h>
#include<assert.h>
#include<malloc.h>

#define MAX_SIZE 20
#define ElemType char

typedef struct ListNode
{
    ElemType data;
    int cur;
}ListNode;

typedef ListNode StaticList[MAX_SIZE];

//declaration of the function

void InitSList(StaticList &space);
void insert(StaticList &space,ElemType x);

int main()
{
    StaticList SL;
    InitSList(SL);
    for(int i=0;i<5;i++)
    {
        insert(SL,'A'+i);
    }
    ShowSList(SL);
    return 0;
}


//implementation of function
void InitSList(SL);
void InitSList(StaticList &space)
{
    for(int i=0;i<MAX_SIZE-1;i++)
    {
        space[i].cur=i+1;
    }
    space[MAX_SIZE-1].cur=0;
    space[0].cur=-1;
}

void insert(StaticList &space,ElemType x)
{


}
