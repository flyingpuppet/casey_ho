#ifndef USER_SETTING_H
#define USER_SETTING_H

#include <spi_regional_division.h>
#include <vpp_api.h>
//#include <vpp_api.h>
#include <cmd.h>

#define FBC_USER_START						0x1FF000
#define FBC_USER_SIZE						0x1000
#define FBC_USER_END						FBC_USER_START + FBC_USER_SIZE

#define	USER_HDCPKEY						FBC_USER_START
#define USER_HDCPKEY_SIZE					0x400

#define USER_SETTING_START					USER_HDCPKEY + USER_HDCPKEY_SIZE
#define USER_SETTING_SIZE					0x100

#define USER_WB_SETTING_START				USER_SETTING_START + USER_SETTING_SIZE
#define USER_WB_SETTING_SIZE				0x100

#define USER_PIC_SETTING_START				USER_WB_SETTING_START + USER_WB_SETTING_SIZE
#define USER_PIC_SETTING_SIZE				0x100


typedef struct white_balance_setting{
	unsigned char r_gain;
	unsigned char g_gain;
	unsigned char b_gain;
	unsigned char r_offset;
	unsigned char g_offset;
	unsigned char b_offset;
}white_balance_setting_t;

//save_parameter write_user_setting(unsigned char *s);
//unsigned char read_user_setting();
unsigned read_project_id();
int write_project_id(unsigned val);
char * read_device_id();
int write_device_id(char * device_id);
char * read_factory_sn();
int write_factory_sn( char * pSn);
unsigned char read_power_on_mode();
int write_power_on_mode(unsigned char mode);
char * read_HDCP_KEY();
int write_HDCP_KEY(const char * key, int len);
void d2d3_select(int mode);

int write_wb_setting(vpu_colortemp_t mode, white_balance_setting_t * val);
white_balance_setting_t * read_wb_setting(vpu_colortemp_t mode);
int write_picmod_setting(vpu_picmod_t mode, vpu_picmod_table_t * val);
vpu_picmod_table_t * read_picmod_setting(vpu_picmod_t mode);

int load_default_setting();

#endif
