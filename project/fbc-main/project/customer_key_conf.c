
#include <key_const.h>
#include <customer_key_conf.h>

int REMOTE_TYPE = DECODEMODE_TOSHIBA;

int remote_coustomer_code = 0x1818; //customer code
float ADC_VOLTAGE_MAX = 3.3;

int send_key_to_soc = 1;
int send_key_to_local_task = 0;

int send_remote_to_soc = 0;
int send_remote_to_local_task = 0;


int CUSTOMER_REMOTE_NUMS = 22;
int customer_key_map[][2]= {
    {38 , AMLKEY_UP}            ,
    {102 , AMLKEY_DOWN}  ,
    {166 , AMLKEY_LEFT}  ,
    {230 , AMLKEY_RIGHT}     ,
    {22 , AMLKEY_ENTER}     ,
    {4 , AMLKEY_MENU}  ,
    {150 , AMLKEY_EXIT}  ,
    {14 , AMLKEY_VOL_PLUS}  ,
    {15 , AMLKEY_VOL_MINUS}     ,
    {67 , AMLKEY_BACK}  ,
    {208 , AMLKEY_POWER}     ,
    {23 , AMLKEY_MUTE}  ,
    {10 , AMLKEY_NUM_0}     ,
    {1 , AMLKEY_NUM_1}  ,
    {2 , AMLKEY_NUM_2}  ,
    {3 , AMLKEY_NUM_3}  ,
    {4, AMLKEY_NUM_4}   ,
    {5 , AMLKEY_NUM_5}  ,
    {6 , AMLKEY_NUM_6}  ,
    {7 , AMLKEY_NUM_7}  ,
    {8 , AMLKEY_NUM_8}  ,
    {9 , AMLKEY_NUM_9}  ,
};

int ADC_KEY_NUM_MAX = 4;

//array num is ADC_KEY_NUM_MAX
float adc_key_vol[] = {0, 0.82,1.65, 2.47,};

//array num is ADC_KEY_NUM_MAX
int adc_key_code[] = {
    AMLKEY_NOP,  AMLKEY_LEFT, AMLKEY_RIGHT, AMLKEY_NOP,
};
int adc_key_code1[] = {
     AMLKEY_ENTER, AMLKEY_NOP, AMLKEY_UP,  AMLKEY_DOWN,   
};
