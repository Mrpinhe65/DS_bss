#include <assert.h>
#include <malloc.h>
#include <stdio.h>

/*
带头结点，头结点仅起链表起始指针的作用 不存储任何数据


|头结点|NULL|next| -> |No1|data|next| -> |No2|data|next| -> |No3|data|NULL|

*/
typedef struct ElemType {
  int num;
  char name[20];
  float score;
} ElemType;

typedef struct LinkNode {
  ElemType data;
  struct LinkNode* next;
} LinkNode;

typedef LinkNode* List;

void InitList(List* head) { *head = NULL; }

// 按尾插法
void CreateList_back(List* head) {
  *head = (LinkNode*)malloc(sizeof(LinkNode));  // 首节点/头结点
  assert(*head != NULL);
  (*head)->next = NULL;

  // 测试数据 生产环境设置键盘输入或从文件读入
  ElemType ar[] = {{100, "huang weidong", 150.0}, {101, "liu xiaoli", 148.7},
                   {102, "huang linbi", 148.9},   {103, "liu su", 142.2},
                   {104, "huang dejia", 133.6},   {105, "nong yuhua", 148.6}};
  size_t n = sizeof(ar) / sizeof(ar[0]);

  LinkNode* p = *head;
  for (int i = 0; i < n; i++) {
    /*
    // 后续结点 逐一创建
    LinkNode* s = (LinkNode*)malloc(sizeof(LinkNode));
    assert(s != NULL);
    p->next = s;
    p = s;
    s->data = ar[i];
    s->next = NULL;
    */
    // 上述代码课写成如下
    p = p->next = (LinkNode*)malloc(sizeof(LinkNode));
    p->data = ar[i];
    p->next = NULL;
  }
}
void CreateList_front(List* head) {
  *head = (LinkNode*)malloc(sizeof(LinkNode));  // 首节点/头结点
  assert(*head != NULL);

  (*head)->next = NULL;

  // 测试数据 生产环境设置键盘输入或从文件读入
  ElemType ar[] = {{10, "huang weidong", 150.0}, {11, "liu xiaoli", 148.7},
                   {12, "huang linbi", 148.9},   {13, "liu su", 142.2},
                   {14, "huang dejia", 133.6},   {15, "nong yuhua", 147.8}};
  size_t n = sizeof(ar) / sizeof(ar[0]);

  LinkNode* p = NULL;
  for (int i = 0; i < n; i++) {
    // 后续结点 逐一创建
    LinkNode* s = (LinkNode*)malloc(sizeof(LinkNode));
    assert(s != NULL);
    (*head)->next = s;

    s->data = ar[i];
    s->next = p;
    p = s;
  }
}
void ShowList(List head) {
  LinkNode* p = head->next;
  while (p != NULL) {
    printf("%d, %s, %.1f\n", p->data.num, p->data.name, p->data.score);
    p = p->next;
  }
}

int main() {
  printf("单链表\n");

  List myList;
  InitList(&myList);
  CreateList_back(&myList);
  ShowList(myList);
  CreateList_front(&myList);
  ShowList(myList);

  return 0;
}