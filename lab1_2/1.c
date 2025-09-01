#include <stdio.h>
#include <string.h>

void search(const char* text, const char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int found = 0;
    
    printf("Текст: %s\n", text);
    printf("Подстрока: %s\n", pattern);

    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }
        if (j == m) {
            printf("Найдено вхождение в позиции: %d\n", i);
            found = 1;
        }
    }
    
    if (!found) {
        printf("Вхождений не найдено.\n");
    }
}

int main() {
    char text[1000];
    char pattern[100];
    
    printf("Введите текст: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';
    
    printf("Введите подстроку для поиска: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0';
    
    search(text, pattern);
    
    return 0;
}