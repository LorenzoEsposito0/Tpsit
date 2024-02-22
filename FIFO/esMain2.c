#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <time.h>

#define BUFFERSIZE 1024
int main()
{
    int array[5];
    int fd;
    int somma;
    //apro la fifo in lettura perchè deve leggere la somma dei numeri generati
    fd = open("somma", O_RDONLY);
    if(fd == -1)
    {
        printf("Errore apertura FIFO \n");
        close(fd);
        exit(-1);
    }
    if(read(fd, array, sizeof(array)) == -1)
    {
        printf("errore lettura della FIFO \n");
        close(fd);
        exit(-1);
    }
    for(int i = 0; i < 5; i++)
    {
        printf("numero letto %d \n", array[i]);
        somma += array[i];
    }
    close(fd);
    printf("\n\n somma: %d ", somma);
    return 0;

}