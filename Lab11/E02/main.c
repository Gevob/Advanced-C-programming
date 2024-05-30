#include <stdio.h>
#include <stdlib.h>
#define N 101
#define MAX 5
#define N_DIAG 3
typedef struct dati *p;
struct dati{
char nome[N];
int tipo,d_in,d_us,req,fin,diff;
float val,valore_spec;
};
p acquisizione_file(int *n, struct dati ***el);
void Bubble(struct dati **el,int n);
void riempimento(struct dati **mat,int *dif_d,p *el,int n,int *flag,int *dif_p,int *d_ele);
int check_el(int k,int n,p *el,int i,int j,int *dif_d,int DP,struct dati **mat,int *flag,int *dif_p);
struct dati **config();
void change_dif_p(int d,int DP,int *dif_p,int *flag);
void stampa(struct dati **mat,int *d_ele);
int main()
{
    int n,dif_d[N_DIAG],dif_p[N_DIAG],flag[N_DIAG],d_ele[N_DIAG];
    p elementi;
    p *el;
    struct dati **mat;
    elementi=acquisizione_file(&n,&el);
    Bubble(el,n);
    for(int i=0;i<n;i++)
        printf("%s  %.3f\n",el[i]->nome,el[i]->valore_spec);
    mat=config();
    riempimento(mat,dif_d,el,n,flag,dif_p,d_ele);
    stampa(mat,d_ele);
    return 0;
}

p acquisizione_file(int *n,struct dati ***el){
int num;
p *vet;
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
vet=malloc(sizeof(struct dati *)*num);
*el=(struct dati **)malloc(sizeof(struct dati *)*num);
for(int i=0;i<num;i++){
    fscanf(fp,"%s%d%d%d%d%d%f%d",dati[i].nome,&dati[i].tipo,&dati[i].d_in,&dati[i].d_us,&dati[i].req,&dati[i].fin,&dati[i].val,&dati[i].diff);
    dati[i].valore_spec=dati[i].val/dati[i].diff;
    vet[i]=&dati[i];
}
*el=vet;
close(fp);
return dati;
}

void Bubble(struct dati **el,int n){
p tmp;
for(int i=0;i<n-1;i++)
  for(int j=0;j<n-i-1;j++){
     if(el[j]->valore_spec<el[j+1]->valore_spec){
        tmp=el[j];
        el[j]=el[j+1];
        el[j+1]=tmp;
     }
  }
return ;
}

struct dati **config(){
struct dati **mat;
mat=(struct dati **)malloc(sizeof(struct dati *)*N_DIAG);
for(int i=0;i<MAX;i++){
    mat[i]=malloc(sizeof(struct dati)*MAX);}
return mat;
}



void riempimento(struct dati **mat,int *dif_d,p *el,int n,int *flag,int *dif_p,int *d_ele){
int DD,DP;
printf("Inserire DD: ");
scanf ("%d",&DD);
printf("\nInserire DP: ");
scanf("%d",&DP);
for(int i=0;i<N_DIAG;i++){
    dif_d[i]=DD;
    dif_p[i]=0;
    flag[i]=0;
    d_ele[i]=0;}
for(int i=0;i<MAX;i++){
    for(int j=0;j<N_DIAG;j++){
         for(int k=0;k<n;k++)
            if(flag[j]==0)
              if(check_el(k,n,el,i,j,dif_d,DP,mat,flag,dif_p)){
                 mat[j][i]=*el[k];
                 d_ele[j]++;
                 break;
            }
     }
   }
}

int check_el(int k,int n,p *el,int i,int j,int *dif_d,int DP,struct dati **mat,int *flag,int *dif_p){
if(i==0){
    if(j==0)
      if((el[k]->d_in==1&&el[k]->req==0)&&(el[k]->diff<=dif_d[0]&&el[k]->tipo==2)){
        dif_d[0]-=el[k]->diff;
        dif_p[0]+=el[k]->diff;
        return 1;}
    if(j==1)
      if((el[k]->d_in==1&&el[k]->req==0)&&(el[k]->diff<=dif_d[1]&&el[k]->tipo==2)){
        dif_d[1]-=el[k]->diff;
        dif_p[1]+=el[k]->diff;
        return 1;}
    if(j==2)
       if((el[k]->d_in==1&&el[k]->req==0)&&((el[k]->diff<=dif_d[2]&&el[k]->tipo==0)&&el[k]->d_us==0)){
        dif_d[2]-=el[k]->diff;
        dif_p[2]+=el[k]->diff;
        return 1;}
return 0;
}
if(i==1){
    switch (j){
        case 0:
            if((el[k]->d_in==mat[j][i-1].d_us&&el[k]->tipo!=0)&&el[k]->diff<=dif_d[0]){
                dif_d[0]-=el[k]->diff;
                dif_p[0]+=el[k]->diff;
                if((dif_d[0]==0||el[k]->fin==1)||dif_p[0]>=DP/3){
                    flag[0]=1;
                    change_dif_p(0,DP,dif_p,flag);
                }
                return 1;}
            return 0;
            break;
        case 1:
            if(el[k]->d_in==mat[j][i-1].d_us&&el[k]->diff<=dif_d[1]){
                dif_d[1]-=el[k]->diff;
                dif_p[1]+=el[k]->diff;
                if((dif_d[1]==0||el[k]->fin==1)||dif_p[1]>=DP/3){
                    flag[1]=1;
                    change_dif_p(1,DP,dif_p,flag);
                    }
                return 1;}
            return 0;
            break;
        case 2:
            if((el[k]->d_in==mat[j][i-1].d_us&&el[k]->diff<=dif_d[2])&&(el[k]->tipo==1&&el[k]->diff<(dif_d[2]-dif_p[2]))){
                dif_d[2]-=el[k]->diff;
                dif_p[2]+=el[k]->diff;
                if((dif_d[2]==0||el[k]->fin==1)||dif_p[2]>=DP/3){
                    flag[2]=1;
                    change_dif_p(2,DP,dif_p,flag);
                    }
                return 1;}
            return 0;
            break;
        }
}
if(i>1){
    switch (j){
        case 0:
            if(el[k]->d_in==mat[j][i-1].d_us&&el[k]->diff<=dif_d[0]){
                dif_d[0]-=el[k]->diff;
                dif_p[0]+=el[k]->diff;
                if((dif_d[0]==0||el[k]->fin==1)||dif_p[0]>=DP/3){
                    flag[0]=1;
                    change_dif_p(0,DP,dif_p,flag);
                }
                return 1;}
            return 0;
            break;
        case 1:
            if(el[k]->d_in==mat[j][i-1].d_us&&el[k]->diff<=dif_d[1]){
                dif_d[1]-=el[k]->diff;
                dif_p[1]+=el[k]->diff;
                if((dif_d[1]==0||el[k]->fin==1)||dif_p[1]>=DP/3){
                    flag[1]=1;
                    change_dif_p(1,DP,dif_p,flag);
                    }
                return 1;}
            return 0;
            break;
        case 2:
            if(el[k]->d_in==mat[j][i-1].d_us&&el[k]->diff<=dif_d[2]){
                dif_d[2]-=el[k]->diff;
                dif_p[2]+=el[k]->diff;
                if((dif_d[2]==0||el[k]->fin==1)||dif_p[2]>=DP/3){
                    flag[2]=1;
                    change_dif_p(2,DP,dif_p,flag);
                    }
                return 1;}
            return 0;
            break;
        }
}
return 0;
}

void change_dif_p(int d,int DP,int *dif_p,int *flag){
switch (d){
case 0:
    if(dif_p[d]<DP/3){
        if(flag[1]==0&&flag[2]==0){
            dif_p[1]-=(DP/3-dif_p[d])/2;
            dif_p[2]-=(DP/3-dif_p[d])/2;
        }
        else if(flag[1]==1)
            dif_p[2]-=DP/3-dif_p[d];
        else if(flag[2]==1)
            dif_p[1]-=DP/3-dif_p[d];
    }
    if(dif_p[d]>DP/3){
       if(flag[1]==0&&flag[2]==0){
            dif_p[1]+=(dif_p[d]-DP/3)/2;
            dif_p[2]+=(dif_p[d]-DP/3)/2;
        }
        else if(flag[1]==1)
            dif_p[2]+=dif_p[d]-DP/3;
        else if(flag[2]==1)
            dif_p[1]+=dif_p[d]-DP/3;
    }
    if(dif_p[1]>=DP/3)
        flag[1]=1;
    if(dif_p[2]>=DP/3)
        flag[2]=1;
    break;
case 1:
        if(dif_p[d]<DP/3){
        if(flag[0]==0&&flag[2]==0){
            dif_p[0]-=(DP/3-dif_p[d])/2;
            dif_p[2]-=(DP/3-dif_p[d])/2;
        }
        else if(flag[0]==1)
            dif_p[2]-=DP/3-dif_p[d];
        else if(flag[2]==1)
            dif_p[0]-=DP/3-dif_p[d];
    }
    if(dif_p[d]>DP/3){
       if(flag[0]==0&&flag[2]==0){
            dif_p[0]+=(dif_p[d]-DP/3)/2;
            dif_p[2]+=(dif_p[d]-DP/3)/2;
        }
        else if(flag[0]==1)
            dif_p[2]+=dif_p[d]-DP/3;
        else if(flag[2]==1)
            dif_p[0]+=dif_p[d]-DP/3;
    }
    if(dif_p[0]>DP/3)
        flag[0]=1;
    if(dif_p[2]>DP/3)
        flag[2]=1;
    break;
case 2:
        if(dif_p[d]<DP/3){
        if(flag[0]==0&&flag[1]==0){
            dif_p[0]-=(DP/3-dif_p[d])/2;
            dif_p[1]-=(DP/3-dif_p[d])/2;
        }
        else if(flag[0]==1)
            dif_p[1]-=DP/3-dif_p[d];
        else if(flag[1]==1)
            dif_p[0]-=DP/3-dif_p[d];
    }
    if(dif_p[d]>DP/3){
       if(flag[0]==0&&flag[1]==0){
            dif_p[0]+=(dif_p[d]-DP/3)/2;
            dif_p[1]+=(dif_p[d]-DP/3)/2;
        }
        else if(flag[0]==1)
            dif_p[1]+=dif_p[d]-DP/3;
        else if(flag[1]==1)
            dif_p[0]+=dif_p[d]-DP/3;
    }
    if(dif_p[0]>DP/3)
        flag[0]=1;
    if(dif_p[1]>DP/3)
        flag[1]=1;
    break;

}

}
void stampa(struct dati **mat,int *d_ele){
for(int i=0;i<N_DIAG;i++){
    printf("DIAG #%d\n",i+1);
    for(int j=0;j<d_ele[i];j++)
        printf("Nome %s Punti %.2f Difficolta %d\n",mat[i][j].nome,mat[i][j].val,mat[i][j].diff);
}
}
