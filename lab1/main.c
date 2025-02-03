#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void FillInc(int n, int A[]){
    for (int i = 0; i < n; i++){
        A[i] = i + 1;
    }
}   

void FillDec(int n, int A[]){
    for (int i = 0; i < n; i++){
        A[i] = n - i;
    }
}

void FillRand(int n, int A[]){
    for (int i = 0; i < n; i++){
        A[i] = rand() % 10;
    }
}

int CheckSum(int n, int A[]){
    int sum = 0;
    for (int i = 0; i < n; i++){
        sum += A[i];
    }
    return sum;
}

int RunNumber(int n, int A[]){
    int cnt = 1;
    for (int i = 0; i < n; i++){
        if (A[i] < A[i-1]){
            cnt += 1;
        }
    }
    return cnt;
}

void PrintMas(int n, int A[]){
    for (int i = 0; i < n; i++){
        printf("%d ", A[i]);
    }
}

int main(){
    srand(time(NULL));
    int n = 10;
    int A[n];
    int cnt = 0;
    int sum = 0;

    FillInc(n, A);
    PrintMas(n, A);
    cnt = RunNumber(n, A);
    sum = CheckSum(n, A);
    printf(" Возрастающая. Контрольная сумма: %d. Количество серий: %d\n", sum, cnt);

    FillDec(n, A);
    PrintMas(n, A);
    cnt = RunNumber(n, A);
    sum = CheckSum(n, A);
    printf(" Убывающая. Контрольная сумма: %d. Количество серий: %d\n", sum, cnt);

    FillRand(n, A);
    PrintMas(n, A);
    cnt = RunNumber(n, A);
    sum = CheckSum(n, A);
    printf(" Рандомная. Контрольная сумма: %d. Количество серий: %d\n", sum, cnt);
}
