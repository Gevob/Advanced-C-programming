#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "titoli.h"
struct titolo{
bst root;
bst z;
char nome[MAX];
};

typedef struct{
float num,den;
}dati;

struct nodo_lista{
link next;
tit titol;
};
typedef struct {
data *date;
dati *quot;
int cap,n_ele;
}tmp;
static void TMPinit(tmp *elementi);
static void lettura(tmp *elementi,int anno,int mese,int giorno,float valore,float num);
static link inserimento_lista(tmp elementi,link lista,char *titolo);
static link NEW(char *tito);
static void TMPfree(tmp *elementi);

link acquisizione(FILE *fp,link lista){
int n_tit,n_dati,anno,mese,ora,minuti,giorno;
float valore,num;
tmp elementi;
char tito[MAX];
fscanf(fp,"%d",&n_tit);
while(n_tit>0){
    fscanf(fp,"%s %d",tito,&n_dati);
    TMPinit(&elementi);
    for(int i=0;i<n_dati;i++){
        fscanf(fp,"%d/%d/%d %d:%d %f %f",&anno,&mese,&giorno,&ora,&minuti,&valore,&num);
        lettura(&elementi,anno,mese,giorno,valore,num);
    }
    lista=inserimento_lista(elementi,lista,tito);
    TMPfree(&elementi);
    n_tit--;
}
return lista;
}

static void TMPinit(tmp *elementi){
    elementi->cap=0;
    elementi->n_ele=0;
    elementi->date=malloc(sizeof(data)*1);
    elementi->quot=malloc(sizeof(dati)*1);
    elementi->quot->den=0;
    elementi->quot->num=0;
    return;
}

static void lettura(tmp *elementi,int anno,int mese,int giorno,float valore,float num){
    if(elementi->cap==0){
        elementi->date->anno=anno;
        elementi->date->mese=mese;
        elementi->date->giorno=giorno;
        elementi->cap++;
        elementi->n_ele++;
        elementi->quot->den=num;
        elementi->quot->num=valore*num;
    }
    else{
        for(int i=0;i<elementi->n_ele;i++){
            if(elementi->date[i].anno==anno)
                if(elementi->date[i].mese==mese)
                  if(elementi->date[i].giorno==giorno){
                       elementi->quot[i].num+=valore*num;
                       elementi->quot[i].den+=num;
                       return;
                  }
        }
        if(elementi->n_ele==elementi->cap){
           elementi->cap=elementi->cap*2;
           elementi->date=realloc(elementi->date,sizeof(data)*elementi->cap);
           elementi->quot=realloc(elementi->quot,sizeof(dati)*elementi->cap);
           for(int i=elementi->cap/2;i<elementi->cap;i++){
                elementi->quot[i].den=0;
                elementi->quot[i].num=0;
           }
        }
        elementi->date[elementi->n_ele].anno=anno;
        elementi->date[elementi->n_ele].mese=mese;
        elementi->date[elementi->n_ele].giorno=giorno;
        elementi->quot[elementi->n_ele].den=num;
        elementi->quot[elementi->n_ele].num=valore*num;
        elementi->n_ele++;
    }
}
static link inserimento_lista(tmp elementi,link lista,char *tito){
int flag=0;
if(lista==NULL)
    lista=NEW(tito);
for(link x=lista;x!=NULL;x=x->next){
   if(strcmp(x->titol->nome,tito)==0){
       for(int i=0;i<elementi.n_ele;i++)
           x->titol->root=BSTinsert(x->titol->root,x->titol->z,elementi.date[i].anno,elementi.date[i].mese,elementi.date[i].giorno,elementi.quot[i].num,elementi.quot[i].den,&flag);
       return lista;
      }
   if(x->next==NULL){
      x->next=NEW(tito);
      for(int i=0;i<elementi.n_ele;i++)
          x->next->titol->root=BSTinsert(x->next->titol->root,x->next->titol->z,elementi.date[i].anno,elementi.date[i].mese,elementi.date[i].giorno,elementi.quot[i].num,elementi.quot[i].den,&flag);
      return lista;
      }
   }
   return lista;
}

static link NEW(char *tito){
link x;
x=malloc(sizeof(*x));
x->next=NULL;
x->titol=malloc(sizeof(struct titolo));
strcpy(x->titol->nome,tito);
x->titol->z=NEWBST(0,0,0,0,0,NULL,NULL,0);
x->titol->root=x->titol->z;
return x;
}

static void TMPfree(tmp *elementi){
elementi->cap=0;
elementi->n_ele=0;
free(elementi->date);
free(elementi->quot);
return;
}

link SEARCHtitolo(char *titolo,link lista){
if(lista==NULL)
        return NULL;
for(link x=lista;x!=NULL;x=x->next)
    if(strcmp(x->titol->nome,titolo)==0)
       return x;
return NULL;
}

void printbyDATE(link temp){
int anno,anno1,mese,mese1,giorno,giorno1;
float min,max;
printf("Inserire data1 aaaa/mm/gg: ");
scanf("%d %d %d",&anno,&mese,&giorno);
printf("Inserire data2 aaaa/mm/gg: ");
scanf("%d %d %d",&anno1,&mese1,&giorno1);
min=-1;
max=-1;
BSTprint_max_minDATE(temp->titol->root,anno,mese,giorno,anno1,mese1,giorno1,temp->titol->z,&min,&max);
printf("Quotazione minima: %.3f\n",min);
printf("Quotazione massima: %.3f\n",max);
return;
}

void printALLT(link temp){
BSTwrap(temp->titol->root,temp->titol->z);
}

void BSTprintQUOTwrapp(link temp,int anno,int mese,int giorno){
BSTprintQUOT(temp->titol->root,anno,mese,giorno,temp->titol->z);
}
void LENGHTminmaxWrapp(link temp,int n){
int cont=1;
float lmax=-1,lmin=1;
LENGHTminmax(temp->titol->root,&lmin,&lmax,temp->titol->z,cont);
if(n<(lmax/lmin)){
printf("Radice iniziale: \n");
BSTprintROOT(temp->titol->root);
temp->titol->root=PartRwrapp(temp->titol->root);
printf("Radice finale: \n");
BSTprintROOT(temp->titol->root);
}
}

void freedati(link lista){
link t;
for(link x=lista;x->next!=NULL;){
    t=x;
    x=x->next;
    freeBST(t->titol->root,t->titol->z);
    free(t->titol);
    free(t);
}
}
