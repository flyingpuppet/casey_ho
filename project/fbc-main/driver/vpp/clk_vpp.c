//---------------------------------------------------
//       clocks_set_sys_defaults
//---------------------------------------------------

#include <c_arc_pointer_reg.h>
#include <register.h>
#include <common.h>
#include <clk_vpp.h>
#include <log.h>
#include <vpp.h>

//---------------------------------------------------
//       clock_set_srcif_ref_clk
//---------------------------------------------------
void clock_set_srcif_ref_clk(void)
{
  Wr(REFERENCE_CLK_CNTL,0x8103);//reset
  //wait lock

}

void Spread_spectrum(int mode)
{
    switch(mode)
        {
           case 0:   //off
                //printf("\nset 80030670 to default value:ca763a21");
                Wr(VX1_LVDS_PLL_CTL2, 0xca763a21);
		        break;
           case 1:   //1p5
                //printf("\nset 80030670 to 0x4a379221, +-1.5%.");
                Wr(VX1_LVDS_PLL_CTL2, 0x4a379221);
		        break;
           case 2:   //2p3
                //printf("\nset 80030670 to 0x4a378a21, +-2.3%.");
                Wr(VX1_LVDS_PLL_CTL2, 0x4a378a21);
                break;
           case 3:   //3p1
                //printf("\nset 80030670 to 0x4a770221, +-3.1%.");
                Wr(VX1_LVDS_PLL_CTL2, 0x4a770221);
                break;
		   defualt:
		   	    break;		
        }

}

// --------------------------------------------------
//              clocks_set_vid_clk_div
// --------------------------------------------------
// wire            clk_final_en    = control[19];
// wire            clk_div1        = control[18];
// wire    [1:0]   clk_sel         = control[17:16];
// wire            set_preset      = control[15];
// wire    [14:0]  shift_preset    = control[14:0];
void clocks_set_vid_clk_div(int div_sel)
{
    int shift_val = 0xffff;
    int shift_sel = 0;

    // Disable the output clock
    Wr( VID_PLL_CLK_CNTL, Rd(VID_PLL_CLK_CNTL) & ~((1 << 19) | (1 << 15)) );

    switch( div_sel ) {
        case CLK_UTIL_VID_PLL_DIV_1:      shift_val = 0xFFFF; shift_sel = 0; break;
        case CLK_UTIL_VID_PLL_DIV_2:      shift_val = 0x0aaa; shift_sel = 0; break;
        case CLK_UTIL_VID_PLL_DIV_3:      shift_val = 0x0db6; shift_sel = 0; break;
        //case CLK_UTIL_VID_PLL_DIV_3p5:    shift_val = 0x36cc; shift_sel = 1; break;
        case CLK_UTIL_VID_PLL_DIV_3p5:    shift_val = 0x3366; shift_sel = 1; break;
        case CLK_UTIL_VID_PLL_DIV_3p75:   shift_val = 0x6666; shift_sel = 2; break;
        case CLK_UTIL_VID_PLL_DIV_4:      shift_val = 0x0ccc; shift_sel = 0; break;
        case CLK_UTIL_VID_PLL_DIV_5:      shift_val = 0x739c; shift_sel = 2; break;
        case CLK_UTIL_VID_PLL_DIV_6:      shift_val = 0x0e38; shift_sel = 0; break;
        case CLK_UTIL_VID_PLL_DIV_6p25:   shift_val = 0x0000; shift_sel = 3; break;
        case CLK_UTIL_VID_PLL_DIV_7:      shift_val = 0x3c78; shift_sel = 1; break;
        case CLK_UTIL_VID_PLL_DIV_7p5:    shift_val = 0x78f0; shift_sel = 2; break;
        case CLK_UTIL_VID_PLL_DIV_12:     shift_val = 0x0fc0; shift_sel = 0; break;
        case CLK_UTIL_VID_PLL_DIV_14:     shift_val = 0x3f80; shift_sel = 1; break;
        case CLK_UTIL_VID_PLL_DIV_15:     shift_val = 0x7f80; shift_sel = 2; break;
        default:
                LOGE (TAG_VPP, "Error: clocks_set_vid_clk_div:  Invalid parameter\n");
                break;
    }

    if( shift_val == 0xffff ) {      // if divide by 1
        Wr( VID_PLL_CLK_CNTL, Rd(VID_PLL_CLK_CNTL) | (1 << 18) );
    } else {
        Wr( VID_PLL_CLK_CNTL, (Rd(VID_PLL_CLK_CNTL) & ~((0x3 << 16) | (1 << 15) | (0x3fff << 0))) |
                           ((shift_sel  << 16)  |
                            (1          << 15)  |
                            (shift_val  << 0)) );
        // Set the selector low
        Wr( VID_PLL_CLK_CNTL, Rd(VID_PLL_CLK_CNTL) & ~(1 << 15) );
    }
    // Enable the final output clock
    Wr( VID_PLL_CLK_CNTL, Rd(VID_PLL_CLK_CNTL) | (1 << 19) );
}



void lvds_init(void)
{
	unsigned long data32;
	data32	= 0;
	data32 |= 0x3ffc << 16;
	data32 |= 1 << 15;//[15] Lvds input data inversion
	data32 |= 1 << 14;//[14] Vx1 protect voltage[2]/lvds input data type select
	data32 |= 1 << 13;//[13] Vx1 protect voltage[1]/lvds main driver digital part enable
	data32 |= 1 << 11;//[11] Lvds opamp current select
	data32 |= 1 << 10;//[10] Lvds bias select
	data32 |= 1 << 9;//[9] Lvds Vcm source select
	data32 |= 1 << 4;//[4] Lvds main driver slew rate control
	data32 |= 1 << 1;//[1] Lvds bias current level
	Wr(VX1_LVDS_COMBO_CTL0,data32);

	data32	= 0;
	data32 |= 1	<< 31;//[31]
	data32 |= 1 << 8;//[8] Bias current source select of opamp in commonbias
	data32 |= 1 << 6;//[6] Pu of current generator
	data32 |= 1 << 4;//[4] Lvds/vx1 current level
	Wr(VX1_LVDS_COMBO_CTL1,data32);


	data32	= 0;
	data32 |= 0xffff;
	Wr(VX1_LVDS_COMBO_CTL2,data32);

	Wr(VX1_LVDS_COMBO_CTL3,0);
}

void vx1_init(void)
{
	unsigned long data32;
	data32	= 0;
	data32 |= 1 << 14;//[14] Vx1 protect voltage[2]/lvds input data type select
	data32 |= 1 << 12;//[12] Vx1 protect voltage[0]/lvds pre driver digital part enable
	data32 |= 1 << 11;//[11] Lvds opamp current select
	data32 |= 1 << 10;//[10] Lvds bias select
	data32 |= 1 << 9;//[9] Lvds Vcm source select
	Wr(VX1_LVDS_COMBO_CTL0,data32);

	data32	= 0;
	data32 |= 1 << 8;//[8] Bias current source select of opamp in commonbias
	data32 |= 1 << 6;//[6] Pu of current generator
	data32 |= 1 << 5;//[5] Lvds/vx1 current level
	data32 |= 1 << 3;//[3] Lvds/vx1 current level
	Wr(VX1_LVDS_COMBO_CTL1,data32);


	data32	= 0;
	data32 |= 0xff0 << 16;//[27:20] VX1_PU
	data32 |= 0x3f;//[5:0] RESOFF
	Wr(VX1_LVDS_COMBO_CTL2,data32);

	Wr(VX1_LVDS_COMBO_CTL3,0);
}

// --------------------------------------------------
//              vclk_set_encl_lvds
// --------------------------------------------------
void vclk_set_encl_lvds(int vformat, int lvds_ports)
{
  int hdmi_clk_out;
  int hdmi_vx1_clk_od1;
  int vx1_phy_div;
  int encl_div;
  unsigned int xd;

  hdmi_vx1_clk_od1 = 1; //OD1=1

  if(lvds_ports<=2)
  {
    //pll_video.pl 3500 pll_out
    switch(vformat) {
#if 0//no use
      case TV_ENC_LCD640x480 : //total: 800x525 pixel clk = 25.2MHz, phy_clk(s)=(pclk*7)= 176.4 = 705.6/2
           hdmi_clk_out = 705.6;
           vx1_phy_div  = (lvds_ports==1) ? 8   : 4;
           encl_div     = (lvds_ports==1) ? 35  : 70;
           break;
      case TV_ENC_LCD720x480 : //total: 858x525 pixel clk = 27MHz, phy_clk(s)=(pclk*7)= 189 = 378/2
           hdmi_clk_out = 378;
           vx1_phy_div  = (lvds_ports==1) ? 4   : 2;
           encl_div     = (lvds_ports==1) ? 35  : 70;
           break;
#endif
      case TIMING_1366x768P60://TV_ENC_LCD1366x768 : //total: 1792x798 pixel clk = 85.5MHz, phy_clk(s)=(pclk*7)= 598.5
           hdmi_clk_out =  598.5;
           vx1_phy_div  = (lvds_ports==1) ? 2 : 1;
           encl_div     = (lvds_ports==1) ? 35: 70;
           break;
      case TIMING_1920x1080P60: //total: 2200x1125 pixel clk = 148.5MHz,phy_clk(s)=(pclk*7)= 1039.5
           hdmi_clk_out = 1039.5;
           vx1_phy_div  = (lvds_ports==1) ? 2 : 1;
           encl_div     = (lvds_ports==1) ? 35: 70;
	   Wr(VX1_LVDS_PLL_CTL6,0x1422b500);
	   Wr(VX1_LVDS_PLL_CTL5,0xd4207000);
	   Wr(VX1_LVDS_PLL_CTL,0x4002422b);
	   Wr(VX1_LVDS_PLL_CTL1,0xadc88500);
	   Wr(VX1_LVDS_PLL_CTL2,0xca763a21);
	   Wr(VX1_LVDS_PLL_CTL3,0xf510a819);
           break;
      case TIMING_3840x2160P60://?? neend to check TV_ENC_LCD3840x2160p_vic03://total: 4400x2250 pixel clk = 594M, phy_clk(s)=(pclk*7)= 4158
           hdmi_clk_out = 4158;
           vx1_phy_div  = (lvds_ports==1) ? 2 : 1;
           encl_div     = (lvds_ports==1) ? 35: 70;
           break;
      default:
           LOGE(TAG_VPP, "Error video format!\n");
           return;
     }
     hdmi_vx1_clk_od1 = vx1_phy_div-1 ;
     if(vx1_phy_div == 1)
        hdmi_vx1_clk_od1 = 0;
     else if(vx1_phy_div == 2)
        hdmi_vx1_clk_od1 = 1;
     if((hdmi_vx1_clk_od1<0) || (hdmi_vx1_clk_od1>3)) {
        LOGW(TAG_VPP, "cannot support this format \n");
     }

     /*if(set_vx1_lvds_dpll(hdmi_clk_out,hdmi_vx1_clk_od1)) //
     {     LOGW(TAG_VPP, "Unsupported VX1_LVDS_DPLL out frequency!\n");
           return;
     }*/

     //configure vid_clk_div_top
     if(encl_div==35)
     {
       clocks_set_vid_clk_div(CLK_UTIL_VID_PLL_DIV_3p5);
       xd = encl_div/35;
     }
     else //7*odd
     {
       clocks_set_vid_clk_div(CLK_UTIL_VID_PLL_DIV_7);
       xd = encl_div/70;
     }

     //enable phy_clk
     Wr_reg_bits(VX1_LVDS_PHY_CNTL1,1,24,1);
     //for vx1 fifo clock divide = 7
     Wr_reg_bits(VX1_LVDS_PHY_CNTL0,1,6,2);
     //enable LVDS decoupling fifo //enable lvds input fifo & input fifo write
     Wr_reg_bits(VX1_LVDS_PHY_CNTL1,3,25,2);
     //select LVDS output
     Wr_reg_bits(VX1_LVDS_PHY_CNTL1,0,31,1);

     //configure crt_video
     xd = xd*2;  //2pixel/clk
     if(xd>=256)
     {
       LOGE(TAG_VPP, "Error XD value!\n");
     }
     set_crt_video_enc(1,xd);  //configure crt_video V1: inSel=vid_pll_clk(1),DivN=xd
   }
}
//#ifdef IN_FBC_MAIN_CONFIG
// --------------------------------------------------
//              vclk_set_encl_vx1
// --------------------------------------------------
void vclk_set_encl_vx1(int vfromat,int lane_num, int byte_num)
{
  int hdmi_clk_out = 0;
  int hdmi_vx1_clk_od1;
  int pclk_div;
  int xd;

  //phy_clk = pixel_clk*10*byte_num/lane_num;
  //                                   lane_num      byte_num      phy_clk
  //TV_ENC_LCD720x480:(pclk=27M) 858x525  8            3            101.25      (pclk*3.75)
  //                                      4            3            202.5       (pclk*7.5)
  //                                      2            3            405         (pclk*15)
  //                                      1            3            810         (pclk*30)
  //                                      8            4            135         (pclk*5)
  //                                      4            4            270         (pclk*10)
  //                                      2            4            540         (pclk*20)
  //                                      1            4            1080        (pclk*40)
  //                                   lane_num      byte_num      phy_clk
  //TIMING_1080P60:(pclk=148.5M)     8            3            556.875     (pclk*3.75)
  //                      2200x1125       4            3            1113.75     (pclk*7.5)
  //                                      2            3            2227.5      (pclk*15)
  //                                      1            3            4455        (pclk*30)
  //                                      8            4            742.5       (pclk*5)
  //                                      4            4            1485        (pclk*10)
  //                                      2            4            2970        (pclk*20)
  //                                      1            4            5940        (pclk*40)
  //                                   lane_num      byte_num      phy_clk
  //TV_ENC_LCD3840x2160p:(pclk=594M)      8            3            2227.5      (pclk*3.75)
  //                      4400x2250       4            3            4455        (pclk*7.5)
  //                                      2            3            8910        (pclk*15)
  //                                      1            3           17820        (pclk*30)
  //                                      8            4            2970        (pclk*5)
  //                                      4            4            5940        (pclk*10)
  //                                      2            4           11880        (pclk*20)
  //                                      1            4           23760        (pclk*40)

   hdmi_vx1_clk_od1 = 0;
   switch(vfromat) {
      case TV_ENC_LCD720x480   :
	  	  if(byte_num==3)
          {
             switch(lane_num) {
               case 1  : hdmi_clk_out = 810;  hdmi_vx1_clk_od1= 0; break;
               case 2  : hdmi_clk_out = 810;  hdmi_vx1_clk_od1= 1; break;
               case 4  : hdmi_vx1_clk_od1=-1; break;
               case 8  : hdmi_vx1_clk_od1=-1; break;
               default : hdmi_vx1_clk_od1=-1; break;
             }
          }
          else //4
          {
              switch(lane_num) {
               case 1  : hdmi_clk_out = 1080;  hdmi_vx1_clk_od1= 0; break;
               case 2  : hdmi_clk_out = 1080;  hdmi_vx1_clk_od1= 1; break;
               case 4  : hdmi_vx1_clk_od1=-1; break;
               case 8  : hdmi_vx1_clk_od1=-1; break;
               default : hdmi_vx1_clk_od1=-1; break;
             }
          }
          break;
      case TIMING_1920x1080P60 :
          if(byte_num==3)
          {
             switch(lane_num) {
               case 1  : hdmi_vx1_clk_od1= -1; break;
               case 2  : hdmi_clk_out = 2227.5;  hdmi_vx1_clk_od1= 0; break;
               case 4  : hdmi_clk_out = 2227.5;  hdmi_vx1_clk_od1= 1; break;
               case 8  : hdmi_clk_out =1113.75;  hdmi_vx1_clk_od1= 2; break;
               default : hdmi_vx1_clk_od1=-1; break;
             }
          }
          else //4
          {
              switch(lane_num) {
               case 1  : hdmi_vx1_clk_od1= -1; break;
               case 2  : hdmi_clk_out = 2970;  hdmi_vx1_clk_od1= 0; break;
               case 4  : hdmi_clk_out = 2970;  hdmi_vx1_clk_od1= 1; break;
               case 8  : hdmi_clk_out = 1485;  hdmi_vx1_clk_od1= 2; break;
               default : hdmi_vx1_clk_od1=-1; break;
             }
          }
          break;
      case TIMING_3840x2160P60:
          if(byte_num==3)
          {
             switch(lane_num) {
               case 1  : hdmi_vx1_clk_od1= -1; break;
               case 2  : hdmi_vx1_clk_od1= -1; break;
               case 4  : hdmi_vx1_clk_od1= -1; break;
               case 8  : hdmi_clk_out = 2227.5;  hdmi_vx1_clk_od1= 0; break;
               default : hdmi_vx1_clk_od1=-1; break;
             }
          }
          else //4
          {
              switch(lane_num) {
               case 1  : hdmi_vx1_clk_od1= -1; break;
               case 2  : hdmi_vx1_clk_od1= -1; break;
               case 4  : hdmi_vx1_clk_od1= -1; break;
               case 8  : hdmi_clk_out = 2970;  hdmi_vx1_clk_od1= 0; break;
               default : hdmi_vx1_clk_od1=-1; break;
             }
          }

		  if (byte_num == 3)
		  {
		  //60hz 3bytes
			  Wr(VX1_LVDS_PLL_CTL,0x4000422e);
			  Wr(VX1_LVDS_PLL_CTL1,0xadc88680);
			  Wr(VX1_LVDS_PLL_CTL2,0xca763a21);
			  Wr(VX1_LVDS_PLL_CTL3,0xf510a819);
		  }
		  else
		  {
			  //60hz 4bytes
			  //Wr(VX1_LVDS_PLL_CTL6,0x1422b500);
			  //Wr(VX1_LVDS_PLL_CTL5,0xd4207000);
			  Wr(VX1_LVDS_PLL_CTL,0x6000423d);
			  Wr(VX1_LVDS_PLL_CTL1,0xadc88e00);
			  Wr(VX1_LVDS_PLL_CTL2,0xca763a21);
			  Wr(VX1_LVDS_PLL_CTL3,0xf510a819);
			  Wr(VX1_LVDS_PLL_CTL3,0xf510a819);
			  Wr(VX1_LVDS_PLL_CTL,0x4000423d);//pll reset
		  }
          break;
		case TIMING_3840x2160P50:
			if(byte_num==3)
			{
			  switch(lane_num) {
			     case 1  : hdmi_vx1_clk_od1= -1; break;
			     case 2  : hdmi_vx1_clk_od1= -1; break;
			     case 4  : hdmi_vx1_clk_od1= -1; break;
			     case 8  : hdmi_clk_out = 1856.25;  hdmi_vx1_clk_od1= 0; break;
			     default : hdmi_vx1_clk_od1=-1; break;
			  }
			}
			else //4
			{
			  switch(lane_num) {
			     case 1  : hdmi_vx1_clk_od1= -1; break;
			     case 2  : hdmi_vx1_clk_od1= -1; break;
			     case 4  : hdmi_vx1_clk_od1= -1; break;
			     case 8  : hdmi_clk_out = 2970;  hdmi_vx1_clk_od1= 0; break;
			     default : hdmi_vx1_clk_od1=-1; break;
			  }
			}
			if (byte_num == 3)
			{
				//50Hz 3bytes
				Wr(VX1_LVDS_PLL_CTL,0x40004226);
				Wr(VX1_LVDS_PLL_CTL1,0xadc88ac0);
				Wr(VX1_LVDS_PLL_CTL2,0xca763a21);
				Wr(VX1_LVDS_PLL_CTL3,0xf510a819);
			}
			else
			{
				//50Hz 4bytes
				Wr(VX1_LVDS_PLL_CTL,0x40004233);
				Wr(VX1_LVDS_PLL_CTL1,0xadc88900);
				Wr(VX1_LVDS_PLL_CTL2,0xca763a21);
				Wr(VX1_LVDS_PLL_CTL3,0xf510a819);
			}
			break;
      case TIMING_4kx1kP120_3D_SG:
          if(byte_num==3)
          {
             switch(lane_num) {
               case 1  : hdmi_vx1_clk_od1= -1; break;
               case 2  : hdmi_vx1_clk_od1= -1; break;
               case 4  : hdmi_vx1_clk_od1= -1; break;
               case 8  : hdmi_clk_out = 2227.5;  hdmi_vx1_clk_od1= 0; break;
               default : hdmi_vx1_clk_od1=-1; break;
             }
          }
          else //4
          {
              switch(lane_num) {
               case 1  : hdmi_vx1_clk_od1= -1; break;
               case 2  : hdmi_vx1_clk_od1= -1; break;
               case 4  : hdmi_vx1_clk_od1= -1; break;
               case 8  : hdmi_clk_out = 2970;  hdmi_vx1_clk_od1= 0; break;
               default : hdmi_vx1_clk_od1=-1; break;
             }
          }

		  if (byte_num == 3)
		  {
		  //60hz 3bytes
			  Wr(VX1_LVDS_PLL_CTL,0x4000422e);
			  Wr(VX1_LVDS_PLL_CTL1,0xadc88680);
			  Wr(VX1_LVDS_PLL_CTL2,0xca763a21);
			  Wr(VX1_LVDS_PLL_CTL3,0xf510a819);
		  }
		  else
		  {
			  //60hz 4bytes
			  //Wr(VX1_LVDS_PLL_CTL6,0x1422b500);
			  //Wr(VX1_LVDS_PLL_CTL5,0xd4207000);
			  Wr(VX1_LVDS_PLL_CTL,0x6000423d);
			  Wr(VX1_LVDS_PLL_CTL1,0xadc88e00);
			  Wr(VX1_LVDS_PLL_CTL2,0xca763a21);
			  Wr(VX1_LVDS_PLL_CTL3,0xf510a819);
			  Wr(VX1_LVDS_PLL_CTL3,0xf510a819);
			  Wr(VX1_LVDS_PLL_CTL,0x4000423d);//pll reset
		  }
          break;

      default:
	  	LOGW(TAG_VPP, "unsupport format, you can add by yourself!\n");
            return;
   }

   /*if(set_vx1_lvds_dpll(hdmi_clk_out,hdmi_vx1_clk_od1))
   {     LOGW(TAG_VPP, "Unsupported VX1_LVDS_DPLL out frequency!\n");
         return;
   }*/

   if(byte_num==3) {
      pclk_div = (lane_num == 1) ?  3000 :
                 (lane_num == 2) ?  1500 :
                 (lane_num == 4) ?  750  : 375;
      if(pclk_div == 375)
      {
        clocks_set_vid_clk_div(CLK_UTIL_VID_PLL_DIV_3p75);
        xd = 1;
      }
      else if(pclk_div ==750)
      {
        clocks_set_vid_clk_div(CLK_UTIL_VID_PLL_DIV_7p5);
        xd = 1;
      }
      else
      {
        clocks_set_vid_clk_div(CLK_UTIL_VID_PLL_DIV_15);
        xd = pclk_div/1500;
      }
   } else {
      pclk_div = (lane_num == 1) ?  40 :
                 (lane_num == 2) ?  20 :
                 (lane_num == 4) ?  10 : 5;
      clocks_set_vid_clk_div(CLK_UTIL_VID_PLL_DIV_5);
      xd = pclk_div/5;
   }

   //enable phy_clk
   Wr_reg_bits(VX1_LVDS_PHY_CNTL2,1,24,1);
   //enable VX1 decoupling fifo
   Wr_reg_bits(VX1_LVDS_PHY_CNTL2,3,25,2);
   //select LVDS
   Wr_reg_bits(VX1_LVDS_PHY_CNTL1,1,31,2);

   //configure crt_video
   xd = xd*2;  //2pixel/clk
   if(xd>=256)
   {
      LOGE(TAG_VPP, "Error XD value!\n");
   }
   set_crt_video_enc(1,xd);  //configure crt_video V1: inSel=vid_pll_clk(1),DivN=xd
}

void vclk_set_lvds_hdmi(int tmds_bits, int tmds_repeat, int lvds_ports)
//input:
//tmds_bits:   0 for 24bits, 1 for 30bits, 2 for 36bits, 3 for 48bits
//tmds_repeat: HDMI repeat mode
//lvds_ports : 0 for single-port LVDS; 1 for dual-port LVDS
{
  int divN;
  int PLL_M;
  int PLL_N;
  int PLL_FRAC;
  int PLL_OD, PLL_OD1;
  int vx1_lvds_pll_cntl0, vx1_lvds_pll_cntl1;
  unsigned int xd;


  //1. tmds_clk -> tmds_div_clk
  divN = 6;//1;   148.5/6= 24.75   //800305f4
  set_crt_hdmi_div(2,divN); //select hdmi_tmds_clk


  //2. VID PLL -> vx1_lvds_clk_out
  if(tmds_bits == 0) { //24bits
    PLL_M = 1; PLL_N = 1; PLL_FRAC = 0;
  } else if(tmds_bits == 1) { //30bits
    PLL_M = 4; PLL_N = 5; PLL_FRAC = 0;
  } else if(tmds_bits == 2) { //36bits
    PLL_M = 2; PLL_N = 3; PLL_FRAC = 0;
  } else if(tmds_bits == 3) { //48bits
    PLL_M = 1; PLL_N = 2; PLL_FRAC = 0;
  } else {
    LOGE(TAG_VPP, "Error TMDS BITS only support 24/30/36/48!\n");
    return;
  }
  if(tmds_repeat == 1)
    PLL_FRAC = PLL_FRAC*2;
  else if(tmds_repeat == 2)
    PLL_FRAC = PLL_FRAC*3;

  //PLL_M   = PLL_M*7*2; //lvds   //dco range 1.5-3.2g
  PLL_M   = PLL_M*7; //lvds   //dco range 1.5-3.2g
  PLL_M   = PLL_M*divN;
  PLL_OD  = (lvds_ports==1) ? 2 : 1;  //div1
  PLL_OD1 = 0;

  vx1_lvds_pll_cntl0 = (1      <<30)   |    //[30]Enable
                       (0      << 29)  |    //[29]LVDS_DPLL_RESET
                       (0      << 28)  |    //[28]LVDS_DPLL_SSEN
                       (0      << 24)  |    //[27:24]LVDS_DPLL_SS_AMP
                       (0      << 20)  |    //[23:20]LVDS_DPLL_SS_CLK
                       (PLL_OD1<< 18)  |    //[19:18]od1
                       (PLL_OD << 16)  |    //[17:16]od
                       (3      << 14)  |    //[15:14]LVDS_DPLL_CLK_EN
                       (PLL_N  << 9)   |    //[13:9]N
                       (PLL_M  << 0);       //[8:0] M

  vx1_lvds_pll_cntl1 = (0      << 28)  |    //[31:28]LVDS_DPLL_LM_W
                       (0      << 22)  |    //[27:22]LVDS_DPLL_LM_S
                       (0      << 21)  |    //[21]LVDS_DPLL_DPFD_LMODE
                       (0      << 19)  |    //[20:19] LVDS_DC_VC_IN
                       (0      << 17)  |    //[18:17] LVDS_DCO_SDMCK_SEL
                       (0      << 16)  |    //[16] LVDS_DCO_M_EN
                       (0      << 15)  |    //[15] LVDS_DPLL_SDM_PR_EN
                       (0      << 14)  |    //[14] LVDS_AFC_DSEL_BYPASS
                       (0      << 13)  |    //[13] LVDS_AFC_DSEL_IN
                       (0      << 12)  |    //[12] LVDS_DPLL_DIV_MODE
                       (PLL_FRAC<< 0);      //[11:0] LVDS_DPLL_DIV_FRAC

  Wr_reg_bits( VX1_LVDS_PLL_CTL,0,14,1); //disable
  Wr( VX1_LVDS_PLL_CTL, vx1_lvds_pll_cntl0 & (~(1<<14)));
  //Wr( VX1_LVDS_PLL_CTL1,vx1_lvds_pll_cntl1);
  Wr(VX1_LVDS_PLL_CTL1,0xadc88000);
  //Wr( VX1_LVDS_PLL_CTL2,0);
  Wr(VX1_LVDS_PLL_CTL2,0xca763a21);
  Wr(VX1_LVDS_PLL_CTL3,0xf510b819);
  //Wr( VX1_LVDS_PLL_CTL3,(1<<12)); //select hdmi_tmds_clk as source
  //Wr( VX1_LVDS_PLL_CTL3,((1<<12)|(1<<28))); //select hdmi_tmds_clk as source && bandgap enable
  Wr( VX1_LVDS_PLL_CTL4,0);
  //1080p60
  if(get_metal_revision() == REV_A){
  	Wr(VX1_LVDS_PLL_CTL6,0x1422b500);
  	Wr(VX1_LVDS_PLL_CTL5,0xd422a000);
  }else{
  	Wr(VX1_LVDS_PLL_CTL6,0xcc22b500);
  	Wr(VX1_LVDS_PLL_CTL5,0xcc22a000);
  }


  //set_crt_hdmi_div(2,1); //select hdmi_tmds_clk, div=1
  Wr_reg_bits( VX1_LVDS_PLL_CTL,1,14,1); //enable
  LOGD(TAG_VPP, "Wait 10us for phy_clk stable!\n");
  // delay 10uS to wait clock is stable
	delay_us(10);
  //configure vid_clk_div_top
  if(lvds_ports==1)  //DIV3.5
  {
     clocks_set_vid_clk_div(CLK_UTIL_VID_PLL_DIV_3p5);
     xd = 1;
  }
  else //DIV7
  {
    clocks_set_vid_clk_div(CLK_UTIL_VID_PLL_DIV_7);
    xd = 1;
  }

  //4: vx1_lvds_clk_out(phy_clk) -> lvds_fifo_clk
  //enable phy_clk
  Wr_reg_bits(VX1_LVDS_PHY_CNTL1,1,24,1);
  //for lvds fifo clock
  Wr_reg_bits(VX1_LVDS_PHY_CNTL0,1,6,2);
  //enable LVDS decoupling fifo
  Wr_reg_bits(VX1_LVDS_PHY_CNTL1,3,25,2);
  //select LVDS
  Wr_reg_bits(VX1_LVDS_PHY_CNTL1,0,31,2);

  //5: vid_pll_clk-> cts_vpu_clk
  //configure crt_video
  xd = xd*2;  //2pixel/clk
  if(xd>=256)
  {
     LOGE(TAG_VPP, "Error XD value!\n");
  }

  set_crt_video_enc(1,xd);  //configure crt_video V1: inSel=vid_pll_clk(1),DivN=xd
  //2pixles/clk
}


void vclk_set_vx1_hdmi(int tmds_bits, int tmds_repeat, int lane_num, int byte_num)
//input:
//tmds_bits:   0 for 24bits, 1 for 30bits, 2 for 36bits, 3 for 48bits
//tmds_repeat: HDMI repeat mode
//4Kx2K: lane_num = 8; byte_num=4
{
  int divN;
  int PLL_M;
  int PLL_N;
  int PLL_FRAC;
  int PLL_OD, PLL_OD1;
  int vx1_lvds_pll_cntl0, vx1_lvds_pll_cntl1;
  unsigned int pclk_div, xd;


   //1. tmds_clk -> tmds_div_clk
  divN = 12;
  set_crt_hdmi_div(2,divN); //select hdmi_tmds_clk


  //2. VID PLL -> vx1_lvds_clk_out

  if(tmds_bits == 0) { //24bits
    PLL_M = 1; PLL_N = 1; PLL_FRAC = 0;
  } else if(tmds_bits == 1) { //30bits
    PLL_M = 4; PLL_N = 5; PLL_FRAC = 0;
  } else if(tmds_bits == 2) { //36bits
    PLL_M = 2; PLL_N = 3; PLL_FRAC = 0;
  } else if(tmds_bits == 3) { //48bits
    PLL_M = 1; PLL_N = 2; PLL_FRAC = 0;
  } else {
    LOGE(TAG_VPP, "Error TMDS BITS only support 24/30/36/48!\n");
    return;
  }
  if(tmds_repeat == 1)
    PLL_N = PLL_N*2;
  else if(tmds_repeat == 2)
    PLL_N = PLL_N*3;

 //phy_clk = pixel_clk*10*byte_num/lane_num;
  PLL_M   = PLL_M*10*byte_num*4;
  PLL_M   = PLL_M*divN;
  PLL_N   = PLL_N*lane_num;
  PLL_OD  = 2;
  PLL_OD1 = 0;

  vx1_lvds_pll_cntl0 = (1      <<30)   |    //[30]Enable
                       (0      << 29)  |    //[29]LVDS_DPLL_RESET
                       (0      << 28)  |    //[28]LVDS_DPLL_SSEN
                       (0      << 24)  |    //[27:24]LVDS_DPLL_SS_AMP
                       (0      << 20)  |    //[23:20]LVDS_DPLL_SS_CLK
                       (PLL_OD1<< 18)  |    //[19:18]od1
                       (PLL_OD << 16)  |    //[17:16]od
                       (3      << 14)  |    //[15:14]LVDS_DPLL_CLK_EN
                       (PLL_N  << 9)   |    //[13:9]N
                       (PLL_M  << 0);       //[8:0] M

  vx1_lvds_pll_cntl1 = (0      << 28)  |    //[31:28]LVDS_DPLL_LM_W
                       (0      << 22)  |    //[27:22]LVDS_DPLL_LM_S
                       (0      << 21)  |    //[21]LVDS_DPLL_DPFD_LMODE
                       (0      << 19)  |    //[20:19] LVDS_DC_VC_IN
                       (0      << 17)  |    //[18:17] LVDS_DCO_SDMCK_SEL
                       (0      << 16)  |    //[16] LVDS_DCO_M_EN
                       (0      << 15)  |    //[15] LVDS_DPLL_SDM_PR_EN
                       (0      << 14)  |    //[14] LVDS_AFC_DSEL_BYPASS
                       (0      << 13)  |    //[13] LVDS_AFC_DSEL_IN
                       (0      << 12)  |    //[12] LVDS_DPLL_DIV_MODE
                       (PLL_FRAC<< 0);      //[11:0] LVDS_DPLL_DIV_FRAC
/*
  Wr_reg_bits( VX1_LVDS_PLL_CTL,0,14,1); //disable
  Wr( VX1_LVDS_PLL_CTL, vx1_lvds_pll_cntl0 & (~(1<<14)));
  Wr( VX1_LVDS_PLL_CTL1,vx1_lvds_pll_cntl1);
  Wr( VX1_LVDS_PLL_CTL2,0);
  //Wr( VX1_LVDS_PLL_CTL3,(1<<12)); //select hdmi_tmds_clk as source
  Wr( VX1_LVDS_PLL_CTL3,((1<<12)|(1<<28))); //select hdmi_tmds_clk as source && bandgap enable
  Wr( VX1_LVDS_PLL_CTL4,0);
  Wr_reg_bits( VX1_LVDS_PLL_CTL,1,14,1); //enable
*/
	Wr(VX1_LVDS_PLL_CTL, 0x6000423c);
	Wr(VX1_LVDS_PLL_CTL1,0xadc88000);
	Wr(VX1_LVDS_PLL_CTL2,0xca763a21);
	Wr(VX1_LVDS_PLL_CTL3,0xf510b819);
	//Wr(VX1_LVDS_PLL_CTL3,0xf510a819);
	Wr(VX1_LVDS_PLL_CTL, 0x4000423c);


	Wr(VX1_LVDS_PLL_CTL6,0x0023d000);
	Wr(VX1_LVDS_PLL_CTL5,0xc023c000);

  //printf("Wait 10us for phy_clk stable!\n");
  // delay 10uS to wait clock is stable
	delay_us(10);



  //3: phy_clk -> vid_pll_clk
  if(byte_num==3) {
    pclk_div = (lane_num == 1) ?  3000 :
               (lane_num == 2) ?  1500 :
               (lane_num == 4) ?  750  : 375;
    if(pclk_div == 375)
    {
      clocks_set_vid_clk_div(CLK_UTIL_VID_PLL_DIV_3p75);
      xd = 1;
    }
    else if(pclk_div ==750)
    {
       clocks_set_vid_clk_div(CLK_UTIL_VID_PLL_DIV_7p5);
       xd = 1;
    }
    else
    {
       clocks_set_vid_clk_div(CLK_UTIL_VID_PLL_DIV_15);
       xd = pclk_div/1500;
    }
  }else {
    pclk_div = (lane_num == 1) ?  40 :
               (lane_num == 2) ?  20 :
               (lane_num == 4) ?  10 : 5;
    clocks_set_vid_clk_div(CLK_UTIL_VID_PLL_DIV_5);
    xd = pclk_div/5;
  }

 //4: phy_clk -> vx1_fifo_clk
 //enable phy_clk
 Wr_reg_bits(VX1_LVDS_PHY_CNTL2,1,24,1);
 //enable VX1 decoupling fifo
 Wr_reg_bits(VX1_LVDS_PHY_CNTL2,3,25,2);
 //select LVDS
 Wr_reg_bits(VX1_LVDS_PHY_CNTL1,1,31,2);


 //5: vid_pll_clk-> cts_vpu_clki
 //configure crt_video
 xd = xd*2;  //2pixel/clk
 if(xd>=256)
 {
    LOGE(TAG_VPP, "Error XD value!\n");
 }
 set_crt_video_enc(1,xd);  //configure crt_video V1: inSel=vid_pll_clk(1),DivN=xd
 //2pixles/clk
}

//#endif
//==============================================================
//  VX1_LVDS_DPLL_TOP SETTING FUNCTIONS
//===============================================================

static const int sLVDS_DPLL_DATA[][3] = {  //frequency(M)    VX1_LVDS_PLL_CTL   VX1_LVDS_PLL_CTL2: (bit18: OD1 is 1)
                                     {   399.84,          0x4007c78f,         0x00000d70},
                                     {      378,          0x4007c27d,         0x00000fff},
                                     {    705.6,          0x4007c2eb,         0x00000333},
                                     {     2079,          0x4005c2ad,         0x00000400},
                                     {      810,          0x4006c286,         0x00000fff},
                                     {     1080,          0x4006c2b3,         0x00000fff},
                                     {   2227.5,          0x4005c573,         0x00000400},
                                     {     4455,          0x4004c573,         0x00000400},
                                     {     2970,          0x4005c5ee,         0x00000fff},
                                     {     5940,          0x4004c5ee,         0x00000fff},
                                     {      540,          0x4007c2b3,         0x00000fff},
                                     {      594,          0x4007c2c5,         0x00000fff},
                                     {      864,          0x4006c28f,         0x00000fff},
                                     {     1152,          0x4006c2bf,         0x00000fff},
                                     {      891,          0x4006c528,         0x00000fff},
                                     {     1188,          0x4006c2c5,         0x00000fff},
                                     {     1782,          0x4005c528,         0x00000fff},
                                     {     2376,          0x4005c2c5,         0x00000fff},
                                     {     1197,          0x4006c58e,         0x00000fff},
                                     {    598.5,          0x4007c58e,         0x00000fff},
                                     {   1039.5,          0x4005c4ad,         0x00000400},
                                     {     4158,          0x4005c2ad,         0x00000400},
                                     {  1113.75,          0x4006c573,         0x00000400},
                                     {     1485,          0x4006c5ee,         0x00000fff},
                                     {        0,                   0,                  0}
                                  };

int set_vx1_lvds_dpll(int freq, int od1)
{
  int i;
  i=0;

  Wr_reg_bits( VX1_LVDS_PLL_CTL,0,14,1); //disable

  while(sLVDS_DPLL_DATA[i][0]!=0) {
     if(sLVDS_DPLL_DATA[i][0] == freq)
       break;
     i++;
  }

  if(sLVDS_DPLL_DATA[i][0]==0)
     return 1;
  else {
     Wr( VX1_LVDS_PLL_CTL, sLVDS_DPLL_DATA[i][1] & (~(1<<14))); // disable
     Wr( VX1_LVDS_PLL_CTL1,sLVDS_DPLL_DATA[i][2]);
     Wr_reg_bits( VX1_LVDS_PLL_CTL,od1,18,2);
  }
  //Wr( VX1_LVDS_PLL_CTL2,0);
  //Wr( VX1_LVDS_PLL_CTL3,0);
  Wr( VX1_LVDS_PLL_CTL3,1<<28);
  //Wr( VX1_LVDS_PLL_CTL4,0);

  Wr_reg_bits( VX1_LVDS_PLL_CTL,1,14,1);
  LOGD(TAG_VPP, "Wait 10us for phy_clk stable!\n");
  // delay 10uS to wait clock is stable
	delay_us(10);
  return 0;
}

//===============================================================
//  CRT_VIDEO SETTING FUNCTIONS
//===============================================================
void set_crt_video_enc (int inSel, int DivN)
//input :
//inSel     : 0:cts_oscin_clk;  1:vid_pll_clk; 2:sys_pll_clk; 3:1'b0
//DivN      : clock divider
{
   Wr_reg_bits(VID_CLK_CNTL, 0, 8, 1); //[8] -disable clk_div

	delay_us(2);

   Wr_reg_bits(VID_CLK_CNTL, inSel,   9, 2);  // [10:9]   - clk_sel
   Wr_reg_bits(VID_CLK_CNTL, (DivN-1), 0, 8); // [7:0]   - clk_div

   // delay 5uS
	delay_us(5);

  Wr_reg_bits(VID_CLK_CNTL, 1, 8, 1); //[8] -enable clk_div

	delay_us(5);
}
//#ifdef IN_FBC_MAIN_CONFIG
void set_crt_hdmi_div (int inSel, int DivN)
//input :
//inSel     : 0:cts_oscin_clk;  1:sys_pll_clk; 2:hdmirx_tmds_clk; 3:1'b0
//DivN      : clock divider
{
   Wr_reg_bits(VID_CLK_CNTL, 0, 24, 1); //[24] -disable clk_div

	delay_us(2);

   Wr_reg_bits(VID_CLK_CNTL, inSel,   25, 2);  // [26:25]   - clk_sel
   Wr_reg_bits(VID_CLK_CNTL, (DivN-1), 16, 8); // [23:16]   - clk_div

   // delay 5uS
   delay_us(5);

  Wr_reg_bits(VID_CLK_CNTL, 1, 24, 1); //[24] -enable clk_div

  delay_us(5);
}


//--------------------------------------
//vpu_clki/vpu_clko enable function
//enable : 1 to enable
//inSel  : 0: vid_div1;    1: vid_div2;    2: vid_div4;    3: vid_div6;    4: vid_div12
//cntl_div1_en : vid_clk_cntl[0]
//cntl_div2_en : vid_clk_cntl[1]
//cntl_div4_en : vid_clk_cntl[2]
//cntl_div6_en : vid_clk_cntl[3]
//cntl_div12_en: vid_clk_cntl[4]

////Enable VPU_CLKI
//void enable_crt_vpu_clki (int enable, int inSel)  //vpu_clki
//{
//   Wr_reg_bits(VID_CLK_CNTL, inSel,    28, 4); //vpu_clki_sel: hi_vid_clk_cntl[31:28];
//   Wr_reg_bits(VID_CLK_CNTL,     1, inSel, 1); //hi_vid_clk_cntl[4:0]
//   Wr_reg_bits(VID_CLK_CNTL,enable,     8, 1); //gclk_encl_clk:vid_clk_cntl[8]
//}
//
////Enable VPU_CLKO
//void enable_crt_vpu_clko (int enable, int inSel)  //vpu_clko
//{
//   Wr_reg_bits(VID_CLK_CNTL, inSel,    24, 4); //vpu_clko_sel: hi_vid_clk_cntl[27:24];
//   Wr_reg_bits(VID_CLK_CNTL,     1, inSel, 1); //hi_vid_clk_cntl[4:0]
//   Wr_reg_bits(VID_CLK_CNTL,enable,     9, 1); //gclk_encl_clk:vid_clk_cntl[9]
//}


// -----------------------------------------
// clk_util_clk_msr
// -----------------------------------------
// from core_everything_else.v
//       .clk_to_msr_in    ({15'h0,
//                           hdmirx_aud_clk,              //[48]
//                           hdmirx_aud_mclk,             //[47]
//                           hdmirx_aud_sck,              //[46]
//                           hdmirx_audmeas_clk,          //[45]
//                           HDMI_RX_CLK_OUT,             //[44]
//                           cts_hdmirx_phy_cfg_clk,      //[43]
//                           AUD_CLK_OUT,                 //[42]
//                           hdmirx_tmds_clk_out,         //[41]
//                           cts_hdmirx_meas_ref_clk,     //[40]
//                           cts_hdmirx_modet_clk,        //[39]
//                           cts_hdmirx_cfg_clk,          //[38]
//                           cts_hdmirx_acr_ref_clk,      //[37]
//                           hdmirx_tmds_clk,             //[36]
//                           hdmirx_vid_clk,              //[35]
//                           cts_ref_clk,                 //[34]
//                           vx1_fifo_clk,                //[33]
//                           lvds_fifo_clk,               //[32]
//                           cts_vpu_clki,                //[31]
//                           vid_pll_clk,                 //[30]
//                           hdmirx_cable_clk,            //[29]
//                           cts_wd_tb_osc_clk,           //[28]
//                           cts_pwm_A_clk,               //[27]
//                           cts_cec_clk_32k,             //[26]
//                           AO_pin_clk,                  //[25]
//                           internal_osc_clk,            //[24]
//                           cts_sar_adc_clk,             //[23]
//                           sys_clk_spi       ,          //[22]
//                           sys_clk_i2c_ptest ,          //[21]
//                           sys_clk_i2c_0     ,          //[20]
//                           sys_clk_i2c_1     ,          //[19]
//                           sys_clk_uart0     ,          //[18]
//                           sys_clk_uart1     ,          //[17]
//                           sys_clk_uart2     ,          //[16]
//                           sys_clk_saradc    ,          //[15]
//                           sys_clk_ir_remote ,          //[14]
//                           sys_clk_pwm       ,          //[13]
//                           sys_clk_i2s       ,          //[12]
//                           sys_clk_vpu       ,          //[11]
//                           sys_clk_hdmirx    ,          //[10]
//                           sys_clk_msr_clk   ,          //[9]
//                           sys_clk_hdmirx_cec,          //[8]
//                           cts_sys_clk_tm,              //[7]
//                           sys_pll_clk,                 //[6]
//                           clk_sys_1mS_tick,            //[5]
//                           clk_sys_100uS_tick,          //[4]
//                           clk_sys_10uS_tick,           //[3]
//                           clk_sys_1uS_tick,            //[2]
//                           clk_sys_xtal3_tick,          //[1]
//                           sys_oscin_i                  //[0]
//                           }),
//
// For Example
//
// unsigend long    clk81_clk   = clk_util_clk_msr( 2,      // mux select 2
//                                                  50 );   // measure for 50uS
//
// returns a value in "clk81_clk" in Hz
//
// The "uS_gate_time" can be anything between 1uS and 65535 uS, but the limitation is
// the circuit will only count 65536 clocks.  Therefore the uS_gate_time is limited by
//
//   uS_gate_time <= 65535/(expect clock frequency in MHz)
//
// For example, if the expected frequency is 400Mhz, then the uS_gate_time should
// be less than 163.
//
// Your measurement resolution is:
//
//    100% / (uS_gate_time * measure_val )
//
unsigned long    clk_util_clk_msr(   unsigned long   clk_mux, unsigned long   uS_gate_time )
{
    // Set the measurement gate to 100uS
    Wr(MSR_CLK_REG0, (Rd(MSR_CLK_REG0) & ~(0xFFFF << 0)) | ((uS_gate_time-1) << 0) );
    // Disable continuous measurement
    // disable interrupts
    Wr(MSR_CLK_REG0, (Rd(MSR_CLK_REG0) & ~((1 << 18) | (1 << 17))) );
    Wr(MSR_CLK_REG0, (Rd(MSR_CLK_REG0) & ~(0x3f << 20)) | ((clk_mux << 20) |  // Select MUX
                                                          (1 << 19) |     // enable the clock
                                                          (1 << 16)) );    // enable measuring
    // Delay
    Rd(MSR_CLK_REG0);
    // Wait for the measurement to be done
    while( (Rd(MSR_CLK_REG0) & (1 << 31)) ) {}
    // disable measuring
    Wr(MSR_CLK_REG0, (Rd(MSR_CLK_REG0) & ~(1 << 16)) | (0 << 16) );

    unsigned long   measured_val = (Rd(MSR_CLK_REG2) & 0x000FFFFF); // only 20 bits
    //LOGD(TAG_VPP, "measured_val = %d\n", measured_val );
    if( measured_val == 0xFFFFF ) {     // 20 bits max
        return(0);
    } else {
        // Return value in Hz
        return(measured_val*(1000000/uS_gate_time));
    }

}
//#endif
