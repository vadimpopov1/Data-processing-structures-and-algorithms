#include <stdio.h>

typedef struct {
    int comparisons;
    int swaps;
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

int calculate_checksum(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

int count_runs(int arr[], int n) {
    if (n == 0) return 0;
    int runs = 1;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            runs++;
        }
    }
    return runs;
}

void analyze_sorting(int arr[], int n) {
    int arr_copy[n];
    for (int i = 0; i < n; i++) {
        arr_copy[i] = arr[i];
    }

    Stats stats = {0, 0};
    quick_sort(arr_copy, 0, n - 1, &stats);

    int checksum = calculate_checksum(arr_copy, n);
    int runs = count_runs(arr_copy, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr_copy[i]);
    }
    printf("\nChecksum: %d\n", checksum);
    printf("Runs: %d\n", runs);
    printf("\nActual:\nComparisons: %d\nSwaps: %d\n", stats.comparisons, stats.swaps);

    int theoretical_comparisons = n * (n - 1) / 2;
    int theoretical_swaps = n * (n - 1) / 4;
    printf("\nTheoretical:\nComparisons: %d\nSwaps: %d\n", theoretical_comparisons, theoretical_swaps);
}

int main() {
    int array[] = {5, 3, 8, 4, 2, 7, 1, 10, 6, 9};
    int n = sizeof(array) / sizeof(array[0]);
    analyze_sorting(array, n);
    return 0;
}
