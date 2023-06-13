#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 16

int main(int argc, char *argv[]) {
    /* File management */
    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        printf("Failed to open file %s\n", argv[1]);
        return 1;
    }

    unsigned char buffer[BUFFER_SIZE];
    size_t bytes_read = BUFFER_SIZE;
    int offset = 0;
    int idx1;
    int idx2;

    /* Printing file data */
    while (bytes_read == BUFFER_SIZE) {
        bytes_read = fread(buffer, sizeof(unsigned char), BUFFER_SIZE, file);
        printf("%08x  ", offset);

        for (idx1 = 0; idx1 < bytes_read; idx1++) {
            printf("%02x ", buffer[idx1]);
        }

        /* ASCII */
        for (idx2 = 0; idx2 < bytes_read; idx2++) {
            if (buffer[idx2] >= 32 && buffer[idx2] <= 126) {
                printf("%c", buffer[idx2]);
            } else {
                printf(".");
            }
        }

        printf("\n");
        offset += bytes_read;
    }

    fclose(file);

    return 0;
}

}
