/* Écrire un programme qui simule le fonctionnement d'un restaurant qui
organise un buffet : les clients viennent se servir aléatoirement, et la
cuisine réapprovisionne les plats à intervalle régulier. Pour simplifier, on
considérera un plat unique. */

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;
sem_t items; // Représente la quantité de nourriture disponible.

void* client(void* arg) {
    sem_wait(&items); // Attendre qu'il y ait de la nourriture.
    sem_wait(&mutex); // Accès exclusif au plat.
    printf("Client se sert...\n");
    sleep(1); // Simuler le temps de se servir.
    sem_post(&mutex); // Libérer l'accès au plat.
    printf("Client a fini de se servir.\n");
    return NULL;
}

void* cuisine(void* arg) {
    while(1) {
        sleep(5); // Simuler le temps avant de réapprovisionner.
        sem_post(&items); // Ajouter de la nourriture.
        printf("Cuisine a réapprovisionné le plat.\n");
    }
    return NULL;
}

int main() {
    sem_init(&mutex, 0, 1); // Initialiser le mutex à 1.
    sem_init(&items, 0, 0); // Initialiser les items à 0.

    pthread_t t1, t2, t3, tCuisine;

    pthread_create(&tCuisine, NULL, cuisine, NULL);
    pthread_create(&t1, NULL, client, NULL);
    pthread_create(&t2, NULL, client, NULL);
    pthread_create(&t3, NULL, client, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(tCuisine, NULL);

    sem_destroy(&mutex);
    sem_destroy(&items);

    return 0;
}
