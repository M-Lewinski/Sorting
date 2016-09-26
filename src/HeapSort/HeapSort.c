//
// Created by lewin on 26.09.16.
//

#include "HeapSort.h"
void heap_sort(int *p,int count,int tryb){
    int tmp,i;
    heap_build(p,count,tryb);
    for (i=count-1;i>0;i--){
        tmp=*p;
        *p=*(p+i);
        *(p+i)=tmp;
        heap_check(p,i,0,tryb);
    }
}


void heap_build(int *p, int count,int tryb){
    int i;
    for (i=(count  / 2)-1;i >=0;i--){
        //printf("iteracja :%d |",i);
        heap_check(p,count,i,tryb);
    }
}

void heap_check(int *p,int count, int i,int tryb){
    int tmp,j;
    bool a;
    j=i;
    do{
        i=j;
        // printf("i: %d j: %d | ",i,j);
        if ((2*i+1<count)&&(tryb!=0)){
            a=(*(p+2*i+1)>*(p+j));
        }
        else if ((2*i+1<count)&&(tryb==0)) {
            a=(*(p+2*i+1)<*(p+j));
        }

        if ((j<count) && (2*i+1<count) && a){
            j=2*i+1;
        }

        if ((2*i+2<count)&&(tryb!=0)){
            a=(*(p+2*i+2)>*(p+j));
        }
        else if ((2*i+1<count)&&(tryb==0)) {
            a=(*(p+2*i+2)<*(p+j));
        }

        if ((j<count) && (2*i+2<count) && a){
            j=2*i+2;
        }
        if (i!=j){
            tmp=*(p+i);
            *(p+i)=*(p+j);
            *(p+j)=tmp;
        }
        /*for (q=0;q<count;q++){
             printf("Liczba %d: %d\n",(q+1),*(p+q));
         }*/

    }while (i!=j);

}
