#ifndef OSD_H
#define OSD_H

// 1. Global layout:

// canvas_width, canvas_height: whole OSD area which could be filled with background color
// region: OSD area can display characters
void OSD_Initial(unsigned canvas_width, unsigned canvas_height, unsigned region_x_start, unsigned region_y_start, unsigned region_x_end, unsigned region_y_end);
void OSD_CleanScreen(const unsigned short *text, int text_len);

// enable and disable OSD
void OSD_Enable(int enable);

// for each font, config paddings for left/right/top/bottom, used for character and line spacing
void OSD_SetSpacing(unsigned left, unsigned right, unsigned top, unsigned bottom);

// set background color used for areas not draw
void OSD_SetBackground(int on, unsigned char color_index);

#define OSD_3D_MODE_NORMAL 0
#define OSD_3D_MODE_LEFT_RIGHT 1
#define OSD_3D_MODE_TOP_BOM 2
#define OSD_3D_MODE_X_INTERLEAVE 3
#define OSD_3D_MODE_Y_INTERLEAVE 4
void OSD_Set3DMode(int mode);

// 2. Color API:
void OSD_SetColor(unsigned char index, unsigned char red, unsigned char green, unsigned char blue, unsigned alpha);

unsigned int OSD_GetColor(unsigned char index);

// 3. Font API:

// config fonts
void OSD_ConfigFonts(int number_fonts, unsigned width, unsigned height, const int *bitmaps, const unsigned char *map, int invert);

// change one font only
void OSD_SetFontBitmap(unsigned char index, unsigned char *bitmap); // implement later

// do not use most left and most right pixels in font, so the font width will be: width - pixels * 2
void OSD_SetFontCut(unsigned char index, unsigned char pixels);

// OSD only support x1/2 x1 and x2 for both vertical and horizontal
#define OSD_SCALE_HALF  0
#define OSD_SCALE_1X    1
#define OSD_SCALE_2X    2
void OSD_SetFontScale(int x_scale, int y_scale);

// 4. Character Ram API:
// Each line is composed by region(s), minimal gap between region = left
// padding + right padding + 10:

// position must be even, return handle >=0 when
// success; each char in string is index to fonts, each char in color array bits 7:4 =
// foreground color index, 3:0 = background color index
int OSD_InitialRegion(unsigned line, unsigned position, char *string, unsigned char *color_array);

// position must be even, return handle >=0 when
// success; each char in string is index to fonts,
// all string use same color as foreground color index and background color index
int OSD_InitialRegionSimple(unsigned line, unsigned position, char *string,
  unsigned char foreground_color_index, unsigned char background_color_index);

int get_string_width(char * string);

// each char in string is index to fonts, each char in color
// array bits 7:4 = foreground color index, 3:0 = background color index, if string is
// NULL, update color index array only, if color_index_array is NULL, update string only
void OSD_UpdateRegionContent (int handle, char *string, unsigned char *color_index_array);

// if string is NULL, update color only; if color_index>=16, update string only
void OSD_UpdateRegionContentSimple(int handle, char *string, unsigned char foreground_color_index,
  unsigned char background_color_index );

// clean and destroy a region
void OSD_RemoveRegion(int handle);

// calculate and return pixel width of one region
unsigned OSD_GetRegionWidth(int handle);

// set OSD to mirror mode(vertical mirror only)
void OSD_SetMirror(int enable);

//get OSD mirror mode(vertical mirror only)
int OSD_GetMirror(void);

#endif