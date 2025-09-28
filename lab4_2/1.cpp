#include <iostream>
#include <random>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <chrono>
#include <queue>

using namespace std;

struct Vertex {
    int Data;
    Vertex* Left;
    Vertex* Right;
    Vertex(int val) : Data(val), Left(nullptr), Right(nullptr) {}
};

void addRecursively(int D, Vertex*& p) {
    if (p == nullptr) {
        p = new Vertex(D);
    } else if (D < p->Data) {
        addRecursively(D, p->Left);
    } else if (D > p->Data) {
        addRecursively(D, p->Right);
    }
}

void addWithDoubleIndirect(int D, Vertex** p) {
    while (*p != nullptr) {
        if (D < (*p)->Data) {
            p = &((*p)->Left);
        } else if (D > (*p)->Data) {
            p = &((*p)->Right);
        } else {
            return;
        }
    }
    *p = new Vertex(D);
}


void inOrderPrint(Vertex* p) {
    if (p != nullptr) {
        inOrderPrint(p->Left);
        cout << p->Data << " ";
        inOrderPrint(p->Right);
    }
}

int getSize(Vertex* p) {
    if (p == nullptr) return 0;
    return 1 + getSize(p->Left) + getSize(p->Right);
}

int getSum(Vertex* p) {
    if (p == nullptr) return 0;
    return p->Data + getSum(p->Left) + getSum(p->Right);
}

int getHeight(Vertex* p) {
    if (p == nullptr) return 0;
    return 1 + max(getHeight(p->Left), getHeight(p->Right));
}

void getTotalDepth(Vertex* p, int depth, int& total) {
    if (p != nullptr) {
        total += depth;
        getTotalDepth(p->Left, depth + 1, total);
        getTotalDepth(p->Right, depth + 1, total);
    }
}

void generateDifferentSequences(int* seq1, int* seq2, int n) {
    for (int i = 0; i < n; ++i) {
        seq1[i] = i + 1;
        seq2[i] = i + 1;
    }
    
    unsigned seed1 = chrono::system_clock::now().time_since_epoch().count();
    unsigned seed2 = seed1 + 1000;
    
    shuffle(seq1, seq1 + n, default_random_engine(seed1));
    shuffle(seq2, seq2 + n, default_random_engine(seed2));
}

Vertex* findMin(Vertex* p) {
    while (p && p->Left != nullptr)
        p = p->Left;
    return p;
}

bool searchNode(Vertex* root, int key) {
    if (root == nullptr) return false;
    
    if (key == root->Data) return true;
    else if (key < root->Data) return searchNode(root->Left, key);
    else return searchNode(root->Right, key);
}

Vertex* deleteNode(Vertex* root, int key) {
    if (root == nullptr) return root;

    if (key < root->Data) {
        root->Left = deleteNode(root->Left, key);
    } else if (key > root->Data) {
        root->Right = deleteNode(root->Right, key);
    } else {
        if (root->Left == nullptr) {
            Vertex* temp = root->Right;
            delete root;
            return temp;
        } else if (root->Right == nullptr) {
            Vertex* temp = root->Left;
            delete root;
            return temp;
        }

        Vertex* temp = findMin(root->Right);
        root->Data = temp->Data;
        root->Right = deleteNode(root->Right, temp->Data);
    }
    return root;
}

int main() {
    const int n = 100;
    int data1[n], data2[n];
    
    generateDifferentSequences(data1, data2, n);

    for (int i = 0; i < n; i++) {
        data1[i] = data2[i];
    }

    Vertex* rootRecursive = nullptr;
    for (int i = 0; i < n; i++) {
        addRecursively(data1[i], rootRecursive);
    }

    Vertex* rootDoubleIndirect = nullptr;
    for (int i = 0; i < n; i++) {
        addWithDoubleIndirect(data2[i], &rootDoubleIndirect);
    }
    
    cout << "\nСДП(1) Рекурсивно (→): ";
    inOrderPrint(rootRecursive);
    cout << "\nСДП(2) Двойная косвенность (→): ";
    inOrderPrint(rootDoubleIndirect);
    cout << endl;

    cout << "\n------------------------ Удаление вершин из СДП1 ------------------------" << endl;
    Vertex* currentTree = rootRecursive;
    
    for (int i = 1; i <= 10; i++) {
        int key;
        cout << "Введите ключ для удаления " << i << " вершины: ";
        cin >> key;
        
        if (!searchNode(currentTree, key)) {
            cout << "Вершина с ключом " << key << " не найдена в дереве!" << endl;
            i--; 
            continue;
        }
        
        currentTree = deleteNode(currentTree, key);
        
        cout << "Дерево после удаления " << key << ":\n";
        cout << "(→): ";
        inOrderPrint(currentTree);
        cout << endl;
        
        cout << "Размер дерева: " << getSize(currentTree) 
             << ", Высота: " << getHeight(currentTree) << endl;
        cout << "-------------------------------------------------------------------------" << endl;
    }            
    
    return 0;
}
