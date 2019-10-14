#include <timer.h>
#include <register.h>
#include <interrupt.h>

#ifdef IN_FBC_MAIN_CONFIG
#include <task.h>
#include <log.h>
#include <hdmi.h>
#endif

//#define TIMER_MUX                                  0x00b0
//#define TIMERA                                     0x00b1
//#define TIMERB                                     0x00b2
//#define TIMERC                                     0x00b3
//#define TIMERD                                     0x00b4
//#define TIMERE                                     0x00b5

static char TAG[]= "timer" ;

#define WR_TIMER_TICK(i,j) 	Wr_reg_bits(TIMER_MUX, (j), (i)*3, 3)
#define WR_TIMER_MODE(index, mode) Wr_reg_bits(TIMER_MUX, (mode), ((index)+16), 1)

int set_timer_int_enable(int timer, int enable)
{
	return SetInterruptEnable(INT_TIMERA-timer, enable);
}

unsigned long OSTimeGet()
{
	return Rd(TIMERE);
}


#ifdef IN_FBC_MAIN_CONFIG
#define MAX_TIMER_COUNTER	32

typedef struct task_timer{
	int id;//task id
	int counterValue;
	int counter;
}task_timer_t;

static task_timer_t counter[MAX_TIMER_COUNTER] = {0};


int request_timer(int taskid, int count)
{
	int i;
	for(i=0;i<MAX_TIMER_COUNTER; i++)
	{
		if(0 == counter[i].id){
			counter[i].counter = count;
			counter[i].counterValue = count;
			counter[i].id = taskid;
			return i;
		}
	}
	return -2;
}

int release_timer(int id)
{
	//int i;
	//printf("release_timer id is %d.\n", id);
	counter[id].counter = 0;
	counter[id].counterValue = 0;
	counter[id].id = 0;
	return 0;
}

void timer_handler()
{
	int i;
	for(i=0;i<MAX_TIMER_COUNTER; i++)
	{
		if(counter[i].counter > 0)
		{
			counter[i].counter--;
		}else if((0 == counter[i].counter)&&(0!=counter[i].id))
		{
			WakeupTaskByID(counter[i].id);
			counter[i].counter = counter[i].counterValue;
			//LOGI(TAG,"wake up task %d counterValue %d\n",counter[i].id,counter[i].counterValue);
		}
	}
}

void init_timer()
{
	//for system time ,unit is 1ms
	WR_TIMER_TICK(TIMERE_INDEX, TIMER_TICK_1MS);
	Wr(TIMERE, 0);

	//init other timer unit is 1ms
	WR_TIMER_TICK(TIMERA_INDEX, TIMER_TICK_1MS);
	WR_TIMER_TICK(TIMERB_INDEX, TIMER_TICK_1MS);
	WR_TIMER_TICK(TIMERC_INDEX, TIMER_TICK_1MS);
	WR_TIMER_TICK(TIMERD_INDEX, TIMER_TICK_1MS);

	//init timer mode 
	//a&b mode default 1 and c&d mode default 0, 
	//1 means always interrupt, 0 means interrupt once
	WR_TIMER_MODE(TIMERC_INDEX, TIMER_MODE_INTERRUPT_ALWAYS);
	WR_TIMER_MODE(TIMERD_INDEX, TIMER_MODE_INTERRUPT_ALWAYS);

	Wr(TIMERA, 10);//TimerA 100ms
	Wr(TIMERB, 20);//TimerB 200ms
	Wr(TIMERC, 10);//TimerC 500ms
	Wr(TIMERD, 10);//TimerD 1000ms

	RegisterInterrupt(INT_TIMERA, INT_TYPE_FIQ, timer_handler);
	set_timer_int_enable(TIMERA_INDEX, 1);

	set_timer_int_enable(TIMERB_INDEX, 1);
}

#else

int create_timer(int index, int unit, unsigned count, void (*fn)(void))
{
	WR_TIMER_TICK(index, unit);

	switch(index)
	{
		case TIMERA_INDEX:
			Wr(TIMERA, count);
			RegisterInterrupt(INT_TIMERA, INT_TYPE_FIQ, fn);
			break;

		case TIMERB_INDEX:
			Wr(TIMERB, count);
			RegisterInterrupt(INT_TIMERB, INT_TYPE_FIQ, fn);
			break;

		case TIMERC_INDEX:
			Wr(TIMERC, count);
			RegisterInterrupt(INT_TIMERC, INT_TYPE_FIQ, fn);
			break;

		case TIMERD_INDEX:
			Wr(TIMERD, count);
			RegisterInterrupt(INT_TIMERD, INT_TYPE_FIQ, fn);
			break;
	}

	set_timer_int_enable(index, 1);
	return 0;
}

int destory_timer(int index, void (*fn)(void))
{
	set_timer_int_enable(index, 0);
	switch(index)
	{
		case TIMERA_INDEX:
			UnregisterInterrupt(INT_TIMERA, fn);
			break;

		case TIMERB_INDEX:
			UnregisterInterrupt(INT_TIMERB, fn);
			break;

		case TIMERC_INDEX:
			UnregisterInterrupt(INT_TIMERC, fn);
			break;

		case TIMERD_INDEX:
			UnregisterInterrupt(INT_TIMERD, fn);
			break;
	}
	return 0;
}

#endif
