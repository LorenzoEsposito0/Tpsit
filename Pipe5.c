#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define Dim 1024

int main(int argc, char *argv[])
{
    int p, n;
    int fd[2];
    FILE *origine, *destinazione;
    unsigned char buffer[Dim]; //char senza segno

    if(pipe(fd) == -1)
    {
        printf("errore creazione pipe \n");
        exit(EXIT_FAILURE);
    }
    p = fork();

    if(p<0)
    {
        printf("errore creazione fork \n");
        exit(-1);
    }
    if(p>0)
    {
        printf("sono il padre \n");
        close(fd[0]);
        if(argc != 3)
        {
            printf("errore scrittura dei parametri \n");
            exit(-1);
        }
        origine = fopen(argv[1], "r");
        if(origine == NULL)
        {
            printf("errore nell'apertura del file \n");
            exit(-1);
        }
        while((n = fread(buffer, 1,sizeof(buffer), origine)) > 0)
        {
            write(fd[1], buffer, n); //write richiede fd[0/1], il buffer, e poi n
        }
        fclose(origine);
        close(fd[1]);
    }
    else
    {
        printf("sono il figlio \n");
        close(fd[1]);
        destinazione = fopen(argv[2], "w");
        if(destinazione == NULL)
        {
            printf("errore nell'apertura del file \n");
            close(fd[0]);
            exit(-1);
        }
        while((n = read(fd[1], buffer, n)) > 0)
        {
            fwrite(buffer, 1, n, destinazione);
        }
        fclose(destinazione);
        close(fd[0]);

    }

    return 0;
} 
