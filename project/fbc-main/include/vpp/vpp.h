#ifndef VPP_H
#define VPP_H
#include <cmd.h>
#include <panel.h>
#include <vpp_api.h>
#define VPU_VER "Ref.2014/12/22"

typedef enum vpu_lutidx_e {
    GAMMA_R0 = 0,
    GAMMA_G0,
    GAMMA_B0,
    GAMMA_R1,
    GAMMA_G1,
    GAMMA_B1,
    DEMURE_BLREF_ODD_TABLE = 0x10,
    DEMURE_R_GAMMA_ODD_TABLE,
    DEMURE_R_DE_GAMMA_ODD_TABLE,
    DEMURE_LU_COEFF_ODD_TABLE,
    DEMURE_G_GAMMA_ODD_TABLE,
    DEMURE_G_DE_GAMMA_ODD_TABLE,
    DEMURE_B_GAMMA_ODD_TABLE,
    DEMURE_B_DE_GAMMA_ODD_TABLE,
    DEMURE_BLREF_EVEN_TABLE,
    DEMURE_R_GAMMA_EVEN_TABLE,
    DEMURE_R_DE_GAMMA_EVEN_TABLE,
    DEMURE_G_GAMMA_EVEN_TABLE,
    DEMURE_G_DE_GAMMA_EVEN_TABLE,
    DEMURE_B_GAMMA_EVEN_TABLE,
    DEMURE_B_DE_GAMMA_EVEN_TABLE,
    DEMURE_LU_COEFF_EVEN_TABLE,
    OSD_FRONT_RAM = 0X20,
    OSD_CHAR_RAM,
    CM2_DATA_RAM,
    VPU_LUTIDX_MAX,
} vpu_lutidx_t;

typedef struct vpu_timing_table_s {
    vpu_timing_t timing;
    unsigned int hactive;
    unsigned int vactive;
    unsigned int htotal;
    unsigned int vtotal;
} vpu_timing_table_t;

typedef enum vpu_source_e {
    SOURCE_NULL = 0,
    SOURCE_AV,
    SOURCE_HDMI,
    SOURCE_MAX,
} vpu_source_t;

typedef enum vpu_gammamod_e {
    GAMMA_BEFORE = 0,   //0:before osd blender;
    GAMMA_AFTER,        //1:after osd blender
} vpu_gammamod_t;

typedef enum vpu_gammacolor_e {
    GAMMA_R = 0,
    GAMMA_G,
    GAMMA_B,
    GAMMA_MAX,
} vpu_gammacolor_t;
typedef enum vpu_wbsel_e {
    WBSEL_R = 0,
    WBSEL_G,
    WBSEL_B,
} vpu_wbsel_t;
typedef enum vpu_wboffset_pos_e {
    WBOFFSET_PRE = 0,
    WBOFFSET_POST,
} vpu_wboffset_pos_t;

typedef enum vpu_gammalever_e {
    GAMMA_LEVER0 = 0,
    GAMMA_LEVER1,
    GAMMA_LEVER2,
    GAMMA_LEVERMAX,
} vpu_gammalever_t;

#define GAMMA_ITEM 257
typedef enum vpu_srcif_mode_e {
    SRCIF_PURE_HARDWARE = 0,
    SRCIF_HYBRID,
    SRCIF_PURE_SOFTWARE,
} vpu_srcif_mode_t;

typedef enum metal_revision_e{
	REV_A = 0,
	REV_B,
	REV_C,
}metal_revision_t;

typedef struct vpu_message_s {
    fbc_command_t cmd_id;
    unsigned int parameter1;
    unsigned int parameter2;
    unsigned int parameter3;
} vpu_message_t;

typedef struct vpu_debug_s {
    char *name;
    vpu_message_t vpu_para;
} vpu_debug_t;

//PQ TOOL no release
typedef struct vpu_cm2_s {
    unsigned short rw_flag;//0:read;1:write
    unsigned int addr;
    unsigned int data[5];
} vpu_cm2_t;


extern void init_vpp(void);
#if 0
extern void vpu_factory_init(void);
#endif


extern void init_display(void);
extern int get_ic_version(void);
extern int get_metal_revision(void);

//------------------------------------------------------------------------------
// LVDS/VX1
//------------------------------------------------------------------------------

//#define USE_VX1_TX

#define LVDS_PORTS   1
#define VX1_LANE_NUM 8
#define VX1_BYTE_NUM 4
#define VX1_COLOR_FORMAT 4  //huaxing 55#
#define VX1_REGION_NUM 2    //huaxing 55#
#define FBC_TOOL_EN  1
#define DEMURA_DEBUG_DATA_NUM 200

#endif
