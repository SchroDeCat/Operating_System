#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int pid1, pid2;

int main()
{
    int fd[2];
    char outpipe[100], inpipe[100];

    pipe(fd);       // create a pipe

    while((pid1 = fork()) == -1);
    if(pid1 == 0)
    {
        lockf(fd[1], 1, 0);
        // put the output sequence into array "outpipe"
        sprintf(outpipe, "child 1 process is sending message!");
        write(fd[1], outpipe, 50);      // write sequence of 50bytes in to pipe
        sleep(3);
        lockf(fd[1], 0, 0);
        exit(0);
    }
    else
    {
        while((pid2 = fork()) == -1);
        if(pid2 == 0)
        {
            lockf(fd[1], 1, 0);     // mutual exclusion
            sprintf(outpipe, "child 2 process is sending message!");
            write(fd[1], outpipe, 50);
            sleep(3);
            lockf(fd[1], 0 , 0);
            exit(0);
        }
        else
        {
            wait(0);                // wait until one child process is over
            read(fd[0], inpipe, 50);// read sequence of 50bytes from the pipe
            printf("%s \n", inpipe);
            wait(0);                // wait until another child process is over
            read(fd[0], inpipe, 50);
            printf("%s \n", inpipe);
            exit(0);
        }
    }
}