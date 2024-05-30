#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "STlabel.h"
struct STlab{
int n_v,cap;
char **vertici;
};

st STinit(){
st lab;
lab=malloc(sizeof(*lab));
lab->n_v=0;
lab->vertici=malloc(sizeof(char *)*2);
lab->vertici[0]=malloc(sizeof(char)*MAX);
lab->vertici[1]=malloc(sizeof(char)*MAX);
lab->cap=2;
return lab;
}
void STinsert(st lab,char *key){
if(lab->n_v==0){
    strcpy(lab->vertici[0],key);
    lab->n_v++;}
if(lab->n_v!=0){
    for(int i=0;i<lab->n_v;i++)
        if(strcmp(lab->vertici[i],key)==0)
           return;
    strcpy(lab->vertici[lab->n_v],key);
    lab->n_v++;
    if(lab->n_v==lab->cap){
        lab->vertici=realloc(lab->vertici,2*lab->cap*sizeof(char *));
        lab->cap=lab->cap*2;
        for(int i=lab->n_v;i<lab->cap;i++)
            lab->vertici[i]=malloc(sizeof(char)*MAX);
    }
}
return;
}

void STBubble(st lab){
char tmp[MAX];
for(int i=0;i<lab->n_v-1;i++)
    for(int j=0;j<lab->n_v-1-i;j++)
       if(strcmp(lab->vertici[j],lab->vertici[j+1])>0){
          strcpy(tmp,lab->vertici[j]);
          strcpy(lab->vertici[j],lab->vertici[j+1]);
          strcpy(lab->vertici[j+1],tmp);
        }
}
int STsize(st lab){
return lab->n_v;
}

int STgetindex(st lab,char *key){
int i=0;
while(strcmp(lab->vertici[i],key)!=0&&i<lab->n_v)
    i++;
if(i<lab->n_v)
    return i;
else
    return -1;
}
char *STgetnamebyindex(st lab,int key){
return lab->vertici[key];
}
void STfree(st lab){
for(int i=0;i<lab->n_v;i++)
    free(lab->vertici[i]);
free(lab->vertici);
free(lab);
return;
}
