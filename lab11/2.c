#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    long comparisons;
    long swaps;
} Stats;

void swap(int *a, int *b, Stats *stats) {
    int temp = *a;
    *a = *b;
    *b = temp;
    stats->swaps++;
}

void quick_sort(int arr[], int left, int right, Stats *stats) {
    if (left >= right) return;

    int pivot = arr[left];
    int i = left + 1;
    int j = right;

    while (1) {
        while (i <= j && arr[i] <= pivot) {
            i++;
            stats->comparisons++;
        }
        if (i <= j) stats->comparisons++;

        while (i <= j && arr[j] >= pivot) {
            j--;
            stats->comparisons++;
        }
        if (i <= j) stats->comparisons++;

        if (i <= j) {
            swap(&arr[i], &arr[j], stats);
        } else {
            break;
        }
    }

    if (left != j) {
        swap(&arr[left], &arr[j], stats);
    }

    quick_sort(arr, left, j - 1, stats);
    quick_sort(arr, j + 1, right, stats);
}

void generate_array(int arr[], int n, int type) {
    switch(type) {
        case 0: // Убывающий
            for (int i = 0; i < n; i++) arr[i] = n - i;
            break;
        case 1: // Возрастающий
            for (int i = 0; i < n; i++) arr[i] = i + 1;
            break;
        case 2: // Случайный
            for (int i = 0; i < n; i++) arr[i] = rand() % (n * 10);
            break;
    }
}

void analyze_for_n(int n) {
    int arr[n];
    Stats stats[3] = {0}; // 0 - убыв, 1 - возр, 2 - случ
    
    for (int type = 0; type < 3; type++) {
        generate_array(arr, n, type);
        quick_sort(arr, 0, n - 1, &stats[type]);
    }
    
    printf("| %4d | %12ld | %12ld | %12ld |\n", 
           n, 
           stats[0].swaps + stats[0].comparisons,
           stats[1].swaps + stats[1].comparisons,
           stats[2].swaps + stats[2].comparisons);
}

int main() {
    srand(time(NULL));
    
    printf("Трудоемкость метода Хоара (QuickSort)\n");
    printf("|  N   |             QuickSort (Mф + Cф)            |\n");
    printf("|      | Убыв.        | Возр.        | Случ.        |\n");
    
    int sizes[] = {100, 200, 300, 400, 500};
    for (int i = 0; i < 5; i++) {
        analyze_for_n(sizes[i]);
    }
    
    return 0;
}