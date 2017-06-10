#include <unistd.h>
#include <printf.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    int count = 0;
    //获得当前进程ID
    printf("Current Process Id = %d \n", getpid());

    if ((pid = fork()) < 0) {
        printf("异常退出");
        exit(1);
    } 
    else 
        if (pid == 0) {
        count++;
        printf("进入子进程, 当前进程 currentPid = %d, 父进程 parentPid = %d \n", getpid(),getppid());
        } 
        else {
        count++;
        printf("当前进程   当前进程 currentPid = %d, 子进程 childPid = %d \n", getpid(), pid);
    }
    printf("当前进程 currentPid = %d, Count = %d \n", getpid(), count);
    return 0;
}