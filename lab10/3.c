#include <stdio.h>
#include <string.h>

typedef struct {
    char first_name[50];
    char last_name[50];
    char phone[15];
    char address[100];
} PhoneRecord;

int less(const PhoneRecord *a, const PhoneRecord *b) {
    int cmp_last = strcmp(a->last_name, b->last_name);
    if (cmp_last != 0) return cmp_last;
    return strcmp(a->first_name, b->first_name);
}

int less_phone(const PhoneRecord *a, const PhoneRecord *b) {
    return strcmp(a->phone, b->phone);
}

void insertion_sort(PhoneRecord *arr, int *indexes, int n, 
    int (*compare)(const PhoneRecord*, const PhoneRecord*)) {
    for (int i = 1; i < n; i++) {
        int key = indexes[i];
        int j = i - 1;
        while (j >= 0 && compare(&arr[indexes[j]], &arr[key]) > 0) {
            indexes[j + 1] = indexes[j];
            j--;
        }
        indexes[j + 1] = key;
    }
}

void print_phone_book(PhoneRecord *phone_book, int *indexes, int n) {
    printf("%-15s %-15s %-15s %-30s\n", "Фамилия", "Имя", "Телефон", "Адрес");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        int idx = indexes[i];
        printf("%-15s %-15s %-15s %-30s\n", 
               phone_book[idx].last_name, 
               phone_book[idx].first_name, 
               phone_book[idx].phone, 
               phone_book[idx].address);
    }
}

int main() {
    PhoneRecord phone_book[] = {
        {"Иван", "Иванов", "123-456-789", "ул. Ленина, 10"},
        {"Глеб", "Иванов", "444-111-333", "ул. Ленина, 22"},
        {"Петр", "Петров", "987-654-321", "ул. Пушкина, 5"},
        {"Алексей", "Сидоров", "555-555-555", "ул. Гагарина, 15"},
        {"Сергей", "Алексеев", "111-222-333", "ул. Мира, 20"},
        {"Дмитрий", "Дмитриев", "444-444-444", "ул. Солнечная, 30"}
    };
    int n = sizeof(phone_book) / sizeof(phone_book[0]);

    int indexes_by_name[n];
    int indexes_by_phone[n];
    
    for (int i = 0; i < n; i++) {
        indexes_by_name[i] = i;
        indexes_by_phone[i] = i;
    }
    printf("Индексный массив (без сортировки): ");
    for (int i = 0; i < n; i++) {
        printf("%d ", indexes_by_name[i]);
    }
    printf("\n");
    printf("\n");
    printf("Телефонный справочник (без сортировки):\n");
    print_phone_book(phone_book, indexes_by_name, n);
    printf("\n\n\n");
    insertion_sort(phone_book, indexes_by_name, n, less);
    insertion_sort(phone_book, indexes_by_phone, n, less_phone);
    printf("Индексный массив (отсортировано по фамилии и имени): ");
    for (int i = 0; i < n; i++) {
        printf("%d ", indexes_by_name[i]);
    }
    printf("\n");
    printf("Телефонный справочник (отсортировано по фамилии и имени):\n");
    print_phone_book(phone_book, indexes_by_name, n);
    printf("\n\n\n");
    printf("Индексный массив (отсортировано по номеру телефона): ");
    for (int i = 0; i < n; i++) {
        printf("%d ", indexes_by_phone[i]);
    }
    printf("\n");
    printf("\nТелефонный справочник (отсортировано по номеру телефона):\n");
    print_phone_book(phone_book, indexes_by_phone, n);
}