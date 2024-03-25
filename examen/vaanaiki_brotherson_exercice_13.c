/** exercice 13 - Vaanaiki Brotherson L3 informatique - CNAM PF
 *
 * Ecrire un programme qui lance 4 process enfants
 * chaque enfant affiche son message avec son pid
 * le parent attend la fin de tous les enfants
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void)
{

    pid_t pid, parent;
    int etat;

    int i = 0;

    parent = getpid();
    printf("\nParent pid : %d\n", parent);

    printf("\n----- Création des processus -----\n\n");

    for (i = 0; i < 4; i++)
    {
        pid = fork();
        sleep(2);
        if (pid < 0)
        {
            fprintf(stderr, "fork() failed ! \n");
        }
        if (pid == 0) // processus enfant
        {
            pid_t fils = getpid();
            printf("\tEnfant pid = %d\n", fils);

            sleep(5);

            printf("\t\tEnfant %d se termine\n\n", fils);
            exit(0);
        }
    }

    // processus parent
    for (i = 0; i < 4; i++)
    {
        wait(&etat);
    }
    printf("Parent : enfants terminés, renvoie %d\n\n", etat);

    printf("Fin programme\n");

    return 0;
}
