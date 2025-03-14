#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shellSort(int arr[], int n, int *M, int *C) {
    int gaps[] = {5, 3, 1}; 
    int numGaps = sizeof(gaps) / sizeof(gaps[0]);
    
    for (int g = 0; g < numGaps; g++) {
        int gap = gaps[g];
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            (*M)++;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                (*C)++; 
                arr[j] = arr[j - gap];
                (*M)++;
            }
            arr[j] = temp;
            (*M)++;
        }
    }
}

int checksum(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

int countSeries(int arr[], int n) {
    int count = 1;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            count++;
        }
    }
    return count;
}

int main() {
    int n = 10;
    int arr[n];
    srand(time(NULL));
    
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }
    
    printf("Исходный массив: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    int M = 0, C = 0;
    int sumBefore = checksum(arr, n);
    int seriesBefore = countSeries(arr, n);
    
    shellSort(arr, n, &M, &C);
    
    printf("Отсортированный массив: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    int sumAfter = checksum(arr, n);
    int seriesAfter = countSeries(arr, n);
    
    printf("Контрольная сумма до: %d, после: %d\n", sumBefore, sumAfter);
    printf("Число серий до: %d, после: %d\n", seriesBefore, seriesAfter);
    printf("Фактические пересылки (Мф): %d\n", M);
    printf("Фактические сравнения (Сф): %d\n", C);
    
    return 0;
}
