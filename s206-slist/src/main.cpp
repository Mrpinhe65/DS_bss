#include "../include/slist.hpp"
#include "slist.cpp"

// 函数指针数组-- 转移表
//  int (*func[])(Node*) = {nullptr, add, sub, mul, div, mod};

int main() {
  List myList;
  InitList(&myList);

  // ElemType elem;

  int select;
  while (1) {
    select = menu();

    switch (select) {
      case 0:
        if (myList.size != 0) {
          saveFile(&myList);
        }
        // 退出时摧毁链表
        destory_list(&myList);
        return 0;
      case 1:
        push_back(&myList);
        break;
      case 2:
        push_front(&myList);
        break;
      case 3:
        show_List(&myList);
        break;
      case 4:
        pop_back(&myList);
        break;
      case 5:
        pop_front(&myList);
        break;
      case 6:
        insert_pos(&myList);
        break;
      case 7:
        find_score(&myList);
        break;
      case 8:
        printf("list.size = %lu\n", myList.size);
        break;
      case 9:
        delete_score(&myList);
        break;
      case 10:
        // sort_score(&myList);
        sort_bbs(&myList);
        break;
      case 13:
        saveFile(&myList);
        break;

      default:
        printf("功能选择错误，请重新选择\n");
        break;
    }
  }
  return 0;
}
