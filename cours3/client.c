// client.c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define BUFLEN 512
#define NPACK 10
#define PATH "/tmp/mon_socket"

int main()
{
    int sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    int i = 0;
    struct sockaddr_un server_addr;
    char buf[BUFLEN];

    // Creating the server address
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, "/tmp/mon_socket");

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