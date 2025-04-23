#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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

int binary_search_by_name(PhoneRecord *arr, int *indexes, int n, const char *last_name) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(arr[indexes[mid]].last_name, last_name);
        
        if (cmp == 0) {
            int result = indexes[mid];
            while (mid > 0 && strcmp(arr[indexes[mid-1]].last_name, last_name) == 0) {
                mid--;
                result = indexes[mid];
            }
            return result;
        }
        if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int binary_search_by_phone(PhoneRecord *arr, int *indexes, int n, const char *phone) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(arr[indexes[mid]].phone, phone);
        
        if (cmp == 0) return indexes[mid];
        if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

void print_record(PhoneRecord *record) {
    if (record == NULL) {
        printf("Запись не найдена\n");
        return;
    }
    printf("Найдена запись: %s %s, телефон: %s, адрес: %s\n", 
           record->last_name, record->first_name, record->phone, record->address);
}

void print_all_by_name(PhoneRecord *arr, int *indexes, int n, const char *last_name) {
    printf("Все записи с фамилией '%s':\n", last_name);
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(arr[indexes[i]].last_name, last_name) == 0) {
            print_record(&arr[indexes[i]]);
            found = 1;
        }
    }
    if (!found) {
        printf("Записей с такой фамилией не найдено\n");
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

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void to_lower_case(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
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

    int indexes[n];
    
    for (int i = 0; i < n; i++) {
        indexes[i] = i;
    }

    int choice;
    char search_key[50];
    print_phone_book(phone_book, indexes, n);
    printf("\n\n");
    do {
        printf("\nМеню поиска:\n");
        printf("1. Поиск по фамилии\n");
        printf("2. Поиск по номеру телефона\n");
        printf("0. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);
        clear_input_buffer();

        switch (choice) {
            case 1:
                printf("Введите фамилию для поиска: ");
                fgets(search_key, sizeof(search_key), stdin);
                search_key[strcspn(search_key, "\n")] = '\0'; 
                
                int found_idx = binary_search_by_name(phone_book, indexes, n, search_key);
                if (found_idx != -1) {
                    print_all_by_name(phone_book, indexes, n, search_key);
                } else {
                    printf("Записей с фамилией '%s' не найдено\n", search_key);
                }
                break;
                
            case 2:
                printf("Введите номер телефона для поиска: ");
                fgets(search_key, sizeof(search_key), stdin);
                search_key[strcspn(search_key, "\n")] = '\0';
                
                found_idx = binary_search_by_phone(phone_book, indexes, n, search_key);
                if (found_idx != -1) {
                    print_record(&phone_book[found_idx]);
                } else {
                    printf("Записи с телефоном '%s' не найдено\n", search_key);
                }
                break;
            case 0:
                printf("Выход из программы...\n");
                break;
                
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 0);

    return 0;
}