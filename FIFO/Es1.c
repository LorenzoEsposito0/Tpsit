#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
    int fd;
    //int x;
    if(mkfifo("myfifo1",0777) == -1)
    {
        if(errno != EEXIST)
        {
            printf("errroe nella creazione della fifo");
            return 1;
        }
    }
    //apro la FIFO in scrittura
    fd = open("myfifo1",O_WRONLY);
    printf("apertura fifo \n");
    int x = 90;
    if(write(fd, &x, sizeof(x)) == -1)
    {
        printf("errore nella scrittura della FIFO \n");
        return 2;
    }
    printf("ho scritto nella FIFO \n");
    close(fd);

    return 0;
}