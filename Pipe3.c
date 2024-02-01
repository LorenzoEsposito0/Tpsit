#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5
int main()
{
    int p;
    int fd[2];
    int numeri[N];
    int moltiplicatore;

    if(pipe(fd) == -1) //se == -1 esce dalla condizione  e segnala l'errore nella creazione della pipe
    {
        printf("errore nella creazione della pipe \n");
        exit(-1);
    }
    p = fork(); //creo il processo figlio
    if(p < 0)// se == -1 esce dalla condizione e segnala l'errore nella creazione dle processo figlio
    {
        printf("errore nella creazione del processo \n");
        exit(-1);
    }
    if(p == 0)//figlio
    {
        close(fd[0]); //chiudo la pipe di lettura
        printf("inserisci 5 numeri \n"); //chiedo 5 numeri all'utente che va ad inserire
        for(int i = 0; i < N; i++)
        {
            printf("%d° numero \n", i+1);
            scanf("%d",&numeri[i]);
        }
        //NELLA PIPE WRITE E READ DEVO PASSARE (FD[0/1], il contenuto dell'array, lunghezza dell'array con sizeof)
        write(fd[1], numeri, sizeof(int) * N); //scrivo nella pipe i 5 numeri presenti nell'array //sizeof(variabile) * grandezza dell'array
        close(fd[1]);//chiudo la pipe di scrittura
    }
    // il padre stampa i numeri ricevuti dopo averli moltiplicati per un numero inserito dall'utente e chiesto dal padre stesso.
    if (p > 0) 
    {
        close(fd[1]);//chiudo la pipe di scrittura
        // Leggi l'array dalla pipe di lettura
        read(fd[0], numeri, sizeof(int) * N);//sizeof(variabile) * grandezza dell'array
        close(fd[0]);//leggo l'array di lettura dove ci sono i 5 numeri 

        printf("inserisci un moltiplicatore \n");
        scanf("%d", &moltiplicatore);

        // Stampa i numeri ricevuti dopo averli moltiplicati per il moltiplicatore
        printf("Numeri ricevuti e moltiplicati:\n");//faccio la moltiplicazione tra tutti i numeri dell'array con il moltiplicatore
        for (int i = 0; i < N; i++)
        {
            printf("%d \n", numeri[i] * moltiplicatore);
        }
    }
    return 0;
    
}