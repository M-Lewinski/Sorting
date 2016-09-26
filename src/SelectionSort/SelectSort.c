
#include "SelectSort.h"


void select_sort(int *lista, int amount, int tryb){
    int i,j,tmp;
    for (i=0;i<(amount-1);i++){
        for (j=i+1;j<amount;j++){
            if(check(lista[i],lista[j],tryb)){
                tmp=lista[i];
                lista[i]=lista[j];
                lista[j]=tmp;
            }
        }
    }
}