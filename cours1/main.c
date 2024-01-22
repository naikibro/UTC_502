#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void) {

    pid_t pid, fils, parent;
    int etat;

    parent = getpid();
    printf("Parent pid : %d\n", parent);

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "fork() failed ! \n");
    }
    
    if (pid == 0) {
        fils = getpid();
        printf("Enfant pid=%d\n", fils);
        sleep(3);
        //exit(0);
    }
    else
    {
        wait(&etat);
        printf("Parent : enfant terminé, renvoie %d\n", etat);
    }

    printf("Fin programme\n");

    return 0;
}