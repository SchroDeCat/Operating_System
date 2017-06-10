#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void * PrintThread(void *);

#define Num_Thread 3

int main()
{
    int i , ret;
    pthread_t a_thread;
    int ThdNum[Num_Thread];

    for(i = 0; i < Num_Thread; i++)
    {
        ThdNum[i] = i;
    }

    for(i = 0; i < Num_Thread; i++)
    {
        ret = pthread_create(&a_thread, NULL, PrintThread, (void*)&ThdNum[i]);
        if(!ret)
        {
            printf("Thread launched successfully\n");
        }
    }
    i = getchar();
    return (0);
}


void * PrintThread(void * num)
{
    int i;

    for(i = 0; i < 5; i++)
    {
        printf("thread number is %d\n", * ((int *)num));
        sleep(1);
    }
    return NULL;
}
