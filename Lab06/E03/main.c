#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 31
typedef struct {char *codice, *partenza, *arrivo, *data, *ora_inizio, *ora_fine;
                int *ritardo}log;
typedef enum {stampa, ordina_data, ordina_codice, ordina_partenza, ordina_arrivo, ricerca_partenza, lettura_file, fine}comando;
typedef enum {schermo, file, errore}opzioni_stampa;
log * acquisizione_file(log ***p_date,log ***p_codice,log ***p_partenza,log ***p_arrivo,int *n, char *nome_file);
comando lettura_comando();
opzioni_stampa output();
void ordinamento_date(log **date,int n);
void ordinamento_partenze(log **partenze,int n);
void ordinamento_arrivi(log **arrivo,int n);
void ordinamento_codice(log **codice,int n);
int ricerca_dicotomica_wrapper(log **partenza,int n,char *parola);
int ricerca_dicotomica(log **partenza,int l,int r,char *parola);
void free_dati(log *corse,log **p_date,log **p_codice,log **p_partenza,log **p_arrivo,int n);
int main()
{
    int n_corse,flag=0,indice_inizio;
    char parola[MAX],nome_file[MAX];
    comando scelta;
    opzioni_stampa opzione;
    log *corse,**date,**codice,**partenza,**arrivo;
    FILE *fp_stampa;
    fp_stampa=fopen("risultati.txt","w");
    if(fp_stampa==NULL){
        printf("Errore apertura file\n");
        return 1;
    }
    corse=acquisizione_file(&date,&codice,&partenza,&arrivo,&n_corse,"log.txt");
    do{
    scelta=lettura_comando();
    switch(scelta)
    {
    case stampa://stampa a schermo i dati log
        do{
        opzione=output();
        }while(opzione>errore);
        if(opzione==schermo){
        for(int i=0;i<n_corse;i++)
            printf("%s %s %s %s %s %s %d\n",codice[i]->codice,codice[i]->partenza,codice[i]->arrivo,codice[i]->data,codice[i]->ora_inizio,codice[i]->ora_fine,*codice[i]->ritardo);
        }
        else if (opzione==file){
        for(int i=0;i<n_corse;i++)
            fprintf(fp_stampa,"%s %s %s %s %s %s %d\n",codice[i]->codice,codice[i]->partenza,codice[i]->arrivo,codice[i]->data,codice[i]->ora_inizio,codice[i]->ora_fine,*codice[i]->ritardo);
        }
        break;
    case ordina_data://ordina per date
        ordinamento_date(date,n_corse);
        do{
        opzione=output();
        }while(opzione>errore);
        if(opzione==schermo){
        for(int i=0;i<n_corse;i++)
            printf("%s %s %s %s %s %s %d\n",date[i]->codice,date[i]->partenza,date[i]->arrivo,date[i]->data,date[i]->ora_inizio,date[i]->ora_fine,*date[i]->ritardo);
        }
        else if (opzione==file){
        for(int i=0;i<n_corse;i++)
            fprintf(fp_stampa,"%s %s %s %s %s %s %d\n",date[i]->codice,date[i]->partenza,date[i]->arrivo,date[i]->data,date[i]->ora_inizio,date[i]->ora_fine,*date[i]->ritardo);
        }
        break;
    case ordina_codice://Ordina per codice
        ordinamento_codice(codice,n_corse);
        do{
        opzione=output();
        }while(opzione>errore);
        if(opzione==schermo){
        for(int i=0;i<n_corse;i++)
            printf("%s %s %s %s %s %s %d\n",codice[i]->codice,codice[i]->partenza,codice[i]->arrivo,codice[i]->data,codice[i]->ora_inizio,codice[i]->ora_fine,*codice[i]->ritardo);
        }
        else if (opzione==file){
        for(int i=0;i<n_corse;i++)
            fprintf(fp_stampa,"%s %s %s %s %s %s %d\n",codice[i]->codice,codice[i]->partenza,codice[i]->arrivo,codice[i]->data,codice[i]->ora_inizio,codice[i]->ora_fine,*codice[i]->ritardo);
        }
        break;
    case ordina_arrivo://ordina per arrivi
        ordinamento_arrivi(arrivo,n_corse);
        do{
        opzione=output();
        }while(opzione>errore);
        if(opzione==schermo){
        for(int i=0;i<n_corse;i++)
            printf("%s %s %s %s %s %s %d\n",arrivo[i]->codice,arrivo[i]->partenza,arrivo[i]->arrivo,arrivo[i]->data,arrivo[i]->ora_inizio,arrivo[i]->ora_fine,*arrivo[i]->ritardo);
        }
        else if (opzione==file){
        for(int i=0;i<n_corse;i++)
            fprintf(fp_stampa,"%s %s %s %s %s %s %d\n",arrivo[i]->codice,arrivo[i]->partenza,arrivo[i]->arrivo,arrivo[i]->data,arrivo[i]->ora_inizio,arrivo[i]->ora_fine,*partenza[i]->ritardo);
        }
        break;
    case ordina_partenza://ordina per partenze
        flag=1;
        ordinamento_partenze(partenza,n_corse);
        do{
        opzione=output();
        }while(opzione>errore);
        if(opzione==schermo){
        for(int i=0;i<n_corse;i++)
            printf("%s %s %s %s %s %s %d\n",partenza[i]->codice,partenza[i]->partenza,partenza[i]->arrivo,partenza[i]->data,partenza[i]->ora_inizio,partenza[i]->ora_fine,*partenza[i]->ritardo);
        }
        else if (opzione==file){
        for(int i=0;i<n_corse;i++)
            fprintf(fp_stampa,"%s %s %s %s %s %s %d\n",partenza[i]->codice,partenza[i]->partenza,partenza[i]->arrivo,partenza[i]->data,partenza[i]->ora_inizio,partenza[i]->ora_fine,*partenza[i]->ritardo);
        }
        break;
    case ricerca_partenza:
        printf("Inserire stazione di partenza, nome intero o parziale\n");
        scanf("%s",parola);
        do{
        opzione=output();
        }while(opzione>errore);
        if(flag==0){//se non ho già ordinato per partenza ricerca lineare
        for(int i=0;i<n_corse;i++)
            if(strstr(partenza[i]->partenza,parola)!=0){
               if(opzione==schermo){
               printf("%s %s %s %s %s %s %d\n",partenza[i]->codice,partenza[i]->partenza,partenza[i]->arrivo,partenza[i]->data,partenza[i]->ora_inizio,partenza[i]->ora_fine,*partenza[i]->ritardo);}
               else if(opzione==file){
                fprintf(fp_stampa,"%s %s %s %s %s %s %d\n",partenza[i]->codice,partenza[i]->partenza,partenza[i]->arrivo,partenza[i]->data,partenza[i]->ora_inizio,partenza[i]->ora_fine,*partenza[i]->ritardo);
               }
            }
         }
         else{
            indice_inizio=ricerca_dicotomica_wrapper(partenza,n_corse,parola);//ricerca dicotomica
            while(strstr(partenza[indice_inizio]->partenza,parola)!=0){
            if(opzione==schermo){
               printf("%s %s %s %s %s %s %d\n",partenza[indice_inizio]->codice,partenza[indice_inizio]->partenza,partenza[indice_inizio]->arrivo,partenza[indice_inizio]->data,partenza[indice_inizio]->ora_inizio,partenza[indice_inizio]->ora_fine,*partenza[indice_inizio]->ritardo);}
               else if(opzione==file){
                fprintf(fp_stampa,"%s %s %s %s %s %s %d\n",partenza[indice_inizio]->codice,partenza[indice_inizio]->partenza,partenza[indice_inizio]->arrivo,partenza[indice_inizio]->data,partenza[indice_inizio]->ora_inizio,partenza[indice_inizio]->ora_fine,*partenza[indice_inizio]->ritardo);
               }
            indice_inizio++;
            }
         }
         break;
    case lettura_file:
    printf("Inserire il nome del file da leggere\n");
    scanf("%s",nome_file);
    free_dati(corse,date,codice,partenza,arrivo,n_corse);
    corse=acquisizione_file(&date,&codice,&partenza,&arrivo,&n_corse,nome_file);
    break;
    default:
        printf("Errore inserimento comando\n");
    }
    }
    while(scelta<fine);
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
    corsa[i].ritardo=(int *)malloc(sizeof(int));
    strcpy(corsa[i].codice,codice);
    strcpy(corsa[i].partenza,partenza);
    strcpy(corsa[i].arrivo,arrivo);
    strcpy(corsa[i].data,data);
    strcpy(corsa[i].ora_inizio,orario_partenza);
    strcpy(corsa[i].ora_fine,orario_arrivo);
    *corsa[i].ritardo=ritardo;
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

 comando lettura_comando(){
 char opzione[MAX],comandi[fine+1][MAX]={"stampa","ordinaXdata","ordinaXcodice","ordinaXpartenza","ordinaXarrivo","ricerca_partenza","lettura_file","fine"};
 comando t;
 printf("Scrivere comando\n-stampa\n-ordinaX... ...=data codice partenza arrivo\n-per ricerca per stazione di partenza inserire <ricerca_partenza>\n-lettura_file per leggere un file\n-fine per terminare\n");
 scanf("%s",opzione);
 t=stampa;
 while(t<=fine&& strcmp(opzione,comandi[t])!=0)
    t++;
 return t;
 }

 opzioni_stampa output(){
 opzioni_stampa t;
 char opzione[MAX],mat[errore+1][MAX]={"schermo","file","errore"};
 printf("Stampare a schermo o su file\n");
 scanf("%s",opzione);
 t=schermo;
 while(t<=errore&&strcmp(opzione,mat[t])!=0)
    t++;
 return t;
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
