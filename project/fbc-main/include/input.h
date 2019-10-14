#ifdef INPUT_H
#else
#define INPUT_H

#include <listop.h>

typedef int (* is_input_supported_func)(int key_value);
unsigned int AddIputdataToTaskList(unsigned int cmd_owner, int data);
int InputTaskInit(void);
int Request100MSTimerToCallInputTask(void);
unsigned int RegisterInput(list_t * cmd_list, unsigned int task_id, unsigned int input_mask, is_input_supported_func func);
unsigned int UnregisterInput(unsigned int task_id);


typedef int (*key_process_func)(unsigned int input_type,unsigned int customer_code,unsigned int key_value,unsigned int key_action);
int registKeyProcess(key_process_func func);
extern key_process_func KeyProcessFunc;



#endif //INPUT_H

