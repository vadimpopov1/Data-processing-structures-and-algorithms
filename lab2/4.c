#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COUNT1 10
#define COUNT2 100

void selectSort_bad(int arr[], int n, int *swaps, int *comparisons) {
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

void selectSort_good(int arr[], int n, int *swaps, int *comparisons) {
    *swaps = 0;
    *comparisons = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            (*comparisons)++;
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        (*swaps) = (*swaps) + 3;
    }
}


int main() {
    srand(time(NULL));

    int* arr1 = (int*)malloc(COUNT1 * sizeof(int)); // Убывающий массив
    int* arr2 = (int*)malloc(COUNT1 * sizeof(int)); // Возрастающий массив
    int* arr3 = (int*)malloc(COUNT1 * sizeof(int)); // Случайный массив

    int* arr1_1 = (int*)malloc(COUNT2 * sizeof(int)); // Убывающий массив
    int* arr2_1 = (int*)malloc(COUNT2 * sizeof(int)); // Возрастающий массив
    int* arr3_1 = (int*)malloc(COUNT2 * sizeof(int)); // Случайный массив

    int* arr4 = (int*)malloc(COUNT1 * sizeof(int)); // Убывающий массив
    int* arr5 = (int*)malloc(COUNT1 * sizeof(int)); // Возрастающий массив
    int* arr6 = (int*)malloc(COUNT1 * sizeof(int)); // Случайный массив

    int* arr4_1 = (int*)malloc(COUNT2 * sizeof(int)); // Убывающий массив
    int* arr5_1 = (int*)malloc(COUNT2 * sizeof(int)); // Возрастающий массив
    int* arr6_1 = (int*)malloc(COUNT2 * sizeof(int)); // Случайный массив


    for (int i = 0; i < COUNT1; i++) {
        arr1[i] = COUNT1 - i; 
    }

    for (int i = 0; i < COUNT1; i++) {
        arr2[i] = i + 1;
    }

    for (int i = 0; i < COUNT1; i++) {
        arr3[i] = rand();
    }

    for (int i = 0; i < COUNT2; i++) {
        arr1_1[i] = COUNT2 - i; 
    }

    for (int i = 0; i < COUNT2; i++) {
        arr2_1[i] = i + 1;
    }

    for (int i = 0; i < COUNT2; i++) {
        arr3_1[i] = rand();
    }

    for (int i = 0; i < COUNT1; i++) {
        arr4[i] = COUNT1 - i; 
    }

    for (int i = 0; i < COUNT1; i++) {
        arr5[i] = i + 1;
    }

    for (int i = 0; i < COUNT1; i++) {
        arr6[i] = rand();
    }

    for (int i = 0; i < COUNT2; i++) {
        arr4_1[i] = COUNT2 - i; 
    }

    for (int i = 0; i < COUNT2; i++) {
        arr5_1[i] = i + 1;
    }

    for (int i = 0; i < COUNT2; i++) {
        arr6_1[i] = rand();
    }

    int swaps1, comparisons1;
    int swaps2, comparisons2;
    int swaps3, comparisons3;
    selectSort_good(arr1, COUNT1, &swaps1, &comparisons1);
    selectSort_good(arr2, COUNT1, &swaps2, &comparisons2);
    selectSort_good(arr3, COUNT1, &swaps3, &comparisons3);
    int swaps4, comparisons4;
    int swaps5, comparisons5;
    int swaps6, comparisons6;
    selectSort_bad(arr4, COUNT1, &swaps4, &comparisons4);
    selectSort_bad(arr5, COUNT1, &swaps5, &comparisons5);
    selectSort_bad(arr6, COUNT1, &swaps6, &comparisons6);
    int teoret1;
    teoret1 = (3*(COUNT1 - 1)) + (COUNT1*COUNT1 - COUNT1)/2;
    printf(" N | M+C Теор. | Убыв. | Возр. | Случ. | Убыв. | Возр. | Случ. |\n");
    printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t\n", COUNT1, teoret1, swaps1 + comparisons1, swaps2 + comparisons2, swaps3 + comparisons3, swaps4 + comparisons4, swaps5 + comparisons5, swaps6 + comparisons6);
    int swaps1_1, comparisons1_1;
    int swaps2_1, comparisons2_1;
    int swaps3_1, comparisons3_1;
    selectSort_good(arr1_1, COUNT2, &swaps1_1, &comparisons1_1);
    selectSort_good(arr2_1, COUNT2, &swaps2_1, &comparisons2_1);
    selectSort_good(arr3_1, COUNT2, &swaps3_1, &comparisons3_1);
    int swaps4_1, comparisons4_1;
    int swaps5_1, comparisons5_1;   
    int swaps6_1, comparisons6_1;
    selectSort_bad(arr4_1, COUNT2, &swaps4_1, &comparisons4_1);
    selectSort_bad(arr5_1, COUNT2, &swaps5_1, &comparisons5_1);
    selectSort_bad(arr6_1, COUNT2, &swaps6_1, &comparisons6_1);
    int teoret2;
    teoret2 = (3*(COUNT2 - 1)) + (COUNT2*COUNT2 - COUNT2)/2;
    printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t\n", COUNT2, teoret2, swaps1_1 + comparisons1_1, swaps2_1 + comparisons2_1, swaps3_1 + comparisons3_1, swaps4_1 + comparisons4_1, swaps5_1 + comparisons5_1, swaps6_1 + comparisons6_1);
    free(arr1);
    free(arr2);
    free(arr3);
    free(arr4);
    free(arr5);
    free(arr6);
    free(arr1_1);
    free(arr2_1);
    free(arr3_1);
    free(arr4_1);
    free(arr5_1);
    free(arr6_1);

    return 0;
}
