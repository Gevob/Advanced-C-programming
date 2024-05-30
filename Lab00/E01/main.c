#include <stdio.h>
#include <stdlib.h>
#define N 10

int main()
{
    int vet[N],vet2[N],cont=0,max=0,i=0,flag=0;
    for (int i=0;i<=N-1;i++)
    {
        printf("Inserire %d valore del vettore \n",i+1);
        scanf("%d",&vet[i]);
    }
    for (i=0;i<=N-1;i++)
    {
        if(vet[i]==0||i==N-1)
        {
            if(i==N-1)
            {
                cont++;
            }
            if(cont>max)
            {
                max=cont;
            }
            cont=0;
        }
        else
        {
            cont++;
        }
    }
    printf("%d max\n",max);
    cont=i=0;

        for(int j=0;j<=N-1&&flag==0;j++)
        {
        if(vet[i]!=0)
        {
            cont++;
            vet2[j]=vet[i];
        }
        if(vet[i]==0||i==N-1)
        {
            if(cont==max)
            {


            for(int y=0;y<max;y++)
            {
                printf("%d ",vet2[y]);
            }
            printf("\n");
            if (i!=N-1)
            {
            cont=0;
            j=-1;
            }
            else
            {
                flag=1;
            }

            }
            else
            {
              if (i!=N-1)
            {
            cont=0;
            j=-1;
            }
            else
            {
                flag=1;
            }
            }
        }//else
        i++;
        }

    return 0;
}
