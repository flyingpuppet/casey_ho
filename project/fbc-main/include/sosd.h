#ifndef SOSD_H
#define SOSD_H
void sosd_enable(int enable);
void sosd_config_canvas(unsigned hsize, unsigned vsize);
void sosd_config_region(unsigned reg_osd_xstart, unsigned reg_osd_ystart, unsigned reg_osd_xend, unsigned reg_osd_yend);
void sosd_config_color(unsigned char index, unsigned char red, unsigned char green, unsigned char blue, unsigned alpha);
unsigned int sosd_get_color(unsigned char index);
void sosd_config_font_size(unsigned width, unsigned height);
void sosd_config_fonts(unsigned count, const int *bitmaps);
void sosd_config_font_scale(int x_scale, int y_scale);
void sosd_config_font_invert(int invert);
void sosd_config_font_cut(unsigned char index, unsigned pixels);
void sosd_config_padding(unsigned left, unsigned right, unsigned top, unsigned bottom);
void sosd_config_3d_mode(int sosd_3d_mode);

void sosd_set_line_return(int font_index);
int sosd_get_line_return(void);
void sosd_setbackground(int enable, int color_index);
int sosd_getbackground(void);

int sosd_config_padding_fonts(int index, const int *pBitmap);
int sosd_add_padding(unsigned short *text, int pixels, int limit);
int sosd_write_text(int addr, unsigned short *text, int size);
int sosd_get_text_width(unsigned short *text, unsigned short len);
int sosd_get_string_width(unsigned short *text, unsigned short len, unsigned char *mapping);

#endif