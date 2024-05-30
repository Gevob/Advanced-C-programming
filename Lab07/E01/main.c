#include <stdio.h>
#include <stdlib.h>
typedef struct{
int a,b;
}punti;
punti *acquisizione_file(int *nv,int *na);//acquisisco gli archi
int powerset(int *vet,int *sol,int *mark,int pos,int n_vertici,int start,int count,int sol_min,punti *archi,int n_archi);
int check_sol(int *sol,int *mark,punti *archi,int pos,int n_archi,int n_vertici);
int main()
{
    int n_vertici,n_archi,*vet,*sol,mark,n_sol,sol_min=2,start=0,count=0,pos=0;
    punti *archi;
    archi=acquisizione_file(&n_vertici,&n_archi);
    vet=malloc(sizeof(int)*n_vertici);
    sol=malloc(sizeof(int)*n_vertici);
    mark=malloc(sizeof(int)*n_vertici);
    for(int i=0;i<n_vertici;i++)
        vet[i]=i;
    n_sol=powerset(vet,sol,mark,pos,n_vertici,start,count,sol_min,archi,n_archi);
    return 0;
}
punti *acquisizione_file(int *nv,int *na){
FILE *fp;
punti *archi;
int n_vertici,n_archi,vertice_a,vertice_b;
fp=fopen("grafo.txt","r");
if(fp==NULL){
    printf("Errore apertura file\n");
    exit(EXIT_FAILURE);
}
fscanf(fp,"%d%d",&n_vertici,&n_archi);
archi=(punti *)malloc(sizeof(punti)*n_archi);
for(int i=0;i<n_archi;i++){
    fscanf(fp,"%d%d",&vertice_a,&vertice_b);
    archi[i].a=vertice_a;
    archi[i].b=vertice_b;
}
*nv=n_vertici;
*na=n_archi;
fclose(fp);
return archi;
}
int powerset(int *vet,int *sol,int *mark,int pos,int n_vertici,int start,int count,int sol_min,punti *archi,int n_archi){
int i;
if(pos>=n_vertici){//soluzione minina, 1 arco, cioè 2 vertici
    if(check_sol(sol,mark,archi,pos,n_archi,n_vertici)==1){
       count++;
       printf("Sol n %d\n",count);
       for(int i=0;i<n_vertici;i++)
          if(sol[i]==1)
            printf("%d",i);
       printf("\n");
    }
    return count;
}
    sol[pos]=0;//genero un powerset con tutti i casi possibili
    count=powerset(vet,sol,mark,pos+1,n_vertici,start+1,count,sol_min,archi,n_archi);
    sol[pos]=1;
    count=powerset(vet,sol,mark,pos+1,n_vertici,start+1,count,sol_min,archi,n_archi);

return count;
}
int check_sol(int *sol,int *mark,punti *archi,int pos,int n_archi,int n_vertici){//controllo che nell'insieme trovato almeno un vertice per ogni arco sia presente
int cont_a,cont_b,cont=0;
for(int i=0;i<n_archi;i++){
        cont_a=cont_b=cont=0;
    for(int j=0;j<n_vertici;j++){
        if(sol[j]==1){
            cont++;
            if(archi[i].a!=j)
            cont_a++;
            if(archi[i].b!=j)
            cont_b++;
        }
    }
if(cont_a+cont_b>=2*cont||cont<2)//conto quando il vertice non compare, se la loro somma è minore del doppio del numero totale allora il vertice non è presente. Considero il caso in cui nel powerset è preso 1 elemento
    return 0;
}
return 1;
}
