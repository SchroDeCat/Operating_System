#include <unistd.h>
#include <printf.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;


int main(int argc, char *argv[]) {
    pid_t pid, pid2;
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
        //cout << "B" << endl;
        printf("子进程B, 当前进程 currentPid = %d, 父进程 parentPid = %d \n", getpid(),getppid());
    } 
    else {
        if((pid2 = fork()) < 0)
        /*exception*/
        {
            cout << "异常退出" << endl;
            exit(1);
        }
        else if(pid2 == 0)
        /*the second child thread*/
        {
            //cout << "C" << endl;
            printf("子进程C, 当前进程 currentPid = %d, 父进程 parentPid = %d \n", getpid(),getppid());
            count++;
        }
        else
        /*the parent thread*/
        {
            //cout << "A" << endl;
            count++;
            printf("父进程A  当前进程 currentPid = %d, 子进程 childPid = %d \n", getpid(), pid2);
            wait();
        }
     //   count++;
     //   printf("当前进程   当前进程 currentPid = %d, 子进程 childPid = %d \n", getpid(), pid);
    }
    printf("\n当前进程 currentPid = %d, Count = %d \n\n", getpid(), count);
    return 0;
}