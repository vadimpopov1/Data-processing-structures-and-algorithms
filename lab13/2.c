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

void addNode(List* list, int data) {
    Node* newNode = createNode(data);
    if (list->tail == NULL) {
        list->head = list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->count++;
}

void fillListRandom(List* list, int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        addNode(list, rand() % 100);
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

void splitAlternating(List* original, List* list1, List* list2) {
    Node* current = original->head;
    int toggle = 0;
    
    while (current != NULL) {
        Node* nextNode = current->next;
        current->next = NULL;
        
        if (toggle == 0) {
            if (list1->tail == NULL) {
                list1->head = list1->tail = current;
            } else {
                list1->tail->next = current;
                list1->tail = current;
            }
            list1->count++;
            toggle = 1;
        } else {
            if (list2->tail == NULL) {
                list2->head = list2->tail = current;
            } else {
                list2->tail->next = current;
                list2->tail = current;
            }
            list2->count++;
            toggle = 0;
        }
        
        current = nextNode;
    }
    
    original->head = original->tail = NULL;
    original->count = 0;
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

int main() {
    List original, list1, list2;
    initList(&original);
    initList(&list1);
    initList(&list2);
    
    int n = 20;
    fillListRandom(&original, n);
    
    printf("S (%d): ", original.count);
    printList(&original);
    
    splitAlternating(&original, &list1, &list2);
    
    printf("\na (%d): ", list1.count);
    printList(&list1);
    
    printf("\nb (%d): ", list2.count);
    printList(&list2);
    
    printf("\nПроверка:\n");
    printf("Сумма элементов подсписков: %d + %d = %d\n", 
           list1.count, list2.count, list1.count + list2.count);
    printf("Исходный список после расщепления: %d элементов\n", original.count);
    
    freeList(&list1);
    freeList(&list2);
    
    return 0;
}