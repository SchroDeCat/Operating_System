#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
using namespace std;

#define TRUE  1
#define FALSE 0
#define INVALID -1
//#define NULL 0
const int total_instruction = 320;      // amount of instructions
const int total_vp = 32;                // amount of virtual pages
const int clear_period = 50;            // amount of 

struct pl_type
/* page type */
{
    int pn;     // page number
    int pfn;    // page face number
    int counter;// the visited amounts during a period cycle
    int time;   // the visited time 
};
pl_type pl[32];

struct pfc_struct
/* page control struct */
{
    int pn;
    int pfn;
    pfc_struct  *next;
};
typedef pfc_struct pfc_type;
pfc_type pfc[32];
pfc_type * freepf_head, * busypf_head, * busypf_tail;

int diseffect;
int total_pf;
int a[total_instruction];
int page[total_instruction];
int offset[total_instruction];

void initialize(int);
void FIFO();
void LRU();
void OPT();
void LFU();
void CLOCK();

int main()
{
    int s, i, j;
    srand(10 * getpid());   // using process id as seed

    s = (float)319 * rand() /32767 / 32767 / 2 + 1; // generate random number as the start point

    for(i = 0; i < total_instruction; i += 4)
    {
        if (s < 0 || s > 319)
        {
            printf("When i == %d, Error, s == %d\n", i , s);
            exit(0);
        }
        a[i] = s;           // randomly choose m*
        a[i + 1] = a[i] + 1;// conducting one sequential command
        a[i + 2] = (float)a[i] * rand() / 32767 / 32767 / 2 + a[i + 1] + 2; // conducting the former m'*
        a[i + 3] = a [i + 2] + 1;                                           // conducting one sequenntial command 
        s = (float)(318 - a[i + 2]) * rand() / 32767 /32767 / 2 + a[i + 2] + 2;
        if((a[i + 2] > 318) || (s > 319))
        {
            printf("a[%d + 2], a number which is : % d and s == %d\n", i, a[i + 2], s);
        }
    }

    for(i = 0; i < total_instruction; i++)
    /* transforming the commands into page address stream*/
    {
        page[i] = a[i] / 10;
        offset[i] = a[i] % 10;
    }

    for(i = 4; i < total_instruction; i++)
    /* the workspace from 4 pages to 32 pages */
    {
        printf("%2d page frames", i);
        FIFO();
        LRU();
        OPT();
        LFU();
        CLOCK();
        printf("\n");
    }
    return 0;
}

void initialize(int total_pf)
/* initialize related data structure */
{
    int i = 0;
    diseffect = 0;

    for(i = 0; i < total_vp; i++)
    {
        pl[i].pn = i;
        pl[i].pfn = INVALID;    // reset the page number in page control structure, the page is blank
        pl[i].counter = 0;
        pl[i].time = -1;        // the visited time is 0; and time is -1
    }

    for(i = 0; i < total_pf - 1; i++)
    /* link the queue of pfc */
    {
        pfc[i].next = &pfc[i + 1];
        pfc[i].pfn = i;
    }
    pfc[total_pf - 1].next = NULL;
    pfc[total_pf - 1].pfn = total_pf-1;
    freepf_head = & pfc[0];     // the blank page queue's head pointer is pfc[0]
}