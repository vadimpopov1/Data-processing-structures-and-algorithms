#include <stdio.h>
#include <string.h>

typedef struct {
    char first_name[50];
    char last_name[50];
    char phone_number[15];
    char address[100];
} PhoneRecord;

int compare_records(const PhoneRecord *a, const PhoneRecord *b) {
    int last_name_cmp = strcmp(a->last_name, b->last_name);
    if (last_name_cmp != 0) {
        return last_name_cmp;
    }
    return strcmp(a->first_name, b->first_name);
}

void insertion_sort(PhoneRecord arr[], int n) {
    for (int i = 1; i < n; i++) {
        PhoneRecord current = arr[i];
        int j = i - 1;
        while (j >= 0 && compare_records(&arr[j], &current) > 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = current;
    }
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
        {"Дмитрий", "Дмитриев", "444-444-444", "ул. Солнечная, 30"}
    };

    int n = sizeof(phone_book) / sizeof(phone_book[0]); 
    insertion_sort(phone_book, n);
    printf("Отсортированный телефонный справочник: (Сортировка по фамилии)\n");
    print_phone_book(phone_book, n);

    return 0;
}
