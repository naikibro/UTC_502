#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int variable_globale;
pthread_mutex_t verrou;
int n = 50;

void *thread1_function(void *arg) {

    pthread_t tid = pthread_self(); // Obtention de l'ID du thread

    for (int i = 0; i < n; i++) {
        pthread_mutex_lock(&verrou); // Acquisition du mutex
        
        int square = variable_globale * variable_globale;

        // Faire une courte pause (simulée avec usleep)
        usleep(0.1);

        // Affichage du résultat
        if(square == variable_globale * variable_globale)
        {
            printf("\nThread parent : OK !");
        }
        else{
            printf("\nThread parent : %d est différent de %d\n", square, variable_globale * variable_globale);
        }
        
        pthread_mutex_unlock(&verrou); // Libération du mutex
    }
    pthread_exit(NULL);
}

void *thread2_function(void *arg) {
    pthread_t tid = pthread_self(); // Obtention de l'ID du thread
    
    for (int i = 0; i < n; i++) {
        pthread_mutex_lock(&verrou); // Acquisition du mutex
        
        // Incrémentation de la variable globale
        variable_globale++;
        printf("\n\tThread fils : i(%d) -> %d\n", variable_globale - 1, variable_globale);
        
        pthread_mutex_unlock(&verrou); // Libération du mutex
        
        // Sleep outside of the critical section to allow Thread 1 to recalculate
        usleep(3);
    }
    pthread_exit(NULL);
}

int main() {

    pid_t parent;

    pthread_mutex_init(&verrou, NULL);
    
    pthread_t thread1, thread2;
    variable_globale = 0;

    pthread_create(&thread1, NULL, thread1_function, NULL);
    pthread_create(&thread2, NULL, thread2_function, NULL);
    
    printf("\nDEBUT DU PROGRAMME : variable globale = %d\n\n", variable_globale);


    // Le main attend la fin des threads avant de se terminer
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    pthread_mutex_destroy(&verrou);
    
    printf("\nFIN DU PROGRAMME : variable globale = %d\n", variable_globale);

    return 0;
}
