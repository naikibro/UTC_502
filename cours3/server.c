// This is a simple client-server communication setup using Unix domain sockets.
// The server sends messages to the client, and the client receives and prints them.

// server.c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define BUFLEN 512
#define NPACK 10

int main()
{
   int sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
   int i = 0;
   struct sockaddr_un server_addr;
   char buf[BUFLEN];

   // Creating the server address
   server_addr.sun_family = AF_UNIX;
   strcpy(server_addr.sun_path, "/tmp/mon_socket");

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