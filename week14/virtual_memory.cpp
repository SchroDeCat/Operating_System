#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/limits.h>
#include <iostream>
using namespace std;


void get_proc_stat()
{
    char procfile[PATH_MAX] = {0};
    char buf[4096];
    char *str, *token ;
    int fd, cnt;

    sprintf(procfile, "/proc/%d/stat", (int)getpid());
    if(access(procfile,F_OK) < 0)
    {
        perror("access.");
        exit(1);
    }
    if((fd = open(procfile, O_RDONLY))<0)
    {
        perror("open.");
        exit(1);
    }
    // char procfile[PATH_MAX] = {0};
	// char buf[4096];
	// char *str,*token;
	// int fd,cnt;
	// sprintf(procfile,"/proc/%d/stat",(int)getpid());
	// if (access(procfile,F_OK)<0){
	// 	perror("access.");
	// 	exit(1);
	// }
	// if ((fd = open(procfile,O_RDONLY))<0){
	// 	perror("open.");
	// 	exit(1);
	// }

    // cout << "PATH_MAX" << PATH_MAX << endl;
    // cout << "getpid: " << getpid() << endl;
    // cout << "fd: " << fd << endl;
    // cout << sizeof(buf) << endl;
    // cout << read(fd,buf,sizeof(buf)) << endl;
    while(read(fd, buf, sizeof(buf)) > 0)
    {
        //printf("test: %d",read(fd, buf, sizeof(buf)));
        for(str = buf, cnt = 1; ; str = NULL, cnt++)
        {
            token = strtok(str, " ");
            if(token == NULL)
            {
                break;
            }
            if(cnt == 1)
            {
                printf("pid: %s\n", token);
            }
            else if(cnt == 12)
            {
                printf("major fault: %s\n", token);
            }
            else if(cnt == 10)
            {
                printf("minor fault: %s\n", token);
            }
        }
     }
    printf("\n");
}

#define PAGE_SIZE 4096

int main(int argc, char* argv[])
{
    char * p = NULL;
    int cnt = 30;

    get_proc_stat();
    p = (char*)malloc(PAGE_SIZE*100);
    get_proc_stat();

    // for(int i = 0; i < 100; i++)
    // {
    //     memset(p + i * PAGE_SIZE, 0x55, PAGE_SIZE*100);
    //     get_proc_stat();
    //     sleep(1);
    // }

    memset(p, 0x55, PAGE_SIZE*100);
    get_proc_stat();

    return 0;
}