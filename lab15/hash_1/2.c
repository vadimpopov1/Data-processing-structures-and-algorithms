#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct HashNode {
    int character;
    struct HashNode* next;
} HashNode;

int addToHashTable(HashNode** table, int size, int char_code, int* is_unique) {
    int index = char_code % size;
    HashNode* current = table[index];
    *is_unique = 1;
    while (current != NULL) {
        if (current->character == char_code) {
            *is_unique = 0;
            return 0;
        }
        current = current->next;
    }

    int collision_occurred = (table[index] != NULL);

    HashNode* new_entry = (HashNode*)malloc(sizeof(HashNode));
    if (!new_entry) exit(EXIT_FAILURE);
    new_entry->character = char_code;
    new_entry->next = table[index];
    table[index] = new_entry;

    return collision_occurred;
}

void freeHashTable(HashNode** table, int size) {
    for (int i = 0; i < size; i++) {
        HashNode* current = table[i];
        while (current) {
            HashNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(table);
}

void generateShakespeareText(char* buffer, size_t length) {
    const char romeoJuliet[] = 
        "Two households both alike in dignity"
        "In fair Verona where we lay our scene"
        "From ancient grudge break to new mutiny"
        "Where civil blood makes civil hands unclean"
        "From forth the fatal loins of these two foes"
        "A pair of star-crossd lovers take their life"
        "Whose misadventured piteous overthrows"
        "Do with their death bury their parents strife"
        "The fearful passage of their death-markd love"
        "And the continuance of their parents rage"
        "Which, but their childrens end, nought could remove"
        "Is now the two hours traffic of our stage"
        "The which if you with patient ears attend"
        "What here shall miss our toil shall strive to mend";
    
    for (size_t i = 0; i < length - 1; i++) {
        buffer[i] = romeoJuliet[rand() % (sizeof(romeoJuliet) - 1)];
    }
    buffer[length - 1] = '\0';
}

void printTableHeader() {
    printf("┌────────────────┬─────────────────────┬────────────────┐\n");
    printf("│ Размер таблицы │ Уникальных символов │ Всего коллизий │\n");
    printf("├────────────────┼─────────────────────┼────────────────┤\n");
}

void printTableRow(int size, int unique, int collisions) {
    printf("│ %14d │ %19d │ %14d │\n", size, unique, collisions);
}

void printTableFooter() {
    printf("└────────────────┴─────────────────────┴────────────────┘\n");
}

int main() {
    srand(time(NULL));

    int table_sizes[] = {11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};
    int num_sizes = sizeof(table_sizes) / sizeof(table_sizes[0]);

    const size_t text_length = 1000;
    char* shakespeare_text = (char*)malloc(text_length + 1);
    generateShakespeareText(shakespeare_text, text_length + 1);

    printTableHeader();

    for (int i = 0; i < num_sizes; i++) {
        int current_size = table_sizes[i];

        HashNode** hash_table = (HashNode**)calloc(current_size, sizeof(HashNode*));
        if (!hash_table) {
            printf("Ошибка выделения памяти для хеш-таблицы.\n");
            free(shakespeare_text);
            return EXIT_FAILURE;
        }

        int total_collisions = 0;
        int unique_characters = 0;
        int ascii_set[256] = {0};

        for (size_t j = 0; j < text_length && shakespeare_text[j] != '\0'; j++) {
            int char_code = (int)shakespeare_text[j];
            if (ascii_set[char_code] == 0) {
                ascii_set[char_code] = 1;
                unique_characters++;
            }
            int is_unique;
            total_collisions += addToHashTable(hash_table, current_size, char_code, &is_unique);
        }

        printTableRow(current_size, unique_characters, total_collisions);

        freeHashTable(hash_table, current_size);
    }

    printTableFooter();

    free(shakespeare_text);
    return EXIT_SUCCESS;
}