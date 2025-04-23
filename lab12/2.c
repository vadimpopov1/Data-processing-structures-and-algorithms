#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear; 
} Queue;

void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

void enqueue(Queue* q, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// Возрастающий
void fillQueueAscending(Queue* q, int n) {
    for (int i = 1; i <= n; i++) {
        enqueue(q, i);
    }
}

// Убывающий
void fillQueueDescending(Queue* q, int n) {
    for (int i = n; i >= 1; i--) {
        enqueue(q, i);
    }
}

// Случайно
void fillQueueRandom(Queue* q, int n, int minVal, int maxVal) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        int randomNum = rand();
        enqueue(q, randomNum);
    }
}

void printQueue(Queue* q) {
    Node* current = q->front;
    printf("Содержимое очереди (начало -> конец): ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void freeQueue(Queue* q) {
    Node* current = q->front;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    q->front = q->rear = NULL;
}

int main() {
    Queue q;
    initQueue(&q);
    
    printf("Заполнение возрастающими числами:\n");
    fillQueueAscending(&q, 5);
    printQueue(&q);
    freeQueue(&q);
    
    printf("\nЗаполнение убывающими числами:\n");
    fillQueueDescending(&q, 5);
    printQueue(&q);
    freeQueue(&q);
    
    printf("\nЗаполнение случайными числами:\n");
    fillQueueRandom(&q, 5, 10, 50);
    printQueue(&q);
    freeQueue(&q);
    
    return 0;
}