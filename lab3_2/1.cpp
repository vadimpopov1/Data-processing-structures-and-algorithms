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

Vertex* buildTreeLevelOrder(int n) {
    if (n == 0) return nullptr;
    
    queue<Vertex*> q;
    Vertex* root = new Vertex(1);
    q.push(root);
    
    int i = 2;
    while (i <= n && !q.empty()) {
        Vertex* current = q.front();
        q.pop();
        
        if (i <= n) {
            current->Left = new Vertex(i++);
            q.push(current->Left);
        }
        
        if (i <= n) {
            current->Right = new Vertex(i++);
            q.push(current->Right);
        }
    }
    
    return root;
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

    Vertex* rootIdeal = buildTreeLevelOrder(n);
    
    cout << "\nИСДП (→): ";
    inOrderPrint(rootIdeal);
    cout << "\nСДП(1) Рекурсивно (→): ";
    for (int i = 0; i < n; ++i) cout << data1[i] << " ";
    cout << "\nСДП(2) Двойная косвенность (→): ";
    for (int i = 0; i < n; ++i) cout << data2[i] << " ";

    int sizeRecursive = getSize(rootRecursive);
    int sumRecursive = getSum(rootRecursive);
    int heightRecursive = getHeight(rootRecursive);
    int totalDepthRecursive = 0;
    getTotalDepth(rootRecursive, 1, totalDepthRecursive);
    float avgDepthRecursive = static_cast<float>(totalDepthRecursive) / sizeRecursive;

    int sizeDouble = getSize(rootDoubleIndirect);
    int sumDouble = getSum(rootDoubleIndirect);
    int heightDouble = getHeight(rootDoubleIndirect);
    int totalDepthDouble = 0;
    getTotalDepth(rootDoubleIndirect, 1, totalDepthDouble);
    float avgDepthDouble = static_cast<float>(totalDepthDouble) / sizeDouble;

    int sizeIdeal = getSize(rootIdeal);
    int sumIdeal = getSum(rootIdeal);
    int heightIdeal = getHeight(rootIdeal);
    int totalDepthIdeal = 0;
    getTotalDepth(rootIdeal, 1, totalDepthIdeal);
    float avgDepthIdeal = static_cast<float>(totalDepthIdeal) / sizeIdeal;

    cout << "\n┌──────┬──────────┬────────────┬────────┬─────────────┐" << endl;
    cout << "│      │  Размер  │ Контр.сумма│ Высота │ Средн.высота│" << endl;
    cout << "├──────┼──────────┼────────────┼────────┼─────────────┤" << endl;
    
    cout << "│ ИСДП │ " << setw(8) << sizeIdeal << " │ " 
          << setw(10) << sumIdeal << " │ " << setw(6) << heightIdeal 
          << " │ " << setw(11) << fixed << setprecision(2) << avgDepthIdeal << " │" << endl;
    
    cout << "├──────┼──────────┼────────────┼────────┼─────────────┤" << endl;
    cout << "│ СДП1 │ " << setw(8) << sizeRecursive << " │ " 
          << setw(10) << sumRecursive << " │ " << setw(6) << heightRecursive 
          << " │ " << setw(11) << fixed << setprecision(2) << avgDepthRecursive << " │" << endl;
    
    cout << "├──────┼──────────┼────────────┼────────┼─────────────┤" << endl;
    cout << "│ СДП2 │ " << setw(8) << sizeDouble << " │ " 
          << setw(10) << sumDouble << " │ " << setw(6) << heightDouble 
          << " │ " << setw(11) << fixed << setprecision(2) << avgDepthDouble << " │" << endl;
    
    cout << "└──────┴──────────┴────────────┴────────┴─────────────┘" << endl;
    
    return 0;
}
