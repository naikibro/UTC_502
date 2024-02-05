#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;  // Mutex pour protéger l'accès au plat
int plat = 10;           // Plat à servir
int clients = 5;        // Nombre de clients
int temps_de_cuisson = 2;  // Temps de cuisson en secondes

// Fonction pour le client
void *client_function(void *arg) {
    int client_id = *(int *)arg;
    
    while (1) {
        pthread_mutex_lock(&mutex); // Acquisition du verrou
        
        if (plat > 0) {
            // Manger le plat
            plat--;
            printf("\nClient %d a mangé un plat. \tPlats restants : %d\n", client_id, plat);
        }
        else {
            // Il n'y a plus de plat, quitter
            pthread_mutex_unlock(&mutex); // Libération du verrou
            break;
        }
        
        pthread_mutex_unlock(&mutex); // Libération du verrou
        sleep(rand() % 3); // Temps passé à manger
    }
    
    printf("Client %d a fini de manger.\n", client_id);
    pthread_exit(NULL);
}

// Fonction pour la cuisine
void *cuisine_function(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex); // Acquisition du verrou
        
        // Réapprovisionner le plat
        plat++;
        printf("Plat réapprovisionné. Plats restants : %d\n", plat);
        
        pthread_mutex_unlock(&mutex); // Libération du verrou
        sleep(temps_de_cuisson); // Temps de cuisson du plat
    }
}

int main() {
    pthread_mutex_init(&mutex, NULL);
    pthread_t cuisine_thread;
    pthread_t client_threads[clients];
    int client_ids[clients];
    
    // Création du thread de la cuisine
    pthread_create(&cuisine_thread, NULL, cuisine_function, NULL);
    
    // Création des threads clients
    for (int i = 0; i < clients; i++) {
        client_ids[i] = i + 1;
        pthread_create(&client_threads[i], NULL, client_function, &client_ids[i]);
    }
    
    // Attente que tous les clients aient fini de manger
    for (int i = 0; i < clients; i++) {
        pthread_join(client_threads[i], NULL);
    }
    
    // Terminaison du thread de la cuisine
    pthread_cancel(cuisine_thread);
    
    // Destruction du mutex
    pthread_mutex_destroy(&mutex);
    
    return 0;
}
