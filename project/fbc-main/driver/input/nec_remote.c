
#include <register.h>
#include <input.h>
#include <inputdata.h>
#include <interrupt.h>
#include <customer_key_conf.h>
#include <timer.h>

static int RepeatNum;
static unsigned long curtime = 0 ;
static INPUTDATA NecIrData;
static int NecBakData = 0 ;

static int NEC_DATA_pro(INPUTDATA * data) {
		int irval=AMLKEY_NOP,i=0;
		
		if (data->input_type == KEY_DOWN) {
				int ir_value = data->input_data;
				if ((ir_value & 0xffff) == remote_coustomer_code) {
						char customer_match=1;
						for(i=0;i<sizeof(customer_key_map);i++) {
								if(ir_value==customer_key_map[i][0]) {
									irval=customer_key_map[i][1];
								}
						}
				}
		}
		return irval;
}
								
									  		 	
static void NEC_IRQ_Handle(void *arg)	{
    int frame_status, frame_data, temp;
    unsigned long time = 0;

    frame_status = Rd(AO_IR_DEC_STATUS);
    if( frame_status & 0x8) {// if Frame Data Valid, bit3
        frame_data = Rd(AO_IR_DEC_FRAME);
        temp = Rd(AO_IR_DEC_FRAME);
        time = OSTimeGet() ;
        if (frame_status & 1) // if it's repeate key
            RepeatNum=1;
        else 
            RepeatNum = 0;
        if((time - curtime) < 200) {
            return ;
        }
    
        NecIrData.input_flag = INPUT_VALID ;
        NecIrData.input_type = KEY_DOWN ;
        if (RepeatNum){
            NecIrData.input_flag |= INPUT_REPEAT_FLAG ;
        	NecIrData.input_data = NecBakData ;
	    }
        else{
        	NecIrData.input_flag &= (~INPUT_REPEAT_FLAG) ;
    	    NecIrData.input_data = NecBakData = frame_data ;
	    }
	    AddIputdataToList(OWNER_IS_REMOTE, (char *)OSD_DO_CMD, (void *)NEC_DATA_pro(&NecIrData));
      curtime = time ;
    } 
}
      
int nec_remote_init(void){
    	int i=-2; 
    	i=RegisterInterrupt(INT_IR_DEC, INT_TYPE_IRQ, (interrupt_handler_t)NEC_IRQ_Handle);
    	if(i==0){
    		SetInterruptEnable(INT_IR_DEC, 1);
    	}
    	return i;
}

