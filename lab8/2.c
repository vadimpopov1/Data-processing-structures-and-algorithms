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

    printf("Сравнение записей:\n");
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int cmp = compare_records(&phone_book[i], &phone_book[j]);
            if (cmp < 0) {
                printf("%s %s < %s %s\n", phone_book[i].last_name, phone_book[i].first_name,
                       phone_book[j].last_name, phone_book[j].first_name);
            } else if (cmp > 0) {
                printf("%s %s > %s %s\n", phone_book[i].last_name, phone_book[i].first_name,
                       phone_book[j].last_name, phone_book[j].first_name);
            } else {
                printf("%s %s == %s %s\n", phone_book[i].last_name, phone_book[i].first_name,
                       phone_book[j].last_name, phone_book[j].first_name);
            }
        }
    }

    return 0;
}