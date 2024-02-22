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
    srand(time(NULL));

    for(int i = 0; i < 5; i++)
    {
        array[i] = rand() % 100;
    }
    //apro la fifo in scrittura perchè deve scrivere i 5 numeri nella fifo da far leggere al programma Consumatore
    fd = open("somma", O_WRONLY);
    for(int i = 0; i < 5; i++)
    {
        //write(fd, &array[i], sizeof(array[i]));//altrimenti fuori dal for facevo 
        printf("write %d \n", array[i]);
    }
    // così
    write(fd, array, sizeof(array));
    close(fd);
    return 0;
}