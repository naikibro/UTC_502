#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

#define FILENAME "example.txt"
#define MESSAGE "Bonjour, ceci est un test d'écriture avec fork!\n"

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child Process
        FILE *fd = fopen(FILENAME, "w");
        if (fd == NULL) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }
        fwrite(MESSAGE, sizeof(char), strlen(MESSAGE), fd);
        printf("\n[ enfant ] : writing in file\n");
        fclose(fd);
        exit(EXIT_SUCCESS); // Terminate the child process
    } else if (pid > 0) {
        // Parent Process
        printf("\n[ parent ] : creating child process\n");
        wait(NULL); // Wait for child process to finish

        FILE *fd = fopen(FILENAME, "r");
        if (fd == NULL) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }
        char buffer[1024];
        fgets(buffer, sizeof(buffer), fd); // Read content of the file
        printf("\n[ parent ] : reading content of %s :\n\t %s\n", FILENAME, buffer);
        fclose(fd);
    } else {
        // Fork failed
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
