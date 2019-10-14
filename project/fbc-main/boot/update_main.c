#include <string.h>
#include <stdlib.h>
#include <serial.h>
#include <common.h>
#include <spi_flash.h>
#include <update.h>
#include <reboot.h>
#include <timer.h>
#include <uart_api.h>
#include <panel.h>
#include <osd.h>
#include <fonts_update.h>

#define DEVICE_UART_PORT_0       0
#define DEVICE_UART_PORT_1       1
#define DEVICE_UART_PORT_2       2

extern int sprintf(char * buffer, const char *__fmt, ...);
extern void init_vpp(void);
extern void panel_init(void);
extern void pwm_init(void);
unsigned long OSTimeGet();

int gTitleMsgHandle = -1;
int gUpdateMsgHandle = -1;
int gUpdateTimeHandle = -1;

void init_osd(void)
{
    int i;
    //hide_logo();
    OSD_Enable(0);
    if(OUTPUT_LVDS == panel_param->output_mode) {
        OSD_Initial(1920,1080,0,0,1919,1079);
        OSD_SetFontScale(1, 1);
    } else if(OUTPUT_VB1 == panel_param->output_mode) {
        OSD_Initial(3840,2160,0,0,3839,2159);
        OSD_SetFontScale(2, 2);
    }
    OSD_Set3DMode(OSD_3D_MODE_NORMAL);
    //OSD_SetFontScale(1, 1);
    //OSD_SetMirror(1);
    OSD_SetSpacing(2,2,2,2);
    if(OSD_GetMirror()==1) {
        OSD_ConfigFonts(FONT_NUM, FONT_WIDTH, FONT_HEIGHT, sosd_font_lib_lut_hvflip, font_mapping, 1);
    } else if(OSD_GetMirror()==0) {
        OSD_ConfigFonts(FONT_NUM, FONT_WIDTH, FONT_HEIGHT, sosd_font_lib_lut, font_mapping, 1);
    }
    for (i=0; i<FONT_NUM; i++)
        OSD_SetFontCut(i, sosd_cut_table[i]);
    for (i=0; i<16; i++)
        OSD_SetColor(i, nRGBA[i][0], nRGBA[i][1], nRGBA[i][2], nRGBA[i][3]);
    OSD_SetBackground(1, FONT_BG_COLOR_INDEX);
    //osd_init = 1;
    //OSD_CleanScreen(update_menu, 78);
    //OSD_InitialRegionSimple(1, 1, "test update", FONT_NORMAL_COLOR_INDEX, FONT_BG_COLOR_INDEX);
    OSD_Enable(1);
}

int show_msg(int *ui_handle, int msg_type, int line, int row, const char *msg) {
    int forecolor = FONT_NORMAL_COLOR_INDEX;
    int bgcolor = FONT_BG_COLOR_INDEX;

    if (msg_type == 0) {
        forecolor = FONT_NORMAL_COLOR_INDEX;
    } else if (msg_type == 1) {
        forecolor = FONT_HILIGHT_COLOR_INDEX;
    }

    if (*ui_handle < 0) {
		OSD_CleanScreen(NULL,0);
        *ui_handle = OSD_InitialRegionSimple(line, row, (char *)msg, forecolor, FONT_BG_COLOR_INDEX);
    } else {
        OSD_UpdateRegionContentSimple(*ui_handle, (char *)msg, forecolor,FONT_BG_COLOR_INDEX);
    }

    return 0;
}

int show_title_msg(int msg_type, const char *msg) {
    return show_msg(&gTitleMsgHandle, msg_type, 0, 100, msg);
}

int show_update_msg(int msg_type, const char *msg) {
    return show_msg(&gUpdateMsgHandle, msg_type, 3, 100, msg);
}

#define CLOCKS_PER_SECOND (1000000)
int show_update_time(unsigned int tm_lapse) {
    char msg_buf[256];

    tm_lapse = tm_lapse / CLOCKS_PER_SECOND;
    sprintf(msg_buf, "Time lapse: %02d:%02d:%02d", tm_lapse / 3600, tm_lapse / 60, tm_lapse % 60);
    return show_msg(&gUpdateTimeHandle, 0, 5, 100, msg_buf);
}

#if 0
void fn(void)
{
	unsigned char buf[100];
	int i;
	serial_puts("\nenter fn\n");
	memset(buf, 0, sizeof(buf));
	int len = uart_ports_read(DEVICE_UART_PORT_1, buf, 10);
	if(len > 0)
		serial_puts("\nlen > 0\n");
	
	for(i=0; i<len; i++)
		serial_putc(buf[i]);
//	destory_timer(TIMERA_INDEX, fn);
}
#endif

int main(int argc, char *argv[])
{
	unsigned int tm_start = 0, tm_lapse = 0;

	update_ctrl_t update_ctrl;
	serial_init(CONSOLE_CHANNEL_DEV);
	serial_puts("serial uart port 0 init success!\n");
	
	serial_puts("init spi flash!\n");
	init_spi_flash();

	serial_puts("Power on.\n");
	power_on_aml();
	serial_puts("Init Panel.\n");
	panel_init();
	serial_puts("Init Vpp.\n");
	init_vpp();

	init_osd();
	show_title_msg(0, "Updating...");

    serial_puts("panel_resume.\n");
	panel_resume();

	serial_puts("Init PWM.\n");
    pwm_init();
	
	init_update_ctrl_t(&update_ctrl);

	int ret = 1;

#if 0
	uart_ports_open(DEVICE_UART_PORT_1);

	create_timer(TIMERA_INDEX, TIMER_TICK_1MS, 10, fn); //10ms
#endif

	show_update_msg(0, "starting to update fbc.");

	tm_start = OSTimeGet();
	show_update_time(0);

	do{
		update_ctrl.show_update_msg = show_update_msg;
		ret = handle_cmd(&update_ctrl);

		tm_lapse = OSTimeGet() - tm_start;
		show_update_time(tm_lapse);
	} while(!ret);

	mdelay(1000);
	show_update_msg(0, "Update done.");
	mdelay(1000);
	
	reboot(0);
	
	return 0;
}
