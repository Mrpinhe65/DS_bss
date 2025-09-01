#ifndef __GENLIST_H__
#define __GENLIST_H__

#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AtomType int

typedef enum { HEAD, ATOM, CHILDLIST } ElemTag;

typedef struct GLNode {
  ElemTag tag; // HEAD / ATOM / CHILDLIST 之一
  union {
    AtomType atom;
    struct GLNode *hp;
  };
  struct GLNode *tp;
} GLNode;

typedef GLNode *GenList;

void InitGenList(GenList &gl);
void CreateGenList(GenList &gl, char *str);
bool server(char *sub, char *hsub);
void ShowGenList(GenList &gl);
bool GenListEmpty(GenList &gl);
size_t GenListLength(GenList &gl);
int GenListDepth(GenList &gl);

#endif // __GENLIST_H__

int main(int argc, char *argv[]) {
  GenList gl;
  InitGenList(gl);

  char ga[] = "(1,2,3)";
  char gb[] = "(1,(2,3))";
  char gc[] = "(1,(2,3),4)";
  char gd[] = "((1,2),3)";
  char ge[] = "((1,2,3))";
  char gf[] = "()";
  char gg[] = "(1,(2,(3,4)),5,(6,7),8)";
  CreateGenList(gl, gg);
  ShowGenList(gl);
  printf("\n");
  size_t length = GenListLength(gl);
  printf("%ld\n", length);

  printf("depth=%d\n", GenListDepth(gl));

  return 0;
}

void InitGenList(GenList &gl) { gl = NULL; }

//     char ga[]="(1,2,3)";
//     char gb[]="(1,(2,3))";
//     char gc[]="(1,(2),3)";
//     char gd[]="((1,2),3)";
//     char ge[]="((1,2,3))";
//     char gf[]="()";
//     char gg[]="(1,(2,(3,4)),5)";

void CreateGenList(GenList &gl, char *str) {
  int n = strlen(str);
  char *sub = (char *)malloc(sizeof(char) * (n - 2));
  char *hsub = (char *)malloc(sizeof(char) * (n - 2));
  assert(sub != NULL && hsub != NULL);
  strncpy(sub, str + 1, n - 2); // "1,2,3"
  sub[n - 2] = '\0';
  if (gl == NULL) {
    gl = (GLNode *)malloc(sizeof(GLNode));
    assert(gl != NULL);
    gl->tag = HEAD;
    gl->hp = gl->tp = NULL;
  }
  GLNode *p = gl;
  while (strlen(sub) != 0) {
    p = p->tp = (GLNode *)malloc(sizeof(GLNode));
    assert(p != NULL);
    p->hp = p->tp = NULL;

    // server函数
    // “1，2，3” -> hsub="1",sub="2,3"
    // "(1,2),3,4" -> hsub="(1,2)",sub="3,4"
    if (server(sub, hsub)) {
      if (hsub[0] == '(') {
        p->tag = CHILDLIST;
        CreateGenList(p->hp, hsub);
      } else {
        p->tag = ATOM;
        p->atom = atoi(hsub);
      }
    }
  }
}
// server函数
// “1，2，3” -> hsub="1",sub="2,3"
// "(1,2),3,4" -> hsub="(1,2)",sub="3,4"
bool server(char *sub, char *hsub) {
  if (*sub == '\0' || strcmp(sub, "()") == 0) {
    hsub[0] = '\0';
    return true;
  }

  int n = strlen(sub);
  int i = 0;
  char ch = sub[0];
  int k = 0;
  while (i < n && (ch != ',' || k != 0)) {
    if (ch == '(')
      k++;
    else if (ch == ')')
      k--;
    i++;
    ch = sub[i];
  }
  if (i < n) {
    sub[i] = '\0';
    strcpy(hsub, sub);
    strcpy(sub, sub + i + 1);
  } else if (k != 0)
    return false;
  else {
    strcpy(hsub, sub);
    sub[0] = '\0';
  }
  return true;
}

void ShowGenList(GenList &gl) {
  GLNode *p = gl->tp;
  printf("(");
  while (p != NULL) {
    if (p->tag == ATOM) {
      printf("%d", p->atom);
      if (p->tp != NULL)
        printf(",");
      p = p->tp;
    } else if (p->tag == CHILDLIST) {
      ShowGenList(p->hp);
      p = p->tp;
    }
  }
  printf("),");
}

bool GenListEmpty(GenList &gl) { return gl->tp == NULL; }

size_t GenListLength(GenList &gl) {
  size_t length = 0;
  GLNode *p = gl->tp;
  while (p != NULL) {
    length++;
    p = p->tp;
  }
  return length;
}

int GenListDepth(GenList &gl) {
  if (gl->tp == NULL)
    return 1;
  GLNode *p = gl->tp;
  int maxdep = 0;
  int dep;
  while (p != NULL) {
    if (p->tag == CHILDLIST) {
      dep = GenListDepth(p->hp->tp);
      if (dep > maxdep)
        maxdep = dep;
    }
    p = p->tp;
  }
  return maxdep + 1;
}
