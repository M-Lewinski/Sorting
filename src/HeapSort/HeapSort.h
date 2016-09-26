//
// Created by lewin on 26.09.16.
//

#ifndef SORTING_HEAPSORT_H
#define SORTING_HEAPSORT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "../tryby.h"

void heap_sort(int *lista, int amount, int tryb);
void heap_check(int *lista, int amount, int i, int tryb);
void heap_build(int *lista, int amount, int tryb);

#endif //SORTING_HEAPSORT_H
