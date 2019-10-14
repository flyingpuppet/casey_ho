#include <osd.h>
#include <fonts.h>
#include <common.h>

static const int nRGBA[16][4] ={
                              {64,64,80,110},
                              {0,0,192,110},
                              {0,192,0,110},
                              {0,192,192,110},
                              {192,0,0,110},
                              {192,0,192,110},
                              {192,192,0,110},
                              {192,192,192,110},
                              {192,224,192,128},
                              {192,224,32,128},
                              {192,32,192,128},
                              {192,0,32,128},
                              {0,192,224,128},
                              {0,192,32,128},
                              {0,32,192,128},
                              {0,0,0,128}};
                              
static unsigned char colors[]={0x0f, 0x1f, 0x2f, 0x3f, 0x4f, 0x5f, 0x6f, 0x7f, 0x8f};

void init_osd(void)
{
  int i;
  printf("OSD_Enable(0).\n");
  OSD_Enable(0);
  printf("OSD_Initial.\n");
  OSD_Initial(1920, 1080, 0, 60, 1919, 1019);
  printf("OSD_ConfigFonts.\n");
  OSD_ConfigFonts(104, 30, 30, sosd_font_lib_lut, 1);
  printf("OSD_SetColor.\n");
  for (i=0;i<16;i++)
    OSD_SetColor(i, nRGBA[i][0], nRGBA[i][1], nRGBA[i][2], nRGBA[i][3]);
  printf("OSD_SetBackground.\n");
  OSD_SetBackground(1, 15);
  printf("OSD_SetSpacing.\n");
  OSD_SetSpacing(4,4,4,4);
  printf("OSD_Enable(1).\n");
  OSD_Enable(1);
  printf("OSD_InitialRegionSimple.\n");
  OSD_InitialRegionSimple(2, 120, "Hello World", 4, 15);
  printf("OSD_InitialRegion.\n");
  OSD_InitialRegion (4, 120, "Test Str", colors);
  printf("OSD test done.\n");
}