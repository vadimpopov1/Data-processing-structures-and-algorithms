#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 500
#define BUCKETS 256

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
    int count;
} Queue;

Queue* create_queue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    q->count = 0;
    return q;
}

void enqueue(Queue* q, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    
    if (q->rear) q->rear->next = newNode;
    else q->front = newNode;
    
    q->rear = newNode;
    q->count++;
}

int dequeue(Queue* q) {
    if (!q->front) return -1;
    
    Node* temp = q->front;
    int data = temp->data;
    
    q->front = q->front->next;
    if (!q->front) q->rear = NULL;
    
    free(temp);
    q->count--;
    return data;
}

void digital_sort(int arr[], int n, int num_bytes, int ascending, int* moves) {
    Queue* buckets[BUCKETS];
    *moves = 0;

    for (int byte_pos = 0; byte_pos < num_bytes; byte_pos++) {
        for (int i = 0; i < BUCKETS; i++)
            buckets[i] = create_queue();

        for (int i = 0; i < n; i++) {
            int byte = (arr[i] >> (8 * byte_pos)) & 0xFF;
            enqueue(buckets[byte], arr[i]);
            (*moves)++;
        }

        int idx = 0;
        if (ascending) {
            for (int i = 0; i < BUCKETS; i++) {
                while (buckets[i]->count > 0) {
                    arr[idx++] = dequeue(buckets[i]);
                    (*moves)++;
                }
            }
        } else {
            for (int i = BUCKETS-1; i >= 0; i--) {
                while (buckets[i]->count > 0) {
                    arr[idx++] = dequeue(buckets[i]);
                    (*moves)++;
                }
            }
        }

        for (int i = 0; i < BUCKETS; i++)
            free(buckets[i]);
    }
}

int check_sum(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    return sum;
}

int count_runs(int arr[], int n) {
    int runs = 1;
    for (int i = 1; i < n; i++)
        if (arr[i] < arr[i-1]) runs++;
    return runs;
}

void generate_array(int arr[], int n, int type) {
    switch(type) {
        case 0: 
            for (int i = 0; i < n; i++)
                arr[i] = n - i;
            break;
        case 1: 
            for (int i = 0; i < n; i++)
                arr[i] = rand() % 1000;
            break;
        case 2:
            for (int i = 0; i < n; i++)
                arr[i] = i + 1;
            break;
    }
}

int main() {
    srand(time(NULL));
    int sizes[] = {100, 200, 300, 400, 500};
    int num_bytes = 2;

    printf("2 байта:\n");
    printf("┌─────┬─────────┬─────────┬─────────┬─────────┐\n");
    printf("│  N  │ Теор. M │ Убыв. M │ Случ. M │ Возр. M │\n");
    printf("├─────┼─────────┼─────────┼─────────┼─────────┤\n");
    
    for (int i = 0; i < 5; i++) {
        int n = sizes[i];
        int theoretical = num_bytes * n;
        
        int arr_dec[n], m_dec;
        generate_array(arr_dec, n, 0);
        digital_sort(arr_dec, n, num_bytes, 1, &m_dec);
        
        int arr_rand[n], m_rand;
        generate_array(arr_rand, n, 1);
        digital_sort(arr_rand, n, num_bytes, 1, &m_rand);
        
        int arr_inc[n], m_inc;
        generate_array(arr_inc, n, 2);
        digital_sort(arr_inc, n, num_bytes, 1, &m_inc);
        
        printf("│ %3d │ %7d │ %7d │ %7d │ %7d │\n", 
            n, theoretical, m_dec, m_rand, m_inc);
    }
    printf("└─────┴─────────┴─────────┴─────────┴─────────┘\n");

int num_bytes_f = 4;
    
    printf("4 байта:\n");
    printf("┌─────┬─────────┬─────────┬─────────┬─────────┐\n");
    printf("│  N  │ Теор. M │ Убыв. M │ Случ. M │ Возр. M │\n");
    printf("├─────┼─────────┼─────────┼─────────┼─────────┤\n");
    
    for (int i = 0; i < 5; i++) {
        int n = sizes[i];
        int theoretical = num_bytes_f * n;
        
        int arr_dec[n], m_dec;
        generate_array(arr_dec, n, 0);
        digital_sort(arr_dec, n, num_bytes_f, 1, &m_dec);
        
        int arr_rand[n], m_rand;
        generate_array(arr_rand, n, 1);
        digital_sort(arr_rand, n, num_bytes_f, 1, &m_rand);
        
        int arr_inc[n], m_inc;
        generate_array(arr_inc, n, 2);
        digital_sort(arr_inc, n, num_bytes_f, 1, &m_inc);
        
        printf("│ %3d │ %7d │ %7d │ %7d │ %7d │\n", 
            n, theoretical, m_dec, m_rand, m_inc);
    }
    printf("└─────┴─────────┴─────────┴─────────┴─────────┘\n");
    return 0;
}