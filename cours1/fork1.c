#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void) {

    pid_t pid, fils, parent;
    int etat;
    int i = 0;

    parent = getpid();
    printf("Parent pid : %d\n", parent);
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "fork() failed ! \n");
    }
    
    if (pid == 0) {
        fils = getpid();
        printf("Enfant pid=%d\n", fils);
        for(i = 0; i < 10; i++)
        {
            printf("Enfant i : %d\n", i);
            sleep(1);
        }
        printf("Enfant se termine\n");
        exit(0);
    }
    else
    {
        for(i = 0; i < 10; i++)
        {
            printf("Parent i : %d\n", i);
            sleep(2);
        }
        wait(&etat);
        printf("Parent : enfant terminé, renvoie %d\n", etat);
    }

    printf("Fin programme\n");

    return 0;
}