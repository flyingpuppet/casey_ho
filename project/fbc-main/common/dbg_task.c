#include <common.h>
#include <log.h>
#include <listop.h>
#include <inputdata.h>
#include <task.h>
#include <input.h>
#include <malloc.h>
#include <command.h>
#include <cmd.h>
#include <spi_flash.h>
#include <task_priority.h>
#include <reboot.h>
#include <user_setting.h>
#include <panel.h>
#include <string.h>
#include <stdlib.h>

static LIST_HEAD(dbg_list);
static int dbg_task_id = -1;
extern char *fbc_get_version_info();
extern char *fbc_get_git_version_info();
extern char *fbc_get_last_chaned_time_info();
extern char *fbc_get_git_branch_info();
extern char *fbc_get_build_time_info();
extern char *fbc_get_build_name_info();

static int check_cmd_is_supported(int cmd)
{
	switch(cmd)
	{
		case FBC_USER_SETTING_DEFAULT:
		case FBC_USER_SETTING_SET:
		case FBC_GET_HDCP_KEY:
		case FBC_REBOOT_UPGRADE:
		case CMD_SET_DEVICE_ID:
		case CMD_DEVICE_ID:
		case CMD_SET_FACTORY_SN:
		case CMD_GET_FACTORY_SN:
		case CMD_CLIENT_TYPE:
		case CMD_DEVICE_NUM:
		case CMD_ACTIVE_KEY:
		case CMD_ACTIVE_STATUS:
		case CMD_DBG_REGISTER_ACCESS:
		case CMD_DBG_MEMORY_ACCESS:
		case CMD_DBG_SPI_ACCESS:
		case CMD_DBG_VPU_MEMORY_ACCESS:
		case CMD_DBG_MEMORY_TRANSFER:
		case CMD_PANEL_INFO:
		case FBC_PANEL_POWER:
		case FBC_SUSPEND_POWER:
		case CMD_FBC_MAIN_CODE_VERSION:
			return 1;
			
		default :
			return 0;
	}
}

extern int load_default_setting();
static unsigned int handle_dbg_cmd(unsigned char *s, int *rets)
{
	int i = 0, tmp_val = 0, tmp_ind = 0;
	char *tmp_ptr = NULL;
	int * params;
	
	if(s == NULL)
	{
		return -1;
	}
	
	switch(*s)
	{
		case FBC_REBOOT_UPGRADE:
			params = GetParams(s);
			reboot((unsigned)params[0]);
			break;
		case FBC_USER_SETTING_DEFAULT:
			load_default_setting();
			break;
		case FBC_USER_SETTING_SET:
			
			break;
		case FBC_GET_HDCP_KEY:
			char * key = read_HDCP_KEY();
			if(key != NULL){
				for(i=0;i<Ret_NumParam(s);i++)
				{
					rets[i] = key[i];
				}
				free(key);
			}			
			break;
		case FBC_PANEL_POWER:
			params = GetParams(s);
			if(0 == params[0])
			{
				//panel_power(read_project_id(), off);
				panel_suspend();
			}
			else if(1 == params[0])
			{
				//panel_power(read_project_id(),on);
				panel_resume();
			}
			break;
		case FBC_SUSPEND_POWER:
			panel_suspend();
			reboot(REBOOT_FLAG_SUSPEND);
			break;
		case CMD_SET_DEVICE_ID:
			char * device = (char *)malloc(33);
			memset(device, 0, 33);
			for(int i=0;i<32;i++)
			{
				device[i] = s[i+1];
			}
			write_device_id(device);
			free(device);
			break;
		case CMD_SET_FACTORY_SN:
			char * pFactorySn = (char *)malloc(18);
			memset(pFactorySn, 0, 18);
			for(int j=0;j<18;j++)
			{
				pFactorySn[j] = s[j+1];
			}
			pFactorySn[17] = '\0';
			
			write_factory_sn(pFactorySn);
			free(pFactorySn);
			break;
		case CMD_GET_FACTORY_SN:
			char * pReadFactorySn;
			pReadFactorySn = read_factory_sn();
			int len = strlen(pReadFactorySn);
			printf("\nget %d sn=%s\n", len,pReadFactorySn);
			if(NULL == rets)
			{
				printf("rets is NULL\n");
				break;
			}
			
            		for(i = 0; i < len; i++)
			{
            			rets[i] = pReadFactorySn[i];
            		}
			printf("ret %s\n",rets);		
            		//rets[len] = 0;
			break;
		case CMD_FBC_MAIN_CODE_VERSION:
			if (rets == NULL) {
				printf("return buffer is null!!!\n");
				break;
			}

			tmp_ind = 0;
			rets[tmp_ind++] = 0x88;
			rets[tmp_ind++] = 0x99;

			tmp_ptr = fbc_get_version_info();
			tmp_val = strlen(tmp_ptr);
			for (i = 0; i < tmp_val; i++) {
				rets[tmp_ind++] = tmp_ptr[i];
			}
			rets[tmp_ind++] = 0;

			tmp_ptr = fbc_get_build_time_info();
			tmp_val = strlen(tmp_ptr);
			for (i = 0; i < tmp_val; i++) {
				rets[tmp_ind++] = tmp_ptr[i];
			}
			rets[tmp_ind++] = 0;

			tmp_ptr = fbc_get_git_version_info();
			tmp_val = strlen(tmp_ptr);
			for (i = 0; i < tmp_val; i++) {
				rets[tmp_ind++] = tmp_ptr[i];
			}
			rets[tmp_ind++] = 0;

			tmp_ptr = fbc_get_git_branch_info();
			tmp_val = strlen(tmp_ptr);
			for (i = 0; i < tmp_val; i++) {
				rets[tmp_ind++] = tmp_ptr[i];
			}
			rets[tmp_ind++] = 0;

			tmp_ptr = fbc_get_build_name_info();
			tmp_val = strlen(tmp_ptr);
			for (i = 0; i < tmp_val; i++) {
				rets[tmp_ind++] = tmp_ptr[i];
			}
			rets[tmp_ind++] = 0;
			break;
		case CMD_DEVICE_ID:
			char * device_id;
			device_id = read_device_id();
			int n = strlen(device_id);
			printf("deviceid=%s\n", device_id);
            for(i = 0; i < n; i++){
            	rets[i] = device_id[i];
            }
            rets[n] = 0;
			break;
			
		case CMD_CLIENT_TYPE:
			break;
			
		case CMD_DEVICE_NUM:
			break;
			
		case CMD_ACTIVE_KEY:
			params = GetParams(s);
			AddIputdataToTaskList(INPUT_REMOTE, params[0]);
			break;
			
		case CMD_ACTIVE_STATUS:
			break;
			
		case CMD_DBG_REGISTER_ACCESS:			
		case CMD_DBG_MEMORY_ACCESS:
			params = GetParams(s);
			if(params != NULL)
			{
				*rets = *(int *)((unsigned)params[0]&(~(0x3)));
				free(params);
			}
			
			break;
			
		case CMD_DBG_SPI_ACCESS:
			params = GetParams(s);
			if(params != NULL)
			{
				printf("parameters are 0x%08x, 0x%08x\n", params[0], params[1]);
				unsigned offset = params[0];
			
				unsigned size = params[1];
				
				if(size <= 0) size = 1;
				if(size > 8) size = 8;
				
				printf("rets address is 0x%08x\n", rets);
				spi_flash_read(get_spi_flash_device(0), offset, size * 4, (unsigned *)((unsigned)rets));
				printf("read spi flash ok!\n");
			}
			
			break;
			
		case CMD_DBG_VPU_MEMORY_ACCESS:
			break;
			
		case CMD_DBG_MEMORY_TRANSFER:
			break;
		case CMD_PANEL_INFO:
			params = GetParams(s);
			if(params != NULL){
				rets[0] = params[0];
				switch(params[0])
				{
					case 0://panel reverse
						rets[1] = panel_param->reverse;
						break;
					case 1://panel output_mode
						rets[1] = panel_param->output_mode;
						break;
					case 2://panel byte num
						rets[1] = panel_param->byte_num;
					default:
						break;
				}
			}
			break;
			
		default :
			break;
	}
	
	return 0;
}

static int ConsoleHandler(int task_id, void *param)
{
	list_t *plist = list_dequeue(&dbg_list);
	if(plist != NULL)
	{
		CMD_LIST *clist = list_entry(plist, CMD_LIST, list);
		if(clist != NULL)
		{
			unsigned char *cmd = (unsigned char *)(clist->cmd_data.data);
			if(cmd != NULL)
			{
				int rcmd_len = Ret_NumParam(cmd);
				if(rcmd_len > 0)
				{
					int *params = (int *)malloc(rcmd_len*sizeof(int));
					handle_dbg_cmd(cmd, params);
					SendReturn(dbg_task_id, clist->cmd_data.cmd_owner, *cmd, (int *)params);
					free(params);
					params = NULL;
				}
				else
				{
					handle_dbg_cmd(cmd, NULL);
				}
			}
			freeCmdList(clist);
		}
	}
	
	return 0;
}

void dbg_task_init()
{
	dbg_task_id = RegisterTask(ConsoleHandler, NULL, 0, TASK_PRIORITY_DBG);	
	RegisterCmd(&dbg_list, dbg_task_id, INPUT_CEC | INPUT_UART_HOST | INPUT_UART_CONSOLE, check_cmd_is_supported, handle_dbg_cmd);
	return;
}

