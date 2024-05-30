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
int acquisizione_file(elenco corse[],elenco **pdate,elenco **pcodice,elenco **ppartenza,elenco **parrivo);
comando lettura_comando();
void esegui_comando(comando scelta, elenco corse[],elenco **pdate,elenco **pcodice,elenco **ppartenza,elenco **parrivo,int n_righe,int *flag);
int ricerca_dicotomica(elenco **p,int l,int r,char ricerca[]);
int main()
{
    int n_corse,flag=0;
    comando scelta;
    elenco corse[MAX_RIGHE],*pdate[MAX_RIGHE],pcodice[MAX_RIGHE],ppartenza[MAX_RIGHE],parrivo[MAX_RIGHE];
    n_corse=acquisizione_file(corse,pdate,pcodice,ppartenza,parrivo);
    do{
    scelta=lettura_comando();
    esegui_comando(scelta,corse,pdate,pcodice,ppartenza,parrivo,n_corse,&flag);
    }while(scelta<fine);
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
    }
    close(fp);
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

 void esegui_comando(comando scelta,elenco corse[],elenco **pdate,elenco **pcodice,elenco **ppartenza,elenco **parrivo,int n_righe,int *flag){
     int x1,x2,x3,min,vet[n_righe],h_min,h_j,tmp_data,l,r,indice_inizio;
     char *tmp,ricerca[N];
     switch(scelta)
     {
     case stampa://stampa a schermo i dati del log
        for(int i=0;i<n_righe;i++)
            printf("%s %s %s %s %s %s %d\n",corse[i].codice,corse[i].partenza,corse[i].arrivo,corse[i].data,corse[i].ora_partenza,corse[i].ora_arrivo,corse[i].ritardo);
        break;
     case ordina_data://ordine crescente per data
        for(int i=0;i<n_righe;i++){
            sscanf(pdate[i]->data,"%d/%d/%d",&x1,&x2,&x3);//copio in un vettore vet le date come numeri da annomesegiorno tipo 2018/10/10=20181010
            vet[i]=(x1*10000)+(x2*100)+(x3);
        }
        for(int i=0;i<n_righe-1;i++){
            min=i;
            for(int j=i+1;j<n_righe;j++){
                if(vet[min]==vet[j]){//a parità di date ordina per orario partenza
                   sscanf(pdate[min]->ora_arrivo,"%d/%d/%d",&x1,&x2,&x3);
                    h_min=(x1*10000)+(x2*100)+x3;
                    sscanf(pdate[j]->ora_arrivo,"%d/%d/%d",&x1,&x2,&x3);
                    h_j=(x1*10000)+(x2*100)+x3;
                    if(h_min>=h_j)
                        min=j;
                }
                else if(vet[min]>vet[j]){
                    min=j;
                }
            }
         tmp=pdate[i];
         pdate[i]=pdate[min];
         pdate[min]=tmp;
         tmp_data=vet[i];
         vet[i]=vet[min];
         vet[min]=tmp_data;
        }
        for(int i=0;i<n_righe;i++)
            printf("%s %s %s %s %s %s %d\n",pdate[i]->codice,pdate[i]->partenza,pdate[i]->arrivo,pdate[i]->data,pdate[i]->ora_partenza,pdate[i]->ora_arrivo,pdate[i]->ritardo);
        break;
     case ordina_codice://ordino per codice
          for(int i=0;i<n_righe-1;i++){
        min=i;
        for(int j=i+1;j<n_righe;j++)
            if(strcmp(pcodice[min]->codice,pcodice[j]->codice)>0)
            min=j;
        tmp=pcodice[i];
        pcodice[i]=pcodice[min];
        pcodice[min]=tmp;
          }
        for(int i=0;i<n_righe;i++)
            printf("%s %s %s %s %s %s %d\n",pcodice[i]->codice,pcodice[i]->partenza,pcodice[i]->arrivo,pcodice[i]->data,pcodice[i]->ora_partenza,pcodice[i]->ora_arrivo,pcodice[i]->ritardo);
         break;
     case ordina_arrivo://ordine per stazione di arrivo
         for(int i=0;i<n_righe-1;i++){
        min=i;
        for(int j=i+1;j<n_righe;j++)
            if(strcmp(parrivo[min]->arrivo,parrivo[j]->arrivo)>0)
            min=j;
        tmp=parrivo[i];
        parrivo[i]=parrivo[min];
        parrivo[min]=tmp;
         }
         for(int i=0;i<n_righe;i++)
            printf("%s %s %s %s %s %s %d\n",parrivo[i]->codice,parrivo[i]->partenza,parrivo[i]->arrivo,parrivo[i]->data,parrivo[i]->ora_partenza,parrivo[i]->ora_arrivo,parrivo[i]->ritardo);
         break;
     case ordina_partenza://ordine per stazione di partenza
         *flag=1;//flag che uso nella ricerca per indicare che già i log sono ordinati
         for(int i=0;i<n_righe-1;i++){
        min=i;
        for(int j=i+1;j<n_righe;j++)
            if(strcmp(ppartenza[min]->partenza,ppartenza[j]->partenza)>0)
            min=j;
        tmp=ppartenza[i];
        ppartenza[i]=ppartenza[min];
        ppartenza[min]=tmp;
         }
         for(int i=0;i<n_righe;i++)
            printf("%s %s %s %s %s %s %d\n",ppartenza[i]->codice,ppartenza[i]->partenza,ppartenza[i]->arrivo,ppartenza[i]->data,ppartenza[i]->ora_partenza,ppartenza[i]->ora_arrivo,ppartenza[i]->ritardo);
         break;
     case ricerca_partenza:
        printf("Inserire stazione di partenza, nome intero o parziale\n");
        scanf("%s",ricerca);
        if(*flag==0){//se non ho già ordinato per partenza ricerca lineare
        for(int i=0;i<n_righe;i++)
            if(strstr(ppartenza[i]->partenza,ricerca)!=0)
               printf("%s %s %s %s %s %s %d\n",ppartenza[i]->codice,ppartenza[i]->partenza,ppartenza[i]->arrivo,ppartenza[i]->data,ppartenza[i]->ora_partenza,ppartenza[i]->ora_arrivo,ppartenza[i]->ritardo);
         }
         else{
            l=0;
            r=n_righe-1;
            indice_inizio=ricerca_dicotomica(ppartenza,l,r,ricerca);//ricerca dicotomica
            while(strstr(ppartenza[indice_inizio]->partenza,ricerca)!=0){
            printf("%s %s %s %s %s %s %d\n",ppartenza[indice_inizio]->codice,ppartenza[indice_inizio]->partenza,ppartenza[indice_inizio]->arrivo,ppartenza[indice_inizio]->data,ppartenza[indice_inizio]->ora_partenza,ppartenza[indice_inizio]->ora_arrivo,ppartenza[indice_inizio]->ritardo);
            indice_inizio++;
            }
         }
        break;
     default:
        printf("Errore inserimento comando\n");
        break;
     }
 }


 int ricerca_dicotomica(elenco **p,int l,int r,char ricerca[]){
 int m,v,cont=0,i;
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


