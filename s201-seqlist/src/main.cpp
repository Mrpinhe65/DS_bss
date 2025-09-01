#include "../include/seqlist.h"
#include "seqlist.cpp"

int main() {
  SeqList myList;
  InitSeqList(&myList);

  ElemType Item;
  ElemType data_del;
  int pos;
  float score;
  int select = 1;
  char flag;
  while (select) {
    select = menu();
    if (select == 0) {
      /*
      printf("退出时默认需要保存数据，如不需要保存数据请输入‘N’:>");
      scanf("%c", &flag);
      if (flag == 'n' | flag == 'N') {
        return 0;
      }
        */

      FILE* fp = fopen(FILENAME, "wb");
      if (fp == NULL) perror("文件打开失败，数据未能保存\n");

      fwrite(myList.base, sizeof(ElemType), myList.size, fp);
      fclose(fp);

      return 0;
    }
    switch (select) {
      case 1:  // push_back
        push_back(&myList, Item);
        break;
      case 2:
        if (myList.size >= myList.capacity) {
          printf("顺序表空间已满，不能头插数据!\n");
          break;
        }
        inputElemData(&Item);
        push_front(&myList, Item);
        break;
      case 3:
        showList(myList);
        break;
      case 4:
        pop_back(&myList, &data_del);

        printf("Number = %d\n", data_del.num);
        printf("Name = %s\n", data_del.name);
        printf("Score = %.1f\n", data_del.score);
        break;
      case 5:
        pop_front(&myList, &data_del);

        printf("Number = %d\n", data_del.num);
        printf("Name = %s\n", data_del.name);
        printf("Score = %.1f\n", data_del.score);
        break;

      case 6:
        // insert_pos
        printf("please input insert postion:>");
        scanf("%d", &pos);
        printf("size = %d\n", myList.size);
        if (pos <= 0 || pos > myList.capacity || pos > myList.size) {
          printf("insert postion Invalid!\n");
          break;
        }
        inputElemData(&Item);
        insert_pos(&myList, Item, pos - 1);
        break;

      case 7:  // find
        printf("\nplease input score:>");
        scanf("%f", &score);
        find_by_score(&myList, score, &Item);

        printf("number = %d\n", Item.num);
        printf("name = %s\n", Item.name);
        printf("score = %.1f\n", Item.score);

        break;
      case 8:
        printf("SeqList capacity = %d\n", myList.capacity);
        printf("SeqList length = %d\n", myList.size);
        break;
      case 9:
        printf("please input delete postion:>");
        scanf("%d", &pos);
        if (pos <= 0 || pos > myList.size) {
          printf("The postion invalid!\n");
          break;
        }
        delete_pos(&myList, &data_del, pos - 1);
        break;
      case 10:
        printf("please input delete's score:>");
        scanf("%f", &score);
        delete_score(&myList, &data_del, score);
        break;
      case 11:
        // sort_by_score(&myList,pfunc);//函数指针 回调函数
        // sort_by_pfun(&myList,myList.size,sizeof(myList),int(*fun)(const
        // void*e1,const void*e2));

        // qsort(&myList, myList.size, sizeof(myList), cmp_score);
        sort_bubble(&myList);

        break;
      case 12:
        resver(&myList);
        break;
      case 13:
        myList.size = 0;
        break;
      case 14:
        /*
        printf("\n销毁顺序表和数据文件，系统退出，确定吗？[y/n]:>");
          char flag;
          scanf("%c", &flag);
          if (flag != 'y' | flag != 'Y') break;
          wait_for_any_key();
          */
        myList.size = 0;
        free(myList.base);
        if (myList.base != NULL) myList.base = NULL;

        remove(FILENAME);
        return 0;
      default:
        printf("you select wrong, please select again!\n");
    }
  }

  return 0;
}