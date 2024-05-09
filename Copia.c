#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define DIM_BUFFER 1024
#define BUFFER_SIZE 64

struct BUFFER
{
    unsigned char buffer[DIM_BUFFER];
    int n;
}typedef BUFFER;

BUFFER ring_buffer[BUFFER_SIZE];
int write_index;
int read_index;
int N_block;
FILE *sorgente, *destinazione;

void *Lettura(void *arg)
{
    int n = fread(ring_buffer[write_index].buffer, 1, DIM_BUFFER, sorgente);
    while(N_block<=BUFFER_SIZE)
    {
        ring_buffer[write_index].n = n;
        write_index = (write_index+1) % BUFFER_SIZE;
        N_block++;
    }
}
void *scrittura(void *arg)
{
    while(N_block>0)
    {
        fwrite(ring_buffer[read_index].buffer, 1, ring_buffer[read_index].n, destinazione);
        read_index = (read_index+1) % BUFFER_SIZE;
        N_block--;
    }
}

int main(int rgc, char *argv[])
{
    pthread_t t1, t2;

    sorgente = fopen(argv[1], "r");
    if(sorgente == NULL)
    {
        printf("errore nell apertura del file sorgente \n");
        exit -1;
    }

    destinazione = fopen(argv[2], "w");
    if(destinazione == NULL)
    {
        printf("errore nell apertura del file sorgente \n");
        exit -1;
    }
    pthread_create(&t1, NULL, Lettura, NULL);
    pthread_create(&t2, NULL, scrittura, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2,NULL);

    fclose(sorgente);
    fclose(destinazione);

    return 0;
}
