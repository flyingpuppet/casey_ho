#ifndef __TAS5707_H__
#define __TAS5707_H__

#define DDX_I2C_ADDR								0x36

#define DDX_CLOCK_CTL                               0x00
#define DDX_DEVICE_ID                               0x01
#define DDX_ERROR_STATUS                            0x02
#define DDX_SYS_CTL_1                               0x03
#define DDX_SERIAL_DATA_INTERFACE                   0x04
#define DDX_SYS_CTL_2                               0x05
#define DDX_SOFT_MUTE                               0x06
#define DDX_MASTER_VOLUME                           0x07
#define DDX_CHANNEL1_VOL							0x08
#define DDX_CHANNEL2_VOL							0x09
#define DDX_MASTER_FINE_VOLUME_REGISTER				0x0A
#define DDX_VOLUME_CONFIG                           0x0E

#define DDX_MODULATION_LIMIT                        0x10
#define DDX_IC_DELAY_CHANNEL_1                      0x11
#define DDX_IC_DELAY_CHANNEL_2                      0x12
#define DDX_IC_DELAY_CHANNEL_3                      0x13
#define DDX_IC_DELAY_CHANNEL_4                      0x14

#define DDX_START_STOP_PERIOD                       0x1A
#define DDX_OSC_TRIM                                0x1B
#define DDX_BKND_ERR                                0x1C
#define DDX_INPUT_MUX                               0x20
#define DDX_PWM_MUX                                 0x25

#define DDX_CH1_BQ_0								0x29
#define DDX_CH1_BQ_1                                0x2A
#define DDX_CH1_BQ_2                                0x2B
#define DDX_CH1_BQ_3                                0x2C
#define DDX_CH1_BQ_4                                0x2D
#define DDX_CH1_BQ_5                                0x2E
#define DDX_CH1_BQ_6                                0x2F

#define DDX_CH2_BQ_0								0x30
#define DDX_CH2_BQ_1								0x31
#define DDX_CH2_BQ_2								0x32
#define DDX_CH2_BQ_3								0x33
#define DDX_CH2_BQ_4								0x34
#define DDX_CH2_BQ_5								0x35
#define DDX_CH2_BQ_6								0x36

#define DDX_DRC1_AE                                 0x3A
#define DDX_DRC1_AA                                 0x3B
#define DDX_DRC1_AD                                 0x3C

#define DDX_DRC1_T                                  0x40
#define DDX_DRC1_K                                  0x41
#define DDX_DRC1_O                                  0x42
#define DDX_DRC_CTL                                 0x46
#define DDX_BANKSWITCH_AND_EQCTL                    0x50
#define DDX_CH_DEV_ADDR_UPDATE                      0xF9
#define DDX_DRC_BYTES                               (8)
#define DDX_BQ_BYTES								(20)

struct tas5707_parameters{
	unsigned char DRC_enable;
	unsigned char EQ_enable;
};

#endif
