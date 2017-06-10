#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int fdrd, fdwt;
char c;

void rdwrt()
{
    for(;;)
    {
        if(read(fdrd, &c, 1) != 1) return;
        sleep(1);
        write(fdwt,&c,1);
    }
}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        exit(1);
    }
    if((fdrd = open(argv[1], O_RDONLY)) == -1)
    {
        exit(1);
    }
    if((fdwt = open(argv[2], 0666)) == -1)
    {
        exit(1);
    }

    fork();
    rdwrt();    // do the same thing in two processes
    exit(0);
}