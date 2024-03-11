# Unix Domain Socket Communication

## Description

This project consists of two C programs, `server.c` and `client.c`, that demonstrate client-server communication using Unix domain sockets. The server sends messages to the client, and the client receives and prints them.

## Tools Used

- C programming language
- Unix domain sockets

## File Descriptions

- `server.c`: Sends messages to the client using Unix domain sockets. Utilizes `socket`, `sendto`, and `close` functions. The `socket` function creates a socket, `sendto` sends messages, and `close` closes the socket.
- `client.c`: Receives messages from the server using Unix domain sockets. Utilizes `socket`, `bind`, `recv`, and `close` functions. The `socket` function creates a socket, `bind` binds the socket to an address, `recv` receives messages, and `close` closes the socket.

## Function Descriptions

- `socket()`: Creates a new communication endpoint (socket).
- `unlink()`: Removes a specified file.
- `bind()`: Binds a socket to an address.
- `recv()`: Receives data from a socket.
- `sendto()`: Sends data to a socket.
- `struct sockaddr`: Represents a socket address structure.

## How It Works

1. The server creates a socket and sends messages to the client.
2. The client creates a socket, binds it to the server address, receives messages, and prints them.
3. The server and client communicate using the same socket file located at "/tmp/mon_socket".

## Instructions

1. Compile `server.c` using a C compiler.
2. Compile `client.c` using a C compiler.
3. Run the server executable first, then run the client executable to see the communication in action.
