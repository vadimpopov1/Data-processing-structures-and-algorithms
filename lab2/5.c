#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COUNT 1000

void selectSort(int arr[], int n, int *comparisons, int *swaps) {
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
            (*swaps) += 3;
        }
    }
}

int main() {
    srand(time(NULL));

    FILE *fp = fopen("data.txt", "w");
    if (fp == NULL) {
        printf("Ошибка открытия файла!\n");
        return 1;
    }

    for (int size = 1; size <= COUNT; size+=25) {
        int *arr = (int *)malloc(size * sizeof(int));
        for (int i = 0; i < size; i++) {
            arr[i] = rand() % 100;
        }

        int comparisons, swaps;
        selectSort(arr, size, &comparisons, &swaps);

        fprintf(fp, "%d %d %d\n", size, comparisons, swaps);
        free(arr);
    }
    fclose(fp);
        FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    if (gnuplotPipe == NULL) {
        perror("Ошибка открытия gnuplot");
        return EXIT_FAILURE;
    }
    fprintf(gnuplotPipe, "set title 'Время выполнения SelectSort'\n");
    fprintf(gnuplotPipe, "set xlabel 'Размер массива n'\n");
    fprintf(gnuplotPipe, "set ylabel 'M + C'\n");
    fprintf(gnuplotPipe, "plot 'data.txt' with linespoints title 'SelectSort'\n");
    pclose(gnuplotPipe);
    return EXIT_SUCCESS;
}
