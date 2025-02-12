#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COUNT 100 

void selectSort(int arr[], int n, int *swaps, int *comparisons) {
    *swaps = 0;
    *comparisons = 0;

    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            (*comparisons)++;
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            int temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
            (*swaps) = *swaps + 3;
        }
    }
}

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));
    int* arr1 = (int*)malloc(COUNT * sizeof(int)); // Убывающий массив
    int* arr2 = (int*)malloc(COUNT * sizeof(int)); // Возрастающий массив
    int* arr3 = (int*)malloc(COUNT * sizeof(int)); // Случайный массив

    for (int i = 0; i < COUNT; i++) {
        arr1[i] = COUNT - i; 
    }

    for (int i = 0; i < COUNT; i++) {
        arr2[i] = i + 1;
    }

    for (int i = 0; i < COUNT; i++) {
        arr3[i] = rand();
    }

    int swaps1, comparisons1;
    selectSort(arr1, COUNT, &swaps1, &comparisons1);
    printf("Убывающий массив: ");
    print_array(arr1, COUNT);
    printf("Перестановки: %d, Сравнения: %d\n", swaps1, comparisons1);

    int swaps2, comparisons2;
    selectSort(arr2, COUNT, &swaps2, &comparisons2);
    printf("Возрастающий массив: ");
    print_array(arr2, COUNT);
    printf("Перестановки: %d, Сравнения: %d\n", swaps2, comparisons2);

    int swaps3, comparisons3;
    selectSort(arr3, COUNT, &swaps3, &comparisons3);
    printf("Случайный массив: ");
    print_array(arr3, COUNT);
    printf("Перестановки: %d, Сравнения: %d\n", swaps3, comparisons3);

    free(arr1);
    free(arr2);
    free(arr3);

    return 0;
}
