#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int count;
} List;

Node* createNode(int data);
void initList(List* list);
void append(List* list, int data);
void generateRandomList(List* list, int n);
void printList(List* list);
int calculateChecksum(List* list);
int countRuns(List* list);
void mergeRuns(List* left, List* right, List* result, int* comparisons, int* moves);
void freeList(List* list);
void testMergeRuns();

int main() {
    testMergeRuns();
    return 0;
}


Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void initList(List* list) {
    list->head = list->tail = NULL;
    list->count = 0;
}

void append(List* list, int data) {
    Node* newNode = createNode(data);
    if (list->tail == NULL) {
        list->head = list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->count++;
}

void generateRandomList(List* list, int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        append(list, rand() % 100);
    }
}

void printList(List* list) {
    Node* current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int calculateChecksum(List* list) {
    int sum = 0;
    Node* current = list->head;
    while (current != NULL) {
        sum += current->data;
        current = current->next;
    }
    return sum;
}

int countRuns(List* list) {
    int runs = 0;
    Node* current = list->head;
    if (current == NULL) return 0;
    
    runs = 1;
    while (current->next != NULL) {
        if (current->data > current->next->data) {
            runs++;
        }
        current = current->next;
    }
    return runs;
}

void mergeRuns(List* left, List* right, List* result, int* comparisons, int* moves) {
    Node* l = left->head;
    Node* r = right->head;
    
    while (l != NULL && r != NULL) {
        (*comparisons)++;
        if (l->data <= r->data) {
            append(result, l->data);
            l = l->next;
        } else {
            append(result, r->data);
            r = r->next;
        }
        (*moves)++;
    }
    
    while (l != NULL) {
        append(result, l->data);
        l = l->next;
        (*moves)++;
    }
    
    while (r != NULL) {
        append(result, r->data);
        r = r->next;
        (*moves)++;
    }
}

void freeList(List* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = list->tail = NULL;
    list->count = 0;
}

void testMergeRuns() {
    List left, right, merged;
    initList(&left);
    initList(&right);
    initList(&merged);
    
    append(&left, 10);
    append(&left, 20);
    append(&left, 30);
    
    append(&right, 15);
    append(&right, 25);
    append(&right, 35);
    
    int comparisons = 0;
    int moves = 0;
    
    printf("Левый список: ");
    printList(&left);
    printf("Правый список: ");
    printList(&right);
    
    mergeRuns(&left, &right, &merged, &comparisons, &moves);
    
    printf("Результат слияния: ");
    printList(&merged);
    
    printf("\nСтатистика:\n");
    printf("Количество серий в левом списке: %d\n", countRuns(&left));
    printf("Количество серий в правом списке: %d\n", countRuns(&right));
    printf("Количество серий в результате: %d\n", countRuns(&merged));
    printf("Контрольная сумма левого списка: %d\n", calculateChecksum(&left));
    printf("Контрольная сумма правого списка: %d\n", calculateChecksum(&right));
    printf("Контрольная сумма результата: %d\n", calculateChecksum(&merged));
    printf("Фактические сравнения (Сф): %d\n", comparisons);
    printf("Фактические перемещения (Мф): %d\n", moves);
    
    int n = left.count + right.count;
    int theoretical_comparisons = n - 1;
    int theoretical_moves = n;
    
    printf("\nТеоретические оценки:\n");
    printf("Ожидаемые сравнения (С): %d\n", theoretical_comparisons);
    printf("Ожидаемые перемещения (М): %d\n", theoretical_moves);
    
    freeList(&left);
    freeList(&right);
    freeList(&merged);
}