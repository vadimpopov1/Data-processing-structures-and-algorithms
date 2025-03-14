#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE_COUNT 5
int sizes[SIZE_COUNT] = {100, 200, 300, 400, 500};

typedef struct {
    int comparisons;
    int swaps;
} Complexity;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selectSort(int arr[], int n, Complexity *c) {
    c->comparisons = 0;
    c->swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            c->comparisons++;
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swap(&arr[i], &arr[minIdx]);
            c->swaps++;
        }
    }
}

void bubbleSort(int arr[], int n, Complexity *c) {
    c->comparisons = 0;
    c->swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            c->comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                c->swaps++;
            }
        }
    }
}

void shakerSort(int arr[], int n, Complexity *c) {
    c->comparisons = 0;
    c->swaps = 0;
    int left = 0, right = n - 1;
    while (left < right) {
        for (int i = left; i < right; i++) {
            c->comparisons++;
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i + 1]);
                c->swaps++;
            }
        }
        right--;
        for (int i = right; i > left; i--) {
            c->comparisons++;
            if (arr[i] < arr[i - 1]) {
                swap(&arr[i], &arr[i - 1]);
                c->swaps++;
            }
        }
        left++;
    }
}

void insertSort(int arr[], int n, Complexity *c) {
    c->comparisons = 0;
    c->swaps = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            c->comparisons++;
            arr[j + 1] = arr[j];
            j--;
            c->swaps++;
        }
        arr[j + 1] = key;
    }
}

void fillArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
}

void printResults() {
    printf("+-----+----------------+----------------+----------------+----------------+\n");
    printf("|  n  | Select (M+C)  | Bubble (M+C)  | Shaker (M+C)  | Insert (M+C)  |\n");
    printf("+-----+----------------+----------------+----------------+----------------+\n");
    for (int s = 0; s < SIZE_COUNT; s++) {
        int n = sizes[s];
        int arr[n];
        Complexity c;
        
        fillArray(arr, n);
        selectSort(arr, n, &c);
        int selectC = c.comparisons + c.swaps;
        
        fillArray(arr, n);
        bubbleSort(arr, n, &c);
        int bubbleC = c.comparisons + c.swaps;
        
        fillArray(arr, n);
        shakerSort(arr, n, &c);
        int shakerC = c.comparisons + c.swaps;
        
        fillArray(arr, n);
        insertSort(arr, n, &c);
        int insertC = c.comparisons + c.swaps;
        
        printf("| %-4d | %-14d | %-14d | %-14d | %-14d |\n", n, selectC, bubbleC, shakerC, insertC);
    }
    printf("+-----+----------------+----------------+----------------+----------------+\n");
}

int main() {
    srand(time(NULL));
    printResults();
    return 0;
}
