#include <stdio.h>
#include <unistd.h>

int main()
{
    int fd[2]; 
    //fd[0] - read
    //fd[1] - write
    if(pipe(fd) == -1)
    {
        printf("errore nella pipe \n");
        return 1;
    }
    int p = fork();
    if(p == 0)
    {
        close(fd[0]);
        int x; 
        printf("scrivi un numero \n");
        scanf("%d\n",x);
        write(fd[1], &x, sizeof(int));
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        int y;
        read(fd[0], &y, sizeof(int));
        close(fd[0]);
        printf("ottenuto dal processo figlio %d\n", &y);
    }
    return 0; 
}