#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pg.h"

int pg_read(FILE *fp,pg_t *pgp){
pg_t pg;
if(fscanf(fp,"%s %s %s %d %d %d %d %d %d",pg.cod,pg.nome,pg.classe,&pg.b_stat.hp,&pg.b_stat.mp,&pg.b_stat.atk,&pg.b_stat.def,&pg.b_stat.mag,&pg.b_stat.spr)!=EOF){
pg.equip=NULL;
pg.eq_stat=pg.b_stat;
*pgp=pg;
return 1;
}
return 0;
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){
fprintf(fp,"%s %s %s %d %d %d %d %d %d\n",pgp->cod,pgp->nome,pgp->classe,pgp->b_stat.hp,pgp->b_stat.mp,pgp->b_stat.atk,pgp->b_stat.def,pgp->b_stat.mag,pgp->b_stat.spr);
if(equipArray_inUse(pgp->equip)){
    printf("Inventario\n");
    equipArray_print(fp,pgp->equip,invArray);
    stat_print(fp,&pgp->eq_stat,0);
}

}

void pg_updateEquip(pg_t *pgp, invArray_t invArray){
int tmp,indice;
stat_t temp;
tmp=equipArray_inUse(pgp->equip);
indice=equipArray_update(pgp->equip,invArray);
if(indice!=-1){
   if(tmp<equipArray_inUse(pgp->equip)){//è stato aggiunto un item
   temp=inv_getStat(invArray_getByIndex(invArray,indice));
   pgp->eq_stat.hp+=temp.hp;
   pgp->eq_stat.mp+=temp.mp;
   pgp->eq_stat.atk+=temp.atk;
   pgp->eq_stat.def+=temp.def;
   pgp->eq_stat.mag+=temp.mag;
   pgp->eq_stat.spr+=temp.spr;
   }
   else{//è stato tolto un item
   temp=inv_getStat(invArray_getByIndex(invArray,indice));
   pgp->eq_stat.hp-=temp.hp;
   pgp->eq_stat.mp-=temp.mp;
   pgp->eq_stat.atk-=temp.atk;
   pgp->eq_stat.def-=temp.def;
   pgp->eq_stat.mag-=temp.mag;
   pgp->eq_stat.spr-=temp.spr;
   }
}
}
void pg_clean(pg_t *pgp){
equipArray_free(pgp->equip);
return;
}
