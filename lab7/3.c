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

int binarySearch(int array[], int size, int target, int *comparisons) {
    int left = 0;
    int right = size - 1;
    
    while (left <= right) {
        int mid = (left + right) / 2;
        (*comparisons)++;
        if (array[mid] == target) {
            return mid;
        }
        (*comparisons)++;
        if (array[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int binarySearchUpper(int array[], int size, int target, int *comparisons) {
    int left = 0;
    int right = size - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        (*comparisons)++;
        if (array[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    (*comparisons)++;
    if (left < size && array[left] == target) {
        return left;
    } else {
        return -1;
    }
}

void fillRandom(int n, int array[]) {
    for (int i = 0; i < n; i++) {
        array[i] = rand() % 1000; 
    }
}

int main() {
    int sizes[] = {100, 500, 1000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("| N\t| C1\t| C2\t|\n");

    for (int i = 0; i < numSizes; i++) {
        int n = sizes[i];
        int arr[n];
        srand(time(NULL));
        fillRandom(n, arr);
        shellSort(arr, n);
        int m = rand() % n;
        int key = arr[m];
        int comparisons1 = 0, comparisons2 = 0;
        binarySearch(arr, n, key, &comparisons1);
        binarySearchUpper(arr, n, key, &comparisons2);
        printf("| %d\t| %d\t| %d\t|\n", n, comparisons1, comparisons2);
    }

    return 0;
}
