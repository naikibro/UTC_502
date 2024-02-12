#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#define PORT 12345
#define MAX_MSG_SIZE 1024
#define NUM_MESSAGES 10

int main() {
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[MAX_MSG_SIZE];

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Get server address
    server = gethostbyname("localhost");

    // Initialize socket structure
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(PORT);

    // Connect to server
    connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    // Send messages to server
    for (int i = 0; i < NUM_MESSAGES; ++i) {
        snprintf(buffer, MAX_MSG_SIZE, "Message %d from client", i + 1);
        n = write(sockfd, buffer, strlen(buffer));
    }

    // Close socket
    close(sockfd);
    return 0;
}
