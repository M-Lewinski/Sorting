//
// Created by lewin on 26.09.16.
//

#ifndef SORTING_QUICKSORTRECURSIVE_H
#define SORTING_QUICKSORTRECURSIVE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "../../tryby.h"

void quick_sort_recursive_random(int *lista,int amount,int type);
void quick_sort_rek_rand(int *lista, int left, int right, int type);
void quick_sort_recursive_right(int *lista,int amount,int type);
void quick_sort_rek_right(int *lista, int left, int right, int type);
void checkKey(int *lista, int type, int key, int *i, int *j);

#endif //SORTING_QUICKSORTRECURSIVE_H
