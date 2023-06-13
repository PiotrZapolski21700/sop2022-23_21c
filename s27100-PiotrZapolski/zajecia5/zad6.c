#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void processMessage(const char *username) {
    char filename[20];
    sprintf(filename, "/tmp/chat_%s.txt", username);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }

    char message[100];

    while (fgets(message, sizeof(message), file) != NULL) {
        printf("Message from user %s: %s", username, message);
    }

    fclose(file);
}

void sendMessage(const char *username, const char *message) {
    char filename[20];
    sprintf(filename, "/tmp/chat_%s.txt", username);

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }

    fputs(message, file);
    fclose(file);
}

int main() {
    char message[100];

    while (1) {
        pid_t childPID = fork();

        if (childPID < 0) {
            printf("Error");
            exit(1);
        } else if (childPID == 0) {
            const char *sender = "UserA";
            const char *receiver = "UserB";

            processMessage(receiver);

            printf("%s: ", sender);
            fgets(message, sizeof(message), stdin);

            sendMessage(receiver, message);
            break;
        } else {
            wait(NULL);
            const char *sender = "UserB";
            const char *receiver = "UserA";

            processMessage(receiver);

            printf("%s: ", sender);
            fgets(message, sizeof(message), stdin);

            sendMessage(receiver, message);
        }
    }

    return 0;
}
