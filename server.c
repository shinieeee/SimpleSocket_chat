#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main() {
    int sockfd, newsockfd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;
    char buffer[255];


    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
        exit(1);
    }


    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(8000);

  
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Binding failed");
        close(sockfd);
        exit(1);
    }


    listen(sockfd, 5);


    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0) {
        perror("Error on accept");
        close(sockfd);
        exit(1);
    }

 
    while (1) {
        bzero(buffer, 255);
        int n = read(newsockfd, buffer, 255);
        if (n <= 0) break;

        printf("Client: %s", buffer);

        bzero(buffer, 255);
        fgets(buffer, 255, stdin);
        write(newsockfd, buffer, strlen(buffer));

        if (strncmp("bye", buffer, 3) == 0) break;
    }

    close(newsockfd);
    close(sockfd);
    return 0;
}
