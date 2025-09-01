#include <stdio.h>
#include <string.h>
#include <math.h>

#define q 101
#define base 256

int hash(char* str, int start, int end) {
    int h = 0;
    for (int i = start; i < end; i++) {
        h = (h * base + str[i]) % q;
    }
    return h;
}

int RabinKarp(char* haystack, char* needle, int* comparisons, int* positions) {
    int n = strlen(haystack);
    int m = strlen(needle);
    int count = 0;
    *comparisons = 0;

    if (m == 0 || n < m) return 0;
    
    int hash_needle = hash(needle, 0, m);
    int hash_haystack = hash(haystack, 0, m);
    
    int h = 1;
    for (int i = 0; i < m - 1; i++) {
        h = (h * base) % q;
    }
    
    for (int i = 0; i <= n - m; i++) {
        if (hash_haystack == hash_needle) {
            int j;
            for (j = 0; j < m; j++) {
                (*comparisons)++;
                if (haystack[i + j] != needle[j]) {
                    break;
                }
            }
            if (j == m) {
                positions[count++] = i;
            }
        }

        if (i < n - m) {
            hash_haystack = (base * (hash_haystack - haystack[i] * h) + haystack[i + m]) % q;
            if (hash_haystack < 0) {
                hash_haystack += q;
            }
        }
    }
    
    return count;
}

int DirectSearch(char* haystack, char* needle, int* comparisons, int* positions) {
    int n = strlen(haystack);
    int m = strlen(needle);
    int count = 0;
    *comparisons = 0;

    if (m == 0) return 0;
    
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            (*comparisons)++;
            if (haystack[i + j] != needle[j]) {
                break;
            }
        }
        if (j == m) {
            positions[count++] = i;
        }
    }
    
    return count;
}

int main() {
    char text[] = "At vero eos et accusamus et iusto odio dignissimos ducimus\n"
                  "qui blanditiis praesentium voluptatum deleniti atque corrupti\n"
                  "quos dolores et quas molestias excepturi sint occaecati cupiditate\n"
                  "non provident, similique sunt in culpa qui officia deserunt mollitia\n"
                  "animi, id est laborum et dolorum fuga. Et harum quidem rerum facilis\n"
                  "est et expedita distinctio. Nam libero tempore, cum soluta nobis est\n"
                  "eligendi optio cumque nihil impedit quo minus id quod maxime placeat\n"
                  "facere possimus, omnis voluptas assumenda est, omnis dolor repellendus.\n"
                  "Temporibus autem quibusdam et aut officiis debitis aut rerum\n"
                  "necessitatibus saepe eveniet ut et voluptates repudiandae sint et\n"
                  "molestiae non recusandae. Itaque earum rerum hic tenetur a sapiente\n"
                  "delectus, ut aut reiciendis voluptatibus maiores alias consequatur\n"
                  "aut perferendis doloribus asperiores repellat.";   
    char search[100];
    
    printf("Введите подстроку для поиска: ");
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = '\0';
    
    int N = strlen(text);
    int M = strlen(search);

    int dcomparisons, rcomparisons;
    int dpositions[N], rpositions[N];
    int dcount, rcount;
    
    dcount = DirectSearch(text, search, &dcomparisons, dpositions);
    rcount = RabinKarp(text, search, &rcomparisons, rpositions);
    
    printf("\nПрямой перебор:\n");
    if (dcount > 0) {
        printf("Подстрока найдена в позициях: ");
        for (int i = 0; i < dcount; i++) {
            printf("%d", dpositions[i]);
            if (i < dcount - 1) printf(", ");
        }
        printf("\n");
    } else {
        printf("Подстрока не найдена\n");
    }
    printf("Количество сравнений: %d\n", dcomparisons);
    
    printf("\nМетод Рабина-Карпа:\n");
    if (rcount > 0) {
        printf("Подстрока найдена в позициях: ");
        for (int i = 0; i < rcount; i++) {
            printf("%d", rpositions[i]);
            if (i < rcount - 1) printf(", ");
        }
        printf("\n");
    } else {
        printf("Подстрока не найдена\n");
    }
    printf("Количество сравнений: %d\n", rcomparisons);
    
    if (rcomparisons < dcomparisons) {
        printf("Метод Рабина-Карпа быстрее чем метод прямого поиска в %.2f раз.\n", (float)dcomparisons / rcomparisons);
    } else if (dcomparisons < rcomparisons) {
        printf("Метод прямого поиска быстрее чем метод Рабина-Карпа в %.2f раз.\n", (float)rcomparisons / dcomparisons);
    } else if (dcomparisons == 0) {
        printf("Сравнений нет.");
    } else {
        printf("Методы сделали одинаковое количество сравнений.\n");
    }
    
    return 0;
}
