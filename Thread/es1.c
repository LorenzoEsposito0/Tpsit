#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define N 1000
#define DIM 4

int array[N];
void* Ricerca1(void* arg)
{
    int num = *((int*)arg);   
     for(int i = 0; i < 250; i++)
    {
        if(array[i]==num)
        {
            printf("sono il thread 1\n");
            printf("numero %d trovato in posizione %d\n",num,i);
        }
    }
        pthread_exit(NULL);
}
void* Ricerca2(void* arg)
{
    int num = *((int*)arg);   
    for(int i = 250; i < 500; i++)
    {
        if(array[i]==num)
        {
            printf("sono il thread 2\n");
            printf("numero %d trovato in posizione %d\n",num,i);
        }
    }
        pthread_exit(NULL);
}
void* Ricerca3(void* arg)
{
    int num = *((int*)arg);   
    for(int i = 500; i < 750; i++)
    {
        if(array[i]==num)
        {
            printf("sono il thread 3\n");
            printf("numero %d trovato in posizione %d\n",num,i);
        }
    }
        pthread_exit(NULL);

}
void* Ricerca4(void* arg)
{
    int num = *((int*)arg);   
    for(int i = 750; i < 1000; i++)
    {
        if(array[i]==num)
        {
            printf("sono il thread 4\n");
            printf("numero %d trovato in posizione %d\n",num,i);
        }
    }
        pthread_exit(NULL);

}
int main()
{
    srand(time(NULL));
    int numero;
    printf("che numero vuoi cercare ? \n");
    scanf("%d",&numero);

    for(int i = 0; i < N; i++)
    {
        array[i]=rand() % 500 +1;
    }


    pthread_t array[DIM];
    pthread_create(&array[0],NULL,Ricerca1,(void*)&numero);
    pthread_create(&array[1],NULL,Ricerca2,(void*)&numero);
    pthread_create(&array[2],NULL,Ricerca3,(void*)&numero);
    pthread_create(&array[3],NULL,Ricerca4,(void*)&numero);
    pthread_join(array[0],NULL);
    pthread_join(array[1],NULL);
    pthread_join(array[2],NULL);
    pthread_join(array[3],NULL);

    return 0;
}