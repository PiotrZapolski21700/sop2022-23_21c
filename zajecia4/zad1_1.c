#include <stdio.h>

int main() {
    int result = 0;
    int number = 0;

    do {
        number = 0;
        printf("Enter a number: ");
        scanf("%d", &number);
        result += number;
    } while (number != 0);

    printf("Result: %d\n", result);
}