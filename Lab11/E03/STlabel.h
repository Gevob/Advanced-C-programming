#ifndef STLABEL_H_INCLUDED
#define STLABEL_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define MAX 31
typedef struct STlab *st;

st STinit();
void STfree(st lab);
void STinsert(st lab,char *key);
void STBubble(st lab);
int STsize(st lab);
int STgetindex(st lab,char *key);
char *STgetnamebyindex(st lab,int key);
#endif // STLABEL_H_INCLUDED
