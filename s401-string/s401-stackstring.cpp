#ifndef __SSTRING_H__
#define __SSTRING_H__

#include <assert.h>
#include <stdio.h>
#include <string.h>

#define MAXSTRLEN 20
#define u_char unsigned char

typedef u_char SString[MAXSTRLEN + 1];

void InitString(SString s);
void StrAssign(SString s, const char *str);
void StrCopy(SString t, SString s);
bool StrEmpty(SString s);
int StrCompare(SString s, SString t);
int StrLength(SString s);
void StrConcat(SString t, SString s1, SString s2);
void SubStr(SString s, SString sub, int pos, int length);
void StrInsert(SString s, int pos, SString t);
void StrDelete(SString s, int pos, int length);
void StrClear(SString s);

int StrIndex(SString s, SString t, int pos);
void StrReplace(SString s, SString t, SString v);

#endif // __SSTRING_H__

int main(int argc, char *argv[]) {
  SString S;
  InitString(S);
  /*
  StrConcatnst char *str = "abcdef";
  StrAssign(S, str);
  printf("%s\n", S);
  SString t;
  StrCopy(t, S);
  printf("%s\n", t);
  StrAssign(S, "abcdefq");
  StrAssign(t, "abcdefx");
  int res = StrCompare(S, t);
  printf("%d\n", res);
  SString Y;
  InitString(Y);
  StrConcat(Y, S, t);
  printf("%s\n", Y);
  SString sub;
  SubStr(Y, sub, 9, 4);
  printf("%s\n", sub);

  StrAssign(S, "abcdefghijklm");
  StrAssign(t, "xyz12345678");
  StrInsert(S, 3, t);
  printf("%s\n", S);
  StrAssign(S, "abcdefghijklmnopqrst");
  printf("%s\n", S);
  StrDelete(S, 18, 19);
  printf("%s\n", S);
*/

  StrAssign(S, "ababcababcabc");
  SString T;
  InitString(T);
  StrAssign(T, "abc");
  int index = StrIndex(S, T, 0);
  printf("index = %d\n", index);

  SString V;
  InitString(V);
  StrAssign(V, "xy");

  StrReplace(S, T, V); // abxyabxyab
  printf("%s\n", S);

  return 0;
}
void InitString(SString s) { s[0] = '\0'; }
void StrAssign(SString s, const char *str) {
  int len = strlen(str);
  for (int i = 0; i < len; i++) {
    s[i] = str[i];
  }
  s[len] = '\0';
}

void StrCopy(SString t, SString s) {
  int len = StrLength(s);
  for (int i = 0; i < len; i++) {
    t[i] = s[i];
  }
  t[len] = '\0';
}
bool StrEmpty(SString s) { return s[0] == '\0'; }
int StrCompare(SString s, SString t) {
  int result = 0;
  while (*s != '\0' || *t != '\0') {
    result = *s - *t;
    if (result != 0)
      break;
    s++;
    t++;
  }
  if (result > 0) {
    result = 1;
  } else if (result < 0) {
    result = -1;
  }
  return result;
}

int StrLength(SString s) {
  int len = 0;
  while (*s != '\0') {
    len++;
    s++;
  }
  return len;
}
void StrConcat(SString t, SString s1, SString s2) {
  int len1 = StrLength(s1);
  int len2 = StrLength(s2);
  if (len1 + len2 <= MAXSTRLEN) {
    for (int i = 0; i < len1; i++) {
      t[i] = s1[i];
    }
    for (int j = 0; j < len2; j++) {
      t[len1 + j] = s2[j];
    }
    t[len1 + len2] = '\0';
  } else if (len1 <= MAXSTRLEN && len1 + len2 > MAXSTRLEN) {
    for (int i = 0; i < len1; i++) {
      t[i] = s1[i];
    }
    for (int j = 0; j < MAXSTRLEN - len1; j++) {
      t[len1 + j] = s2[j];
    }
    t[MAXSTRLEN] = '\0';
  } else {
    for (int i = 0; i < MAXSTRLEN; i++) {
      t[i] = s1[i];
    }
    t[MAXSTRLEN] = '\0';
  }
}

void SubStr(SString s, SString sub, int pos, int length) {
  if (pos < 0 || pos >= MAXSTRLEN || length < 0)
    return;
  if (pos + length > MAXSTRLEN)
    length = MAXSTRLEN - pos;

  for (int i = 0; i < length; i++) {
    sub[i] = s[i + pos];
  }
  sub[length] = '\0';
}

// 长度不足的，保留s的字符，剩余的才考虑插入t的字符
void StrInsert(SString s, int pos, SString t) {
  int len_s = StrLength(s);
  int len_t = StrLength(t);
  if (len_s == MAXSTRLEN)
    return;
  if (len_s + len_t <= MAXSTRLEN) {
    for (int i = len_s - 1; i >= pos; i--) {
      s[i + len_t] = s[i];
    }
    for (int j = 0; j < len_t; j++) {
      s[j + pos] = t[j];
    }
  } else {
    int remain = MAXSTRLEN - len_s;
    // if(remain>len_t)remain=len_t;//在前面条件（len_s+len_t<=MAXSTRLEN）控制下，不会发生

    for (int i = len_s - 1; i >= pos; i--) {
      s[i + remain] = s[i];
    }
    for (int j = 0; j < remain; j++) {
      s[j + pos] = t[j];
    }
  }
}

void StrDelete(SString s, int pos, int length) {
  int len = StrLength(s);
  if (pos < 0 || pos > len || length <= 0)
    return;
  if (length > len - pos)
    length = len - pos;
  for (int i = 0; i < len; i++) {
    s[i + pos] = s[i + pos + length];
  }
  s[len - length] = '\0';
}
void StrClear(SString s) { s[0] = '\0'; }

int StrIndex(SString s, SString t, int pos) {
  int i = pos;
  int j = 0;
  // 逐个字符比对，如果字符串没有结束则一直比对
  while (s[i] != '\0' && t[j] != '\0') {
    // 字符比对成功，继续比对下一个字符
    if (s[i] == t[j]) {
      i++;
      j++;
      // 否则S串从上一次比对的第一个字符的下一个字符开始
      // 匹配串从头开始
    } else {
      i = i - j + 1;
      j = 0;
    }
  }
  // 如果匹配串比对到\0,则比对成功
  if (t[j] == '\0')
    return i - j;
  return -1;
}

void StrReplace(SString s, SString t, SString v) {
  int len_s = StrLength(s);
  int len_t = StrLength(t);
  int len_v = StrLength(v);
  int index = -1;
  int pos = 0;

  while (pos < len_s) {
    index = StrIndex(s, t, pos);
    if (index == -1)
      return;
    StrDelete(s, index, len_t);
    StrInsert(s, index, v);
    len_s = StrLength(s);
    pos = index + len_v;
  }
}
