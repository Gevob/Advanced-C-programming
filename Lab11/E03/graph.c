#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "STlabel.h"
typedef struct node *link;
struct node{
int v;
int wt;
link next;
};
struct graph{
int V;
int E;
int **mat;
st vertici;
link *list;
link z;
};


Graph GRAPHload(FILE *fp){
char label1[MAX],label2[MAX],label3[MAX],label4[MAX];
Graph G;
FILE *fp1;
int wt,ind1,ind2;
G=malloc(sizeof(*G));
G->vertici=STinit();
while(fscanf(fp,"%s %s %s %s %d",label1,label2,label3,label4,&wt)!=EOF){
 STinsert(G->vertici,label1);
 STinsert(G->vertici,label3);
}
close(fp);
STBubble(G->vertici);
G->V=STsize(G->vertici);
G->E=0;
G->mat=GRAPHmat(G->V,G->V,0);
fp1=fopen("grafo.txt","r");
while(fscanf(fp1,"%s %s %s %s %d",label1,label2,label3,label4,&wt)!=EOF){
  ind1=STgetindex(G->vertici,label1);
  ind2=STgetindex(G->vertici,label3);
  if(ind1>=0&&ind1>=0)
    GRAPHinsertE(G,ind1,ind2,wt);
}
return G;
}

int **GRAPHmat(int r,int c,int val){
int **mat=malloc(sizeof(int *)*r);
for(int i=0;i<r;i++)
    mat[i]=malloc(sizeof(int)*c);
for(int i=0;i<r;i++)
    for(int j=0;j<c;j++)
        mat[i][j]=val;
return mat;
}

void GRAPHinsertE(Graph G,int i,int j,int wt){
if(G->mat[i][j]==0){
    G->E++;
    G->mat[i][j]=wt;
    G->mat[j][i]=wt;
}
return;
}
void GRAPTHprint(Graph G,FILE *fp){
for(int i=0;i<G->V;i++){
   fprintf(fp,"Vertice #%d\n",i+1);
   for(int j=0;j<G->V;j++){
       if(G->mat[i][j]!=0){
          fprintf(fp,"%s------%s weight %d\n",STgetnamebyindex(G->vertici,i),STgetnamebyindex(G->vertici,j),G->mat[i][j]);
       }
   }
}
}
void GRAPH3v(Graph G,char *vertice1,char *vertice2,char *vertice3,FILE *fp){
int ind1,ind2,ind3;
ind1=STgetindex(G->vertici,vertice1);
ind2=STgetindex(G->vertici,vertice2);
ind3=STgetindex(G->vertici,vertice3);
if(ind1!=-1&&(ind2!=-1&&ind3!=-1)){
    if(G->mat[ind1][ind2]!=0)
       if(G->mat[ind2][ind3]!=0)
          if(G->mat[ind1][ind3]!=0){
             fprintf(fp,"I 3 vertici costituiscono un grafo completo\n");
             return;}
fprintf(fp,"I 3 vertici non costituiscono un grafo completo\n");
}
else
   fprintf(fp,"Errore inserimento dati, vertici non presenti\n");
return;
}

void GRAPHlistinit(Graph G){
G->list=malloc(sizeof(link)*G->V);
G->z=NEW(-1,-1,NULL);
for(int i=0;i<G->V;i++)
    G->list[i]=G->z;
for(int i=0;i<G->V;i++){
    for(int j=G->V-1;j>=0;j--){
        if(G->mat[i][j]!=0){
            G->list[i]=NEW(j,G->mat[i][j],G->list[i]);
        }
    }
}
return;
}

link NEW(int v,int wt,link next){
link x=malloc(sizeof(*x));
x->next=next;
x->v=v;
x->wt=wt;
return x;
}

/*void EDGEListprint(Graph G,FILE *fp){
for(int i=0;i<G->V;i++){
  fprintf(fp,"Vertice #%d\n",i+1);
  for(link x=G->list[i];x->next!=NULL;x=x->next)
      fprintf(fp,"%s------%s weight %d\n",STgetnamebyindex(G->vertici,i),STgetnamebyindex(G->vertici,x->v),x->wt);
}
}*/

void EDGE3v(Graph G,char *vertice1,char *vertice2,char *vertice3,FILE *fp){
int ind1,ind2,ind3;
ind1=STgetindex(G->vertici,vertice1);
ind2=STgetindex(G->vertici,vertice2);
ind3=STgetindex(G->vertici,vertice3);
if(ind1!=-1&&(ind2!=-1&&ind3!=-1)){
   if(EDGEvertSearch(G,ind1,ind2,ind3))
      if(EDGEvertSearch(G,ind2,ind1,ind3))
        if(EDGEvertSearch(G,ind3,ind1,ind2)){
           fprintf(fp,"I 3 vertici costituiscono un grafo completo\n");
           return;}
fprintf(fp,"I 3 vertici non costituiscono un grafo completo\n");
}
else
   fprintf(fp,"Errore inserimento dati, vertici non presenti\n");
return;
}

int EDGEvertSearch(Graph G,int ind1,int ind2,int ind3){
int flag1=0,flag2=0;
for(link x=G->list[ind1];x->next!=NULL;x=x->next){
    if(x->v==ind2)
        flag1=1;
    if(x->v==ind3)
        flag2=1;
}
if(flag1==1&&flag2==1)
    return 1;
return 0;
}

void GRAPHfree(Graph G,int flag){
link next;
for(int i=0;i<G->V;i++)
    free(G->mat[i]);
free(G->mat);
STfree(G->vertici);
if(flag==1){
    for(int i=0;i<G->V;i++)
      for(link x=G->list[i];x!=G->z;x=next){
        next=x->next;
        free(x);
    }
    free(G->list);
    free(G->z);
}
free(G);
}
