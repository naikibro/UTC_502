#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <semaphore.h>

#define NUM_PHILOSOPHERS 5

pthread_t philosophers[NUM_PHILOSOPHERS];            // IDs des threads pour les philosophes
sem_t philosophers_semaphores[NUM_PHILOSOPHERS];      // Sémaphores pour chaque philosophe

int meals_eaten[NUM_PHILOSOPHERS] = {0};              // Compteur pour suivre les repas mangés par chaque philosophe

void *dining(void *arg) {
    int philosopher_id = *((int *)arg);
    int left_philosopher = philosopher_id;
    int right_philosopher = (philosopher_id + 1) % NUM_PHILOSOPHERS;
    
    // Générer une limite aléatoire pour le nombre de repas que chaque philosophe peut manger
    int max_meals = rand() % 10 + 1; // Limite aléatoire entre 1 et 10 repas

    while (meals_eaten[philosopher_id] < max_meals) {
        // Penser (durée aléatoire)
        printf("Philosophe %d pense.\n", philosopher_id+1);
        usleep(rand() % 5);

        // Demander les fourchettes
        printf("Philosophe %d veut prendre les fourchettes.\n", philosopher_id+1);
        sem_wait(&philosophers_semaphores[left_philosopher]);
        sem_wait(&philosophers_semaphores[right_philosopher]);

        // Manger (durée aléatoire)
        printf("Philosophe %d mange.\n", philosopher_id+1);
        usleep(rand() % 5);

        // Relâcher les fourchettes
        sem_post(&philosophers_semaphores[left_philosopher]);
        sem_post(&philosophers_semaphores[right_philosopher]);

        // Incrémenter le compteur de repas
        meals_eaten[philosopher_id]++;
    }

    printf("\tPhilosophe %d a fini de manger ses %d repas.\n", philosopher_id+1, max_meals);
    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    printf("\nLe dîner des philosophes est ouvert !\n\n-----------------------\n\n");

    // Initialiser les sémaphores pour les philosophes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&philosophers_semaphores[i], 0, 1); // Initialiser les sémaphores des philosophes à 1
    }

    int philosopher_ids[NUM_PHILOSOPHERS];
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, dining, &philosopher_ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    printf("\nLe dîner des philosophes est terminé, les estomacs sont pleins et les esprits sont allégés !\n\n\n");

    printf("----- L E A D E R B O A R D -----\n\n");
    int max = 0, winner=0;
    for(int i=0; i < NUM_PHILOSOPHERS; i++)
    {
        printf("\tPhilosophe n°%d a mangé %d repas\n", i+1, meals_eaten[i]);
        if(max < meals_eaten[i])
        {
            max = meals_eaten[i];
            winner = i+1;
        }
    }

    printf("\nFélicitations au philosophe n°%d qui a mangé le plus de repas avec %d repas engloutis !\n\n", winner, max);

    return 0;
}
