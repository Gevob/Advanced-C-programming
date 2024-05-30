#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 51
#define M 6
#define MAX 8
typedef struct dati *link;
typedef struct equipaggiamento *coll;
typedef struct inventario *p;
struct dati{
char nome[N],classe[N],codice[N];
int hp,mp,atk,def,mag,spr,buf[M],hp_f,mp_f,atk_f,def_f,mag_f,spr_f;
coll equip;
link next;
};
struct equipaggiamento{
int n_equip;
p *inventory;
};
struct inventario{
char nome[N],tipo[N];
int hp,mp,atk,def,mag,spr;
};
typedef enum{agg_pers,delete_pers,agg_equip,delete_equip,show_pers,fine,err}opzioni;
link acquisizione_personaggi(link head);
link lettura_lista(link head,char *codice, char *nome, char *classe,int hp,int mp,int atk,int def,int mag,int spr);
link NewNode(char *codice, char *nome, char *classe,int hp,int mp,int atk,int def,int mag,int spr);
link delete_pg(link head,char *codice);
p lettura_inventario(int *n);
opzioni lettura_comando();
void inserimento_item(link head,char *i_nome,char *pg_codice,int n,p inv);
void elimina_item(link head,char *i_nome,char *pg_codice);
void show_pg(link head,char *codice);
void ordina_inventario(p *inventario,int n);
void free_dati(link head);
int main()
{
char codice[N],nome[N],classe[N];
int hp,mp,atk,def,mag,spr,n_elementi;
opzioni scelta;
p inv;
link head=NULL;
head=acquisizione_personaggi(head);
inv=lettura_inventario(&n_elementi);
scelta=lettura_comando();
while(scelta!=fine){
switch(scelta){
  case agg_pers:
       printf("Aggiungere codice univoco perconsaggio: ");
       scanf("%s",codice);
       printf("Aggiungere nome e classe perconsaggio: ");
       scanf("%s%s",nome,classe);
       printf("Aggiungere le 6 stats base perconsaggio: ");
       scanf("%d%d%d%d%d%d",&hp,&mp,&atk,&def,&mag,&spr);
       head=lettura_lista(head,codice,nome,classe,hp,mp,atk,def,mag,spr);
       break;
  case delete_pers:
       printf("Inserire codice personaggio da eliminare del tipo PGXXXX, pg deve essere scritto: ");
       scanf("%s",codice);
       head=delete_pg(head,codice);
       break;
  case agg_equip:
       printf("Inserire nome dell'item corrispondente da aggiungere al pg: ");
       scanf("%s",nome);
       printf("Aggiungere codice univoco perconsaggio: ");
       scanf("%s",codice);
       inserimento_item(head,nome,codice,n_elementi,inv);
       break;
  case delete_equip:
       printf("Inserire nome dell'item da eliminare: ");
       scanf("%s",nome);
       printf("Aggiungere codice univoco perconsaggio: ");
       scanf("%s",codice);
       elimina_item(head,nome,codice);
       break;
  case show_pers:
       printf("Aggiungere codice univoco perconsaggio: ");
       scanf("%s",codice);
       show_pg(head,codice);
       break;
  case err:
    printf("Errore inserimento comando\n");
    break;


}
scelta=lettura_comando();
}
free(inv);
free_dati(head);
return 0;
}
link acquisizione_personaggi(link head){//acquisisco da file la lista dei personaggi
char codice[N],nome[N],classe[N];
int hp,mp,atk,def,mag,spr;
FILE *fp;
fp=fopen("pg.txt","r");
if(fp==NULL)
{
    printf("Errore apertura file personaggi\n");
    exit(EXIT_FAILURE);
}
while(fscanf(fp,"%s %s %s %d %d %d %d %d %d",codice,nome,classe,&hp,&mp,&atk,&def,&mag,&spr)!=EOF){//analizzo la prima riga, chiamo una funzione lettura_lista che inserisce i nuovi dati in un nuovo nodo
head=lettura_lista(head,codice,nome,classe,hp,mp,atk,def,mag,spr);
}
close(fp);
return head;
}

link lettura_lista(link head,char *codice, char *nome, char *classe,int hp,int mp,int atk,int def,int mag,int spr){
link x=head;
if(x==NULL){//se la lista e' vuota creo un nodo
   head=NewNode(codice,nome,classe,hp,mp,atk,def,mag,spr);
}
else{
for(x=head;x!=NULL;x=x->next){
if(strcmp(x->codice,codice)==0){
    printf("Codice gia' presente\n\n");
    return head;
}
if(x->next==NULL){
        x->next=NewNode(codice,nome,classe,hp,mp,atk,def,mag,spr);//quando arrivo a fine lista aggiungo un nodo
        break;
}
}
}
return head;
}

link NewNode(char *codice, char *nome, char *classe,int hp,int mp,int atk,int def,int mag,int spr){//crea il nodo
link x;
x=malloc(sizeof(struct dati));
if(x==NULL)
    exit(EXIT_FAILURE);
strcpy(x->codice,codice);
strcpy(x->nome,nome);
strcpy(x->classe,classe);
x->hp=hp;
x->mp=mp;
x->atk=atk;
x->def=def;
x->mag=mag;
x->spr=spr;
x->hp_f=hp;//queste variabili rappresentano quelle che verranno utilizzate per mostrare le stats effettive
x->mp_f=mp;
x->atk_f=atk;
x->def_f=def;
x->mag_f=mag;
x->spr_f=spr;
x->next=NULL;
x->equip=malloc(sizeof(struct equipaggiamento));
x->equip->n_equip=0;
x->equip->inventory=(struct inventario **)malloc(8*sizeof(struct inventario *));
for(int i=0;i<8;i++){
    x->equip->inventory[i]=NULL;
}
for(int i=0;i<M;i++){
    x->buf[i]==0;
}
return x;
}

p lettura_inventario(int *n){//acquisisco da file l'invetario complessivo e lo inserisco in un vettore di struct
int n_elementi;
p eq;
FILE *fp;
fp=fopen("inventario.txt","r");
if(fp==NULL)
{
    printf("Errore apertura file inventario\n");
    exit(EXIT_FAILURE);
}
fscanf(fp,"%d",&n_elementi);
eq=malloc(n_elementi*sizeof(*eq));
for(int i=0;i<n_elementi;i++){
fscanf(fp,"%s%s%d%d%d%d%d%d",eq[i].nome,eq[i].tipo,&eq[i].hp,&eq[i].mp,&eq[i].atk,&eq[i].def,&eq[i].mag,&eq[i].spr);
}
*n=n_elementi;
return eq;
}


opzioni lettura_comando(){//questa funzione gestisce il menu' dell'utente
char mat[fine+1][N]={"+pg","-pg","+eq","-eq","show","fine","err"};
char scelta[N];
opzioni t;
t=agg_pers;
printf("+pg per aggiungere un personaggio\n-pg per eliminare un personaggio\n+eq per aggiungere un equipaggiamento ad un personaggio\n-eq per eliminare oggetti dall'equipaggiamento\nshow per mostrare le stats di un personaggio\nfine per finire\n");
scanf("%s",scelta);
while(t<err&&strcmp(scelta,mat[t])!=0)
    t++;
return t;
}
link delete_pg(link head,char *codice){//cancella il personaggio corrispondente al codice scritto, se la cancellazIone è in testa opero con un caso diverso spostando la testa sul successivo
link x=head,p=NULL,tmp;
if(x==NULL)
    return NULL;
for(x=head;x!=NULL;p=x,x=x->next){
    if(strcmp(codice,x->codice)==0){
        if(x!=head){
        tmp=x;
        p->next=x->next;
        free(tmp->equip->inventory);
        free(tmp->equip);
        free(tmp);
        printf("Personaggio eliminato\n\n");
        break;
        }
        else{
            tmp=head;
            head=head->next;
            free(tmp->equip->inventory);
            free(tmp->equip);
            free(tmp);
            printf("Personaggio eliminato\n\n");
            break;
        }
    }
}
return head;
}

void inserimento_item(link head,char *i_nome,char *pg_codice,int n,p inv){
 int pos,flag=0;
 link x=head;
 if(x==NULL)
    return NULL;
 for(x=head;x!=NULL;x=x->next){
    if(strcmp(pg_codice,x->codice)==0){//mi fermo al personaggio con il codice corrispondente
      for(int i=0;i<n;i++){//struct di elementi, mi fermo all'item con il nome corrisponndente
        if(strcmp(i_nome,inv[i].nome)==0){
            if(x->equip->n_equip<MAX){//controllo che il personaggio non abbia 8 oggetti equipaggiati
                x->equip->n_equip++;
                for(int j=0;j<x->equip->n_equip;j++){//scandisco il vettore dell'equip, se trovo un null mi salvo la posizione e salto i null successivi
                if(x->equip->inventory[j]==NULL&&flag==0){
                    flag=1;
                    pos=j;
                }
                if(x->equip->inventory[j]!=NULL&&strcmp(x->equip->inventory[j]->nome,i_nome)==0){//controllo nel mentre se l'item fa già parte dell'inventario
                    printf("Item gia' inserito\n\n");
                    flag=1;
                    break;
                }
                if(j==x->equip->n_equip-1){//se sono arrivato a fine inventario allora inserisco nel null trovato l'item, aggiornando le stats
                    printf("Item aggiunto correttamente\n\n");//aggiorno le stats del personaggio verificando che siano tutte positive, altrimento vengono settate a 0;
                    x->equip->inventory[pos]=&inv[i];
                    x->buf[0]+=x->equip->inventory[pos]->hp;
                    x->buf[1]+=x->equip->inventory[pos]->mp;
                    x->buf[2]+=x->equip->inventory[pos]->atk;
                    x->buf[3]+=x->equip->inventory[pos]->def;
                    x->buf[4]+=x->equip->inventory[pos]->mag;
                    x->buf[5]+=x->equip->inventory[pos]->spr;
                    if(x->hp+x->buf[0]>0)
                        x->hp_f=x->hp+x->buf[0];
                    else
                        x->hp_f=0;
                    if(x->mp+x->buf[1]>0)
                        x->mp_f=x->mp+x->buf[1];
                    else
                        x->mp_f=0;
                    if(x->atk+x->buf[2]>0)
                        x->atk_f=x->atk+x->buf[2];
                    else
                        x->atk_f=0;
                    if(x->def+x->buf[3]>0)
                        x->def_f=x->def+x->buf[3];
                    else
                        x->def_f=0;
                    if(x->mag+x->buf[4]>0)
                        x->mag_f=x->mag+x->buf[4];
                    else
                        x->mag_f=0;
                    if(x->mag+x->buf[5]>0)
                        x->spr_f=x->mag+x->buf[5];
                    else
                        x->spr_f=0;
                }
                }
            }
            else{
                printf("L'inventario del personaggio e' pieno, liberare spazio\n");
            }
            break;
        }
        if(i==n-1){
        printf("L'arma inserita non esiste\n");
      }
      }
      break;
    }
    if(x->next==NULL){
        printf("Il personaggio inserito non esiste\n");
    }
 }

}
void elimina_item(link head,char *i_nome,char *pg_codice){
link x=head;
 if(x==NULL)
    return NULL;
 for(x=head;x!=NULL;x=x->next){
  if(strcmp(x->codice,pg_codice)==0){//mi fermo al personaggio con il codice corrispondente
    for(int i=0;i<x->equip->n_equip;i++){
        if(strcmp(x->equip->inventory[i]->nome,i_nome)==0){//mi fermo all'item, dell'equip con il nome inserito
            printf("Ogetto eliminato correttamente\n\n");//aggiorno le stats del personaggio
            x->buf[0]-=x->equip->inventory[i]->hp;
            x->buf[1]-=x->equip->inventory[i]->mp;
            x->buf[2]-=x->equip->inventory[i]->atk;
            x->buf[3]-=x->equip->inventory[i]->def;
            x->buf[4]-=x->equip->inventory[i]->mag;
            x->buf[5]-=x->equip->inventory[i]->spr;
            x->equip->inventory[i]=NULL;//punta a null
            x->equip->n_equip--;
            ordina_inventario(x->equip->inventory,x->equip->n_equip);//shift della parte successiva al null di una posizione a sinistra
            if(x->hp+x->buf[0]>0)
                x->hp_f=x->hp+x->buf[0];
            else
                x->hp_f=0;
            if(x->mp+x->buf[1]>0)
                x->mp_f=x->mp+x->buf[1];
            else
                x->mp_f=0;
            if(x->atk+x->buf[2]>0)
                x->atk_f=x->atk+x->buf[2];
            else
                x->atk_f=0;
            if(x->def+x->buf[3]>0)
                x->def_f=x->def+x->buf[3];
            else
                x->def_f=0;
            if(x->mag+x->buf[4]>0)
                x->mag_f=x->mag+x->buf[4];
            else
                x->mag_f=0;
            if(x->mag+x->buf[5]>0)
                x->spr_f=x->mag+x->buf[5];
            else
                x->spr_f=0;
            break;
        }
        if(i==x->equip->n_equip-1){
            printf("Questo oggetto non fa parte dell'inventario del personaggio\n\n");
        }
        }
     if(x->equip->n_equip==0)
            printf("L'inventario del personaggio e' vuoto \n");
        break;
    }
  if(x->next==NULL){
        printf("Il personaggio inserito non esiste\n\n");
  }
 }
}


 void show_pg(link head,char *codice){
 link x=head;
 if(x==NULL)
    return NULL;
 for(x=head;x!=NULL;x=x->next){
    if(strcmp(x->codice,codice)==0){
    printf("%s %s %d %d %d %d %d %d\n",x->nome,x->classe,x->hp_f,x->mp_f,x->atk_f,x->def_f,x->mag_f,x->spr_f);
    if(x->equip->n_equip>0){
    printf("Inventario:\n");
    for(int i=0;i<x->equip->n_equip;i++){
    if(x->equip->inventory[i]!=NULL){
    printf("%s %s %d %d %d %d %d %d\n",x->equip->inventory[i]->nome,x->equip->inventory[i]->tipo,x->equip->inventory[i]->hp,x->equip->inventory[i]->mp,x->equip->inventory[i]->atk,x->equip->inventory[i]->def,x->equip->inventory[i]->mag,x->equip->inventory[i]->spr);
    }
    }
    printf("\n");
    }
    break;
    }
    if(x->next==NULL){
        printf("Il personaggio inserito non esiste\n\n");
    }
 }
 }
void ordina_inventario(p *inventario,int n){
p tmp;
int flag=0;
for(int i=0;i<n&&flag==0;i++){
    if(inventario[i]==NULL){
        inventario[i]=inventario[i+1];
        inventario[i+1]=NULL;
    }
}
}

void free_dati(link head){
if(head==NULL){
return;
}
free_dati(head->next);
free(head->equip->inventory);
free(head->equip);
free(head);
}

