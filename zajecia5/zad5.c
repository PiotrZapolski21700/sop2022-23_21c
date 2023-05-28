#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
    int i;
    int numProcesses = 100;
    pid_t masterPID = getpid();

    for (i = 0; i < numProcesses; i++) {
        pid_t child_pid = 0;
        child_pid = fork();

        if (child_pid == 0) {
            printf("PID: %d\tPPID: %d\n", getpid(), getppid());
            sleep(2);
            break;
        }
    }

    if (masterPID == getpid()) {
        waitpid(-1, NULL, 0);
        printf("Parent %d stopped waiting\n", getpid());
    }

    return 0;
}
