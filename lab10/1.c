#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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
    move_count = 0;
    compare_count = 0;
    
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

void generateDecreasingArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}

void generateRandomArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
}

void generateIncreasingArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
}

// Теоретическая оценка для сравнений
double theoreticalCompare(int n) {
    return 2 * log2(n);
}

// Теоретическая оценка для перемещений
double theoreticalMove(int n) {
    return 2 * log2(n) + 2;
}

int main() {
    srand(time(NULL));
    int sizes[] = {100, 200, 300, 400, 500};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    printf("Трудоемкость построения пирамиды\n");
    printf("| N    | Теория C+M | Мфакт+Сфакт |\n");
    printf("|      |            | Убыв.    | Случ.    | Возр.    |\n");
    
    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        int *arr = (int *)malloc(n * sizeof(int));
        
        double theoryC = theoreticalCompare(n);
        double theoryM = theoreticalMove(n);
        double theoryCM = theoryC + theoryM;

        generateDecreasingArray(arr, n);
        buildHeap(arr, n);
        int dec = move_count + compare_count;

        generateRandomArray(arr, n);
        buildHeap(arr, n);
        int rand = move_count + compare_count;
        
        generateIncreasingArray(arr, n);
        buildHeap(arr, n);
        int inc = move_count + compare_count;
        
        printf("| %-4d | %-10.2f | %-8d | %-8d | %-8d |\n", 
               n, theoryCM, dec, rand, inc);
        
        free(arr);
    }
    
    return 0;
}
