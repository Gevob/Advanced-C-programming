#include <stdio.h>
#include <stdlib.h>
typedef struct{
int a,b;}successivo;
void casi_possibili(int *k, int n, int pos,int *pietre,int *mark,int *sol,successivo *adiacente,int *soluzione,int *n_finale);
int check_sol(int *sol,int pos,successivo *adiacente);
int main()
{
    int n_z,n_t,n_r,n_s,pos=0,n=4,mark[4],pietre[4],*sol,*soluzione,k,n_finale=0;
    successivo adiacente[4];
    adiacente[0].a=1;//il successivo del rubino è  smeraldo o topazio
    adiacente[0].b=2;
    adiacente[1].a=1;//il successivo dello smeraldo è  smeraldo o topazio
    adiacente[1].b=2;
    adiacente[2].a=3;//il successivo del topazio è zaffiro o rubino
    adiacente[2].b=0;
    adiacente[3].a=3;//il successivo dello zaffiro è zaffiro o rubino
    adiacente[3].b=0;
    printf("Inserire numero di zaffiri: ");
    scanf("%d",&n_z);
    mark[3]=n_z;
    printf("Inserire numero di topazi: ");
    scanf("%d",&n_t);
    mark[2]=n_t;
    printf("Inserire numero di rubini: ");
    scanf("%d",&n_r);
    mark[0]=n_r;
    printf("Inserire numero di smeraldi: ");
    scanf("%d",&n_s);
    mark[1]=n_s;
    k=n_z+n_t+n_s+n_r;
    sol=malloc(k*sizeof(int));//creo un vettore delle soluzioni di lunghezza massima pari a k
    soluzione=malloc(k*sizeof(int));//ha la stessa lunghezza del vettore delle soluzioni, in questo è ricopiata la collana della soluzione
    k=0;
    for(int i=0;i<4;i++)//riempo il vettore delle pietre con valori da 0 a n-1, ogni valore corrisponde a una pietra;
        pietre[i]=i;
    casi_possibili(&k,n,pos,pietre,mark,sol,adiacente,soluzione,&n_finale);
printf("La collana e' lunga %d\n",n_finale);
    for(int i=0;i<n_finale;i++)
        printf("%d",soluzione[i]);
    return 0;
}

void casi_possibili(int *k, int n, int pos,int *pietre,int *mark,int *sol,successivo *adiacente,int *soluzione,int *n_finale){//permutazioni ripetute
if(pos>*k){//ogni volta che chiamo una nuova istanza aggiorno il vettore delle soluzioni
    *k=pos;
    for(int i=0;i<pos;i++)
        soluzione[i]=sol[i];
    *n_finale=pos;
}//0 rubini, 1 smeraldi 2 topazi 3 zaffiri
for(int i=0;i<n;i++){
    if(mark[i]>0){
        mark[i]--;
        sol[pos]=pietre[i];
        if(check_sol(sol,pos,adiacente)==1){//pruning controllo che le pietre, man mano che vengono prese possano formare una collana contigua
        casi_possibili(k,n,pos+1,pietre,mark,sol,adiacente,soluzione,n_finale);
        }
        mark[i]++;
    }
}
return;
}

int check_sol(int *sol,int pos,successivo *adiacente){
if(pos!=0){
if(sol[pos]==adiacente[sol[pos-1]].a||sol[pos]==adiacente[sol[pos-1]].b)
   return 1;
 return 0;
}
return 1;
}


