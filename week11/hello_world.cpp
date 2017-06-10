#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
int main()
{
    pthread_t t1, t2;

    void *p_msg(void *);

    pthread_create(&t1, NULL, p_msg, (void*)"hello ");
    pthread_create(&t2, NULL, p_msg, (void*)"world\n");
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}

void* p_msg(void * m) {
    int i;
    
    for(int i = 0; i < 100; i++)
    {
        printf("%s", m);
        fflush(stdout);
        sleep(1);
    }
    return NULL;
}