#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 1000
#define DIM 4

int array[N];

void* Ricerca1(void* arg)
{
    int num = *((int*)arg);
    for(int i = 0; i < 250; i++)
    {
        if(array[i] == num)
        {
            printf("Sono il thread 1. Numero %d trovato in posizione %d\n", num, i);
        }
    }
    pthread_exit(NULL);
}

void* Ricerca2(void* arg)
{
    int num = *((int*)arg);
    for(int i = 250; i < 500; i++)
    {
        if(array[i] == num)
        {
            printf("Sono il thread 2. Numero %d trovato in posizione %d\n", num, i);
        }
    }
    pthread_exit(NULL);
}

void* Ricerca3(void* arg)
{
    int num = *((int*)arg);
    for(int i = 500; i < 750; i++)
    {
        if(array[i] == num)
        {
            printf("Sono il thread 3. Numero %d trovato in posizione %d\n", num, i);
        }
    }
    pthread_exit(NULL);
}

void* Ricerca4(void* arg)
{
    int num = *((int*)arg);
    for(int i = 750; i < 1000; i++)
    {
        if(array[i] == num)
        {
            printf("Sono il thread 4. Numero %d trovato in posizione %d\n", num, i);
        }
    }
    pthread_exit(NULL);
}

int main()
{
    srand(time(NULL)); // Inizializzazione del generatore di numeri casuali
    int numero;
    printf("Che numero vuoi cercare?\n");
    scanf("%d",&numero);

    for(int i = 0; i < N; i++)
    {
        array[i] = rand() % 500 + 1;
    }

    pthread_t threads[DIM];
    pthread_create(&threads[0], NULL, Ricerca1, (void*)&numero);
    pthread_create(&threads[1], NULL, Ricerca2, (void*)&numero);
    pthread_create(&threads[2], NULL, Ricerca3, (void*)&numero);
    pthread_create(&threads[3], NULL, Ricerca4, (void*)&numero);

    for(int i = 0; i < DIM; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
