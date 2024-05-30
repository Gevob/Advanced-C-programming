#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int cont;
typedef struct{
int num_scelte;//numero totale di canzoni per ogni amico
char **scelte;//vettore di puntatori alle singole canzoni
}livelli;
void casi_possibili(livelli *livello,char **soluzione,int livello_corrente, int n);
void dealloc(livelli *livello,char **soluzione,int n);
int main()
{
    int n_amici,posizione_corrente=0;
    livelli *livello;
    char **soluzione;
    FILE *fp;//apro il file e copio i dati in una struct
    fp=fopen("brani.txt","r");
    if(fp==NULL){
        printf("Errore apertura file\n");
        return 1;
    }
    fscanf(fp,"%d",&n_amici);
    livello=malloc(n_amici*sizeof(livelli));
    for(int i=0;i<n_amici;i++){
     fscanf(fp,"%d",&livello[i].num_scelte);
     livello[i].scelte=(char **)malloc(livello[i].num_scelte*sizeof(char *));//assegno il puntatore corrispondente al vettore di puntatori delle singole canzoni di ogni amico
     for(int j=0;j<livello[i].num_scelte;j++){
      livello[i].scelte[j]=malloc(255*sizeof(char));
      fscanf(fp,"%s",livello[i].scelte[j]);
     }
    }//ho copiato tutta la struct
    //costruisco la matrice con le soluzioni, n_amici*255
    soluzione=(char **)malloc(n_amici*sizeof(char *));
    for(int i=0;i<n_amici;i++)
        soluzione[i]=malloc(255*sizeof(char));
    casi_possibili(livello,soluzione,posizione_corrente,n_amici);
    dealloc(livello,soluzione,n_amici);
    close(fp);
    system("PAUSE");
    return 0;
}
void casi_possibili(livelli *livello,char **soluzione,int livello_corrente, int n){
    if(livello_corrente>n-1){//ho trovato una playlist
      cont++;
      printf("Playlist: %d\n",cont);
      for(int i=0;i<n;i++)
            printf("%s\n",soluzione[i]);
      printf("\n");
      return;
    }
    for(int i=0;i<livello[livello_corrente].num_scelte;i++){

            strcpy(soluzione[livello_corrente],(livello[livello_corrente].scelte[i]));
            casi_possibili(livello,soluzione,livello_corrente+1,n);
    }
     return;
}
void dealloc(livelli *livello,char **soluzione,int n){
for (int i=0;i<n;i++){//libero la struct
    for(int j=0;j<livello[i].num_scelte;j++){
        free(livello[i].scelte[j]);
    }
    free(livello[i].scelte);
}
free(livello);
for(int i=0;i<n;i++){//libero la matrice delle soluzioni
   free(soluzione[i]);
}
free(soluzione);
return;
}
