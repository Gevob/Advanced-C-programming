#include <stdio.h>
#include <stdlib.h>
#define N 20
#define M 20

void acquisizione(int dim[], int mat[][M]);
void calcolo_giornate(int dim[],int mat[][M]);

int main()
{
    int dim[2],mat[N][M],s[N];
    acquisizione(dim,mat);
    calcolo_giornate(dim,mat);
    system ("PAUSE");
    return 0;
}

void acquisizione(int dim[], int mat[][M])
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

void calcolo_giornate(int dim[],int mat[][M])
{
    int punti_squadre[N]={0},s=0,max,indice_squadra,x;
    for(int j=0;j<dim[1];j++)//giornate
    {
    for(int i=0;i<dim[0];i++)
    {
        punti_squadre[s]=punti_squadre[s]+mat[i][j];//attribuisco i punti di ogni giornata alle squadre
        s++;
    }
    s=0;
    max=punti_squadre[0];
    for(x=0;x<dim[0];x++)
    {
        if(punti_squadre[x]>max)
        {
            max=punti_squadre[x];
            indice_squadra=x;//indice della squadra con punteggio massimo

        }
    }
    printf("La squadra prima in classifica alla %d giornate e\' la %d\n",j+1,indice_squadra+1);
    }

}
