//
// Created by lewin on 25.09.16.
//

#include "InsertSort.h"

//Insertion sort
void insert_sort(int *lista, int amount, int tryb) {
    int i, j, movingElement;
    for (i = 1; i < amount; ++i) {
        movingElement = lista[i]; //Wybrany kolejmy element
        for (j = i;
             check(lista[j - 1], movingElement, tryb) && j > 0; j--) {     //Sprawdzenie pozycji, na którą trafi element;
            //Zamiana elementu
            lista[j] = lista[j - 1];
            lista[j - 1] = movingElement;
        }
    }
}