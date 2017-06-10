void __schedule_RR()
{
	sturct PCBNode *p = tail;
	do 
	{
		printf("RR: run progress: %s\n", head->porcessName);
		head->state = STA_RUN;
		head->remainSecs -= 1;
		if(head -> remainSecs > 0)
		{
			tail -> Next = head;		// catch the head
			tail = tail -> Next;		// move to head
			head -> State = STA_READY;	// change state to ready
			tail->Next = NULL;			// clear the tail of tail
		}
		else
		{
			head->state = STA_END;		// end the head
			head = head->Next;			// move head to next one
		}
	}while( !p && head != p->Next);
}

//#define SCHE_FIFO
void __schedule()
{
	#ifdef SCHE_FIFO
	__scheduleFIFO();
	#else // default RR
	__schedule_RR();
	#endif
}