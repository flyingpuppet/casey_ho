#ifdef TIMER_H
#else
#define TIMER_H
#include <interrupt.h>
#include <stdio.h>


#define TIMERA_INDEX 		0
#define TIMERB_INDEX 		1
#define TIMERC_INDEX 		2
#define TIMERD_INDEX 		3
#define TIMERE_INDEX 		4

#define TIMER_TICK_CYCLE 	0
#define TIMER_TICK_1US		1
#define TIMER_TICK_10US 	2
#define TIMER_TICK_100US	3
#define TIMER_TICK_1MS	 	4


#define TIMER_MODE_INTERRUPT_ONCE 	0
#define TIMER_MODE_INTERRUPT_ALWAYS 1

#ifdef IN_FBC_MAIN_CONFIG

unsigned long OSTimeGet();

// return: timer id, fail if id < 0
int request_timer(int taskid, int count);

int release_timer(int id);

#else

int create_timer(int index, int unit, unsigned count, void (*fn)(void));
int destory_timer(int index, void (*fn)(void));

#endif

#endif //TIMER_H

