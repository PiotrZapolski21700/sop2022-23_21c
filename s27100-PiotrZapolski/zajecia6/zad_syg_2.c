#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define LOCK_FILE "/tmp/lock"

int pid;

void handleSIGUSR1(int signum) {
    printf("Wykryto próbę uruchomienia drugiej instancji programu.\n");
}

void handleSIGINT(int signum) {
    printf("Przechwycono sygnał SIGINT. Kasowanie pliku lock i wyjście z programu.\n");
    remove(LOCK_FILE);
    exit(0);
}

int main() {
    int lockFile;
    FILE *fp;
    char buffer[10];
    pid_t existingPid;

    // Sprawdź, czy plik lock już istnieje
    lockFile = open(LOCK_FILE, O_CREAT | O_RDWR, 0644);
    if (lockFile == -1) {
        fp = fopen(LOCK_FILE, "r");
        fscanf(fp, "%s", buffer);
        fclose(fp);

        existingPid = atoi(buffer);
        printf("Program już uruchomiony (PID: %d).\n", existingPid);

        // Wyślij sygnał SIGUSR1 do istniejącego procesu
        kill(existingPid, SIGUSR1);
        exit(1);
    } else {
        // Zapisz PID bieżącego procesu do pliku lock
        dprintf(lockFile, "%d\n", getpid());
        close(lockFile);

        // Instaluj obsługę sygnału SIGUSR1
        signal(SIGUSR1, handleSIGUSR1);

        // Instaluj obsługę sygnału SIGINT (CTRL+C)
        signal(SIGINT, handleSIGINT);

        // Pętla nieskończona
        while (1) {
            sleep(1);
        }
    }

    return 0;
}
