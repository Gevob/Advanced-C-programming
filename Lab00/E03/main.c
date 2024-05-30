#include <stdio.h>
#include <stdlib.h>
#define maxN 30
void ruota(int v[maxN], int N, int P, int dir);
int main()
{
    int vet[maxN],P,N,dir,flag=0;
    while(flag==0)
    {
        printf("Inserire il numero di elementi del vettore \n");
        scanf("%d",&N);
        if(N>maxN)
            {
            printf("Non va bene\n");
            }
            else
            {
                flag=1;
            }
    }
    flag=0;
    printf("Valori\n");
    for (int i=0;i<N;i++)
    {
    printf("%d) ",i+1);
    scanf("%d",&vet[i]);
    printf("\n");
    }
    printf("Inserire il numero di spostamenti con P<N,0 per terminare \n");
    scanf("%d",&P);
    while(P!=0)
    {
        printf("Inserire la direzione\n-1 per andare verso destra\n1 per andare verso sinistra\n");
        scanf("%d",&dir);
        if(dir!=-1&&dir!=1)
        {
            printf("Valore non supportato\n");
        }
        else
        {
            ruota(vet, N,P,dir);//sottoprogramma.
        }
        while(flag==0)
        {
            printf("Inserire il numero di spostamenti con P<N,0 per terminare \n");
            scanf("%d",&P);
            if(P>=N)
            {
            printf("Non va bene\n");
            }
            else
            {
                flag=1;
            }
        }
        flag=0;
    }
    system ("Pause");
    return 0;
}
void ruota(int v[maxN], int N, int P, int dir)
{
    int passaggio;
  for (int i=0;i<P;i++)
  {
      if(dir==1)//sinistra
    {
       passaggio=v[0];
       for(int j=0;j<N-1;j++)
      {
       v[j]=v[j+1];
      }
       v[N-1]=passaggio;
    }
   else
       {
           passaggio=v[N-1];
           for(int j=N-1;j>0;j--)
          {
          v[j]=v[j-1];
          }
           v[0]=passaggio;
       }
  }
  for(int j=0;j<N;j++)
    {
        printf("%d ",v[j]);
    }
    printf("\n");

}
