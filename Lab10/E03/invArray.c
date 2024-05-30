#include <stdio.h>
#include <stdlib.h>
#include "invArray.h"

struct invArray_s{
inv_t *invp;
int n,item;
};

invArray_t invArray_init(){
invArray_t invArray;
invArray=malloc(sizeof(struct invArray_s));
invArray->item=-1;
return invArray;
}
void invArray_read(FILE *fp, invArray_t invArray){
int l;
fscanf(fp,"%d",&l);
invArray->invp=malloc(sizeof(inv_t)*l);
invArray->n=l;
for(int i=0;i<l;i++){
    inv_read(fp,&invArray->invp[i]);
    stat_read(fp,&invArray->invp[i].stat);
    }
return;
}
void invArray_print(FILE *fp, invArray_t invArray){
    for(int i=0;i<invArray->n;i++){
        inv_print(fp,&invArray->invp[i]);
        stat_print(fp,&invArray->invp[i].stat,1);
    }
}
int invArray_searchByName(invArray_t invArray, char *name){
for(int i=0;i<invArray->n;i++)
    if(strcmp(name,invArray->invp[i].nome)==0){
       invArray->item=i;
       return i;
    }
return -1;
}


void invArray_free(invArray_t invArray){
free(invArray->invp);
free(invArray);
}
void invArray_printByIndex(FILE *fp, invArray_t invArray, int index){
inv_print(fp,&invArray->invp[index]);
stat_print(fp,&invArray->invp[index].stat,1);
}
inv_t *invArray_getByIndex(invArray_t invArray, int index){
inv_t *inv;
inv=&invArray->invp[index];
return inv;
}
