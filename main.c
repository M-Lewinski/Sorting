#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "src/SelectionSort/SelectSort.h"

void (*sort[1])(int* list,int count,int mode) = {select_sort};
//Lista sortowań do wykonania
int sortList[8];
//Liczba sortowań do wykonania
int sortNumber=0;
//Ilość liczb
int amount = -1;
//Liczba powtórzeń do wykonania;
int cycles = 1;
//Sposób zwiększania ilości liczb. Mnożenie lub dodawanie.
int increaseType = -1;
//Zwiększenie ilości liczb. Iloczyn lub suma.
int increase = 0;
//Sprawdzanie poprawności sortowania.
bool doingTest = false;

int checkArguments(int index,int argc,char* argv[]);
int checkNumber(char *arg);
void updateSortList(int number);
void copyList(int *listToCopy,int *copy,int amount);

void checkVariables(){
    printf("Amount: %d\n",amount);
    printf("Cycles: %d\n",cycles);
    printf("increase: %d\n",increase);
    printf("increaseType: %d\n",increaseType);
    printf("sortNumber: %d\n",sortNumber);
}

int main(int argc,char* argv[]){
    int i;
    if(argc < 2){
        printf("Za mało argumentów. Sprawdź pomoc -h lub --help");
        exit(1);
    }
    else{
        amount = checkNumber(argv[1]);
    }
    for(i=2;i<argc;i++){
        i=checkArguments(i,argc,argv);
    }
    if(sortNumber<=0){
        for(i=0;i<8;++i){
            updateSortList(i);
        }
    }
    checkVariables();

    for(i=0;i<cycles;i++){
        if(i!=0){
            switch (increaseType){
                case 0:amount*=increase;
                    break;
                case 1:amount+=increase;
                    break;
            }
        }
        int *primaryList = (int*) malloc(sizeof(int)*amount);
        int *temporaryList = (int*) malloc(sizeof(int)*amount);
        int j;
        for(j=0;j<sortNumber;j++){
            copyList(primaryList,temporaryList,amount);

        }

        free(primaryList);
        free(temporaryList);
    }
        return 0;
}

//Rejestrowanie, które sortowania mają być wykonane
void updateSortList(int number){
    sortList[sortNumber]= number;
    sortNumber++;
}

//Informacja pomocnicza do obsługi programu
void helpInfo(){
    printf("HELP!\n");
    exit(0);
}

//Zwiększenie indexu dla argumentów
char* increaseIndex(int *index,int argc,char*argv[]){
    *index=*index + 1;
    if(*index >= argc){
        printf("Zła liczba argumentów. Sprawdź pomoc -h lub --help");
        exit(1);
    }
    return argv[*index];
}

//Obsługa argumentów oraz sprawdzenie ich poprawności
int checkArguments(int index,int argc,char* argv[]){
    char *arg = argv[index];
    if(strcmp(arg,"-h")==0 || strcmp(arg,"--help")==0) {
        helpInfo();
    }
    else if(strcmp(arg,"-c")==0 || strcmp(arg,"-cycles")==0){
        arg = increaseIndex(&index,argc,argv);
        cycles=checkNumber(arg);
        if(cycles < 1){
            printf("Liczba powtórzeń musi być większa lub równa 1");
            exit(1);
        }
        arg = increaseIndex(&index,argc,argv);
        if(strcmp(arg,"m")== 0 || strcmp(arg,"multiplication")== 0){
            increaseType = 0;
        }
        else if(strcmp(arg,"a")== 0 || strcmp(arg,"addition")== 0){
            increaseType = 1;
        }
        else{
            printf("Zły argument, sprawdź pomoc. Argument -h lub --help");
            exit(1);
        }
        arg = increaseIndex(&index,argc,argv);
        increase = checkNumber(arg);
        if(increase < 1){
            printf("Zły argument, sprawdź pomoc. Argument -h lub --help");
            exit(1);
        }
    }
    else if(strcmp(arg,"-s")==0 || strcmp(arg,"-selection")==0){
        updateSortList(0);
    }
    else if(strcmp(arg,"-a")==0 || strcmp(arg,"-all")==0){
        int i;
        for(i=0;i<8;i++){
            updateSortList(i);
        }
    }
        else if(strcmp(arg,"-t")== 0 || strcmp(arg,"--test")== 0){

    }
    else{
        printf("Zły argument, sprawdź pomoc. Argument -h lub --help");
        exit(1);
    }
    return index;
}

//Zmiana łańcucha znaków na integer. Sprawdzenie poprawności
int checkNumber(char *arg){
    char *test;
    int number = strtol(arg,&test,10);
    if(strcmp(test,"") != 0){
        printf("Zła wartość integer! %s\n",test);
        exit(1);
    }
    return number;
}

void copyList(int *listToCopy,int *copy,int amount){
    int i;
    for(i=0;i<amount;i++){
        copy[i] = listToCopy[i];
    }
}
