#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 1024
int main()
{
    int p;
    int fd[2];
    char buffer[BUFFERSIZE];

    if(pipe(fd) == -1)
    {
        printf("errore creazione pipe \n");
        exit(-1);
    }
    p = fork();
    if (p<0) //errore creazione processo figlio
    {
        printf("errore generazione del processo figlio");
    }

    if(p>0) //padre
    {
        printf("ciao io sono il processo padre, PID=%d, PID FIGLIO=%d \n", getpid(), p);
        close(fd[0]);
        const char *messaggio = "buona fortuna";
        if(write(fd[1], messaggio , strlen(messaggio)) == -1)//failed
        {
            printf("errore di scrittura nella pipe \n");
            close(fd[1]);
            exit(-1);
        }
        //write(fd[1], messaggio, sizeof(char) ); //strlen(messaggio)
        close(fd[1]);
    }
    else //figlio
    {
        printf("ciao io sono il processo figlio PID=%d, PID PADRE=%d \n", getpid(), getppid());
        close(fd[1]);
        //const char *mess = "buona fortuna";
        int n = read(fd[0], buffer, BUFFERSIZE);
        if (n == -1) //failed
        {
            printf("errore nella lettura della pipe \n");
            close(fd[0]);
            exit(-1);
        }
        else //success
        {
            buffer[n] = '\0';
            printf("messaggio letto: %s \n",buffer);
            close(fd[0]);
        }        
    }

    return 0;
}