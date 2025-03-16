#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shellSort(int arr[], int n) {
    int gaps[] = {5, 3, 1}; 
    int numGaps = sizeof(gaps) / sizeof(gaps[0]);
    
    for (int g = 0; g < numGaps; g++) {
        int gap = gaps[g];
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

int binarySearchIterative(int arr[], int n, int key, int *comparisons) {
    int low = 0, high = n - 1;
    while (low <= high) {
        (*comparisons)++;
        int mid = low + (high - low) / 2;
        if (arr[mid] == key)
            return mid;
        if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

void FillRand(int n, int A[]){
    for (int i = 0; i < n; i++){
        A[i] = rand() % 10;
    }
}

void PrintMas(int n, int A[]){
    for (int i = 0; i < n; i++){
        printf("%d ", A[i]);
    }
}

int main() {
    int arr[100];
    int n = 100;
    FillRand(n, arr);
    shellSort(arr, n);
    PrintMas(n, arr);
    printf("\n");
    int key, comparisons = 0;

    printf("Введите ключ поиска: ");
    scanf("%d", &key);

    int result = binarySearchIterative(arr, n, key, &comparisons);

    if (result != -1) {
        printf("Элемент найден на позиции %d\n", result);
    } else {
        printf("Элемент не найден\n");
    }

    printf("Количество сравнений: %d\n", comparisons);

    return 0;
}
