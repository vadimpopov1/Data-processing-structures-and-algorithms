#include <stdio.h>

void selectSort(int arr[], int n, int *comparisons, int *swaps) {
    *comparisons = 0;
    *swaps = 0;

    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            (*comparisons)++;
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        (*swaps) = *swaps + 3;
    }
}

int CheckSum(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

int RunNumber(int arr[], int n) {
    if (n == 0) return 0;

    int runs = 1;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            runs++;
        }
    }
    return runs;
}

void testSorting(int arr[], int n) {
    int comparisons, swaps;
    int sortedArr[n];

    for (int i = 0; i < n; i++) {
        sortedArr[i] = arr[i];
    }

    selectSort(sortedArr, n, &comparisons, &swaps);

    int checksum = CheckSum(sortedArr, n);
    int runs = RunNumber(sortedArr, n);

    printf("Исходный массив: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Отсортированный массив: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", sortedArr[i]);
    }
    printf("\n");

    printf("Контрольная сумма: %d\n", checksum);
    printf("Число серий: %d\n", runs);
    printf("Фактическое количество сравнений (Сф): %d\n", comparisons);
    printf("Фактическое количество пересылок (Мф): %d\n", swaps);

    int theoreticalComparisons = n * (n - 1) / 2;
    int theoreticalswaps = 3*(n - 1);

    printf("Теоретическое количество сравнений (С): %d\n", theoreticalComparisons);
    printf("Теоретическое количество пересылок (М): %d\n", theoreticalswaps);
}

int main() {
    int arr[] = {25, 30, 15, 10, 5};
    int n = 5;
    
    testSorting(arr, n);

    return 0;
}
