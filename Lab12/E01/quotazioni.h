#ifndef QUOTAZIONI_H_INCLUDED
#define QUOTAZIONI_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
typedef struct BST *bst;
typedef struct daily *day;
struct daily{
int mese,anno,giorno;
float num,den;
}daily;

bst NEWBST(int anno,int mese,int giorno,int num,int den,bst l,bst r,int n);
bst BSTinsert(bst root,bst z,int anno,int mese,int giorno,float num,float den,int *flag);
void BSTprintQUOT(bst h,int anno,int mese,int giorno,bst z);
void BSTprint_max_minDATE(bst h,int anno,int mese,int giorno,int anno1,int mese1,int giorno1,bst z,float *m,float *M);
void BSTwrap(bst h,bst z);
void LENGHTminmax(bst h,float *lmin,float *lmax,bst z,int cont);
bst PartRwrapp(bst h);
void freeBST(bst h,bst z);
bst PartR(bst h,int mediana);
bst RotR(bst h);
bst RotL(bst h);
void BSTprintROOT(bst h);
#endif // QUOTAZIONI_H_INCLUDED
