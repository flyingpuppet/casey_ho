#include <stdlib.h>
#include <register.h>
#include <input.h>
#include <inputdata.h>
#include <interrupt.h>
#include <customer_key_conf.h>
#include <timer.h>
#include <cmd.h>
#include <task.h>
#include <task_priority.h>
#include <c_arc_pointer_reg.h>

#ifdef IN_FBC_MAIN_CONFIG
static int RepeatNum = 0;
static INPUTDATA RemoteIrData;
static long fisrs_repeat_time = 0;
static int remote_cur_key_code = 0;
static int remote_last_key_code = 0;
static int remote_count_task_id = -1;
static int remote_count_timer_id = -1;
#endif

#define KEYDOMIAN 1 // find key val vail data domain
#define CUSTOMDOMAIN 0 // find key val vail custom domain
static int remote_type=0;

/*******************************************************/
typedef struct reg_s {
		int reg;
		unsigned int val;
} remotereg_t;

static int remote_task_id = -1;
static int remote_key_value = -1;

/*remote config val*/
/****************************************************************/
#define CONFIG_END 0xff

#ifdef IN_FBC_MAIN_CONFIG
static const remotereg_t RDECODEMODE_NEC[] = {
		{AO_MF_IR_DEC_LDR_ACTIVE,((unsigned)477<<16) | ((unsigned)400<<0)},// NEC leader 9500us,max 477: (477* timebase = 20) = 9540 ;min 400 = 8000us
		{AO_MF_IR_DEC_LDR_IDLE, 248<<16 | 202<<0},// leader idle
		{AO_MF_IR_DEC_LDR_REPEAT,130<<16|110<<0}, // leader repeat
		{AO_MF_IR_DEC_BIT_0,60<<16|48<<0 },// logic '0' or '00'      
		{AO_MF_IR_DEC_REG0,3<<28|(0xFA0<<12)|0x13},  // sys clock boby time.base time = 20 body frame 108ms         
		{AO_MF_IR_DEC_STATUS,(111<<20)|(100<<10)}, // logic '1' or '01'      
		{AO_MF_IR_DEC_REG1,0x9f40},// boby long decode (8-13)
		{AO_MF_IR_DEC_REG2,0x0}, // hard decode mode
		{AO_MF_IR_DEC_DURATN2,0},
		{AO_MF_IR_DEC_DURATN3,0},  
		{CONFIG_END,            0      }
};

/****************************************************************/
static const remotereg_t RDECODEMODE_RCA[] = {
		{AO_MF_IR_DEC_LDR_ACTIVE,225<<16 | 175<<0},// THOMSON leader 8000us,
		{AO_MF_IR_DEC_LDR_IDLE, 225<<16 | 175<<0},// leader idle
		{AO_MF_IR_DEC_LDR_REPEAT,80<<16|70<<0}, // leader repeat
		{AO_MF_IR_DEC_BIT_0,80<<16|60<<0 },// logic '0' or '00'      
		{AO_MF_IR_DEC_REG0,3<<28|(0xFA0<<12)|0x13},         
		{AO_MF_IR_DEC_STATUS,140<<20|120<<10},// logic '1' or '01'      
		{AO_MF_IR_DEC_REG1,0x9740},// boby long decode (8-13)
		{AO_MF_IR_DEC_REG2,0x104}, // hard decode mode
		{AO_MF_IR_DEC_DURATN2,0},
		{AO_MF_IR_DEC_DURATN3,0},  
		{CONFIG_END,            0      }
};

/**********************************************************/
static const remotereg_t RDECODEMODE_TOSHIBA[] = {
	{AO_MF_IR_DEC_LDR_ACTIVE,250<<16 | 200<<0},//TOSHIBA leader 9000us
	{AO_MF_IR_DEC_LDR_IDLE, 250<<16 | 200<<0},// leader idle
	{AO_MF_IR_DEC_LDR_REPEAT,525<<16|425<<0}, // leader repeat
	{AO_MF_IR_DEC_BIT_0,60<<16|40<<0 },// logic '0' or '00'      
	{AO_MF_IR_DEC_REG0,3<<28|(0xFA0<<12)|0x13},         
	{AO_MF_IR_DEC_STATUS,111<<20|100<<10},// logic '1' or '01'      
	{AO_MF_IR_DEC_REG1,0x9f40},// boby long decode (8-13)
	{AO_MF_IR_DEC_REG2,0x105}, // hard decode mode
	{AO_MF_IR_DEC_DURATN2,0},
	{AO_MF_IR_DEC_DURATN3,0},
	{CONFIG_END,            0      }

};

#else 

static const remotereg_t RDECODEMODE_NEC[] = {
	{AO_MF_IR_DEC_LDR_ACTIVE, ((unsigned)(294*1.1) << 16) | ((unsigned)(294*0.9) << 0)},// NEC leader 9500us,max 477: (477* timebase = 20) = 9540 ;min 400 = 8000us
	{AO_MF_IR_DEC_LDR_IDLE, ((unsigned)(147*1.1) << 16) | ((unsigned)(147*0.9) << 16)},// leader idle
	{AO_MF_IR_DEC_LDR_REPEAT, (0x4f << 16) | (0x42 << 0)}, // leader repeat
	{AO_MF_IR_DEC_BIT_0, ((unsigned)(36*1.1) << 16) | ((unsigned)(36*0.9) << 0)},// logic '0' or '00'      
	{AO_MF_IR_DEC_REG0, (0<<28) | (0xa3f << 12) | 0x0},  // sys clock boby time.base time = 20 body frame 108ms   
	{AO_MF_IR_DEC_REG1, 0x600fdf00},// boby long decode (8-13)
	{CONFIG_END,            0      }
};

/****************************************************************/
static const remotereg_t RDECODEMODE_RCA[] = {  
		{AO_MF_IR_DEC_LDR_ACTIVE, 147 << 16 | 114 << 0},// THOMSON leader 8000us,
		{AO_MF_IR_DEC_LDR_IDLE, 147 << 16 | 114 << 0},// leader idle
		{AO_MF_IR_DEC_LDR_REPEAT, 52 << 16 | 45 << 0}, // leader repeat
		{AO_MF_IR_DEC_BIT_0, 53 << 16 | 39 << 0 },// logic '0' or '00'      
		{AO_MF_IR_DEC_REG0, 0 << 28 | (0xA3E << 12) | 0x0},         
		{AO_MF_IR_DEC_STATUS, 92 << 20 | 78 << 10},// logic '1' or '01'      
		{AO_MF_IR_DEC_REG1, 0x600fd700},// boby long decode (8-13)
		{AO_MF_IR_DEC_REG2, 0x104}, // hard decode mode
 		{CONFIG_END,            0      }
 };

/**********************************************************/
/*static const remotereg_t RDECODEMODE_TOSHIBA[] = {
	{AO_MF_IR_DEC_LDR_ACTIVE,164<<16 | 131<<0},//TOSHIBA leader 9000us
	{AO_MF_IR_DEC_LDR_IDLE, 164<<16 | 131<<0},// leader idle
	{AO_MF_IR_DEC_LDR_REPEAT,344<<16|278<<0}, // leader repeat
	{AO_MF_IR_DEC_BIT_0,39<<16|26<<0 },// logic '0' or '00' 
	{AO_MF_IR_DEC_REG0,0<<28|(0xa3f<<12)|0x0},
	{AO_MF_IR_DEC_STATUS,72<<20|65<<10},// logic '1' or '01' 
	{AO_MF_IR_DEC_REG1,0x600fdf00},// boby long decode (8-13)
	{AO_MF_IR_DEC_REG2,0x105}, // hard decode mode
	{CONFIG_END,            0      }

};*/

static const remotereg_t RDECODEMODE_TOSHIBA[] = {
	{AO_MF_IR_DEC_LDR_ACTIVE,250<<16 | 200<<0},//TOSHIBA leader 9000us
	{AO_MF_IR_DEC_LDR_IDLE, 250<<16 | 200<<0},// leader idle
	{AO_MF_IR_DEC_LDR_REPEAT,525<<16|425<<0}, // leader repeat
	{AO_MF_IR_DEC_BIT_0,60<<16|40<<0 },// logic '0' or '00'      
	{AO_MF_IR_DEC_REG0,3<<28|(0xFA0<<12)|0x13},         
	{AO_MF_IR_DEC_STATUS,111<<20|100<<10},// logic '1' or '01'      
	{AO_MF_IR_DEC_REG1,0x9f40},// boby long decode (8-13)
	{AO_MF_IR_DEC_REG2,0x105}, // hard decode mode
	{AO_MF_IR_DEC_DURATN2,0},
	{AO_MF_IR_DEC_DURATN3,0},
	{CONFIG_END,            0      }

};



#endif


static const remotereg_t *remoteregsTab[] = {
		RDECODEMODE_NEC,
		RDECODEMODE_RCA,
		RDECODEMODE_TOSHIBA,
};

/******************************************************************************/

unsigned int NEC_DOMAIN(int frame, int domain){
		if(domain) {
				return ((frame >>16) &0xff);
		}
		else { 
				return (frame &0xffff);
		}
}

unsigned int RCA_DOMAIN(int frame, int domain){
		if(domain) {
				return (frame &0xff);//D7 ~ D0
		}
		else { 
				return ((frame>>8) &0xf);
		}
}

unsigned int TOSHIBA_DOMAIN(int frame, int domain){
	if(domain)
		return ((frame >>8) &0xff);
	else
		return ((frame>>16) &0xffff);
}

static unsigned int (*get_cur_key_domian[])(int frame, int domain)={
		NEC_DOMAIN,
		RCA_DOMAIN,
		TOSHIBA_DOMAIN,
};

static int Remote_DATA_pro(int frame, INPUTDATA * data) {
		int irval=AMLKEY_NOP, i=0, ir_value=0, ir_customer=0;
		
		if (KEY_DOWN == data->input_type || KEY_UP == data->input_type) {
				ir_customer = get_cur_key_domian[remote_type](frame, CUSTOMDOMAIN);
				ir_value = get_cur_key_domian[remote_type](frame, KEYDOMIAN);
				//printf("ir_customer =%d, ir_value=%d, input_type=%d\n", ir_customer,ir_value,data->input_type);
				if(KeyProcessFunc)	{
						KeyProcessFunc(INPUT_REMOTE, ir_customer,  ir_value, data->input_type);
				}

				if (ir_customer == remote_coustomer_code) {
						char customer_match=1;
						for(i=0;i<CUSTOMER_REMOTE_NUMS;i++) {
								if(ir_value==customer_key_map[i][0]) {
									irval=customer_key_map[i][1];
									break;
								}
						}
				}
		}
		return irval;
}

#ifdef IN_FBC_MAIN_CONFIG 
int remote_count_task_handle(int task_id, void * param)
{
	//release timer 
	if(remote_count_timer_id >= 0)
	{
		release_timer(remote_count_timer_id);
		remote_count_timer_id = -1;
	}

	RemoteIrData.input_flag = 0;
	RemoteIrData.input_data = remote_last_key_code;
	if(KEY_DOWN == RemoteIrData.input_type)
	{
	    RemoteIrData.input_type = KEY_UP;
	    remote_key_value = Remote_DATA_pro(RemoteIrData.input_data, &RemoteIrData);
        RemoteIrData.input_type = INPUT_VALID;
	}
	remote_last_key_code = 0;
	remote_cur_key_code = 0;
	return 0;
}

static void Remote_IRQ_Handle(void *arg)	{
    int frame_status, frame_LSB;
    unsigned long delta = 0;
    frame_status = Rd(AO_MF_IR_DEC_STATUS);
	frame_LSB = Rd(AO_MF_IR_DEC_FRAME);

	if(DECODEMODE_NEC == remote_type || DECODEMODE_TOSHIBA== remote_type)
	{
		// if it's repeate key
		if (frame_status & 1)
		{
			RepeatNum += 1;
			if(RepeatNum == 1)
			{
				fisrs_repeat_time = OSTimeGet();
				delta = fisrs_repeat_time;
			}

		    delta = OSTimeGet() - fisrs_repeat_time;
	    }
	    else
		{
			RepeatNum = 0;
		}

		if(!RepeatNum || (RepeatNum && delta >= 200))
		{
			if (RepeatNum)
			{
				RemoteIrData.input_flag = 1 ;
		        RemoteIrData.input_data = remote_last_key_code ;
			}
			else
			{
				RemoteIrData.input_flag = 0 ;
				RemoteIrData.input_data = remote_last_key_code = frame_LSB;
			}

		    RemoteIrData.input_type = KEY_DOWN ;
			remote_key_value = Remote_DATA_pro(RemoteIrData.input_data, &RemoteIrData);
		
			if(RepeatNum)
				RepeatNum = 0;

			WakeupTaskByID(remote_task_id);
		}
	}
	else  //if(DECODEMODE_RCA == remote_type)
	{	
		if(remote_count_timer_id >= 0)
		{
			release_timer(remote_count_timer_id);
			remote_count_timer_id = -1;
		}
		
		RemoteIrData.input_flag = 0;
		remote_cur_key_code = frame_LSB;
		if(remote_last_key_code != 0 && remote_last_key_code != remote_cur_key_code)
		{
		    RemoteIrData.input_type = KEY_UP;
			RemoteIrData.input_data = remote_last_key_code;
			remote_key_value = Remote_DATA_pro(RemoteIrData.input_data, &RemoteIrData);
			RemoteIrData.input_type = INPUT_VALID;
			remote_last_key_code = 0;
		}
		RemoteIrData.input_data = remote_cur_key_code;
		if(INPUT_VALID == RemoteIrData.input_type)
		{
		    RemoteIrData.input_type = KEY_DOWN ;
		    remote_last_key_code = remote_cur_key_code;
		    remote_key_value = Remote_DATA_pro(RemoteIrData.input_data, &RemoteIrData);
		    WakeupTaskByID(remote_task_id);
		}

		if(remote_count_task_id < 0)
		{
			remote_count_task_id = RegisterTask(remote_count_task_handle, NULL, 0, TASK_PRIORITY_REMOTE_RCA);
		}
		
		if(remote_count_timer_id < 0 && remote_count_task_id > 0)
		{
			remote_count_timer_id = request_timer(remote_count_task_id,7);
		}
	}
	return;
}

#endif

int set_remote_mode(int mode){
		const remotereg_t *reg;
		reg = remoteregsTab[mode];
		while(CONFIG_END != reg->reg) {
				Wr(reg->reg, reg->val);
				reg++;
		}
		remote_type= mode;
		return 0;

}


static int Remote_Task_Handle(int task_id, void *param)
{
	//printf("Enter Remote task process, param add is %d!\n", remote_key_value);
	if(send_remote_to_soc == 1)
	{
		SendCmd(task_id,INPUT_UART_HOST,CMD_ACTIVE_KEY,&remote_key_value);
	}
	if(send_remote_to_local_task == 1)
	{
		AddIputdataToTaskList(INPUT_REMOTE, remote_key_value);
	}
	return 0;
}

#ifdef IN_FBC_MAIN_CONFIG 
int remote_init(void){
    	int i=-2; 
		//set_remote_mode(REMOTE_TYPE);
    	i=RegisterInterrupt(INT_IR_DEC, INT_TYPE_IRQ, (interrupt_handler_t)Remote_IRQ_Handle);
    	if(i==0){
			Wr_reg_bits(PERIPHS_PIN_MUX_0, 1, 0, 1);
    		SetInterruptEnable(INT_IR_DEC, 1);
    	}
		remote_task_id= RegisterTask(Remote_Task_Handle,NULL,0,TASK_PRIORITY_REMOTE);
		RemoteIrData.input_type = INPUT_VALID;
    	return i;
}

#else

int resume_remote(int mode)
{
	int i;
	
	Wr_reg_bits(AO_MF_IR_DEC_REG0, 1, 0, 1);
	for(i=0; i<100; i++);
	Wr_reg_bits(AO_MF_IR_DEC_REG0, 0, 0, 1);
	
	set_remote_mode(mode);
	Wr_reg_bits(PERIPHS_PIN_MUX_0, 1, 0, 1);	//set pinmux.
	
	return 0;
}

unsigned query_key_value()
{
	unsigned value = 0;
	if(DECODEMODE_NEC == remote_type)
	{
		value = (Rd(AO_MF_IR_DEC_FRAME) >> 16) & 0xff;
	}
	else if(DECODEMODE_RCA == remote_type)
	{
		value = (Rd(AO_MF_IR_DEC_FRAME)) & 0xff;
	}
	else //DECODEMODE_TOSHIBA == remote_type
	{
	    value = (Rd(AO_MF_IR_DEC_FRAME) >> 8) & 0xff;
	}
	return value;
}

#define writel(data, addr)	*(volatile unsigned long *)(addr)=(data)
#define readl(addr)			*(volatile unsigned long *)(addr)

#if 0
int ir_remote_init_32k_mode(void)
{
    unsigned int control_value,status,data_value;

    Wr_reg_bits(PERIPHS_PIN_MUX_0, 1, 0, 1);	//set pinmux.

	control_value = 0x600fdf00;
	
    writel( control_value,P_AO_MF_IR_DEC_REG1 );
    
    control_value = (0xa3f << 12) | 0;

    writel(control_value,P_AO_MF_IR_DEC_REG0);
	
	// no filter
    writel((readl(P_AO_MF_IR_DEC_REG0)& ~(0x7 << 28)) | (0 << 28),P_AO_MF_IR_DEC_REG0);
    
    // SCALE LEADER ACTIVE
    writel((readl(P_AO_MF_IR_DEC_LDR_ACTIVE)& ~(0x3FF << 16)) | ((unsigned)(294*1.1) << 16),P_AO_MF_IR_DEC_LDR_ACTIVE);
    writel((readl(P_AO_MF_IR_DEC_LDR_ACTIVE)& ~(0x3FF << 0)) | ((unsigned)(294*0.9) << 0),P_AO_MF_IR_DEC_LDR_ACTIVE);

    // SCALE LEADER IDLE
    writel((readl(P_AO_MF_IR_DEC_LDR_IDLE)& ~(0x3FF << 16)) | ((unsigned)(147*1.1) << 16),P_AO_MF_IR_DEC_LDR_IDLE);
    writel((readl(P_AO_MF_IR_DEC_LDR_IDLE)& ~(0x3FF << 0)) | ((unsigned)(147*0.9) << 16),P_AO_MF_IR_DEC_LDR_IDLE);
	
	writel((readl(P_AO_MF_IR_DEC_LDR_REPEAT)& ~(0x3FF << 16)) | (0x4f << 16),P_AO_MF_IR_DEC_LDR_REPEAT);
    writel((readl(P_AO_MF_IR_DEC_LDR_REPEAT)& ~(0x3FF << 0))  | (0x42 << 0),P_AO_MF_IR_DEC_LDR_REPEAT);
	
    // SCALE BIT 0 (1.11mS)
    writel((readl(P_AO_MF_IR_DEC_BIT_0)& ~(0x3FF << 16)) | ((unsigned)(36*1.1) << 16),P_AO_MF_IR_DEC_BIT_0);
    writel((readl(P_AO_MF_IR_DEC_BIT_0)& ~(0x3FF << 0))  | ((unsigned)(36*0.9) << 0),P_AO_MF_IR_DEC_BIT_0);


    status = readl(P_AO_MF_IR_DEC_STATUS);
    data_value = readl(P_AO_MF_IR_DEC_FRAME);

    //step 2 : request nec_remote irq  & enable it
    return 0;
}
#endif 

#endif
