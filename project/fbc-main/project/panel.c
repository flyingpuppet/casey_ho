#include <string.h>
#include <panel.h>
#include <user_setting.h>
#include <gpio.h>
#include <project.h>
#include <vpp_api.h>

int project_id = 0;
int customer_ptn = 0;
extern "C" int printf(const char *__fmt, ...);

panel_config_t panel_aml = {
    .output_mode = OUTPUT_LVDS,
    .lvds_timing = TIMING_1920x1080P60,
    .vx1_timing = TIMING_3840x2160P60,

    .format = PANEL_NORMAL,

    .reverse = 0,
    .scaler = 0,

    .clk = 0x63,
    .repack = 0,
    .odd_even = 0,
    .hv_invert = 0,
    .lsb_first = 0,
    .pn_swap = 0,
    .ports = 1,
    .bit_size = 0,
    .b_select = 0,
    .g_select = 1,
    .r_select = 2,
    .reg_de_exten = 0,
    .reg_blank_align = 0,
    .lvds_swap = 7,
    .clk_pin_swap = 0,

    .bl_inverter = 0,

    .lane_num = 8,
    .byte_num = 4,
    .region_num = 2,
    .color_fmt = 4,

    .pwm_duty =128,
    .pwm_hz = 120,

    .panel_power_on_delay = 0,
    .panel_power_off_delay = 0,
    .pwm_enable_delay = 0,
    .pwm_disable_delay = 0,
    .clock_enable_delay = 0,
    .clock_disable_delay = 0,
    .backlight_power_on_delay = 0,
    .backlight_power_off_delay = 0,


    .ManufactureID = {0x05,0xAc},
	.ProductID = {0xff,0xff},
	.SerialNumber = {0xff,0xff,0xff,0xff},
	.ManufactureDate = {0x00,0x19},
	.ChipID = {0xfb,0x0c},
	.PanelInfo = 0x03,
	.ThreeDinfo = 0x04,
	.SpecicalInfo = 0x05
};

panel_config_t panel_aml_vb1_3B = {
    .output_mode = OUTPUT_VB1,
    .lvds_timing = TIMING_1920x1080P60,
    .vx1_timing = TIMING_3840x2160P60,

    .format = PANEL_YUV420,

    .reverse = 0,
    .scaler = 0,

    .clk = 0x63,
    .repack = 1,
    .odd_even = 0,
    .hv_invert = 0,
    .lsb_first = 0,
    .pn_swap = 0,
    .ports = 1,
    .bit_size = 0,
    .b_select = 0,
    .g_select = 1,
    .r_select = 2,
    .reg_de_exten = 0,
    .reg_blank_align = 0,
    .lvds_swap = 7,
    .clk_pin_swap = 0,

    .bl_inverter = 1,

    .lane_num = 8,
    .byte_num = 3,
    .region_num = 2,
    .color_fmt = 4,

    .pwm_duty =128,
    .pwm_hz = 120,

    .panel_power_on_delay = 0,
    .panel_power_off_delay = 0,
    .pwm_enable_delay = 0,
    .pwm_disable_delay = 0,
    .clock_enable_delay = 0,
    .clock_disable_delay = 0,
    .backlight_power_on_delay = 0,
    .backlight_power_off_delay = 0
};

panel_config_t panel_aml_vb1_4B = {
    .output_mode = OUTPUT_VB1,
    .lvds_timing = TIMING_1920x1080P60,
    .vx1_timing = TIMING_3840x2160P60,

    .format = PANEL_YUV420,

    .reverse = 0,
    .scaler = 0,

    .clk = 0x63,
    .repack = 1,
    .odd_even = 0,
    .hv_invert = 0,
    .lsb_first = 0,
    .pn_swap = 0,
    .ports = 1,
    .bit_size = 0,
    .b_select = 0,
    .g_select = 1,
    .r_select = 2,
    .reg_de_exten = 0,
    .reg_blank_align = 0,
    .lvds_swap = 7,
    .clk_pin_swap = 0,

    .bl_inverter = 1,

    .lane_num = 8,
    .byte_num = 4,
    .region_num = 2,
    .color_fmt = 4,

    .pwm_duty =128,
    .pwm_hz = 120,

    .panel_power_on_delay = 0,
    .panel_power_off_delay = 0,
    .pwm_enable_delay = 0,
    .pwm_disable_delay = 0,
    .clock_enable_delay = 0,
    .clock_disable_delay = 0,
    .backlight_power_on_delay = 0,
    .backlight_power_off_delay = 0
};

panel_config_t panel_aml_vb1_4k1k_4B = {
    .output_mode = OUTPUT_VB1,
    .lvds_timing = TIMING_1920x1080P60,
    .vx1_timing = TIMING_4kx1kP120_3D_SG,

    .format = PANEL_YUV420,

    .reverse = 0,
    .scaler = 0,

    .clk = 0x63,
    .repack = 1,
    .odd_even = 0,
    .hv_invert = 0,
    .lsb_first = 0,
    .pn_swap = 0,
    .ports = 1,
    .bit_size = 0,
    .b_select = 0,
    .g_select = 1,
    .r_select = 2,
    .reg_de_exten = 0,
    .reg_blank_align = 0,
    .lvds_swap = 7,
    .clk_pin_swap = 0,

    .bl_inverter = 1,

    .lane_num = 8,
    .byte_num = 4,
    .region_num = 2,
    .color_fmt = 4,

    .pwm_duty =128,
    .pwm_hz = 120,

    .panel_power_on_delay = 0,
    .panel_power_off_delay = 0,
    .pwm_enable_delay = 0,
    .pwm_disable_delay = 0,
    .clock_enable_delay = 0,
    .clock_disable_delay = 0,
    .backlight_power_on_delay = 0,
    .backlight_power_off_delay = 0
};

panel_config_t panel_aml_vb1_4B_1r = {
    .output_mode = OUTPUT_VB1,
    .lvds_timing = TIMING_1920x1080P60,
    .vx1_timing = TIMING_3840x2160P60,

    .format = PANEL_YUV420,

    .reverse = 0,
    .scaler = 0,

    .clk = 0x63,
    .repack = 1,
    .odd_even = 0,
    .hv_invert = 0,
    .lsb_first = 0,
    .pn_swap = 0,
    .ports = 1,
    .bit_size = 0,
    .b_select = 0,
    .g_select = 1,
    .r_select = 2,
    .reg_de_exten = 0,
    .reg_blank_align = 0,
    .lvds_swap = 7,
    .clk_pin_swap = 0,

    .bl_inverter = 1,

    .lane_num = 8,
    .byte_num = 4,
    .region_num = 1,
    .color_fmt = 4,

    .pwm_hz = 120,

    .panel_power_on_delay = 0,
    .panel_power_off_delay = 0,
    .pwm_enable_delay = 0,
    .pwm_disable_delay = 0,
    .clock_enable_delay = 0,
    .clock_disable_delay = 0,
    .backlight_power_on_delay = 0,
    .backlight_power_off_delay = 0
};

#define panel_power(id,action) \
    switch(id){ \
        case 0: \
	case 1: \
	case 2: \
	case 3: \
	case 4: \
        case 0x101a: \
        case 0x101b: \
            panel_power_##action##_aml(); break; \
        default: break; \
    }
#define backlight_power(id,action) \
    switch(id){ \
        case 0: \
	case 1: \
	case 2: \
	case 3: \
	case 4: \
        case 0x101a: \
        case 0x101b: \
            backlight_power_##action##_aml(); break; \
        default: break; \
    }



panel_config_t *panel_param;

static void get_panel_by_id(int id)
{
    switch(id) {
    case 0:
        panel_param = &panel_aml;
        printf("the current panel param is for aml.\n");
        break;
    case 1:
        panel_param = &panel_aml_vb1_3B;
        printf("the current panel param is for aml vb1 3 Byte.\n");
        break;
    case 2:
        panel_param = &panel_aml_vb1_4B;
        printf("the current panel param is for aml vb1 4 Byte.\n");
        break;
    case 3:
        panel_param = &panel_aml_vb1_4k1k_4B;
        printf("the current panel param is for aml vb1 4 Byte.\n");
        break;
    case 4:
        panel_param = &panel_aml_vb1_4B_1r;
        printf("the current panel param is for aml vb1 4 Byte 1 region.\n");
        break;

    default:
        panel_param = &panel_aml;
        printf("the project_id is undefined, using default panel param!\n");
        break;
    }
}

vpu_outputmode_t get_output_mode(void)
{
    return panel_param->output_mode;
}

vpu_timing_t get_timing_mode(void)
{
    vpu_timing_t curr_timing;
    vpu_outputmode_t out_mode;

    out_mode = get_output_mode();

    if(out_mode == OUTPUT_LVDS) {
        curr_timing = panel_param->lvds_timing;
        printf("the outputmode is lvds, the current timing is %d.\n",curr_timing);
    } else if(out_mode == OUTPUT_VB1) {
        curr_timing = panel_param->vx1_timing;
        printf("the outputmode is vx1, the current timing is %d.\n",curr_timing);
    } else {
        printf("the outputmode is error, using default timing!\n");
        curr_timing = panel_param->lvds_timing;
    }

    return curr_timing;
}

#ifdef IN_FBC_MAIN_CONFIG
 extern void sleep(int us);
#else
void sleep(int us){
	int n= us*(80/3);
	while(n--);
}
#endif

void mdelay(int ms)
{
    sleep(1000*ms);
}

void power_on_aml(void)
{
    *P_PREG_PAD_GPIO0_EN_N &= (~(1<<1));
    *P_PREG_PAD_GPIO0_O |= (1<<1);
}

void power_off_aml(void)
{
    *P_PREG_PAD_GPIO0_EN_N &= (~(1<<1));
    *P_PREG_PAD_GPIO0_O &= (~(1<<1));
}

void panel_power_on_aml(void)
{
    *P_PREG_PAD_GPIO3_EN_N &= (~(1<<5));
    *P_PREG_PAD_GPIO3_O |= (1<<5);
}

void panel_power_off_aml(void)
{
    *P_PREG_PAD_GPIO3_EN_N &= (~(1<<5));
    *P_PREG_PAD_GPIO3_O &= (~(1<<5));
}

void backlight_power_on_aml(void)
{
    *P_PREG_PAD_GPIO3_EN_N &= (~(1<<12));
    *P_PREG_PAD_GPIO3_O &= (~(1<<12));
}

void backlight_power_off_aml(void)
{
    *P_PREG_PAD_GPIO3_EN_N &= (~(1<<12));
    *P_PREG_PAD_GPIO3_O |= (1<<12);
}

void local_dimming_disable(void)
{
    *P_PREG_PAD_GPIO3_EN_N &= (~(1<<4));
    *P_PREG_PAD_GPIO3_O &= (~(1<<4));
}

void set_led_onoff(unsigned char vcValue)
{
    *P_PERIPHS_PIN_MUX_0 &=(~(1<<3));
    *P_PERIPHS_PIN_MUX_0 &=(~(1<<26));
    *P_PREG_PAD_GPIO0_EN_N &= (~(1<<3));
    if(vcValue)
    {
        *P_PREG_PAD_GPIO0_O |= (1<<3);
    }
    else
    {
	    *P_PREG_PAD_GPIO0_O &= (~(1<<3));
    }
}

int panel_suspend(void)
{
    backlight_power(project_id, off);
    mdelay(panel_param->backlight_power_off_delay);
    mdelay(panel_param->clock_disable_delay);
    mdelay(panel_param->pwm_disable_delay);
	panel_power(project_id, off);

    return 0;
}

int panel_resume(void)
{
    panel_power(project_id, on);
    mdelay(panel_param->panel_power_on_delay);
    mdelay(panel_param->pwm_enable_delay);
    mdelay(panel_param->clock_enable_delay);
    backlight_power(project_id, on);

    return 0;
}

static void panel_backlight_power(char val)
{
	if(0 == val)
	{
		backlight_power(project_id, off);
	}else
	{
		backlight_power(project_id, on);
	}
}


void panel_init(void)
{
    int ret = 0;

#ifdef IN_FBC_MAIN_CONFIG
    project_id = read_project_id();
#else
	project_id = PROJECT_ID;

#endif
	//printf("current project_id is %d\n",project_id);
    get_panel_by_id(project_id);
    local_dimming_disable();
#ifdef IN_FBC_MAIN_CONFIG
	register_backlight_func(panel_backlight_power);
#endif
}


