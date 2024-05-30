#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pgList.h"

typedef struct node *link;
struct node{
pg_t pg_node;
link next;
};
struct pgList_s{
pg_t pg_tmp;
link head;
int n;
};

pgList_t pgList_init(){
pgList_t pgList;
pgList=malloc(sizeof(struct pgList_s));
if(pgList==NULL){
    printf("Errore malloc pgList\n");
    exit(EXIT_FAILURE);
}
pgList->head=NULL;
pgList->n=0;
return pgList;
}
void pgList_read(FILE *fp, pgList_t pgList){
while(pg_read(fp,&pgList->pg_tmp)==1){
pgList_insert(pgList,pgList->pg_tmp);
}
}


void pgList_insert(pgList_t pgList, pg_t pg){
link x=pgList->head;
if(x==NULL){
pgList->head=malloc(sizeof(*pgList->head));
pgList->head->pg_node=pg;
pgList->head->pg_node.equip=equipArray_init();
pgList->head->next=NULL;
}else{
for(x;x!=NULL;x=x->next)
   if(x->next==NULL){
    x->next=malloc(sizeof(*x));
    x->next->pg_node=pg;
    x->next->pg_node.equip=equipArray_init();
    x->next->next=NULL;
    break;
   }
}
}

void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray){
link x=pgList->head;
for(x;x!=NULL;x=x->next){
    pg_print(fp,&x->pg_node,invArray);//void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray);
}
}

void pgList_remove(pgList_t pgList, char* cod){
link p=NULL,x,t;
for(x=pgList->head;x!=NULL;p=x,x=x->next){
    if(strcmp(x->pg_node.cod,cod)==0){
       if(x==pgList->head){
       t=pgList->head;
       pgList->head=x->next;
       pg_clean(&t->pg_node);
       free(t);
       printf("PG rimosso\n");
       return;
       }
       else{
       t=x;
       p->next=x->next;
       x=x->next;
       pg_clean(&t->pg_node);
       free(t);
       printf("PG rimosso\n");
       return;
       }
    }
}
}

pg_t *pgList_searchByCode(pgList_t pgList, char* cod){
link x;
for(x=pgList->head;x!=NULL;x=x->next){
    if(strcmp(x->pg_node.cod,cod)==0){
        return &x->pg_node;
    }
}
printf("Il codice inserito non corrisponde a nessun personaggio\n");
return NULL;
}

void pgList_free(pgList_t pgList){
link x=pgList->head,tmp;
for(x;x!=NULL;){
  tmp=x;
  if(x->next!=NULL){
  x=x->next;
  pg_clean(&tmp->pg_node);
  free(tmp);
  }
  else{
  pg_clean(&tmp->pg_node);
  free(tmp);
  break;
  }
}
return;
}
