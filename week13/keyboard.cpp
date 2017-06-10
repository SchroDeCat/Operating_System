#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

#define MSGKEY 75

// struct msgform
// {
//     long mtype;
//     char mtext[1];
// }msg;

msgbuf msg;

const bool end = true;

int msgqid;

void client(string message , bool end)
{
    int i;
    // open the 75# message sequence
    msgqid = msgget(MSGKEY, 0777);
    if(!end)
    // send messages from type 10 to type 1
    {
        msg.mtype = 2;
        printf("(client)sent\n" );                           // print the info of successfully sending the message
        msgsnd(msgqid, &msg, message.size(), 0);             // send the message of id: msgid in length of 1
    }
    else
    {
        msg.mtype = 1;
        printf("(client)sent\n" );                           // print the info of successfully sending the message
        msgsnd(msgqid, &msg, message.size(), 0);             // send the message of id: msgid in length of 1
    }
    exit(0);
}

int main()
{
    string message;
    int num = 0;
    cout << "keyboard Checker is running!" << endl;
    cout << "Please enter the amount of message you want to send: " << endl;
    cin >> num;
    cout << endl;
    cout << "Please enter the message you want to send to the printer: " << endl;

    for(int i = 0; i < num; i++)
    // send the message to printer by character
    {
        cin >> message;
        if(i != num - 1)
        client(message, !end);
        else
        client(message, end);
    }
    
    return 0;
}