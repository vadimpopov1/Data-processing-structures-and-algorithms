#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char first_name[50];
    char last_name[50];
    char phone_number[15];
    char address[100];
} PhoneRecord;

typedef enum {
    SORT_BY_LAST_NAME,
    SORT_BY_FIRST_NAME,
    SORT_BY_PHONE_NUMBER,
    EXIT_PROGRAM
} SortKey;

typedef enum {
    SORT_ASCENDING,
    SORT_DESCENDING
} SortDirection;

SortKey current_sort_key = SORT_BY_LAST_NAME;
SortDirection current_sort_direction = SORT_ASCENDING;

int less(const PhoneRecord *a, const PhoneRecord *b) {
    int cmp;
    switch (current_sort_key) {
        case SORT_BY_LAST_NAME:
            cmp = strcmp(a->last_name, b->last_name);
            if (cmp != 0) return cmp < 0;
            cmp = strcmp(a->first_name, b->first_name);
            return cmp < 0;
        case SORT_BY_FIRST_NAME:
            cmp = strcmp(a->first_name, b->first_name);
            if (cmp != 0) return cmp < 0;
            cmp = strcmp(a->last_name, b->last_name);
            return cmp < 0; 
        case SORT_BY_PHONE_NUMBER:
            cmp = strcmp(a->phone_number, b->phone_number);
            return cmp < 0; 
        default:
            return 0;
    }
}

int compare_records(const void *a, const void *b) {
    const PhoneRecord *record_a = (const PhoneRecord *)a;
    const PhoneRecord *record_b = (const PhoneRecord *)b;

    int cmp = less(record_a, record_b) ? -1 : (less(record_b, record_a) ? 1 : 0);

    return current_sort_direction == SORT_DESCENDING ? -cmp : cmp;
}

void print_phone_book(PhoneRecord arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s %s: %s, %s\n", arr[i].first_name, arr[i].last_name, arr[i].phone_number, arr[i].address);
    }
}

int main() {
    PhoneRecord phone_book[] = {
        {"Иван", "Иванов", "123-456-789", "ул. Ленина, 10"},
        {"Глеб", "Иванов", "444-111-333", "ул. Ленина, 22"},
        {"Петр", "Петров", "987-654-321", "ул. Пушкина, 5"},
        {"Алексей", "Сидоров", "555-555-555", "ул. Гагарина, 15"},
        {"Сергей", "Алексеев", "111-222-333", "ул. Мира, 20"},
        {"Дмитрий", "Дмитриев", "444-444-444", "ул. Солнечная, 30"},
        {"Александр", "Иванов", "999-999-999", "ул. Примерная, 8"}
    };

    int n = sizeof(phone_book) / sizeof(phone_book[0]);

    while (1) {
        printf("\nВыберите действие:\n");
        printf("1. Сортировать по фамилии (по возрастанию)\n");
        printf("2. Сортировать по фамилии (по убыванию)\n");
        printf("3. Сортировать по имени (по возрастанию)\n");
        printf("4. Сортировать по имени (по убыванию)\n");
        printf("5. Сортировать по номеру телефона (по возрастанию)\n");
        printf("6. Сортировать по номеру телефона (по убыванию)\n");
        printf("0. Выйти из программы\n");
        printf("Ваш выбор: ");

        int choice;
        scanf("%d", &choice); 

        switch (choice) {
            case 1:
                current_sort_key = SORT_BY_LAST_NAME;
                current_sort_direction = SORT_ASCENDING;
                break;
            case 2:
                current_sort_key = SORT_BY_LAST_NAME;
                current_sort_direction = SORT_DESCENDING;
                break;
            case 3:
                current_sort_key = SORT_BY_FIRST_NAME;
                current_sort_direction = SORT_ASCENDING;
                break;
            case 4:                current_sort_key = SORT_BY_FIRST_NAME;
            current_sort_direction = SORT_DESCENDING;
            break;
        case 5:
            current_sort_key = SORT_BY_PHONE_NUMBER;
            current_sort_direction = SORT_ASCENDING;
            break;
        case 6:
            current_sort_key = SORT_BY_PHONE_NUMBER;
            current_sort_direction = SORT_DESCENDING;
            break;
        case 0:
            printf("Завершение программы.\n");
            return 0;
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
            continue;
    }
    printf("\nНеотсортированный телефонный справочник:\n");
    print_phone_book(phone_book, n);
    qsort(phone_book, n, sizeof(PhoneRecord), compare_records);
    printf("\nОтсортированный телефонный справочник:\n");
    print_phone_book(phone_book, n);
}

return 0;
}