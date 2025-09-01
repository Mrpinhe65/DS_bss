#include "../include/slist.hpp"

// 菜单显示和选择
int menu() {
  printf("************************************\n");
  printf("====      Single LinkList       ====\n");
  printf("************************************\n");
  printf("* [1] push_back    [2] push_front  *\n");
  printf("* [3] show_list    [4] pop_back    *\n");
  printf("* [5] pop_front    [6] insert_pos  *\n");
  printf("* [7] find_score   [8] length      *\n");
  printf("* [9] delete_score [10] sort_score *\n");
  printf("* [11]resver       [12] clear      *\n");
  printf("* [13]save         [0] save&exit   *\n");
  printf("************************************\n");

  int select;
  printf("please select >");
  scanf("%d", &select);
  return select;
}

void InitList(List *list) {
  list->first = list->last = (Node *)malloc(sizeof(Node));
  assert(list->first != NULL);
  list->first->next = NULL;
  list->size = 0;

  readFile(list);
}

// 结点数据输入
void inputElem(ElemType *elem) {
  printf("\nplease input data:[1] Card number>");
  scanf("%d", &elem->num);

  while (getchar() != '\n');  // 清除输入缓冲区

  // 输入带空格的名字或其他字符串，scanf fgets
  printf("\nplease input data:[2] Name>");
  // scanf("%s", &elem->name);
  fgets(elem->name, sizeof(elem->name), stdin);
  // 去除可能的换行符
  elem->name[strcspn(elem->name, "\n")] = '\0';
  printf("\nplease input data:[3] Score>");
  scanf("%f", &elem->score);
}

// deepseek 方案
void readFile(List *list) {
  if (access(FILENAME, F_OK)) {
    printf("数据文件《%s》尚未创建\n", FILENAME);
    return;
  }
  FILE *fp = fopen(FILENAME, "rb");
  if (fp == NULL) {
    perror("File open fail on readFile!\n");
    fclose(fp);
    return;
  }

  // 读取文件头
  File_Format f;
  fread(&f, sizeof(f), 1, fp);
  printf("%s,  %s,  %s,  %lu\n", f.program, f.author, f.create_date,
         f.num_elem);

  Node *current = list->first;

  for (size_t i = 0; i < f.num_elem; i++) {
    Node *p = (Node *)malloc(sizeof(Node));
    if (fread(&(p->data), sizeof(ElemType), 1, fp) != 1) {
      free(p);
      break;
    }
    printf("%d,  %s,  %.1f\n", p->data.num, p->data.name, p->data.score);

    p->next = NULL;
    current->next = p;
    current = p;
    list->size++;
  }

  list->last = current;
  fclose(fp);
}

void saveFile(List *list) {
  if (list->size == 0) {
    remove(FILENAME);
    return;
  }
  // 文件头的内容
  File_Format const format = {"Single Link List By c", "黄卫东", "2025-08-05",
                              list->size};

  // 打开文件 二进制写入模式
  FILE *fp = fopen(FILENAME, "wb");
  if (fp == NULL) {
    perror("File open fail in saveFile!\n");
    return;
  }
  // 写入文件头
  fwrite(&format, sizeof(format), 1, fp);

  // 把ElemType 数据写入二进制文件 写入data域
  // next指针域不写
  // 每次打开文件前 开辟结点Node，指针由系统分配 把ElemType data域数据读入即可
  Node *s = list->first->next;

  while (s != NULL) {
    fwrite(&(s->data), sizeof(ElemType), 1, fp);
    printf("{%d, %s, %.1f}\n", s->data.num, s->data.name, s->data.score);
    s = s->next;
  }
  // free(s);
  fclose(fp);
}

void show_List(List *list) {
  if (list->size == 0 || list->first == NULL) {
    printf("链表为空，没有数据！\n");
    return;
  }
  Node *s = list->first->next;

  while (s != NULL) {
    printf("{%d, %s, %.1f}\n", s->data.num, s->data.name, s->data.score);
    s = s->next;
  }
  free(s);  // rem
}

void push_back(List *list) {
  // 程序调试期间代替输入的数据
  ElemType arr[] = {{1001, "huang weidong", 150.0},
                    {1002, "liu xiaoli", 148.9},
                    {1003, "huang linbin", 146.6},
                    {1004, "huang dejia", 143.8},
                    {1005, "liu su", 138.7}};
  int num = sizeof(arr) / sizeof(ElemType);
  // end调试数据结束

  // 调试屏蔽
  //  结点输入数据
  // ElemType elem;
  // inputElem(&elem);
  //

  for (int i = 0; i < num; i++) {
    // 创建结点 放置data
    Node *s = (Node *)malloc(sizeof(Node));
    assert(s != NULL);

    // 新节点放入数据
    // s->data = elem;
    s->data = arr[i];
    // 设置next为 NULL
    s->next = NULL;

    // 后插 list->last 指向 s
    list->last->next = s;
    list->last = s;

    // 链表有效节点数+1
    list->size++;
  }
}

void push_front(List *list) {
  // 程序调试期间代替输入的数据
  ElemType arr[] = {{1001, "huang weidong", 150.0},
                    {1002, "liu xiaoli", 148.9},
                    {1003, "huang linbin", 146.6},
                    {1004, "huang dejia", 143.8},
                    {1005, "liu su", 138.7}};
  int num = sizeof(arr) / sizeof(ElemType);
  // end调试数据结束

  // 调试程序屏蔽
  //  输入新节点数据
  // ElemType elem;
  // inputElem(&elem);
  //

  for (int i = 0; i < num; i++) {
    // 创建节点 放置数据
    Node *s = (Node *)malloc(sizeof(Node));
    assert(s != NULL);

    // s->data = elem;
    s->data = arr[i];
    // 新结点next指向原链表第一个结点
    s->next = list->first->next;

    // 头结点next指向s
    list->first->next = s;

    if (list->size == 0) {
      list->last = s;
    }

    // 链表有效节点数+1
    list->size++;
  }
}

void destory_list(List *list) {
  printf("%p, %lu\n", list->first, list->size);
  if (list->first->next == NULL) {
    // if (list->first->next == NULL) {
    //  free(list->first->next);  // rem
    // free(list->first);  // rem
    free(list->last);
    list->last = NULL;
    return;
  }
  Node *s = list->first->next;
  while (s != NULL) {
    list->last = s->next;
    s = list->last;
  }
  free(s);
  free(list->first);
  free(list->last);
  list->first = list->last = NULL;
}

void pop_back(List *list) {
  // 空链表/没有数据节点 则返回
  if (list->size == 0 || list->first == NULL) {
    printf("链表中没有数据可删除\n");
    return;
  }
  if (list->size == 1) {
    Node *to_delete = list->first->next;  // 获取第一个数据节点
    free(to_delete);
    list->first->next = NULL;  // 头结点的next置为NULL
    list->last = list->first;  // 尾指针指向头结点
    list->size--;
    return;
  }

  // 通用情况：size > 1
  Node *p = list->first;
  while (p->next != list->last) {
    p = p->next;
  }
  // 此时 p 是倒数第二个节点
  free(list->last);         // 释放最后一个节点
  list->last = p;           // 更新尾指针
  list->last->next = NULL;  // 新的尾结点的next置为NULL
  list->size--;
  // free(p);//rem
}

void pop_front(List *list) {
  // 空链表/没有数据节点 则返回
  if (list->size == 0) {
    printf("链表中没有数据可删除\n");
    return;
  }

  // 指针pop结点
  Node *s = list->first;
  // first指向pop节点的下一个结点
  list->first = s->next;
  // 释放pop节点
  free(s->next);  // rem
  if (list->size == 1) {
    list->last = list->first;
  }
  free(s);  // rem
  //  结点数-1
  list->size--;
}

void insert_pos(List *list) {
  printf("链表长度：%lu, 请选择数据插入位置:>", list->size);
  size_t pos;
  scanf("%lu", &pos);
  if (pos < 1 || pos > list->size) {
    printf("无法在 %lu 插入数据\n", pos);
    return;
  }
  if (pos == 1) {
    push_front(list);
    return;
  }
  if (pos == list->size) {
    push_back(list);
    return;
  }
  ElemType elem;
  inputElem(&elem);

  Node *p = (Node *)malloc(sizeof(Node));
  assert(p != NULL);
  p->data = elem;

  size_t count = 0;
  Node *ptr = list->first->next;
  while (1) {
    count++;
    if (count + 1 == pos) {
      p->next = ptr->next;
      ptr->next = p;
      list->size++;
      free(ptr);
      return;
    }
    // ptr = ptr->next;
  }
  // free(ptr);//rem
}
void find_score(List *list) {
  float score_find;
  printf("请输入要查找的score:>");
  scanf("%f", &score_find);
  Node *s = list->first->next;
  while (s->next != NULL) {
    if (fabs(s->data.score - score_find) < 0.01) {
      printf("查找结果如下:\n");
      printf("{%d, %s, %.1f}\n", s->data.num, s->data.name, s->data.score);
      // free(s);//rem
      return;
    }
    s = s->next;
  }
  // free(s);rem
  printf("链表中没有和score匹配的数据!\n");
}

// TODO
void delete_score(List *list) {
  float score_delete;
  size_t count = 0;
  printf("请输入要删除的score:>");
  scanf("%f", &score_delete);
  Node *ptr = list->first;
  while (ptr->next != NULL) {
    count++;
    if (fabs(ptr->next->data.score - score_delete) < 0.01) {
      if (list->size == 1) {
        free(ptr->next);
        list->last = list->first;
        list->size = 0;
        // free(ptr);
        return;
      } else if (count == 1)
        pop_front(list);
      // free(ptr);
      return;
    } else if (count == list->size) {
      pop_back(list);
      // free(ptr);
      return;
    } else {
      Node *p_back = ptr->next->next;
      if (ptr->next->next != NULL) ptr->next->next = NULL;

      ptr->next = p_back;
      list->size--;
      ptr = ptr->next;
    }
    // free(ptr);
    printf("链表中未找到需要删除的结点\n");
  }
}

void sort_score(List *list) {
  if (list->size == 1) return;
  ElemType tmp;
  for (size_t i = 0; i < list->size - 1; i++) {
    Node *ptr = list->first->next;
    for (size_t j = 0; j < list->size - 1 - i; j++)
      if (ptr->data.score > ptr->next->data.score) {
        tmp = ptr->data;
        ptr->data = ptr->next->data;
        ptr->next->data = tmp;
        ptr = ptr->next;
      }
  }
}

void sort_bbs(List *list) {
  if (list->size == 0 || list->size == 1) return;

  // 指针指向首结点
  Node *s = list->first->next;

  // 指针指向次结点
  Node *q = s->next;

  // 切断首结点和次结点的链接
  // 形成两个独立的链list->first 和 q
  list->last = s;
  list->last->next = NULL;

  while (q != NULL) {
    s = q;
    q = q->next;

    Node *p = list->first;
    while (p->next != NULL || p->next->data.score < s->data.score) {
      p = p->next;
    }

    if (p->next = NULL) {
      list->last = s;
    }

    s->next = p->next;
    p->next = s;
  }
}