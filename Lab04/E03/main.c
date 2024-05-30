#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define N 100
#define S 100
int ricerca(char *s_stringa,char *s_regexp);
int strlen2(char *s_regexp);//calcola la lunghezza della regexp tentendo conto delle quadre
int main()
{
    char *p,src[N],regexp[S];
    int n_regexp;
    printf("Regexp\n");
    gets(regexp);
    printf("Inserire stringa in cui cercare\n");
    gets(src);
    p=ricerca(src,regexp);
    if(p!=0){
        printf("Occorrenza trovata all' indirizzo %p indirizo stringa=%p\n", p, src);
        for(int i=0;i<strlen2(regexp);i++)
            printf("%c",*(p+i));
    }
    else{
        printf("Occorrenza non presente\n");
    }
    return 0;
}
int ricerca(char *s_stringa,char *s_regexp){
int carattere_corrente,flag;
int c=strlen(s_stringa)-strlen2(s_regexp);
for(int i=0;i<=c;i++){
    carattere_corrente=flag=0;
    for(int j=i;j<strlen2(s_regexp)+i&&flag==0;j++){
        if(s_stringa[j]==s_regexp[carattere_corrente])
            carattere_corrente++;
        else{
            if(ispunct(s_regexp[carattere_corrente])!=0){
               if(s_regexp[carattere_corrente]=='['&&s_regexp[carattere_corrente+1]=='^'){//caso 1
                  while(s_regexp[carattere_corrente]!=']'){
                     if(s_regexp[carattere_corrente]==s_stringa[j]){
                        flag=1;
                        break;
                     }
                  carattere_corrente++;
                  }
                carattere_corrente++;
                }
               if(s_regexp[carattere_corrente]=='['&&s_regexp[carattere_corrente+1]!='^'){//caso 2
               carattere_corrente +=1;
               flag=1;
               while(s_regexp[carattere_corrente]!=']'){
                 if(s_regexp[carattere_corrente]==s_stringa[j])
                    flag=0;
               carattere_corrente++;
               }
               carattere_corrente++;
               }
               if(s_regexp[carattere_corrente]=='\\'){
                    if(s_regexp[carattere_corrente+1]=='a'){//caso 3
                    if(islower(s_stringa[j])==0)
                       flag=1;
                    }
                    if(s_regexp[carattere_corrente+1]=='A'){//caso 4
                    if(isupper(s_stringa[j])==0)
                       flag=1;
                    }
              carattere_corrente+=2;
              }
              if(s_regexp[carattere_corrente]=='.'){//caso 5
                    if(isalnum(s_stringa[j])==0)
                    flag=1;
              carattere_corrente++;
              }
          }
          else{
            flag=1;
          }
        }
    }
if(carattere_corrente>=strlen2(s_regexp)){
    return &s_stringa[i];
}
}
return NULL;
}


int strlen2(char *s_regexp){//calcola la lunghezza della sottostringa, considerando le limitazioni del pdf.
int i,cont=i=0;
while(s_regexp[i]!='\0'){
if(s_regexp[i]!='[')
        cont++;
else{
    while(s_regexp[i]!=']')
      i++;
cont++;
}
if(s_regexp[i]=='\\'){
i++;
}
i++;
}
return cont;
}
