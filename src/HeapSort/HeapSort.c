//
// Created by lewin on 26.09.16.
//

#include "HeapSort.h"
void heap_sort(int *lista, int amount, int tryb){
    int swap,i;
    heap_build(lista,amount,tryb); //budujemy początkowy kopiec. Musimy uzyskać kopiec, w którym korzeń jest elementem największym/najmniejszym dla uporządkowania rosnącego/malejącego
    //Zabieramy elementy z korzenia, które już są uporządkowane
    for (i=amount-1;i>0;i--){
        swap=*lista;
        *lista=*(lista+i);
        *(lista+i)=swap;
        heap_check(lista,i,0,tryb);
    }
}


void heap_build(int *lista, int amount, int tryb){
    int i;
    //Sprawdzanie kopca zaczynamy od najbardziej prawego wierzchołka w kopcu.
    //Rodzic tego wierzchołka w kopcu jest zawsze pośrodku listy, z której został stworzony kopiec.
    for (i=(amount  / 2)-1;i >=0;i--){
        heap_check(lista,amount,i,tryb); //Sprawdzamy kopiec.
    }
}
/*
 * Sprawdzanie kopca. Chcemy aby w korzeniu, znajdował się element największy/najmniejszy dla uporządkowania rosnącego/malejącego.
 */
void heap_check(int *lista, int amount, int i, int tryb){
    int swap,j;
    bool a;
    j=i;
    do{
        i=j;
        //Sprawdzamy lewe dziecko wierzchołka i.
        if ((2*i+1<amount)&&(tryb!=0)){
            a=(*(lista+2*i+1)>*(lista+j));
        }
        else if ((2*i+1<amount)&&(tryb==0)) {
            a=(*(lista+2*i+1)<*(lista+j));
        }
        //Zapamiętujemy, że lewe dziecko powinno być zamienione z rodzicem.
        if ((j<amount) && (2*i+1<amount) && a){
            j=2*i+1;
        }
        //Sprawdzamy prawe dziecko wierzchołka i.
        if ((2*i+2<amount)&&(tryb!=0)){
            a=(*(lista+2*i+2)>*(lista+j));
        }
        else if ((2*i+1<amount)&&(tryb==0)) {
            a=(*(lista+2*i+2)<*(lista+j));
        }
        //Zapamiętujemy, że prawe dziecko powinno być zmienione z rodzicem.
        if ((j<amount) && (2*i+2<amount) && a){
            j=2*i+2;
        }
        //Zamieniamy dziecko z rodzicem jeżeli są one uporządkowane nieprawidłowo.
        if (i!=j){
            swap=*(lista+i);
            *(lista+i)=*(lista+j);
            *(lista+j)=swap;
        }
        //Kończymy jeżeli dla danego wierzchołka, wszystkie dzieci/wierzchołki są uporządkowane prawidłowo.
    }while (i!=j);
}
