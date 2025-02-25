#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define COUNT 5

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

void FillRand(int n, int A[]){
    for (int i = 0; i < n; i++){
        A[i] = rand() % 1000;
    }
}

int CheckSum(int A[], int n){
    int sum = 0;
    for (int i = 0; i < n; i++){
        sum += A[i];
    }
    return sum;
}

int RunNumber(int A[], int n){
    int cnt = 1;
    for (int i = 0; i < n; i++){
        if (A[i] < A[i-1]){
            cnt += 1;
        }
    }
    return cnt;
}

void PrintMas(int A[], int n){
    for (int i = 0; i < n; i++){
        printf("%d ", A[i]);
    }
}

int main() {
    int arr[COUNT];
    int n = COUNT;
    FillRand(n, arr);
    int comparisons, swaps;
    ShakerSort(arr, n, &comparisons, &swaps);
    printf("Отсортированный массив: ");
    PrintMas(arr, n);
    printf("\n");
    printf("Контрольная сумма: %d\n", CheckSum(arr, n));
    printf("Число серий: %d\n", RunNumber(arr, n));
    printf("Фактическое количество сравнений (Сф): %d\n", comparisons);
    printf("Фактическое количество пересылок (Мф): %d\n", swaps);

    return 0;
}
