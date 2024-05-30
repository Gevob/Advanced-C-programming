#include <stdio.h>
#include <stdlib.h>
typedef struct{
int a,b;}successivo;
void casi_possibili(int *k, int n, int pos,int *pietre,int *mark,int *sol,successivo *adiacente,int *soluzione,int *n_finale,int *val,int val_tot,int *val_finale,int rip,int rip_tmp,int max_rip,int n_za,int n_sm);
int check_sol(int *sol,int pos,successivo *adiacente);
int main()
{
    int pos=0,n=4,mark[4],pietre[4],*sol,*soluzione,k,n_finale=0,val[4],val_tot=0,val_finale=0,rip=0,max_rip,rip_tmp=0,n_za=0,n_sm=0;
    char *collana;
    successivo adiacente[4];
    adiacente[0].a=1;//il successivo del rubino è  smeraldo o topazio
    adiacente[0].b=2;
    adiacente[1].a=1;//il successivo dello smeraldo è  smeraldo o topazio
    adiacente[1].b=2;
    adiacente[2].a=3;//il successivo del topazio è zaffiro o rubino
    adiacente[2].b=0;
    adiacente[3].a=3;//il successivo dello zaffiro è zaffiro o rubino
    adiacente[3].b=0;
    printf("Inserire numero di zaffiri e il loro valore: ");
    scanf("%d%d",&mark[3],&val[3]);
    printf("Inserire numero di topazi e il loro valore: ");
    scanf("%d%d",&mark[2],&val[2]);
    printf("Inserire numero di rubini e il loro valore: ");
    scanf("%d%d",&mark[0],&val[0]);
    printf("Inserire numero di smeraldi e il loro valore: ");
    scanf("%d%d",&mark[1],&val[1]);
    printf("Inserire max ripetizioni: ");
    scanf("%d",&max_rip);
    k=mark[0]+mark[1]+mark[2]+mark[3];
    sol=malloc(k*sizeof(int));//creo un vettore delle soluzioni di lunghezza massima pari a k
    soluzione=malloc(k*sizeof(int));//ha la stessa lunghezza del vettore delle soluzioni, in questo è ricopiata la collana della soluzione
    k=0;
    for(int i=0;i<4;i++)//riempo il vettore delle pietre con valori da 0 a n-1, ogni valore corrisponde a una pietra;
        pietre[i]=i;
    casi_possibili(&k,n,pos,pietre,mark,sol,adiacente,soluzione,&n_finale,val,val_tot,&val_finale,rip,rip_tmp,max_rip,n_za,n_sm);
    printf("La collana e' lunga %d e ha un valore pari a %d\n",n_finale,val_finale);
    collana=malloc(n_finale*sizeof(char));
    for(int i=0;i<n_finale;i++){
    switch(soluzione[i]){
    case 0:
           collana[i]='R';
           printf("%c",collana[i]);
           break;
    case 1:
           collana[i]='S';
           printf("%c",collana[i]);
           break;
    case 2:
           collana[i]='T';
           printf("%c",collana[i]);
           break;
    case 3:
           collana[i]='Z';
           printf("%c",collana[i]);
           break;
    }
    }


    return 0;
}

void casi_possibili(int *k, int n, int pos,int *pietre,int *mark,int *sol,successivo *adiacente,int *soluzione,int *n_finale,int *val,int val_tot,int *val_finale,int rip,int rip_tmp,int max_rip,int n_za,int n_sm){//genero tutti i casi possibili
if(pos>*k){//ogni volta che chiamo una nuova istanza aggiorno il vettore delle soluzioni e la lunghezza massima
        if(val_tot>=*val_finale){
           *k=pos;
            for(int i=0;i<pos;i++)
               soluzione[i]=sol[i];
           *n_finale=pos;
           *val_finale=val_tot;
        }
}//0 rubini, 1 smeraldi 2 topazi 3 zaffiri
for(int i=0;i<n;i++){
    if(mark[i]>0){
        mark[i]--;
        sol[pos]=pietre[i];
        val_tot+=val[i];
        if(sol[pos]==sol[pos-1]||pos==0){
            rip_tmp=rip;
            rip++;
        }
        else{
            rip_tmp=rip;
            rip=1;
            }
        if(sol[pos]==3)
          n_za++;
        if(sol[pos]==1)
          n_sm++;
        if(n_za<=n_sm){
        if(check_sol(sol,pos,adiacente)==1&&rip<=max_rip){//pruning controllo che le pietre, man mano che vengono prese, possano formare una collana contigua
        casi_possibili(k,n,pos+1,pietre,mark,sol,adiacente,soluzione,n_finale,val,val_tot,val_finale,rip,rip_tmp,max_rip,n_za,n_sm);
        }
        }
        rip=rip_tmp;
        val_tot-=val[i];
        mark[i]++;
        if(pos==0)
            rip=0;
        if(sol[pos]==3)
          n_za--;
        if(sol[pos]==1)
          n_sm--;

    }
}

}

int check_sol(int *sol,int pos,successivo *adiacente){
if(pos!=0){
if(sol[pos]==adiacente[sol[pos-1]].a||sol[pos]==adiacente[sol[pos-1]].b)
   return 1;
 return 0;
}
return 1;
}



