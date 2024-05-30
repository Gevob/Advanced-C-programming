#include <stdio.h>
#include <stdlib.h>
#define maxN 20
 int letturafile(int dim[2],int mat[maxN][maxN]);
 void algoritmo(int n, int dim[],int mat[maxN][maxN]);
 int main()
{
 int lett=0,dim[2],mat[maxN][maxN],n=0;
 lett=letturafile(dim,mat);
 if(!lett)
    printf("Errore apertura file\n");
 printf("Inserire valore n compreso tra 0 e il min tra nc e nr\n");
 scanf("%d",&n);
 while((n<=dim[0]&&dim[0]<=dim[1])||(n<=dim[1]&&dim[1]<=dim[0]))
 {
     algoritmo(n,dim,mat);
     printf("Inserire valore n compreso tra 0 e il min tra nc e nr\n");
     scanf("%d",&n);
 }

 system("PAUSE");
 return 0;
}

int letturafile(int dim[2],int mat[maxN][maxN])
{
    int lett=1,i=0,j=0;
    char file[maxN];
    FILE *fp;
    printf("Inserire nome file\n");
    gets(file);
    fp=fopen(file,"r");
    if(fp==NULL)
    lett=0;
    else
    {
        fscanf(fp,"%d",&dim[0]);
        printf("%d\n",dim[0]);
        fscanf(fp,"%d",&dim[1]);
        printf("%d\n",dim[1]);

        for(i=0;i<dim[0];i++)
    {
        for(j=0;j<dim[1];j++)
        {
            fscanf(fp,"%d",&mat[i][j]);
            printf("%d\t",mat[i][j]);
        }

        printf("\n");
    }
    }
    return lett;
}

void algoritmo(int n, int dim[2], int mat[maxN][maxN])
{
    int IndDim[4],s=0,x,y,max;
    max=-100000000000;
    for(int i=0;i<dim[0]&&i<=dim[0]-n;i++)
    {
        for(int j=0;j<dim[1]&&j<=dim[1]-n;j++)
        {
          for(y=i;y<i+n;y++)
          {
            for(x=j;x<j+n;x++)
            {
                printf("%d\t",mat[y][x]);
                s=s+mat[y][x];
            }
            printf("\n");
          }
          printf("-------\n");
          if(s>max)
          {
            IndDim[0]=i;//y0
            IndDim[1]=j;//xo
            IndDim[2]=i+n-1;//yf
            IndDim[3]=j+n-1;//xf
            max=s;
          }
          s=0;
        }
    }
 printf("Matrice la somma di cui elementi è massima\n");
 for(int i=IndDim[0];i<=IndDim[2];i++)
 {
     for(int j=IndDim[1];j<=IndDim[3];j++)
     {
         printf("%d\t",mat[i][j]);
     }
     printf("\n");
 }
}

