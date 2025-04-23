#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
} Stack;

void initStack(Stack* s) {
    s->top = NULL;
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

// Возрастающий
void fillAscending(Stack* s, int n) {
    for (int i = 1; i <= n; i++) {
        push(s, i);
    }
}

// Убывающий
void fillDescending(Stack* s, int n) {
    for (int i = n; i >= 1; i--) {
        push(s, i);
    }
}

// Случайно
void fillRandom(Stack* s, int n, int minVal, int maxVal) {
    srand(time(NULL)); 
    for (int i = 0; i < n; i++) {
        int randomNum = rand();
        push(s, randomNum);
    }
}

void printStack(Stack* s) {
    Node* current = s->top;
    printf("Содержимое стека (начало -> конец): ");
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

int main() {
    Stack s;
    initStack(&s);
    
    printf("Заполнение возрастающими числами:\n");
    fillAscending(&s, 5);
    printStack(&s);
    freeStack(&s);
    
    printf("\nЗаполнение убывающими числами:\n");
    fillDescending(&s, 5);
    printStack(&s);
    freeStack(&s);
    
    printf("\nЗаполнение случайными числами:\n");
    fillRandom(&s, 5, 10, 50);
    printStack(&s);
    freeStack(&s);
    
    return 0;
}
