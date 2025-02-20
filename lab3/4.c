#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COUNT 1000

void BubbleSort(int arr[], int n, int *comparisons, int *swaps) {
    *comparisons = 0;
    *swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            (*comparisons)++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                (*swaps)++;
            }
        }
    }
}

void SelectSort(int arr[], int n, int *comparisons, int *swaps) {
    *comparisons = 0;
    *swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            (*comparisons)++;
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            int temp = arr[min_index];
            arr[min_index] = arr[i];
            arr[i] = temp;
            (*swaps)++;
        }
    }
}

int main() {
    srand(time(NULL));

    FILE *fp = fopen("data.txt", "w");
    if (fp == NULL) {
        printf("Error while openning file!\n");
        return 1;
    }

    for (int size = 1; size <= COUNT; size += 25) {
        int *arr1 = (int *)malloc(size * sizeof(int));
        int *arr2 = (int *)malloc(size * sizeof(int));
        for (int i = 0; i < size; i++) {
            int num = rand() % 100;
            arr1[i] = num;
            arr2[i] = num;
        }
        
        int comparisons_bubble, swaps_bubble;
        int comparisons_select, swaps_select;
        
        BubbleSort(arr1, size, &comparisons_bubble, &swaps_bubble);
        SelectSort(arr2, size, &comparisons_select, &swaps_select);
        
        fprintf(fp, "%d %d %d %d %d\n", size, comparisons_bubble, swaps_bubble, comparisons_select, swaps_select);
        
        free(arr1);
        free(arr2);
    }
    fclose(fp);

    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    if (gnuplotPipe == NULL) {
        perror("Ошибка открытия gnuplot");
        return EXIT_FAILURE;
    }

    fprintf(gnuplotPipe, "set title 'Сравнение BubbleSort и SelectSort'\n");
    fprintf(gnuplotPipe, "set xlabel 'Размер массива n'\n");
    fprintf(gnuplotPipe, "set ylabel 'M + C'\n");
    fprintf(gnuplotPipe, "plot 'data.txt' using 1:($2+$3) with linespoints title 'BubbleSort', \
                            'data.txt' using 1:($4+$5) with linespoints title 'SelectSort'\n");
    pclose(gnuplotPipe);

    return EXIT_SUCCESS;
}
