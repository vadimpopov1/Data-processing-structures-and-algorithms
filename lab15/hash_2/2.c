#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_TABLE_SIZE 101
#define EMPTY -1
#define DELETED -2

typedef struct {
    int symbol;
    int is_occupied;
} HashEntry;

const int table_sizes[] = {11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};
const int num_sizes = sizeof(table_sizes) / sizeof(table_sizes[0]);

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

void analyzeText(const char* text, int text_length) {
    printf("┌──────────────────┬──────────────────────┬──────────────────────┬──────────────────────┐\n");
    printf("│ Размер таблицы   │ Уникальные символы   │ Коллизии (линейные)  │ Коллизии (квадратич) │\n");
    printf("├──────────────────┼──────────────────────┼──────────────────────┼──────────────────────┤\n");

    int unique_chars[256] = {0};
    int total_unique = 0;
    
    for (int i = 0; i < text_length; i++) {
        if (text[i] != ' ' && !unique_chars[(unsigned char)text[i]]) {
            unique_chars[(unsigned char)text[i]] = 1;
            total_unique++;
        }
    }

    for (int i = 0; i < num_sizes; i++) {
        int size = table_sizes[i];
        HashEntry linear_table[MAX_TABLE_SIZE];
        HashEntry quadratic_table[MAX_TABLE_SIZE];
        
        int linear_collisions = 0;
        int quadratic_collisions = 0;
        
        initHashTable(linear_table, size);
        initHashTable(quadratic_table, size);
        
        for (int j = 0; j < text_length; j++) {
            if (text[j] != ' ') {
                insert(linear_table, size, text[j], &linear_collisions, 0);
                insert(quadratic_table, size, text[j], &quadratic_collisions, 1);
            }
        }
        
        printf("│ %16d │ %20d │ %20d │ %20d │\n", 
               size, total_unique, linear_collisions, quadratic_collisions);
    }
    
    printf("└──────────────────┴──────────────────────┴──────────────────────┴──────────────────────┘\n");
}

int main() {
    const char shakespeare_text[] = 
        "Two households both alike in dignity In fair Verona where we lay our scene "
        "From ancient grudge break to new mutiny Where civil blood makes civil hands unclean "
        "From forth the fatal loins of these two foes A pair of star-cross'd lovers take their life "
        "Whose misadventured piteous overthrows Do with their death bury their parents strife "
        "The fearful passage of their death-mark'd love And the continuance of their parents rage "
        "Which but their children end nought could remove Is now the two hours traffic of our stage "
        "The which if you with patient ears attend What here shall miss our toil shall strive to mend";
    
    analyzeText(shakespeare_text, strlen(shakespeare_text));
    
    return 0;
}