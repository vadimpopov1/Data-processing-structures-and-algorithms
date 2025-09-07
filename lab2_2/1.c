#include <stdio.h>
#include <stdlib.h>

struct Vertex {
    int Data;
    struct Vertex* Left;
    struct Vertex* Right;
};

struct Vertex* createNode(int value) {
    struct Vertex* newNode = (struct Vertex*)malloc(sizeof(struct Vertex));
    newNode->Data = value;
    newNode->Left = NULL;
    newNode->Right = NULL;
    return newNode;
}

struct Vertex* buildTree() {
    struct Vertex* root = createNode(1);
    root->Left = createNode(2);
    root->Left->Right = createNode(3);
    root->Left->Right->Left = createNode(4);
    root->Left->Right->Left->Right = createNode(5);
    root->Left->Right->Left->Right->Left = createNode(6);
    return root;
}

void preorderTraversal(struct Vertex* root) {
    if (root != NULL) {
        printf("%d ", root->Data);
        preorderTraversal(root->Left);
        preorderTraversal(root->Right);
    }
}

void inorderTraversal(struct Vertex* root) {
    if (root != NULL) {
        inorderTraversal(root->Left);
        printf("%d ", root->Data);
        inorderTraversal(root->Right);
    }
}

void postorderTraversal(struct Vertex* root) {
    if (root != NULL) {
        postorderTraversal(root->Left);
        postorderTraversal(root->Right);
        printf("%d ", root->Data);
    }
}

int calculateSize(struct Vertex* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + calculateSize(root->Left) + calculateSize(root->Right);
}

int calculateChecksum(struct Vertex* root) {
    if (root == NULL) {
        return 0;
    }
    return root->Data + calculateChecksum(root->Left) + calculateChecksum(root->Right);
}

int calculateHeight(struct Vertex* root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = calculateHeight(root->Left);
    int rightHeight = calculateHeight(root->Right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

void calculateTotalDepthHelper(struct Vertex* root, int depth, int* total) {
    if (root != NULL) {
        *total += depth;
        calculateTotalDepthHelper(root->Left, depth + 1, total);
        calculateTotalDepthHelper(root->Right, depth + 1, total);
    }
}

int calculateTotalDepth(struct Vertex* root) {
    int total = 0;
    calculateTotalDepthHelper(root, 0, &total);
    return total;
}

void freeTree(struct Vertex* root) {
    if (root != NULL) {
        freeTree(root->Left);
        freeTree(root->Right);
        free(root);
    }
}

int main() {
    struct Vertex* root = buildTree();
    
    printf("Обходы: \n");
    printf("(↓): ");
    preorderTraversal(root);
    printf("\n");
    
    printf("(→): ");
    inorderTraversal(root);
    printf("\n");
    
    printf("(↑): ");
    postorderTraversal(root);
    printf("\n");
    
    int size = calculateSize(root);
    int checksum = calculateChecksum(root);
    int height = calculateHeight(root);
    int totalDepth = calculateTotalDepth(root);
    float averageDepth = (float)totalDepth / size;
    
    printf("Размер дерева: %d\n", size);
    printf("Контрольная сумма: %d\n", checksum);
    printf("Высота дерева: %d\n", height);
    printf("Средняя высота: %.2f\n", averageDepth);
    
    freeTree(root);
    
    return 0;
}
