#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int index_i, index_j, result = 0;
    int arg_value = atoi(argv[1]);

    if (argc < 2) {
        printf("No arguments provided\n");
        return 1;
    }

    pid_t child_pid = fork();

    if (child_pid == -1) {
        printf("%d Failed to create a child!\n", getpid());
    } else if (child_pid == 0) {
        printf("Child process PID: %d\tPPID: %d\n", getpid(), getppid());
        for (index_i = 1; index_i < arg_value; index_i += 2) {
            printf("Number: %d\n", index_i);
        }
        printf("Child process PID: %d has finished\n", getpid());
    } else {
        wait(NULL);
        for (index_j = 0; index_j < arg_value; index_j++) {
            result += index_j;
        }
        printf("Parent PID: %d - Result: %d\n", getpid(), result);
    }

    return 0;
}
