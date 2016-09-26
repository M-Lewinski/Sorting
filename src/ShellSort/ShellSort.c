//
// Created by lewin on 25.09.16.
//

#include "ShellSort.h"

int shell_gap(int *lista, int count, int loop){
    int i,gap;
    for (i=0;((pow(3,i)-1)/2<=ceil((float)count/3));i++)
        gap=(pow(3,i-loop)-1)/2;
    return gap;
}

void shell_sort(int *lista, int amount, int tryb) {
    int tmp, i, j, k, gap = 1;
    for (i = 0; gap > 0; i++) {
        gap = shell_gap(lista, amount, i);
        for (j = gap; j < amount; j++) {
            tmp = lista[j];
            for (k = j; k >= gap; k -= gap) {
                if (check(lista[k - gap],tmp, tryb)) {
                    lista[k] = lista[k - gap];
                }
                else {
                    break;
                }
            }
            lista[k] = tmp;
        }
    }
}
