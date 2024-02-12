#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 12345
#define MAX_MSG_SIZE 1024
#define NUM_MESSAGES 10

int main() {
    int sockfd, newsockfd, clilen;
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    char buffer[MAX_MSG_SIZE];

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Initialize socket structure
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    // Bind the host address
    bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    // Start listening for the clients
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    // Accept connection from client
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

    // Receive messages and print them
    for (int i = 0; i < NUM_MESSAGES; ++i) {
        bzero(buffer, MAX_MSG_SIZE);
        n = read(newsockfd, buffer, MAX_MSG_SIZE - 1);
        printf("Message from client: %s\n", buffer);
    }

    // Close sockets
    close(newsockfd);
    close(sockfd);
    return 0;
}
