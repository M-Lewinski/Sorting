#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>
#include <sys/resource.h>

#include "src/SelectionSort/SelectSort.h"
#include "src/InsertionSort/InsertSort.h"
#include "src/ShellSort/ShellSort.h"
#include "src/HeapSort/HeapSort.h"
#include "src/QuickSort/Recursive/QuickSortRecursive.h"
#include "src/QuickSort/Iterative/QuickSortIterative.h"

void changeStackSize();

void a_Shaped(int *lista,int count);
void increasing(int *lista,int count);
void decreasing(int *lista,int count);
void same(int *lista,int count);
void helpInfo();
void startFiles();
char * checkFile(char *name);
FILE **fileArray;

int seconds = 1000000;
int nanoseconds = 1000;
//Wielkość stacku. Domyślnie 16MB.
int stack = 16;
//Liczba sortowań
int sorts = 8;
//Tablica funkcji sortujących
void (*sort[])(int* list,int count,int mode) = {select_sort,insert_sort,shell_sort,heap_sort,quick_sort_recursive_random,quick_sort_recursive_right,quick_sort_iterative_rand,quick_sort_iterative_right};
//Nazwy sortowań
char *sortName[] = {"Selection Sort","Insertion Sort","Shell Sort","Heap Sort","Quick Sort Recursive Random pivot/key","Quick Sort Recursive Right pivot/key","Quick Sort Iterative Random pivot/key","Quick Sort Iterative Right pivot/key"};
//Nazwy plików, do których zostaną zapisane czasy wykonania poszczególnych sortowań.
char *fileName[] = {"select_sort.txt","insertion_sort.txt","shell_sort.txt","heap_sort.txt","quick_sort_rec_rand.txt","quick_sort_rec_right.txt","quick_sort_iter_rand.txt","quick_sort_iter_right.txt"};
//liczba sposobów uporządkowania początkowej listy do sortowania
int arrangement = 5;
//Tablica funkcji uporzątkowujących początkowe listy do sortowania
void (*arrange[])(int *lista,int count) = {a_Shaped,increasing,decreasing,same};
char *arrangmentName[] = {"Random","A Shaped","Increasing","Decreasing","same"};
//Lista sortowań do wykonania
int sortList[8];
//Liczba sortowań do wykonania
int sortCount=0;
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
//tryb = 0-sortowanie malejąco | 1-sortowanie rosnąco
int tryb=1;

//min i max losowanej wartości
int min = 0; int max = 100000;

int checkArguments(int index,int argc,char* argv[]);
int checkNumber(char *arg);
void updateSortList(int number);
void copyList(int *listToCopy,int *copy,int amount);
void printList(int *list,int amount);
void printListSort(int *list,int amount,int sort);
void test(int *list,int amount,int sort,int tryb);
//Pseudo random generator
void randomize(int *list,int amount);

void printing(const int *list, int amount);

void checkVariables(){
    printf("Amount: %d\n",amount);
    printf("Cycles: %d\n",cycles);
    printf("increase: %d\n",increase);
    printf("increaseType: %d\n",increaseType);
    printf("sortCount: %d\n",sortCount);
}

int main(int argc,char* argv[]){
  int i;
    srand(time(0));
    if(argc < 2){
        printf("Za mało argumentów, Pierwszym argumentem musi być długość listy. Sprawdź pomoc -h lub --help\n");
        exit(1);
    }
    else{
      if(strcmp(argv[1],"-h")==0 || strcmp(argv[1],"--help")==0) {
          helpInfo();
      }
        amount = checkNumber(argv[1]);
    }
    for(i=2;i<argc;i++){
        i=checkArguments(i,argc,argv);
    }
    if(sortCount<=0){
        for(i=0;i<sorts;++i){
            updateSortList(i);
        }
    }
    if(doingTest){
        checkVariables();
    }
    changeStackSize();
    startFiles();
    //Powtarzanie sortowań
    for(i=0;i<cycles;i++){
        if(i!=0){
            switch (increaseType){
                case 0:amount*=increase;
                    break;
                case 1:amount+=increase;
                    break;
            }
        }
        int k;

        //Tworzenie list
        int *primaryList = (int*) malloc(sizeof(int)*amount);
        int *temporaryList = (int*) malloc(sizeof(int)*amount);

        int j;
        for (j = 0; j < arrangement; ++j) {
            if(j==0){
                //PRNG
                randomize(primaryList,amount);
            }
            else{
                arrange[j-1](primaryList,amount);
            }
            printList(primaryList, amount);
            for (k = 0; k < sortCount; k++) {
                struct timespec start,end;
                copyList(primaryList, temporaryList, amount);
                clock_gettime(CLOCK_MONOTONIC_RAW,&start);
                (*sort[k])(temporaryList, amount, tryb);
                clock_gettime(CLOCK_MONOTONIC_RAW,&end);
                uint64_t delta = (end.tv_sec - start.tv_sec) * seconds + (end.tv_nsec - start.tv_nsec)/nanoseconds;
                fseek(fileArray[k],0,SEEK_END);
                fprintf(fileArray[k],"%"PRIu64"\t",delta);
                printListSort(temporaryList, amount, k);
                test(temporaryList, amount, k, tryb);
                if(j == arrangement-1){
                    fseek(fileArray[k],0,SEEK_END);
                    fprintf(fileArray[k],"\n");
                }
            }
        }
        //Usuwanie list
        free(primaryList);
        free(temporaryList);
    }
    int f;
    for (f = 0; f < sortCount; ++f) {
        fclose(fileArray[sortList[f]]);
    }
        return 0;
}

//Rejestrowanie, które sortowania mają być wykonane
void updateSortList(int number){
    sortList[sortCount]= number;
    sortCount++;
}

//Informacja pomocnicza do obsługi programu
void helpInfo(){
    printf("\n");
    printf("Program testuje szybkości różnych sortowań na liście liczb pseudolosowych w różnych konfiguracjach.\n");
    printf("Czasy wykonywania poszczególnych sortowań zapisywane są do plików w microsekundach.\n");
    printf("\nPierwszym argumentem musi być długość listy liczb. Domyślnie program wykonuje wszystkie sortowania i sortuje rosnąco\n");
    printf("Opcję programu:\n");
    printf("  -h, --help\t program wyświetli podstawowe informacje o programie.\n");
    printf("  -d\t sortowania będą sortować liczby malejąco. Domyślnie sortowanie rosnąco.\n");
    printf("  -c, --cycles\t definiuje liczbę cykli. Następnie należy podać liczbę cykli oraz sposób zwiększania długości listy.\n");
    printf("\nMożliwe sposoby modyfikacji listy:\n");
    printf("  a, addition\t Dodanie ustalonej wartości do obecnej długości. -c 10 a 10 : Sortowania wykonają się 10 razy, zwiększjąc za każdym razem długość listy o 10\n");
    printf("  m, multiplication\t Pomnożenie obecnej długości o ustaloną wartość. -c 10 m 2 : Sortowania wykonają się 10 razy, za każdym razem długość listy jest dwukrotnie zwiększana.\n");
    printf("  -t, --test\t program będzie sprawdzać czy lista została posortowana prawidłowo.\n");
    printf("  --max\t możliwość zmiany maksymalnie wartości, która jest losowana. Domyślnie --max %d.\n",max);
    printf("  --min\t możliwość zmiany minimalnej wartości, która jest losowana. Domyślnie --min %d.\n",min);
    printf("  --stack\t możliwość zmiany wielkości stacku. Wartość podawana jest w MB. Domyślnie --stack %d\n",stack);
    printf("  -n\t wyniki czasów będę zapisywane w nanosekundach\n");

    printf("\nMożliowści sortowania:\n");
    printf("  -a, --all\t program wykona wszystkie sortowania. Jest to domyślnie ustawiona opcja w programie.\n");
    printf("  -s, --selection\t wykonane zostanie sortowanie Selection Sort.\n");
    printf("  -i, --insertion\t wykonane zostanie sortowanie Insertion Sort.\n");
    printf("  -sh, --shell\t wykonane zostanie sortowanie Shell Sort.\n");
    printf("  -hp, --heap\t wykonane zostanie sortowanie Heap Sort.\n");
    printf("  -qsrrand\t wykonane zostanie sortowanie Quick Sort rekurencyjny z wyborem losowego klucza.\n");
    printf("  -qsrright\t wykonane zostanie sortowanie Quick Sort rekurencyjny z wyborem prawego klucza.\n");
    printf("  -qsirand\t wykonane zostanie sortowanie Quick Sort iteracyjny z wyborem losowego klucza.\n");
    printf("  -qsiright\t wykonane zostanie sortowanie Quick Sort iteracyjny z wyborem prawego klucza.\n");
    printf("\nPrzykład użycia:\n");
    printf("  ./Sorting 1000 -a -c 10 m 2\n");
    printf("Powyższa komenda wykona wszystkie sortowania, zaczynając z listą o długości 1000 i wykona 10 cykli, zwiększając długość listy dwukrotnie. -a jest opcjonalne\nDługości list: 1000 2000 4000 8000 16000 32000 64000 128000 256000 512000\n");
    printf("\nProgram napisany przez Michała Lewińskiego - https://github.com/M-Lewinski/Sorting\n");
    printf("\n");
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

void printList(int *list,int amount){
    if(!doingTest){
        return;
    }
    printf("List of numbers:\n");
    printing(list, amount);
}

void printListSort(int *list,int amount,int sort){
    if(!doingTest){
        return;
    }
    printf("%s:\n",sortName[sort]);
    printing(list,amount);
}

void printing(const int *list, int amount) {
    int i;
    for (i = 0; i < amount; i++) {
        printf("%d\t",list[i]);
    }
    printf("\n");
}

void randomize(int *list,int amount){
    int i,random;
    for (i = 0; i < amount; i++) {
        random = rand() %(max - min + 1) + min;
        list[i] = random;
    }
}

void test(int *list,int amount,int sort,int tryb){
    if(!doingTest){
        return;
    }
    int i;
    for (i = 0; i < amount-1; i++) {
        if(check(list[i],list[i+1],tryb)){
            if(list[i]!=list[i+1]){
                printf("Błędne sortowanie: %s ### %d | %d ###",sortName[sort],list[i],list[i+1]);
                exit(1);
            }
        }
    }
}


//Obsługa argumentów oraz sprawdzenie ich poprawności
int checkArguments(int index,int argc,char* argv[]){
    char *arg = argv[index];
    if(strcmp(arg,"-c")==0 || strcmp(arg,"--cycles")==0){
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
    else if(strcmp(arg,"-s")==0 || strcmp(arg,"--selection")==0){
        updateSortList(0);
    }
    else if(strcmp(arg,"-i")==0 || strcmp(arg,"--insertion")==0){
        updateSortList(1);
    }
    else if(strcmp(arg,"-sh")==0 || strcmp(arg,"--shell")==0){
        updateSortList(2);
    }
    else if(strcmp(arg,"-hp")==0 || strcmp(arg,"--heap")==0){
        updateSortList(3);
    }
    else if(strcmp(arg,"-qsrrand")==0){
        updateSortList(4);
    }
    else if(strcmp(arg,"-qsrright")==0){
        updateSortList(5);
    }
    else if(strcmp(arg,"-qsirand")==0){
        updateSortList(6);
    }
    else if(strcmp(arg,"-qsiright")==0){
        updateSortList(7);
    }
    else if(strcmp(arg,"-a")==0 || strcmp(arg,"-all")==0){
        int i;
        for(i=0;i<sorts;i++){
            updateSortList(i);
        }
    }
    else if(strcmp(arg,"-t")== 0 || strcmp(arg,"--test")== 0) {
        doingTest = true;
    }
    else if(strcmp(arg,"--min")== 0){
        arg = increaseIndex(&index,argc,argv);
        min = checkNumber(arg);
    }
    else if(strcmp(arg,"--max")== 0){
        arg = increaseIndex(&index,argc,argv);
        max = checkNumber(arg);
    }
    else if(strcmp(arg,"-d")== 0){
        tryb = 0;
    }
    else if(strcmp(arg,"--stack") == 0){
        arg = increaseIndex(&index,argc,argv);
        stack = checkNumber(arg);
    }
        else if(strcmp(arg,"-n") == 0){
        seconds = 1000000000;
        nanoseconds = 1;
    }
    else{
        printf("Zły argument, sprawdź pomoc. Argument -h lub --help");
        exit(1);
    }
    return index;
}

void a_Shaped(int *lista,int count){
    heap_sort(lista,count,0);
    heap_sort(lista,count/2,1);
}
void increasing(int *lista,int count){
    heap_sort(lista,count,1);
}
void decreasing(int *lista,int count){
    heap_sort(lista,count,0);
}
void same(int *lista,int count){
    int i;
    for (i = 1; i < count; ++i) {
        lista[i]=lista[0];
    }
}

void startFiles(){
    int i;
    fileArray = (FILE**)malloc(sizeof(FILE)*sortCount);
    for (i = 0; i < sortCount; ++i) {
        fileArray[i] = (FILE*)malloc(sizeof(FILE));
    }
    for (i = 0; i < sortCount; i++) {
        int j;
        char* name = checkFile(fileName[sortList[i]]);
        fileArray[i] = fopen(name,"w");
        free(name);
        for (j = 0; j < arrangement; j++) {
            fprintf(fileArray[i],"%s\t",arrangmentName[j]);
        }
        fprintf(fileArray[i],"\n");
    }
}

char * checkFile(char *name){
    char* temp = (char*)malloc(sizeof(char)*100);
    strcpy(temp,name);
    int i=0;
    while(temp!=NULL){
        i++;
        char number = i + '0';
        if(access(temp,F_OK)== -1){
            printf("NAZWA PLIKU: %s\n",temp);
            return temp;
        }
        strcpy(temp,name);
        strcat(temp,"(");
        strncat(temp,&number,1);
        strcat(temp,")");
    }
    return NULL;
}

void changeStackSize(){
    const rlim_t newStackSize = stack * 1024 * 1024;
    struct rlimit rl;
    int result;
    result = getrlimit(RLIMIT_STACK,&rl);
    if(result == 0){
        if(rl.rlim_cur < newStackSize){
            rl.rlim_cur = newStackSize;
            result = setrlimit(RLIMIT_STACK,&rl);
            if(result!=0){
                fprintf(stderr,"Błąd stacku. Setrlimit error: %d\n",result);
            }
        }
    }
}
