#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int receiveFile(int socketDescriptor, char *file){
    int bytesRead;
    FILE *destinationFile;
    char data[1024];
    destinationFile = fopen(file, "w");
    while (1) {
        bytesRead = recv(socketDescriptor, data, 1024, 0);
            if (bytesRead <= 0){
                break;    
    }
    fprintf(destinationFile, "%s", data);
    memset(data, 0, 1024);
    }

      fclose(destinationFile);
      return 0;
}


int main(int argumentCount, char *argumentValues[])
{
    int socket, portNumber, errorCode;
    struct sockaddr_in serverAddress;
    char *fileName = argumentValues[2];

    if (argumentCount < 3) {
        perror("Port or file name not provided\n");
        exit(1);
    }

    socket = socket(AF_INET, SOCK_STREAM, 0);

    if (socket < 0) {
        perror("Error in creating socket\n");
    }

    portNumber = atoi(argumentValues[1]);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = portNumber;

    errorCode = connect(socket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    if(errorCode == -1){
        perror("Error during connection\n");
        exit(1);
    }

    if (send(socket, fileName, strlen(fileName), 0) < 0) {
        perror("Send error");
        exit(1);
    }


    if(receiveFile(socket, fileName) == 0){
        printf("File reception successful\n");
        return 0;
    }else{
        exit(1);
    }


    close(socket);

    return 0;
}
