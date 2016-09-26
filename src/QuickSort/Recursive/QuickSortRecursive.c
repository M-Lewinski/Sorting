//
// Created by lewin on 26.09.16.
//

#include "QuickSortRecursive.h"

void quick_sort_recursive_random(int *lista, int amount, int type){
    quick_sort_rek_rand(lista, 0, amount - 1, type);
}

void quick_sort_rek_rand(int *lista, int left, int right, int type) {
    int n,i=left,j=right,key;
    n=rand() %(right - left  +1) + left;
    key =lista[n];
    checkKey(lista, type, key, &i, &j);
    if (left < j){
            quick_sort_rek_rand(lista, left, j, type);
        }
        if (i < right){
            quick_sort_rek_rand(lista, i, right, type);
        }
}

void checkKey(int *lista, int type, int key, int *i, int *j) {
    while ((*i) <= (*j)){
        int tmp;
        while (check(key, lista[(*i)], type)){
                (*i)++;
        }
        while (check(lista[(*j)], key, type)){
                (*j)--;
        }
        if ((*i) <= (*j)){
            tmp = lista[(*i)];
            lista[(*i)]=lista[(*j)];
            lista[(*j)]=tmp;
                (*i)++;
                (*j)--;
        }
    }
}


void quick_sort_recursive_right(int *lista,int amount,int type){
    quick_sort_rek_right(lista, 0, amount - 1, type);
}


void quick_sort_rek_right(int *lista, int left, int right, int type) {
    int i=left,j=right,key;
    key =lista[right];
    checkKey(lista, type, key, &i, &j);
        if (left < j){
            quick_sort_rek_right(lista, left, j, type);
        }
        if (i < right){
            quick_sort_rek_right(lista, i, right, type);
        }
}
