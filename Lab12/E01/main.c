#include <stdio.h>
#include <stdlib.h>
#include "titoli.h"
#include "quotazioni.h"
#define NFILE 31
int main()
{
    int scelta,anno,mese,giorno,soglia,lmin,lmax;
    char n_file[NFILE],tito[MAX];
    link lista=NULL;
    link temp;
    FILE *fp;
    printf("-0 per aggiungere contenuto di un file\n-1 Ricerca dato un titolo di una quotazione in una certa data\n-2 Ricerca dato un titolo di quot max e min tra 2 date\n-3 Ricerca dato un titolo della quot max e min\n-4 Bilanciamento BST dato un titolo\n-5> fine\n");
    scanf("%d",&scelta);
    while(scelta<5){
        switch(scelta){
           case 0:
            printf("Inserire nome file: ");
            scanf("%s",n_file);
            fp=fopen(n_file,"r");
            lista=acquisizione(fp,lista);
            break;
           case 1:
             printf("Inserire codice titolo: ");
             scanf("%s",tito);
             temp=SEARCHtitolo(tito,lista);
             if(temp==NULL){
                printf("Titolo non presente\n");
                break;
             }
             printf("Inserire data aaaa/mm/gg: ");
             scanf("%d %d %d",&anno,&mese,&giorno);
             BSTprintQUOTwrapp(temp,anno,mese,giorno);
            break;
           case 2:
             printf("Inserire codice titolo: ");
             scanf("%s",tito);
             temp=SEARCHtitolo(tito,lista);
             if(temp==NULL)
                printf("Titolo non presente\n");
             else
                printbyDATE(temp);
            break;
           case 3:
             printf("Inserire codice titolo: ");
             scanf("%s",tito);
             temp=SEARCHtitolo(tito,lista);
             if(temp==NULL)
                printf("Titolo non presente\n");
             else
                printALLT(temp);
            break;
           case 4:
             printf("Inserire codice titolo: ");
             scanf("%s",tito);
             temp=SEARCHtitolo(tito,lista);
             if(temp==NULL)
                printf("Titolo non presente\n");
             else{
             printf("Inserire soglia : ");
             scanf("%d",&soglia);
             LENGHTminmaxWrapp(temp,soglia);
             }
            break;
        }
        printf("-0 per aggiungere contenuto di un file\n-1 Ricerca dato un titolo di una quotazione in una certa data\n-2 Ricerca dato un titolo di quot max e min tra 2 date\n-3 Ricerca dato un titolo della quot max e min\n-4 Bilanciamento BST dato un titolo\n-5> fine\n");
        scanf("%d",&scelta);
    }
    freedati(lista);
    return 0;
}
