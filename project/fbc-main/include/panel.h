#ifndef PANEL_H
#define PANEL_H

typedef enum panel_format_e{
	PANEL_NORMAL = 0,
	PANEL_YUV420,
	PANEL_MAX,
}panel_format_t;

typedef enum vpu_outputmode_e{
	OUTPUT_LVDS = 0,
	OUTPUT_VB1,
	PORT_MAX,
}vpu_outputmode_t;

typedef enum vpu_timing_e{
	TIMING_NULL = 0,
	TIMING_1366x768P60,
	TIMING_1920x1080P50,
	TIMING_1920x1080P60,
	TIMING_1920x1080P100,
	TIMING_1920x1080P120,
	TIMING_1920x1080P60_3D_SG,
	TIMING_1920x1080P240,
	TIMING_1920x1080P120_3D_SG,
	TIMING_3840x2160P60,
	TIMING_3840x2160P50,
	TIMING_3840x2160P24,
	TIMING_3840x2160P30,
	TIMING_4kx1kP120_3D_SG,
	TIMING_4kxd5kP240_3D_SG,
	TIMING_MAX,
}vpu_timing_t;


typedef struct panel_config_s{
	vpu_outputmode_t output_mode;
	vpu_timing_t lvds_timing;
	vpu_timing_t vx1_timing;

	panel_format_t format;

	unsigned char reverse;
	unsigned char scaler;

	unsigned char clk;
	unsigned char repack;		/* 0:normal, 1,2:repack */
	unsigned char odd_even;	/* 0:normal, 1:swap */
	unsigned char hv_invert;	/* invert hs and vs */
	unsigned char lsb_first;		/* 0:MSB first, 1:LSB first */
	unsigned char pn_swap;	/* positive and negative swap */
	unsigned char ports;		/* 0: single port;  1: dual ports */
	unsigned char bit_size;		/* 0:10bits, 1:8bits, 2:6bits, 3:4bits */
	unsigned char b_select;		/* 0:R, 1:G, 2:B, 3:0 */
	unsigned char g_select;		/* 0:R, 1:G, 2:B, 3:0 */
	unsigned char r_select;		/* 0:R, 1:G, 2:B, 3:0 */
	unsigned char reg_de_exten;
	unsigned char reg_blank_align;
	unsigned char lvds_swap;
	unsigned char clk_pin_swap;

	unsigned char bl_inverter;   /*  1: inverter backlight pwm   0 : not inverter backlight pwm*/

	int lane_num;
	int byte_num;
	int region_num;
	int color_fmt;

	unsigned short pwm_duty;   /*  range 0-255*/
	unsigned short pwm_hz;

	unsigned short panel_power_on_delay;
	unsigned short panel_power_off_delay;
	unsigned short pwm_enable_delay;
	unsigned short pwm_disable_delay;
	unsigned short clock_enable_delay;
	unsigned short clock_disable_delay;
	unsigned short backlight_power_on_delay;
	unsigned short backlight_power_off_delay;

	char ManufactureID[2];
	char ProductID[2];
	//machine serial number
	char SerialNumber[4];
	//week,year
	char ManufactureDate[2];
	//0xfb,0x0c(fbc) || 0xff,0xff(non-fbc)
	char ChipID[2];
	//=0 1080p
	//=1 4k2k
	//=2 1366x768
	char PanelInfo:4;
	//=0 non-3D
	//=1 frame packing
	//=2 top bottom
	//=3 side by side full
	//=4 side byte side half (horz sub-sampling)
	//=5 Line alternative
	//=6 side byte side half (all quincunx sub-sampling)
	//=7 L+depth
	//=8 L+depth+graphics-depth
	//=9 Field alternative
	char ThreeDinfo:4;
	//bit0=1 panel screen upside-down; bit0=0 normal
	char SpecicalInfo;
}panel_config_t;

/*
typedef struct Usr_EDID_s{
	char ManufactureID[2];
	char ProductID[2];
	//machine serial number
	char SerialNumber[4];
	//week,year
	char ManufactureDate[2];
	//0xfb,0x0c(fbc) || 0xff,0xff(non-fbc)
	char ChipID[2];
	//=0 1080p
	//=1 4k2k
	//=2 1366x768
	char PanelInfo:4;
	//=0 non-3D
	//=1 frame packing
	//=2 top bottom
	//=3 side by side full
	//=4 side byte side half (horz sub-sampling)
	//=5 Line alternative
	//=6 side byte side half (all quincunx sub-sampling)
	//=7 L+depth
	//=8 L+depth+graphics-depth
	//=9 Field alternative
	char ThreeDinfo:4;
	//bit0=1 panel screen upside-down; bit0=0 normal
	char SpecicalInfo;
}Usr_EDID_t;
*/
extern int project_id;
extern panel_config_t *panel_param;

vpu_outputmode_t get_output_mode(void);
vpu_timing_t get_timing_mode(void);

int panel_suspend(void);
int panel_resume(void);

void mdelay(int ms);

void power_on_aml(void);
void power_off_aml(void);
void panel_power_on_aml(void);
void panel_power_off_aml(void);
void backlight_power_on_aml(void);
void backlight_power_off_aml(void);
void set_led_onoff(unsigned char vcValue);

#endif

