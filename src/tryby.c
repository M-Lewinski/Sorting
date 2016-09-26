//
// Created by lewin on 25.09.16.
//

#include "tryby.h"

//Sprawdzenie elementów w zależności od trybu. 0-malejąco 1-rosnąco.
bool check(int left,int right,int tryb){
    switch (tryb){
        case 0:
            return left < right;
        case 1:
            return left > right;
        default:
            return false;
    }
}
