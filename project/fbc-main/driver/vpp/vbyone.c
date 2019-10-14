#include <register.h>
#include <common.h>
#include <vbyone.h>
#include <vpu_util.h>
#include <log.h> 
int config_vbyone(int lane_num, int byte_num, int region_num, int hsize, int vsize, int enable)
{
   int sublane_num;
   int region_size[4];
   int tmp;

   if((lane_num == 0) || (lane_num == 3) || (lane_num == 5) || (lane_num == 6) || (lane_num == 7) || (lane_num>8))
      return 1;
   if((region_num==0) || (region_num==3) || (region_num>4))
      return 1;
   if(lane_num%region_num)
      return 1;
   if((byte_num<3) || (byte_num>4))
      return 1;

   sublane_num = lane_num/region_num;
   Wr_reg_bits(VBO_LANES,lane_num-1,  VBO_LANE_NUM_BIT,    VBO_LANE_NUM_WID);
   Wr_reg_bits(VBO_LANES,region_num-1,VBO_LANE_REGION_BIT, VBO_LANE_REGION_WID);
   Wr_reg_bits(VBO_LANES,sublane_num-1,VBO_SUBLANE_NUM_BIT, VBO_SUBLANE_NUM_WID);
   Wr_reg_bits(VBO_LANES,byte_num-1,VBO_BYTE_MODE_BIT, VBO_BYTE_MODE_WID);

   if(region_num>1)
   {
       region_size[3] = (hsize/lane_num)*sublane_num;
       tmp = (hsize%lane_num);
       region_size[0] = region_size[3] + (((tmp/sublane_num)>0) ? sublane_num : (tmp%sublane_num));
       region_size[1] = region_size[3] + (((tmp/sublane_num)>1) ? sublane_num : (tmp%sublane_num));
       region_size[2] = region_size[3] + (((tmp/sublane_num)>2) ? sublane_num : (tmp%sublane_num));
       Wr_reg_bits(VBO_REGION01,region_size[0],VBO_REGION_0_BIT,VBO_REGION_0_WID);
       Wr_reg_bits(VBO_REGION01,region_size[1],VBO_REGION_1_BIT,VBO_REGION_1_WID);
       Wr_reg_bits(VBO_REGION23,region_size[2],VBO_REGION_2_BIT,VBO_REGION_2_WID);
       Wr_reg_bits(VBO_REGION23,region_size[3],VBO_REGION_3_BIT,VBO_REGION_3_WID);
   }
   Wr_reg_bits(VBO_VIN_CTRL,vsize,VBO_ACT_VSIZE_BIT,VBO_ACT_VSIZE_WID);
   Wr_reg_bits(VBO_VIN_CTRL,1,VBO_VIN_SYNC_CTRL_BIT,VBO_VIN_SYNC_CTRL_WID);//receive the data after first vsync
   Wr_reg_bits(VBO_CTRL,0x80,VBO_CTL_MODE_BIT,VBO_CTL_MODE_WID);  //don't use go_fld for CTL register
   Wr_reg_bits(VBO_CTRL,0x0,VBO_CTL_MODE2_BIT,VBO_CTL_MODE2_WID); //only for stimulation
   Wr_reg_bits(VBO_CTRL,0x7,VBO_FSM_CTRL_BIT,VBO_FSM_CTRL_WID);
   Wr_reg_bits(VBO_CTRL,0x1,VBO_VIN2ENC_HVSYNC_DLY_BIT,VBO_VIN2ENC_HVSYNC_DLY_WID);
   Wr_reg_bits(VBO_CTRL,enable,VBO_ENABLE_BIT,VBO_EBABLE_WID);

   return 0;
}

void set_vbyone_vfmt(int vin_color, int vin_bpp)
{
   Wr_reg_bits(VBO_VIN_CTRL,vin_color,VBO_VIN_PACK_BIT,VBO_VIN_PACK_WID);
   Wr_reg_bits(VBO_VIN_CTRL,vin_bpp,  VBO_VIN_BPP_BIT,VBO_VIN_BPP_WID);
}

void set_vbyone_ctlbits(int p3d_en, int p3d_lr, int mode)
{
   if(mode==0)  //insert at the first pixel
     Wr_reg_bits(VBO_HBK_PXL_CTL,(1<<p3d_en)|(p3d_lr&0x1),VBO_PXL_CTL0_BIT,VBO_PXL_CTL0_WID);
   else
     Wr_reg_bits(VBO_VBK_CTL,(1<<p3d_en)|(p3d_lr&0x1),0,2);
}

void set_vbyone_sync_pol(int hsync_pol, int vsync_pol)
{
    Wr_reg_bits(VBO_VIN_CTRL,hsync_pol,VBO_VIN_HSYNC_POL_BIT,VBO_VIN_HSYNC_POL_WID);
    Wr_reg_bits(VBO_VIN_CTRL,vsync_pol,VBO_VIN_VSYNC_POL_BIT,VBO_VIN_VSYNC_POL_WID);

    Wr_reg_bits(VBO_VIN_CTRL,hsync_pol,VBO_VOUT_HSYNC_POL_BIT,VBO_VOUT_HSYNC_POL_WID);
    Wr_reg_bits(VBO_VIN_CTRL,vsync_pol,VBO_VOUT_VSYNC_POL_BIT,VBO_VOUT_VSYNC_POL_WID);
}

int set_vbyone_lanes(int lane_num, int byte_num, int region_num, int hsize)
{
   int sublane_num;
   int region_size[4];
   int tmp;

   if((lane_num == 0) || (lane_num == 3) || (lane_num == 5) || (lane_num == 6) || (lane_num == 7) || (lane_num>8))
      return 1;
   if((region_num==0) || (region_num==3) || (region_num>4))
      return 1;
   if(lane_num%region_num)
      return 1;
   if((byte_num<3) || (byte_num>4))
      return 1;

   sublane_num = lane_num/region_num;
   Wr_reg_bits(VBO_LANES,lane_num-1,  VBO_LANE_NUM_BIT,    VBO_LANE_NUM_WID);
   Wr_reg_bits(VBO_LANES,region_num-1,VBO_LANE_REGION_BIT, VBO_LANE_REGION_WID);
   Wr_reg_bits(VBO_LANES,sublane_num-1,VBO_SUBLANE_NUM_BIT, VBO_SUBLANE_NUM_WID);
   Wr_reg_bits(VBO_LANES,byte_num-1,VBO_BYTE_MODE_BIT, VBO_BYTE_MODE_WID);

   if(region_num>1)
   {
       region_size[3] = (hsize/lane_num)*sublane_num;
       tmp = (hsize%lane_num);
       region_size[0] = region_size[3] + (((tmp/sublane_num)>0) ? sublane_num : (tmp%sublane_num));
       region_size[1] = region_size[3] + (((tmp/sublane_num)>1) ? sublane_num : (tmp%sublane_num));
       region_size[2] = region_size[3] + (((tmp/sublane_num)>2) ? sublane_num : (tmp%sublane_num));
       Wr_reg_bits(VBO_REGION01,region_size[0],VBO_REGION_0_BIT,VBO_REGION_0_WID);
       Wr_reg_bits(VBO_REGION01,region_size[1],VBO_REGION_1_BIT,VBO_REGION_1_WID);
       Wr_reg_bits(VBO_REGION23,region_size[2],VBO_REGION_2_BIT,VBO_REGION_2_WID);
       Wr_reg_bits(VBO_REGION23,region_size[3],VBO_REGION_3_BIT,VBO_REGION_3_WID);
   }

   return 0;
}


//===============================================================
void set_VX1_output(int lane_num, int byte_num, int region_num, int color_fmt, int hsize, int vsize)
{
    int vin_color,vin_bpp;

    switch (color_fmt)
      {
        case 0:   //SDVT_VBYONE_18BPP_RGB
                  vin_color = 4;
                  vin_bpp   = 2;
                  break;
        case 1:   //SDVT_VBYONE_18BPP_YCBCR444
                  vin_color = 0;
                  vin_bpp   = 2;
                  break;
        case 2:   //SDVT_VBYONE_24BPP_RGB
                  vin_color = 4;
                  vin_bpp   = 1;
                  break;
        case 3:   //SDVT_VBYONE_24BPP_YCBCR444
                  vin_color = 0;
                  vin_bpp   = 1;
                  break;
        case 4:   //SDVT_VBYONE_30BPP_RGB
                  vin_color = 4;
                  vin_bpp   = 0;
                  break;
        case 5:   //SDVT_VBYONE_30BPP_YCBCR444
                  vin_color = 0;
                  vin_bpp   = 0;
                  break;
        default:  LOGE(TAG_VBY, "Error VBYONE_COLOR_FORMAT!\n");
                  return;
      }

      //PIN_MUX for VX1
      LOGD(TAG_VBY, "Set VbyOne PIN MUX ......\n");
      Wr_reg_bits(PERIPHS_PIN_MUX_3,3,8,2);

      //set Vbyone
      LOGD(TAG_VBY, "VbyOne Configuration ......\n");
      set_vbyone_vfmt(vin_color,vin_bpp);
      config_vbyone(lane_num,byte_num,region_num,hsize,vsize,0);
      set_vbyone_sync_pol(1,1); //set hsync/vsync polarity to let the polarity is low active inside the VbyOne

      //PAD select:
      if((lane_num == 1) || (lane_num==2)) {
       Wr_reg_bits(VBO_LANE_SWAP,1,9,2);
      }
      else if(lane_num ==4) {
        Wr_reg_bits(VBO_LANE_SWAP,2,9,2);
      }
      else {
        Wr_reg_bits(VBO_LANE_SWAP,0,9,2);
      }
      Wr_reg_bits(VBO_LANE_SWAP,1,8,1);//reverse lane output order

      set_vpu_output_mode(1); //Vbyone

      //LOGW(TAG_VBY, "Waiting for VbyOne CDR/ALN......\n");
      //while((Rd(VBO_RO_STATUS)&(1<<5))==0)
      //{};
      LOGD(TAG_VBY, "VbyOne is In Normal Status ......\n");
}

#ifdef IN_FBC_MAIN_CONFIG
extern    int vbyone_reset_flag;
void vbyone_softreset(void)
{
    vbyone_reset_flag = 1;
}
#endif

