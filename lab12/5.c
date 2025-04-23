#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
} Stack;

typedef struct {
    Node* front;
    Node* rear; 
} Queue;

void initStack(Stack* s) {
    s->top = NULL;
}

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

void push(Stack* s, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = s->top;
    s->top = newNode;
}

void fillAscending(Stack* s, int n) {
    for (int i = 1; i <= n; i++) {
        push(s, i);
    }
}

void fillDescending(Stack* s, int n) {
    for (int i = n; i >= 1; i--) {
        push(s, i);
    }
}

void fillRandom(Stack* s, int n, int minVal, int maxVal) {
    srand(time(NULL)); 
    for (int i = 0; i < n; i++) {
        int randomNum = minVal + rand() % (maxVal - minVal + 1);
        push(s, randomNum);
    }
}

void fillQueueAscending(Queue* q, int n) {
    for (int i = 1; i <= n; i++) {
        enqueue(q, i);
    }
}

void fillQueueDescending(Queue* q, int n) {
    for (int i = n; i >= 1; i--) {
        enqueue(q, i);
    }
}

void fillQueueRandom(Queue* q, int n, int minVal, int maxVal) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        int randomNum = minVal + rand() % (maxVal - minVal + 1);
        enqueue(q, randomNum);
    }
}

void printStack(Stack* s) {
    Node* current = s->top;
    printf("Содержимое стека (вершина -> основание): ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void freeStack(Stack* s) {
    Node* current = s->top;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    s->top = NULL;
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

int calculateChecksum(Node* head) {
    int sum = 0;
    Node* current = head;
    while (current != NULL) {
        sum += current->data;
        current = current->next;
    }
    return sum;
}

int countSeries(Node* head) {
    if (head == NULL) return 0;
    
    int count = 1;
    Node* current = head;
    
    while (current->next != NULL) {
        if (current->data >= current->next->data) {
            count++;
        }
        current = current->next;
    }
    return count;
}

int main() {
    Stack s;
    Queue q;
    const int n = 10;
    const int minVal = 10;
    const int maxVal = 50;

    printf("СТЕКИ (LIFO)\n");
    
    // Возрастающие
    initStack(&s);
    fillAscending(&s, n);
    printf("\nСтек с возрастающими числами:\n");
    printf("Контрольная сумма: %d\n", calculateChecksum(s.top));
    printf("Количество серий: %d\n", countSeries(s.top));
    printStack(&s);
    freeStack(&s);
    
    // Убывающие
    initStack(&s);
    fillDescending(&s, n);
    printf("\nСтек с убывающими числами:\n");
    printf("Контрольная сумма: %d\n", calculateChecksum(s.top));
    printf("Количество серий: %d\n", countSeries(s.top));
    printStack(&s);
    freeStack(&s);
    
    // Случайные
    initStack(&s);
    fillRandom(&s, n, minVal, maxVal);
    printf("\nСтек со случайными числами:\n");
    printf("Контрольная сумма: %d\n", calculateChecksum(s.top));
    printf("Количество серий: %d\n", countSeries(s.top));
    printStack(&s);
    freeStack(&s);

    printf("\nОЧЕРЕДИ (FIFO)\n");
    
    // Возрастающие
    initQueue(&q);
    fillQueueAscending(&q, n);
    printf("\nОчередь с возрастающими числами:\n");
    printf("Контрольная сумма: %d\n", calculateChecksum(q.front));
    printf("Количество серий: %d\n", countSeries(q.front));
    printQueue(&q);
    freeQueue(&q);
    
    // Убывающие
    initQueue(&q);
    fillQueueDescending(&q, n);
    printf("\nОчередь с убывающими числами:\n");
    printf("Контрольная сумма: %d\n", calculateChecksum(q.front));
    printf("Количество серий: %d\n", countSeries(q.front));
    printQueue(&q);
    freeQueue(&q);
    
    // Случайные
    initQueue(&q);
    fillQueueRandom(&q, n, minVal, maxVal);
    printf("\nОчередь со случайными числами:\n");
    printf("Контрольная сумма: %d\n", calculateChecksum(q.front));
    printf("Количество серий: %d\n", countSeries(q.front));
    printQueue(&q);
    freeQueue(&q);

    return 0;
}