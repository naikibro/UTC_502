#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

int variable_globale;
sem_t semaphore;
int n = 50;

void *thread1_function(void *arg) {

    pthread_t tid = pthread_self(); // Obtention de l'ID du thread

    for (int i = 0; i < n; i++) {
        sem_wait(&semaphore); // Wait for access to the shared resource

        int square = variable_globale * variable_globale;

        // Faire une courte pause (simulée avec usleep)
        usleep(.1); // 100ms

        // Affichage du résultat
        if (square == variable_globale * variable_globale) {
            printf("\nThread parent : OK !");
        } else {
            printf("\nThread parent : %d est différent de %d\n", square, variable_globale * variable_globale);
        }

        sem_post(&semaphore); // Release access to the shared resource
    }
    pthread_exit(NULL);
}

void *thread2_function(void *arg) {
    pthread_t tid = pthread_self(); // Obtention de l'ID du thread

    for (int i = 0; i < n; i++) {
        sem_wait(&semaphore); // Wait for access to the shared resource

        // Incrémentation de la variable globale
        variable_globale++;
        printf("\n\tThread fils : i(%d) -> %d\n", variable_globale - 1, variable_globale);

        sem_post(&semaphore); // Release access to the shared resource

        // Sleep outside of the critical section to allow Thread 1 to recalculate
        usleep(3); // 300ms
    }
    pthread_exit(NULL);
}

int main() {

    pthread_t thread1, thread2;
    variable_globale = 0;

    sem_init(&semaphore, 0, 1); // Initialize the semaphore with an initial value of 1

    pthread_create(&thread1, NULL, thread1_function, NULL);
    pthread_create(&thread2, NULL, thread2_function, NULL);

    printf("\nDEBUT DU PROGRAMME : variable globale = %d\n\n", variable_globale);

    // Le main attend la fin des threads avant de se terminer
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    sem_destroy(&semaphore);

    printf("\nFIN DU PROGRAMME : variable globale = %d\n", variable_globale);

    return 0;
}
