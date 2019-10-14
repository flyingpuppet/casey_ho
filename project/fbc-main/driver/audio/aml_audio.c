#include <stdint.h>
#include <register.h>
#include <c_arc_pointer_reg.h>
#include <log.h>
#include <interrupt.h>
#include <task.h>
#include <malloc.h>
#include <arc600.h>
#include <XYmemoryMapping.h>
#include <task_priority.h>

#include "aml_audio.h"
#include "audio_control.h"

static char TAG[] = "Audio_main";

#define I2S_READ_ADR I2S_READ_ADR_00
#define I2S_WRITE_ADR I2S_WRITE_ADR_00
#define I2S_in_FIFO_ADR P_I2S_READ_ADR_00
#define I2S_out_FIFO_ADR P_I2S_WRITE_ADR_00

#define I2S_IRQ_NUM			256		//frame size
#define HALF_I2S_IRQ_NUM	(I2S_IRQ_NUM/2)
#define PERIOD_SIZE			3
#define BUFFER_SIZE			(I2S_IRQ_NUM*PERIOD_SIZE) //32bit

static int input_started_counter = 0;
extern struct codec_control *codec;
extern struct audio_control audio_state;

static int audio_process_init(void);
static int audio_process_set_parameter(unsigned char value);
static int audio_process_DMA_test(unsigned int input, unsigned int output, int frame_num);
static int audio_process_test(short *input, short *output, int frame_num);

static struct buffer_status i2s_in_buffer = {
	.start_add = NULL,
	.level = 0,
	.rd = 0,
	.wr = 0,
};
static struct buffer_status i2s_out_buffer = {
	.start_add = NULL,
	.level = 0,
	.rd = 0,
	.wr = 0,
};
static struct audio_effect user_audio_effect = {
	.init = audio_process_init,
#ifdef DMA_USED
	.audio_process = audio_process_DMA_test,
#else
	.audio_process = audio_process_test,
#endif
	.set_parameter = audio_process_set_parameter,
};

static int audio_process_test(short *input, short *output, int frame_num){
	for(int i = 0; i < frame_num; i++){
		*output++ = *input++;	//L
		*output++ = *input++;	//R
	}
	return 0;
}

static int audio_process_init(void){
	LOGI(TAG, "amlogic audio process init!\n");
#ifdef DMA_USED
	_SetXMem(0, 0, 1024);
	_SetYMem(0, 0, 1024);
#endif
	return 0;
}

static int audio_process_set_parameter(unsigned char value){
	LOGI(TAG, "amlogic set_parameter!\n");
	return 0;
}

static int audio_process_DMA_test(unsigned int input, unsigned int output, int frame_num){
	
	_Set_ax0(input);__set_mx00(1);
	_Set_ay0(output);__set_my00(1);

	for(int i = 0; i < frame_num; i++){
		_set_y0_u0(_x0_u0());
	}
	return 0;
}

static int Audio_Process(void)
{
	struct audio_effect *ptr = &user_audio_effect;

#ifdef DMA_USED
	unsigned int input = INPUT_DATA;
	unsigned int output = OUTPUT_DATA + i2s_out_buffer.wr;
	ptr->audio_process(input,output,I2S_IRQ_NUM);
	i2s_out_buffer.wr += I2S_IRQ_NUM;
	i2s_out_buffer.wr %= BUFFER_SIZE;
#else
	short *input = (short *)i2s_in_buffer.start_add;
	short *output = (short *)i2s_out_buffer.start_add + i2s_out_buffer.wr;
	ptr->audio_process(input,output,I2S_IRQ_NUM);
	i2s_out_buffer.wr += I2S_IRQ_NUM*2;
	i2s_out_buffer.wr %= BUFFER_SIZE*2;
#endif
	i2s_out_buffer.level += I2S_IRQ_NUM;
	return 0;
}

static int I2S_IN_IRQ_Handle(void *arg)	{
	
	int i = 0;
	unsigned int tmp = 0;
	short *input = (short *)i2s_in_buffer.start_add;
	for (i  = 0; i < I2S_IRQ_NUM; i++){
		tmp = Rd(I2S_READ_ADR);
		*input ++ = (short) (tmp & 0xffff); //L
		*input ++ = (short) ((tmp >> 16) & 0xffff); //R
	}
	Audio_Process();
	if(input_started_counter < 10){
		(codec->set_mute)();
		input_started_counter++;
	} else if(input_started_counter == 10){
		(codec->set_master_vol)(audio_state.master_volume);
		input_started_counter++;
	}
	return 0;
}

static int I2S_OUT_IRQ_Handle(void *arg)	{
	int i = 0;
	unsigned int tmp = 0;
	short *output = (short *)i2s_out_buffer.start_add + i2s_out_buffer.rd;
	if(i2s_out_buffer.level > 0){
		for (i  = 0; i < I2S_IRQ_NUM; i++){
			tmp = (int)(*output++) & 0xffff;
			tmp |= ((int)(*output++) << 16) & 0xffff0000;
			Wr(I2S_WRITE_ADR, tmp);
		}
		i2s_out_buffer.rd += I2S_IRQ_NUM*2;
		i2s_out_buffer.rd %= BUFFER_SIZE*2;
		i2s_out_buffer.level -= I2S_IRQ_NUM;
	}
	return 0;
}

static int I2S_IN_IRQ_DMA_Handle(void *arg){

	int *fifo_add = (int *)(I2S_in_FIFO_ADR);
	unsigned int xy_add = INPUT_DATA;
	
	_BurstSMemToXMem(xy_add, fifo_add, 128);
	_BurstSMemToXMem((xy_add + 128),fifo_add, 128);
	Audio_Process();
	
	return 0;
}
static int I2S_OUT_IRQ_DMA_Handle(void *arg){

	int *fifo_add = (int *)(I2S_out_FIFO_ADR);
	unsigned int xy_add = OUTPUT_DATA + i2s_out_buffer.rd;
	
	if(i2s_out_buffer.level > 0){
		_BurstYMemToSMem(fifo_add, xy_add, 128);
		_BurstYMemToSMem(fifo_add, (xy_add + 128), 128);
		i2s_out_buffer.rd += I2S_IRQ_NUM;
		i2s_out_buffer.rd %= BUFFER_SIZE;
		i2s_out_buffer.level -= I2S_IRQ_NUM;
	}
	return 0;
}

static int set_i2s_in(void){

	LOGI(TAG, "Set audio i2s-in registers!\n");
	//enable i2s in interrupt
	int ret = -1;
#ifdef DMA_USED
	ret = RegisterInterrupt(INT_I2S_IN_PLS_RD_IRQ, INT_TYPE_IRQ, (interrupt_handler_t)I2S_IN_IRQ_DMA_Handle);
#else
	ret = RegisterInterrupt(INT_I2S_IN_PLS_RD_IRQ, INT_TYPE_IRQ, (interrupt_handler_t)I2S_IN_IRQ_Handle);
#endif
    if(ret < 0){
		LOGE(TAG, "Set i2s in irq failed!\n");
    	return ret;
    }
	//register user audio process
	user_audio_effect.init();
	SetInterruptEnable(INT_I2S_IN_PLS_RD_IRQ, 1);
	
	Wr(I2S_IN_CTRL , (Rd(I2S_IN_CTRL) | (0<<I2S_IN_SLOW_ENABLE)));
	Wr(I2S_IN_CTRL , (Rd(I2S_IN_CTRL) | (0<<I2S_IN_FAST_ENABLE)));
	
	// i2s_in control
	Wr(I2S_IN_CTRL , ((0<<I2S_IN_FAST_ENABLE)|		//Enable i2s_in_path_fast work.
						(0<<I2S_IN_SLOW_ENABLE)|	//Enable i2s_in_path_slow work.
						(1<<I2S_IN_16BIT)|			//0: i2s_dat is 24bit; 1: i2s_dat is 16bit;
						(0<<I2S_IN_DEBUG)|			//0: in 24bit mode, write to fifo {8'd0,24'd0};1: in 24bit mode, write to fifo as :{fifo_adr,24'd0};
						(0<<I2S_IN_REV_WS)|			//0: use hdmi_i2s_ws;1: revert hdmi_i2s_ws;
						(0<<I2S_IN_REV_DAT)|		//0: use hdmi_i2s_dat;1: revert hdmi_i2s_dat;
						(0<<I2S_IN_BIT_SKEW)|		//Select the position of msb.
						(0<<I2S_IN_LR_TOREG)|		//0: {right_ch[31:16],left_ch[15:0]};1: {left_ch[31:16],right_ch[15:0]};
						(0<<I2S_SCK_TOINPATH_SEL)|	//0: use hdmi_i2s_sck;1: revert hdmi_i2s_sck;
						(0<<I2S_SCK_TOOUTPATH_SEL)|	//0: use hdmi_i2s_sck;1: revert hdmi_i2s_sck;
						(1<<I2S_SCK_TOGPIO_SEL)|	//0: use hdmi_i2s_sck;1: revert hdmi_i2s_sck;
						(0<<DETECT_CH_STATUS)|		//1: use spdif detect ch_status;
						(I2S_IRQ_NUM<<I2S_IN_IRQ_EN_NUM)|	//prevent many irq when apb read fifo
						((2*I2S_IRQ_NUM)<<I2S_IN_IRQ_NUM)));	//generate an irq
	//start input
	Wr(I2S_IN_CTRL , (Rd(I2S_IN_CTRL) | (1<<I2S_IN_SLOW_ENABLE)));
	Wr(I2S_IN_CTRL , (Rd(I2S_IN_CTRL) | (1<<I2S_IN_FAST_ENABLE)));
	
	return 0;
}

static int set_i2s_out(void){

	LOGI(TAG, "Set audio i2s-out registers!\n");
	//enable i2s out interrupt
	int ret = -1;
#ifdef DMA_USED
	ret = RegisterInterrupt(INT_I2S_OUT_PLS_WR_IRQ, INT_TYPE_IRQ, (interrupt_handler_t)I2S_OUT_IRQ_DMA_Handle);
#else
	ret = RegisterInterrupt(INT_I2S_OUT_PLS_WR_IRQ, INT_TYPE_IRQ, (interrupt_handler_t)I2S_OUT_IRQ_Handle);
#endif
    if(ret < 0){
		LOGE(TAG, "Set i2s out irq failed!\n");
    	return ret;
    }
	SetInterruptEnable(INT_I2S_OUT_PLS_WR_IRQ, 1);
	
	Wr(I2S_IN_CTRL , (Rd(I2S_IN_CTRL) | (0<<I2S_IN_SLOW_ENABLE)));
	Wr(I2S_IN_CTRL , (Rd(I2S_IN_CTRL) | (0<<I2S_IN_FAST_ENABLE)));
	
	// i2s_out  control
	Wr(I2S_OUT_CTRL , ((0<<I2S_OUT_FAST_ENABLE)|	//Enable i2s_out_path_fast work
						(0<<I2S_OUT_SLOW_ENABLE)|	//Enable i2s_out_path_slow work
						(1<<I2S_OUT_16BIT)|			//0: i2s_dat is 24bit; 1: i2s_dat is 16bit;
						(0<<I2S_OUT_DEBUG)|			//0: in 24bit mode, write to fifo {8'd0,24'd0};1: in 24bit mode, write to fifo as :{fifo_adr,24'd0};
						(0<<I2S_OUT_REV_WS)|		//0: use hdmi_i2s_ws;1: revert hdmi_i2s_ws;
						(0<<I2S_OUT_REV_DAT)|		//0: use hdmi_i2s_dat;1: revert hdmi_i2s_dat;
						(0<<I2S_OUT_BIT_SKEW)|		//Select the position of msb.
						(0<<I2S_OUT_LR_TOREG)|		//0: {right_ch[31:16],left_ch[15:0]};1: {left_ch[31:16],right_ch[15:0]};
						(I2S_IRQ_NUM<<I2S_OUT_IRQ_EN_NUM)|	//prevent many irq when apb read fifo
						((2*I2S_IRQ_NUM)<<I2S_OUT_IRQ_NUM)));	//send a irq to cpu
	//start out put
	Wr(I2S_OUT_CTRL , (Rd(I2S_OUT_CTRL) | (1<<I2S_OUT_FAST_ENABLE)));
	Wr(I2S_OUT_CTRL , (Rd(I2S_OUT_CTRL) | (1<<I2S_OUT_SLOW_ENABLE)));
	//enable i2s to GPIO
	Wr(PERIPHS_PIN_MUX_4,(Rd(PERIPHS_PIN_MUX_4)|(15<<4)));
	Wr(PREG_PAD_GPIO4_EN_N,(Rd(PREG_PAD_GPIO4_EN_N)|(15<<4)));
	
	return 0;
}

static int malloc_buffer(void){

	LOGI(TAG,"init audio buffer!\n");
#ifndef DMA_USED
	//malloc i2s in tmp buffer
	i2s_in_buffer.start_add = (void*) malloc(I2S_IRQ_NUM*sizeof(int));
	if(i2s_in_buffer.start_add == NULL){
		LOGE(TAG,"Malloc in buffer fail\n");
		return -1;
	}
	//malloc i2s out buffer
	i2s_out_buffer.start_add = (void*) malloc(BUFFER_SIZE*sizeof(int));
	if(i2s_out_buffer.start_add == NULL){
		LOGE(TAG,"Malloc out buffer fail\n");
		free(i2s_in_buffer.start_add);
		i2s_in_buffer.start_add = NULL;
		return -1;
	}
#endif
	i2s_out_buffer.level = 0;
	i2s_out_buffer.rd = 0;
	i2s_out_buffer.wr = 0;
	return 0;
}

static int release_buffer(void){
#ifndef DMA_USED
	if(i2s_in_buffer.start_add != NULL){
		free(i2s_in_buffer.start_add);
		i2s_in_buffer.start_add = NULL;
	}
	if(i2s_out_buffer.start_add != NULL){
		free(i2s_out_buffer.start_add);
		i2s_out_buffer.start_add = NULL;
	}
#endif
	i2s_out_buffer.level = 0;
	i2s_out_buffer.rd = 0;
	i2s_out_buffer.wr = 0;
	return 0;
}

void RigisterAudioProcess(struct audio_effect *ptr){
	struct audio_effect *tmp = &user_audio_effect;
	LOGI(TAG,"Set user process!\n");
	tmp->init = ptr->init;
	tmp->audio_process = ptr->audio_process;
	tmp->set_parameter = ptr->set_parameter;
	return;
}

//------------------------------------------------------------------------------------
int i2s_audio_init(void)
{
	int ret = -1;
	LOGI(TAG,"Enter i2s_audio_open\n");

	ret = malloc_buffer();
	if(ret < 0){
		LOGE(TAG,"malloc_buffer fail\n");
		return ret;
	}

	ret = audio_codec_init();
	if(ret < 0){
		LOGE(TAG,"Init audio codec failed\n");
		return ret;
	}
	
	ret = set_i2s_in();
	if(ret < 0){
		LOGE(TAG,"set_i2s_in fail\n");
		return ret;
	}
	
	ret = set_i2s_out();
	if(ret < 0){
		LOGE(TAG,"set_i2s_out fail\n");
		return ret;
	}
	
	ret = init_audio_cec_control_task();
	if(ret < 0){
		LOGE(TAG,"Init audio_cec_control_task failed\n");
		return ret;
	}

	return ret;
}


