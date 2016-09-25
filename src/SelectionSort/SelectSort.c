
#include "SelectSort.h"


void select_sort(int *p, int amount, int tryb){
    int i,j,tmp;
    bool a;
    for (i=0;i<(amount-1);i++){
        for (j=i;j<amount-1;j++){
            switch (tryb){
                case 0: a=(*(p+i)<*(p+j+1));
                    break;
                case 1: a=(*(p+i)>*(p+j+1));
                    break;
            }
            if (a==true){
                tmp=*(p+i);
                *(p+i)=*(p+j+1);
                *(p+j+1)=tmp;
            }

        }
    }
}