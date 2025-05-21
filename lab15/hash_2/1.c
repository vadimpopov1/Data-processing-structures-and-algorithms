#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 23
#define EMPTY -1
#define DELETED -2

typedef struct {
    int symbol;
    int is_occupied;
} HashEntry;

void initHashTable(HashEntry* table, int size) {
    for (int i = 0; i < size; i++) {
        table[i].symbol = EMPTY;
        table[i].is_occupied = 0;
    }
}

int hashFunction(int key, int size) {
    return key % size;
}

int linearProbe(HashEntry* table, int size, int key, int* collisions) {
    int index = hashFunction(key, size);
    int original_index = index;
    
    while (table[index].is_occupied && table[index].symbol != key) {
        (*collisions)++;
        index = (index + 1) % size;
        if (index == original_index) return -1;
    }
    
    return index;
}

int quadraticProbe(HashEntry* table, int size, int key, int* collisions) {
    int index = hashFunction(key, size);
    int original_index = index;
    int i = 1;
    
    while (table[index].is_occupied && table[index].symbol != key) {
        (*collisions)++;
        index = (original_index + i * i) % size;
        i++;
        if (i > size) return -1; 
    }
    
    return index;
}

void insert(HashEntry* table, int size, int key, int* collisions, int use_quadratic) {
    int index;
    
    if (use_quadratic) {
        index = quadraticProbe(table, size, key, collisions);
    } else {
        index = linearProbe(table, size, key, collisions);
    }
    
    if (index != -1) {
        table[index].symbol = key;
        table[index].is_occupied = 1;
    }
}

void printHashTable(HashEntry* table, int size) {
    printf("┌─────────────┬─────────┐\n");
    printf("│ Номер ячейки │ Символ  │\n");
    printf("├─────────────┼─────────┤\n");
    
    for (int i = 0; i < size; i++) {
        if (table[i].is_occupied) {
            printf("│ %11d │ %7c │\n", i, table[i].symbol);
        } else {
            printf("│ %11d │ %7s │\n", i, table[i].symbol == DELETED ? "DEL" : "EMPTY");
        }
    }
    
    printf("└─────────────┴─────────┘\n");
}

void fillWithShakespeareText(HashEntry* table, int size, int* collisions, int use_quadratic) {
    const char text[] = 
        "Two households both alike in dignity In fair Verona where we lay our scene "
        "From ancient grudge break to new mutiny Where civil blood makes civil hands unclean";
    
    for (size_t i = 0; i < strlen(text); i++) {
        if (text[i] != ' ') {  // Исключаем пробелы
            insert(table, size, text[i], collisions, use_quadratic);
        }
    }
}

int main() {
    HashEntry linear_table[TABLE_SIZE];
    HashEntry quadratic_table[TABLE_SIZE];
    
    int linear_collisions = 0;
    int quadratic_collisions = 0;

    initHashTable(linear_table, TABLE_SIZE);
    initHashTable(quadratic_table, TABLE_SIZE);

    fillWithShakespeareText(linear_table, TABLE_SIZE, &linear_collisions, 0);
    fillWithShakespeareText(quadratic_table, TABLE_SIZE, &quadratic_collisions, 1);
    printf("\nЛинейное пробирование:\n");
    printHashTable(linear_table, TABLE_SIZE);
    printf("Количество коллизий: %d\n\n", linear_collisions);
    
    printf("Квадратичное пробирование:\n");
    printHashTable(quadratic_table, TABLE_SIZE);
    printf("Количество коллизий: %d\n\n", quadratic_collisions);
    
    printf("┌────────────────────┬──────────────┐\n");
    printf("│ Метод пробирования │ Коллизии     │\n");
    printf("├────────────────────┼──────────────┤\n");
    printf("│ Линейное           │ %12d │\n", linear_collisions);
    printf("│ Квадратичное       │ %12d │\n", quadratic_collisions);
    printf("└────────────────────┴──────────────┘\n");
    
    return 0;
}