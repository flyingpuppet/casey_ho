#ifdef TASK_H
#else
#define TASK_H

#include <stdio.h>

//#define DEBUG_TASK

#define MAX_TASK  32

typedef struct task{
	//int id;
	int priority;
	unsigned int interrupt_mask;
	void * parameter;
	int (*handler)(int task_id, void *param);
}fbc_task_t;

typedef int (* handlerFunction)(int task_id, void * param);

extern void InitTask(void);
#ifdef DEBUG_TASK
extern int RegisterTaskWithName(char *name, handlerFunction handler , void * parameter, unsigned int interrupt_mask, int priority);
#define RegisterTask(name, param, mask, priority) RegisterTaskWithName(#name, name, param, mask, priority)
#else
extern int RegisterTask(handlerFunction handler , void * parameter, unsigned int interrupt_mask, int priority);
#endif
extern void UnregisterTask(int id);
extern void WakeupTaskByID(int id);
extern void WakeupTaskByInterrupt(int interrupt);

extern void sleep(int us);
extern void Delay_ms(unsigned int ms);
extern void MainTask(void);

extern int getCPUUsage(void);

#endif //TASK_H

