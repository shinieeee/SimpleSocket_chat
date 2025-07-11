#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8000
#define BUFFER_SIZE 255

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serv_addr;

 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }


    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Connect to localhost


    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        close(sockfd);
        exit(1);
    }

    printf("Connected to server\n");

    while (1) {
        bzero(buffer, BUFFER_SIZE);
        fgets(buffer, BUFFER_SIZE, stdin);
        write(sockfd, buffer, strlen(buffer));

        if (strncmp("bye", buffer, 3) == 0) {
            break;
        }

        bzero(buffer, BUFFER_SIZE);
        int n = read(sockfd, buffer, BUFFER_SIZE);
        if (n <= 0) {
            break;
        }
        printf("Server: %s", buffer);
    }

    close(sockfd);
    return 0;
}
