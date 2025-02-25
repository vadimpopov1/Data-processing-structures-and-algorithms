#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COUNT 10 

void ShakerSort(int A[], int n, int *comparisons, int *swaps) {
    int left = 0, right = n - 1;
    int swapped = 1;
    *comparisons = 0;
    *swaps = 0;

    while (left < right && swapped) {
        swapped = 0;
        for (int i = left; i < right; i++) {
            (*comparisons)++;
            if (A[i] > A[i + 1]) {
                int temp = A[i];
                A[i] = A[i + 1];
                A[i + 1] = temp;
                (*swaps)++;
                swapped = 1;
            }
        }
        right--;

        for (int i = right; i > left; i--) {
            (*comparisons)++;
            if (A[i] < A[i - 1]) {
                int temp = A[i];
                A[i] = A[i - 1];
                A[i - 1] = temp;
                (*swaps)++;
                swapped = 1;
            }
        }
        left++;
    }
}


void PrintMas(int A[], int n){
    for (int i = 0; i < n; i++){
        printf("%d ", A[i]);
    }
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
    ShakerSort(arr1, COUNT, &swaps1, &comparisons1);
    printf("Убывающий массив: ");
    PrintMas(arr1, COUNT);
    printf("Перестановки: %d, Сравнения: %d\n", swaps1, comparisons1);

    int swaps2, comparisons2;
    ShakerSort(arr2, COUNT, &swaps2, &comparisons2);
    printf("Возрастающий массив: ");
    PrintMas(arr2, COUNT);
    printf("Перестановки: %d, Сравнения: %d\n", swaps2, comparisons2);

    int swaps3, comparisons3;
    ShakerSort(arr3, COUNT, &swaps3, &comparisons3);
    printf("Случайный массив: ");
    PrintMas(arr3, COUNT);
    printf("Перестановки: %d, Сравнения: %d\n", swaps3, comparisons3);

    free(arr1);
    free(arr2);
    free(arr3);

    return 0;
}