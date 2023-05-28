#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
    int i;
    int numProcesses = 99;

    for (i = 0; i < numProcesses; i++) {
        pid_t child_pid = 0;
        printf("PID: %d\tPPID: %d\n", getpid(), getppid());
        child_pid = fork();

        if (child_pid > 0) {
            wait(NULL);
            break;
        }
    }

    return 0;
}
