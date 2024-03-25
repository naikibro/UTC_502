/** exercice 14 - Vaanaiki Brotherson L3 informatique - CNAM PF
 *
 * Ecrire un programme qui lance 4 threads enfants
 * chaque enfant affiche son message avec son tid
 * le parent attend la fin de tous les threads enfants
 *
 *
 * build this with : gcc vaanaiki_brotherson_exercice_14.c -o vaanaiki_brotherson_exercice_14 -pthread
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void *thread_function(void *arg)
{
    pthread_t tid = pthread_self();
    printf("\tEnfant tid = %lu\n", tid);
    sleep(5);
    printf("\t\tThread %lu se termine\n\n", tid);
    return NULL;
}

int main(void)
{

    pid_t pid, parent;
    int i = 0;

    // threads
    pthread_t thread1, thread2, thread3, thread4;

    printf("\n----- DEBUT DU PROGRAMME -----\n\n");

    pthread_create(&thread1, NULL, thread_function, NULL);
    sleep(2);
    pthread_create(&thread2, NULL, thread_function, NULL);
    sleep(2);
    pthread_create(&thread3, NULL, thread_function, NULL);
    sleep(2);
    pthread_create(&thread4, NULL, thread_function, NULL);

    // Le main attend la fin des threads avant de se terminer
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);

    printf("\n----- FIN DU PROGRAMME -----\n");

    return 0;
}
