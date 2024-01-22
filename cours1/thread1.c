#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pthread.h>

void* maFonction(void *arg)
{
    int thread_number = *((int*)arg);
    printf("Thread n°%d\n", thread_number);
    return NULL;
}

int main(void)
{
    pid_t pid;
    pthread_t tid;
    int n = 10;

    printf("Parent tid : %lu\n", pthread_self());

    for(int i = 0; i < n; i++)
    {
        // TODO : pass i to the maFonction and display it
        int *thread_number = malloc(sizeof(int));
        *thread_number = i;

        pthread_create(&tid, NULL, maFonction, thread_number);   
    }

    // Wait for the thread to finish
    if (pthread_join(tid, NULL) != 0)
    {
        perror("pthread_join");
        exit(EXIT_FAILURE);
    }

    printf("Fin programme\n");

    return 0;
}
