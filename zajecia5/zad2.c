#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid = fork();
    if (child_pid == -1) {
        printf("%d Failed to create a child!\n", getpid());
    } else if (child_pid == 0) {
        printf("PID: %d\tPPID: %d\n", getpid(), getppid());
    } else {
        wait(NULL);
        printf("PID: %d\tPPID: %d\n", getpid(), getppid());
    }

    return 0;
}
