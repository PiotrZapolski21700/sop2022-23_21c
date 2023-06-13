#include <stdio.h>
#include <stdlib.h>

void reverseArray(int length, int array[]) {
    int temp;
    int idx1;
    int idx2;

    for (idx1 = 0; idx1 < length / 2; idx1++) {
        temp = array[idx1];
        idx2 = length - idx1 - 1;
        array[idx1] = array[idx2];
        array[idx2] = temp;
    }
}

int main(int argc, char* argv[]) {
    int idx1;
    int idx2;
    FILE* file;

    if (argv[1] != NULL) {
        file = fopen(argv[1], "r");
        if (file == NULL) {
            printf("Failed to open the file.\n");
            return 1;
        }
    } else {
        file = fopen("test", "r");
        if (file == NULL) {
            printf("Failed to open the file.\n");
            return 1;
        }
    }

    int n;
    fscanf(file, "%d", &n);
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Failed to allocate memory.\n");
        return 1;
    }

    for (idx1 = 0; idx1 < n; idx1++) {
        fscanf(file, "%d", &arr[idx1]);
    }

    fclose(file);

    reverseArray(n, arr);

    for (idx2 = 0; idx2 < n; idx2++) {
        printf("%d\n", arr[idx2]);
    }

    return 0;
}
