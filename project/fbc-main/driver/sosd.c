#include <register.h>
#include <common.h>
#include <log.h>
#include <stdlib.h>

//#define SOSD_DEBUG
#define TAG "SOSD"

extern int vpu_write_lut_new (int lutIdx, int sizeItem, int saddr, int *pData, int twoDatas);
extern int vpu_read_lut_new(int lutIdx, int sizeItem, int saddr, int *pData, int twoDatas);
extern void Delay_ms(unsigned int ms);

static int sosd_hsize = 1920;
static int sosd_vsize = 1080;
static int sosd_xstart = 0;
static int sosd_ystart = 0;
static int sosd_xend = 1919;
static int sosd_yend = 1079;
static int sosd_3d_mode = 0;
static int sosd_fonts = 0;

static void enable_blend(int enable)
{
   Wr_reg_bits(VP_CTRL,        enable&0x1,     12,1);   //enable
   Wr_reg_bits(VP_BYPASS_CTRL,(enable>>1)&0x1, 10,1);   //bypass
}

/* SOSD API */
void sosd_enable(int enable)
{
  if (enable){
    enable_blend(1);
    Wr_reg_bits(OSD_RAM_REG0, 0, 25, 1);
  }
  else{
    Wr_reg_bits(OSD_RAM_REG0, 0, 25, 1);
  }
  Wr_reg_bits(VP_CTRL,        enable&0x1,     11,1);  //enable
  Wr_reg_bits(VP_BYPASS_CTRL,(enable>>1)&0x1,  9,1);  //bypass
}

void sosd_config_canvas(unsigned hsize, unsigned vsize)
{
  Wr(OSD_PSIZE,(vsize<<16)|hsize);
  sosd_hsize = hsize;
  sosd_vsize = vsize;
}

void sosd_config_region(unsigned reg_osd_xstart, unsigned reg_osd_ystart, unsigned reg_osd_xend, unsigned reg_osd_yend)
{
  int hsize = Rd_reg_bits(OSD_PSIZE, 0, 16);
  int vsize = Rd_reg_bits(OSD_PSIZE, 16, 16);

  sosd_enable(0);
  Wr(OSD_TXT_REGION_X,(reg_osd_xend<<16)|reg_osd_xstart);
  Wr(OSD_TXT_REGION_Y,(reg_osd_yend<<16)|reg_osd_ystart);
  sosd_xstart = reg_osd_xstart;
  sosd_xend = reg_osd_xend;
  sosd_ystart = reg_osd_ystart;
  sosd_yend = reg_osd_yend;

  Wr_reg_bits(OSD_RAM_REG0, 0, 24, 1);
  Wr_reg_bits(OSD_RAM_REG0, 2304, 0, 12);
}

void sosd_config_color(unsigned char index, unsigned char red, unsigned char green, unsigned char blue, unsigned alpha)
{
  if (index>=16)
    return;
  Wr(OSD_COLOR_RGBA0+index, (red<<24)|(green<<16)|(blue<<8)|((alpha+1)/2)); // alpha only 7bit
}

unsigned int sosd_get_color(unsigned char index)
{
  return Rd(OSD_COLOR_RGBA0+index);
}

void sosd_set_line_return(int font_index)
{
  Wr_reg_bits(OSD_CHAR_REG0, font_index, 16, 8);
}

int sosd_get_line_return(void)
{
  return Rd_reg_bits(OSD_CHAR_REG0, 16, 8);
}

void sosd_setbackground(int enable, int color_index)
{
  int reg_osd_align_mode = enable ? 1 : 0;
  int reg_osd_align_bcindex = (color_index < 15) ? color_index : 15;

  Wr_reg_bits(OSD_CHAR_REG0, reg_osd_align_mode, 8, 1);
  Wr_reg_bits(OSD_CHAR_REG0, reg_osd_align_bcindex, 0, 4);
}

int sosd_getbackground(void)
{
  return Rd_reg_bits(OSD_CHAR_REG0, 0, 4);
}

void sosd_config_font_size(unsigned width, unsigned height)
{
  int reg_osd_font_xsize = (width<63)?width:63;
  int reg_osd_font_ysize = (height<63)?height:63;
  int reg_osd_font_size = reg_osd_font_xsize * reg_osd_font_ysize;

  Wr_reg_bits(OSD_FONT_REG0, reg_osd_font_xsize, 24, 6);
  Wr_reg_bits(OSD_FONT_REG0, reg_osd_font_ysize, 16, 6);
  Wr_reg_bits(OSD_FONT_REG0, reg_osd_font_size, 0, 12);
}

void sosd_config_fonts(int num_font, const int *pBitmap)
{
  int lutIdx = 0x20|0x0;
  int reg_osd_font_size = Rd_reg_bits(OSD_FONT_REG0, 0, 12);

  sosd_fonts = num_font;
  Wr_reg_bits(OSD_RAM_REG0, sosd_fonts, 16, 8);
  sosd_set_line_return(sosd_fonts);
#ifdef SOSD_DEBUG
  printf("write lut32 %d from %d size %d\n", lutIdx, 0, (sosd_fonts * reg_osd_font_size + 31) / 32);
#endif
  vpu_write_lut_new(lutIdx, (sosd_fonts * reg_osd_font_size + 31) / 32, 0, (int *)pBitmap, 0);
#ifdef SOSD_DEBUG
  int _size = ((sosd_fonts * reg_osd_font_size + 31) / 32);

  int * p = (int *)malloc(_size*sizeof(int));
  vpu_read_lut_new(lutIdx, _size, 0, (int *)p, 0);

  int match = 1;
  //printf("sosd_config_fonts\n");
  for(int i=0;i<_size;i++)
  {
  	if(p[i]!=pBitmap[i])	
	{
		match = 0;
		printf("pBitmap[%d] is 0x%08x, p[%d] is 0x%08x\n", i, pBitmap[i],i,p[i]);
		break;
  	}
  }
  //printf("match is %d\n", match);
  free(p);
#endif
}

void sosd_config_font_scale(int x_scale, int y_scale)
{
  int reg_osd_font_xscal = (x_scale<2)?x_scale:2;
  int reg_osd_font_yscal = (y_scale<2)?y_scale:2;
  int reg_osd_font_xintm;
  int reg_osd_font_yintm;

  if (reg_osd_font_xscal<2)
    reg_osd_font_xintm=0;
  else
    reg_osd_font_xintm=1;

  if (reg_osd_font_yscal<2)
    reg_osd_font_yintm=0;
  else
    reg_osd_font_yintm=1;

  Wr_reg_bits(OSD_FONT_REG0, reg_osd_font_xscal, 30, 2);
  Wr_reg_bits(OSD_FONT_REG0, reg_osd_font_yscal, 22, 2);
  Wr_reg_bits(OSD_FONT_REG0, reg_osd_font_xintm, 14, 1);
  Wr_reg_bits(OSD_FONT_REG0, reg_osd_font_yintm, 13, 1);
}

void sosd_config_font_invert(int invert)
{
  int reg_osd_font_bgfginvert = invert ? 1 : 0;

  Wr_reg_bits(OSD_FONT_REG0, reg_osd_font_bgfginvert, 12, 1);
}

void sosd_config_font_cut(unsigned char index, unsigned pixels)
{
  unsigned reg_osd_hct = (pixels>0x0f)?0x0f:pixels;

  Wr_reg_bits(OSD_FONT_HCT0+(index>>3), reg_osd_hct, ((index&0x07)<<2), 4);
}

static unsigned char sosd_padding_index = 0;
static unsigned char sosd_padding_number = 7;
static const unsigned char sosd_padding_width[7] = {30,22,20,18,16,14,12};

static void set_padding_fonts_cut(void)
{
  int width = Rd_reg_bits(OSD_FONT_REG0, 24, 6) + Rd_reg_bits(OSD_FONT_PAD, 24, 8) + Rd_reg_bits(OSD_FONT_PAD, 16, 8);
  int i;

  if (sosd_padding_index > 0){
    for (i=0;i<sosd_padding_number;i++){
      sosd_config_font_cut(sosd_padding_index+i, (width - sosd_padding_width[i])/2);
    }
  }
}

static int find_padding(int width)
{
  if ((width > sosd_padding_width[1]*2)||(width == sosd_padding_width[0]))
    return 0;
  else if (width > sosd_padding_width[1])
    return ((width/2)&1) ? (sosd_padding_number-1-(((width/2+1)-sosd_padding_width[sosd_padding_number-1])/2))
                         : (sosd_padding_number-1-(((width/2)-sosd_padding_width[sosd_padding_number-1])/2));
  else if (width >= sosd_padding_width[sosd_padding_number-1])
    return sosd_padding_number-1-((width-sosd_padding_width[sosd_padding_number-1])/2);
  else
    return -1;
}

int sosd_config_padding_fonts(int index, const int *pBitmap)
{
  int lutIdx = 0x20|0x0;
  int reg_osd_font_size = Rd_reg_bits(OSD_FONT_REG0, 0, 12);
  int reg_osd_font_width = Rd_reg_bits(OSD_FONT_REG0, 24, 6);
  int i, ret;
  sosd_padding_index = index;

  // increase font numbers for padding and line return
  sosd_fonts = sosd_padding_index + sosd_padding_number;
  Wr_reg_bits(OSD_RAM_REG0, sosd_fonts, 16, 8);
  sosd_set_line_return(sosd_fonts);

  sosd_padding_index = index;
  set_padding_fonts_cut();

  // write fonts for padding and line return
  for (i=0; i<sosd_padding_number; i++){
    printf("write lut32 %d from %d size %d\n", lutIdx, ((sosd_padding_index+i) * reg_osd_font_size + 31) / 32, (reg_osd_font_size + 31) / 32);
    ret = vpu_write_lut_new(lutIdx, (reg_osd_font_size + 31) / 32, ((sosd_padding_index+i) * reg_osd_font_size + 31) / 32, (int *)pBitmap, 0);
#ifdef SOSD_DEBUG
    if (ret!=0)
      printf("vpu_write_lut_new(%d, %d, %d, 0x%x, %d) timeout!\n", lutIdx, (reg_osd_font_size + 31) / 32, ((sosd_padding_index+i) * reg_osd_font_size + 31) / 32, pBitmap, 0);
#endif
  }

  return 0;
}

int sosd_add_padding(unsigned short *text, int pixels, int limit)
{
  int padding_pixels = pixels&0xfffffffe;
  int padding_len = 0;
  int color = (sosd_getbackground()<<4)|sosd_getbackground();
  int index = -1;

  while(1){
    index = find_padding(padding_pixels);
    if ((index<0)||(padding_len==limit))
      return padding_len;
    padding_pixels -= sosd_padding_width[index];
    text[padding_len++] = ((sosd_padding_index+index)<<8)|color;
  }
  return padding_len;
}

void sosd_config_padding(unsigned left, unsigned right, unsigned top, unsigned bottom)
{
  int reg_osd_font_bound_xpad[2];
  int reg_osd_font_bound_ypad[2];

  reg_osd_font_bound_xpad[0]=left;
  reg_osd_font_bound_xpad[1]=right;
  if ((left+right)&1) left+=1; // make sure left+rigth is even
  reg_osd_font_bound_ypad[0]=top;
  reg_osd_font_bound_ypad[1]=bottom;
  Wr(OSD_FONT_PAD,(reg_osd_font_bound_xpad[0]<<24)|(reg_osd_font_bound_xpad[1]<<16)|(reg_osd_font_bound_ypad[0]<<8)|
                   (reg_osd_font_bound_ypad[1]));
  set_padding_fonts_cut();
}

void sosd_config_3d_mode(int sosd_3d_mode)
{
  int reg_osd_xstart = sosd_xstart;
  int reg_osd_xend = sosd_xend;
  int reg_osd_ystart = sosd_ystart;
  int reg_osd_yend = sosd_yend;
  int hsize = sosd_hsize;
  int vsize = sosd_vsize;
  int reg_osd_3d_xintlv=0; //u1
  int reg_osd_3d_yintlv=0; //u1
  int reg_osd_3d_xintlv_phase = 0; //u1 collum interleave 3D mode phase offset
  int reg_osd_3d_yintlv_phase = 0; //u1 row interleave 3D mode phase offset
  int reg_osd_3d_xsplit = sosd_hsize;
  int reg_osd_3d_ysplit = sosd_vsize;

  if(sosd_3d_mode==0) //0-No
  {
    // use defualt values
  }
  if(sosd_3d_mode==1) //0-No, 1-left/right, 2-top/bot
  {
    reg_osd_3d_xsplit = ((hsize>>2)<<1); //can only be even numbers
    reg_osd_xstart = reg_osd_xstart>>1;
    reg_osd_xend = reg_osd_xend>>1;
  }
  else if(sosd_3d_mode==2) //3D: top/bot mode
  {
    reg_osd_3d_ysplit = ((vsize>>2)<<1);
    reg_osd_ystart = reg_osd_ystart>>1;
    reg_osd_yend = reg_osd_yend>>1;
  }
  else if(sosd_3d_mode==3) //3D x interleave mode
  {
    reg_osd_3d_xintlv = 1; //u1
  }
  else if(sosd_3d_mode==4) //3D y interleave mode
  {
    reg_osd_3d_yintlv = 1; //u1
  }
  Wr(OSD_3D_CTRL,(reg_osd_3d_xintlv<<31)|(reg_osd_3d_xintlv_phase<<30)|(reg_osd_3d_xsplit<<16)|
                (reg_osd_3d_yintlv<<15)|(reg_osd_3d_yintlv_phase<<14)|(reg_osd_3d_ysplit));
  Wr(OSD_TXT_REGION_X,(reg_osd_xend<<16)|reg_osd_xstart);
  Wr(OSD_TXT_REGION_Y,(reg_osd_yend<<16)|reg_osd_ystart);
}

int sosd_write_text(int addr, unsigned short *text, int size)
{
	int lutIdx = 0x20|0x1;
	int ret = -1;
	int ram_char_sel;
	int *p = (int*)((unsigned)text);
	if (text){
#ifdef SOSD_DEBUG
		printf("write lut16x2 %d from %d size %d\n", lutIdx, addr, size);
#endif
		ram_char_sel = Rd_reg_bits(OSD_RAM_REG0, 24, 1) ? 0 : 1;
		ret = vpu_write_lut_new(lutIdx,size,addr>>1,(int *)p,1);
		Wr_reg_bits(OSD_RAM_REG0, addr+size, 0, 12);
		Wr_reg_bits(OSD_RAM_REG0, ram_char_sel, 24, 1);
#ifdef SOSD_DEBUG	
		int _size = (size+1)/2;

		int * p1 = (int *)malloc(_size*sizeof(int));
		vpu_read_lut_new(lutIdx, size, addr>>1, p1, 1);

		int match = 1;
		int i;
		//printf("sosd_write_text\n");
		for(i=0;i<_size;i++)
		{

			if((i==_size-1)&&(size &0x1))
			{
				if((p1[i]&0xffff) != (p[i]&0xffff))
				{
					match = 0;
				}
			}
			else
			{
				if(p1[i]!=p[i])	
				{
					match = 0;
					break;
				}
			}
			//printf("p[%d] is 0x%08x, p1[%d] is 0x%08x\n", i,p[i],i,p1[i]);
		}
		if(match == 0)
		{
			printf("pre match is %d\n", match);
		}

		free(p1);
#endif


#ifdef SOSD_DEBUG
		if (ret!=0)
		printf("vpu_write_lut_new(%d, %d, %d, 0x%x, %d) timeout!\n", lutIdx, size, addr>>1, text, 1);
#endif
		return ret;
	}
	return -1;
}

int sosd_get_text_width(unsigned short *text, unsigned short len)
{
	int width;
	int index;
	int i;

	width = (Rd_reg_bits(OSD_FONT_REG0, 24, 6) + Rd_reg_bits(OSD_FONT_PAD, 24, 8) + Rd_reg_bits(OSD_FONT_PAD, 16, 8)) * len;
	for (i=0; i<len; i++){
		index = (text[i]>>8)&0xff;
		width -= (Rd_reg_bits(OSD_FONT_HCT0+(index>>3), (index&0x07)<<2, 4))<<1;
	}
	return width;
}

int sosd_get_string_width(unsigned short *text, unsigned short len, unsigned char *mapping)
{
  int width;
  int index;
  int i;

  width = (Rd_reg_bits(OSD_FONT_REG0, 24, 6) + Rd_reg_bits(OSD_FONT_PAD, 24, 8) + Rd_reg_bits(OSD_FONT_PAD, 16, 8)) * len;
  for (i=0; i<len; i++){
    index = mapping[(text[i]>>8)&0xff];
    width -= (Rd_reg_bits(OSD_FONT_HCT0+(index>>3), (index&0x07)<<2, 4))<<1;
  }
  return width;
}