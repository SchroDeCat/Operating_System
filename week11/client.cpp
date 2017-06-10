#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <stdio.h>
#define MSGKEY 75

struct msgform
{
    long mtype;
    char mtext[1000];
}msg;

int msgqid;

void client()
{
    int i;
    // open the 75# message sequence
    msgqid = msgget(MSGKEY, 0777);
    for(int i = 10; i >= 1; i-- )
    // send messages from type 10 to type 1
    {
        msg.mtype = i;
        printf("(client)sent\n" );               // print the info of successfully sending the message
        msgsnd(msgqid, &msg, 1024, 0);         // send the message of id: msgid in length of 1024
    }
    exit(0);
}

int main()
{
    client();
    return 0;
}