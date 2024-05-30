#ifndef TITOLI_H_INCLUDED
#define TITOLI_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define MAX 21
#include "quotazioni.h"
typedef struct{
int mese,giorno,anno;
}data;

typedef struct titolo *tit;
typedef struct nodo_lista *link;

link acquisizione(FILE *fp,link lista);
link SEARCHtitolo(char *titolo,link lista);
void freedati(link lista);
void printbyDATE(link temp);
void printALLT(link temp);
void BSTprintQUOTwrapp(link temp,int anno,int mese,int giorno);
void LENGHTminmaxWrapp(link temp,int n);
#endif // TITOLI_H_INCLUDED
