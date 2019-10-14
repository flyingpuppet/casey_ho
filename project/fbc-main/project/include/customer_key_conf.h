#ifndef CUSTOMER_KEY_CONF_H
#define CUSTOMER_KEY_CONF_H

#include <key_const.h>

typedef enum {
    DECODEMODE_NEC = 0,
    DECODEMODE_RCA = 1 ,
    DECODEMODE_TOSHIBA = 2 ,

} ddmode_t;

extern int REMOTE_TYPE;

extern int remote_coustomer_code; // 0xfe01, customer code

extern int customer_key_map[][2];
extern int CUSTOMER_REMOTE_NUMS;
extern int ADC_KEY_NUM_MAX;
extern float ADC_VOLTAGE_MAX;

extern float adc_key_vol[];


extern int adc_key_code[];
extern int adc_key_code1[];

extern int send_key_to_soc;
extern int send_key_to_local_task;

extern int send_remote_to_soc;
extern int send_remote_to_local_task;




#endif /*CUSTOMER_KEY_CONF_H8*/
