
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
#include <cmd.h>
#include <listop.h>
#include <command.h>
#include <stdlib.h>


//static LIST_HEAD(input_data_list);
//static int input_task_id=0;

//#define CMD_DEBUG

static char TAG[]= "cmd" ;

typedef struct{
	unsigned int cmd_owner;
	int (* sendData)(unsigned char *s, unsigned short len);
}channel_send_t;

#define MAX_CHANNEL		8
static channel_send_t send_channels[MAX_CHANNEL] = {0}; /*= {
	{INPUT_CEC,				NULL},
	{INPUT_UART_CONSOLE, 	NULL},
	{INPUT_UART_HOST, 		NULL},
};*/


int RegisterChannel(unsigned int cmd_owner, channel_send_data func){

	int i;
	if(NULL == func){
		return -1;
	}

	for(i=0;i<MAX_CHANNEL;i++){
		if(cmd_owner == send_channels[i].cmd_owner)
		{
			return -2;//already registered.
		}
	}

	for(i=0;i<MAX_CHANNEL;i++){
		if(0 == send_channels[i].cmd_owner)
		{
			send_channels[i].cmd_owner = cmd_owner;
			send_channels[i].sendData = func;
			return 0;
		}
	}

	return -1;
}



//unsigned char * PackCmd(int id, int * params);
//unsigned char * PackReturn(int id, int * params);
//int CmdChannelSend(unsigned int cmd_owner, unsigned char * s);
typedef struct {
	list_t *     cmd_list;
	unsigned int task_id;
	unsigned int input_mask;
	int (*func)(int cmd);
	unsigned int (*run_command)(unsigned char * s, int * returns);
}cmd_call_task_t;

cmd_call_task_t cmd_call_tasks[CMD_CALL_TASK_MAX];

static LIST_HEAD(cmd_results);
unsigned char pending_cmd[MAX_CMD]; // 0 ¨C no pending, 1~0x7f task_id - pending, 0x80|task_id ¨C got return

static unsigned char * PackCmd(int id, int * params){
	unsigned char * retVal = NULL;
	int charCount = 1;//cmd is 1 byte
	int charIndex = 1;//cmd is 1 byte
	int i;
	int type;


	for(i=0; i<cmd_def[id].num_param; i++){
		type = (cmd_def[id].type >> (i*2)) & 0x03;
		charCount += type<3 ? type:4;
	}

	retVal = (unsigned char *)malloc(charCount);
	retVal[0] = (unsigned char)id;
	for(i=0;i<cmd_def[id].num_param;i++){
		type = (cmd_def[id].type >> (i*2)) & 0x03;
		switch(type){
			case 1:
				retVal[charIndex] = (unsigned char)params[i];
				charIndex++;
				break;
			case 2:
				retVal[charIndex] = (unsigned char)(params[i] & 0xFF);
				retVal[charIndex+1] = (unsigned char)((params[i] >> 8) & 0xFF);
				charIndex+=2;
				break;
			case 3:
				retVal[charIndex] = (unsigned char)(params[i] & 0xFF);
				retVal[charIndex+1] = (unsigned char)((params[i]  >> 8) & 0xFF);
				retVal[charIndex+2] = (unsigned char)((params[i]  >> 16) & 0xFF);
				retVal[charIndex+3] = (unsigned char)((params[i]  >> 24) & 0xFF);
				charIndex+=4;
				break;
			default:
				break;
		}

	}
#ifdef CMD_DEBUG
	printf("pack cmd\n");
	for(i=0;i<charCount;i++){
		printf("retVal[%d] is 0x%2x.\n", i,retVal[i]);
	}
#endif

	return retVal;
}

static unsigned char * PackReturn(int id, int * params){
	unsigned char * retVal = NULL;
	int charCount = 1;//cmd is 1 byte
	int charIndex = 1;//cmd is 1 byte
	int i;
	int type;
	if(params == NULL)
	{
		return NULL;
	}

	if((cmd_def[id].ret_num > 8)&&(cmd_def[id].ret_len > 33)&&
		(cmd_def[id].ret_len == cmd_def[id].ret_num+1))
	{
		retVal = (unsigned char *)malloc(cmd_def[id].ret_len);
		retVal[0] = (unsigned char)id;
		for(i=0;i<cmd_def[id].ret_num;i++)
		{
			retVal[i+1] = (unsigned char)params[i];
		}
		
	}
	else{
		for(i=0;i<cmd_def[id].ret_num;i++){
			type = (cmd_def[id].retval_type >> (i*2)) & 0x03;
			charCount += type<3 ? type:4;
		}

		retVal = (unsigned char *)malloc(charCount);

		retVal[0] = (unsigned char)id;
		for(i=0;i<cmd_def[id].ret_num;i++){
			type = (cmd_def[id].retval_type >> (i*2)) & 0x03;
			switch(type){
				case 1:
					retVal[charIndex] = (unsigned char)params[i];
					charIndex++;
					break;
				case 2:
					retVal[charIndex] = (unsigned char)(params[i] & 0xFF);
					retVal[charIndex+1] = (unsigned char)((params[i] >> 8) & 0xFF);
					charIndex+=2;
					break;
				case 3:
					retVal[charIndex] = (unsigned char)(params[i] & 0xFF);
					retVal[charIndex+1] = (unsigned char)((params[i]  >> 8) & 0xFF);
					retVal[charIndex+2] = (unsigned char)((params[i]  >> 16) & 0xFF);
					retVal[charIndex+3] = (unsigned char)((params[i]  >> 24) & 0xFF);
					charIndex+=4;
					break;
				default:
					break;
			}
		}
	}
#ifdef CMD_DEBUG
	printf("pack return\n");
	for(i=0;i<charCount;i++){
		printf("retVal[%d] is 0x%2x.\n", i,retVal[i]);
	}
#endif
	//free(params);
	return retVal;
}


static int CmdChannelSend(unsigned int cmd_owner, unsigned char * s, unsigned short len){
	int ret = -2;
	int i;
#ifdef CMD_DEBUG
	printf("send length is %d bytes.\n", len);
	for(i=0;i<len;i++)
	{
		printf("0x%02x ", s[i]);
	}
	printf("\n");
#endif
	for(i=0; i<MAX_CHANNEL; i++){
		if((send_channels[i].cmd_owner == cmd_owner)&&(send_channels[i].sendData != NULL)){
			ret = send_channels[i].sendData(s, len);
		}
	}
	return ret;
}


unsigned int CmdChannelAddData(unsigned int cmd_owner, unsigned char * data) {
	unsigned int ret=0;
	CMD_LIST *cmd_list = (CMD_LIST *)malloc(sizeof(CMD_LIST));
#ifdef CMD_DEBUG
	printf("CmdChannelAddData cmd_owner is %u, cmd is %d.\n",cmd_owner, CmdID(data));
#endif
	if(cmd_list) {
		cmd_list->cmd_data.cmd_owner = cmd_owner;
		cmd_list->cmd_data.data = (void *)data;
		if(pending_cmd[CmdID(data)] != 0){
			//send return value to result list.
			//DisableAllInterrupt();
			list_add_tail(&cmd_list->list, &cmd_results);
			pending_cmd[CmdID(data)] |= 0x80;
			//EnableAllInterrupt();
			WakeupTaskByID(pending_cmd[CmdID(data)]&0x7F);
			ret = 1;
		}else{
			for (int id=0; id<CMD_CALL_TASK_MAX; id++){
				if((cmd_call_tasks[id].cmd_list==NULL)||(cmd_call_tasks[id].input_mask==0)||(cmd_call_tasks[id].task_id==0)) {
					continue;
	    		}
	    		if((cmd_call_tasks[id].input_mask&cmd_list->cmd_data.cmd_owner)&&(cmd_call_tasks[id].func != NULL)
	    				&&(cmd_call_tasks[id].func(CmdID(data)))) {
    				//DisableAllInterrupt();
					list_add_tail(&cmd_list->list , cmd_call_tasks[id].cmd_list);
					//EnableAllInterrupt();
    				WakeupTaskByID(cmd_call_tasks[id].task_id);
    				ret=1;
    				continue;
	    		}
			}
		}
		if(ret==0) {
			freeCmdList(cmd_list);
		}
	}
	return ret;
}

unsigned int run_command_local(unsigned char * data, int * returns){
	unsigned int ret = 0;
#ifdef CMD_DEBUG
	printf("run_command_local cmd is %d.\n", CmdID(data));
#endif
	for (int id=0; id<CMD_CALL_TASK_MAX; id++){
		if((cmd_call_tasks[id].input_mask==0)||(cmd_call_tasks[id].task_id==0)) {
			continue;
		}
		if((cmd_call_tasks[id].func != NULL)&&(cmd_call_tasks[id].func(CmdID(data)))&&(cmd_call_tasks[id].run_command != NULL)){
			return cmd_call_tasks[id].run_command(data, returns);
		}
	}
	return ret;
}

unsigned int RegisterCmd(list_t * cmd_list, unsigned int task_id, unsigned int input_mask, is_cmd_supported func, cmd_process_func run_command){
	for (int id=0; id<CMD_CALL_TASK_MAX; id++){
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
		if (CMD_CALL_TASK_MAX == id){
			LOGI(TAG,"tasks is full, cannot register.\n");
			return -1;
		}
		if(cmd_call_tasks[id].task_id==0) {
			cmd_call_tasks[id].cmd_list=cmd_list;
			cmd_call_tasks[id].task_id = task_id;
			cmd_call_tasks[id].input_mask = input_mask;
			cmd_call_tasks[id].func = func;
			cmd_call_tasks[id].run_command = run_command;
			return id;
		}
	}
	return -1;
}


unsigned int UnregisterCmd(unsigned int task_id){

	for (int id=0; id<CMD_CALL_TASK_MAX; id++){
		if(cmd_call_tasks[id].task_id == task_id) {
			cmd_call_tasks[id].task_id=0;
			cmd_call_tasks[id].cmd_list=NULL;
			cmd_call_tasks[id].input_mask = 0;
			return 0;
		}
   	}
   	return -1;
}

int SendCmd(int task_id, unsigned int cmd_owner, int cmd, int* params){
	int ret;
	if(cmd_def[cmd].ret_num > 0){
		pending_cmd[cmd] = task_id;
	}
	unsigned char * s = PackCmd(cmd, params);
	ret = CmdChannelSend(cmd_owner, s, LEN(s));
	free(s);
	return ret;
}

int SendReturn(int task_id, unsigned int cmd_owner, int cmd, int* params){
	int ret;
	unsigned char * s = PackReturn(cmd, params);
	ret = CmdChannelSend(cmd_owner, s, RET_LEN(s));
	free(s);
	return ret;
}

unsigned char * GetReturns(int cmd){
	unsigned char * retVal = NULL;
	list_t * p = &cmd_results;
	CMD_LIST * pList = NULL;
	unsigned char * s = NULL;

	if(pending_cmd[cmd] > 0x80){

		pending_cmd[cmd] = 0;

		while(p->next != &cmd_results){
			p = p->next;
			pList = list_entry(p, CMD_LIST, list);
			s = (unsigned char *)pList->cmd_data.data;
			if(CmdID(s) == cmd){
				retVal = (unsigned char *)malloc(RET_LEN(s));
				memcpy(retVal, s, RET_LEN(s));
				list_del(p);
				free(pList);
				break;
			}
		}
	}
	return retVal;
}

int * GetReturnValues(unsigned char *s){
	int * retVal = NULL;
	int charIndex = 1;
	int i = 0;
	int type;

	if(NULL == s){
		return NULL;
	}

	retVal = (int*)malloc(Ret_NumParam(s)*sizeof(int));

	for(i=0; i<=Ret_NumParam(s); i++){
		type = Ret_Type(s, i);
		switch(type){
			case 1:
				retVal[i] = (int)s[charIndex];
				break;
			case 2://????
				retVal[i] = (int)((s[charIndex+1]<<8)|s[charIndex]);
				break;
			case 3://????
				retVal[i] = (int)((s[charIndex+3]<<24)|(s[charIndex+2]<<16)|(s[charIndex+1]<<8)|s[charIndex]);
				break;
			default:
				break;
		}
		charIndex += type<3 ? type:4;
	}
	return retVal;
}

int GetReturnValue(unsigned char *s, int index){ // get return[index]
	//int types;
	int i;
	int charIndex = 1;
	if(NULL == s){
		return -1;
	}

	if(index >= Ret_NumParam(s)){
		return -1;
	}

	//types = cmd_def[CmdID(s)].type;

	for(i=0; i<index; i++){
		charIndex += Ret_Type(s,i)<3 ? Ret_Type(s, i):4;
	}

	switch(Ret_Type(s, index)){
		case 1:
			return (int)s[charIndex];
		case 2://????
			return (int)((s[charIndex+1]<<8)|s[charIndex]);
		case 3://????
			return (int)((s[charIndex+3]<<24)|(s[charIndex+2]<<16)|(s[charIndex+1]<<8)|s[charIndex]);
		default:
			return 0;
	}
}


int * GetParams(unsigned char *s){
	int * retVal = NULL;
	int charIndex = 1;
	int i = 0;
	int type;

	if(NULL == s){
		return NULL;
	}

	retVal = (int*)malloc(NumParam(s)*sizeof(int));

	for(i=0; i<=NumParam(s); i++){
		type = Type(s, i);
		switch(type){
			case 1:
				retVal[i] = (int)s[charIndex];
				break;
			case 2://????
				retVal[i] = (int)((s[charIndex+1]<<8)|s[charIndex]);
				break;
			case 3://????
				retVal[i] = (int)((s[charIndex+3]<<24)|(s[charIndex+2]<<16)|(s[charIndex+1]<<8)|s[charIndex]);
				break;
			default:
				break;
		}
		charIndex += type<3 ? type:4;
	}

	return retVal;
}

int GetParam(unsigned char *s, int index){ // get param[index]
	//int types;
	int i;
	int charIndex = 1;
	if(NULL == s){
		return -1;
	}

	if(index >= NumParam(s)){
		return -1;
	}

	//types = cmd_def[CmdID(s)].type;

	for(i=0; i<index; i++){
		charIndex += Type(s,i)<3 ? Type(s, i):4;
	}

	switch(Type(s, index)){
		case 1:
			return (int)s[charIndex];
		case 2://????
			return (int)((s[charIndex+1]<<8)|s[charIndex]);
		case 3://????
			return (int)((s[charIndex+3]<<24)|(s[charIndex+2]<<16)|(s[charIndex+1]<<8)|s[charIndex]);
		default:
			return 0;
	}
}





int do_cmd_debug(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int i;
	int * val = (int *)malloc((argc-2)*sizeof(int));
	int cmd = strtoul(argv[1], NULL, 16);
	for(i=2;i<argc;i++){
		val[i-2] = strtoul(argv[i], NULL, 16);
	}

	CmdChannelAddData(INPUT_UART_HOST, PackCmd(cmd, val));//packcmd return char * add to list, no need free

	free(val);

	return -1;
}

int do_scmd_debug(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int i;
	int * val = (int *)malloc((argc-2)*sizeof(int));
	int * rets = NULL;
	int cmd = strtoul(argv[1], NULL, 16);
	for(i=2;i<argc;i++){
		val[i-2] = strtoul(argv[i], NULL, 16);
	}


	unsigned char * s = PackCmd(cmd, val);//packcmd need free
	rets = (int *)malloc(Ret_NumParam(s)*sizeof(int));
	run_command_local(s, rets);


	free(rets);
	free(s);
	free(val);

	return -1;
}

int *RunCommand(int id, int *params)
{
	int *retval = NULL;
	unsigned char *s = PackCmd(id, params);//packcmd need free
	if (s){
		if (Ret_NumParam(s)){
			retval = (int *)malloc(Ret_NumParam(s)*sizeof(int));
			run_command_local(s, retval);
		}
		else{
			run_command_local(s, NULL);
		}
	}
	free(s);
	return retval;
}

void freeCmdList(CMD_LIST * list)
{
	if(list != NULL)
	{
		if(list->cmd_data.data != NULL)
		{
			free(list->cmd_data.data);
		}
		free(list);
	}	
}