#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 8000
#define BUFFER_SIZE 255

int main() {
    int sockfd, newsockfd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;
    char buffer[BUFFER_SIZE];

 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }


    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);


    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Binding failed");
        close(sockfd);
        exit(1);
    }

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);


    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0) {
        perror("Accept failed");
        close(sockfd);
        exit(1);
    }

    printf("Client connected!\n");

    while (1) {
        bzero(buffer, BUFFER_SIZE);
        int n = read(newsockfd, buffer, BUFFER_SIZE);
        if (n <= 0) {
            printf("Client disconnected.\n");
            break;
        }

        printf("Client: %s", buffer);

        if (strncmp("bye", buffer, 3) == 0) {
            printf("Connection closing...\n");
            break;
        }

        bzero(buffer, BUFFER_SIZE);
        printf("You: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        write(newsockfd, buffer, strlen(buffer));

        if (strncmp("bye", buffer, 3) == 0) {
            printf("Connection closing...\n");
            break;
        }
    }

    close(newsockfd);
    close(sockfd);
    return 0;
}
