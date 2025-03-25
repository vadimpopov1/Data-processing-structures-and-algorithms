#include <stdio.h>
#include <string.h>

typedef struct {
    char first_name[50];
    char last_name[50];
    char phone_number[15];
    char address[100];
} PhoneRecord;

int less(PhoneRecord x, PhoneRecord y) {
    int last_name_comparison = strcmp(x.last_name, y.last_name);
    if (last_name_comparison < 0) {
        return 1;
    } else if (last_name_comparison > 0) {
        return 0;
    } else {
        return strcmp(x.first_name, y.first_name) < 0;
    }
}

void print_phone_book(PhoneRecord arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s %s: %s, %s\n", arr[i].first_name, arr[i].last_name, arr[i].phone_number, arr[i].address);
    }
}

void find_records_by_last_name(PhoneRecord arr[], int n, const char *last_name) {
    int found = 0;
    PhoneRecord first_record;
    int first_found = 0;

    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i].last_name, last_name) == 0) {
            printf("Найдена запись: %s %s: %s, %s\n", arr[i].first_name, arr[i].last_name, arr[i].phone_number, arr[i].address);
            found = 1;

            if (!first_found) {
                first_record = arr[i];
                first_found = 1;
            } else {
                if (less(arr[i], first_record)) {
                    first_record = arr[i];
                }
            }
        }
    }

    if (!found) {
        printf("Запись с фамилией '%s' не найдена.\n", last_name);
    } else {
        printf("\nПервая запись: %s %s: %s, %s\n", first_record.first_name, first_record.last_name,
               first_record.phone_number, first_record.address);
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

    printf("Телефонный справочник:\n");
    print_phone_book(phone_book, n);
    printf("\n");

    char search_last_name[50];
    printf("Введите фамилию для поиска: ");
    scanf("%s", search_last_name);

    find_records_by_last_name(phone_book, n, search_last_name);

    return 0;
}