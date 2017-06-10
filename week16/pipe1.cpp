#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

int pid_read, pid_print, pid_move;


int main()
{
    int to_move[2], to_print[2];
    int count = 1000;
    // create two pipes
    pipe(to_move);
    pipe(to_print);

    while((pid_read = fork()) == -1);
    if(pid_read == 0)
    /* process read*/
    {
        pid_read = getpid();
        char msg[1000];

        for(int i = 0; i < count; i++)
        /* run for n times */
        {
            
            cout << "Please enter the message you want to enter( end with \"eof\"): " << endl;
            cin >> msg;
            if(strcmp(msg, "eof") == 0) 
            /* Receive end signal */
            {
                i = count;
                cout << "Receive EOF!" << endl;
            }

            /* send to process move through pipe to_move */
            lockf(to_move[1], 1, 0); 
            cout << "(Process Read)Send: " << msg << endl;  // print info
            write(to_move[1], msg, 1000);     // write the data to pipe
            sleep(1);
            lockf(to_move[1], 0, 0);
        }


        exit(0);
    }
    else
    {
        while((pid_move = fork()) == -1);
        if(pid_move == 0)
        /* process move */
        {
            pid_move = getpid();

            char msg[1000];
              
            for(int i = 0; i < count; i++)
            {
                /* receive through pipe to_move */
                lockf(to_move[0], 1, 0);
                read(to_move[0], msg, 1000);
                lockf(to_move[0], 0, 0);
                cout << "(Process Move)Recieve: " << msg << endl;   // print info
                if(strcmp(msg, "eof") == 0) 
                /* Receive end signal */
                {
                    i = count;
                }

                /* send to process move through pipe to_print */
                lockf(to_print[1], 1, 0);
                cout << "(Porcess Move)Send: " << msg << endl;      // print info
                write(to_print[1], msg, 1000);                      // write the data to pipe
                sleep(1);
                lockf(to_print[1], 0, 0);
            }


            exit(0);
        }
        else
        /* process print */
        {          
            pid_print = getpid();

            char msg[1000];
            string content = "";

            for(int i = 0; i < count; i++)
            {
                /* receive through pipe to_print */
                lockf(to_print[0], 1, 0);
                read(to_print[0], msg, 1000);
                cout << "(Process Print)Recieve: " << msg << endl;  // print info
                if(strcmp(msg, "eof") == 0) 
                /* Receive end signal */
                {
                    i = count;
                }
                if(i < count - 1)
                {
                    content += msg;
                    content += "\n";
                }
                lockf(to_print[0], 0, 0);
            }
            cout << "\nOriginal Content:" << endl
            << ">----------------------------------------------------------------<" << endl
            << content << endl
            << ">----------------------------------------------------------------<" << endl;

            exit(0);            
        }
    }
}