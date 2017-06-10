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
/* virtual page type */
{
    int pn;     // page number
    int pfn;    // page frame number
    int counter;// the visited amounts during a period cycle
    int time;   // the visited time
};
pl_type pl[32];

struct pfc_struct
/* page frame control struct */
{
    int pn;     // page number
    int pfn;    // page frame number
    pfc_struct  *next;  // pointer to next pfc_struct
};
typedef pfc_struct pfc_type;
pfc_type pfc[32];
pfc_type * freepf_head, * busypf_head, * busypf_tail;

/* global variables */
int diseffect;                  // miss amount
int total_pf;                   // total page frame
int a[total_instruction];       // command sequence
int page[total_instruction];    // page stream of the commands
int offset[total_instruction];  // offset stream of the commands
/* replacement algorithms */
void initialize();              // initialize the data
void FIFO();                    // calculate the hit rate of FIFO
void LRU();                     // calculate the hit rate of LRU
void OPT();                     // calculate the hit rate of OPT
void LFU();                     // calculate the hit rate of LFU
void CLOCK();                   // calculate the hit rate of CLOCK
/* auxiliary functions*/
int find_next_use_interval(int, int);   // find the interval between this use and the next one
int find_last_use_interval(int, int);   // find the interval between this use and the previous one

int main()
{
    int s, i, j;
    srand(10 * getpid());   // using process id as seed

    //s = (float)319 * rand() /32767 / 32767 / 2 + 1; // generate random number as the start point
    s = rand() % 320;   if(s < 0) s *= -1;

    for(i = 0; i < total_instruction; i += 4)
    /* generating the command sequence */
    {
        if (s < 0 || s > 319)
        {
            printf("When i == %d, Error, s == %d\n", i , s);
            exit(0);
        }
        a[i] = s;           // randomly choose m*
        a[i + 1] = a[i] + 1;// conducting one sequential command
        //a[i + 2] = (float)a[i] * rand() / 32767 / 32767 / 2 + a[i + 1] + 2; // conducting the former m'*
        a[i + 2] = (a[i] * rand()) % 319;   if(a[i + 2] < 0) a[i + 2] *= -1;
        a[i + 3] = a [i + 2] + 1;                                           // conducting one sequenntial command 
        //s = (float)(318 - a[i + 2]) * rand() / 32767 /32767 / 2 + a[i + 2] + 2;
        s = ((318 - a[i + 1]) * rand()) % 320;  if(s < 0) s *= -1;
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

    for(total_pf = 4; total_pf <= 32; total_pf++)
    /* the workspace from 4 pages to 32 pages */
    {
        printf("%2d page frames", total_pf);
        FIFO();
        LRU();
        OPT();
        LFU();
        CLOCK();
        printf("\n");
    }
    return 0;
}

void initialize()
/* initialize related data structure */
{
    int i = 0;
    diseffect = 0;

    for(i = 0; i < total_vp; i++)
    /* initialize the virtual pages */
    {
        pl[i].pn = i;
        pl[i].pfn = INVALID;    // reset the page number in page control structure, the page is blank
        pl[i].counter = 0;
        pl[i].time = -1;        // the visited time is 0; and time is -1
    }

    for(i = 0; i < total_pf - 1; i++)
    /* link the queue of page frame controller */
    {
        pfc[i].next = &pfc[i + 1];
        pfc[i].pfn = i;
    }
    pfc[total_pf - 1].next = NULL;
    pfc[total_pf - 1].pfn = total_pf-1;
    freepf_head = & pfc[0];     // the blank page queue's head pointer is pfc[0]
    busypf_head = NULL;
    busypf_tail = NULL;
}

void FIFO()
{
    initialize();   // initialize the pages and the frame

    for(int i = 0; i < total_instruction; i++)
    /* load the new page into memory */
    {
        /* if not loaded */
        if(pl[page[i]].pfn == INVALID)
        {
            diseffect++;    // record the diseffect

            /* if there is still free page frame in memory*/
            if(freepf_head != NULL)
            {
                freepf_head->pn = page[i];          // put the page in the frame
                pl[page[i]].pfn = freepf_head->pfn; // record the frame for the page
                pl[page[i]].counter++;              // record the visit
                pl[page[i]].time = 0;               // start to count time
                freepf_head = freepf_head->next;    // move to the next  
            }
            /* if there is no free page frame in memory */  
            else
            {
                int longest_used_page_frame = 0;
                int longest_used_page_frame_time = pl[pfc[0].pn].time;
                for(int s = 0; s < total_pf; s++)
                /* find the longest existing page in memory */
                {
                    if(pl[pfc[s].pn].time > longest_used_page_frame_time && (pl[pfc[s].pn].time >= 0))
                    {
                        longest_used_page_frame_time = pl[pfc[s].pn].time;
                        longest_used_page_frame = s;
                    }
                }
                /* replace the oldest frame in memory */
                pl[pfc[longest_used_page_frame].pn].pfn = INVALID; // reset the returned page's frame
                pl[pfc[longest_used_page_frame].pn].time = -1;     // reset the returned page's time
                pfc[longest_used_page_frame].pn = page[i]; // record the page for the frame
                pl[page[i]].pfn = longest_used_page_frame; // record the frame for the page
                pl[page[i]].counter++;              // record the visit
                pl[page[i]].time = 0;               // restart to count time
            }
        }
        else
        /* if loaded */
        {
            pl[page[i]].counter++;  // record the visit
        }
        
         /* refresh the timer */
        for(int s = 0; s < total_vp; s++)
        {
            if(pl[s].pfn != INVALID)
            {
                pl[s].time++;
            }
        }
    }
   cout << " FIFO:" << fixed << setprecision(4) << (1 - (double)diseffect / total_instruction);
}

void LRU()
{
    initialize();   // initialize the pages and the frame

    for(int i = 0; i < total_instruction; i++)
    /* load the new page into memory */
    {
        /* if not loaded */
        if(pl[page[i]].pfn == INVALID)
        {
            diseffect++;    // record the diseffect

            /* if there is still free page frame in memory*/
            if(freepf_head != NULL)
            {
                freepf_head->pn = page[i];          // put the page in the frame
                pl[page[i]].pfn = freepf_head->pfn; // record the frame for the page
                pl[page[i]].counter++;              // record the visit
                pl[page[i]].time = 0;               // start to count time
                freepf_head = freepf_head->next;    // move to the next  
            }
            /* if there is no free page frame in memory */  
            else
            {
                int longest_last_used = 0;
                int longest_last_used_frame_interval = find_last_use_interval(longest_last_used, i);
                for(int s = 0; s < total_pf; s++)
                /* find the longest no used frame in memory */
                {
                    if(find_next_use_interval(s, i) > longest_last_used_frame_interval)
                    {
                        longest_last_used_frame_interval = find_last_use_interval(s, i);
                        longest_last_used = s;
                    }
                }
                /* replace the oldest frame in memory */
                pl[pfc[longest_last_used].pn].pfn = INVALID; // reset the returned page's frame
                pl[pfc[longest_last_used].pn].time = -1;     // reset the returned page's time
                pfc[longest_last_used].pn = page[i]; // record the page for the frame
                pl[page[i]].pfn = longest_last_used; // record the frame for the page
                pl[page[i]].counter++;               // record the visit
                pl[page[i]].time = 0;                // restart to count time
            }
        }
        else
        /* if loaded */
        {
            pl[page[i]].counter++;  // record the visit
        }
        
         /* refresh the timer */
        for(int s = 0; s < total_vp; s++)
        {
            if(pl[s].pfn != INVALID)
            {
                pl[s].time++;
            }
        }       
    }
   cout << " LRU:" << fixed << setprecision(4) << (1 - (double)diseffect / total_instruction);
}

void OPT()
{    
    initialize();   // initialize the pages and the frame

    for(int i = 0; i < total_instruction; i++)
    /* load the new page into memory */
    {
        /* if not loaded */
        if(pl[page[i]].pfn == INVALID)
        {
            diseffect++;    // record the diseffect

            /* if there is still free page frame in memory*/
            if(freepf_head != NULL)
            {
                freepf_head->pn = page[i];          // put the page in the frame
                pl[page[i]].pfn = freepf_head->pfn; // record the frame for the page
                pl[page[i]].counter++;              // record the visit
                pl[page[i]].time = 0;               // start to count time
                freepf_head = freepf_head->next;    // move to the next  
            }
            /* if there is no free page frame in memory */  
            else
            {
                int longest_no_used = 0;
                int longest_no_used_frame_interval = find_next_use_interval(longest_no_used, i);
                for(int s = 0; s < total_pf; s++)
                /* find the longest no used frame in memory */
                {
                    if(find_next_use_interval(s, i) > longest_no_used_frame_interval)
                    {
                        longest_no_used_frame_interval = find_next_use_interval(s, i);
                        longest_no_used = s;
                    }
                }
                /* replace the oldest frame in memory */
                pl[pfc[longest_no_used].pn].pfn = INVALID; // reset the returned page's frame
                pl[pfc[longest_no_used].pn].time = -1;     // reset the returned page's time
                pfc[longest_no_used].pn = page[i]; // record the page for the frame
                pl[page[i]].pfn = longest_no_used; // record the frame for the page
                pl[page[i]].counter++;              // record the visit
                pl[page[i]].time = 0;               // restart to count time
            }
        }
        else
        /* if loaded */
        {
            pl[page[i]].counter++;  // record the visit
        }
        
         /* refresh the timer */
        for(int s = 0; s < total_vp; s++)
        {
            if(pl[s].pfn != INVALID)
            {
                pl[s].time++;
            }
        }       
    }
   cout << " OPT:" << fixed << setprecision(4) << (1 - (double)diseffect / total_instruction);
}

void LFU()
{    
    initialize();   // initialize the pages and the frame

    for(int i = 0; i < total_instruction; i++)
    /* load the new page into memory */
    {
        /* if not loaded */
        if(pl[page[i]].pfn == INVALID)
        {
            diseffect++;    // record the diseffect

            /* if there is still free page frame in memory*/
            if(freepf_head != NULL)
            {
                freepf_head->pn = page[i];          // put the page in the frame
                pl[page[i]].pfn = freepf_head->pfn; // record the frame for the page
                pl[page[i]].counter++;              // record the visit
                pl[page[i]].time = 0;               // start to count time
                freepf_head = freepf_head->next;    // move to the next  
            }
            /* if there is no free page frame in memory */  
            else
            {
                int least_used_page_frame = 0;
                int least_used_page_frame_count = pl[pfc[0].pn].counter;
                for(int s = 0; s < total_pf; s++)
                /* find the least used frame in memory */
                {
                    if(pl[pfc[s].pn].counter < least_used_page_frame_count)
                    {
                        least_used_page_frame_count = pl[pfc[s].pn].counter;
                        least_used_page_frame = s;
                    }
                }
                /* replace the oldest frame in memory */
                pl[pfc[least_used_page_frame].pn].pfn = INVALID; // reset the returned page's frame
                pl[pfc[least_used_page_frame].pn].time = -1;     // reset the returned page's time
                pfc[least_used_page_frame].pn = page[i]; // record the page for the frame
                pl[page[i]].pfn = least_used_page_frame; // record the frame for the page
                pl[page[i]].counter++;              // record the visit
                pl[page[i]].time = 0;               // restart to count time
            }
        }  
        else
        /* if loaded */
        {
            pl[page[i]].counter++;  // record the visit
        }
        
         /* refresh the timer */
        for(int s = 0; s < total_vp; s++)
        {
            if(pl[s].pfn != INVALID)
            {
                pl[s].time++;
            }
        }      
    }
    
   cout << " LFU:" << fixed << setprecision(4) << (1 - (double)diseffect / total_instruction);
}

void CLOCK()
{
    static int least_used_page_frame = 0;
    initialize();   // initialize the pages and the frame

    for(int i = 0; i < total_instruction; i++)
    /* load the new page into memory */
    {
        /* if not loaded */
        if(pl[page[i]].pfn == INVALID)
        {
            diseffect++;    // record the diseffect

            /* if there is still free page frame in memory*/
            if(freepf_head != NULL)
            {
                freepf_head->pn = page[i];          // put the page in the frame
                pl[page[i]].pfn = freepf_head->pfn; // record the frame for the page
                pl[page[i]].counter = 1;              // record the visit
                pl[page[i]].time = 0;               // start to count time
                freepf_head = freepf_head->next;    // move to the next  
            }
            /* if there is no free page frame in memory */  
            else
            {
                int least_used_page_frame_bigin = least_used_page_frame;
                int least_used_page_frame_count = pl[pfc[0].pn].counter;
                for(int s = 0; s < total_pf; s++)
                /* find the least used frame in memory */
                {
                    if(pl[pfc[(s + least_used_page_frame_bigin) % total_pf].pn].counter < least_used_page_frame_count)
                    {
                        least_used_page_frame_count = pl[pfc[s].pn].counter;
                        least_used_page_frame = (s + least_used_page_frame_bigin) % total_pf;   // move in a circle
                    }
                }
                /* replace the oldest frame in memory */
                pl[pfc[least_used_page_frame].pn].pfn = INVALID; // reset the returned page's frame
                pl[pfc[least_used_page_frame].pn].time = -1;     // reset the returned page's time
                pfc[least_used_page_frame].pn = page[i]; // record the page for the frame
                pl[page[i]].pfn = least_used_page_frame; // record the frame for the page
                for(int t = 0; t < total_pf; t++) pl[pfc[t].pn].counter = 0;    // reset counters to 0
                pl[page[i]].counter = 1;                 // record the visit
                pl[page[i]].time = 0;                    // restart to count time
            }
        }  
        
         /* refresh the timer */
        for(int s = 0; s < total_vp; s++)
        {
            if(pl[s].pfn != INVALID)
            {
                pl[s].time++;
            }
        }      
    }
    
   cout << " CLOCK:" << fixed << setprecision(4) << (1 - (double)diseffect / total_instruction);
}

int find_next_use_interval(int frame, int instruction)
{
    for(int i = instruction; i >= 0; i --)
    /* find the nearest former same page */
    {
        if(page[i] == pfc[frame].pn)
        {
            instruction = i;
            break;
        }
    }

    int interval = total_instruction;
    for(int i = instruction + 1; i < total_instruction; i++)
    {
        if(page[i] == page[instruction])
        {
            interval = i - instruction;
            break;
        }
    }
    return interval;
}

int find_last_use_interval(int frame, int instruction)
{
    int interval = 0;
    for(int i = instruction; i >= 0; i --)
    /* find the nearest former same page */
    {
        if(page[i] == pfc[frame].pn)
        {
            instruction = i;
            break;
        }
    }

    for(int i = instruction - 1; i >= 0; i--)
    {
        if(page[i] == page[instruction])
        {
            interval = instruction - i;
            break;
        }
    }

    return interval;
}