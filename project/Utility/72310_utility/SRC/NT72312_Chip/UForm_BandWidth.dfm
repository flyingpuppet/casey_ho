inherited Form_BandWidth: TForm_BandWidth
  Left = 91
  Top = 36
  Width = 1162
  Height = 629
  Caption = 'Form_BandWidth'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 32
    Width = 73
    Height = 13
    AutoSize = False
    Caption = 'me_i_y_r :'
  end
  object Label2: TLabel
    Left = 8
    Top = 52
    Width = 73
    Height = 13
    AutoSize = False
    Caption = 'me_p_y_r :'
  end
  object Label3: TLabel
    Left = 8
    Top = 72
    Width = 73
    Height = 13
    AutoSize = False
    Caption = 'me_i2_y_r :'
  end
  object Label4: TLabel
    Left = 8
    Top = 92
    Width = 73
    Height = 13
    AutoSize = False
    Caption = 'mc_i_y_r :'
  end
  object Label5: TLabel
    Left = 8
    Top = 112
    Width = 73
    Height = 13
    AutoSize = False
    Caption = 'mc_i_c_r :'
  end
  object Label6: TLabel
    Left = 8
    Top = 132
    Width = 73
    Height = 13
    AutoSize = False
    Caption = 'mc_p_y_r :'
  end
  object Label7: TLabel
    Left = 8
    Top = 152
    Width = 73
    Height = 13
    AutoSize = False
    Caption = 'mc_p_c_r :'
  end
  object Label8: TLabel
    Left = 8
    Top = 172
    Width = 73
    Height = 13
    AutoSize = False
    Caption = 'ip_y_w :'
  end
  object Label9: TLabel
    Left = 8
    Top = 192
    Width = 73
    Height = 13
    AutoSize = False
    Caption = 'ip_c_w :'
  end
  object Label10: TLabel
    Left = 8
    Top = 212
    Width = 73
    Height = 13
    AutoSize = False
    Caption = 'ip_qy_w :'
  end
  object Label11: TLabel
    Left = 8
    Top = 232
    Width = 73
    Height = 13
    AutoSize = False
    Caption = 'ip_fdet_r :'
  end
  object Label12: TLabel
    Left = 8
    Top = 252
    Width = 73
    Height = 13
    AutoSize = False
    Caption = 'ip_logo_w :'
  end
  object Label13: TLabel
    Left = 8
    Top = 272
    Width = 73
    Height = 13
    AutoSize = False
    Caption = 'ip_logo_r :'
  end
  object Label14: TLabel
    Left = 8
    Top = 292
    Width = 73
    Height = 13
    AutoSize = False
    Caption = 'me_mv1_w :'
  end
  object Label15: TLabel
    Left = 8
    Top = 312
    Width = 73
    Height = 13
    AutoSize = False
    Caption = 'me_mv1_r :'
  end
  object Label16: TLabel
    Left = 8
    Top = 332
    Width = 73
    Height = 13
    AutoSize = False
    Caption = 'me_pi_v_w :'
  end
  object Label17: TLabel
    Left = 8
    Top = 352
    Width = 73
    Height = 13
    AutoSize = False
    Caption = 'me_pi_v_r :'
  end
  object Label18: TLabel
    Left = 8
    Top = 372
    Width = 73
    Height = 13
    AutoSize = False
    Caption = 'me_ppi_v_r :'
  end
  object Label19: TLabel
    Left = 8
    Top = 392
    Width = 73
    Height = 13
    AutoSize = False
    Caption = 'vdp_r :'
  end
  object Label20: TLabel
    Left = 8
    Top = 412
    Width = 73
    Height = 13
    AutoSize = False
    Caption = 'vdp_w :'
  end
  object Label21: TLabel
    Left = 8
    Top = 432
    Width = 73
    Height = 13
    AutoSize = False
    Caption = 'logo_mask_w :'
  end
  object Label22: TLabel
    Left = 8
    Top = 452
    Width = 73
    Height = 13
    AutoSize = False
    Caption = 'logo_mask_r :'
  end
  object Label23: TLabel
    Left = 184
    Top = 8
    Width = 60
    Height = 13
    AutoSize = False
    Caption = 'Burst Length'
  end
  object Label24: TLabel
    Left = 336
    Top = 8
    Width = 60
    Height = 13
    AutoSize = False
    Caption = 'Cmd Length'
  end
  object Label25: TLabel
    Left = 512
    Top = 8
    Width = 60
    Height = 13
    AutoSize = False
    Caption = ' Flag'
  end
  object Label26: TLabel
    Left = 64
    Top = 8
    Width = 73
    Height = 13
    AutoSize = False
    Caption = 'DM reset/off'
  end
  object Label27: TLabel
    Left = 176
    Top = 484
    Width = 114
    Height = 13
    AutoSize = False
    Caption = 'Wait Cycle write back :'
  end
  object Label28: TLabel
    Left = 176
    Top = 500
    Width = 114
    Height = 13
    AutoSize = False
    Caption = 'Wait Cycle pre fetch :'
  end
  object RegScrollBar1: TRegScrollBar
    Left = 128
    Top = 32
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 0
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000B6C'
    RegBits = 6
  end
  object RegEdit1: TRegEdit
    Left = 248
    Top = 30
    Width = 33
    Height = 21
    TabOrder = 1
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000B6C'
    RegBits = 6
    TextType = ttInt
  end
  object RegScrollBar2: TRegScrollBar
    Left = 128
    Top = 52
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 2
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000B6E'
    RegBits = 6
  end
  object RegEdit2: TRegEdit
    Left = 248
    Top = 50
    Width = 33
    Height = 21
    TabOrder = 3
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000B6E'
    RegBits = 6
    TextType = ttInt
  end
  object RegScrollBar3: TRegScrollBar
    Left = 128
    Top = 72
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 4
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000B70'
    RegBits = 6
  end
  object RegEdit3: TRegEdit
    Left = 248
    Top = 70
    Width = 33
    Height = 21
    TabOrder = 5
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000B70'
    RegBits = 6
    TextType = ttInt
  end
  object RegScrollBar4: TRegScrollBar
    Left = 128
    Top = 92
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 6
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000B72'
    RegBits = 6
  end
  object RegEdit4: TRegEdit
    Left = 248
    Top = 90
    Width = 33
    Height = 21
    TabOrder = 7
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000B72'
    RegBits = 6
    TextType = ttInt
  end
  object RegScrollBar5: TRegScrollBar
    Left = 128
    Top = 112
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 8
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000B74'
    RegBits = 6
  end
  object RegEdit5: TRegEdit
    Left = 248
    Top = 110
    Width = 33
    Height = 21
    TabOrder = 9
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000B74'
    RegBits = 6
    TextType = ttInt
  end
  object RegScrollBar6: TRegScrollBar
    Left = 128
    Top = 132
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 10
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000B76'
    RegBits = 6
  end
  object RegEdit6: TRegEdit
    Left = 248
    Top = 130
    Width = 33
    Height = 21
    TabOrder = 11
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000B76'
    RegBits = 6
    TextType = ttInt
  end
  object RegScrollBar7: TRegScrollBar
    Left = 128
    Top = 152
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 12
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000B78'
    RegBits = 6
  end
  object RegEdit7: TRegEdit
    Left = 248
    Top = 150
    Width = 33
    Height = 21
    TabOrder = 13
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000B78'
    RegBits = 6
    TextType = ttInt
  end
  object RegScrollBar8: TRegScrollBar
    Left = 128
    Top = 172
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 14
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000108'
    RegBits = 7
  end
  object RegEdit8: TRegEdit
    Left = 248
    Top = 170
    Width = 33
    Height = 21
    TabOrder = 15
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000108'
    RegBits = 7
    TextType = ttInt
  end
  object RegScrollBar9: TRegScrollBar
    Left = 128
    Top = 192
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 16
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000109'
    RegBits = 7
  end
  object RegEdit9: TRegEdit
    Left = 248
    Top = 190
    Width = 33
    Height = 21
    TabOrder = 17
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000109'
    RegBits = 7
    TextType = ttInt
  end
  object RegScrollBar10: TRegScrollBar
    Left = 128
    Top = 212
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 18
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE000010A'
    RegBits = 7
  end
  object RegEdit10: TRegEdit
    Left = 248
    Top = 210
    Width = 33
    Height = 21
    TabOrder = 19
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE000010A'
    RegBits = 7
    TextType = ttInt
  end
  object RegScrollBar11: TRegScrollBar
    Left = 128
    Top = 232
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 20
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000106'
    RegBits = 7
  end
  object RegEdit11: TRegEdit
    Left = 248
    Top = 230
    Width = 33
    Height = 21
    TabOrder = 21
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000106'
    RegBits = 7
    TextType = ttInt
  end
  object RegScrollBar12: TRegScrollBar
    Left = 128
    Top = 252
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 22
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000100'
    RegBits = 7
  end
  object RegEdit12: TRegEdit
    Left = 248
    Top = 250
    Width = 33
    Height = 21
    TabOrder = 23
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000100'
    RegBits = 7
    TextType = ttInt
  end
  object RegScrollBar13: TRegScrollBar
    Left = 128
    Top = 272
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 24
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000101'
    RegBits = 7
  end
  object RegEdit13: TRegEdit
    Left = 248
    Top = 270
    Width = 33
    Height = 21
    TabOrder = 25
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000101'
    RegBits = 7
    TextType = ttInt
  end
  object RegScrollBar14: TRegScrollBar
    Left = 128
    Top = 292
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 26
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000A8E'
    RegBits = 6
  end
  object RegEdit14: TRegEdit
    Left = 248
    Top = 290
    Width = 33
    Height = 21
    TabOrder = 27
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000A8E'
    RegBits = 6
    TextType = ttInt
  end
  object RegScrollBar15: TRegScrollBar
    Left = 128
    Top = 312
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 28
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000A8C'
    RegBits = 6
  end
  object RegEdit15: TRegEdit
    Left = 248
    Top = 310
    Width = 33
    Height = 21
    TabOrder = 29
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000A8C'
    RegBits = 6
    TextType = ttInt
  end
  object RegScrollBar16: TRegScrollBar
    Left = 128
    Top = 332
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 30
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000A8F'
    RegBits = 6
  end
  object RegEdit16: TRegEdit
    Left = 248
    Top = 330
    Width = 33
    Height = 21
    TabOrder = 31
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000A8F'
    RegBits = 6
    TextType = ttInt
  end
  object RegScrollBar17: TRegScrollBar
    Left = 128
    Top = 352
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 32
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000A8D'
    RegBits = 6
  end
  object RegEdit17: TRegEdit
    Left = 248
    Top = 350
    Width = 33
    Height = 21
    TabOrder = 33
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000A8D'
    RegBits = 6
    TextType = ttInt
  end
  object RegScrollBar18: TRegScrollBar
    Left = 128
    Top = 372
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 34
    Visible = False
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000A8D'
    RegBits = 6
  end
  object RegEdit18: TRegEdit
    Left = 248
    Top = 370
    Width = 33
    Height = 21
    TabOrder = 35
    Visible = False
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000A8D'
    RegBits = 6
    TextType = ttInt
  end
  object RegScrollBar19: TRegScrollBar
    Left = 128
    Top = 392
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 36
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE000118A'
    RegBits = 6
  end
  object RegEdit19: TRegEdit
    Left = 248
    Top = 390
    Width = 33
    Height = 21
    TabOrder = 37
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE000118A'
    RegBits = 6
    TextType = ttInt
  end
  object RegScrollBar20: TRegScrollBar
    Left = 128
    Top = 412
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 38
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE000118B'
    RegBits = 6
  end
  object RegEdit20: TRegEdit
    Left = 248
    Top = 410
    Width = 33
    Height = 21
    TabOrder = 39
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE000118B'
    RegBits = 6
    TextType = ttInt
  end
  object RegScrollBar21: TRegScrollBar
    Left = 128
    Top = 432
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 40
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000107'
    RegBits = 7
  end
  object RegEdit21: TRegEdit
    Left = 248
    Top = 430
    Width = 33
    Height = 21
    TabOrder = 41
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000107'
    RegBits = 7
    TextType = ttInt
  end
  object RegScrollBar22: TRegScrollBar
    Left = 128
    Top = 452
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 42
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000202'
    RegBits = 7
  end
  object RegEdit22: TRegEdit
    Left = 248
    Top = 450
    Width = 33
    Height = 21
    TabOrder = 43
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000202'
    RegBits = 7
    TextType = ttInt
  end
  object RegScrollBar23: TRegScrollBar
    Left = 288
    Top = 32
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 44
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000B6D'
    RegBits = 4
  end
  object RegEdit23: TRegEdit
    Left = 408
    Top = 30
    Width = 33
    Height = 21
    TabOrder = 45
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000B6D'
    RegBits = 4
    TextType = ttInt
  end
  object RegScrollBar24: TRegScrollBar
    Left = 288
    Top = 52
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 46
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000B6F'
    RegBits = 4
  end
  object RegEdit24: TRegEdit
    Left = 408
    Top = 50
    Width = 33
    Height = 21
    TabOrder = 47
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000B6F'
    RegBits = 4
    TextType = ttInt
  end
  object RegScrollBar25: TRegScrollBar
    Left = 288
    Top = 72
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 48
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000B71'
    RegBits = 4
  end
  object RegEdit25: TRegEdit
    Left = 408
    Top = 70
    Width = 33
    Height = 21
    TabOrder = 49
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000B71'
    RegBits = 4
    TextType = ttInt
  end
  object RegScrollBar26: TRegScrollBar
    Left = 288
    Top = 92
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 50
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000B73'
    RegBits = 4
  end
  object RegEdit26: TRegEdit
    Left = 408
    Top = 90
    Width = 33
    Height = 21
    TabOrder = 51
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000B73'
    RegBits = 4
    TextType = ttInt
  end
  object RegScrollBar27: TRegScrollBar
    Left = 288
    Top = 112
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 52
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000B75'
    RegBits = 4
  end
  object RegEdit27: TRegEdit
    Left = 408
    Top = 110
    Width = 33
    Height = 21
    TabOrder = 53
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000B75'
    RegBits = 4
    TextType = ttInt
  end
  object RegScrollBar28: TRegScrollBar
    Left = 288
    Top = 132
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 54
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000B77'
    RegBits = 4
  end
  object RegEdit28: TRegEdit
    Left = 408
    Top = 130
    Width = 33
    Height = 21
    TabOrder = 55
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000B77'
    RegBits = 4
    TextType = ttInt
  end
  object RegScrollBar29: TRegScrollBar
    Left = 288
    Top = 152
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 56
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000B79'
    RegBits = 4
  end
  object RegEdit29: TRegEdit
    Left = 408
    Top = 150
    Width = 33
    Height = 21
    TabOrder = 57
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000B79'
    RegBits = 4
    TextType = ttInt
  end
  object RegScrollBar30: TRegScrollBar
    Left = 288
    Top = 172
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 58
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000104'
    RegBits = 4
  end
  object RegEdit30: TRegEdit
    Left = 408
    Top = 170
    Width = 33
    Height = 21
    TabOrder = 59
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000104'
    RegBits = 4
    TextType = ttInt
  end
  object RegScrollBar31: TRegScrollBar
    Left = 288
    Top = 192
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 60
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000104'
    RegBits = 4
    RegStart = 4
  end
  object RegEdit31: TRegEdit
    Left = 408
    Top = 190
    Width = 33
    Height = 21
    TabOrder = 61
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000104'
    RegBits = 4
    RegStart = 4
    TextType = ttInt
  end
  object RegScrollBar32: TRegScrollBar
    Left = 288
    Top = 212
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 62
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000105'
    RegBits = 4
  end
  object RegEdit32: TRegEdit
    Left = 408
    Top = 210
    Width = 33
    Height = 21
    TabOrder = 63
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000105'
    RegBits = 4
    TextType = ttInt
  end
  object RegScrollBar33: TRegScrollBar
    Left = 288
    Top = 232
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 64
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000105'
    RegBits = 4
    RegStart = 4
  end
  object RegEdit33: TRegEdit
    Left = 408
    Top = 230
    Width = 33
    Height = 21
    TabOrder = 65
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000105'
    RegBits = 4
    RegStart = 4
    TextType = ttInt
  end
  object RegScrollBar34: TRegScrollBar
    Left = 288
    Top = 252
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 66
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000102'
    RegBits = 4
  end
  object RegEdit34: TRegEdit
    Left = 408
    Top = 250
    Width = 33
    Height = 21
    TabOrder = 67
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000102'
    RegBits = 4
    TextType = ttInt
  end
  object RegScrollBar35: TRegScrollBar
    Left = 288
    Top = 272
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 68
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000102'
    RegBits = 4
    RegStart = 4
  end
  object RegEdit35: TRegEdit
    Left = 408
    Top = 270
    Width = 33
    Height = 21
    TabOrder = 69
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000102'
    RegBits = 4
    RegStart = 4
    TextType = ttInt
  end
  object RegScrollBar36: TRegScrollBar
    Left = 288
    Top = 292
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 70
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000A85'
    RegBits = 4
  end
  object RegEdit36: TRegEdit
    Left = 408
    Top = 290
    Width = 33
    Height = 21
    TabOrder = 71
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000A85'
    RegBits = 4
    TextType = ttInt
  end
  object RegScrollBar37: TRegScrollBar
    Left = 288
    Top = 312
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 72
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000A84'
    RegBits = 4
  end
  object RegEdit37: TRegEdit
    Left = 408
    Top = 310
    Width = 33
    Height = 21
    TabOrder = 73
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000A84'
    RegBits = 4
    TextType = ttInt
  end
  object RegScrollBar38: TRegScrollBar
    Left = 288
    Top = 332
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 74
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000A85'
    RegBits = 4
    RegStart = 4
  end
  object RegEdit38: TRegEdit
    Left = 408
    Top = 330
    Width = 33
    Height = 21
    TabOrder = 75
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000A85'
    RegBits = 4
    RegStart = 4
    TextType = ttInt
  end
  object RegScrollBar39: TRegScrollBar
    Left = 288
    Top = 352
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 76
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000A84'
    RegBits = 4
    RegStart = 4
  end
  object RegEdit39: TRegEdit
    Left = 408
    Top = 350
    Width = 33
    Height = 21
    TabOrder = 77
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000A84'
    RegBits = 4
    RegStart = 4
    TextType = ttInt
  end
  object RegScrollBar40: TRegScrollBar
    Left = 288
    Top = 372
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 78
    Visible = False
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000A84'
    RegBits = 4
    RegStart = 4
  end
  object RegEdit40: TRegEdit
    Left = 408
    Top = 370
    Width = 33
    Height = 21
    TabOrder = 79
    Visible = False
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000A84'
    RegBits = 4
    RegStart = 4
    TextType = ttInt
  end
  object RegScrollBar41: TRegScrollBar
    Left = 288
    Top = 392
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 80
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0001188'
    RegBits = 5
  end
  object RegEdit41: TRegEdit
    Left = 408
    Top = 390
    Width = 33
    Height = 21
    TabOrder = 81
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0001188'
    RegBits = 5
    TextType = ttInt
  end
  object RegScrollBar42: TRegScrollBar
    Left = 288
    Top = 412
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 82
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0001189'
    RegBits = 5
  end
  object RegEdit42: TRegEdit
    Left = 408
    Top = 410
    Width = 33
    Height = 21
    TabOrder = 83
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0001189'
    RegBits = 5
    TextType = ttInt
  end
  object RegScrollBar43: TRegScrollBar
    Left = 288
    Top = 432
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 84
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000103'
    RegBits = 4
  end
  object RegEdit43: TRegEdit
    Left = 408
    Top = 430
    Width = 33
    Height = 21
    TabOrder = 85
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000103'
    RegBits = 4
    TextType = ttInt
  end
  object RegScrollBar44: TRegScrollBar
    Left = 288
    Top = 452
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 86
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000203'
    RegBits = 5
  end
  object RegEdit44: TRegEdit
    Left = 408
    Top = 450
    Width = 33
    Height = 21
    TabOrder = 87
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000203'
    RegBits = 5
    TextType = ttInt
  end
  object RegCheckBox4: TRegCheckBox
    Left = 448
    Top = 92
    Width = 71
    Height = 17
    Caption = 'pre fetch'
    TabOrder = 88
    RegAddress = '0xE0000B5F'
  end
  object RegCheckBox5: TRegCheckBox
    Left = 448
    Top = 112
    Width = 71
    Height = 17
    Caption = 'pre fetch'
    TabOrder = 89
    RegAddress = '0xE0000B5F'
    RegBit = 1
  end
  object RegCheckBox6: TRegCheckBox
    Left = 448
    Top = 132
    Width = 71
    Height = 17
    Caption = 'pre fetch'
    TabOrder = 90
    RegAddress = '0xE0000B5F'
    RegBit = 2
  end
  object RegCheckBox7: TRegCheckBox
    Left = 448
    Top = 152
    Width = 71
    Height = 17
    Caption = 'pre fetch'
    TabOrder = 91
    RegAddress = '0xE0000B5F'
    RegBit = 3
  end
  object RegCheckBox8: TRegCheckBox
    Left = 448
    Top = 172
    Width = 58
    Height = 17
    Caption = 'error'
    TabOrder = 92
    RegAddress = '0xE000015A'
  end
  object RegCheckBox9: TRegCheckBox
    Left = 448
    Top = 192
    Width = 58
    Height = 17
    Caption = 'error'
    TabOrder = 93
    RegAddress = '0xE000015A'
    RegBit = 1
  end
  object RegCheckBox10: TRegCheckBox
    Left = 448
    Top = 212
    Width = 58
    Height = 17
    Caption = 'error'
    TabOrder = 94
    RegAddress = '0xE000015A'
    RegBit = 2
  end
  object RegCheckBox11: TRegCheckBox
    Left = 448
    Top = 232
    Width = 58
    Height = 17
    Caption = 'error'
    TabOrder = 95
    RegAddress = '0xE000015A'
    RegBit = 3
  end
  object RegCheckBox12: TRegCheckBox
    Left = 448
    Top = 252
    Width = 58
    Height = 17
    Caption = 'error'
    TabOrder = 96
    RegAddress = '0xE000015A'
    RegBit = 4
  end
  object RegCheckBox13: TRegCheckBox
    Left = 448
    Top = 272
    Width = 58
    Height = 17
    Caption = 'error'
    TabOrder = 97
    RegAddress = '0xE000015A'
    RegBit = 5
  end
  object RegCheckBox14: TRegCheckBox
    Left = 448
    Top = 292
    Width = 58
    Height = 17
    Caption = 'error'
    TabOrder = 98
    RegAddress = '0xE0000A95'
  end
  object RegCheckBox15: TRegCheckBox
    Left = 448
    Top = 312
    Width = 58
    Height = 17
    Caption = 'error'
    TabOrder = 99
    RegAddress = '0xE0000A95'
    RegBit = 2
  end
  object RegCheckBox16: TRegCheckBox
    Left = 448
    Top = 332
    Width = 58
    Height = 17
    Caption = 'error'
    TabOrder = 100
    RegAddress = '0xE0000A95'
    RegBit = 1
  end
  object RegCheckBox17: TRegCheckBox
    Left = 448
    Top = 352
    Width = 58
    Height = 17
    Caption = 'error'
    TabOrder = 101
    RegAddress = '0xE0000A95'
    RegBit = 3
  end
  object RegCheckBox18: TRegCheckBox
    Left = 448
    Top = 372
    Width = 58
    Height = 17
    Caption = 'error'
    TabOrder = 102
    RegAddress = '0xE0000A95'
    RegBit = 4
  end
  object RegCheckBox19: TRegCheckBox
    Left = 448
    Top = 392
    Width = 58
    Height = 17
    Caption = 'error'
    TabOrder = 103
    RegAddress = '0xE0001180'
  end
  object RegCheckBox20: TRegCheckBox
    Left = 448
    Top = 412
    Width = 58
    Height = 17
    Caption = 'error'
    TabOrder = 104
    RegAddress = '0xE0001180'
    RegBit = 1
  end
  object RegCheckBox21: TRegCheckBox
    Left = 448
    Top = 432
    Width = 58
    Height = 17
    Caption = 'error'
    TabOrder = 105
    RegAddress = '0xE000015A'
    RegBit = 6
  end
  object RegCheckBox22: TRegCheckBox
    Left = 448
    Top = 452
    Width = 65
    Height = 17
    Caption = 'pre fetch'
    TabOrder = 106
    RegAddress = '0xE000020F'
  end
  object RegCheckBox23: TRegCheckBox
    Left = 88
    Top = 32
    Width = 25
    Height = 17
    TabOrder = 107
    RegAddress = '0xE0000B17'
  end
  object RegCheckBox24: TRegCheckBox
    Left = 88
    Top = 52
    Width = 25
    Height = 17
    TabOrder = 108
    RegAddress = '0xE0000B17'
    RegBit = 1
  end
  object RegCheckBox25: TRegCheckBox
    Left = 88
    Top = 72
    Width = 25
    Height = 17
    TabOrder = 109
    RegAddress = '0xE0000B17'
    RegBit = 2
  end
  object RegCheckBox26: TRegCheckBox
    Left = 88
    Top = 92
    Width = 25
    Height = 17
    TabOrder = 110
    RegAddress = '0xE0000B17'
    RegBit = 3
  end
  object RegCheckBox27: TRegCheckBox
    Left = 88
    Top = 112
    Width = 25
    Height = 17
    TabOrder = 111
    RegAddress = '0xE0000B17'
    RegBit = 4
  end
  object RegCheckBox28: TRegCheckBox
    Left = 88
    Top = 132
    Width = 25
    Height = 17
    TabOrder = 112
    RegAddress = '0xE0000B17'
    RegBit = 5
  end
  object RegCheckBox29: TRegCheckBox
    Left = 88
    Top = 152
    Width = 25
    Height = 17
    TabOrder = 113
    RegAddress = '0xE0000B17'
    RegBit = 6
  end
  object RegCheckBox30: TRegCheckBox
    Left = 88
    Top = 172
    Width = 25
    Height = 17
    TabOrder = 114
    RegAddress = '0xE000015B'
  end
  object RegCheckBox31: TRegCheckBox
    Left = 88
    Top = 192
    Width = 25
    Height = 17
    TabOrder = 115
    RegAddress = '0xE000015B'
    RegBit = 1
  end
  object RegCheckBox32: TRegCheckBox
    Left = 88
    Top = 212
    Width = 25
    Height = 17
    TabOrder = 116
    RegAddress = '0xE000015B'
    RegBit = 2
  end
  object RegCheckBox33: TRegCheckBox
    Left = 88
    Top = 232
    Width = 25
    Height = 17
    TabOrder = 117
    RegAddress = '0xE000015B'
    RegBit = 3
  end
  object RegCheckBox34: TRegCheckBox
    Left = 88
    Top = 252
    Width = 25
    Height = 17
    TabOrder = 118
    RegAddress = '0xE000015B'
    RegBit = 4
  end
  object RegCheckBox35: TRegCheckBox
    Left = 88
    Top = 272
    Width = 25
    Height = 17
    TabOrder = 119
    RegAddress = '0xE000015B'
    RegBit = 5
  end
  object RegCheckBox36: TRegCheckBox
    Left = 88
    Top = 292
    Width = 25
    Height = 17
    TabOrder = 120
    RegAddress = '0xE0000A80'
  end
  object RegCheckBox37: TRegCheckBox
    Left = 88
    Top = 312
    Width = 25
    Height = 17
    TabOrder = 121
    RegAddress = '0xE0000A80'
    RegBit = 2
  end
  object RegCheckBox38: TRegCheckBox
    Left = 88
    Top = 332
    Width = 25
    Height = 17
    TabOrder = 122
    RegAddress = '0xE0000A80'
    RegBit = 1
  end
  object RegCheckBox39: TRegCheckBox
    Left = 88
    Top = 352
    Width = 25
    Height = 17
    TabOrder = 123
    RegAddress = '0xE0000A80'
    RegBit = 3
  end
  object RegCheckBox40: TRegCheckBox
    Left = 88
    Top = 372
    Width = 25
    Height = 17
    TabOrder = 124
    RegAddress = '0xE0000A80'
    RegBit = 4
  end
  object RegCheckBox41: TRegCheckBox
    Left = 88
    Top = 392
    Width = 25
    Height = 17
    TabOrder = 125
    RegAddress = '0xE000118C'
  end
  object RegCheckBox42: TRegCheckBox
    Left = 88
    Top = 412
    Width = 25
    Height = 17
    TabOrder = 126
    RegAddress = '0xE000118C'
    RegBit = 1
  end
  object RegCheckBox43: TRegCheckBox
    Left = 88
    Top = 432
    Width = 25
    Height = 17
    TabOrder = 127
    RegAddress = '0xE000015B'
    RegBit = 5
  end
  object RegCheckBox44: TRegCheckBox
    Left = 88
    Top = 452
    Width = 25
    Height = 17
    TabOrder = 128
    RegAddress = '0xE0000200'
  end
  object Panel1: TPanel
    Left = 654
    Top = 0
    Width = 500
    Height = 595
    Align = alRight
    BevelOuter = bvNone
    TabOrder = 129
  end
  object RegCheckBox45: TRegCheckBox
    Left = 520
    Top = 32
    Width = 69
    Height = 17
    Caption = 'line write'
    TabOrder = 130
    RegAddress = '0xE0000B60'
  end
  object RegCheckBox46: TRegCheckBox
    Left = 520
    Top = 52
    Width = 69
    Height = 17
    Caption = 'line write'
    TabOrder = 131
    RegAddress = '0xE0000B60'
    RegBit = 1
  end
  object RegCheckBox47: TRegCheckBox
    Left = 520
    Top = 72
    Width = 69
    Height = 17
    Caption = 'line write'
    TabOrder = 132
    RegAddress = '0xE0000B60'
    RegBit = 2
  end
  object RegCheckBox48: TRegCheckBox
    Left = 520
    Top = 92
    Width = 69
    Height = 17
    Caption = 'line write'
    TabOrder = 133
    RegAddress = '0xE0000B60'
    RegBit = 3
  end
  object RegCheckBox49: TRegCheckBox
    Left = 520
    Top = 112
    Width = 69
    Height = 17
    Caption = 'line write'
    TabOrder = 134
    RegAddress = '0xE0000B60'
    RegBit = 4
  end
  object RegCheckBox50: TRegCheckBox
    Left = 520
    Top = 132
    Width = 69
    Height = 17
    Caption = 'line write'
    TabOrder = 135
    RegAddress = '0xE0000B60'
    RegBit = 5
  end
  object RegCheckBox51: TRegCheckBox
    Left = 520
    Top = 152
    Width = 69
    Height = 17
    Caption = 'line write'
    TabOrder = 136
    RegAddress = '0xE0000B60'
    RegBit = 6
  end
  object RegCheckBox52: TRegCheckBox
    Left = 592
    Top = 32
    Width = 58
    Height = 17
    Caption = 'frame'
    TabOrder = 137
    RegAddress = '0xE0000B61'
  end
  object RegCheckBox53: TRegCheckBox
    Left = 592
    Top = 52
    Width = 58
    Height = 17
    Caption = 'frame'
    TabOrder = 138
    RegAddress = '0xE0000B61'
    RegBit = 1
  end
  object RegCheckBox54: TRegCheckBox
    Left = 592
    Top = 72
    Width = 58
    Height = 17
    Caption = 'frame'
    TabOrder = 139
    RegAddress = '0xE0000B61'
    RegBit = 2
  end
  object RegCheckBox55: TRegCheckBox
    Left = 592
    Top = 92
    Width = 58
    Height = 17
    Caption = 'frame'
    TabOrder = 140
    RegAddress = '0xE0000B61'
    RegBit = 3
  end
  object RegCheckBox56: TRegCheckBox
    Left = 592
    Top = 112
    Width = 58
    Height = 17
    Caption = 'frame'
    TabOrder = 141
    RegAddress = '0xE0000B61'
    RegBit = 4
  end
  object RegCheckBox57: TRegCheckBox
    Left = 592
    Top = 130
    Width = 58
    Height = 21
    Caption = 'frame'
    TabOrder = 142
    RegAddress = '0xE0000B61'
    RegBit = 5
  end
  object RegCheckBox58: TRegCheckBox
    Left = 592
    Top = 152
    Width = 58
    Height = 17
    Caption = 'frame'
    TabOrder = 143
    RegAddress = '0xE0000B61'
    RegBit = 6
  end
  object RegCheckBox1: TRegCheckBox
    Left = 520
    Top = 452
    Width = 65
    Height = 17
    Caption = 'line write'
    TabOrder = 144
    RegAddress = '1'
  end
  object RegCheckBox2: TRegCheckBox
    Left = 592
    Top = 452
    Width = 58
    Height = 17
    Caption = 'read'
    TabOrder = 145
    RegAddress = '2'
  end
  object refresh: TButton
    Left = 16
    Top = 536
    Width = 75
    Height = 25
    Caption = 'refresh'
    TabOrder = 146
    OnClick = refreshClick
  end
  object RegCheckBox3: TRegCheckBox
    Left = 88
    Top = 480
    Width = 73
    Height = 17
    Caption = 'dma reset'
    TabOrder = 147
    RegAddress = '0xE0000B17'
    RegBit = 7
  end
  object RegScrollBar45: TRegScrollBar
    Left = 288
    Top = 480
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 148
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000A90'
    RegBits = 6
  end
  object RegEdit45: TRegEdit
    Left = 408
    Top = 478
    Width = 33
    Height = 21
    TabOrder = 149
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000A90'
    RegBits = 6
    TextType = ttInt
  end
  object RegScrollBar46: TRegScrollBar
    Left = 288
    Top = 500
    Width = 121
    Height = 17
    Max = 0
    PageSize = 0
    TabOrder = 150
    OnScroll = RegScrollBar1Scroll
    RegStartAddress = '0xE0000A91'
    RegBits = 6
  end
  object RegEdit46: TRegEdit
    Left = 408
    Top = 498
    Width = 33
    Height = 21
    TabOrder = 151
    OnExit = RegEdit1Exit
    OnKeyPress = RegEdit1KeyPress
    RegStartAddress = '0xE0000A91'
    RegBits = 6
    TextType = ttInt
  end
end
