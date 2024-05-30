#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 51
typedef struct dati *link;
struct dati{
int cap,giorno,mese,anno;
char *codice, *nome, *cognome, *via, *citta;
link next;
};
link inserimento_da_file(char *nome_file,link h);
link NewNode(char *codice,char *nome,char *cognome,char *via,char *citta,int cap,int giorno,int mese,int anno);
link lettura_lista(link h,char *codice,char *nome,char *cognome,char *via,char *citta,int cap,int giorno,int mese,int anno);
link cancella_per_codice(link h,char *key);
link lettura_date(link h,int giorno,int mese,int anno,int *flag);
link cancellazione_date(link h,link i,int giorno,int mese,int anno);
int Check_date(int giorno,int mese,int anno,int giorno2,int mese2,int anno2);
typedef enum {file,tastiera,stampa,cancella_codice,cancella_date,fine}opzioni;
opzioni lettura_comando();
void stampa_file(link h);
void libera_spazio(link h);
int main(){
 char nome_file[N],codice[N],nome[N],cognome[N],via[N],citta[N],codice_da_cancellare[N];
 int cap,giorno,mese,anno,flag=0;
 opzioni t;
 link head=NULL,inizio_cancellazione;
 t=lettura_comando();
 while(t!=fine){
 system("cls");
 switch(t){//menu
 case stampa:
     stampa_file(head);
     break;
 case file:
     printf("Inserire nome file: ");
     scanf("%s",nome_file);
     head=inserimento_da_file(nome_file,head);
     break;
 case tastiera:
     printf("<codice> <nome> <cognome> <data di nascita> <via> <città> <cap>\n");
     scanf("%s %s %s %d/%d/%d %s %s %d",codice,nome,cognome,&giorno,&mese,&anno,via,citta,&cap);
     head=lettura_lista(head,codice,nome,cognome,via,citta,cap,giorno,mese,anno);
     break;
 case cancella_codice:
     printf("Inserire codice da cercare e rimuovere dalla lista del tipo AXXXX\n");
     scanf("%s",codice_da_cancellare);
     head=cancella_per_codice(head,codice_da_cancellare);
     break;
 case cancella_date:
     printf("Inserire 2 date\n");
     printf("Prima data gg/mm/aaaa: ");
     scanf("%d/%d/%d",&giorno,&mese,&anno);
     inizio_cancellazione=lettura_date(head,giorno,mese,anno,&flag);
     if(flag==0)
        break;
     printf("Seconda data gg/mm/aaaa: ");
     scanf("%d/%d/%d",&giorno,&mese,&anno);
     head=cancellazione_date(head,inizio_cancellazione,giorno,mese,anno);
     break;
 default:
    printf("Errore inserimento comando\n");
 }
 t=lettura_comando();
 }
 libera_spazio(head);
 return 0;
}
void stampa_file(link h){
char nome_file[N];
FILE *fp;
printf("Inserire nome file: ");
scanf("%s",nome_file);
fp=fopen(nome_file,"w");
if(fp==NULL){
    printf("Errore apertura file\n");
    exit(EXIT_FAILURE);
}
for(link x=h;x!=NULL;x=x->next){
        fprintf(fp,"%s %s %s %d/%d/%d %s %s %d\n",x->codice,x->nome,x->cognome,x->giorno,x->mese,x->anno,x->via,x->citta,x->cap);
        printf("%s %s %s %d/%d/%d %s %s %d\n",x->codice,x->nome,x->cognome,x->giorno,x->mese,x->anno,x->via,x->citta,x->cap);
}
fclose(fp);
}
link inserimento_da_file(char *nome_file,link h){
    FILE *fp;
    int cap,giorno,mese,anno;
    char codice[N],nome[N],cognome[N],via[N],citta[N];
    fp=fopen(nome_file,"r");
    if(fp==NULL){
        printf("Errore apertura file\n");
        exit(EXIT_FAILURE);
    }
    while(fscanf(fp,"%s %s %s %d/%d/%d %s %s %d",codice,nome,cognome,&giorno,&mese,&anno,via,citta,&cap)!=EOF){//prima ordino e poi vedo dove inserire i dati;
    h=lettura_lista(h,codice,nome,cognome,via,citta,cap,giorno,mese,anno);
    }
    fclose(fp);
    return h;
}

link NewNode(char *codice,char *nome,char *cognome,char *via,char *citta,int cap,int giorno,int mese,int anno){
link x;
x=malloc(sizeof(*x));
if(x==NULL)
    return NULL;
else{
x->codice=malloc((strlen(codice)+1)*sizeof(char));
strcpy(x->codice,codice);
x->nome=malloc((strlen(nome)+1)*sizeof(char));
strcpy(x->nome,nome);
x->cognome=malloc((strlen(cognome)+1)*sizeof(char));
strcpy(x->cognome,cognome);
x->via=malloc((strlen(via)+1)*sizeof(char));
strcpy(x->via,via);
x->citta=malloc((strlen(citta)+1)*sizeof(char));
strcpy(x->citta,citta);
x->cap=cap;
x->giorno=giorno;
x->mese=mese;
x->anno=anno;
x->next=NULL;
}
return x;
}


link lettura_lista(link h,char *codice,char *nome,char *cognome,char *via,char *citta,int cap,int giorno,int mese,int anno){
link x,p=NULL,tmp;
if(h==NULL){
    h=NewNode(codice,nome,cognome,via,citta,cap,giorno,mese,anno);
}
else{
for(x=h;x!=NULL;p=x,x=x->next){
    if(Check_date(giorno,mese,anno,x->giorno,x->mese,x->anno)==1){
      tmp=NewNode(codice,nome,cognome,via,citta,cap,giorno,mese,anno);
      if(x==h){
      tmp->next=x;
      h=tmp;
      }
      else{
      p->next=tmp;
      p->next->next=x;
      }
      break;
    }
    else if(x->next==NULL){
    tmp=NewNode(codice,nome,cognome,via,citta,cap,giorno,mese,anno);
    x->next=tmp;
    break;
    }
}
}
return h;
}

int Check_date(int giorno,int mese,int anno,int giorno2,int mese2,int anno2){
int c=0;
int data,data2;
data=(anno*10000)+(mese*100)+giorno;
data2=(anno2*10000)+(mese2*100)+giorno2;
if(data<=data2)
    c=1;
return c;
}

opzioni lettura_comando(){//gestione enum
char mat[fine+1][N]={"file","tastiera","stampa","codice","date","fine"};
char comando[N];
printf("-Per stampare su file <stampa>\n-Inserire in lista da <file> o <tasteria>\n-Per cancellare per codice o date <codice> <date>\n");
scanf("%s",comando);
opzioni t=file;
while(t<=fine&&strcmp(comando,mat[t])!=0)
    t++;
return t;
}
link cancella_per_codice(link h,char *key){
link p=NULL,t;
if(h==NULL)
        return NULL;
for(link x=h;x!=NULL;p=x,x=x->next){
    if(strcmp(x->codice,key)==0){
            printf("Riga cancellata\n");
            printf("%s %s %s %d/%d/%d %s %s %d\n",x->codice,x->nome,x->cognome,x->giorno,x->mese,x->anno,x->via,x->citta,x->cap);
            if(x==h){
            t=h;
            h=h->next;
            free(t);
            break;
            }
            else{
                t=x;
                p->next=x->next;
                free(t);
                break;
            }
    }
}
return h;
}
link lettura_date(link h,int giorno,int mese,int anno,int *flag){
link p=NULL;
for(link x=h;x!=NULL;p=x,x=x->next){
    if(Check_date(giorno,mese,anno,x->giorno,x->mese,x->anno)==1){//se la data della lista corrente è compresa tra quelle inserite da tastiera
        *flag=1;
        return p;
       }
    }
return NULL;
}

link cancellazione_date(link h,link i,int giorno,int mese,int anno){//permette la cancellazione di più date
link t,x;
if(i==NULL)
    x=h;
else
    x=i->next;
printf("Riga cancellata\e\n");
for(x;Check_date(x->giorno,x->mese,x->anno,giorno,mese,anno)==1;){
    if(x==h){
        printf("%s %s %s %d/%d/%d %s %s %d\n",x->codice,x->nome,x->cognome,x->giorno,x->mese,x->anno,x->via,x->citta,x->cap);
        t=x;
        h=h->next;
        x=h;
        free(t);
        if(x==NULL)
            break;
    }
    else{
        printf("%s %s %s %d/%d/%d %s %s %d\n",x->codice,x->nome,x->cognome,x->giorno,x->mese,x->anno,x->via,x->citta,x->cap);
        t=x;
        x=x->next;
        i->next=x;
        free(t);
        if(x==NULL)
            break;
    }
}
return h;
}

void libera_spazio(link h){
if(h==NULL){
    return;
}
libera_spazio(h->next);
free(h->citta);
free(h->nome);
free(h->cognome);
free(h->codice);
free(h->via);
free(h);
return;
}
