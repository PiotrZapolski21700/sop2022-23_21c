#include <stdio.h>

int fibonacci(int n) {
    if (n <= 1) {
        return n;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
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
