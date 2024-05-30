#include <stdio.h>
#include <stdlib.h>
#define N 101
#define MAX 5
#define N_DIAG 3
typedef struct dati *p;
typedef struct diagonali *diagon;
struct dati{
char nome[N];
int tipo,d_in,d_us,req,fin,diff;
float val;
};
struct diagonali{
float punti;
p *ele;
int n_ele;
int dif;
};
struct wrapper{
int n_diag,cap;
diagon d;
};
struct prog{
float punti;
struct diagonali **dg;
int dif;
};
p acquisizione_file(int *n);
void diag_possibili(int n,int DD,p elementi,struct wrapper *diag,struct diagonali *tmp,int pos);
void prog_possibili(int pos,struct prog *tmp_prog,struct prog *best_prog,struct wrapper diag,int DP,float *max,int start);
void diag_insert(struct wrapper *diag,struct diagonali tmp);
int check_el(struct diagonali tmp,int pos,int n,p elementi,int DD);
int check_diag(struct diagonali tmp,int *flag1,int *flag2,int *flag3,int DD);
int check_prog(struct prog *tmp);
void punti_bonus(struct wrapper *diag);
void swap_prog(struct prog tmp,struct prog *best_prog);

int main()
{
    int n,DD,DP,pos=0,start=0,a,b;
    float max=-1;
    p elementi;
    struct wrapper diag;
    struct diagonali tmp;
    struct prog tmp_prog;
    struct prog best_prog;
    elementi=acquisizione_file(&n);
    printf("DD: \n");
    scanf("%d",&DD);
    diag.n_diag=0;
    diag.cap=0;
    tmp.ele=(struct dati **)malloc(sizeof(struct dati *)*MAX);
    for(int i=0;i<MAX;i++)
        tmp.ele[i]=NULL;
    tmp.punti=0;
    tmp.n_ele=0;
    tmp.dif=0;
    diag_possibili(n,DD,elementi,&diag,&tmp,pos);
    printf("DP: \n");
    scanf("%d",&DP);
    tmp_prog.dg=(struct diagonali **)malloc(sizeof(struct diagonali *));
    best_prog.dg=(struct diagonali **)malloc(sizeof(struct diagonali *));
    for(int i=0;i<N_DIAG;i++){
     tmp_prog.dg[i]=NULL;
     best_prog.dg[i]=NULL;
     }
    prog_possibili(pos,&tmp_prog,&best_prog,diag,DP,&max,start);
    printf("Miglior programma\n");
    printf("PUNTI %.2f\n",best_prog.punti);
    return 0;
}

p acquisizione_file(int *n){
int num;
p dati;
FILE *fp;
fp=fopen("elementi.txt","r");
if(fp==NULL){
    printf("Errore apertura file\n");
    exit(EXIT_FAILURE);
}
fscanf(fp,"%d",&num);
*n=num;
dati=malloc(sizeof(*dati)*num);
for(int i=0;i<num;i++){
    fscanf(fp,"%s%d%d%d%d%d%f%d",dati[i].nome,&dati[i].tipo,&dati[i].d_in,&dati[i].d_us,&dati[i].req,&dati[i].fin,&dati[i].val,&dati[i].diff);
}
return dati;
}

void diag_possibili(int n,int DD,p elementi,struct wrapper *diag,struct diagonali *tmp,int pos){
int flag1=0,flag2=0,flag3=0;
if(pos!=0){
if(check_diag(*tmp,&flag1,&flag2,&flag3,DD)){
    diag_insert(diag,*tmp);
    punti_bonus(diag);
    }
if((flag1==1||flag2==1)||flag3==1)
    return;
}
  for(int i=0;i<n;i++){
    if(check_el(*tmp,pos,i,elementi,DD)){
       tmp->ele[pos]=&elementi[i];
       tmp->punti+=elementi[i].val;
       tmp->dif+=elementi[i].diff;
       tmp->n_ele++;
       diag_possibili(n,DD,elementi,diag,tmp,pos+1);
       tmp->punti=tmp->punti-elementi[i].val;
       tmp->dif=tmp->dif-elementi[i].diff;
       tmp->n_ele--;
       tmp->ele[pos]=NULL;
  }
}
}

int check_diag(struct diagonali tmp,int *flag1,int *flag2,int *flag3,int DD){
int fl1=0,fl2=0,fl3=0;
if(tmp.n_ele==MAX-1)
        fl1=1;
*flag1=fl1;
if(tmp.ele[tmp.n_ele-1]->fin==1)
    fl2=1;
*flag2=fl2;
if(tmp.punti==DD)
    fl3=1;
*flag3=fl3;
for(int i=0;i<tmp.n_ele;i++)
    if(tmp.ele[i]->tipo==2||tmp.ele[i]->tipo==1)
       return 1;
return 0;
}

int check_el(struct diagonali tmp,int pos,int n,p elementi,int DD){
if(pos==0){
    if(elementi[n].d_in==1)
        if(elementi[n].req==0)
           if(elementi[n].diff<=DD)
              return 1;
return 0;
}
if(pos!=0)
    if(elementi[n].d_in==tmp.ele[pos-1]->d_us)
       if(elementi[n].diff+tmp.dif<=DD)
          return 1;
return 0;
}

void diag_insert(struct wrapper *diag,struct diagonali tmp){
if(diag->n_diag==0){
    diag->d=(struct diagonali *)malloc(sizeof(struct diagonali ));
    if(diag->d==NULL)
       printf("Errore\n");
    diag->d[0]=tmp;
    diag->n_diag++;
    diag->cap=1;
    return;
}
else{
    if(diag->cap==diag->n_diag){
       diag->d=(struct diagonali *)realloc(diag->d,2*diag->n_diag*sizeof(struct diagonali ));
       if(diag->d==NULL)
        printf("Errore\n");
       diag->cap=diag->cap*2;
    }
    diag->d[diag->n_diag]=tmp;
    diag->n_diag++;
}
}

void punti_bonus(struct wrapper *diag){
if(diag->d[diag->n_diag-1].ele[diag->d[diag->n_diag-1].n_ele-1]->val==8.0)
   diag->d[diag->n_diag-1].punti=diag->d[diag->n_diag-1].punti*1.5;
}

void prog_possibili(int pos,struct prog *tmp_prog,struct prog *best_prog,struct wrapper diag,int DP,float *max,int start){
if(pos==N_DIAG){
   if(tmp_prog->punti>*max&&tmp_prog->dif<=DP)
      if(check_prog(tmp_prog)){
         swap_prog(*tmp_prog,best_prog);
         *max=tmp_prog->punti;
      }
   return;
}
for(int i=start;i<diag.n_diag;i++){
    tmp_prog->dg[pos]=&diag.d[i];
    tmp_prog->dif+=diag.d[i].dif;
    tmp_prog->punti+=diag.d[i].punti;
    if(tmp_prog->dif<=DP)
        prog_possibili(pos+1,tmp_prog,best_prog,diag,DP,max,start);
    tmp_prog->dif-=diag.d[i].dif;
    tmp_prog->punti-=diag.d[i].punti;
    tmp_prog->dg[pos]=NULL;
    start++;
}
}

void swap_prog(struct prog tmp,struct prog *best_prog){
best_prog=&tmp;
}

int check_prog(struct prog *tmp){
int flag1=0,flag2=0,flag3=0;
for(int i=0;i<N_DIAG-1;i++){
    for(int j=0;j<tmp->dg[i]->n_ele;j++){
        if(tmp->dg[i]->ele[j]->tipo==1)
            flag1=1;
        if(tmp->dg[i]->ele[j]->tipo==2)
            flag2=1;
        if(j!=0)
                if(tmp->dg[i]->ele[j]->tipo==1||tmp->dg[i]->ele[j]->tipo==2)
                   if(tmp->dg[i]->ele[j-1]->tipo==1||tmp->dg[i]->ele[j-1]->tipo==2)
                      flag3=1;
    }
}
if((flag1==1&&flag2==1)&&flag3==1)
    return 1;
return 0;
}
