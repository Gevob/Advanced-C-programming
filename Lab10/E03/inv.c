#include <stdio.h>
#include <stdlib.h>
#include "inv.h"

void inv_read(FILE *fp, inv_t *invp){
inv_t tmp;
fscanf(fp,"%s %s",tmp.nome,tmp.tipo);
*invp=tmp;
}

void stat_read(FILE *fp, stat_t *statp){
stat_t tmp;
fscanf(fp,"%d %d %d %d %d %d",&tmp.hp,&tmp.mp,&tmp.atk,&tmp.def,&tmp.mag,&tmp.spr);
*statp=tmp;
}

void inv_print(FILE *fp, inv_t *invp){
fprintf(fp,"%s %s",invp->nome,invp->tipo);
}

void stat_print(FILE *fp, stat_t *statp, int soglia){
if(soglia==1)
    fprintf(fp," %d %d %d %d %d %d\n",statp->hp,statp->mp,statp->atk,statp->def,statp->mag,statp->spr);
if(soglia==0){
    if(statp->hp>0)
        fprintf(fp," %d",statp->hp);
    else
        fprintf(fp," 1");
    if(statp->mp>0)
        fprintf(fp," %d",statp->mp);
    else
        fprintf(fp," 1");
    if(statp->atk>0)
        fprintf(fp," %d",statp->atk);
    else
        fprintf(fp," 1");
    if(statp->def>0)
        fprintf(fp," %d",statp->def);
    else
        fprintf(fp," 1");
    if(statp->mag>0)
        fprintf(fp," %d",statp->mag);
    else
        fprintf(fp," 1");
    if(statp->spr>0)
        fprintf(fp," %d\n",statp->spr);
    else
        fprintf(fp," 1\n");
}
}
stat_t inv_getStat(inv_t *invp){
return invp->stat;
}
