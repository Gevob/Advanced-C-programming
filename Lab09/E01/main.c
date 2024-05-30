#include <stdio.h>
#include <stdlib.h>
typedef struct{
int s,f;
}elenco;
elenco *acquisizione_file(int *n);
void attSel(int N, elenco *v);
void casi(int n,elenco *v,elenco **sol,int *mark,int pos,int *d,int somma,int indice,int previous,int *n_finale,elenco **sol_finale);
int check(elenco **sol,int indice,int pos);
int main()
{
    int n_att;
    elenco *attivita;
    attivita=acquisizione_file(&n_att);
    attSel(n_att,attivita);
    return 0;
}
elenco *acquisizione_file(int *n){
int n_att,s,f;
elenco *attivita;
FILE *fp;
fp=fopen("att.txt","r");
if(fp==NULL){
    printf("Errore apertura file\n");
    exit(EXIT_FAILURE);
}
fscanf(fp,"%d",&n_att);
attivita=(elenco *)malloc(n_att*sizeof(elenco));
for(int i=0;i<n_att;i++){
fscanf(fp,"%d%d",&s,&f);
attivita[i].s=s;
attivita[i].f=f;
}
fclose(fp);
*n=n_att;
return attivita;
}
void attSel(int N, elenco *v){
int *mark,pos=0,d=0,somma=0,indice=0,previous=0,n_finale;
elenco **sol,**sol_finale;
mark=malloc(N*sizeof(int));
sol=(elenco **)malloc(N*sizeof(elenco *));
sol_finale=(elenco **)malloc(N*sizeof(elenco *));
for(int i=0;i<N;i++)
{
    mark[i]=1;
}
casi(N,v,sol,mark,pos,&d,somma,indice,previous,&n_finale,sol_finale);
//free
for(int i=0;i<n_finale;i++)
    printf("(%d,%d)",sol_finale[i]->s,sol_finale[i]->f);
}
void casi(int n,elenco *v,elenco **sol,int *mark,int pos,int *d,int somma,int indice,int previous,int *n_finale,elenco **sol_finale){
if(somma>*d){
*d=somma;
for(int j=0;j<pos;j++)
    sol_finale[j]=sol[j];
*n_finale=pos;
}
for(int i=0;i<n;i++){
if(mark[i]==1&&i>=indice){
    mark[i]=0;
    sol[pos]=&v[i];
    somma+=(sol[pos]->f-sol[pos]->s);
    previous=indice;
    indice=i;
    if(check(sol,i,pos)==1){
            casi(n,v,sol,mark,pos+1,d,somma,indice,previous,n_finale,sol_finale);
     }
    mark[i]=1;
    somma-=(sol[pos]->f-sol[pos]->s);
    sol[pos]=NULL;
    indice=previous;
  }
}
return;
}

int check(elenco **sol,int indice,int pos){
if(pos==0)//caso con una sola attività
    return 1;
if(sol[pos-1]->s<sol[pos]->f&&sol[pos]->s<sol[pos-1]->f)
    return 0;
return 1;
}
