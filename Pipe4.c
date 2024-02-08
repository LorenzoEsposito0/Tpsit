#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_DIM 1024

int main(int argc, char *argv[])
{
    int p, n;
    int fd[2];
    FILE *origine, *destinazione;
    unsigned char buffer[BUFFER_DIM];

    if (pipe(fd) == -1)
    {
        printf("errore creazione pipe\n");
        exit(-1);
    }

    p = fork();

    if (p < 0)
    {
        printf("errore generazione figlio\n");
        exit(-1);
    }

    if (p > 0)// padre
    {                 
        printf("sono il padre \n");

        close(fd[0]); // chiudo pipe di lettura nel padre

        if (argc != 4)//devo passare il quarto parametro che è il carattere da cercare 
        {
            fprintf(stderr, "Inserire correttamente il numero di parametri\n");
            exit(-1);
        }

        origine = fopen(argv[1], "r");

        if (origine == NULL)
        {
            printf("Errore apertura file origine\n");
            exit(-1);
        }

        while ((n = fread(buffer, 1, sizeof(buffer), origine)) > 0)
        {
            write(fd[1], buffer, n); // scrivo sulla pipe
        }

        fclose(origine);
        close(fd[1]); // chiudo scrittura. Uscita pipe
        p = fork();
        if(p==0)//figlio 1
        {    
            printf("sono il figlio 1 \n");
            close(fd[1]); // chiudo scrittura nel figlio

            destinazione = fopen(argv[2], "w");

            if (destinazione == NULL)
            {
                printf("Errore apertura file destinazione\n");
                close(fd[0]);
                exit(-1);
            }

            while ((n = read(fd[0], buffer, sizeof(buffer))) > 0)
            {
                fwrite(buffer, 1, n, destinazione); // leggo dalla pipe e scrivo nel file di destinazione
            }

            fclose(destinazione);
            close(fd[0]); // chiudo lettura. Uscita pipe
        }
        else //figlio2
        {
            printf("sono il figlio 2 \n");
            char c;
            int contatore = 0;
            origine = fopen("memoryProcess.txt", "r");//apro il file origine in lettura 
            do
            {
                c = fgetc(origine); //passo al carattere ogni singolo carattere del file
                if(c == argv[3][0])//se il carattere passato come argomento di 3 di 0 è uguale al carattere del file incrementa un contatore
                {
                    contatore++;
                }
            } while (c != EOF);
            fclose(origine);
            printf("il numero di volte in cui è presente la lettera (%s) è: %d \n",argv[3], contatore);
        }
    }

    return 0;
}
