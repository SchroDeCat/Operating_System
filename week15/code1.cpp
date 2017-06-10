#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STA_READY 0
#define STA_RUN 1
#define STA_END 2
#define NR_PC 10

#define SCHE_FIFO

struct PCBNode
{
	char processName[20];
	int processID;
	int remianSecs;
	int ArriveTime;
	int state;
	struct PCBNode * Next;
};

PCBNode nodes[NR_PC];
PCBNode *head, *tail;

void initialize()
// initialize the nodes in queue
{
	int i;

	for(i = 0; i < NR_PC; i++)
	{
		sprintf(nodes[i].processName, "proc_%d", i);
		nodes[i].processID = i;
		nodes[i].remianSecs = rand()%10 + 1;	// at least 1sec
		nodes[i].ArriveTime - rand()%10;		// should use srand() to set seed
	}
}

void setup_ready_queue()
{
	int i, j;
	PCBNode node; 		// temp node used for swap

	// simple sort
	for(i = 0; i < NR_PC; i++)
	{
		for(j = i + 1; j < NR_PC; j++)
		{
			if(nodes[i].ArriveTime > nodes[j].ArriveTime)
				// swap node[i] and node[j]
			{
				memcpy(&node, &nodes[i], sizeof(struct PCBNode));
				memcpy(&nodes[i], &nodes[j], sizeof(struct PCBNode));
				memcpy(&nodes[j], &node, sizeof(struct PCBNode));
			}
		}
	}

	// initialize ready queue;
	for(i = 0; i < NR_PC; i++)
	{
		nodes[i].Next = &nodes[i + 1];
		nodes[i].state = STA_READY;
	}
	nodes[NR_PC - 1].Next = NULL;
	nodes[NR_PC - 1].state = STA_READY;

	head = &nodes[0];
	tail = &nodes[NR_PC - 1];
}

void print_ready_queue()
{
	PCBNode *p;
	printf("Ready queue: ");
	for(p = head; p != NULL; p = p->Next)
	{
		printf("%s[%d] ", p->processName, p->remianSecs);
	}
	printf("\n");
}

void __schedule_FIFO()
{
	printf("FIFP: run progress: %s\n", head->processName);
	head->state = STA_RUN;
	head->remianSecs = 0;
	head->state = STA_END;
	head = head->Next;
}

void __schedule()
{
	#ifdef SCHE_FIFO
	__schedule_FIFO();
	#else
	#endif
}

void schedule()
{
	while(head != NULL && head -> state == STA_READY)
	{
		print_ready_queue();
		__schedule();
	}
}

int main()
{
	initialize();
	setup_ready_queue();
	schedule();
	return 0;
}