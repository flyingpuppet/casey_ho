/*
 * saradc.c
 *
 *  Created on: 6/13/2014
 *      Author: Jing.Wei
 */
#include <log.h>
#include <register.h>
#include <pwm.h>

void pwm_init(void){
	serial_puts("Init PWM.\n");
	Wr_reg_bits(PERIPHS_PIN_MUX_0, 1, 3, 1);  //set pinmux
	Wr_reg_bits(PWM_MISC_REG_AB, 1, 15, 1);   // enable clock
	Wr_reg_bits(PWM_MISC_REG_AB, 0x77, 8, 6); // set divider to 199+1=120 
	Wr_reg_bits(PWM_MISC_REG_AB, 1, 0, 1);    //PWM_A_EN
}

void led_bl_level_set(int level){
	unsigned int level_value=0;
	if (level > LED_BL_MAX_LEVEL){
		level = LED_BL_MAX_LEVEL;
	}
	if (level < LED_BL_MIN_LEVEL){
		level = LED_BL_MIN_LEVEL;
	}
	level_value=level * PWM_MAX / LED_BL_MAX_LEVEL ;
	Wr(PWM_PWM_A, ((level_value << 16) | ((PWM_MAX - level_value) << 0)));
}


