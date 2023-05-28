#include <stdio.h>

int main() {
    int height;
    int numStars;
    int numSpaces;
    int row;
    int space;
    int star;

    printf("Enter the height of the Christmas tree: ");
    scanf("%d", &height);

    numSpaces = height - 1;
    numStars = 1;

    for (row = 0; row < height; row++) {
        for (space = 0; space < numSpaces; space++) {
            printf(" ");
        }

        for (star = 0; star < numStars; star++) {
            printf("*");
        }

        numSpaces--;
        numStars += 2;

        printf("\n");
    }

    return 0;
}