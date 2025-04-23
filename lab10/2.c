#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int move_count = 0;
int compare_count = 0;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    move_count += 3;
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    compare_count++;
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    compare_count++;
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void buildHeap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

void heapSort(int arr[], int n) {
    move_count = 0;
    compare_count = 0;
    
    buildHeap(arr, n);

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int calculateChecksum(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

int countRuns(int arr[], int n) {
    if (n == 0) return 0;
    int runs = 1;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i-1]) {
            runs++;
        }
    }
    return runs;
}

int theoreticalComplexity(int n) {
    return 2 * n * (int)(log(n)/log(2)) + (int)(1.5 * n * log(n)/log(2));
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));
    int n = 10;
    int arr[n];

    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }

    printf("Original array: ");
    printArray(arr, n);

    int checksum_before = calculateChecksum(arr, n);
    int runs_before = countRuns(arr, n);

    heapSort(arr, n);

    int checksum_after = calculateChecksum(arr, n);
    int runs_after = countRuns(arr, n);

    printf("Sorted array: ");
    printArray(arr, n);

    printf("Checksum before: %d, after: %d\n", checksum_before, checksum_after);
    printf("Number of runs before: %d, after: %d\n", runs_before, runs_after);
    printf("Move operations: %d, Compare operations: %d\n", move_count, compare_count);
    printf("Theoretical complexity: %d\n", theoreticalComplexity(n));

    return 0;
}