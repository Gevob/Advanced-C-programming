#include <stdio.h>
#include <stdlib.h>
#define N 20
int  conta(char cont[N], int n);
int main()
{
    char str[N];
    int l,n,nss=0,tot=0;
    FILE *fp;
    fp=fopen("testo.txt","r");
    if(fp==NULL)
    {
        printf("Errore apertura file\n");
        return 1;
    }
    else
    {
        printf("Inserire n \n");
        scanf("%d",&n);
     fscanf(fp,"%d",&l);

     for (int i=0;i<=l-1;i++)
     {
         fscanf(fp,"%s",&str);

         printf("%s\n",str);
         nss=conta(str,n);
         tot=tot+nss;
     }
    printf("Numero di sottostringhe totali %d\n",tot);
    system ("PAUSE");
    return 0;
    }
}
int  conta(char cont[N], int n)
{
    int flag=0,flag2=0,flag3=0,flag4=0,vocali=0,nlettera=0,sottostringhe=0;
    char vocalil[10]={'a','e','i','o','u','A','E','I','O','U'};

    for(int i=0;i<=N&&flag==0;i++)
    {

        if(cont[i]=='\0')
        {
            flag=1;

        }
        else
        {
            for(int j=i;j<=i+n-1&&flag3==0&&flag4==0;j++)
            {
             if(cont[j]=='\0')
        {
            flag4=1;
            vocali=0;

        }
        else
        {
                if (vocali>2)
                {
                    flag3=1;
                    vocali=0;
                }
                else
                {
                for(int y=0;y<=9&&flag2==0;y++)
            {
                if(cont[j]==vocalil[y])
                {
                  vocali++;
                  flag2=1;
                }

            }
            flag2=0;
            }
        }
            }
            flag3=0;
                if(vocali==2)
                {
                  sottostringhe++;
                  vocali=0;
                }
                else
                {
                    vocali=0;
                }


        }
    }

    return sottostringhe;
}
