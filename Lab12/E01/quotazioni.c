#include <stdio.h>
#include <stdlib.h>
#include "quotazioni.h"
struct BST{
day quota;
bst l,r;
int n;
};

static int COMPAREdate(int anno,int mese,int giorno,day nodo);
static void BSTmaxmin(bst h,bst z,float *m,float *M);
static void treeFree(bst h,bst z);

bst BSTinsert(bst h,bst z,int anno,int mese,int giorno,float num,float den,int *flag){
if(h==z){
    *flag=1;
    return NEWBST(anno,mese,giorno,num,den,z,z,1);}
if(COMPAREdate(anno,mese,giorno,h->quota)==0){
    h->quota->num+=num;
    h->quota->den+=den;
    return h;
}
if(COMPAREdate(anno,mese,giorno,h->quota)==1)
    h->r=BSTinsert(h->r,z,anno,mese,giorno,num,den,flag);
else
    h->l=BSTinsert(h->r,z,anno,mese,giorno,num,den,flag);
if(*flag==1)
        h->n++;
return h;
}

static int COMPAREdate(int anno,int mese,int giorno,day nodo){
int data1,data2;
data1=(anno*10000)+(mese*10)+giorno;
data2=(nodo->anno*10000)+(nodo->mese*10)+nodo->giorno;
if(data1==data2)
    return 0;
if(data1>data2)
    return 1;
return -1;
}

bst NEWBST(int anno,int mese,int giorno,int num,int den,bst l,bst r,int n){
bst x;
x=malloc(sizeof(*x));
x->quota=malloc(sizeof(struct daily));
x->quota->anno=anno;
x->quota->mese=mese;
x->quota->giorno=giorno;
x->quota->den=den;
x->quota->num=num;
x->l=l;
x->r=r;
x->n=n;
return x;
}

void BSTprintQUOT(bst h,int anno,int mese,int giorno,bst z){
if(h==z){
    printf("Il titolo non \' quotato in questa data\n");
    return;
}
if(COMPAREdate(anno,mese,giorno,h->quota)==0){
    printf("Il titolo e\' quotato a %.3f\n",h->quota->num/h->quota->den);
    return;}
if(COMPAREdate(anno,mese,giorno,h->quota)==1)
    BSTprintQUOT(h->r,anno,mese,giorno,z);
else
    BSTprintQUOT(h->l,anno,mese,giorno,z);
return;
}

void BSTprint_max_minDATE(bst h,int anno,int mese,int giorno,int anno1,int mese1,int giorno1,bst z,float *m,float *M){
if(h==z)
    return;
if(COMPAREdate(anno,mese,giorno,h->l->quota)==0||COMPAREdate(anno,mese,giorno,h->l->quota)==-1)
    BSTprint_max_minDATE(h->l,anno,mese,giorno,anno1,mese1,giorno1,z,m,M);
if(*m==-1||h->quota->num/h->quota->den<*m)
        *m=h->quota->num/h->quota->den;
if(*M==-1||h->quota->num/h->quota->den>*M)
        *M=h->quota->num/h->quota->den;
if(COMPAREdate(anno1,mese1,giorno1,h->r->quota)==0||COMPAREdate(anno1,mese1,giorno1,h->r->quota)==1)
    BSTprint_max_minDATE(h->r,anno,mese,giorno,anno1,mese1,giorno1,z,m,M);
}

void BSTwrap(bst h,bst z){
float min,max;
min=-1;
max=-1;
BSTmaxmin(h,z,&min,&max);
printf("Quotazione minima: %.3f\n",min);
printf("Quotazione massima: %.3f\n",max);
}

static void BSTmaxmin(bst h,bst z,float *m,float *M){
if(h==z)
    return;
BSTmaxmin(h->l,z,m,M);
if(*m==-1||h->quota->num/h->quota->den<*m)
        *m=h->quota->num/h->quota->den;
if(*M==-1||h->quota->num/h->quota->den>*M)
        *M=h->quota->num/h->quota->den;
BSTmaxmin(h->r,z,m,M);
return;
}

void LENGHTminmax(bst h,float *lmin,float *lmax,bst z,int cont){
if(h==z){
    if(cont>*lmax||*lmax==-1)
       *lmax=cont;
    if(cont<*lmin||*lmin==-1)
        *lmin=cont;
    return;
}
LENGHTminmax(h->l,lmin,lmax,z,cont+1);
LENGHTminmax(h->r,lmin,lmax,z,cont+1);
return;
}

bst PartRwrapp(bst h){
return PartR(h,(h->n+1)/2-1);
}

bst PartR(bst h,int mediana){
int t=h->l->n;
if(t>mediana){
    h->l=PartR(h->l,mediana);
    h=RotR(h);
}
if(t<mediana){
    h->r=PartR(h->r,mediana-t-1);
    h=RotL(h);
}
return h;
}

bst RotR(bst h){
bst temp;
temp=h->l;
h->l=temp->r;
temp->r=h;
temp->n=h->n;
h->n=h->l->n+h->r->n+1;
return temp;
}

bst RotL(bst h){
bst temp;
temp=h->r;
h->r=temp->l;
temp->l=h;
temp->n=h->n;
h->n=h->l->n+h->r->n+1;
return temp;
}
void BSTprintROOT(bst h){
printf("%d/%d/%d\n",h->quota->anno,h->quota->mese,h->quota->giorno);
}

void freeBST(bst h,bst z){
if(h==NULL)
    return;
treeFree(h,z);
free(h);
}

static void treeFree(bst h,bst z){
if(h==z)
    return;
treeFree(h->l,z);
treeFree(h->r,z);
free(h);
}
