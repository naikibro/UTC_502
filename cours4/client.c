// client.c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define BUFLEN 512
#define NPACK 10
#define PATH "/tmp/mon_socket"

int main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0); // Changed AF_UNIX to AF_INET for using IP addresses
    int i = 0;
    struct sockaddr_in server_addr; // Changed from sockaddr_un to sockaddr_in for IP addresses
    char buf[BUFLEN];

    // Creating the server address
    server_addr.sin_family = AF_INET;                     // Changed from AF_UNIX to AF_INET for using IP addresses
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Set the IP address to 127.0.0.1
    server_addr.sin_port = htons(8080);                   // Set the port number to 8080

    // Removes the existing socket file if it exists
    if (!unlink(PATH))
    {
        // Prints a message indicating that the existing socket file was removed
        printf("Removed existing socket: %s\n", PATH);
    }

    printf("\nWaiting...");

    // Binds the socket to the server address
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Error binding socket");
        return 1;
    }

    for (i = 0; i < NPACK; i++)
    {
        // Receives a message from the server and stores it in the buffer 'buf'
        recv(sockfd, buf, BUFLEN, 0);
        printf("Message received: %s\n", buf);
    }

    close(sockfd);

    return 0;
}