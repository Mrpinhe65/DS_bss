#ifndef __HEAPSTR_H__
#define __HEAPSTR_H__

#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

typedef struct HString {
  char *ch;
  int length;
} HString;

void InitString(HString *s);

void PrintString(HString *s);
void StrAssign(HString *s, const char *str);
void StrCopy(HString *t, HString *s);
bool StrEmpty(HString *s);
int StrCompare(HString *s, HString *t);
int StrLength(HString *s);
void StrConcat(HString *t, HString *s1, HString *s2);
void SubStr(HString *s, HString *sub, int pos, int length);
void StrInsert(HString *s, int pos, HString *t);
void StrDelete(HString *s, int pos, int length);
void StrClear(HString *s);
void StrDestroy(HString *s);
void StrIndex(HString *s, HString *t, int pos);
void StrReplace(HString *s, HString *t, HString *v);

#endif //__HEAPSTR_H__

int main(int argc, char *argv[]) {

  HString S;
  InitString(&S);

  StrAssign(&S, "abcd");
  PrintString(&S);

  HString T;
  InitString(&T);
  StrCopy(&T, &S);
  PrintString(&T);

  StrAssign(&T, "abcdxyz");
  PrintString(&T);
  int res = StrCompare(&S, &T);
  printf("res = %d\n", res);

  HString STR;
  InitString(&STR);
  StrConcat(&STR, &S, &T);
  PrintString(&STR);

  HString sub;
  InitString(&sub);
  SubStr(&STR, &sub, 0, 6);
  PrintString(&sub);

  InitString(&S);
  StrAssign(&S, "0123456789");
  StrInsert(&STR, 23, &S);
  PrintString(&STR);

  StrDelete(&STR, 5, 5);
  PrintString(&STR);

  StrDestroy(&S);
  // StrDestroy(&sub);
  StrDestroy(&T);
  StrDestroy(&STR);

  return 0;
}

void InitString(HString *s) {
  s->ch = NULL;
  s->length = 0;
}

void PrintString(HString *s) {
  for (int i = 0; i <= s->length; i++) {
    printf("%c", s->ch[i]);
  }
  printf("\n");
}

void StrAssign(HString *s, const char *str) {
  int len = strlen(str);
  if (s->ch != NULL)
    free(s->ch);
  s->ch = (char *)malloc(sizeof(char) * len);
  assert(s->ch != NULL);
  for (int i = 0; i < len; i++) {
    s->ch[i] = str[i];
  }
  s->length = len;
}

void StrCopy(HString *t, HString *s) {
  int len = StrLength(s);
  if (t->ch != NULL)
    free(t->ch);
  t->ch = (char *)malloc(sizeof(char) * len);
  assert(t->ch != NULL);
  for (int i = 0; i <= len; i++) {
    t->ch[i] = s->ch[i];
  }
  t->length = len;
}

bool StrEmpty(HString *s) { return s->length == 0; }

int StrCompare(HString *s, HString *t) {
  if (s->length == 0 && t->length == 0)
    return 0;
  int i = 0;
  int j = 0;
  int result = 0;
  while (i < s->length && j < t->length) {
    if (s->ch[i] > t->ch[j])
      return 1;
    else if (s->ch[i] < t->ch[j])
      return -1;
    else {
      i++;
      j++;
    }
  }
  if (i < s->length) {
    result = 1;
  } else if (j < t->length) {
    result = -1;
  }
  return result;
}

int StrLength(HString *s) { return s->length; }

void StrConcat(HString *t, HString *s1, HString *s2) {
  int len_s1 = StrLength(s1);
  int len_s2 = StrLength(s2);
  if (t->ch != NULL)
    free(t->ch);
  t->ch = (char *)malloc(sizeof(char) * (len_s1 + len_s2));
  assert(t->ch != NULL);
  for (int i = 0; i < len_s1; i++) {
    t->ch[i] = s1->ch[i];
  }
  for (int j = 0; j < len_s2; j++) {
    t->ch[len_s1 + j] = s2->ch[j];
  }
  t->length = len_s1 + len_s2;
}

void SubStr(HString *s, HString *sub, int pos, int length) {
  if (pos < 0 || pos > s->length)
    return;

  if (length + pos > s->length)
    length = s->length - pos;
  sub->ch = (char *)malloc(sizeof(char) * length);
  assert(sub->ch != NULL);

  for (int i = 0; i < length; i++) {
    sub->ch[i] = s->ch[i + pos];
  }
  sub->length = length;
}

void StrInsert(HString *s, int pos, HString *t) {
  int len = StrLength(t);
  if (len == 0)
    return;
  if (pos < 0)
    return;
  if (pos > s->length + 1)
    pos = s->length + 1;
  int len_realloc = s->length + len;
  char *ch = (char *)realloc(s->ch, sizeof(char) * len_realloc);
  assert(ch != NULL);
  s->ch = ch;
  ch = NULL;
  for (int i = len_realloc; i >= pos; i--) {
    s->ch[i] = s->ch[i - len];
  }
  for (int j = 0; j < len; j++) {
    s->ch[j + pos] = t->ch[j];
  }
  s->length = len_realloc;
}

void StrDelete(HString *s, int pos, int length) {
  if (pos < 0 || pos > s->length)
    return;
  if (length + pos > s->length)
    length = s->length - pos;
  for (int i = 0; i < s->length; i++) {
    s->ch[i + pos] = s->ch[i + pos + length];
  }
  s->length -= length;
}

void StrClear(HString *s) { s->length = 0; }

void StrDestroy(HString *s) {
  if (s->ch != NULL)
    free(s->ch);
  s->ch = NULL;
  s->length = 0;
}

void StrIndex(HString *s, HString *t, int pos);
void StrReplace(HString *s, HString *t, HString *v);
