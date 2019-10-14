#ifndef _CM2_LUT_H_
#define _CM2_LUT_H_
/*
    // Below is the pre-defined registers
    // parameters reg_CM2_Adj_Luma_via_Hue[32] 8bits-signed
    static int reg_CM2_Adj_Luma_via_Hue[32]=  // 8bits-signed (-128~127)    //=======
    {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
#if 0
    static int reg_CM2_Adj_Luma_via_Hue_Lshift = 0;   // 2bits: 0: no shift.  1: (-256~254)
                                               //        2:(-512~508)  3: (-1024~1016)
    // update for RTL, 04/08/2014
    static int reg_CM2_Adj_Luma_via_Hue_SatTh = 0; // u12
    static int reg_CM2_Adj_Luma_via_Hue_SatK  = 0 ; // u8
    static int reg_CM2_Adj_Hue_via_Hue_SatTh  = 0; // u12
    static int reg_CM2_Adj_Hue_via_Hue_SatK   = 0 ; // u8
    static int reg_CM2_Adj_Sat_via_Hue_SatTh  = 0; // u12
    static int reg_CM2_Adj_Sat_via_Hue_SatK   = 0 ; // u8

    static int reg_CM2_Before_U_offset = 0; // s8 -128~127
    static int reg_CM2_Before_V_offset = 0; // s8 -128~127
    static int reg_CM2_After_U_offset  = 0; // s8 -128~127
    static int reg_CM2_After_V_offset  = 0; // s8 -128~127
    static int reg_CM2_Before_Hue_offset=0; // u12 0~4095
    static int reg_CM2_Hue_div_mode     = 0;// u2
    static int reg_CM2_Adj_Hue_via_HS_mode = 0; // u3
    static int reg_CM2_Hue_protect_en   = 0;  // u1

    // update for RTL, 04/08/2014
    static int reg_CM2_Adj_Sat_via_HS_Satth0 = 1024; // 12bits: threshold on Sat
    static int reg_CM2_Adj_Sat_via_HS_Satth1 = 2048; // 12bits:
    static int reg_CM2_Adj_Sat_via_HS_Rshift  = 0;  // 2bits: 0: (0,2)  1: (0.5, 1.5)
                                             //        2:(1.75~2.25)  3: (-1.875~2.125)

     static int reg_CM2_Adj_Satgain_via_Y_Rshift = 0;	 // 2bits: 0: (0,2)  1: (0.5, 1.5)
						  //	    2:(1.75~2.25)  3: (-1.875~2.125)

  // parameter of Hue offset scale
  // update for RTL, 04/08/2014
  static int reg_CM2_Adj_Hue_via_HSV_Lshift  = 0; // 3bits: 0: (-128,127)  1: (-256, 254)
						  //	    2: (-512~508)  3: (-1024~1016)
						  //	    4: (-2048~2032)5: (-4096~4064)
						  //	    6: (-8192~8128)7: (-16384~16256)

#endif
    // parameters reg_CM2_Adj_Sat_via_HS[32] 8bits-signed
    static const int reg_CM2_Adj_Sat_via_HS[3][32]=  // 8bits-signed (-128~127)   //========
    {
    { 17, 17, 19, 19, 19, 17, 15, 13,  10, 10, 10, 8, 8, 8, 8, 6, 6, 6, 6, 8, 10, 13, 13, 13, 15, 15, 17, 21, 26, 28, 26, 21},  // Satth0
    { 10, 13, 15, 15, 15, 15, 13, 10,  8, 8, 10, 10, 10, 8, 6, 4, 6, 6, 6, 8, 6, 6, 8, 10, 15, 17, 19, 19, 21, 23, 23, 19},  // Satth1
    {  0,  0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}   // Satth2
    };

    static const int reg_CM2_Adj_Satgain_via_Y[5][32]= // 8bits-signed (-128~127) Normalized to 128   //==========
    {
    {0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0},  // Luma=0
    {0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0},  // Luma=1/4
    {0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0},  // Luma=2/4
    {0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0},  // Luma=3/4
    {0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0},   // Luma=4/4
    };

    static const int reg_CM2_Adj_SatGLBgain_via_Y[9]= // 8bits-signed (-128~127) Normalized to 128   //=================
    {15, 18, 20, 28, 30, 30, 28, 18,  15};        // global gain for all hue/sat

    // parameters reg_CM2_Adj_Hue_via_H[32] 8bits-signed
    static const int reg_CM2_Adj_Hue_via_H[32]=  // 8bits-signed (-128~127)   //========
    //{  0,  0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    {12, 31, 51, 63, 64, 64, 63, 50, 9, -22, -44, -61, -64, -53, -44, -37, -22, -9, 3, 9, 12, 14, 12, 7, -5, -14, -18, -11, 1, 5, 5, 7};

    // parameters reg_CM2_Adj_Hue_via_S[5][32] 8bits-signed
    static const int reg_CM2_Adj_Hue_via_S[5][32]=  // 8bits-signed (-128~127)  //===============
    {
    {0,  0, 0, 0, 0, 0, 0,  0,  0, 0, 0,   0, 0,  0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0},  // Sat= 0
    {0,  0, 0, 0, 0, 0, 0,  0,  0, 0, 0,   0, 0,  0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0},  // Sat= 1/4
    {0,  0, 0, 0, 0, 0, 0,  0,  0, 0, 0,   0, 0,  0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0},  // Sat= 2/4
    {0,  0, 0, 0, 0, 0, 0,  0,  0, 0, 0,   0, 0,  0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0},  // Sat= 3/4
    {0,  0, 0, 0, 0, 0, 0,  0,  0, 0, 0,   0, 0,  0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0}      // Sat= 4/4
    };

    //parameters reg_CM2_Adj_Hue_via_Y[5][32] 8bits-signed
    static const int reg_CM2_Adj_Hue_via_Y[5][32]=  // 8bits-signed (-128~127)   //========
    {
    {0,  0, 0, 0, 0, 0, 0,  0,  0, 0, 0,   0, 0,  0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0},  // Y= 0
    {0,  0, 0, 0, 0, 0, 0,  0,  0, 0, 0,   0, 0,  0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0},  // Y= 1/4
    {0,  0, 0, 0, 0, 0, 0,  0,  0, 0, 0,   0, 0,  0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0},  // Y= 2/4
    {0,  0, 0, 0, 0, 0, 0,  0,  0, 0, 0,   0, 0,  0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0},  // Y= 3/4
    {0,  0, 0, 0, 0, 0, 0,  0,  0, 0, 0,   0, 0,  0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0}   // Y= 4/4
    };
    static int reg_CM2_global_HUE        = 0;
    static int reg_CM2_global_Sat        = 502;
    static int reg_CM2_Lum_adj_EN        = 1;
    static int reg_CM2_Hue_adj_EN        = 1;
    static int reg_CM2_Sat_adj_EN        = 1;
    //static int reg_CM2_ONLPF_mode        = 0;
    //static int reg_CM2_ONLPF_interleave  = 0;

    //static int reg_CM1_EN                = 0;
    static int reg_CM2_EN                = 1;
    //static int reg_CM2_FILTER_EN         = 0;
    //static int reg_CM_bypass             = 0;

*/
#endif

