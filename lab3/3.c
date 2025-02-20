#include <gtk/gtk.h>
#include <stdlib.h>
#include <time.h>

void BubbleSort(int arr[], int n, int *comparisons, int *swaps);
int theoretical_workload(int n);
void FillInc(int A[], int n);
void FillDec(int A[], int n);
void FillRand(int A[], int n);

void add_results_to_grid(GtkGrid *grid, int row, int n) {
    int *arr = (int *)malloc(n * sizeof(int));
    char buffer[256];

    // Теоретическая нагрузка
    int workload_theoretical = theoretical_workload(n);
    
    // Убывающий массив
    FillDec(arr, n);
    int comparisons_desc, swaps_desc;
    BubbleSort(arr, n, &comparisons_desc, &swaps_desc);
    int workload_desc = comparisons_desc + swaps_desc;

    // Случайный массив
    FillRand(arr, n);
    int comparisons_rand, swaps_rand;
    BubbleSort(arr, n, &comparisons_rand, &swaps_rand);
    int workload_rand = comparisons_rand + swaps_rand;

    // Возрастающий массив
    FillInc(arr, n);
    int comparisons_asc, swaps_asc;
    BubbleSort(arr, n, &comparisons_asc, &swaps_asc);
    int workload_asc = comparisons_asc + swaps_asc;

    // Заполнение сетки результатами
    snprintf(buffer, sizeof(buffer), "%d", n);
    gtk_grid_attach(grid, gtk_label_new(buffer), 0, row, 1, 1);
    
    snprintf(buffer, sizeof(buffer), "%d", workload_theoretical);
    gtk_grid_attach(grid, gtk_label_new(buffer), 1, row, 1, 1);

    snprintf(buffer, sizeof(buffer), "%d", workload_desc);
    gtk_grid_attach(grid, gtk_label_new(buffer), 2, row, 1, 1);

    snprintf(buffer, sizeof(buffer), "%d", workload_rand);
    gtk_grid_attach(grid, gtk_label_new(buffer), 3, row, 1, 1);

    snprintf(buffer, sizeof(buffer), "%d", workload_asc);
    gtk_grid_attach(grid, gtk_label_new(buffer), 4, row, 1, 1);

    free(arr);
}

void create_table(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog;
    GtkWidget *grid;
    int sizes[] = {100, 200, 300, 400, 500};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    dialog = gtk_dialog_new_with_buttons("Результаты сортировки", NULL, GTK_DIALOG_MODAL,
                                         GTK_STOCK_OK, GTK_RESPONSE_OK,
                                         NULL);
    
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dialog))), grid);
    
    // Заголовки таблицы
    const char *headers[] = {"N", "M+C (теоретич.)", "M+C (убыв.)", "M+C (случ.)", "M+C (возр.)"};
    for (int i = 0; i < 5; i++) {
        gtk_grid_attach(GTK_GRID(grid), gtk_label_new(headers[i]), i, 0, 1, 1);
    }

    // Добавление результатов в таблицу
    for (int i = 0; i < num_sizes; i++) {
        add_results_to_grid(GTK_GRID(grid), i + 1, sizes[i]);
    }

    gtk_widget_show_all(dialog); // Показываем все элементы диалога
}