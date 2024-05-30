#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
typedef struct graph *Graph;
typedef struct node *link;

Graph GRAPHload(FILE *fp);
int **GRAPHmat(int r,int c,int val);
void GRAPHfree(Graph G,int flag);
void GRAPHinsertE(Graph G,int i,int j,int wt);
void GRAPTHprint(Graph G,FILE *fp);
void GRAPH3v(Graph G,char *vertice1,char *vertice2,char *vertice3,FILE *fp);
void GRAPHlistinit(Graph G);
link NEW(int v,int wt,link next);
/*void EDGEListprint(Graph G,FILE *fp);*/
void EDGE3v(Graph G,char *vertice1,char *vertice2,char *vertice3,FILE *fp);
int EDGEvertSearch(Graph G,int ind1,int ind2,int ind3);
#endif // GRAPH_H_INCLUDED
