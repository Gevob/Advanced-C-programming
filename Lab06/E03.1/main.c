#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 31
typedef struct {char *codice, *partenza, *arrivo, *data, *ora_inizio, *ora_fine;
                int *ritardo;
                }log;
log * acquisizione_file(log ***p_date,log ***p_codice,log ***p_partenza,log ***p_arrivo,int *n, char *nome_file);
int lettura_comando();
void output();
void ordinamento_date(log **date,int n);
void ordinamento_partenze(log **partenze,int n);
void ordinamento_arrivi(log **arrivo,int n);
void ordinamento_codice(log **codice,int n);
int ricerca_dicotomica_wrapper(log **partenza,int n,char *parola);
int ricerca_dicotomica(log **partenza,int l,int r,char *parola);
void free_dati(log *corse,log **p_date,log **p_codice,log **p_partenza,log **p_arrivo,int n);
int main()
{
    int n_corse,flag=0,indice_inizio,scelta,out;
    char parola[MAX],nome_file[MAX];
    log *corse,**date,**codice,**partenza,**arrivo;
    FILE *fp_stampa;
    fp_stampa=fopen("risultati.txt","w");
    if(fp_stampa==NULL){
        printf("Errore apertura file\n");
        return 1;
    }
    corse=acquisizione_file(&date,&codice,&partenza,&arrivo,&n_corse,"log.txt");
    do{
    printf("Scrivere comando\n0:stampa\n1:ordina per data\n2:ordina per codice\n3:ordina per partenza\n4:ordina per arrivo\n5:ricerca per stazione di partenza\n6:lettura file\n7:per terminare\n");
    scanf("%d",&scelta);
    switch(scelta)
    {
    case 0://stampa a schermo i dati log
        do{
         printf("0 Stampare a schermo\n1 stampare su file\n");
         scanf("%d",&out);
        if(out>=2)
            printf("Errore inserimento comando\n");
        }while(out>=2);
            for(int i=0;i<n_corse;i++){
               if(out==0)
                 printf("%s %s %s %s %s %s %d\n",corse[i].codice,corse[i].partenza,corse[i].arrivo,corse[i].data,corse[i].ora_inizio,corse[i].ora_fine,*corse[i].ritardo);
               if(out==1)
                 fprintf(fp_stampa,"%s %s %s %s %s %s %d\n",corse[i].codice,corse[i].partenza,corse[i].arrivo,corse[i].data,corse[i].ora_inizio,corse[i].ora_fine,*corse[i].ritardo);
        }
        break;
    case 1://ordina per date
        ordinamento_date(date,n_corse);
        output(n_corse,date,fp_stampa);
        break;
    case 2://Ordina per codice
        ordinamento_codice(codice,n_corse);
        output(n_corse,codice,fp_stampa);
        break;
    case 3://ordina per arrivi
        ordinamento_arrivi(arrivo,n_corse);
        output(n_corse,arrivo,fp_stampa);
        break;
    case 4://ordina per partenze
        flag=1;
        ordinamento_partenze(partenza,n_corse);
        output(n_corse,partenza,fp_stampa);
        break;
    case 5://ricerca per stazione di partenza
        printf("Inserire stazione di partenza, nome intero o parziale\n");
        scanf("%s",parola);
        do{
         printf("0 Stampare a schermo\n1 stampare su file\n");
         scanf("%d",&out);
         if(out>=2)
            printf("Errore inserimento comando\n");
        }while(out>=2);
        if(flag==0){//se non ho già ordinato per partenza ricerca lineare
        for(int i=0;i<n_corse;i++)
            if(strstr(partenza[i]->partenza,parola)!=0){
               if(out==0){
               printf("%s %s %s %s %s %s %d\n",partenza[i]->codice,partenza[i]->partenza,partenza[i]->arrivo,partenza[i]->data,partenza[i]->ora_inizio,partenza[i]->ora_fine,*partenza[i]->ritardo);}
               else if(out==1){
                fprintf(fp_stampa,"%s %s %s %s %s %s %d\n",partenza[i]->codice,partenza[i]->partenza,partenza[i]->arrivo,partenza[i]->data,partenza[i]->ora_inizio,partenza[i]->ora_fine,*partenza[i]->ritardo);
               }
            }
         }
         else{
            indice_inizio=ricerca_dicotomica_wrapper(partenza,n_corse,parola);//ricerca dicotomica
            while(strstr(partenza[indice_inizio]->partenza,parola)!=0){
            if(out==0){
               printf("%s %s %s %s %s %s %d\n",partenza[indice_inizio]->codice,partenza[indice_inizio]->partenza,partenza[indice_inizio]->arrivo,partenza[indice_inizio]->data,partenza[indice_inizio]->ora_inizio,partenza[indice_inizio]->ora_fine,*partenza[indice_inizio]->ritardo);}
               else if(out==1){
                fprintf(fp_stampa,"%s %s %s %s %s %s %d\n",partenza[indice_inizio]->codice,partenza[indice_inizio]->partenza,partenza[indice_inizio]->arrivo,partenza[indice_inizio]->data,partenza[indice_inizio]->ora_inizio,partenza[indice_inizio]->ora_fine,*partenza[indice_inizio]->ritardo);
               }
            indice_inizio++;
            }
         }
         break;
    case 6://ricerca per stazione di partenza
    printf("Inserire il nome del file da leggere\n");
    scanf("%s",nome_file);
    free_dati(corse,date,codice,partenza,arrivo,n_corse);
    corse=acquisizione_file(&date,&codice,&partenza,&arrivo,&n_corse,nome_file);
    break;
    case 7:
        break;
    default:
        printf("Errore inserimento comando\n");
    }
    }
    while(scelta!=7);
    close(fp_stampa);
    return 0;

}
log * acquisizione_file(log ***p_date,log ***p_codice,log ***p_partenza,log ***p_arrivo,int *n,char *nome_file){
    int n_corse,ritardo;
    char codice[MAX],partenza[MAX],arrivo[MAX],data[MAX],orario_partenza[MAX],orario_arrivo[MAX];
    log *corsa,**vet_codice,**vet_date,**vet_partenza,**vet_arrivo;
    FILE *fp;
    fp=fopen(nome_file,"r");
    if(fp==NULL){
        printf("Errore apertura file\n");
        return 0;
    }
    fscanf(fp,"%d",&n_corse);
    corsa=malloc(n_corse*sizeof(log));
    vet_codice=(log **)malloc(n_corse*sizeof(log *));
    vet_partenza=(log **)malloc(n_corse*sizeof(log *));
    vet_arrivo=(log **)malloc(n_corse*sizeof(log *));
    vet_date=(log **)malloc(n_corse*sizeof(log *));
    for(int i=0;i<n_corse;i++){
    fscanf(fp,"%s%s%s%s%s%s%d",codice,partenza,arrivo,data,orario_partenza,orario_arrivo,&ritardo);
    corsa[i].codice=(char *)malloc((strlen(codice)+1)*sizeof(char));
    corsa[i].partenza=(char *)malloc((strlen(partenza)+1)*sizeof(char));
    corsa[i].arrivo=(char *)malloc((strlen(arrivo)+1)*sizeof(char));
    corsa[i].data=(char *)malloc((strlen(data)+1)*sizeof(char));
    corsa[i].ora_inizio=(char *)malloc((strlen(orario_partenza)+1)*sizeof(char));
    corsa[i].ora_fine=(char *)malloc((strlen(orario_arrivo)+1)*sizeof(char));

    strcpy(corsa[i].codice,codice);
    strcpy(corsa[i].partenza,partenza);
    strcpy(corsa[i].arrivo,arrivo);
    strcpy(corsa[i].data,data);
    strcpy(corsa[i].ora_inizio,orario_partenza);
    strcpy(corsa[i].ora_fine,orario_arrivo);
    corsa[i].ritardo=ritardo;
    vet_codice[i]=vet_partenza[i]=vet_arrivo[i]=vet_date[i]=&corsa[i];
    }
    *p_date=vet_date;
    *p_codice=vet_codice;
    *p_partenza=vet_partenza;
    *p_arrivo=vet_arrivo;
    *n=n_corse;
    close(fp);
    return corsa;
}


 void output(int n,log **p,FILE *fp){
 int out;
 do{
 printf("0 Stampare a schermo\n1 stampare su file\n");
 scanf("%d",&out);
 switch(out){
 case 0:
      for(int i=0;i<n;i++)
            printf("%s %s %s %s %s %s %d\n",p[i]->codice,p[i]->partenza,p[i]->arrivo,p[i]->data,p[i]->ora_inizio,p[i]->ora_fine,*p[i]->ritardo);
     break;
 case 1:
     for(int i=0;i<n;i++)
            fprintf(fp,"%s %s %s %s %s %s %d\n",p[i]->codice,p[i]->partenza,p[i]->arrivo,p[i]->data,p[i]->ora_inizio,p[i]->ora_fine,*p[i]->ritardo);
    break;
 default:
    printf("Errore inserimento comando\n");
    break;
 }
 }while(out>=3);
 }

 void ordinamento_date(log **date,int n){
 int l=0,r=n-1;
 log *tmp;
 for(int i=l;i<r;i++){
            for(int j=l;j<r-i+l;j++){
                if(strcmp(date[j]->data,date[j+1]->data)>0){
                    tmp=date[j];
                    date[j]=date[j+1];
                    date[j+1]=tmp;
                }
                if(strcmp(date[j]->data,date[j+1]->data)==0){
                    if(strcmp(date[j]->ora_inizio,date[j+1]->ora_inizio)>0){
                        tmp=date[j];
                        date[j]=date[j+1];
                        date[j+1]=tmp;
                    }
                }
            }
        }
 }

 void ordinamento_codice(log **codice,int n){
 int l=0,r=n-1;
 log *tmp;
 for(int i=l;i<r;i++){
            for(int j=l;j<r-i+l;j++){
                if(strcmp(codice[j]->codice,codice[j+1]->codice)>0){
                    tmp=codice[j];
                    codice[j]=codice[j+1];
                    codice[j+1]=tmp;
                }
            }
        }
 }

 void ordinamento_arrivi(log **arrivo,int n){
 int l=0,r=n-1;
 log *tmp;
 for(int i=l;i<r;i++){
            for(int j=l;j<r-i+l;j++){
                if(strcmp(arrivo[j]->arrivo,arrivo[j+1]->arrivo)>0){
                    tmp=arrivo[j];
                    arrivo[j]=arrivo[j+1];
                    arrivo[j+1]=tmp;
                }
            }
        }
 }

 void ordinamento_partenze(log **partenze,int n){
  int l=0,r=n-1;
 log *tmp;
 for(int i=l;i<r;i++){
            for(int j=l;j<r-i+l;j++){
                if(strcmp(partenze[j]->partenza,partenze[j+1]->partenza)>0){
                    tmp=partenze[j];
                    partenze[j]=partenze[j+1];
                    partenze[j+1]=tmp;
                }
            }
 }
 }

int ricerca_dicotomica_wrapper(log **partenza,int n,char *parola){
int l=0,r=n-1;
return ricerca_dicotomica(partenza,l,r,parola);
}
int ricerca_dicotomica(log **partenza,int l,int r,char *parola){
 int m,v,i;
 m=(l+r)/2;
 if(strcmp(partenza[m]->partenza,parola)>0&&strstr(partenza[m]->partenza,parola)==0){
    v=ricerca_dicotomica(partenza,l,m,parola);
 }
 else if(strcmp(partenza[m]->partenza,parola)<0&&strstr(partenza[m]->partenza,parola)==0){
    v=ricerca_dicotomica(partenza,m+1,r,parola);
 }
 if(strstr(partenza[m]->partenza,parola)!=0){//se trovo una corrispondenza, dato che è ordinato mi sposto verso stringhe più piccolo fino a quandio arrivo alla prima corrispondenza
    i=m;
    while(strstr(partenza[i]->partenza,parola)!=0){
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

void free_dati(log *corse,log **p_date,log **p_codice,log **p_partenza,log **p_arrivo,int n){
    free(p_date);
    free(p_codice);
    free(p_partenza);
    free(p_arrivo);
    for(int i=0;i<n;i++){
        free(corse[i].codice);
        free(corse[i].partenza);
        free(corse[i].arrivo);
        free(corse[i].data);
        free(corse[i].ora_inizio);
        free(corse[i].ora_fine);
        free(corse[i].ritardo);
    }
    free(corse);
}
