    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    
    long comparisons = 0, moves = 0;

    void insertSort(int arr[], int n) {
        comparisons = 0;
        moves = 0;
        
        for (int i = 1; i < n; i++) {
            int key = arr[i];
            int j = i - 1;
            
            comparisons++; 
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
                moves++;      
                comparisons++; 
            }
            arr[j + 1] = key;
            moves++; 
        }
    }

    void generateDescending(int arr[], int n) {
        for (int i = 0; i < n; i++)
            arr[i] = n - i;
    }

    void generateRandom(int arr[], int n) {
        for (int i = 0; i < n; i++)
            arr[i] = rand() % 1000;
    }

    void generateAscending(int arr[], int n) {
        for (int i = 0; i < n; i++)
            arr[i] = i + 1;
    }

    int main() {
        srand(time(NULL)); 
        
        int sizes[] = {100, 200, 300, 400, 500}; 
        int numSizes = sizeof(sizes) / sizeof(sizes[0]);

        printf(" N   | M+C (теоретич.) | M+C (Убыв.) | M+C (Случ.) | M+C (Возр.)\n");
        printf("---------------------------------------------------------------\n");

        for (int i = 0; i < numSizes; i++) {
            int n = sizes[i];
            int arr[n];
            long theoretical = (n * n) / 2 + n/2 - 1;
            generateDescending(arr, n);
            insertSort(arr, n);
            long decreasing = moves + comparisons;
            generateRandom(arr, n);
            insertSort(arr, n);
            long random = moves + comparisons;
            generateAscending(arr, n);
            insertSort(arr, n);
            long increasing = moves + comparisons;
            printf("%-4d | %-15ld | %-11ld | %-11ld | %-11ld\n", n, theoretical, decreasing, random, increasing);
        }
    }
