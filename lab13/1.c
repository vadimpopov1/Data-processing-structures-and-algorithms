#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct ListNode {
    long long int value;
    struct ListNode* next;
} ListNode;

typedef struct {
    ListNode* first;
    ListNode* last;
    int size;
} List;

ListNode* makeNode(long long int val) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->value = val;
    newNode->next = NULL;
    return newNode;
}

void setupList(List* lst) {
    lst->first = lst->last = NULL;
    lst->size = 0;
}

void addNode(List* lst, long long int val) {
    ListNode* newNode = makeNode(val);
    if (lst->last == NULL) {
        lst->first = lst->last = newNode;
    } else {
        lst->last->next = newNode;
        lst->last = newNode;
    }
    lst->size++;
}

void fillListIncreasing(List* lst, int n) {
    for (int i = 1; i <= n; i++) {
        addNode(lst, i);
    }
}

void fillListDecreasing(List* lst, int n) {
    for (int i = n; i >= 1; i--) {
        addNode(lst, i);
    }
}

void fillListRandomized(List* lst, int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        addNode(lst, rand() % (2*n));
    }
}

void clearList(List* lst) {
    ListNode* curr = lst->first;
    while (curr != NULL) {
        ListNode* tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    lst->first = lst->last = NULL;
    lst->size = 0;
}

void transferNode(List* dst, List* src, int* moves) {
    if (src->first == NULL) return;
    ListNode* node = src->first;
    src->first = src->first->next;
    if (src->first == NULL) src->last = NULL;
    src->size--;
    node->next = NULL;
    if (dst->last == NULL) {
        dst->first = dst->last = node;
    } else {
        dst->last->next = node;
        dst->last = node;
    }
    dst->size++;
    (*moves)++;
}

void mergeLists(List* a, int q, List* b, int r, List* c, int* moves, int* comps) {
    while (q > 0 && r > 0) {
        (*comps)++;
        if (a->first->value <= b->first->value) {
            transferNode(c, a, moves);
            q--;
        } else {
            transferNode(c, b, moves);
            r--;
        }
    }
    
    while (q > 0) {
        transferNode(c, a, moves);
        q--;
    }
    
    while (r > 0) {
        transferNode(c, b, moves);
        r--;
    }
}

void divideList(List* S, List* a, List* b) {
    setupList(a);
    setupList(b);
    if (S->first == NULL) return;
    ListNode* slow = S->first;
    ListNode* fast = S->first->next;
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    a->first = S->first;
    a->last = slow;
    b->first = slow->next;
    b->last = S->last;
    ListNode* curr = a->first;
    a->size = 0;
    while (curr != NULL && curr != b->first) {
        a->size++;
        curr = curr->next;
    }
    b->size = S->size - a->size;
    if (a->last) a->last->next = NULL;
}

int performMergeSort(List* S) {
    if (S->first == NULL || S->first->next == NULL) return 0;
    List a, b;
    divideList(S, &a, &b);
    int leftOps = performMergeSort(&a);
    int rightOps = performMergeSort(&b);
    int totalMoves = 0, totalComps = 0;
    List temp;
    setupList(&temp);
    mergeLists(&a, a.size, &b, b.size, &temp, &totalMoves, &totalComps);
    *S = temp;
    return totalMoves + totalComps + leftOps + rightOps;
}

int calcTheoreticalComps(int n) {
    return (int)(n * ceil(log2(n)));
}

int calcTheoreticalMoves(int n) {
    return (int)(n * ceil(log2(n))) + n;
}

int calcTotalTheoretical(int n) {
    return calcTheoreticalComps(n) + calcTheoreticalMoves(n);
}

int main() {
    int dimensions[] = {100, 200, 300, 400, 500};
    int count = sizeof(dimensions)/sizeof(dimensions[0]);
    
    printf("+-------+---------+-----------------------+\n");
    printf("|   N   |   M+C   |     M факт + C факт   |\n");
    printf("|       |  Теория | Убыв. | Случ. | Возр. |\n");
    printf("+-------+---------+-------+-------+-------+\n");

    for (int i = 0; i < count; i++) {
        int n = dimensions[i];
        int theory = calcTotalTheoretical(n);
        int dec, rand, inc;
        
        List descending;
        setupList(&descending);
        fillListDecreasing(&descending, n);
        dec = performMergeSort(&descending);
        clearList(&descending);
        
        List random;
        setupList(&random);
        fillListRandomized(&random, n);
        rand = performMergeSort(&random);
        clearList(&random);
        
        List ascending;
        setupList(&ascending);
        fillListIncreasing(&ascending, n);
        inc = performMergeSort(&ascending);
        clearList(&ascending);
        
        printf("|  %d  |  %4d   |  %4d |  %d |  %d |\n", n, theory, dec, rand, inc);
    }
    printf("+-------+---------+-------+-------+-------+\n");
}
