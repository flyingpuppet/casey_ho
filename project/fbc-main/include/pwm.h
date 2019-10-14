#ifdef PWM_H
#else
#define PWM_H

#define PWM_MAX 4000
#define LED_BL_MAX_LEVEL    255
#define LED_BL_MIN_LEVEL    0

void pwm_init(void);
void led_bl_level_set(int level);

#endif // PWM_H


