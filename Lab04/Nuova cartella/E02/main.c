#include <stdio.h>
#include <stdlib.h>
#define N 10
int vettore(int *v,int *v_copia, int n, int n_valori_diversi);
int majority(int *a, int l, int r, int valore_corrente);
int main()
{
 int vet[N],vet_copia[N],n_valori_diversi=0,risultato;
 printf("Inserire elementi:");
 for(int i=0;i<N;i++){
 scanf("%d",&vet[i]);
 for(int j=0;j<n_valori_diversi||n_valori_diversi==0;j++){//per ottimizzare copio in un secondo vettore tutti gli elementi distinti
    if(vet_copia[j]==vet[i])
        break;
    else if(j==(n_valori_diversi-1)||n_valori_diversi==0){
    vet_copia[n_valori_diversi]=vet[i];
    n_valori_diversi++;
    }
 }
 }
 if((risultato=vettore(vet,vet_copia,N,n_valori_diversi))!=-1)
    printf("Valore trovato %d\n",risultato);
 return 0;
}
int majority(int *a, int l, int r, int valore_corrente){
    int m=(l+r)/2;//divido il vettore in 2 e osservo prima la sua metà di sinistra
    if(l==r){
        if(a[l]==valore_corrente)//il valore del vettore unitario corrisponde al valore cercato
            return 1;
        else
            return 0;
    }
    return majority(a,l,m,valore_corrente)+majority(a,m+1,r,valore_corrente);

}

int vettore(int *v,int *v_copia, int n, int n_valori_diversi)
{
  int risultato;
  int l=0,r=n-1;//indice di sinistra e destra
  for(int i=0;i<n_valori_diversi;i++){
        risultato=majority(v,l,r,v_copia[i]);
        if(risultato>n/2)
                return v_copia[i];//torna il valore dei vettori distinti
}
return -1;
}
