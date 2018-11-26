# Sorting

Program testuje szybkości różnych sortowań na liście liczb pseudolosowych w różnych konfiguracjach.
Czas wykonywania poszczególnych sortowań zapisywane są do plików w **microsekundach**.

Wykonywane sortowania:
- Selection sort
- Insertion sort
- Shellsort
- Heap sort
- Quick sort rekurencyjny z wyborem klucza "Random pivot" : Klucz brany jest losowo spośród elementów w analizowanym fragmencie listy
- Quick sort rekurencyjny z wyborem klucza "Right pivot" : Klucz brany jest jako ostatni element w analizowanym fragmencie listy.
- Quick sort iteracyjny z wyborem klucza "Random pivot" : Klucz brany jest losowo spośród elementów w analizowanym fragmencie listy
- Quick sort iteracyjny z wyborem klucza "Right pivot" : Klucz brany jest jako ostatni element w analizowanym fragmencie listy.
## Budowanie i uruchamianie
Program napisany jest w języku C. Kompilacja przebiega przy użyciu narzędzia **cmake**. Skrypt **makeAndRun.sh** ma na celu ułatwienie uruchamiania zbudowaniu i uruchomieniu programu przy użyciu jednego polecenia.

## Opcje programu
```
  -h, --help	 program wyświetli podstawowe informacje o programie.
  -d	 sortowania będą sortować liczby malejąco. Domyślnie sortowanie rosnąco.
  -c, --cycles	 definiuje liczbę cykli. Następnie należy podać liczbę cykli oraz sposób zwiększania długości listy.

Możliwe sposoby modyfikacji listy:
  a, addition	 Dodanie ustalonej wartości do obecnej długości. -c 10 a 10 : Sortowania wykonają się 10 razy, zwiększjąc za każdym razem długość listy o 10
  m, multiplication	 Pomnożenie obecnej długości o ustaloną wartość. -c 10 m 2 : Sortowania wykonają się 10 razy, za każdym razem długość listy jest dwukrotnie zwiększana.
  -t, --test	 program będzie sprawdzać czy lista została posortowana prawidłowo.
  --max	 możliwość zmiany maksymalnie wartości, która jest losowana. Domyślnie --max 100000.
  --min	 możliwość zmiany minimalnej wartości, która jest losowana. Domyślnie --min 0.
  --stack	 możliwość zmiany wielkości stacku. Wartość podawana jest w MB. Domyślnie --stack 16
  -n	 wyniki czasów będę zapisywane w nanosekundach

Możliowści sortowania:
  -a, --all	 program wykona wszystkie sortowania. Jest to domyślnie ustawiona opcja w programie.
  -s, --selection	 wykonane zostanie sortowanie Selection Sort.
  -i, --insertion	 wykonane zostanie sortowanie Insertion Sort.
  -sh, --shell	 wykonane zostanie sortowanie Shell Sort.
  -hp, --heap	 wykonane zostanie sortowanie Heap Sort.
  -qsrrand	 wykonane zostanie sortowanie Quick Sort rekurencyjny z wyborem losowego klucza.
  -qsrright	 wykonane zostanie sortowanie Quick Sort rekurencyjny z wyborem prawego klucza.
  -qsirand	 wykonane zostanie sortowanie Quick Sort iteracyjny z wyborem losowego klucza.
  -qsiright	 wykonane zostanie sortowanie Quick Sort iteracyjny z wyborem prawego klucza.
```

## Przykłady użycia
```
./Sorting 1000 -a -c 10 m 2
```
Powyższa komenda wykona wszystkie sortowania, zaczynając z listą o długości 1000 i wykona 10 cykli, zwiększając długość listy dwukrotnie. -a jest opcjonalne.
Długości list liczb w poszczególnych cyklach: 1000 2000 4000 8000 16000 32000 64000 128000 256000 512000

## Autor
Program samodzielnie napisany przez Michała Lewińskiego - https://github.com/M-Lewinski/Sorting
