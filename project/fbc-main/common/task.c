#include <task.h>
#include <log.h>
#include <timer.h>
#include <malloc.h>
#include <string.h>
#include <task_priority.h>
#include <reboot.h>

#define WATCH_DOG_THRESHHOLD	16384

static char TAG[]= "task" ;
static fbc_task_t tasks[MAX_TASK];
static unsigned int PendingTaskFlag = 1; //32bit , 0: pending 1: running
static unsigned int NextPendingTaskFlag = 0; //32bit , 0: pending 1: running
static int current_task = 0;

static int idle_counter;
static int cpu_usage;

#ifdef DEBUG_TASK
static char *task_name[MAX_TASK];
#endif

void sleep(int us){
	int n= us*(80/3);
	while(n--);
}

void Delay_ms(unsigned int ms)
{
	unsigned int i = 0;
	unsigned int num = 5000;// 1ms
	for(i=0; i<ms; i++)
	{
		sleep(num);
	}
}

static int idle_task(int id, void * param){
	int start, end;
	start = OSTimeGet();
	__asm__("sleep");
	end = OSTimeGet();
	idle_counter += end - start;
	return 1;
}

static int idleHandler(int task_id, void *param)
{
	 cpu_usage = ((1110-idle_counter)*100) / 1110 ;
	 //printf("counter is %d , cpu_usage is %d%\n", idle_counter, cpu_usage);
	 idle_counter = 0;
	 return 0;
}

int getCPUUsage(void)
{
	return cpu_usage;
}

void InitTask(void)
{
	idle_counter = 0;
	tasks[0].handler = idle_task;
	tasks[0].parameter = NULL;
	tasks[0].interrupt_mask = 0;
	tasks[0].priority = 0;
#ifdef DEBUG_TASK
	task_name[0]="idle_task";
#endif
	int cpu_idle_task_id = RegisterTask(idleHandler, NULL, 0, TASK_PRIORITY_CPU_IDLE);
	request_timer(cpu_idle_task_id,100);//1s
}

#ifndef DEBUG_TASK
int RegisterTask(handlerFunction handler , void * parameter, unsigned int interrupt_mask, int priority)
#else
int RegisterTaskEx(handlerFunction handler , void * parameter, unsigned int interrupt_mask, int priority)
#endif
{
	for (int id=1; id<MAX_TASK; id++){
		if(tasks[id].handler == NULL){
			//tasks[id].id = id;
	        tasks[id].handler = handler;
	        tasks[id].parameter = parameter;
	        tasks[id].interrupt_mask = interrupt_mask;
	        tasks[id].priority = priority;
#ifndef DEBUG_TASK
	        if (current_task == 0)
	        	LOGD(TAG,"task %d(p%d) regiter OK", id, tasks[id].priority);
	        else
	        	LOGD(TAG,"task %d(p%d) regiter OK in task %d(p%d)", id, tasks[id].priority, current_task, tasks[current_task].priority);
#endif
			return id;
		}        
    }
	return -1;
}

#ifdef DEBUG_TASK
int RegisterTaskWithName(char *name, handlerFunction handler , void * parameter, unsigned int interrupt_mask, int priority){
	int len;
	int id = RegisterTaskEx(handler, parameter, interrupt_mask, priority);
	if (id){
		if (name){
			len = strlen(name);
			if (len > 31) len = 31;
			task_name[id] = (char *)calloc(len+1, 1);
			if (task_name[id]) {
				strncpy(task_name[id], name, len);
		        if (current_task == 0)
		        	LOGD(TAG,"task %d(p%d):%s regiter OK", id, tasks[id].priority, task_name[id]);
		        else
		        	LOGD(TAG,"task %d(p%d):%s regiter OK in task %d(p%d):%s", id, tasks[id].priority, task_name[id], current_task, tasks[current_task].priority, task_name[current_task]);
				return id;
			}
		}
        if (current_task == 0)
        	LOGD(TAG,"task %d(p%d) regiter OK", id, tasks[id].priority);
        else
        	LOGD(TAG,"task %d(p%d) regiter OK in task %d(p%d)", id, tasks[id].priority, current_task, tasks[current_task].priority);
	}
	return id;
}
#endif

void UnregisterTask(int id){
	PendingTaskFlag &= ~(1<<id);
	tasks[id].handler = NULL;
#ifdef DEBUG_TASK
	if (task_name[id]){
        if (current_task == 0)
        	LOGD(TAG,"task %d(p%d):%s unregiter OK", id, tasks[id].priority, task_name[id]);
        else
        	LOGD(TAG,"task %d(p%d):%s unregiter OK in task %d(p%d):%s", id, tasks[id].priority, task_name[id], current_task, tasks[current_task].priority, task_name[current_task]);
		free(task_name[id]);
	}
	else{
		if (current_task == 0)
			LOGD(TAG,"task %d(p%d) unregiter OK", id, tasks[id].priority);
		else
			LOGD(TAG,"task %d(p%d) unregiter OK in task %d(p%d)", id, tasks[id].priority, current_task, tasks[current_task].priority);
	}
#else
	if (current_task == 0)
		LOGD(TAG,"task %d(p%d) unregiter OK", id, tasks[id].priority);
	else
		LOGD(TAG,"task %d(p%d) unregiter OK in task %d(p%d)", id, tasks[id].priority, current_task, tasks[current_task].priority);
#endif
}

void WakeupTaskByID(int id){
	NextPendingTaskFlag |= 1<<id;
}

void WakeupTaskByInterrupt(int interrupt){
	for (int id=1; id<MAX_TASK; id++){
		if ((tasks[id].handler != NULL)&&(tasks[id].interrupt_mask & (1<<interrupt))){
			NextPendingTaskFlag |= 1<<id;
		}
	}
}

int NeedSwitchTask(int cur_id){
	int id;
	int next_id = 0;
	_disable();
	PendingTaskFlag |= NextPendingTaskFlag;
	NextPendingTaskFlag = 0;
	_enable();
	for (id=1; id<MAX_TASK; id++){
	    if ((id!=cur_id)&&(tasks[id].handler!=NULL)&&(PendingTaskFlag&(1<<id))&&(tasks[id].priority>=tasks[cur_id].priority)) {
	    	if (tasks[id].priority >= tasks[next_id].priority)
	    		next_id = id;
	    }
	}
#ifdef DEBUG_TASK
	if (next_id) 
		LOGD(TAG,"higher priority task %d(p%d):%s waiting", next_id, tasks[next_id].priority, task_name[next_id]);
#endif
	return next_id;
}

int RunTask(int id)
{
	int ret = 0;
	if (tasks[id].handler){
		current_task = id;
		ret = tasks[id].handler(id, tasks[id].parameter);
	}
	return ret;
}

void SuspendTask(int id){
	PendingTaskFlag &= ~(1<<id);
}

void MainTask(void){
	int id = 0;
	int new_id = 0;
#ifdef DEBUG_TASK
	unsigned task_start_time = OSTimeGet();
	unsigned task_run_count = 0;
	unsigned int dog_count;
	unsigned while_time = 0;
	unsigned while_time1 = 0;
	unsigned while_time2 = OSTimeGet();
#endif
	int task_ret = 0;
	set_watchdog_threshold(WATCH_DOG_THRESHHOLD);
	enable_watchdog();
		
	while(1){
#ifdef DEBUG_TASK
		dog_count = get_watchdog_current_count();
		printf("watch dog count is %u\n", dog_count);
		while_time = OSTimeGet();
		printf("delta time is %u ms\n", while_time-while_time1);
		while_time1 = while_time;
		printf("time is %u ms\n", while_time-while_time2);
#endif
		reset_watchdog();
		
		new_id = NeedSwitchTask(id);
		if (new_id){
			// switch to a different task
#ifdef DEBUG_TASK
			if (id > 0)
				LOGD(TAG,"task %d(p%d):%s run %d times, total %d ms, return %d", id, tasks[id].priority, task_name[id], task_run_count, OSTimeGet() - task_start_time, task_ret);
			else{
				LOGD(TAG,"idle for %d ms", OSTimeGet() - task_start_time);
			}
			LOGD(TAG,"task %d(p%d):%s start", new_id, tasks[new_id].priority, task_name[new_id]);
			task_start_time = OSTimeGet();
			task_run_count = 1;
#endif
			id = new_id; 
		}
		else{
			if ((PendingTaskFlag&(1<<id))==0){
				// from other task to idle
#ifdef DEBUG_TASK
				LOGD_NO_WAKEUP(TAG,"task %d(p%d):%s, run %d times, total %d ms", id, tasks[id].priority, task_name[id], task_run_count, OSTimeGet() - task_start_time);
				task_start_time = OSTimeGet(); 
				task_run_count = 1;
#endif
				id = 0;
			}
#ifdef DEBUG_TASK
			else{
				// continue same task
				task_run_count++; 
			}
#endif
		}
		task_ret = RunTask(id);
		if (task_ret == 0){
			SuspendTask(id);
		}
	}
}