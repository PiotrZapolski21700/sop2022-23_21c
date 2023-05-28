#include <stdio.h>

/* Functions */
int getMax(int a, int b) {
    if (a >= b) {
        return a;
    } else {
        return b;
    }
}

int getMin(int a, int b) {
    if (a <= b) {
        return a;
    } else {
        return b;
    }
}

int getSum(int a, int b) {
    return a + b;
}

int main(int argc, char* argv[]) {
    int functionId;
    int elementCount;
    int idx1;
    int idx2;
    int result;

    printf("Enter the function number: ");
    scanf("%d", &functionId);

    /* Argument validation */
    if (functionId >= 0 && functionId <= 2) {
        printf("Enter the number of elements in the sequence: ");
        scanf("%d", &elementCount);

        int numbArray[elementCount];

        int (*array[])(int, int) = {getMax, getMin, getSum};

        for (idx1 = 0; idx1 < elementCount; idx1++) {
            scanf("%d", &numbArray[idx1]);
        }

        result = numbArray[0];
        for (idx2 = 1; idx2 < elementCount; idx2++) {
            result += (*array[functionId])(result, numbArray[idx2]);
        }

        printf("Result: %d\n", result);

        return 0;
    } else {
        printf("Invalid arguments\n");
        return 1;
    }
}
