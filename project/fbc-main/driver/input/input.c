
#include <register.h>
#include <inputdata.h>
#include <interrupt.h>
#include <key_const.h>
#include <customer_key_conf.h>
#include <malloc.h>
#include <task.h>
#include <string.h>
#include <timer.h>
#include <log.h>
#include <input.h>
#include <task_priority.h>


static LIST_HEAD(input_data_list);
static int input_task_id=0;

static char TAG[]= "input" ;

static int timer_id = -2;

input_call_task_t input_call_tasks[INPUT_CALL_TASK_MAX];

unsigned int AddIputdataToTaskList(unsigned int cmd_owner, int data) {
	  unsigned int ret=0;
		INPUT_LIST *input_list = (INPUT_LIST *)malloc(sizeof(INPUT_LIST));
		if(input_list) {
				input_list->input_data.cmd_owner = cmd_owner;
				input_list->input_data.data = data;
				for (int id=0; id<INPUT_CALL_TASK_MAX; id++){
						if((input_call_tasks[id].cmd_list==NULL)||(input_call_tasks[id].input_mask==0)||(input_call_tasks[id].task_id==0)) {
								continue;
		    		}
		    		if((input_call_tasks[id].input_mask&input_list->input_data.cmd_owner)&&(input_call_tasks[id].func != NULL)
		    				&&(input_call_tasks[id].func(data))) {
		    				DisableAllInterrupt();
								list_add_tail(&input_list->list , input_call_tasks[id].cmd_list);
								EnableAllInterrupt();
		    				WakeupTaskByID(input_call_tasks[id].task_id);
		    				ret=1;
		    				continue;
		    		}
		    		if((input_call_tasks[id].input_mask&input_list->input_data.cmd_owner)&&(input_call_tasks[id].func == NULL)) {
		    				DisableAllInterrupt();
								list_add_tail(&input_list->list , input_call_tasks[id].cmd_list);
								EnableAllInterrupt();
		    				WakeupTaskByID(input_call_tasks[id].task_id);
		    				ret=1;
		    				continue;
		    		}
    		}
    		if(ret==0) {
    				free(input_list);
    		}
		}
		return ret;
}

unsigned int RegisterInput(list_t * cmd_list, unsigned int task_id, unsigned int input_mask, is_input_supported_func func){
		for (int id=0; id<INPUT_CALL_TASK_MAX; id++){
				if (NULL == cmd_list){
						LOGI(TAG,"no input cmd_list , cannot register.\n");
					  return -1;
				}
				if (0 == task_id){
						LOGI(TAG,"no input call task id , cannot register.\n");
					  return -1;
				}
				if (0 == input_mask){
						LOGI(TAG,"no input_mask , cannot register.\n");
					  return -1;
				}
				if(input_call_tasks[id].task_id==0) {
						input_call_tasks[id].cmd_list= cmd_list;
						input_call_tasks[id].task_id = task_id;
						input_call_tasks[id].input_mask = input_mask;
						input_call_tasks[id].func = func;
						return id;
				}
   }
   return -1;
}


unsigned int UnregisterInput(unsigned int task_id){

		for (int id=0; id<INPUT_CALL_TASK_MAX; id++){
				if(input_call_tasks[id].task_id == task_id) {
						input_call_tasks[id].task_id= 0;
						input_call_tasks[id].cmd_list= NULL;
						input_call_tasks[id].input_mask = 0;
						input_call_tasks[id].func = NULL;
						return 0;
				}
   }
   return -1;
}

static int InputData_Task_handle(int task_id, void * param) {
		DisableAllInterrupt();
		list_t *plist = list_dequeue(&input_data_list);
		EnableAllInterrupt();
		LOGI(TAG,"run inputData task %d from input 0x%x\n", task_id, plist);
		if (plist) {
		    INPUT_LIST *input_list = list_entry(plist, INPUT_LIST, list);
		    if (input_list){
		    		for(int i=0; i<INPUT_CALL_TASK_MAX; i++) {
		    				if((input_call_tasks[i].input_mask==0)||(input_call_tasks[i].task_id==0)) {
		    						break;
		    		    }
		    				if(input_call_tasks[i].input_mask&input_list->input_data.cmd_owner) {
		    						WakeupTaskByID(input_call_tasks[i].task_id);
		    				}
  			    }
  			    free(input_list);
		   }
		}
		return 0;
}

int InputTaskInit(void) {
	int task_id=-1;
	task_id=input_task_id=RegisterTask(InputData_Task_handle, NULL, 0 , TASK_PRIORITY_INPUT);
	return task_id;
}

int Request100MSTimerToCallInputTask(void) {
	timer_id=request_timer(input_task_id, 10);//100ms interrupt
    return timer_id;
}

key_process_func KeyProcessFunc= NULL;
int registKeyProcess(key_process_func  func)	{
	  int ret= 1;
		KeyProcessFunc=func;
		return ret;
}
	  




