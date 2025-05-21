#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct Node {
    int key;
    struct Node* next;
} Node;

typedef struct {
    Node** table;     // Массив указателей на списки
    int size;         // Размер таблицы
    int collisions;   // Количество коллизий
} HashTable;

Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

HashTable* initHashTable(int size) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    if (!ht) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    
    ht->size = size;
    ht->collisions = 0;
    ht->table = (Node**)malloc(size * sizeof(Node*));
    if (!ht->table) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    
    for (int i = 0; i < size; i++) {
        ht->table[i] = NULL;
    }
    
    return ht;
}

int hashFunction(int key, int size) {
    return key % size;
}

void insert(HashTable* ht, int key) {
    int index = hashFunction(key, ht->size);
    Node* newNode = createNode(key);
    
    if (ht->table[index] != NULL) {
        ht->collisions++;
        newNode->next = ht->table[index];
    }
    ht->table[index] = newNode;
}

int search(HashTable* ht, int key) {
    int index = hashFunction(key, ht->size);
    Node* current = ht->table[index];
    
    while (current != NULL) {
        if (current->key == key) {
            return 1; // Найден
        }
        current = current->next;
    }
    
    return 0; // Не найден
}

void display(HashTable* ht) {
    printf("Хеш-таблица (размер = %d):\n", ht->size);
    for (int i = 0; i < ht->size; i++) {
        printf("Индекс %d: ", i);
        Node* current = ht->table[i];
        while (current != NULL) {
            printf("%d -> ", current->key);
            current = current->next;
        }
        printf("NULL\n");
    }
    printf("Количество коллизий: %d\n", ht->collisions);
}

int binarySearch(int arr[], int size, int key) {
    int left = 0;
    int right = size - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key) {
            return 1;
        } else if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return 0;
}

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void comparePerformance() {
    const int dataSize = 10000;
    const int testSize = 100;
    int data[dataSize];
    int testKeys[testSize + 10];
    
    srand(time(NULL));
    for (int i = 0; i < dataSize; i++) {
        data[i] = rand() % 100000;
    }
    
    int hashSize = (int)(dataSize * 1.3);
    HashTable* ht = initHashTable(hashSize);
    
    for (int i = 0; i < dataSize; i++) {
        insert(ht, data[i]);
    }
    
    int sortedData[dataSize];
    for (int i = 0; i < dataSize; i++) {
        sortedData[i] = data[i];
    }
    qsort(sortedData, dataSize, sizeof(int), compare);
    
    for (int i = 0; i < testSize; i++) {
        testKeys[i] = data[rand() % dataSize];
    }
    for (int i = testSize; i < testSize + 10; i++) {
        testKeys[i] = 100000 + rand() % 100000;
    }
    
    clock_t start = clock();
    for (int i = 0; i < testSize + 10; i++) {
        search(ht, testKeys[i]);
    }
    double hashTime = (double)(clock() - start) / CLOCKS_PER_SEC;
    
    start = clock();
    for (int i = 0; i < testSize + 10; i++) {
        binarySearch(sortedData, dataSize, testKeys[i]);
    }
    double binaryTime = (double)(clock() - start) / CLOCKS_PER_SEC;
    
    printf("\nСравнение производительности:\n");
    printf("Размер данных: %d\n", dataSize);
    printf("Размер хеш-таблицы: %d\n", hashSize);
    printf("Количество коллизий: %d\n", ht->collisions);
    printf("Время поиска в хеш-таблице: %.6f сек\n", hashTime);
    printf("Время бинарного поиска: %.6f сек\n", binaryTime);
    printf("Хеширование быстрее в %.2f раз\n", binaryTime / hashTime);
    
    for (int i = 0; i < ht->size; i++) {
        Node* current = ht->table[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht->table);
    free(ht);
}

void demoHashTable() {
    printf("\nДемонстрация работы хеш-таблицы:\n");
    HashTable* ht = initHashTable(10);
    
    int keys[] = {15, 25, 12, 14, 10, 30, 35, 22, 11, 17, 27};
    int keysSize = sizeof(keys) / sizeof(keys[0]);
    
    for (int i = 0; i < keysSize; i++) {
        insert(ht, keys[i]);
    }
    
    display(ht);
    
    for (int i = 0; i < ht->size; i++) {
        Node* current = ht->table[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht->table);
    free(ht);
}

int main() {
    comparePerformance();
    demoHashTable();
    return 0;
}