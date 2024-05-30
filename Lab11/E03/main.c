#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "STlabel.h"

int main()
{
char nome1[MAX],nome2[MAX],nome3[MAX];
int s,flag=0,s2;
Graph G;
FILE *fp;
fp=fopen("grafo.txt","r");
G=GRAPHload(fp);
printf("-0 Elenco Alfabetico vertici\n-1 Check 3 vertici grafo completo\n-2 Inizializzazione lista\n-3 Fine\n");
scanf("%d",&s);
while(s<3){
    switch(s){
       case 0:
             GRAPTHprint(G,stdout);
             break;
       case 1:
             printf("Inserire vertice: ");
             scanf("%s",nome1);
             printf("Inserire vertice: ");
             scanf("%s",nome2);
             printf("Inserire vertice: ");
             scanf("%s",nome3);
             if(flag==0){
             GRAPH3v(G,nome1,nome2,nome3,stdout);
             }
             if(flag==1){
                printf("1 per cercare con la matrice di adiancenza\n2 per cercare con la lista di adiacenza\n");
                scanf("%d",&s2);
                if(s2==1)
                   GRAPH3v(G,nome1,nome2,nome3,stdout);
                if(s2==2)
                    EDGE3v(G,nome1,nome2,nome3,stdout);
             }
             break;
       case 2:
             if(flag==1)
                printf("Lista gia inizializzata\n");
             if(flag==0){
             GRAPHlistinit(G);
             flag=1;
             printf("Lista inizializzata\n"); }
             break;
    }
printf("-0 Elenco Alfabetico vertici\n-1 Check 3 vertici grafo completo\n-2 Inizializzazione lista\n-3 Fine\n");
scanf("%d",&s);
}
GRAPHfree(G,flag);
return 0;
}
