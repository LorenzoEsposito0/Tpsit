#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define N 5
int main()
{
    int p;
    int fd[2];
    int moltiplicatore;
    int status; 

    if(pipe(fd) == -1)
    {
        printf("errore nella creazione della pipe \n");
        exit(EXIT_FAILURE);
    }
    p = fork();
    if(p<0)
    {
        printf("errore nella creazione del processo figlio \n ");
        exit(-1);
    }
    else if(p>0)
    {
        close(fd[1]);
        printf("sono il padre, PID = %d \n", getpid());
        int numeri[N];
        read(fd[0], numeri, sizeof(int)*N);
        printf("inserisci il moltiplicatore \n");
        scanf("%d", &moltiplicatore);
        close(fd[0]);
        for(int i = 0; i < N; i++)
        {
            printf("numero %d: %d\n", N, numeri[i]*moltiplicatore);
        }
        wait(&status);
    }
    else 
    {
        close(fd[0]);
        printf("sono il figlio, PID = %d \n", getpid());
        printf("inserisci 5 numeri nell'array \n");
        int numeri[N]; // se dichiaro l'array sotto il main, sia padre che figlio si fanno una copia dell'array, mentre qua solo il figlio lo ha
        for(int i = 0; i < 5; i++)
        {    
            printf("inserire il %d° numero \n", i+1);
            scanf("%d ",&numeri[i]);
        }
        write(fd[1], numeri, sizeof(int)*N);
        close(fd[1]);
    }
        return 0;    
}