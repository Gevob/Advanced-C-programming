#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 30
#define MAX_RIGHE 1000
typedef struct{
char codice[N],partenza[N],arrivo[N],data[N],ora_partenza[N],ora_arrivo[N];
int ritardo;
}elenco;
int acquisizione_file(elenco corse[],elenco **pdate,elenco **pcodice,elenco **ppartenza,elenco **parrivo);
void output();
void esegui_comando(int scelta, elenco corse[],elenco **pdate,elenco **pcodice,elenco **ppartenza,elenco **parrivo,int n_righe,int *flag,FILE *fp);
int ricerca_dicotomica(elenco **p,int l,int r,char ricerca[]);
int main()
{
    int n_corse,flag=0,scelta;
    elenco *corse[MAX_RIGHE],*pdate[MAX_RIGHE],*pcodice[MAX_RIGHE],*ppartenza[MAX_RIGHE],*parrivo[MAX_RIGHE];
    FILE *fp2;
     fp2=fopen("risultati.txt","w");
     if(fp2==NULL){
        printf("Errore file 'risultati'\n");
        return 0;}
    n_corse=acquisizione_file(corse,pdate,pcodice,ppartenza,parrivo);
    do{
    printf("Scrivere comando\n0:stampa\n1:ordina per data\n2:ordina per codice\n3:ordina per partenza\n4:ordina per arrivo\n5:ricerca per stazione di partenza\n6:fine per terminare\n");
    scanf("%d",&scelta);
    esegui_comando(scelta,corse,pdate,pcodice,ppartenza,parrivo,n_corse,&flag,fp2);
    }while(scelta!=6);
    return 0;
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

 void esegui_comando(int scelta,elenco corse[],elenco **pdate,elenco **pcodice,elenco **ppartenza,elenco **parrivo,int n_righe,int *flag,FILE *fp){
     int l=0,r=n_righe-1,indice_inizio,out;
     char ricerca[N];
     elenco *tmp;
     switch(scelta)
     {
     case 0://stampa a schermo i dati del log
        do{
         printf("0 Stampare a schermo\n1 stampare su file\n");
         scanf("%d",&out);
        if(out>=2)
            printf("Errore inserimento comando\n");
        }while(out>=2);
            for(int i=0;i<n_righe;i++){
               if(out==0)
                 printf("%s %s %s %s %s %s %d\n",corse[i].codice,corse[i].partenza,corse[i].arrivo,corse[i].data,corse[i].ora_partenza,corse[i].ora_arrivo,corse[i].ritardo);
               if(out==1)
                 fprintf(fp,"%s %s %s %s %s %s %d\n",corse[i].codice,corse[i].partenza,corse[i].arrivo,corse[i].data,corse[i].ora_partenza,corse[i].ora_arrivo,corse[i].ritardo);
        }
        break;
     case 1://ordine crescente per data
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
        output(n_righe,pdate,fp);
        break;
     case 2://ordino per codice
        for(int i=l;i<r;i++){
            for(int j=l;j<r-i+l;j++){
                if(strcmp(pcodice[j]->codice,pcodice[j+1]->codice)>0){
                    tmp=pcodice[j];
                    pcodice[j]=pcodice[j+1];
                    pcodice[j+1]=tmp;
                }
            }
        }
        output(n_righe,pcodice,fp);
         break;
     case 3://ordine per stazione di arrivo
        for(int i=l;i<r;i++){
            for(int j=l;j<r-i+l;j++){
                if(strcmp(parrivo[j]->arrivo,parrivo[j+1]->arrivo)>0){
                    tmp=parrivo[j];
                    parrivo[j]=parrivo[j+1];
                    parrivo[j+1]=tmp;
                }
            }
        }
        output(n_righe,parrivo,fp);
         break;
     case 4://ordine per stazione di partenza
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
         output(n_righe,ppartenza,fp);
         break;
     case 5:
        printf("Inserire stazione di partenza, nome intero o parziale\n");
        scanf("%s",ricerca);
        do{
         printf("0Stampare a schermo\n1 stampare su file\n");
         scanf("%d",&out);
         if(out>=2)
            printf("Errore inserimento comando\n");
        }while(out>=2);
        if(*flag==0){//se non ho già ordinato per partenza ricerca lineare
        for(int i=0;i<n_righe;i++)
            if(strstr(ppartenza[i]->partenza,ricerca)!=0){
               if(out==0){
               printf("%s %s %s %s %s %s %d\n",ppartenza[i]->codice,ppartenza[i]->partenza,ppartenza[i]->arrivo,ppartenza[i]->data,ppartenza[i]->ora_partenza,ppartenza[i]->ora_arrivo,ppartenza[i]->ritardo);}
               else if(out==1){
                fprintf(fp,"%s %s %s %s %s %s %d\n",ppartenza[i]->codice,ppartenza[i]->partenza,ppartenza[i]->arrivo,ppartenza[i]->data,ppartenza[i]->ora_partenza,ppartenza[i]->ora_arrivo,ppartenza[i]->ritardo);
               }
            }
         }
         else{
            l=0;
            r=n_righe-1;
            indice_inizio=ricerca_dicotomica(ppartenza,l,r,ricerca);//ricerca dicotomica
            while(strstr(ppartenza[indice_inizio]->partenza,ricerca)!=0){
            if(out==0){
               printf("%s %s %s %s %s %s %d\n",ppartenza[indice_inizio]->codice,ppartenza[indice_inizio]->partenza,ppartenza[indice_inizio]->arrivo,ppartenza[indice_inizio]->data,ppartenza[indice_inizio]->ora_partenza,ppartenza[indice_inizio]->ora_arrivo,ppartenza[indice_inizio]->ritardo);}
               else if(out==1){
                fprintf(fp,"%s %s %s %s %s %s %d\n",ppartenza[indice_inizio]->codice,ppartenza[indice_inizio]->partenza,ppartenza[indice_inizio]->arrivo,ppartenza[indice_inizio]->data,ppartenza[indice_inizio]->ora_partenza,ppartenza[indice_inizio]->ora_arrivo,ppartenza[indice_inizio]->ritardo);
               }
            indice_inizio++;
            }
         }
        break;
     case 6:
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

 void output(int n,elenco **p,FILE *fp){
 int out;
 do{
 printf("0 Stampare a schermo\n1 stampare su file\n");
 scanf("%d",&out);
 switch(out){
 case 0:
      for(int i=0;i<n;i++)
            printf("%s %s %s %s %s %s %d\n",p[i]->codice,p[i]->partenza,p[i]->arrivo,p[i]->data,p[i]->ora_partenza,p[i]->ora_arrivo,p[i]->ritardo);
     break;
 case 1:
     for(int i=0;i<n;i++)
            fprintf(fp,"%s %s %s %s %s %s %d\n",p[i]->codice,p[i]->partenza,p[i]->arrivo,p[i]->data,p[i]->ora_partenza,p[i]->ora_arrivo,p[i]->ritardo);
    break;
 default:
    printf("Errore inserimento comando\n");
    break;
 }
 }while(out>=3);
 }
