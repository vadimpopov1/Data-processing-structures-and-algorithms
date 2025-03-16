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

int binarySearchRecursive(int arr[], int low, int high, int key, int *comparisons) {
    if (high >= low) {
        (*comparisons)++;
        int mid = low + (high - low) / 2;
        if (arr[mid] == key)
            return mid;
        if (arr[mid] > key)
            return binarySearchRecursive(arr, low, mid - 1, key, comparisons);
        return binarySearchRecursive(arr, mid + 1, high, key, comparisons);
    }
    return -1;
}

void FillRand(int n, int A[]) {
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 1000; 
    }
}

int main() {

    int sizes[] = {100, 500, 1000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("| N\t| Сф I\t| Сф II\t|\n");

    for (int i = 0; i < 3; i++) {
        int n = sizes[i];
        int arr[n];
        srand(time(NULL));
        FillRand(n, arr);
        shellSort(arr, n);
        int m = rand() % n;
        int key = arr[m];
        int comparisons1 = 0, comparisons2 = 0;
        binarySearchIterative(arr, n, key, &comparisons1);
        binarySearchRecursive(arr, 0, n - 1, key, &comparisons2);
        printf("| %d\t| %d\t| %d\t|\n", n, comparisons1, comparisons2);
    }

    return 0;
}