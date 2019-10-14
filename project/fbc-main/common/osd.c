#include <string.h>
#include <malloc.h>
#include <common.h>
#include <sosd.h>
#include <log.h>

#define MAX_WIDTH 1920
#define MAX_HEIGHT 1080
#define MAX_COL_NUM 64
#define MAX_ROW_NUM 36
#define COL_IN_ROW 64
#define MAX_FONTS 224
#define DEF_FONT_HEIGHT 30
#define MAX_COLORS 16
#define MIN_PADDING 8

#define MAX_REGION_PER_LINE 6

//#define OSD_DEBUG
#define TAG "OSD"

typedef struct{
	unsigned short position;
	unsigned char color;
	unsigned char len;
	unsigned short *text;
} txt_region_t;

static txt_region_t txt_regions[MAX_ROW_NUM][MAX_REGION_PER_LINE];
static int row_offset[MAX_ROW_NUM+1];
static unsigned short text[MAX_ROW_NUM*COL_IN_ROW];
static int text_count;
static unsigned char text_map[256];
static int mirror_mode = 0;
static int line_spaceing = 0;
static int region_width = MAX_WIDTH;
static int region_height = MAX_HEIGHT;
static int font_height = DEF_FONT_HEIGHT;
static int max_line = MAX_ROW_NUM;
static int y_scale_factor = 1;
static int x_scale_factor = 1;

static void update_max_row(void)
{
	max_line = region_height /y_scale_factor / (font_height + line_spaceing);
	//printf("max_line is %d\n", max_line);
}

// 1. Global layout:
// canvas_width, canvas_height: whole OSD area which could be filled with background color
// region: OSD area can display characters
void OSD_Initial(unsigned canvas_width, unsigned canvas_height, unsigned region_x_start, unsigned region_y_start, unsigned region_x_end, unsigned region_y_end)
{
	sosd_config_canvas(canvas_width, canvas_height);
	sosd_config_region(region_x_start, region_y_start, region_x_end, region_y_end);
	region_height = region_y_end - region_y_start + 1;
	region_width = region_x_end - region_x_start + 1;
	update_max_row();
}

void OSD_CleanScreen(const unsigned short *txt, int txt_len)
{
	int i;

	if (txt)
		sosd_write_text(0, (unsigned short *)txt, txt_len);
	else{
		for (i=0;i<max_line;i++){
			text[i] = (sosd_get_line_return()<<8)|(sosd_getbackground()<<4)|sosd_getbackground();
			row_offset[i] = i;
		}
		text_count = row_offset[i-1]+1;
#ifdef OSD_DEBUG
	LOGD(TAG, "clean osd offset %d len %d\n", 0, text_count);
	printf("clean osd offset %d len %d data:\n", 0, text_count);
	for (i=0;i<text_count;i++)
		printf(" %02x", text[i]>>8);
	printf("\n");
#endif
		sosd_write_text(0, text, text_count);
	}
}

void OSD_SetMirror(int enable)
{
	mirror_mode = enable;	
}

int OSD_GetMirror(void)
{
	return mirror_mode;
}

void OSD_Enable(int enable)
{
	sosd_enable(enable);
}

void OSD_SetSpacing(unsigned left, unsigned right, unsigned top, unsigned bottom){
	sosd_config_padding(left, right, top, bottom);
	line_spaceing = top + bottom;
	update_max_row();
}

void OSD_SetBackground(int on, unsigned char color_index)
{
	sosd_setbackground(on, color_index);
}

void OSD_Set3DMode(int mode)
{
	sosd_config_3d_mode(mode);
}

// 2. Color API:
void OSD_SetColor(unsigned char index, unsigned char red, unsigned char green, unsigned char blue, unsigned alpha)
{
	sosd_config_color(index, red, green, blue, alpha);
}

unsigned int OSD_GetColor(unsigned char index)
{
	return sosd_get_color(index);
}

// 3. Font API:
void OSD_ConfigFonts(int number_fonts, unsigned width, unsigned height, const int *bitmaps, const unsigned char *map, int invert)
{
	int num_fonts = (number_fonts > MAX_FONTS) ? MAX_FONTS : number_fonts;
	int i;

	sosd_config_font_invert(invert);
	sosd_config_font_size(width, height);
	sosd_config_fonts(num_fonts, bitmaps);
	sosd_config_padding_fonts(num_fonts, bitmaps+((num_fonts-1)*width*height+31)/32);
	if (map){
		for (i=0;i<256;i++)
			text_map[i] = map[i];
	}
	else{
		for (i=0;i<256;i++)
			text_map[i] = i;
	}
	font_height = height;
	update_max_row();
}

void OSD_SetFontBitmap(unsigned char index, unsigned char *bitmap); // implement later

void OSD_SetFontCut(unsigned char index, unsigned char pixels)
{
	sosd_config_font_cut(index, pixels);
}

void OSD_SetFontScale(int x_scale, int y_scale) // 0: ½, 1: 1, 2: 2
{
	sosd_config_font_scale(x_scale, y_scale);
	y_scale_factor = y_scale;
	x_scale_factor = x_scale;
	update_max_row();
}

// 4. Character Ram API:
// Each line is composed by region(s), minimal gap between region = left
// padding + right padding + 10:

static int osd_next_region(int cur_region, txt_region_t *regions)
{
	int i;
	int cur_position, position;
	int next_position = MAX_WIDTH;
	int next_region_index = -1;

	if (cur_region>=0)
		cur_position = regions[cur_region].position;
	else
		cur_position = 0;
	for (i=0;i<MAX_REGION_PER_LINE;i++){
		if ((i!=cur_region)&&(regions[i].text!=NULL)){
			position = regions[i].position;
			if ((position >= cur_position)&&(position < next_position)){
				next_position = position;
				next_region_index = i;
			}
		}
	}
	return next_region_index;
}

static int osd_draw_row(int row)
{
	int cur_position;
	int cur_region_width;
	int next_position;
	int next_region_index;
	txt_region_t *regions = &txt_regions[row][0];
	short len = 0;
	int i = 0;
	short region_padding = 0;
	unsigned short *p;
	unsigned short *t = &text[row_offset[row]];

	cur_position = 0;
	cur_region_width = 0;
	next_region_index = osd_next_region(-1, regions);
	while (next_region_index>=0){
		next_position = regions[next_region_index].position;
		if (next_position>cur_position+cur_region_width){
			if (len<COL_IN_ROW-1){
				region_padding = sosd_add_padding(&t[len], next_position-(cur_position+cur_region_width), COL_IN_ROW-len-1);
				len += region_padding;
			}
		}
		else if (next_position<cur_position+cur_region_width){
			LOGD(TAG, "region %d in row %d overlap\n", next_region_index, row);
		}
		for (p = regions[next_region_index].text; p < regions[next_region_index].text + regions[next_region_index].len; p++){
			t[len++] = (text_map[(*p>>8)&0xff]<<8)|(*p&0xff);
		}
#ifdef OSD_DEBUG
		LOGD(TAG, "osd_draw_row %d region %d position %d padding %d(%d) width %d(%d) character %d\n", row, next_region_index, next_position, next_position-(cur_position+cur_region_width), region_padding, sosd_get_text_width(t, len), sosd_get_string_width(regions[next_region_index].text, regions[next_region_index].len, text_map), regions[next_region_index].len);
		printf("osd_draw_row %d region %d position %d padding %d(%d) width %d(%d) character %d\n", row, next_region_index, next_position, next_position-(cur_position+cur_region_width), region_padding, sosd_get_text_width(t, len), sosd_get_string_width(regions[next_region_index].text, regions[next_region_index].len, text_map), regions[next_region_index].len);
#endif
		cur_position = next_position;
		//cur_region_width = sosd_get_text_width(t, len);
		cur_region_width = sosd_get_string_width(regions[next_region_index].text, regions[next_region_index].len, text_map);
		next_region_index = osd_next_region(next_region_index, regions);
	}
#if 0
	if (len & 1){
		t[len++] = (sosd_get_line_return()<<8)|(sosd_getbackground()<<4)|sosd_getbackground();
	}
	else{
		len += sosd_add_padding(&t[len], MIN_PADDING, 1);
		t[len++] = (sosd_get_line_return()<<8)|(sosd_getbackground()<<4)|sosd_getbackground();
	}
#else
	t[len++] = (sosd_get_line_return()<<8)|(sosd_getbackground()<<4)|sosd_getbackground();
#endif

#ifdef OSD_DEBUG
	LOGD(TAG, "update_row %d offset %d len %d\n", row, row_offset[row], len);
	printf("update_row %d offset %d len %d data:\n", row, row_offset[row], len);
	for (i=0;i<len;i++)
		printf(" %02x", t[i]>>8);
	printf("\n");
#endif
	return len;
}

static int update_osd(int row)
{
	int i;
	int len;

	len = osd_draw_row(row);
	for (i=row+1;i<max_line;i++){
		if (row_offset[i] == row_offset[i-1] + len)
			break;
		row_offset[i] = row_offset[i-1] + len;
		len = osd_draw_row(i);
	}
	if (i==max_line)
		text_count = row_offset[max_line-1] + len;
	sosd_write_text(0, text, text_count);
	return 0;
}

// position must be even, return handle >=0 when
// success; each char in string is index to fonts, each char in color array bits 7:4 =
// foreground color index, 3:0 = background color index
int OSD_InitialRegion(unsigned line, unsigned position, char *string, unsigned char *color_array)
{
	int i, j, len;
	unsigned short *t;
	int width;

	if ((string==NULL)||(color_array==NULL)) return -1;
	if (mirror_mode){
		if ((line >= max_line)||(position >= MAX_WIDTH-1))
			return -2;
		line = max_line - line;
	}
	else{
		if ((line >= max_line)||(position >= MAX_WIDTH-1))
			return -2;
	}
	for (i=0;i<MAX_REGION_PER_LINE;i++){
		if (txt_regions[line][i].text == NULL){
			len = strlen(string);
			t = (unsigned short *)calloc(len+1, 2);
			if (t==NULL)
				return -3;
			if (mirror_mode){
				for (j=0;j<len;j++)
					t[j] = (string[len-j-1]<<8)|(color_array[len-j-1]&0xff);
			}
			else{
				for (j=0;j<len;j++)
					t[j] = (string[j]<<8)|(color_array[j]&0xff);
			}
			t[j]=0;
			if (mirror_mode){
				width = sosd_get_string_width(t, len, text_map);
				if (width > region_width / x_scale_factor - position){
					free(t);
					return -2;
				}
				txt_regions[line][i].position = region_width / x_scale_factor - position - width;
			}
			else{
				txt_regions[line][i].position = position;
			}
			txt_regions[line][i].text = t;
			txt_regions[line][i].len = len;
			update_osd(line);
			return line*MAX_REGION_PER_LINE+i;
		}
	}
	return -4;
}

int OSD_InitialRegionSimple(unsigned line, unsigned position, char *string,
	unsigned char foreground_color_index, unsigned char background_color_index)
{
	int i, j, len;
	unsigned short *t;
	unsigned char c;
	int width;
	
	if (string==NULL) return -1;
	if ((line >= max_line)||(position >= MAX_WIDTH-1))
		return -2;
	if (mirror_mode){
		line = max_line - line - 1;
	}
	for (i=0;i<MAX_REGION_PER_LINE;i++){
		if (txt_regions[line][i].text == NULL){
			len = strlen(string);
			t = (unsigned short *)calloc(len+1, 2);
			if (t==NULL)
				return -3;
			c = ((background_color_index<<4)|foreground_color_index)&0xff;
			if (mirror_mode){
				for (j=0;j<len;j++)
					t[j] = (string[len-j-1]<<8)|c;
			}
			else{
				for (j=0;j<len;j++)
					t[j] = (string[j]<<8)|c;
			}
			t[j]=0;
			if (mirror_mode){
				width = sosd_get_string_width(t, len, text_map);
				if (width > region_width / x_scale_factor - position){
					free(t);
					return -2;
				}
				txt_regions[line][i].position = region_width / x_scale_factor - position - width;
			}
			else{
				txt_regions[line][i].position = position;
			}
			txt_regions[line][i].color = c;
			txt_regions[line][i].text = t;
			txt_regions[line][i].len = len;
			update_osd(line);
			return line*MAX_REGION_PER_LINE+i;
		}
	}
	return -4;
};

// each char in string is index to fonts, each char in color
// array bits 7:4 = foreground color index, 3:0 = background color index, if string is
// NULL, update color index array only, if color_index_array is NULL, update string
// only
void OSD_UpdateRegionContent (int handle, char *string, unsigned char *color_array)
{
	int row = handle/MAX_REGION_PER_LINE;
	txt_region_t *region = &txt_regions[row][handle%MAX_REGION_PER_LINE];
	int len, i;
	unsigned short *t = NULL;
	int old_width = 0; 
	int width;

	if (region->text){
			if (string){
				if (mirror_mode)
					old_width = sosd_get_string_width(region->text, region->len, text_map);
				len = strlen(string);
				if (len > region->len){
					if (color_array==NULL){
						LOGE(TAG, "color_array not provided for new string\n");
						return;
					}
					t = (unsigned short *)calloc(len+1, 2);
				}
				else{
					t = region->text;
				}
				if (t==NULL)
					return;
				if (color_array){
					if (mirror_mode){
						for (i=0;i<len;i++)
							t[i] = (string[len-i-1]<<8)|(color_array[len-i-1]&0xff);
					}
					else{
						for (i=0;i<len;i++)
							t[i] = (string[i]<<8)|(color_array[i]&0xff);
					}
				}
				else{
					if (mirror_mode){
						for (i=0;i<len;i++)
							t[i] = (string[len-i-1]<<8)|(t[i]&0xff);
					}
					else{
						for (i=0;i<len;i++)
							t[i] = (string[i]<<8)|(t[i]&0xff);
					}
				}
				t[i]=0;
				if (t!=region->text){
					free(region->text);
					region->text = t;
				}
				region->len = len;
				if (mirror_mode){
					width = sosd_get_string_width(t, len, text_map);
					region->position -= width - old_width;
				}
			}
			else if (color_array){
				for (i=0;i<region->len;i++)
					t[i] = (t[i]&0xff00)|(color_array[i]&0xff);
			}
			update_osd(row);
	}
}

// if string is
// NULL, update color only; if color_index>=16, update string only
void OSD_UpdateRegionContentSimple(int handle, char *string, unsigned char foreground_color_index,
	unsigned char background_color_index )
{
	int row = handle/MAX_REGION_PER_LINE;
	txt_region_t *region = &txt_regions[row][handle%MAX_REGION_PER_LINE];
	int len, i;
	unsigned char c;
	unsigned short *t = NULL;
	int old_width = 0;
	int width;

	if (region->text){
			if (string){
				if (mirror_mode)
					old_width = sosd_get_string_width(region->text, region->len, text_map);
				len = strlen(string);
				if (len > region->len){
					t = (unsigned short *)calloc(len+1, 2);
				}
				else{
					t = region->text;
				}
				if (t==NULL)
					return;
				if ((foreground_color_index >= MAX_COLORS)||(background_color_index >= MAX_COLORS)){
					if (mirror_mode){
						for (i=0;i<len;i++)
							t[i] = (string[len-i-1]<<8)|(region->color&0xff);
					}
					else{
						for (i=0;i<len;i++)
							t[i] = (string[i]<<8)|(region->color&0xff);
					}
				}
				else{
					if (mirror_mode){
						for (i=0;i<len;i++)
							t[i] = (string[len-i-1]<<8)|(background_color_index<<4)|foreground_color_index;
					}
					else{
						for (i=0;i<len;i++)
							t[i] = (string[i]<<8)|(background_color_index<<4)|foreground_color_index;
					}
					region->color = (background_color_index<<4)|foreground_color_index;
				}
				t[i]=0;
				if (t!=region->text){
					free(region->text);
					region->text = t;
				}
				region->len = len;
				if (mirror_mode){
					width = sosd_get_string_width(t, len, text_map);
					region->position -= width - old_width;
				}
			}
			else if ((foreground_color_index < MAX_COLORS)&&(background_color_index < MAX_COLORS)){
				t = region->text;
				len = region->len;
				c = ((background_color_index<<4)|foreground_color_index)&0xff;
				for (i=0;i<len;i++)
					t[i] = (t[i]&0xff00)|c;
				region->color = c;
			}
			update_osd(row);
	}
}

void OSD_RemoveRegion(int handle)
{
	int row = handle/MAX_REGION_PER_LINE;
	txt_region_t *region = &txt_regions[row][handle%MAX_REGION_PER_LINE];

	if (region->text)
		free(region->text);
	region->text = NULL;
	region->len = 0;
	region->position = 0;
	region->color = 0;
	update_osd(row);
	return;
};

// calculate and return pixel width of one region
unsigned OSD_GetRegionWidth(int handle)
{
	int row = handle/MAX_REGION_PER_LINE;
	txt_region_t *region = &txt_regions[row][handle%MAX_REGION_PER_LINE];

	return sosd_get_string_width(region->text, region->len, text_map);
}
