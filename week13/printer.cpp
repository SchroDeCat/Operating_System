#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#define MSGKEY 75

using namespace std;

// struct msgform
// {
//     long mtype;
//     char mtext[1000];
// }msg;

msgbuf msg;

int msgqid;

void server()
{
    // create the 75# sequence
    msgqid = msgget(MSGKEY, 0777|IPC_CREAT);// open the msg queue with id: msgqid
    do
    {
        msgrcv(msgqid, &msg, 1000, 0, 0);    // receive the msg in length of 0777
        printf("(server)received\n");       // print the info of receiving successfully
        cout << msg.mtext << endl;
        if()
    }while(msg.mtype != 1);                 // end until receiving the last msg in type 1;
   

    // delete the msgqueue and return the resources
    msgctl(msgqid, IPC_RMID, 0);            // delete the msg queue with id: msgqid
    exit(0);                                // 
}

int main()
{
    server();
    return 0;
}