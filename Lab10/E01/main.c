#include <stdio.h>
#include <stdlib.h>
#define MAX 50
typedef struct dati *att;
struct dati{
int i,f;
};
att acquisizione_file(int *n,char *nome);
void ordinamento(att attivita,int n);
void sol(int *p,int *l,int n,att attivita);
void s_print(int *p,int *l,int n,att attivita);
int compatibilita(int i,int j,att attivita);
int main()
{
    int n,*p,*l;
    char nome[MAX];
    att attivita;
    printf("Inserire nome file: \n");
    scanf("%s",nome);
    attivita=acquisizione_file(&n,nome);
    ordinamento(attivita,n);
    l=malloc(n*sizeof(int));
    if(l==NULL){
        printf("Errore malloc\n");
        exit(EXIT_FAILURE);
    }
    p=malloc(n*sizeof(int));
    if(p==NULL){
        printf("Errore malloc\n");
        exit(EXIT_FAILURE);
    }
    sol(p,l,n,attivita);
    free(l);
    free(p);
    free(attivita);
    return 0;
}
att acquisizione_file(int *n,char *nome){
FILE *f;
int righe;
att attivita;
f=fopen(nome,"r");
if(f==NULL){
    printf("Errore apertura file\n");
    exit(EXIT_FAILURE);
}
fscanf(f,"%d",&righe);
attivita=malloc(righe*sizeof(struct dati));
if (attivita==NULL){
        printf("Errore malloc\n");
        exit(EXIT_FAILURE);
    }
if(attivita==NULL){
    printf("Errore malloc\n");
    exit(EXIT_FAILURE);
}
for(int i=0;i<righe;i++)
    fscanf(f,"%d %d",&attivita[i].i,&attivita[i].f);
*n=righe;
close(f);
return attivita;
}
void ordinamento(att attivita,int n){
struct dati temp;
for(int i=0;i<n-1;i++){
    for(int j=0;j<n-1-i;j++)
    if(attivita[j].i>attivita[j+1].i){
    temp=attivita[j+1];
    attivita[j+1]=attivita[j];
    attivita[j]=temp;
    }
}
return ;
}
void sol(int *p,int *l,int n,att attivita){
int flag,max=0,pos=-1;
l[0]=attivita[0].f-attivita[0].i;
p[0]=-1;
for(int i=1;i<n;i++){
l[i]=attivita[i].f-attivita[i].i;
p[i]=-1;
flag=0;
for(int j=0;j<i;j++)
    if(compatibilita(i,j,attivita)==1){
        if(flag==0){
            flag=1;
            max=l[j];
            pos=j;
        }
        if(l[j]>max){
            max=l[j];
            pos=j;
        }
    }
l[i]=max+l[i];
p[i]=pos;
}
printf("Miglior insieme possibile\n");
s_print(p,l,n,attivita);
return;
}

int compatibilita(int i,int j,att attivita){
if(attivita[j].i<attivita[i].f&&attivita[i].i<attivita[j].f)
    return 0;
return 1;
}

void s_print(int *p,int *l,int n,att attivita){
int max=0,indice;
for(int i=0;i<n;i++)//trovo il valore dell'insieme massimo
    if(l[i]>max){
       max=l[i];
       indice=i;
    }
printf("Valore massimo %d\n",max);
while(indice!=-1){
    printf("(%d,%d)",attivita[indice].i,attivita[indice].f);
    indice=p[indice];
}
return;
}

void free_dati(int *p,int *l,att attivita);
