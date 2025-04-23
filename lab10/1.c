#include <stdio.h>
#include <string.h>

typedef struct {
    char first_name[50];
    char last_name[50];
    char phone[15];
    char address[100];
} PhoneRecord;

int compare_records(const PhoneRecord *a, const PhoneRecord *b) {
    int cmp_last = strcmp(a->last_name, b->last_name);
    if (cmp_last != 0) {
        return cmp_last;
    }
    return strcmp(a->first_name, b->first_name);
}

void bubble_sort(PhoneRecord *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (compare_records(&arr[j], &arr[j + 1]) > 0) {
                PhoneRecord temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) break;
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
    printf("Неотсортированный список:\n");
    printf("-------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%s %s %s %s:\n", phone_book[i].last_name, phone_book[i].first_name, phone_book[i].phone, phone_book[i].address);
    }
    printf("\n"); 
    bubble_sort(phone_book, n);
    printf("Отсортированный список:\n");
    printf("-------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%s %s %s %s:\n", phone_book[i].last_name, phone_book[i].first_name, phone_book[i].phone, phone_book[i].address);
    }
    return 0;
}
