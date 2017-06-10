#include <unistd.h>
#include <printf.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int pid;
    int count = 0;
    //获得当前进程ID
    printf("Current Process Id = %d \n", getpid());

    if ((pid = fork()) < 0) {
        printf("异常退出");
        exit(1);
    } 
    if (pid == 0) {
        printf("b \n");
    } 
    else {
        count++;
        printf("a \n");
    }
    printf("当前进程 currentPid = %d, Count = %d \n", getpid(), count);
    return 0;
}