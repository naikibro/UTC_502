// This is a simple client-server communication setup using Internet domain sockets.
// The server sends messages to the client, and the client receives and prints them.

// server.c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define BUFLEN 512
#define NPACK 10

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

    for (i = 0; i < NPACK; i++)
    {
        printf("Message sent\n");
        sprintf(buf, "Message #%d", i + 1);

        // Sends the message in 'buf' to the server address
        sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    }

    close(sockfd);

    return 0;
}