#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 30
#define MAX_RIGHE 1000
typedef struct{
char codice[N],partenza[N],arrivo[N],data[N],ora_partenza[N],ora_arrivo[N];
int ritardo;
}elenco;
typedef enum {stampa, ordina_data, ordina_codice, ordina_partenza, ordina_arrivo, ricerca_partenza, fine}comando;
typedef enum {schermo, file, errore}opzioni_stampa;
int acquisizione_file(elenco corse[],elenco **pdate,elenco **pcodice,elenco **ppartenza,elenco **parrivo);
comando lettura_comando();
opzioni_stampa output();
void esegui_comando(comando scelta, elenco corse[],elenco **pdate,elenco **pcodice,elenco **ppartenza,elenco **parrivo,int n_righe,int *flag,FILE *fp);
int ricerca_dicotomica(elenco **p,int l,int r,char ricerca[]);
int main()
{
    int n_corse,flag=0;
    comando scelta;
    elenco corse[MAX_RIGHE],*pdate[MAX_RIGHE],*pcodice[MAX_RIGHE],*ppartenza[MAX_RIGHE],*parrivo[MAX_RIGHE];
    FILE *fp2;
     fp2=fopen("risultati.txt","a");
     if(fp2==NULL){
        printf("Errore file 'risultati'\n");
        return 0;}
    n_corse=acquisizione_file(corse,pdate,pcodice,ppartenza,parrivo);
    do{
    scelta=lettura_comando();
    esegui_comando(scelta,corse,pdate,pcodice,ppartenza,parrivo,n_corse,&flag,fp2);
    }while(scelta<fine);
    close("fp2");
}
int acquisizione_file(elenco corse[],elenco **pdate,elenco **pcodice,elenco **ppartenza,elenco **parrivo){
    int n_righe;
    FILE *fp;
    fp=fopen("log.txt","r");
    if(fp==NULL){
        printf("Errore apertura file\n");
        exit(EXIT_FAILURE);
    }
    fscanf(fp,"%d",&n_righe);
    for(int i=0;i<n_righe;i++){
    fscanf(fp,"%s%s%s%s%s%s%d",corse[i].codice,corse[i].partenza,corse[i].arrivo,corse[i].data,corse[i].ora_partenza,corse[i].ora_arrivo,&corse[i].ritardo);
    pdate[i]=pcodice[i]=ppartenza[i]=parrivo[i]=&corse[i];
    }    close(fp);
    return n_righe;
}
 comando lettura_comando(){
 char opzione[N],comandi[fine+1][N]={"stampa","ordinaXdata","ordinaXcodice","ordinaXpartenza","ordinaXarrivo","ricerca_partenza","fine"};
 comando t;
 printf("Scrivere comando\n-stampa\n-ordinaX... ...=data codice partenza arrivo\n-per ricerca per stazione di partenza inserire <ricerca_partenza>\n-fine per terminare\n");
 scanf("%s",opzione);
 t=stampa;
 while(t<=fine&& strcmp(opzione,comandi[t])!=0)
    t++;
 return t;
 }

 void esegui_comando(comando scelta,elenco corse[],elenco **pdate,elenco **pcodice,elenco **ppartenza,elenco **parrivo,int n_righe,int *flag,FILE *fp){
     int l=0,r=n_righe-1,indice_inizio;
     opzioni_stampa opzione;
     char ricerca[N];
     elenco *tmp;
     switch(scelta)
     {
     case stampa://stampa a schermo i dati del log
        do{
        opzione=output();
        }while(opzione>errore);
        if(opzione==schermo){
        for(int i=0;i<n_righe;i++)
            printf("%s %s %s %s %s %s %d\n",pdate[i]->codice,pdate[i]->partenza,pdate[i]->arrivo,pdate[i]->data,pdate[i]->ora_partenza,pdate[i]->ora_arrivo,pdate[i]->ritardo);
        }
        else if (opzione==file){
        for(int i=0;i<n_righe;i++){
            fprintf(fp,"%s %s %s %s %s %s %d\n",pdate[i]->codice,pdate[i]->partenza,pdate[i]->arrivo,pdate[i]->data,pdate[i]->ora_partenza,pdate[i]->ora_arrivo,pdate[i]->ritardo);
        }
        }
        break;
     case ordina_data://ordine crescente per data
        for(int i=l;i<r;i++){
            for(int j=l;j<r-i+l;j++){
                if(strcmp(pdate[j]->data,pdate[j+1]->data)>0){
                    tmp=pdate[j];
                    pdate[j]=pdate[j+1];
                    pdate[j+1]=tmp;
                }
                if(strcmp(pdate[j]->data,pdate[j+1]->data)==0){
                    if(strcmp(pdate[j]->ora_partenza,pdate[j+1]->ora_partenza)>0){
                        tmp=pdate[j];
                        pdate[j]=pdate[j+1];
                        pdate[j+1]=tmp;
                    }
                }
            }
        }
        do{
        opzione=output();
        }while(opzione>errore);
        if(opzione==schermo){
        for(int i=0;i<n_righe;i++)
            printf("%s %s %s %s %s %s %d\n",pdate[i]->codice,pdate[i]->partenza,pdate[i]->arrivo,pdate[i]->data,pdate[i]->ora_partenza,pdate[i]->ora_arrivo,pdate[i]->ritardo);
        }
        else if (opzione==file){
        for(int i=0;i<n_righe;i++){
            fprintf(fp,"%s %s %s %s %s %s %d\n",pdate[i]->codice,pdate[i]->partenza,pdate[i]->arrivo,pdate[i]->data,pdate[i]->ora_partenza,pdate[i]->ora_arrivo,pdate[i]->ritardo);
        }
        }
        break;
     case ordina_codice://ordino per codice
        for(int i=l;i<r;i++){
            for(int j=l;j<r-i+l;j++){
                if(strcmp(pcodice[j]->codice,pcodice[j+1]->codice)>0){
                    tmp=pcodice[j];
                    pcodice[j]=pcodice[j+1];
                    pcodice[j+1]=tmp;
                }
            }
        }
        do{
        opzione=output();
        }while(opzione>errore);
        if(opzione==schermo){
        for(int i=0;i<n_righe;i++)
          printf("%s %s %s %s %s %s %d\n",pcodice[i]->codice,pcodice[i]->partenza,pcodice[i]->arrivo,pcodice[i]->data,pcodice[i]->ora_partenza,pcodice[i]->ora_arrivo,pcodice[i]->ritardo);
        }
        else if (opzione==file){
        for(int i=0;i<n_righe;i++){
          fprintf(fp,"%s %s %s %s %s %s %d\n",pcodice[i]->codice,pcodice[i]->partenza,pcodice[i]->arrivo,pcodice[i]->data,pcodice[i]->ora_partenza,pcodice[i]->ora_arrivo,pcodice[i]->ritardo);
        }
        }
         break;
     case ordina_arrivo://ordine per stazione di arrivo
        for(int i=l;i<r;i++){
            for(int j=l;j<r-i+l;j++){
                if(strcmp(parrivo[j]->arrivo,parrivo[j+1]->arrivo)>0){
                    tmp=parrivo[j];
                    parrivo[j]=parrivo[j+1];
                    parrivo[j+1]=tmp;
                }
            }
        }
        do{
        opzione=output();
        }while(opzione>errore);
        if(opzione==schermo){
        for(int i=0;i<n_righe;i++)
          printf("%s %s %s %s %s %s %d\n",pcodice[i]->codice,pcodice[i]->partenza,pcodice[i]->arrivo,pcodice[i]->data,pcodice[i]->ora_partenza,pcodice[i]->ora_arrivo,pcodice[i]->ritardo);
        }
        else if (opzione==file){
        for(int i=0;i<n_righe;i++){
          fprintf(fp,"%s %s %s %s %s %s %d\n",pcodice[i]->codice,pcodice[i]->partenza,pcodice[i]->arrivo,pcodice[i]->data,pcodice[i]->ora_partenza,pcodice[i]->ora_arrivo,pcodice[i]->ritardo);
        }
        }
         break;
     case ordina_partenza://ordine per stazione di partenza
         *flag=1;//flag che uso nella ricerca per indicare che già i log sono ordinati
          for(int i=l;i<r;i++){
            for(int j=l;j<r-i+l;j++){
                if(strcmp(ppartenza[j]->partenza,ppartenza[j+1]->partenza)>0){
                    tmp=ppartenza[j];
                    ppartenza[j]=ppartenza[j+1];
                    ppartenza[j+1]=tmp;
                }
            }
          }
         do{
        opzione=output();
        }while(opzione>errore);
        if(opzione==schermo){
        for(int i=0;i<n_righe;i++)
         printf("%s %s %s %s %s %s %d\n",ppartenza[i]->codice,ppartenza[i]->partenza,ppartenza[i]->arrivo,ppartenza[i]->data,ppartenza[i]->ora_partenza,ppartenza[i]->ora_arrivo,ppartenza[i]->ritardo);
        }
        else if (opzione==file){
        for(int i=0;i<n_righe;i++){
          fprintf(fp,"%s %s %s %s %s %s %d\n",ppartenza[i]->codice,ppartenza[i]->partenza,ppartenza[i]->arrivo,ppartenza[i]->data,ppartenza[i]->ora_partenza,ppartenza[i]->ora_arrivo,ppartenza[i]->ritardo);
        }
        }
         break;
     case ricerca_partenza:
        printf("Inserire stazione di partenza, nome intero o parziale\n");
        scanf("%s",ricerca);
        do{
        opzione=output();
        }while(opzione>errore);
        if(*flag==0){//se non ho già ordinato per partenza ricerca lineare
        for(int i=0;i<n_righe;i++)
            if(strstr(ppartenza[i]->partenza,ricerca)!=0){
               if(opzione==schermo){
               printf("%s %s %s %s %s %s %d\n",ppartenza[i]->codice,ppartenza[i]->partenza,ppartenza[i]->arrivo,ppartenza[i]->data,ppartenza[i]->ora_partenza,ppartenza[i]->ora_arrivo,ppartenza[i]->ritardo);}
               else if(opzione==file){
                fprintf(fp,"%s %s %s %s %s %s %d\n",ppartenza[i]->codice,ppartenza[i]->partenza,ppartenza[i]->arrivo,ppartenza[i]->data,ppartenza[i]->ora_partenza,ppartenza[i]->ora_arrivo,ppartenza[i]->ritardo);
               }
            }
         }
         else{
            l=0;
            r=n_righe-1;
            indice_inizio=ricerca_dicotomica(ppartenza,l,r,ricerca);//ricerca dicotomica
            while(strstr(ppartenza[indice_inizio]->partenza,ricerca)!=0){
            if(opzione==schermo){
               printf("%s %s %s %s %s %s %d\n",ppartenza[indice_inizio]->codice,ppartenza[indice_inizio]->partenza,ppartenza[indice_inizio]->arrivo,ppartenza[indice_inizio]->data,ppartenza[indice_inizio]->ora_partenza,ppartenza[indice_inizio]->ora_arrivo,ppartenza[indice_inizio]->ritardo);}
               else if(opzione==file){
                fprintf(fp,"%s %s %s %s %s %s %d\n",ppartenza[indice_inizio]->codice,ppartenza[indice_inizio]->partenza,ppartenza[indice_inizio]->arrivo,ppartenza[indice_inizio]->data,ppartenza[indice_inizio]->ora_partenza,ppartenza[indice_inizio]->ora_arrivo,ppartenza[indice_inizio]->ritardo);
               }
            indice_inizio++;
            }
         }
        break;
     case fine:
         break;
         default:
        printf("Errore inserimento comando\n");
        break;
     }

 }


 int ricerca_dicotomica(elenco **p,int l,int r,char ricerca[]){
 int m,v,i;
 m=(l+r)/2;
 if(strcmp(p[m]->partenza,ricerca)>0&&strstr(p[m]->partenza,ricerca)==0){
    v=ricerca_dicotomica(p,l,m,ricerca);
 }
 else if(strcmp(p[m]->partenza,ricerca)<0&&strstr(p[m]->partenza,ricerca)==0){
    v=ricerca_dicotomica(p,m+1,r,ricerca);
 }
 if(strstr(p[m]->partenza,ricerca)!=0){//se trovo una corrispondenza, dato che è ordinato mi sposto verso stringhe più piccolo fino a quandio arrivo alla prima corrispondenza
    i=m;
    while(strstr(p[i]->partenza,ricerca)!=0){
        i--;
        if(i<0){
            i=0;
            break;
        }
    }
    return i+1;
 }
  return v;
 }

 opzioni_stampa output(){
 opzioni_stampa t;
 char opzione[N],mat[errore+1][N]={"schermo","file","errore"};
 printf("Stampare a schermo o su file\n");
 scanf("%s",opzione);
 t=schermo;
 while(t<=errore&&strcmp(opzione,mat[t])!=0)
    t++;
 return t;
 }
