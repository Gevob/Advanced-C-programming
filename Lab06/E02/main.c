#include <stdio.h>
#include <stdlib.h>
int lettura_file(int *nr,int *nc);
void separa(int **mat, int nr, int nc,int **bianc,int **ner,int *cont_neri,int *cont_bianchi);
int main()
{
int **mat,nr,nc,*bianc,*ner,cont_neri=0,cont_bianchi=0;
mat=lettura_file(&nr,&nc);
separa(mat,nr,nc,&bianc,&ner,&cont_neri,&cont_bianchi);
printf("NERI\n");
for(int i=0;i<cont_neri;i++)
    printf("%d ",ner[i]);
printf("\n");
printf("BIANCHI\n");
for(int i=0;i<cont_bianchi;i++)//free
    printf("%d ",bianc[i]);
for(int i=0;i<nr;i++)
free(mat[i]);
free(mat);
free(bianc);
free(ner);
system("PAUSE");
return 0;
}

int lettura_file(int *nr,int *nc){
FILE *fp;
int **mat;
int n_righe,n_colonne;
fp=fopen("mat.txt","r");
if(fp==NULL)
{
    printf("Errore apertura file\n");
    exit(EXIT_FAILURE);
}
fscanf(fp,"%d%d",&n_righe,&n_colonne);
mat=(int **)malloc(n_righe*sizeof(int *));
for(int i=0;i<n_righe;i++){
    mat[i]=(int *)malloc(n_colonne*sizeof(int));
    for(int j=0;j<n_colonne;j++){
    fscanf(fp,"%d",&mat[i][j]);
    }
}
*nc=n_colonne;
*nr=n_righe;
close(fp);
return mat;
}

void separa(int **mat, int nr, int nc,int **bianc,int **ner,int *cont_neri,int *cont_bianchi){
int flag=0,primo_colore=0,*bianchi,*neri,n_neri=1,n_bianchi=1;//0 corrisponde idealmente al nero, prima cella in alto a sinistra
bianchi=malloc(sizeof(int));
neri=malloc(sizeof(int));
for(int i=0;i<nr;i++){

    for(int j=0;j<nc;j++){//copia in maniera alternata prima nei vettori bianchi e poi in quello neri, la prima volta inizio dai neri
     if(flag==0){
        neri[(*cont_neri)++]=mat[i][j];
        flag=1;
        if(*cont_neri==n_neri){
        n_neri=2*n_neri;//se il vettore dei neri si riempi, lo rialloco con un vettore pari al doppio della lunghezza precedcente, lo stesso per i bianchi
        neri=realloc(neri,n_neri*sizeof(int));
        }
     }
     else{
        bianchi[(*cont_bianchi)++]=mat[i][j];
        flag=0;
        if(*cont_bianchi==n_bianchi){
        n_bianchi=2*n_bianchi;
        bianchi=realloc(bianchi,n_bianchi*sizeof(int));
        }

     }
    }
    if(primo_colore==0){//a fine riga controllo se l'indice di inizio della stessa è nero allora il flag sulla riga successiva sarà inizializzato al colore opposto e si aggionra anche "primo colore" per quella riga
        primo_colore=1;
        flag=1;
    }
    else{
        flag=0;
        primo_colore=0;
    }
}
*ner=neri;
*bianc=bianchi;
return;
}

