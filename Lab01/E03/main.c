#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 30

void acquisizione(int mat[][N],int dim[]);
void riga( char direzione[], int indice, int posti,int dim[], int mat[][N]);
void colonna(char direzione[], int indice, int posti,int dim[], int mat[][N]);
void rappresentazione_matrice(int dim[], int mat[][N]);

int main()
{
int mat[N][N],dim[2],indice,posizioni,flag=0;
char istruzioni[101],selettore[8],direzione[9];
acquisizione (mat,dim);
while(flag==0)
{
printf("Inserire <selettore> <indice> <direzione> <posizioni>\n");
gets(istruzioni);
sscanf(istruzioni,"%s %d %s %d",selettore,&indice,direzione,&posizioni);
if(strcmp(selettore,"riga")!=0&&strcmp(selettore,"colonna")!=0&&strcmp(selettore,"fine")!=0)
{
    printf("Errore inserimento selettore\n");
}
else if(strcmp(selettore,"fine")==0)
{
    flag=1;
}
else
{
    if(strcmp(selettore,"riga")==0)
    {
        if(indice>dim[0]||indice<0)
            printf("Errore inserimento indice\n");
        else if(strcmp(direzione,"sinistra")!=0&&strcmp(direzione,"destra")!=0)
            printf("Errore inserimento direzione\n");
        else if(posizioni>dim[1])
            printf("Errore inserimento posizioni\n");
        else
        {
            riga(direzione,indice,posizioni,dim,mat);
        }
    }
    else
    {
      if(indice>dim[1]||indice<0)
            printf("Errore inserimento indice\n");
        else if(strcmp(direzione,"su")!=0&&strcmp(direzione,"giu")!=0)
            printf("Errore inserimento direzione\n");
        else if(posizioni>dim[0])
            printf("Errore inserimento posizioni\n");
        else
        {
            colonna(direzione,indice, posizioni,dim,mat);
        }
    }
}

}
system ("PAUSE");
return 0;
}




void acquisizione(int mat[][N],int dim[])//acquisisco la matrice
{
    FILE *fp;
    fp=fopen("mat.txt","r");
    if(fp==NULL)
    {
        printf("Errore apertura file\n");
        return 1;
    }
    fscanf(fp,"%d%d",&dim[0],&dim[1]);
    for(int i=0;i<dim[0];i++)
    {
        for(int j=0;j<dim[1];j++)
        {
            fscanf(fp,"%d",&mat[i][j]);
            printf("%d\t",mat[i][j]);
        }
        printf("\n");
    }

}



void riga( char direzione[], int indice, int posti,int dim[], int mat[][N] )
{
  int passaggio;//variabile che assegna all'ultimo valore, quello del primo
  for (int i=0;i<posti;i++)
  {
    if(strcmp(direzione,"sinistra")==0)
    {
       passaggio=mat[indice-1][0];
       for(int j=0;j<dim[1]-1;j++)
      {
       mat[indice-1][j]=mat[indice-1][j+1];
      }
       mat[indice-1][dim[1]-1]=passaggio;
    }
   else
       {
          passaggio=mat[indice-1][dim[1]-1];
            for(int j=dim[1]-1;j>0;j--)
          {
          mat[indice-1][j]=mat[indice-1][j-1];
          }
           mat[indice-1][0]=passaggio;
       }
}
rappresentazione_matrice(dim,mat);
}



void colonna(char direzione[], int indice, int posti,int dim[], int mat[][N])
{
    int passaggio;
    for (int i=0;i<posti;i++)
    {
        if(strcmp(direzione,"su")==0)
        {
            passaggio=mat[0][indice-1];
            for(int j=0;j<dim[0]-1;j++)
            {
                mat[j][indice-1]=mat[j+1][indice-1];
            }
            mat[dim[0]-1][indice-1]=passaggio;
        }
        else
        {
          passaggio=mat[dim[0]-1][indice-1];
            for(int j=dim[0]-1;j>0;j--)
            {
                mat[j][indice-1]=mat[j-1][indice-1];
            }
            mat[0][indice-1]=passaggio;
        }
    }
    rappresentazione_matrice(dim,mat);
}

void rappresentazione_matrice(int dim[], int mat[][N])
{
    for(int i=0;i<dim[0];i++)
    {
        for(int j=0;j<dim[1];j++)
        {
            printf("%d\t",mat[i][j]);
        }
        printf("\n");
    }
}
