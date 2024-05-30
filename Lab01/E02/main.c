#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 30
#define L 200
#define MAX_C 101

typedef struct
{
 char codice[N],caratteri[N];
}dizionario;

int acquisizione_diz(dizionario righe[L]);
void modifica_parola(char parola[N],dizionario righe[L], int nr);

int main()
{
    int n_righe,lunghezza_riga,i,j,c,lunghezza;
    char riga[MAX_C],parola[N],parola_codificata[N];
    dizionario righe[L];//suppongo che il dizionario abbia massimo 200 parole
    FILE *fp1;//sorgente
    FILE *fp2;//ricondizionato
    fp1=fopen("sorgente.txt","r");
    fp2=fopen("ricondizionato.txt","w");
    if (fp1==NULL)
    {
        printf("Errore apertura sorgente\n");
        return 2;
    }
    if (fp2==NULL)
    {
        printf("Errore apertura ricondizionato\n");
        return 2;
    }
    n_righe=acquisizione_diz(righe);
    c=0;//indice caratteri della stringa parola
    while (fgets(riga,MAX_C,fp1)!=NULL)
    {
    for (i=0;i<strlen(riga);i++)//scandisco tutta la riga
    {
        if(riga[i]!=' '&&riga[i]!='\0')//se il carattere è diverso da spazio o \0 lo copio in un vettore di caratteri
        {
            parola[c]=riga[i];
            c++;
            if (riga[i+1]==' '||riga[i+1]=='\0')
            {
                parola[c]='\0';//rendo il vettore di caratteri una stringa
                modifica_parola(parola, righe,n_righe);
                fprintf(fp2,"%s",parola);
                printf("%s",parola);
                lunghezza=strlen(parola);//torno a considerare 'parola' come un vettore di caratter e non di stringhe,serve poi per ripulirlo dopo aver modificato la 'parola'
                parola[lunghezza]='a';
                c=0;
            }
        }
        if (riga[i]==' ')//se è presente lo spazio, stampo nel file uno spazio.
        {
            fprintf(fp2," ");
            printf(" ");
            c=0;//ritorna a 0 per poter ricominciare a copiare da capo.

        }
        if (riga[i]=='\0')
        {
            fprintf(fp2,"\n");
            printf("\n");
            c=0;

        }
    }
    }
    fclose(fp1);
    fclose(fp2);
    system ("PAUSE");
}

int acquisizione_diz(dizionario righe[L])
{
   int nr;
   FILE *fp;
   fp=fopen("dizionario.txt","r");
   if(fp==NULL)
   {
       printf("Errore apertura dizionario\n");
       exit(EXIT_FAILURE);
   }
   fscanf(fp,"%d",&nr);
   for(int i=0;i<nr;i++)
   {
       fscanf(fp,"%s%s",righe[i].codice,righe[i].caratteri);
   }
   fclose(fp);
   return nr;
}

void modifica_parola(char parola[N],dizionario righe[L], int nr)
{
  int indice=-1,flag=0,indice_inizio,indice_fine;
  int controllo=0;//serve per ricercare gli indici
  char s1[N],s2[N];//sfrutto due stringhe per codificare il tutto.
  for(int i=0;i<nr&&flag==0;i++)
  {
      if(strstr(parola,righe[i].caratteri)!=NULL)//trovata una corrispondenza
      {
          flag=1;
          indice=i;
      }
  }
  if(indice!=-1)
  {//non è stata trovata alcuna corrispondenza
  flag=0;
  //cerco gli indici di inizio e fine caratteri
  for(int i=0;i<strlen(parola)-strlen(righe[indice].caratteri)+1&&flag==0;i++)
  {
      controllo=0;
      for(int j=i;j<strlen(righe[indice].caratteri)+i;j++)
      {
        if(parola[j]==righe[indice].caratteri[controllo])
            controllo++;
            else
                controllo=0;
        if(controllo==strlen(righe[indice].caratteri))//ho trovato gli indici
        {
           indice_inizio=i;
           indice_fine=j;
           flag=1;
        }
      }
  }
  controllo=0;
  for(int i=0;i<strlen(parola);i++)//copio su una stringa i valori prima dell'indice di inizio dei caratteri da sostituire/ faccio lo stesso con gli indice dopo indice fine caratteri
  {
    if(i<indice_inizio)
  {
      s1[controllo]=parola[i];
      controllo++;
  }
  if(i==indice_inizio)
  {
      s1[controllo]='\0';
      strcat(s1,righe[indice].codice);//alla stringa che contiene i caratteri precedentemente copiati viene affiancata la stringa corrispondente al codice.
      controllo=0;
  }
  if(i>indice_fine)
  {
      s2[controllo]=parola[i];
      controllo++;
  }
  if(i==strlen(parola)-1)
  {
      s2[controllo]='\0';
      strcat(s1,s2);//unisco la stringa s1=caratteri prima di inizio_indice+codice con s2 che contiene la parte destra della parola, quella che non va modificata
  }
  }
  strcpy(parola,s1);
  }
}
