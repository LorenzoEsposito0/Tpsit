#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 1000
#define DIM 4

int array[N]; //array di numeri in globale perchè la funzione deve vedere tutti i numeri
int num; //sempre in globale perchè la funzione deve vedere il numero da ricercare
void *Ricerca(void* arg)
{
    int inizio = *((int*)arg);
    int fine = inizio + N/4;
   for(int i = inizio; i < fine; i++)
   {
        if(array[i]==num)
        {
            printf("numero %d trovato in posizione %d \n", num, i);
            pthread_exit(NULL);
        }
   }
   pthread_exit(NULL);
}

int main()
{
    srand(time(NULL)); // Inizializzazione del generatore di numeri casuali
    printf("Che numero vuoi cercare?\n");
    scanf("%d",&num);

    int arrayy[DIM];
    for(int i = 0; i < N; i++)
    {
        array[i] = rand() % 500 + 1;
    }

    pthread_t threads[DIM];
    for(int i = 0; i < 4; i++)
    {
        arrayy[i]=i*(N/4);
        pthread_create(&threads[i], NULL, Ricerca, (void*)&arrayy[i]);
    }
    
    pthread_join(threads[0],NULL);
    pthread_join(threads[1],NULL);
    pthread_join(threads[2],NULL);
    pthread_join(threads[3],NULL);

    return 0;
}
