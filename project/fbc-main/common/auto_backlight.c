#include <stdio.h>
#include <task.h>
#include <timer.h>
#include <crc.h>
#include <task_priority.h>

#define PWM_MAX 255
#define PWM_MIN 0
#define USER_BACKLIGHT_MAX  100

static int DynamicGammaOffset = 0;
static int default_auto_bl_value = 0;
static int current_backlight = 100;
static int USER_BACKLIGHT_MAX = 100;
static int DynamicGamma = 100;
static int adjustBacklightCount = 0;
static int auto_backlight_task_id = -1;
static volatile int AutoBacklight_OnOff_Flag = 0;
static int timer_id = -1;
void getDynamicGammaOffset() 
{	
	int pwm = fbc_avg_lut();//CecHistogramGet_AVE();
	if (pwm > 0)	
	{		
		PWM_MAX = pwm;	
	}	
	else 	
	{		
		PWM_MIN = pwm;	
	}    	
	pwm = 255 - pwm;	
	int average = (PWM_MIN + PWM_MAX) / 2;	
	DynamicGammaOffset = (pwm - average) / 10;        
	DynamicGammaOffset = DynamicGammaOffset * default_auto_bl_value / 100;
}

int adjustByKF()
{	
	//if (isStaticFrame() == 0)
	if(0)
	{		
		return USER_BACKLIGHT_MAX;	
	}	
	else	
	{		
		int dest_backlight = DynamicGamma + DynamicGammaOffset;		
		if(dest_backlight > USER_BACKLIGHT_MAX)
		{
			dest_backlight = USER_BACKLIGHT_MAX ;		
		}
		else if(dest_backlight < 0)
		{
			dest_backlight = 0 ;		
			return dest_backlight;	
		}
	} 
}

void adjustBacklight(int dest_backlight) 
{	
	//current_backlight = SystemProperties.getInt("tv.real_backlight",current_backlight);
	current_backlight = getCurrentRealBackLight();	
	if (current_backlight < dest_backlight) 	
	{		
		current_backlight++;		
		SetBacklight_OPC(current_backlight);	
	} 
	else if (current_backlight > dest_backlight) 
	{		
		current_backlight--;		
		SetBacklight_OPC(current_backlight);	
	} 
	else 
	{				 	
	}
}

void SetBacklight_OPC(int value) 
{	
	//int currentSrcInputType = 0;	
	//currentSrcInputType = CecGetCurrentSrcInputType();	
	//CecSetBacklight(value, currentSrcInputType, 0);
	fbc_backlight_set(value);
}

/*void setBacklight(int value, int currentSrcInputType, int is_save)
{	
	CecSaveRealBacklight(value);
	CecSetBacklight(value, currentSrcInputType, is_save);
}*/

void initDynamicValue() 
{	
	USER_BACKLIGHT_MAX = USER_PICTURE_BACKLIGHT//getStaticBacklightVal();
	default_auto_bl_value = getDynamicBacklightVal();//get_Dynamic_Backlight_Val();
	DynamicGamma = default_auto_bl_value * USER_BACKLIGHT_MAX / 100;
	if (DynamicGamma > USER_BACKLIGHT_MAX)
	{
		DynamicGamma = USER_BACKLIGHT_MAX;
	}
}

int getStaticBacklightVal() 
{	
	int val = 50;//CecGetBacklight(CecGetCurrentSrcInputType());	
	return val;
}

int getDynamicBacklightVal()
{			
	int val = 50;		
	//val = CecGetDtvDynamicBacklightVal();		
	return val;	
}




void autoBacklightInit()
{	
	/*if(GlobalVariableDefine.Enable_AutoBacklight_M )
	{		
		SystemProperties.set("persist.tv.auto_backlight", "1");	
	}
	else 
	{	
		SystemProperties.set("persist.tv.auto_backlight", "0");	
	}*/	
	int default_user_bl_value  =  getStaticBacklightVal();//get_Static_Backlight_Val();
	default_auto_bl_value  =  getDynamicBacklightVal();//get_Dynamic_Backlight_Val();	
	//CecSetBacklight(default_user_bl_value, CecGetSrcInputType(), 1);	
	fbc_backlight_set(default_user_bl_value);
	current_backlight = default_user_bl_value ;
}

void startAutoBacklight() 
{	
	if(!AutoBacklight_OnOff_Flag)	
	{		
		if (timer_id >= 0)		
		{			
			release_timer(timer_id);		
		}		
		autoBacklightTaskInit();		
		AutoBacklight_OnOff_Flag = 0;	
	}	
}

void stopAutoBacklight()
{	
	if(AutoBacklight_OnOff_Flag)	
	{		
		if (timer_id >= 0)	
		{			
			release_timer(timer_id);			
			timer_id = -1;		
		}		
		if (auto_backlight_task_id != -1)		
		{			
			UnregisterTask(auto_backlight_task_id);			
			auto_backlight_task_id = -1;		
		}		
		//CecSetBacklight(USER_BACKLIGHT_MAX, getCurrentSrcInputType(), 1);
		fbc_backlight_set(USER_BACKLIGHT_MAX);
		current_backlight = USER_BACKLIGHT_MAX ;		
		AutoBacklight_OnOff_Flag = 1;	
	}
}

void updateAutoBacklight() 
{	
	if(AutoBacklight_OnOff_Flag == 1)	
	{		 
		initDynamicValue();	
	}	
	else	
	{		
		startAutoBacklight();	
	}
}

int autoBacklightTaskHandler(int task_id, void *param)
{	
	adjustBacklightCount++;	
	if (adjustBacklightCount == 5) 
	{
		// 5s		
		adjustBacklightCount = 0;		
		getDynamicGammaOffset();	
	}	
	adjustBacklight(adjustByKF());
}


void autoBacklightTaskInit()
{	
	if (auto_backlight_task_id == -1)	
	{		
		auto_backlight_task_id = RegisterTask(autoBacklightTaskHandler, NULL, 0, TASK_PRIORITY_AUTO_BACKLIGHT);
	}	
	if(auto_backlight_task_id > 0)
	{
		timer_id = request_timer(auto_backlight_task_id,100);//1s
	}
}


