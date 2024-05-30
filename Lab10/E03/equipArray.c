#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "equipArray.h"
struct equipArray_s{
int n_item,equip_tot[L];
};
equipArray_t equipArray_init(){
equipArray_t eq;
eq=malloc(sizeof(struct equipArray_s));
if(eq==NULL){
    printf("Errore malloc equipArray\n");
    exit(EXIT_FAILURE);
}
eq->n_item=0;
for(int i=0;i<L;i++)
    eq->equip_tot[i]=-1;
return eq;
}

void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
for(int i=0;i<L;i++)
    if(equipArray->equip_tot[i]!=-1)
        invArray_printByIndex(fp,invArray,i);

}
int equipArray_inUse(equipArray_t equipArray){
if (equipArray->n_item>0)
    return 1;
return 0;
}
int equipArray_update(equipArray_t equipArray, invArray_t invArray){
char nome[LEN];
int scelta,indice,tmp,flag=0;
printf("- 0 per aggiungere\n- 1 per rimuovere\n");
scanf("%d",&scelta);
if(scelta==0){
   if(equipArray->n_item<8){
    printf("Inserire nome oggetto da aggiungere\n");
    scanf("%s",nome);
    indice=invArray_searchByName(invArray,nome);
    if(indice!=-1){
      for(int i=0;i<L;i++){
        tmp=equipArray_getEquipByIndex(equipArray,i);
        if(tmp==indice){
            printf("Oggetto già inserito\n");
            flag=1;
            return -1;
        }
      }
      if(flag==0){
        for(int i=0;i<L;i++)
        if(equipArray->equip_tot[i]==-1){
           equipArray->equip_tot[i]=indice;
           equipArray->n_item++;
           printf("Item aggiunto\n");
           return indice;
        }
      }
    }
    else{
        printf("Item non esistente\n");
        return -1;
    }
   }
   else{
    printf("Inventario pieno\n");
    return -1;
   }
}
else if(scelta==1){
    printf("Inserire nome oggetto da eliminare\n");
    scanf("%s",nome);
    indice=invArray_searchByName(invArray,nome);
    if(indice!=-1){
      for(int i=0;i<L;i++){
          tmp=equipArray_getEquipByIndex(equipArray,i);
          if(tmp==indice){
            equipArray->equip_tot[indice]=-1;
            equipArray->n_item--;
            printf("Item rimosso\n");
            return indice;
        }
      }
      printf("L'item non fa parte dell'equipaggiamento\n");
      return -1;
    }
    else{
        printf("Oggetto non esistente\n");
        return -1;
    }
}
else{
    printf("Errore inserimento comando");
    return -1;
}
return -1;
}


int equipArray_getEquipByIndex(equipArray_t equipArray, int index){
if(index<L)
  return equipArray->equip_tot[index];
}
void equipArray_free(equipArray_t equipArray){
free(equipArray);
return;
}
