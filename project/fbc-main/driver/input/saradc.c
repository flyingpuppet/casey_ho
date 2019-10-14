/*
 * saradc.c
 *
 *  Created on: 6/13/2014
 *      Author: Jing.Wei
 */
	 
#include <customer_key_conf.h>
#include <inputdata.h>
#include "saradc_reg.h"

#ifdef IN_FBC_MAIN_CONFIG
#include <input.h>
#include <interrupt.h>
#include <log.h>
#include <task.h>
#include <timer.h>
#include <task_priority.h>
#include <register.h>
#include <stdlib.h>
#include <string.h>
#include <cmd.h>

#define DEBUG 0
#define TAG "saradc"
#define LOG_D(...) if(DEBUG){\
		log_print_to_buffer(LOG_LEVEL_D, LOG_FLAG_WAKEUP, TAG, __VA_ARGS__);\
	}
#define LOG_E(...) if(DEBUG){\
		log_print_to_buffer(LOG_LEVEL_E, LOG_FLAG_WAKEUP, TAG, __VA_ARGS__);\
	}

static INPUTDATA ADCIrData;
static int timer_id = -1;

#else

#define LOG_D(...)
#define LOG_E(...)
#endif

static unsigned int chan_mux[SARADC_CHAN_NUM] = {0,1,};

void udelay(int us){
	int n= us*(80/3);
	while(n--);
}

static void saradc_power_control(int on)
{
	if (on) {
		enable_bandgap();
		udelay(10);
		enable_adc();
		udelay(5);
		enable_clock();
		enable_sample_engine();
	}
	else {
		disable_sample_engine();
		disable_clock();
		disable_adc();
		disable_bandgap();		
	}
	return;
}


static void saradc_reset(void)
{
	int i;

	//set adc clock as 1.26Mhz
	enable_clock_cntl();
	enable_clock_gate();
	set_clock_divider(18);
	
	saradc_power_control(1);

	set_sample_mode(DIFF_MODE);
	set_tempsen(0);
	disable_fifo_irq();
	disable_continuous_sample();
	disable_chan0_delta();
	disable_chan1_delta();

	set_input_delay(10, INPUT_DELAY_TB_1US);
	set_sample_delay(10, SAMPLE_DELAY_TB_1US);
	set_block_delay(10, BLOCK_DELAY_TB_1US);
	
	// channels sampling mode setting
	for(i=0; i<SARADC_CHAN_NUM; i++)
	{
		set_sample_sw(i, IDLE_SW);
		set_sample_mux(i, chan_mux[i]);
	}
	
	// idle mode setting
	set_idle_sw(IDLE_SW);
	set_idle_mux(chan_mux[CHAN_0]);
	
	// detect mode setting
	set_detect_sw(DETECT_SW);
	set_detect_mux(chan_mux[CHAN_0]);
	disable_detect_sw();
	disable_detect_pullup();
	set_detect_irq_pol(0);
	disable_detect_irq();

	enable_sample_engine();
}

#ifdef IN_FBC_MAIN_CONFIG
static int ADC_DATA_pro(int chan, INPUTDATA *data)
{
	int key_val;
	int ret = AMLKEY_NOP;

	int temp = data->input_data;
	
	if(KeyProcessFunc)	{
		KeyProcessFunc(INPUT_SARADC, 0xff,  temp, 0);
	}

	for(int i=0; i<ADC_KEY_NUM_MAX; i++)
	{
		
		key_val = (int)(adc_key_vol[i] / ADC_VOLTAGE_MAX * 1023);
		if(temp>=key_val-40 && temp<=key_val+40)
		{
			if(chan == 0){
				ret = adc_key_code[i];
			}
			else if(chan == 1){
				ret = adc_key_code1[i];
			}
		}
	}
	LOG_D("saradc key pressed is %d.\n",ret);
	return ret;
}
#else

int adc2key(int chan, INPUTDATA *data)
{
	int key_val;
	int ret = AMLKEY_NOP;
	int temp = data->input_data;
	
	for(int i=0; i<ADC_KEY_NUM_MAX; i++)
	{			
		key_val = (int)(adc_key_vol[i] / ADC_VOLTAGE_MAX * 1023);
		if(temp>=key_val-40 && temp<=key_val+40)
		{
			if(chan == 0)
			{
				ret = adc_key_code[i];
			}
			else if(chan == 1)
			{
				ret = adc_key_code1[i];
			}
		}
	}

	return ret;

}

#endif

static int get_adc_sample(int chan)
{
	int count=0;
	int value = -1;
	int sum = 0;
	saradc_power_control(1);
	set_chan_list(chan, 1);
	set_avg_mode(chan, NO_AVG_MODE, SAMPLE_NUM_8);
	set_sample_mux(chan, chan_mux[chan]);
	set_detect_mux(chan_mux[chan]);
	set_idle_mux(chan_mux[chan]); // for revb
	enable_sample_engine();
	start_sample();

	count = 0;
	while (delta_busy() || sample_busy() || avg_busy())
	{
		if (++count > 10000)
		{
			//LOG_E("ADC busy error=%x.\n", get_reg(AO_SAR_ADC_REG0));
			goto end;
		}
	}

	if(fifo_empty())
	{
		//LOG_E("FIFO empty error=%x.\n", get_reg(AO_SAR_ADC_REG0));
		goto end;
	}

	stop_sample();

	value = get_fifo_sample();
	value = count = 0;
	while (get_fifo_cnt())
	{
		value = get_fifo_sample() & 0x3ff;
		sum += value & 0x3ff;
		count++;
	}
	value = (count) ? (sum / count) : (-1);
	//LOG_D("======sample value averaged is %d.\n", value);

end:
	disable_sample_engine();
	return value;
}

/*
 * param key_code: the sample value averaged.
 * return : KEY_DOWN & KEY_UP & error(-1)
 */
int get_input_type(int key_code)
{
	int ret = 0;	
	int max_vol = (int)(adc_key_vol[ADC_KEY_NUM_MAX-1] / ADC_VOLTAGE_MAX * 1023) + 40;
	int min_vol = (int)(adc_key_vol[0] / ADC_VOLTAGE_MAX * 1023) - 40;

	if(key_code>max_vol && key_code<1023)
		ret = KEY_UP;
	else if(key_code>=min_vol && key_code<=max_vol)
		ret = KEY_DOWN;
	else
		ret = -1;

	return ret;
}

#ifdef IN_FBC_MAIN_CONFIG
static int adc_task_handle(int task_id, void *param)
{
	static int oldparams_0 = -1;
	static int oldparams_1 = -1;
	int params;
	int key_code = get_adc_sample(0);
	if(key_code == -1)
		return 0;
	//printf("key_code %d\n",key_code);
	ADCIrData.input_data = key_code;
	ADCIrData.input_type = get_input_type(key_code);
	if(ADCIrData.input_type == KEY_DOWN){
		params = ADC_DATA_pro(0, &ADCIrData);
		if(params != oldparams_0)
		{
			if(send_key_to_soc == 1)
			{
				SendCmd(task_id,INPUT_UART_HOST,CMD_INPUT_DOWN,&params);
			}
			if(send_key_to_local_task == 1)
			{
				AddIputdataToTaskList(INPUT_SARADC, params);
			}
			//printf("type: %d, value:  %d\n",CMD_INPUT_DOWN, params);
			oldparams_0 = params;
			//AddIputdataToTaskList(INPUT_SARADC, params);
			
		}		
		return 0;
	}
	else if(ADCIrData.input_type == KEY_UP)
	{
		if(oldparams_0 != -1)
		{
			SendCmd(task_id, INPUT_UART_HOST,CMD_INPUT_UP,&oldparams_0);
			//printf("type: %d, value:  %d\n",CMD_INPUT_UP,oldparams_0);
			oldparams_0 = -1;
			return 0;
		}
	}

	key_code = get_adc_sample(1);
	if(key_code == -1)
		return 0;
	//printf("key_code %d\n",key_code);
	ADCIrData.input_data = key_code;
	ADCIrData.input_type = get_input_type(key_code);
	if(ADCIrData.input_type == KEY_DOWN){
		params = ADC_DATA_pro(1, &ADCIrData);
		if(params != oldparams_1)
		{
			if(send_key_to_soc == 1)
			{
				SendCmd(task_id,INPUT_UART_HOST,CMD_INPUT_DOWN,&params);
			}
			if(send_key_to_local_task == 1)
			{
				AddIputdataToTaskList(INPUT_SARADC, params);
			}
			//printf("type: %d, value:  %d\n",CMD_INPUT_DOWN,params);
			oldparams_1 = params;
		}
		//AddIputdataToTaskList(INPUT_SARADC, params);
		
	}
	else if(ADCIrData.input_type == KEY_UP)
	{
		if(oldparams_1 != -1)
		{
			SendCmd(task_id, INPUT_UART_HOST,CMD_INPUT_UP,&oldparams_1);
			//printf("type: %d, value:  %d\n",CMD_INPUT_UP,oldparams_1);
			oldparams_1 = -1;
		}
		
	}
	
	return 0;
}
#else

static int rd_flag = 0;

int set_redetect_flag()
{
	rd_flag = 1;
	return 0;
}

int detect_adc_key(int chanel, INPUTDATA *inputdata)
{
	static int action = 0;	//0:up, 1:down
	static int key_code = -1;
	int type = -1;
	
	if(!inputdata) return -1;

	if(rd_flag)
	{
		rd_flag = 0;
		action = 0;
		key_code = -1;
	}
	
	int cur_code = get_adc_sample(chanel);
	if(cur_code == -1)
		return -1;

	type = get_input_type(cur_code);

	if(action && KEY_UP == type && key_code >= 0)
	{
		action = 0;
		inputdata->input_data = key_code;
		inputdata->input_type = type;
		key_code = -1;
		return 0;
	}
	
	if(!action && KEY_DOWN == type)
	{
		action = 1;
		inputdata->input_data = cur_code;
		inputdata->input_type = type;
		key_code = cur_code;
		return 0;
	}
	
	return -1;

}

#endif

void sar_adc_init(void)
{
	saradc_reset();
	
#ifdef IN_FBC_MAIN_CONFIG	
	int tmp = -1;
	tmp = RegisterTask(adc_task_handle, NULL, 0 , TASK_PRIORITY_SARADC);
	if(tmp != -1)
	{
		LOG_D("=====adc task id is %d.\n", tmp);
		timer_id = request_timer(tmp, 10);//100ms interrupt
	}
#endif
}


