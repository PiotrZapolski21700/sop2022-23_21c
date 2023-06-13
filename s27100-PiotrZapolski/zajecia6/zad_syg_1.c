#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int pid;

void signalHandler(int signum) {
    if (signum == SIGUSR1) {
        printf("Otrzymano sygnał SIGUSR1\n");
        // Zakończ program
        _exit(0);
    }
}

int main() {
    // Pobierz PID procesu
    pid = getpid();
    printf("PID: %d\n", pid);

    // Ustaw obsługę sygnału SIGUSR1
    signal(SIGUSR1, signalHandler);

    // Pętla nieskończona
    while (1) {
        // Czekaj na sygnał użytkownika
        pause();
    }

    return 0;
}
