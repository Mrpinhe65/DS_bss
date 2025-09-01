#ifndef __SPARSEMATRIX_H__
#define __SPARSEMATRIX_H__

#include <assert.h>
#include <malloc.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>

#define ElemType int

#define MAXSIZE 100

typedef struct Triple // 三元组
{
  int i;      // 行
  int j;      // 列
  ElemType e; // 值
} Triple;

typedef struct SMatrix {
  Triple data[MAXSIZE];
  int mu; // 矩阵行数
  int nu; // 矩阵列数
  int tu; // 矩阵非零元素数量
} SMatrix;

// declaration of function
void CreateSMatrix(SMatrix *m);
void ShowMatrix(SMatrix *m);
void CopyMatrix(SMatrix *sm, SMatrix *sm_cp);
void AddMatrix(SMatrix *M, SMatrix *N, SMatrix *T);
void SubMatrix(SMatrix *M, SMatrix *N, SMatrix *T);
void MulMatrix(SMatrix *M, SMatrix *N, SMatrix *T);
void TransposeMatrix(SMatrix *M, SMatrix *T);
void TransposeMatrix_bss(SMatrix *M, SMatrix *T);
void TransposeMatrix_fast(SMatrix *M, SMatrix *T);

#endif //__SPARSEMATRIX_H__

int main() {
  SMatrix sm;
  memset(&sm, 0, sizeof(sm));
  CreateSMatrix(&sm);
  ShowMatrix(&sm);

  SMatrix sm_cp;
  memset(&sm_cp, 0, sizeof(sm_cp));
  CopyMatrix(&sm, &sm_cp);
  ShowMatrix(&sm_cp);

  SMatrix T;
  printf("先转轴再冒泡按新x轴/行排序\n");
  TransposeMatrix(&sm, &T);
  ShowMatrix(&T);
  TransposeMatrix_bss(&sm, &T);
  printf("原数据外层按列nu循环，内层按个数tu循环，内层列数据与外层相同的则先排"
         "进T->data[]\n");
  ShowMatrix(&T);

  memset(&T, 0, sizeof(T));
  TransposeMatrix_fast(&sm, &T);
  ShowMatrix(&T);

  return 0;
}
// implementationmi
void CreateSMatrix(SMatrix *m) {
  FILE *fp = fopen("matrix.dat", "r");
  if (fp == NULL) {
    perror("File open error!");
    return;
  }
  fscanf(fp, "%d %d", &m->mu, &m->nu);
  printf("%d %d\n", m->mu, m->nu);

  int value;
  int count = 0;
  for (int i = 0; i < m->mu; i++) {
    for (int j = 0; j < m->nu; j++) {
      fscanf(fp, "%d", &value);
      if (value != 0) {
        m->data[count].e = value;
        m->data[count].i = i;
        m->data[count].j = j;

        count++;
      }
    }
  }
  m->tu = count;
  fclose(fp);
}

void ShowMatrix(SMatrix *m) {
  printf("row = %d, col = %d\n", m->mu, m->nu);
  for (int i = 0; i < m->tu; i++) {
    printf("(%d, %d, %d)\n", m->data[i].i, m->data[i].j, m->data[i].e);
  }
}

void CopyMatrix(SMatrix *sm, SMatrix *sm_cp) {
  sm_cp->mu = sm->mu;
  sm_cp->nu = sm->nu;
  sm_cp->tu = sm->tu;
  for (int i = 0; i < sm->tu; i++) {
    sm_cp->data[i].e = sm->data[i].e;
    sm_cp->data[i].i = sm->data[i].i;
    sm_cp->data[i].j = sm->data[i].j;
  }
}
void AddMatrix(SMatrix *M, SMatrix *N, SMatrix *T) {}
void SubMatrix(SMatrix *M, SMatrix *N, SMatrix *T);
void MulMatrix(SMatrix *M, SMatrix *N, SMatrix *T);

void TransposeMatrix(SMatrix *M, SMatrix *T) {
  // 先直接交换先x轴y轴，在按新的x轴进行排序
  T->mu = M->nu;
  T->nu = M->mu;
  T->tu = M->tu;

  // 先直接交换先x轴y轴
  for (int i = 0; i < M->tu; i++) {
    T->data[i].i = M->data[i].j;
    T->data[i].j = M->data[i].i;
    T->data[i].e = M->data[i].e;
  }

  // 冒泡排序
  for (int i = 0; i < T->tu - 1; i++) {
    for (int j = 0; j < T->tu - 1 - i; j++) {
      if (T->data[j].i > T->data[j + 1].i ||
          (T->data[j].i == T->data[j + 1].i &&
           T->data[j].j > T->data[j + 1].j)) {
        Triple tmp = T->data[j];
        T->data[j] = T->data[j + 1];
        T->data[j + 1] = tmp;
      }
    }
  }
}

void TransposeMatrix_bss(SMatrix *M, SMatrix *T) {
  // 以下是鲍老师的算法
  // 待完善
  T->mu = M->nu;
  T->nu = M->mu;
  T->tu = M->tu;
  int index = 0;
  for (int col = 0; col < T->mu; col++) {
    for (int i = 0; i < T->tu; i++) {
      // printf("x=%d,y=%d,val=%d\n", M->data[i].i, M->data[i].j, M->data[i].e);
      if (M->data[i].j == col) {
        T->data[index].i = M->data[i].j;
        T->data[index].j = M->data[i].i;
        T->data[index].e = M->data[i].e;
        index++;
        if (index >= T->tu)
          return;
      }
    }
  }
}
void TransposeMatrix_fast(SMatrix *M, SMatrix *T) {
  T->mu = M->nu;
  T->nu = M->mu;
  T->tu = M->tu;
  if (T->tu == 0)
    return;
  // 开辟记录非零元素在某一列个数的堆区空间，按列数开辟
  int *num = (int *)malloc(sizeof(int) * M->nu);
  assert(num != NULL);
  // num全部赋0
  for (int i = 0; i < M->nu; i++)
    num[i] = 0;

  // 将每一列的元素按列映射到num中
  // 如(0,1,12),则是num[1]++,代表第一列有非零数据+1
  //   (0,2,9),则是num[2]++,代表第二有非零数据+1
  for (int col = 0; col < M->tu; col++) {
    num[M->data[col].j]++;
  }

  // 开辟记录每列非零元素的个数,按列数开辟
  // cpot = column postion
  int *cpot = (int *)malloc(sizeof(int) * M->nu);
  assert(cpot != NULL);
  //
  cpot[0] = 0;
  for (int col = 1; col < M->nu; col++) {
    cpot[col] = cpot[col - 1] + num[col - 1];
  }
  int q = 0;
  for (int p = 0; p < M->tu; p++) {
    int col = M->data[p].j;
    q = cpot[col];
    T->data[q].i = M->data[p].j;
    T->data[q].j = M->data[p].i;
    T->data[q].e = M->data[p].e;
    cpot[col]++;
  }
  free(num);
  free(cpot);
}
