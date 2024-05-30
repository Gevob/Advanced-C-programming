#include <stdio.h>
#include <stdlib.h>
#define N 7
void acquisizione_vet(int *vett);
int majority(int *vett,int l,int r);
int main()
{
    int vett[N],magg,l=0,r=N-1;
    acquisizione_vet(vett);
    magg=majority(vett,l,r);
    if(magg==-1)
      printf("Maggioritario non presente\n");
    else
      printf("Maggioritario %d",magg);
    return 0;
}
void acquisizione_vet(int *vett)
{
    printf("Inserire elementi del vettore: ");
    for(int i=0;i<N;i++)
        scanf("%d",&vett[i]);
}
int majority(int *vett,int l,int r)//cerco il maggioritario in ogni sottovettore
{
    int m,u,v,cont_u=0,cont_v=0,n;
    n=(r-l)+1;//lunghezza del vettore corrente
    m=(l+r)/2;
    if(l==r)
        return vett[l];
    u=majority(vett,l,m);
    v=majority(vett,m+1,r);
    if(u==v)
        return u;//se il maggioritario del sottovettore di sinistra è uguale a quello di destra, ritorna il numero
    for(int i=l;i<=r;i++){//altrimenti con un ciclo for conto le occorrenze dei singoli valori
    if(u!=-1&&u==vett[i])
        cont_u++;
    if(v!=-1&&v==vett[i])
        cont_v++;
    }
    if(cont_u>n/2)
        return u;
    if(cont_v>n/2)
        return v;
    return -1;//-1 nel caso in cui il maggioritario non ci sia
}
