#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void append(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

void deleteAllNodes(Node** head) {
    Node* current = *head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}

void printForwardRecursive(Node* node) {
    if (node == NULL) return;
    printf("%d ", node->data);
    printForwardRecursive(node->next);
}

void printBackwardRecursive(Node* node) {
    if (node == NULL) return;
    printBackwardRecursive(node->next);
    printf("%d ", node->data);
}

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
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
    Node* list = NULL;
    srand(time(NULL));
    
    for (int i = 0; i < 10; i++) {
        append(&list, rand() % 10);
    }

    printf("Исходный список: ");
    printList(list);

    printf("Прямой порядок (рекурсивно): ");
    printForwardRecursive(list);
    printf("\n");

    printf("Обратный порядок (рекурсивно): ");
    printBackwardRecursive(list);
    printf("\n");

    printf("Контрольная сумма: %d\n", calculateChecksum(list));
    printf("Количество серий: %d\n", countSeries(list));

    deleteAllNodes(&list);
    printf("После удаления: ");
    printList(list);

    return 0;
}