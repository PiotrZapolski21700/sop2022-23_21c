#include <stdio.h>

int fibonacci(int n) {
    if (n <= 1) {
        return n;
    } else {
        int prev = 0;
        int current = 1;
        int result = 0;

        for (int i = 2; i <= n; i++) {
            result = prev + current;
            prev = current;
            current = result;
        }

        return result;
    }
}

int main() {
    int n;
    printf("Podaj liczbę n: ");
    scanf("%d", &n);

    printf("Ciąg Fibonacciego o długości %d:\n", n);
    for (int i = 0; i < n; i++) {
        printf("%d ", fibonacci(i));
    }

    return 0;
}