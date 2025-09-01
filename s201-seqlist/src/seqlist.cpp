#include "../include/seqlist.h"

// 顺序表初始化 开辟顺序表内存 确定容量 实际大小
void InitSeqList(SeqList *list) {
  list->base = (ElemType *)malloc(sizeof(ElemType) * SEQLIST_INIT_SIZE);
  assert(list->base != NULL);
  list->capacity = SEQLIST_INIT_SIZE;
  list->size = 0;

  FILE *fp = fopen(FILENAME, "rb");
  if (fp != NULL) {
    // 移动到文件末尾
    fseek(fp, 0, SEEK_END);
    // 获取文件大小（单位：字节）
    long file_size = ftell(fp);
    fclose(fp);

    // 计算结构体个数
    list->size = file_size / sizeof(ElemType);

    FILE *fp = fopen(FILENAME, "rb");
    fread(list->base, sizeof(ElemType), list->size, fp);
    fclose(fp);
  }
}

// 菜单显示和选择
int menu() {
  printf("************************************\n");
  printf("* [1] push_back    [2] push_front  *\n");
  printf("* [3] show_list    [4] pop_back    *\n");
  printf("* [5] pop_front    [6] insert_pos  *\n");
  printf("* [7] find_score   [8] length      *\n");
  printf("* [9] delete_pos   [10] delete_val *\n");
  printf("* [11]sort         [12] resver     *\n");
  printf("* [13]clear        [14] destory    *\n");
  printf("* [0] quit_system                  *\n");
  printf("************************************\n");

  int select;
  printf("please select >");
  scanf("%d", &select);
  return select;
}

// 顺序表元素数据输入
void inputElemData(ElemType *item) {
  printf("\nplease input data:[1] Card number>");
  scanf("%d", &item->num);

  while (getchar() != '\n');  // 清除输入缓冲区

  // 输入带空格的名字或其他字符串，scanf fgets
  printf("\nplease input data:[2] Name>");
  // scanf("%s", &item->name);
  fgets(item->name, sizeof(item->name), stdin);
  // 去除可能的换行符
  item->name[strcspn(item->name, "\n")] = '\0';
  printf("\nplease input data:[3] Score>");
  scanf("%f", &item->score);
}

// case 1
void push_back(SeqList *list, ElemType data) {
  if (list->size >= list->capacity && !Inc(list)) {
    printf("顺序表空间已满，不能尾插数据!\n");
    return;
  }
  inputElemData(&data);
  list->base[list->size] = data;

  list->size++;
}

// case 2
void push_front(SeqList *list, ElemType data) {
  if (list->size >= list->capacity && !Inc(list)) {
    printf("顺序表空间已满，不能前插数据！\n");
    return;
  }
  for (int i = list->size; i > 0; i--) {
    list->base[i] = list->base[i - 1];
  }
  list->base[0] = data;
  list->size++;
}

// case 3
void showList(SeqList list) {
  for (int i = 0; i < list.size; i++) {
    printf("Number = %d\n", list.base[i].num);
    printf("Name = %s\n", list.base[i].name);
    printf("Score = %.1f\n", list.base[i].score);
    printf("=====================\n");
  }
}

// case 4 pop_back

void pop_back(SeqList *list, ElemType *data) {
  if (list->size == 0) {
    printf("顺序表已没有可删除数据！\n");
    return;
  }
  *data = list->base[list->size - 1];
  list->size--;
}

// case 5 pop_front

void pop_front(SeqList *list, ElemType *data) {
  if (list->size == 0) {
    printf("顺序表已没有可删除数据！\n");
    return;
  }

  *data = list->base[0];
  for (int i = 0; i < list->size; i++) {
    list->base[i] = list->base[i + 1];
  }
  list->size--;
}

// case 6 insert_pos
void insert_pos(SeqList *list, ElemType data, int pos) {
  if (list->size >= list->capacity && !Inc(list)) {
    printf("顺序表空间已满，不能尾插数据!\n");
    return;
  }
  // 以下2个if可以省略
  if (pos == 0) {
    push_front(list, data);
    list->size++;
    return;
  }
  if (pos == list->size) {
    push_back(list, data);
    list->size++;
    return;
  }

  for (int i = list->size; i <= pos; i--) {
    list->base[i] = list->base[i - 1];
  }
  list->base[pos] = data;
  list->size++;
}

// case 7 find by score
void find_by_score(SeqList *list, float score, ElemType *data) {
  //
  for (int i = 0; i < list->size; i++) {
    if (fabs(list->base[i].score - score) < 0.01) {
      printf("list->base[i]->score = %f\n", list->base[i].score);
      *data = list->base[i];
      return;
    }
  }
}

// case 9 delete by postion
void delete_pos(SeqList *list, ElemType *data, int pos) {
  if (pos == list->size - 1) {
    pop_back(list, data);
    list->size--;
    return;
  }
  for (int i = pos; i < list->size - 1; i++) {
    list->base[i] = list->base[i + 1];
  }
  list->size--;
}

void delete_score(SeqList *list, ElemType *data, float score) {
  for (int i = 0; i < list->size; i++) {
    if (fabs(list->base[i].score - score) < 0.01) {
      if (i == 0) {
        pop_front(list, data);
        return;
      }
      if (i == list->size - 1) {
        pop_back(list, data);
        return;
      }
      delete_pos(list, data, i);
    }
  }
}

void sort_by_pfun(void *list, int n, int width,
                  int (*fun)(const void *e1, const void *e2)) {
  // TODO
  for (int i = 0; i < n; i++) {
  }
}

void resver(SeqList *list) {
  int low = 0;
  int hight = list->size - 1;
  ElemType tmp;
  while (1) {
    tmp = list->base[low];
    list->base[low] = list->base[hight];
    list->base[hight] = tmp;
    low++;
    hight--;
    if (low >= hight) break;
  }
}
/*
void wait_for_any_key() {
  system("clear");
  printf("program in fenction 'wait_for_any_key'\n");
  struct termios oldt, newt;
  tcgetattr(STDIN_FILENO, &oldt);  // 获取当前终端设置
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);  // 禁用规范模式和回显
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  printf("Press any key to continue...\n");
  getchar();                                // 现在可以捕获任意键（无需回车）
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // 恢复终端设置
}
  */

int cmp_score(const void *a, const void *b) {
  float score1 = *(const float *)a;
  float score2 = *(const float *)b;
  if (score1 < score2) return -1;
  if (score1 > score2) return 1;
  return 0;
}

void sort_bubble(SeqList *list) {
  for (int i = 0; i < list->size - 1; i++) {
    for (int j = 0; j < list->size - i - 1; j++) {
      if (list->base[j].score < list->base[j + 1].score) {
        ElemType temp = (list->base[j]);
        (list->base[j]) = (list->base[j + 1]);
        (list->base[j + 1]) = temp;
      }
    }
  }
}

void wait_for_any_key() {
  printf("Press any key to continue...\n");
  getchar();  // 等待用户按回车键
              // 如果之前有残留的输入（如 scanf
              // 后的换行符），需要先清空缓冲区： while (getchar() != '\n');
}

/* 二进制文件读写
#include <stdio.h>

int main(int argc, char* argv[]) {
  int ar[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int n = sizeof(ar) / sizeof(ar[0]);

  // 存储成二进制文件
  FILE* fp_write = fopen("binary.dat", "wb");
  if (fp_write == nullptr) {
    printf("File open error!\n");
    return -1;
  }

  fwrite(ar, sizeof(int), n, fp_write);
  fclose(fp_write);

  // 二进制文件读取
  int br[10];
  FILE* fp_read = fopen("binary.dat", "rb");
  if (fp_read == nullptr) {
    printf("File open error!\n");
    return -1;
  }

  fread(br, sizeof(int), 10, fp_read);

  fclose(fp_read);

  for (int i = 0; i < 10; i++) {
    printf("%d ", br[i]);
  }
  printf("\n");

  return 0;
}
*/

bool Inc(SeqList *list) {
  ElemType *newbase = (ElemType *)realloc(
      list->base, sizeof(ElemType) * (list->capacity + INC_SIZE));
  if (newbase == NULL) {
    perror("增扩空间失败");
    return false;
  }
  list->base = newbase;
  list->capacity += INC_SIZE;
  return true;
}