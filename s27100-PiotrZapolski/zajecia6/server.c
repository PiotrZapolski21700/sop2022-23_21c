#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <signal.h>

int transmitFile(FILE *source, int socketDescriptor){
  char data[1024] = {0};
  size_t bytesRead;

  while ((bytesRead = fread(data, 1, sizeof(data), source)) > 0) {
        if (send(socketDescriptor, data, bytesRead, 0) == -1) {
            perror("Error while sending file\n");
            return 1;
        }
    }

  return 0;
}

int registerFile(int socketDescriptor, struct sockaddr_in clientInfo){
    FILE *logFile;
    logFile=fopen("log","a");

    fprintf(logFile,"Client IP address: %s\n",inet_ntoa(clientInfo.sin_addr));
    fprintf(logFile, "Client port: %d\n", (int) ntohs(clientInfo.sin_port));
    fprintf(logFile,"|=========================|\n");

    fclose(logFile);

    return 0;
}

void processSigInt(int signal){
    printf(" Server connection closed, signal %d\n", signal);
}

int main(int argCount, char *argValues[])
{
    int serverSocket, newSocket, port, clientLength, errorCode;
    struct sockaddr_in serverInfo, clientInfo;
    FILE *sourceFile;
    char filename[64];
    struct stat fileStats;


    if (argCount < 2) {
        perror("Port not provided\n");
        exit(1);
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(signal(SIGINT, processSigInt)){
        close(serverSocket);
    };


    if (serverSocket < 0) {
        perror("Error while creating socket\n");
    }

    port = atoi(argValues[1]);
    serverInfo.sin_family = AF_INET;
    serverInfo.sin_addr.s_addr = INADDR_ANY;
    serverInfo.sin_port = port;

    errorCode = bind(serverSocket, (struct sockaddr *) &serverInfo,sizeof(serverInfo));

    if(errorCode == -1){
        perror("Error while binding\n");
    }

    if(listen(serverSocket,5) == 0){
        printf("Listening...\n");
    }else{
        perror("Listen error\n");
    };

    clientLength = sizeof(clientInfo);

    while((newSocket = accept(serverSocket, (struct sockaddr*) &clientInfo, &clientLength)) >= 0){

        if (newSocket < 0) {
             perror("Error during accept\n");
        }

        read(newSocket, filename, 64);

        sourceFile = fopen(filename, "r");
        stat(filename, &fileStats);

        if (sourceFile == NULL) {
            printf("File size: -1 bytes\n");
            perror("Error while reading file\n");
            exit(1);
        }else{
            printf("File size: %ld bytes\n",fileStats.st_size);
        }

        if(transmitFile(sourceFile, newSocket) == 0){
            printf("File transmission successful\n");
        }else{
            exit(1);
        }

        if(registerFile(serverSocket,clientInfo) == 0){
            printf("Log file writing was successful\n");
        }else{
            printf("Failed to write log file\n");
        }


        fclose(sourceFile);
        close(newSocket);
    }
    return 0; 
} 
