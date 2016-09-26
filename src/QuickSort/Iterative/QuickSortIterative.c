//
// Created by lewin on 26.09.16.
//

#include "QuickSortIterative.h"

void quick_sort_iterative_right(int *lista, int amount, int type) {
    int  key, beg[MAX_STACK], end[MAX_STACK], i=0, L, R, swap;

    beg[0]=0; end[0]=amount;
    while (i>=0) {
        L=beg[i]; R=end[i]-1;
        if (L<R) {
            key=lista[R];
            swap =lista[L];
            lista[L]=lista[R];
            lista[R]=swap;
            while (L<R) {
                while (check(lista[R],key,type) && L<R) {
                    R--;
                }
                if (L<R){
                    swap =lista[L];
                    lista[L++]=lista[R];
                    lista[R]=swap;
                }
                while (check(key,lista[L],type) && L<R) {
                    L++;
                }
                if (L<R){
                    swap =lista[L];
                    lista[L]=lista[R];
                    lista[R--]=swap;
                }
            }
            beg[i+1]=L+1; end[i+1]=end[i]; end[i++]=L;
            if (end[i]-beg[i]>end[i-1]-beg[i-1]) {
                swap=beg[i]; beg[i]=beg[i-1]; beg[i-1]=swap;
                swap=end[i]; end[i]=end[i-1]; end[i-1]=swap;
            }
        }
        else {
            i--;
        }
    }
}


void quick_sort_iterative_rand(int *lista, int amount, int type) {
    int  n,key, beg[MAX_STACK], end[MAX_STACK], i=0, L, R, swap;
    beg[0]=0; end[0]=amount;
    while (i>=0) {
        L=beg[i]; R=end[i]-1;
        if (L<R) {
            n=rand() %(R - L +1) + L;
            key=lista[n];
            swap =lista[L];
            lista[L]=lista[n];
            lista[n]=swap;
            while (L<R) {
                while (check(lista[R],key,type) && L<R) {
                    R--;
                }
                if (L<R){
                    swap =lista[L];
                    lista[L++]=lista[R];
                    lista[R]=swap;
                }
                while (check(key,lista[L],type) && L<R) {
                    L++;
                }
                if (L<R){
                    swap =lista[L];
                    lista[L]=lista[R];
                    lista[R--]=swap;
                }
            }
            beg[i+1]=L+1; end[i+1]=end[i]; end[i++]=L;
            if (end[i]-beg[i]>end[i-1]-beg[i-1]) {
                swap=beg[i]; beg[i]=beg[i-1]; beg[i-1]=swap;
                swap=end[i]; end[i]=end[i-1]; end[i-1]=swap;
            }
        }
        else {
            i--;
        }
    }
}
