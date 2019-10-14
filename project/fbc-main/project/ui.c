#include <osd.h>
#include <fonts.h>
#include <common.h>
#include <log.h>
#include <listop.h>
#include <inputdata.h>
#include <key_const.h>
#include <task.h>
#include <input.h>
#include <malloc.h>
#include <command.h>
#include <task_priority.h>
#include <cmd.h>
#include <panel.h>
#include <timer.h>
#include <customer_key_conf.h>

extern unsigned int audio_handle_cmd(unsigned char *s, int *rets);
extern int sprintf(char * buffer, const char *__fmt, ...);

static LIST_HEAD(osd_input_data_list);

static int osd_init = 0;
static int logo_handle[LOGO_V_FONTS] = {-1};

#define KEY_CMD_MAX             7

typedef struct key_cmd {
    char * key_name;
    int key_value;
} key_cmd_t;

static const key_cmd_t options[KEY_CMD_MAX] = {
    {"up", AMLKEY_UP},
    {"down", AMLKEY_DOWN},
    {"menu", AMLKEY_MENU},
    {"left", AMLKEY_LEFT},
    {"right", AMLKEY_RIGHT},
    {"exit", AMLKEY_EXIT},
    {"enter", AMLKEY_ENTER},
};

int do_key_transfer(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    int i;
    int val = NULL;
    printf("test key argv = %s.\n", argv[1]);
    if(argc != 2) {
        return -1;
    }

    for(i=0; i<KEY_CMD_MAX; i++) {
        if((strcmp(argv[1], options[i].key_name)) == 0) {
            val = options[i].key_value;
            AddIputdataToTaskList(INPUT_REMOTE , val);
            return 0;
        }
    }
    return -1;
}

static char TAG[] = "ui";

typedef struct menu_item {
    int id;
    int handle;
    char * name;
    int line;
    int col;
    struct menu_item * up;
    struct menu_item * down;
    struct menu_item * next;
    struct menu_item * pre;
    int (* key_process)(struct menu_item * item, int key);
    int (* execute)(struct menu_item * item);
} menu_item_t;

typedef struct menu_item_value {
    int handle;
    char * name;
    int line;
    int col;
} menu_item_value_t;

int process_menu(struct menu_item * item, int key);
int do_test1(struct menu_item * item);
int do_test2(struct menu_item * item);
int adjust_brightness(struct menu_item * item);
int adjust_contrast(struct menu_item * item);
int adjust_volume(struct menu_item * item);
int adjust_mute(struct menu_item * item);
void show_menu();
void hide_menu();
void invalidate(struct menu_item * last, struct menu_item * curr);
void invalidateValue(struct menu_item * item,int key);
void invalidateInitValue();

void init_logo_osd(void);

#define MENU_START_LINE 0
#define MENU_START_POSITION 0

menu_item_t menu_screen;
menu_item_t menu_test1;
menu_item_t menu_test2;
menu_item_t menu_brightness;
menu_item_t menu_contrast;
menu_item_t menu_volume;
menu_item_t menu_mute;

menu_item_value_t menu_item_value[7];

menu_item_t menu_screen = {0, -1, "main menu 1234567890", MENU_START_LINE+0, MENU_START_POSITION+0, NULL, NULL, &menu_test1, NULL, &process_menu, NULL};
menu_item_t menu_test1 = {1, -1, "HV FLIP", MENU_START_LINE+1, MENU_START_POSITION+128, &menu_mute, &menu_test2, NULL, &menu_screen, &process_menu, &do_test1};
menu_item_t menu_test2 = {2, -1, "Show logo", MENU_START_LINE+2, MENU_START_POSITION+128, &menu_test1, &menu_brightness, NULL, &menu_screen, &process_menu, &do_test2};
menu_item_t menu_brightness = {3, -1, "adjust brightness", MENU_START_LINE+3, MENU_START_POSITION+128, &menu_test2, &menu_contrast, NULL, &menu_screen, &process_menu, NULL};
menu_item_t menu_contrast = {4, -1, "adjust contrast", MENU_START_LINE+4, MENU_START_POSITION+128, &menu_brightness, &menu_volume, NULL, &menu_screen, &process_menu, NULL};
menu_item_t menu_volume = {5, -1, "adjust volume", MENU_START_LINE+5, MENU_START_POSITION+128, &menu_contrast, &menu_mute, NULL, &menu_screen, &process_menu, NULL};
menu_item_t menu_mute = {6, -1, "mute", MENU_START_LINE+6, MENU_START_POSITION+128, &menu_volume, &menu_test1, NULL, &menu_screen, &process_menu, NULL};

menu_item_value_t menu_item_value[7] = {
    {-1,     "", MENU_START_LINE+0, MENU_START_POSITION},
    {-1,     "", MENU_START_LINE+1, MENU_START_POSITION},
    {-1,     "", MENU_START_LINE+2, MENU_START_POSITION},
    {-1,     "", MENU_START_LINE+3, MENU_START_POSITION},
    {-1,     "", MENU_START_LINE+4, MENU_START_POSITION},
    {-1,     "", MENU_START_LINE+5, MENU_START_POSITION},
    {-1, "off", MENU_START_LINE+6, MENU_START_POSITION},
};

static menu_item_t * current_menu_item = &menu_screen;
static menu_item_t * last_menu_item = &menu_screen;

int osd_task_id;
static int logo_task_id;
static int logo_timer_id;

int osd_task_handle(int task_id, void * param)
{
    int cmd;
    list_t *plist = list_dequeue(&osd_input_data_list);
    LOGI(TAG,"run inputData task %d from input 0x%x\n", task_id, plist);
    if (plist) {
        INPUT_LIST *input_list = list_entry(plist, INPUT_LIST, list);
        if (input_list) {
            cmd = input_list->input_data.data;
            free(input_list);
            if(current_menu_item != NULL) {
                return current_menu_item->key_process(current_menu_item, cmd);
            }
        }
    }
    return 0;

}

void hide_logo();

int logo_task_handle(int task_id, void * param)
{
    release_timer(logo_timer_id);
    hide_logo();
    return 0;
}

//static int volume;
int process_menu(struct menu_item * item, int key)
{
    if(NULL == item) {
        return -1;
    }

    LOGD(TAG, "item id is %d, key is %d.\n", item->id, key);

    switch(key) {
    case AMLKEY_MENU:
        if(item->id == menu_screen.id) {
            if(NULL != item->next) {
                last_menu_item = item;
                current_menu_item = item->next;
                invalidate(last_menu_item, current_menu_item);
                invalidateInitValue();
                break;
            }
        }
        if(NULL != item->pre) {
            last_menu_item = item;
            current_menu_item = item->pre;

            invalidate(last_menu_item, current_menu_item);
        }
        break;
    case AMLKEY_UP:
        if(NULL != item->up) {
            last_menu_item = item;
            current_menu_item = item->up;

            invalidate(last_menu_item, current_menu_item);
        }
        break;
    case AMLKEY_DOWN:
        if(NULL != item->down) {
            last_menu_item = item;
            current_menu_item = item->down;

            invalidate(last_menu_item, current_menu_item);
        }
        break;
    case AMLKEY_ENTER:
        if(item->id == menu_brightness.id || item->id == menu_contrast.id || item->id == menu_volume.id || item->id == menu_mute.id)
            break;
        if(NULL != item->execute) {
            (*item->execute)(item);
            break;
        }
        if((NULL != item->next)&&(item->id != menu_screen.id)) {
            last_menu_item = item;
            current_menu_item = item->next;

            invalidate(last_menu_item, current_menu_item);
        }
        break;
    case AMLKEY_EXIT:
        last_menu_item = item;
        current_menu_item = &menu_screen;

        invalidate(last_menu_item, current_menu_item);
        break;
    case AMLKEY_RIGHT:
        if(item->id == menu_brightness.id || item->id == menu_contrast.id || item->id == menu_volume.id || item->id == menu_mute.id) {
            //(*item->execute)(item);
            invalidateValue(item,AMLKEY_VOL_PLUS);
        }
        break;
    case AMLKEY_LEFT:
        if(item->id == menu_brightness.id || item->id == menu_contrast.id || item->id == menu_volume.id || item->id == menu_mute.id) {
            //(*item->execute)(item);
            invalidateValue(item,AMLKEY_VOL_MINUS);
        }
        break;
    case AMLKEY_VOL_PLUS:
        //volume = audio_handle_cmd();
        //volume ++;
        //audio_handle_cmd(unsigned char * s,int * rets)
        break;
    case AMLKEY_VOL_MINUS:
        break;
    default:
        break;
    }

    return 0;

}

void invalidateInitValue()
{
    invalidateValue(&menu_brightness,NULL);
    invalidateValue(&menu_contrast,NULL);
    invalidateValue(&menu_volume,NULL);
    invalidateValue(&menu_mute,NULL);
}

void invalidateValue(struct menu_item * item,int key)
{
    char  toDisplayvalue[20];
    int curValue;
    if(item == NULL)
        return;
    LOGD(TAG,"enable osd fresh item value,curr item id is %d\n",item->id);
    printf("enable osd fresh item value,curr item id is %d\n",item->id);

    //get
    if(item->id == menu_brightness.id) {
        curValue = RunCommand(VPU_CMD_BRIGHTNESS | VPU_CMD_READ,NULL)[0];
    } else if(item->id == menu_contrast.id) {
        curValue = RunCommand(VPU_CMD_CONTRAST | VPU_CMD_READ,NULL)[0];
    } else if(item->id == menu_volume.id) {
        curValue = RunCommand(AUDIO_CMD_GET_VOLUME_BAR,NULL)[0];
        //RunCommand(AUDIO_CMD_GET_MASTER_VOLUME,NULL)[0];
    } else if(item->id == menu_mute.id) {
        curValue = RunCommand(AUDIO_CMD_GET_MUTE,NULL)[0];
    }

    //change
    if(key == AMLKEY_VOL_PLUS) {
        curValue++;
        if(item->id == menu_mute.id) {
            if(curValue == 2) curValue = 0;
        } else {
            if(curValue >= 255) curValue = 255;
        }
    } else if(key == AMLKEY_VOL_MINUS) {
        curValue--;
        if(item->id == menu_mute.id) {
            if(curValue == -1) curValue = 1;
        } else {
            if(curValue <= 0) curValue = 0;
        }
    }

    //set
    if(item->id == menu_brightness.id) {
        RunCommand(VPU_CMD_BRIGHTNESS,&curValue);
    } else if(item->id == menu_contrast.id) {
        RunCommand(VPU_CMD_CONTRAST,&curValue);
    } else if(item->id == menu_volume.id) {
        RunCommand(AUDIO_CMD_SET_VOLUME_BAR,&curValue);
        //RunCommand(AUDIO_CMD_SET_MASTER_VOLUME,&curValue);
    } else if(item->id == menu_mute.id) {
        RunCommand(AUDIO_CMD_SET_MUTE,&curValue);
    }

    if(item->id == menu_mute.id) {
        if(curValue == 1) {
            sprintf(toDisplayvalue,"%s","on");
        } else {
            sprintf(toDisplayvalue,"%s","off");
        }
    } else {
        sprintf(toDisplayvalue,"%d",curValue);
    }

    printf("_toDisplayValue: %d\n",toDisplayvalue);

    if(menu_item_value[item->id].handle >0)
        OSD_UpdateRegionContentSimple(menu_item_value[item->id].handle, toDisplayvalue, key != NULL ? FONT_HILIGHT_COLOR_INDEX : FONT_NORMAL_COLOR_INDEX, FONT_BG_COLOR_INDEX);
}

void invalidate(struct menu_item * last, struct menu_item * curr)
{
    if((NULL == last)||(NULL == curr)) {
        return;
    }

    if(curr->id == last->id) {
        return;
    }

    if(curr->id == menu_screen.id) {
        LOGD(TAG,"disable osd fresh curr item id is %d, last id is %d.\n", curr->id, last->id);
        hide_menu();
        printf("disable osd fresh curr item id is %d, last id is %d.\n", curr->id, last->id);
        return;
    } else if(last->id == menu_screen.id) {
        show_menu();
        LOGD(TAG,"enable osd fresh curr item id is %d, last id is %d.\n", curr->id, last->id);
        printf("enable osd fresh curr item id is %d, last id is %d.\n", curr->id, last->id);
        return;
    } else {
        LOGD(TAG,"osd fresh curr item id is %d, last id is %d.\n", curr->id, last->id);
        if (last->handle < 0) {
            last->handle = OSD_InitialRegionSimple(last->line, 0, last->name, FONT_NORMAL_COLOR_INDEX, FONT_BG_COLOR_INDEX);
            //last->handle = OSD_InitialRegionSimple(menu_item_value[last->id].line, 0, menu_item_value[last->id].name, FONT_NORMAL_COLOR_INDEX, FONT_BG_COLOR_INDEX);
        } else {
            OSD_UpdateRegionContentSimple(last->handle, NULL, FONT_NORMAL_COLOR_INDEX, FONT_BG_COLOR_INDEX);
            OSD_UpdateRegionContentSimple(menu_item_value[last->id].handle, NULL, FONT_NORMAL_COLOR_INDEX, FONT_BG_COLOR_INDEX);
        }
        if (curr->handle < 0) {
            curr->handle = OSD_InitialRegionSimple(curr->line, 0, curr->name, FONT_HILIGHT_COLOR_INDEX, FONT_BG_COLOR_INDEX);
            //curr->handle = OSD_InitialRegionSimple(menu_item_value[curr->id].line, 0, menu_item_value[curr->id].name, FONT_HILIGHT_COLOR_INDEX, FONT_BG_COLOR_INDEX);
        } else {
            OSD_UpdateRegionContentSimple(curr->handle, NULL, FONT_HILIGHT_COLOR_INDEX, FONT_BG_COLOR_INDEX);
            OSD_UpdateRegionContentSimple(menu_item_value[curr->id].handle, NULL, FONT_HILIGHT_COLOR_INDEX, FONT_BG_COLOR_INDEX);
        }
        printf("osd fresh curr item id is %d, last id is %d.\n", curr->id, last->id);
    }
}

int do_test1(menu_item_t * item)
{
    if(NULL == item) {
        return -1;
    }
    LOGD(TAG,"do_test1 current item[%d] execute.\n", item->id);
    printf("do_test1 current item[%d] execute.\n", item->id);
    OSD_Enable(0);
    hide_menu();
    if(OSD_GetMirror() == 1) {
        OSD_SetMirror(0);
        OSD_ConfigFonts(FONT_NUM, FONT_WIDTH, FONT_HEIGHT, sosd_font_lib_lut, font_mapping, 1);
    } else if(OSD_GetMirror() == 0) {
        OSD_SetMirror(1);
        OSD_ConfigFonts(FONT_NUM, FONT_WIDTH, FONT_HEIGHT, sosd_font_lib_lut_hvflip, font_mapping, 1);
    }
    ///current_menu_item = &menu_screen;
    // = &menu_screen;
    show_menu();
    OSD_Enable(1);

    return 0;
}

int do_test2(menu_item_t * item)
{
    if(NULL == item) {
        return -1;
    }
    LOGD(TAG,"do_test2 current item[%d] execute.\n", item->id);
    printf("do_test2 current item[%d] execute.\n", item->id);



    hide_menu();
    init_logo_osd();
    current_menu_item = &menu_screen;
    last_menu_item = &menu_screen;

    return 0;
}

void init_osd(void);

void show_menu()
{
    if(0==osd_init) {
        init_osd();
    }

    OSD_CleanScreen(NULL, 0);

    if (menu_screen.handle<0)
        menu_screen.handle = OSD_InitialRegionSimple(menu_screen.line, menu_screen.col, menu_screen.name, FONT_NORMAL_COLOR_INDEX, FONT_BG_COLOR_INDEX);
    if (menu_test1.handle<0)
        menu_test1.handle = OSD_InitialRegionSimple(menu_test1.line, menu_test1.col, menu_test1.name, FONT_HILIGHT_COLOR_INDEX, FONT_BG_COLOR_INDEX);
    if (menu_test2.handle<0)
        menu_test2.handle = OSD_InitialRegionSimple(menu_test2.line, menu_test2.col, menu_test2.name, FONT_NORMAL_COLOR_INDEX, FONT_BG_COLOR_INDEX);
    if (menu_brightness.handle<0)
        menu_brightness.handle = OSD_InitialRegionSimple(menu_brightness.line, menu_brightness.col, menu_brightness.name, FONT_NORMAL_COLOR_INDEX, FONT_BG_COLOR_INDEX);
    if (menu_contrast.handle<0)
        menu_contrast.handle = OSD_InitialRegionSimple(menu_contrast.line, menu_contrast.col, menu_contrast.name, FONT_NORMAL_COLOR_INDEX, FONT_BG_COLOR_INDEX);
    if (menu_volume.handle<0)
        menu_volume.handle = OSD_InitialRegionSimple(menu_volume.line, menu_volume.col, menu_volume.name, FONT_NORMAL_COLOR_INDEX, FONT_BG_COLOR_INDEX);
    if (menu_mute.handle<0)
        menu_mute.handle = OSD_InitialRegionSimple(menu_mute.line, menu_mute.col, menu_mute.name, FONT_NORMAL_COLOR_INDEX, FONT_BG_COLOR_INDEX);

    char * menu_name[7] = {menu_screen.name,menu_test1.name,menu_test2.name,menu_brightness.name,menu_contrast.name,menu_volume.name,menu_mute.name};
    for(int i =0; i < sizeof(menu_item_value)/sizeof(menu_item_value[0]); i++) {
        if(menu_item_value[i].handle<0)
            menu_item_value[i].handle = OSD_InitialRegionSimple(menu_item_value[i].line, menu_item_value[i].col+700, menu_item_value[i].name, i == 1 ? FONT_HILIGHT_COLOR_INDEX : FONT_NORMAL_COLOR_INDEX, FONT_BG_COLOR_INDEX);
    }

    OSD_Enable(1);
}

void hide_menu()
{
    if (menu_screen.handle>=0) {
        OSD_RemoveRegion(menu_screen.handle);
        menu_screen.handle = -1;
    }
    if (menu_test1.handle>=0) {
        OSD_RemoveRegion(menu_test1.handle);
        menu_test1.handle = -1;
    }
    if (menu_test2.handle>=0) {
        OSD_RemoveRegion(menu_test2.handle);
        menu_test2.handle = -1;
    }
    if (menu_brightness.handle>=0) {
        OSD_RemoveRegion(menu_brightness.handle);
        menu_brightness.handle = -1;
    }
    if (menu_contrast.handle>=0) {
        OSD_RemoveRegion(menu_contrast.handle);
        menu_contrast.handle = -1;
    }
    if (menu_volume.handle>=0) {
        OSD_RemoveRegion(menu_volume.handle);
        menu_volume.handle = -1;
    }
    if (menu_mute.handle>=0) {
        OSD_RemoveRegion(menu_mute.handle);
        menu_mute.handle = -1;
    }

    for(int i = 0; i < sizeof(menu_item_value)/sizeof(menu_item_value[0]); i++) {
        if(menu_item_value[i].handle>=0) {
            OSD_RemoveRegion(menu_item_value[i].handle);
            menu_item_value[i].handle = -1;
        }
    }
    OSD_Enable(0);
}

void show_logo(unsigned line, unsigned position )
{
    for(int i=0; i<LOGO_V_FONTS; i++) {
        logo_handle[i] = OSD_InitialRegion(line+i,position,logo[i],logo_color[i]);
    }
    printf("show_logo.\n");
}

void hide_logo()
{
    OSD_Enable(0);
    for(int i=0; i<LOGO_V_FONTS; i++) {
        //printf("logo_handle[%d] is %d.\n ",i, logo_handle[i]);
        if(logo_handle[i]<0) {
            continue;
        }
        OSD_RemoveRegion(logo_handle[i]);
        logo_handle[i] = -1;
    }

    printf("hide_logo.\n");
}

void init_osd(void)
{

    int i;
    hide_logo();
    OSD_Enable(0);
    if(OUTPUT_LVDS == panel_param->output_mode) {
        OSD_Initial(1920,1080,60,60,1859,1019);
        OSD_SetFontScale(1, 1);
    } else if(OUTPUT_VB1 == panel_param->output_mode) {
        OSD_Initial(3840,2160,120,120,3719,2039);
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
    osd_init = 1;
    //OSD_CleanScreen(logo, 78);
    //OSD_Enable(1);
}

void init_logo_osd(void)
{
    int i;

    OSD_Enable(0);
    //OSD_Initial(1920, 1080, 725, 360, 1194, 719);
    //OSD_Initial(1920,1080,0,0,1919,1079);
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

    OSD_SetSpacing(0,0,0,0);
    if(OSD_GetMirror()==1) {
        OSD_ConfigFonts(LOGO_FONT_NUM, FONT_WIDTH, FONT_HEIGHT, sosd_font_lib_lut_logo_hvflip, font_mapping_logo, 1);
    } else if(OSD_GetMirror()==0) {
        OSD_ConfigFonts(LOGO_FONT_NUM, FONT_WIDTH, FONT_HEIGHT, sosd_font_lib_lut_logo, font_mapping_logo, 1);
    }

    for (i=0; i<LOGO_FONT_NUM; i++)
        OSD_SetFontCut(i, sosd_cut_table_logo[i]);
    for (i=0; i<16; i++)
        OSD_SetColor(i, nRGBA_logo[i][0], nRGBA_logo[i][1], nRGBA_logo[i][2], nRGBA_logo[i][3]);

    OSD_SetBackground(1, LOGO_BG_COLOR_INDEX);
    //Delay_ms(20);
    OSD_CleanScreen(NULL, 0);
    //Delay_ms(20);
    show_logo(12,705);
    OSD_Enable(1);
    osd_init = 0;
}



void init_ui(void)
{
#if 0
    OSD_CleanScreen(NULL, 0);
    OSD_InitialRegionSimple(0, 100, ":ABCDEFGHIJKLMNOPQRSTUVWXYZ", FONT_HILIGHT_COLOR_INDEX, FONT_BG_COLOR_INDEX);
    OSD_InitialRegionSimple(1, 100, ":abcdefghijklmnopqrstuvwxyz", FONT_NORMAL_COLOR_INDEX, FONT_BG_COLOR_INDEX);
    OSD_InitialRegionSimple(2, 100, ":0123456789,.+-*/!@#$^&()[]{}", FONT_NORMAL_COLOR_INDEX, FONT_BG_COLOR_INDEX);
#else
    osd_task_id = RegisterTask(osd_task_handle, NULL, 0, TASK_PRIORITY_OSD);
    RegisterInput(&osd_input_data_list, osd_task_id, INPUT_REMOTE|INPUT_SARADC, NULL);



#endif
    if(panel_param != NULL) {
        if(1==panel_param->reverse) {
            OSD_SetMirror(1);
        } else {
            OSD_SetMirror(0);
        }
        /*if(OUTPUT_LVDS == panel_param->output_mode)
        {
            OSD_Initial(1920,1080,0,0,1919,1079);
            OSD_SetFontScale(1, 1);
        }
        else if(OUTPUT_VB1 == panel_param->output_mode)
        {
            OSD_Initial(3840,2160,0,0,3839,2159);
            OSD_SetFontScale(2, 2);
        }*/
    }
    init_logo_osd();
    logo_task_id = RegisterTask(logo_task_handle, NULL, 0, TASK_PRIORITY_OSD);
    logo_timer_id = request_timer(logo_task_id,500);
}

//1:blue, 2:green, 4:red, 10:black
void osd_cover(int color)
{
    current_menu_item = &menu_screen;
    last_menu_item = &menu_screen;
    hide_menu();
    OSD_SetBackground(1,color);
    OSD_Enable(1);
}



int KeyFunc(unsigned int input_type,unsigned int customer_code,unsigned int key_value,unsigned int repeatstatus)
{
    if(customer_key_map[10][0] == key_value)
    {
        printf("KeyFunc enter suspend\n");
		//panel_power(read_project_id(), off);
		//panel_suspend();
        //reboot_sw(REBOOT_FLAG_SUSPEND);
    }
    return 0;
}



