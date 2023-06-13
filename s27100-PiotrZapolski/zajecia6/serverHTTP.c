#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <signal.h>

pid_t processId;

void sendHttpResponse(int socketDescriptor, const char *content){
    const char *responseTemplate = "HTTP/1.1 200 OK\r\n"
                                   "Content-Length: %lu\r\n"
                                   "Content-Type: text/html\r\n\r\n"
                                   "%s";

    char responseBuffer[1024];

    snprintf(responseBuffer, sizeof(responseBuffer), responseTemplate, strlen(content), content);

    send(socketDescriptor, responseBuffer, strlen(responseBuffer), 0);
}

int recordLogFile(int socketDescriptor, struct sockaddr_in clientAddress, int pid){
    FILE *logFilePointer;
    logFilePointer = fopen("log","a");

    fprintf(logFilePointer,"Client IP address: %s\n", inet_ntoa(clientAddress.sin_addr));
    fprintf(logFilePointer, "Client port: %d\n", (int) ntohs(clientAddress.sin_port));
    fprintf(logFilePointer,"PID number: %d\n", pid);
    fprintf(logFilePointer,"|=========================|\n");

    fclose(logFilePointer);

    return 0;
}

void sigIntHandler(int signal){
    if(processId == 0){
        printf(" Server connection closed, signal %d\n", signal);
        kill(processId, SIGKILL);
    }
    exit(1);
}

int main(int argc, char *argv[])
{
    const int parentProcessId = getpid();
    int socketDescriptor, newSocketDescriptor, clientLength, error, i;
    struct sockaddr_in serverAddress, clientAddress;

    const char ipBlackList[20][12] = {"10.54.21.42","23.243.43.21"};

    int blackListSize = sizeof(ipBlackList)/sizeof(ipBlackList[0]);

    FILE *logFilePointer;

    const char *pageContent = "<html><head><title>Test page</title></head><body><h1>Hello HTTP server!</h1></body></html>";

    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);

    if(signal(SIGINT, sigIntHandler)){
        close(socketDescriptor);
    };

    if (socketDescriptor < 0) {
        perror("Socket error\n");
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);

    error = bind(socketDescriptor, (struct sockaddr *) &serverAddress,sizeof(serverAddress));

    if(error == -1){
        perror("Binding error\n");
    }

    while(1){
        if(parentProcessId != getppid()){
            processId = fork();
            if(listen(socketDescriptor,5) == 0){
                printf("Listening...\n");
            }else{
                perror("Listen error\n");
            };

            clientLength = sizeof(clientAddress);

            while((newSocketDescriptor = accept(socketDescriptor, (struct sockaddr*) &clientAddress, &clientLength)) >= 0){

                char clientIpAddress[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &(clientAddress.sin_addr), clientIpAddress, INET_ADDRSTRLEN);

                for(i=0; i<blackListSize;i++){
                    if(strcmp(ipBlackList[i], clientIpAddress) == 0){
                        printf("Forbidden IP address: %s\n", clientIpAddress);
                        close(newSocketDescriptor);
                        break;
                    }
                }

                if (newSocketDescriptor < 0) {
                     perror("Accept error\n");
                }

                logFilePointer = fopen("log","a");

                sendHttpResponse(newSocketDescriptor, pageContent);

                fprintf(logFilePointer,"Sent page\n");

                 if(recordLogFile(socketDescriptor,clientAddress,getpid()) == 0){
                    printf("Successful log record\n");
                }else{
                    printf("Failed to record log\n");
                }

                close(newSocketDescriptor);
                fclose(logFilePointer);

            }

    }
    }
    return 0; 
}
