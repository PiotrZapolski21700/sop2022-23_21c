#include <unistd.h>
#include <stdio.h>

int main() {
    int value;

    printf("PID: %d\tPPID: %d\n", getpid(), getppid());
    scanf("%d", &value);

    return 0;
}
