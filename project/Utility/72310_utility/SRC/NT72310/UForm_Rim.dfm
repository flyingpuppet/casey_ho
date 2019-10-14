inherited Form_Rim: TForm_Rim
  Left = 251
  Top = 0
  Width = 1007
  Height = 734
  Caption = 'Rim'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  object setting_GroupBox: TGroupBox
    Left = 544
    Top = 184
    Width = 193
    Height = 273
    Caption = 'Thresholds'
    TabOrder = 4
    object Label36: TLabel
      Left = 24
      Top = 24
      Width = 42
      Height = 13
      Caption = 'V_THD1'
    end
    object Label37: TLabel
      Left = 24
      Top = 48
      Width = 42
      Height = 13
      Caption = 'V_THD2'
    end
    object Label38: TLabel
      Left = 24
      Top = 72
      Width = 42
      Height = 13
      Caption = 'V_THD3'
    end
    object Label39: TLabel
      Left = 8
      Top = 96
      Width = 56
      Height = 13
      Caption = 'H_THD1_B'
    end
    object Label40: TLabel
      Left = 8
      Top = 120
      Width = 56
      Height = 13
      Caption = 'H_THD2_B'
    end
    object Label41: TLabel
      Left = 8
      Top = 144
      Width = 56
      Height = 13
      Caption = 'H_THD3_B'
    end
    object Label42: TLabel
      Left = 8
      Top = 168
      Width = 55
      Height = 13
      Caption = 'H_THD1_F'
    end
    object Label43: TLabel
      Left = 8
      Top = 192
      Width = 55
      Height = 13
      Caption = 'H_THD2_F'
    end
    object Label44: TLabel
      Left = 8
      Top = 216
      Width = 55
      Height = 13
      Caption = 'H_THD3_F'
    end
    object Label45: TLabel
      Left = 8
      Top = 240
      Width = 56
      Height = 13
      Caption = 'Black_THD'
    end
    object Edit49: TRegEdit
      Left = 88
      Top = 65
      Width = 33
      Height = 21
      Color = clMoneyGreen
      TabOrder = 0
      Text = '400'
      RegStartAddress = '0xE00001A6'
      RegBits = 12
      RegStart = 4
      TextType = ttInt
    end
    object Edit48: TRegEdit
      Left = 88
      Top = 41
      Width = 33
      Height = 21
      Color = clMoneyGreen
      TabOrder = 1
      Text = '300'
      RegStartAddress = '0xE00001A5'
      RegBits = 12
      TextType = ttInt
    end
    object Edit47: TRegEdit
      Left = 88
      Top = 17
      Width = 33
      Height = 21
      Color = clMoneyGreen
      TabOrder = 2
      Text = '100'
      OnChange = Edit47Change
      RegStartAddress = '0xE00001A3'
      RegBits = 12
      RegStart = 4
      TextType = ttInt
    end
    object Edit50: TRegEdit
      Tag = 3
      Left = 88
      Top = 88
      Width = 33
      Height = 21
      Color = clScrollBar
      TabOrder = 3
      Text = '100'
      OnChange = Edit50Change
      OnKeyPress = Edit51KeyPress
      RegStartAddress = '0xE00001A8'
      RegBits = 8
      TextType = ttInt
    end
    object Edit51: TRegEdit
      Tag = 2
      Left = 88
      Top = 112
      Width = 33
      Height = 21
      Color = clInactiveBorder
      TabOrder = 4
      Text = '200'
      OnChange = Edit51Change
      OnKeyPress = Edit51KeyPress
      RegStartAddress = '0xE00001A9'
      RegBits = 8
      TextType = ttInt
    end
    object Edit52: TRegEdit
      Tag = 1
      Left = 88
      Top = 136
      Width = 33
      Height = 21
      Color = clInactiveBorder
      TabOrder = 5
      Text = '400'
      OnKeyPress = Edit51KeyPress
      RegStartAddress = '0xE00001AA'
      RegBits = 8
      TextType = ttInt
    end
    object Edit53: TRegEdit
      Tag = 3
      Left = 88
      Top = 160
      Width = 33
      Height = 21
      Color = clMoneyGreen
      TabOrder = 6
      Text = '100'
      OnKeyPress = Edit51KeyPress
      RegStartAddress = '0xE00001AC'
      RegBits = 8
      TextType = ttInt
    end
    object Edit54: TRegEdit
      Tag = 2
      Left = 88
      Top = 184
      Width = 33
      Height = 21
      Color = clMoneyGreen
      TabOrder = 7
      Text = '200'
      OnKeyPress = Edit51KeyPress
      RegStartAddress = '0xE00001AD'
      RegBits = 8
      TextType = ttInt
    end
    object Edit55: TRegEdit
      Tag = 1
      Left = 88
      Top = 208
      Width = 33
      Height = 21
      Color = clMoneyGreen
      TabOrder = 8
      Text = '200'
      OnKeyPress = Edit51KeyPress
      RegStartAddress = '0xE00001AE'
      RegBits = 8
      TextType = ttInt
    end
    object Button1: TButton
      Left = 128
      Top = 16
      Width = 57
      Height = 241
      Caption = 'reset'
      TabOrder = 9
      OnClick = Button1Click
    end
    object Edit56: TRegEdit
      Left = 88
      Top = 232
      Width = 33
      Height = 21
      Color = clInactiveBorder
      TabOrder = 10
      Text = '12'
      RegStartAddress = '0xE00001A2'
      RegBits = 8
      TextType = ttInt
    end
  end
  object posi_cnt_detail_GroupBox: TGroupBox
    Left = 8
    Top = 240
    Width = 529
    Height = 233
    Caption = 'posi_cnt_detail_GroupBox'
    TabOrder = 1
    object Label35: TLabel
      Left = 40
      Top = 204
      Width = 46
      Height = 13
      Caption = 'RIGHT_F'
    end
    object Label34: TLabel
      Left = 40
      Top = 180
      Width = 38
      Height = 13
      Caption = 'LEFT_F'
    end
    object Label33: TLabel
      Left = 296
      Top = 65
      Width = 34
      Height = 13
      Caption = 'CNT_3'
    end
    object Label32: TLabel
      Left = 256
      Top = 65
      Width = 37
      Height = 13
      Caption = 'POSI_3'
    end
    object Label31: TLabel
      Left = 216
      Top = 65
      Width = 34
      Height = 13
      Caption = 'CNT_2'
    end
    object Label30: TLabel
      Left = 176
      Top = 65
      Width = 37
      Height = 13
      Caption = 'POSI_2'
    end
    object Label29: TLabel
      Left = 136
      Top = 65
      Width = 34
      Height = 13
      Caption = 'CNT_1'
    end
    object Label28: TLabel
      Left = 96
      Top = 65
      Width = 37
      Height = 13
      Caption = 'POSI_1'
    end
    object Label27: TLabel
      Left = 40
      Top = 156
      Width = 47
      Height = 13
      Caption = 'RIGHT_B'
    end
    object Label26: TLabel
      Left = 40
      Top = 132
      Width = 39
      Height = 13
      Caption = 'LEFT_B'
    end
    object Label25: TLabel
      Left = 40
      Top = 108
      Width = 35
      Height = 13
      Caption = 'DOWN'
    end
    object Label24: TLabel
      Left = 40
      Top = 84
      Width = 15
      Height = 13
      Caption = 'UP'
    end
    object Label12: TLabel
      Left = 379
      Top = 64
      Width = 17
      Height = 13
      AutoSize = False
      Caption = '1'
    end
    object Label13: TLabel
      Left = 411
      Top = 64
      Width = 17
      Height = 13
      AutoSize = False
      Caption = '2'
    end
    object Label14: TLabel
      Left = 443
      Top = 64
      Width = 17
      Height = 13
      AutoSize = False
      Caption = '3'
    end
    object Edit11: TRegEdit
      Left = 96
      Top = 80
      Width = 41
      Height = 21
      Color = clInfoBk
      TabOrder = 0
      Text = '0'
      OnChange = Edit11Change
      RegStartAddress = '0xE00001B1'
      RegBits = 12
      TextType = ttInt
    end
    object Edit46: TRegEdit
      Tag = 1
      Left = 296
      Top = 201
      Width = 41
      Height = 21
      Color = clSkyBlue
      TabOrder = 1
      Text = '0'
      OnKeyPress = Edit51KeyPress
      RegStartAddress = '0xE00001E2'
      RegBits = 8
      TextType = ttInt
    end
    object Edit45: TRegEdit
      Left = 256
      Top = 201
      Width = 41
      Height = 21
      Color = clInfoBk
      TabOrder = 2
      Text = '1920'
      RegStartAddress = '0xE00001DA'
      RegBits = 12
      TextType = ttInt
    end
    object Edit44: TRegEdit
      Tag = 2
      Left = 216
      Top = 201
      Width = 41
      Height = 21
      Color = clSkyBlue
      TabOrder = 3
      Text = '0'
      OnKeyPress = Edit51KeyPress
      RegStartAddress = '0xE00001E1'
      RegBits = 8
      TextType = ttInt
    end
    object Edit43: TRegEdit
      Left = 176
      Top = 201
      Width = 41
      Height = 21
      Color = clInfoBk
      TabOrder = 4
      Text = '1920'
      RegStartAddress = '0xE00001D9'
      RegBits = 12
      TextType = ttInt
    end
    object Edit42: TRegEdit
      Tag = 3
      Left = 136
      Top = 201
      Width = 41
      Height = 21
      Color = clSkyBlue
      TabOrder = 5
      Text = '0'
      OnKeyPress = Edit51KeyPress
      RegStartAddress = '0xE00001E0'
      RegBits = 8
      TextType = ttInt
    end
    object Edit41: TRegEdit
      Left = 96
      Top = 201
      Width = 41
      Height = 21
      Color = clInfoBk
      TabOrder = 6
      Text = '1920'
      RegStartAddress = '0xE00001D7'
      RegBits = 12
      RegStart = 4
      TextType = ttInt
    end
    object Edit40: TRegEdit
      Tag = 1
      Left = 296
      Top = 177
      Width = 41
      Height = 21
      Color = clSkyBlue
      TabOrder = 7
      Text = '0'
      OnKeyPress = Edit51KeyPress
      RegStartAddress = '0xE00001DE'
      RegBits = 8
      TextType = ttInt
    end
    object Edit39: TRegEdit
      Left = 256
      Top = 177
      Width = 41
      Height = 21
      Color = clInfoBk
      TabOrder = 8
      Text = '0'
      RegStartAddress = '0xE00001D6'
      RegBits = 12
      TextType = ttInt
    end
    object Edit38: TRegEdit
      Tag = 2
      Left = 216
      Top = 177
      Width = 41
      Height = 21
      Color = clSkyBlue
      TabOrder = 9
      Text = '0'
      OnKeyPress = Edit51KeyPress
      RegStartAddress = '0xE00001DD'
      RegBits = 8
      TextType = ttInt
    end
    object Edit37: TRegEdit
      Left = 176
      Top = 177
      Width = 41
      Height = 21
      Color = clInfoBk
      TabOrder = 10
      Text = '0'
      RegStartAddress = '0xE00001D4'
      RegBits = 12
      RegStart = 4
      TextType = ttInt
    end
    object Edit36: TRegEdit
      Tag = 3
      Left = 136
      Top = 177
      Width = 41
      Height = 21
      Color = clSkyBlue
      TabOrder = 11
      Text = '0'
      OnKeyPress = Edit51KeyPress
      RegStartAddress = '0xE00001DC'
      RegBits = 8
      TextType = ttInt
    end
    object Edit35: TRegEdit
      Left = 96
      Top = 177
      Width = 41
      Height = 21
      Color = clInfoBk
      TabOrder = 12
      Text = '0'
      RegStartAddress = '0xE00001D3'
      RegBits = 12
      TextType = ttInt
    end
    object Edit34: TRegEdit
      Tag = 1
      Left = 296
      Top = 153
      Width = 41
      Height = 21
      Color = clSkyBlue
      TabOrder = 13
      Text = '0'
      OnKeyPress = Edit51KeyPress
      RegStartAddress = '0xE00001D0'
      RegBits = 8
      TextType = ttInt
    end
    object Edit33: TRegEdit
      Left = 256
      Top = 153
      Width = 41
      Height = 21
      Color = clInfoBk
      TabOrder = 14
      Text = '1920'
      RegStartAddress = '0xE00001C9'
      RegBits = 8
      TextType = ttInt
    end
    object Edit32: TRegEdit
      Tag = 2
      Left = 216
      Top = 153
      Width = 41
      Height = 21
      Color = clSkyBlue
      TabOrder = 15
      Text = '0'
      OnKeyPress = Edit51KeyPress
      RegStartAddress = '0xE00001CF'
      RegBits = 8
      TextType = ttInt
    end
    object Edit31: TRegEdit
      Left = 176
      Top = 153
      Width = 41
      Height = 21
      Color = clInfoBk
      TabOrder = 16
      Text = '1920'
      RegStartAddress = '0xE00001C8'
      RegBits = 8
      TextType = ttInt
    end
    object Edit30: TRegEdit
      Tag = 3
      Left = 136
      Top = 153
      Width = 41
      Height = 21
      Color = clSkyBlue
      TabOrder = 17
      Text = '0'
      OnKeyPress = Edit51KeyPress
      RegStartAddress = '0xE00001CE'
      RegBits = 8
      TextType = ttInt
    end
    object Edit29: TRegEdit
      Left = 96
      Top = 153
      Width = 41
      Height = 21
      Color = clInfoBk
      TabOrder = 18
      Text = '1920'
      RegStartAddress = '0xE00001C7'
      RegBits = 8
      TextType = ttInt
    end
    object Edit28: TRegEdit
      Tag = 1
      Left = 296
      Top = 129
      Width = 41
      Height = 21
      Color = clSkyBlue
      TabOrder = 19
      Text = '0'
      OnKeyPress = Edit51KeyPress
      RegStartAddress = '0xE00001CC'
      RegBits = 8
      TextType = ttInt
    end
    object Edit27: TRegEdit
      Left = 256
      Top = 129
      Width = 41
      Height = 21
      Color = clInfoBk
      TabOrder = 20
      Text = '0'
      RegStartAddress = '0xE00001C6'
      RegBits = 8
      TextType = ttInt
    end
    object Edit26: TRegEdit
      Tag = 2
      Left = 216
      Top = 129
      Width = 41
      Height = 21
      Color = clSkyBlue
      TabOrder = 21
      Text = '0'
      OnKeyPress = Edit51KeyPress
      RegStartAddress = '0xE00001CB'
      RegBits = 8
      TextType = ttInt
    end
    object Edit25: TRegEdit
      Left = 176
      Top = 129
      Width = 41
      Height = 21
      Color = clInfoBk
      TabOrder = 22
      Text = '0'
      RegStartAddress = '0xE00001C5'
      RegBits = 8
      TextType = ttInt
    end
    object Edit24: TRegEdit
      Tag = 3
      Left = 136
      Top = 129
      Width = 41
      Height = 21
      Color = clSkyBlue
      TabOrder = 23
      Text = '0'
      OnKeyPress = Edit51KeyPress
      RegStartAddress = '0xE00001CA'
      RegBits = 8
      TextType = ttInt
    end
    object Edit23: TRegEdit
      Left = 96
      Top = 129
      Width = 41
      Height = 21
      Color = clInfoBk
      TabOrder = 24
      Text = '0'
      RegStartAddress = '0xE00001C4'
      RegBits = 8
      TextType = ttInt
    end
    object Edit22: TRegEdit
      Left = 296
      Top = 105
      Width = 41
      Height = 21
      Color = clSkyBlue
      TabOrder = 25
      Text = '0'
      RegStartAddress = '0xE00001C1'
      RegBits = 12
      RegStart = 4
      TextType = ttInt
    end
    object Edit21: TRegEdit
      Left = 256
      Top = 105
      Width = 41
      Height = 21
      Color = clInfoBk
      TabOrder = 26
      Text = '1080'
      RegStartAddress = '0xE00001B8'
      RegBits = 12
      RegStart = 4
      TextType = ttInt
    end
    object Edit20: TRegEdit
      Left = 216
      Top = 105
      Width = 41
      Height = 21
      Color = clSkyBlue
      TabOrder = 27
      Text = '0'
      RegStartAddress = '0xE00001C0'
      RegBits = 12
      TextType = ttInt
    end
    object Edit19: TRegEdit
      Left = 176
      Top = 105
      Width = 41
      Height = 21
      Color = clInfoBk
      TabOrder = 28
      Text = '1080'
      RegStartAddress = '0xE00001B7'
      RegBits = 12
      TextType = ttInt
    end
    object Edit18: TRegEdit
      Left = 136
      Top = 105
      Width = 41
      Height = 21
      Color = clSkyBlue
      TabOrder = 29
      Text = '0'
      RegStartAddress = '0xE00001BE'
      RegBits = 12
      RegStart = 4
      TextType = ttInt
    end
    object Edit17: TRegEdit
      Left = 96
      Top = 105
      Width = 41
      Height = 21
      Color = clInfoBk
      TabOrder = 30
      Text = '1080'
      RegStartAddress = '0xE00001B5'
      RegBits = 12
      RegStart = 4
      TextType = ttInt
    end
    object Edit16: TRegEdit
      Left = 296
      Top = 81
      Width = 41
      Height = 21
      Color = clSkyBlue
      TabOrder = 31
      Text = '0'
      RegStartAddress = '0xE00001BD'
      RegBits = 12
      TextType = ttInt
    end
    object Edit15: TRegEdit
      Left = 256
      Top = 81
      Width = 41
      Height = 21
      Color = clInfoBk
      TabOrder = 32
      Text = '0'
      RegStartAddress = '0xE00001B4'
      RegBits = 12
      TextType = ttInt
    end
    object Edit14: TRegEdit
      Left = 216
      Top = 81
      Width = 41
      Height = 21
      Color = clSkyBlue
      TabOrder = 33
      Text = '0'
      RegStartAddress = '0xE00001BB'
      RegBits = 12
      RegStart = 4
      TextType = ttInt
    end
    object Edit13: TRegEdit
      Left = 176
      Top = 81
      Width = 41
      Height = 21
      Color = clInfoBk
      TabOrder = 34
      Text = '0'
      RegStartAddress = '0xE00001B2'
      RegBits = 12
      RegStart = 4
      TextType = ttInt
    end
    object Edit12: TRegEdit
      Left = 136
      Top = 81
      Width = 41
      Height = 21
      Color = clSkyBlue
      TabOrder = 35
      Text = '0'
      RegStartAddress = '0xE00001BA'
      RegBits = 12
      TextType = ttInt
    end
    object Show_rim_detail: TRegCheckBox
      Left = 16
      Top = 32
      Width = 145
      Height = 17
      Caption = 'Show_rim_detail'
      TabOrder = 36
    end
    object Button3: TButton
      Left = 128
      Top = 16
      Width = 97
      Height = 25
      Caption = 'Show rim detail'
      TabOrder = 37
      OnClick = Button3Click
    end
    object RegCheckBox1: TRegCheckBox
      Left = 376
      Top = 82
      Width = 25
      Height = 17
      TabOrder = 38
      RegAddress = '0xE00001B0'
    end
    object RegCheckBox2: TRegCheckBox
      Left = 408
      Top = 82
      Width = 25
      Height = 17
      TabOrder = 39
      RegAddress = '0xE00001B0'
      RegBit = 1
    end
    object RegCheckBox3: TRegCheckBox
      Left = 440
      Top = 82
      Width = 25
      Height = 17
      TabOrder = 40
      RegAddress = '0xE00001B0'
      RegBit = 2
    end
    object RegCheckBox4: TRegCheckBox
      Left = 376
      Top = 106
      Width = 25
      Height = 17
      TabOrder = 41
      RegAddress = '0xE00001B0'
      RegBit = 3
    end
    object RegCheckBox5: TRegCheckBox
      Left = 408
      Top = 106
      Width = 25
      Height = 17
      TabOrder = 42
      RegAddress = '0xE00001B0'
      RegBit = 4
    end
    object RegCheckBox6: TRegCheckBox
      Left = 440
      Top = 106
      Width = 25
      Height = 17
      TabOrder = 43
      RegAddress = '0xE00001B0'
      RegBit = 5
    end
    object RegCheckBox7: TRegCheckBox
      Left = 376
      Top = 131
      Width = 25
      Height = 17
      TabOrder = 44
      RegAddress = '0xE00001C3'
    end
    object RegCheckBox8: TRegCheckBox
      Left = 408
      Top = 131
      Width = 25
      Height = 17
      TabOrder = 45
      RegAddress = '0xE00001C3'
      RegBit = 1
    end
    object RegCheckBox9: TRegCheckBox
      Left = 440
      Top = 131
      Width = 25
      Height = 17
      TabOrder = 46
      RegAddress = '0xE00001C3'
      RegBit = 2
    end
    object RegCheckBox10: TRegCheckBox
      Left = 376
      Top = 155
      Width = 25
      Height = 17
      TabOrder = 47
      RegAddress = '0xE00001C3'
      RegBit = 3
    end
    object RegCheckBox11: TRegCheckBox
      Left = 408
      Top = 155
      Width = 25
      Height = 17
      TabOrder = 48
      RegAddress = '0xE00001C3'
      RegBit = 4
    end
    object RegCheckBox12: TRegCheckBox
      Left = 440
      Top = 155
      Width = 25
      Height = 17
      TabOrder = 49
      RegAddress = '0xE00001C3'
      RegBit = 5
    end
    object RegCheckBox13: TRegCheckBox
      Left = 376
      Top = 178
      Width = 25
      Height = 17
      TabOrder = 50
      RegAddress = '0xE00001D2'
    end
    object RegCheckBox14: TRegCheckBox
      Left = 408
      Top = 178
      Width = 25
      Height = 17
      TabOrder = 51
      RegAddress = '0xE00001D2'
      RegBit = 1
    end
    object RegCheckBox15: TRegCheckBox
      Left = 440
      Top = 178
      Width = 25
      Height = 17
      TabOrder = 52
      RegAddress = '0xE00001D2'
      RegBit = 2
    end
    object RegCheckBox16: TRegCheckBox
      Left = 376
      Top = 202
      Width = 25
      Height = 17
      TabOrder = 53
      RegAddress = '0xE00001D2'
      RegBit = 3
    end
    object RegCheckBox17: TRegCheckBox
      Left = 408
      Top = 202
      Width = 25
      Height = 17
      TabOrder = 54
      RegAddress = '0xE00001D2'
      RegBit = 4
    end
    object RegCheckBox18: TRegCheckBox
      Left = 440
      Top = 202
      Width = 25
      Height = 17
      TabOrder = 55
      RegAddress = '0xE00001D2'
      RegBit = 5
    end
  end
  object OOR_motion: TGroupBox
    Left = 544
    Top = 0
    Width = 393
    Height = 185
    Caption = 'OOR_motion'
    TabOrder = 3
    object Label173: TLabel
      Left = 8
      Top = 96
      Width = 22
      Height = 13
      Caption = 'DN: '
    end
    object Label174: TLabel
      Left = 8
      Top = 120
      Width = 19
      Height = 13
      Caption = 'LE: '
    end
    object Label175: TLabel
      Left = 8
      Top = 144
      Width = 17
      Height = 13
      Caption = 'RI: '
    end
    object Label179: TLabel
      Left = 40
      Top = 48
      Width = 77
      Height = 13
      Caption = '-- OOR Motion --'
    end
    object Label180: TLabel
      Left = 64
      Top = 96
      Width = 140
      Height = 13
      Caption = 'reg_04FB[1:0], reg_04FA[7:0]'
    end
    object Label171: TLabel
      Left = 8
      Top = 72
      Width = 21
      Height = 13
      Caption = 'UP: '
    end
    object Label1: TLabel
      Left = 64
      Top = 120
      Width = 138
      Height = 13
      Caption = 'reg_04F7[1:0], reg_04F6[7:0]'
    end
    object Label2: TLabel
      Left = 64
      Top = 144
      Width = 138
      Height = 13
      Caption = 'reg_04F9[1:0], reg_04F8[7:0]'
    end
    object Label3: TLabel
      Left = 64
      Top = 72
      Width = 138
      Height = 13
      Caption = 'reg_04F5[1:0], reg_04F4[7:0]'
    end
    object Show_OOR_info: TRegCheckBox
      Left = 8
      Top = 24
      Width = 145
      Height = 17
      Caption = 'Show_OOR_info'
      TabOrder = 0
    end
    object RegEdit1: TRegEdit
      Left = 208
      Top = 65
      Width = 161
      Height = 21
      Color = clInfoBk
      TabOrder = 1
      Text = '0'
      RegStartAddress = '0xE00004F4'
      RegBits = 10
      TextType = ttInt
    end
    object RegEdit2: TRegEdit
      Left = 208
      Top = 89
      Width = 161
      Height = 21
      Color = clInfoBk
      TabOrder = 2
      Text = '0'
      RegStartAddress = '0xE00004FA'
      RegBits = 10
      TextType = ttInt
    end
    object RegEdit3: TRegEdit
      Left = 208
      Top = 113
      Width = 161
      Height = 21
      Color = clInfoBk
      TabOrder = 3
      Text = '0'
      RegStartAddress = '0xE00004F6'
      RegBits = 10
      TextType = ttInt
    end
    object RegEdit4: TRegEdit
      Left = 208
      Top = 137
      Width = 161
      Height = 21
      Color = clInfoBk
      TabOrder = 4
      Text = '0'
      RegStartAddress = '0xE00004F8'
      RegBits = 10
      TextType = ttInt
    end
    object Button6: TButton
      Left = 144
      Top = 16
      Width = 97
      Height = 25
      Caption = 'Show OOR info'
      TabOrder = 5
      OnClick = Button6Click
    end
  end
  object dyn_dc_GroupBox: TGroupBox
    Left = 8
    Top = 480
    Width = 529
    Height = 217
    Caption = 'dyn_dc'
    TabOrder = 2
    object Label113: TLabel
      Left = 16
      Top = 80
      Width = 21
      Height = 13
      Caption = 'UP: '
    end
    object Label158: TLabel
      Left = 16
      Top = 104
      Width = 22
      Height = 13
      Caption = 'DN: '
    end
    object Label159: TLabel
      Left = 16
      Top = 130
      Width = 19
      Height = 13
      Caption = 'LE: '
    end
    object Label160: TLabel
      Left = 18
      Top = 157
      Width = 17
      Height = 13
      Caption = 'RI: '
    end
    object Label161: TLabel
      Left = 96
      Top = 40
      Width = 20
      Height = 13
      Caption = 'APL'
    end
    object Label258: TLabel
      Left = 200
      Top = 40
      Width = 20
      Height = 13
      Caption = 'MIN'
    end
    object Label277: TLabel
      Left = 296
      Top = 40
      Width = 23
      Height = 13
      Caption = 'MAX'
    end
    object Label278: TLabel
      Left = 395
      Top = 37
      Width = 26
      Height = 13
      Caption = 'Zposi'
    end
    object Show_rb_APL: TRegCheckBox
      Left = 56
      Top = 8
      Width = 121
      Height = 17
      Caption = 'Show_rb_APL'
      TabOrder = 0
    end
    object Button4: TButton
      Left = 168
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Show rb APL'
      TabOrder = 1
      OnClick = Button4Click
    end
    object RegEdit5: TRegEdit
      Left = 63
      Top = 76
      Width = 90
      Height = 21
      Color = clInfoBk
      TabOrder = 2
      OnChange = Edit11Change
      RegStartAddress = '0xE0000D31'
      RegBits = 8
      TextType = ttInt
    end
    object RegEdit6: TRegEdit
      Left = 367
      Top = 152
      Width = 90
      Height = 21
      Color = clSkyBlue
      TabOrder = 3
      RegStartAddress = '0xE0000DE'
      RegBits = 8
      TextType = ttInt
    end
    object RegEdit7: TRegEdit
      Left = 265
      Top = 152
      Width = 90
      Height = 21
      Color = clInfoBk
      TabOrder = 4
      RegStartAddress = '0xE0000D3A'
      RegBits = 8
      TextType = ttInt
    end
    object RegEdit8: TRegEdit
      Left = 164
      Top = 152
      Width = 90
      Height = 21
      Color = clSkyBlue
      TabOrder = 5
      RegStartAddress = '0xE0000D36'
      RegBits = 8
      TextType = ttInt
    end
    object RegEdit9: TRegEdit
      Left = 63
      Top = 152
      Width = 90
      Height = 21
      Color = clInfoBk
      TabOrder = 6
      RegStartAddress = '0xE0000D32'
      RegBits = 8
      TextType = ttInt
    end
    object RegEdit10: TRegEdit
      Left = 367
      Top = 126
      Width = 90
      Height = 21
      Color = clSkyBlue
      TabOrder = 7
      RegStartAddress = '0xE0000D3C'
      RegBits = 8
      TextType = ttInt
    end
    object RegEdit11: TRegEdit
      Left = 265
      Top = 126
      Width = 90
      Height = 21
      Color = clInfoBk
      TabOrder = 8
      RegStartAddress = '0xE0000D38'
      RegBits = 8
      TextType = ttInt
    end
    object RegEdit12: TRegEdit
      Left = 164
      Top = 126
      Width = 90
      Height = 21
      Color = clSkyBlue
      TabOrder = 9
      RegStartAddress = '0xE0000D34'
      RegBits = 8
      TextType = ttInt
    end
    object RegEdit13: TRegEdit
      Left = 63
      Top = 126
      Width = 90
      Height = 21
      Color = clInfoBk
      TabOrder = 10
      RegStartAddress = '0xE0000D30'
      RegBits = 8
      TextType = ttInt
    end
    object RegEdit14: TRegEdit
      Left = 367
      Top = 101
      Width = 90
      Height = 21
      Color = clSkyBlue
      TabOrder = 11
      RegStartAddress = '0xE0000D3F'
      RegBits = 8
      TextType = ttInt
    end
    object RegEdit15: TRegEdit
      Left = 265
      Top = 101
      Width = 90
      Height = 21
      Color = clInfoBk
      TabOrder = 12
      RegStartAddress = '0xE0000D3B'
      RegBits = 8
      TextType = ttInt
    end
    object RegEdit16: TRegEdit
      Left = 164
      Top = 101
      Width = 90
      Height = 21
      Color = clSkyBlue
      TabOrder = 13
      RegStartAddress = '0xE0000D37'
      RegBits = 8
      TextType = ttInt
    end
    object RegEdit17: TRegEdit
      Left = 63
      Top = 101
      Width = 90
      Height = 21
      Color = clInfoBk
      TabOrder = 14
      RegStartAddress = '0xE0000D33'
      RegBits = 8
      TextType = ttInt
    end
    object RegEdit18: TRegEdit
      Left = 367
      Top = 76
      Width = 90
      Height = 21
      Color = clSkyBlue
      TabOrder = 15
      RegStartAddress = '0xE0000D3D'
      RegBits = 8
      TextType = ttInt
    end
    object RegEdit19: TRegEdit
      Left = 265
      Top = 76
      Width = 90
      Height = 21
      Color = clInfoBk
      TabOrder = 16
      RegStartAddress = '0xE0000D39'
      RegBits = 8
      TextType = ttInt
    end
    object RegEdit20: TRegEdit
      Left = 164
      Top = 76
      Width = 90
      Height = 21
      Color = clSkyBlue
      TabOrder = 17
      RegStartAddress = '0xE0000D35'
      RegBits = 8
      TextType = ttInt
    end
  end
  object GroupBox21: TGroupBox
    Left = 536
    Top = 480
    Width = 385
    Height = 217
    Caption = 'rim_transition'
    TabOrder = 5
    object Label4: TLabel
      Left = 16
      Top = 80
      Width = 35
      Height = 13
      AutoSize = False
      Caption = 'Top'
    end
    object Label5: TLabel
      Left = 16
      Top = 104
      Width = 35
      Height = 13
      AutoSize = False
      Caption = 'Bottom'
    end
    object Label6: TLabel
      Left = 16
      Top = 130
      Width = 35
      Height = 13
      AutoSize = False
      Caption = 'Left'
    end
    object Label7: TLabel
      Left = 16
      Top = 157
      Width = 35
      Height = 13
      AutoSize = False
      Caption = 'Right'
    end
    object Label8: TLabel
      Left = 80
      Top = 56
      Width = 20
      Height = 13
      Caption = 'APL'
    end
    object Label9: TLabel
      Left = 157
      Top = 56
      Width = 20
      Height = 13
      Caption = 'MIN'
    end
    object Label10: TLabel
      Left = 234
      Top = 56
      Width = 23
      Height = 13
      Caption = 'MAX'
    end
    object Label11: TLabel
      Left = 311
      Top = 56
      Width = 26
      Height = 13
      Caption = 'Zposi'
    end
    object Show_rim_transition: TRegCheckBox
      Left = 24
      Top = 32
      Width = 161
      Height = 17
      Caption = 'Show_rim_transition'
      TabOrder = 0
    end
    object Button2: TButton
      Left = 168
      Top = 24
      Width = 105
      Height = 25
      Caption = 'Show_rim_transition'
      TabOrder = 1
      OnClick = Button2Click
    end
    object RegEdit21: TRegEdit
      Left = 55
      Top = 76
      Width = 72
      Height = 21
      Color = clInfoBk
      TabOrder = 2
      OnChange = Edit11Change
      RegStartAddress = '0xE0000D08'
      RegBits = 16
      TextType = ttInt
    end
    object RegEdit22: TRegEdit
      Left = 287
      Top = 152
      Width = 72
      Height = 21
      Color = clSkyBlue
      TabOrder = 3
      RegStartAddress = '0xE0000D26'
      RegBits = 16
      TextType = ttInt
    end
    object RegEdit23: TRegEdit
      Left = 209
      Top = 152
      Width = 72
      Height = 21
      Color = clInfoBk
      TabOrder = 4
      RegStartAddress = '0xE0000D24'
      RegBits = 16
      TextType = ttInt
    end
    object RegEdit24: TRegEdit
      Left = 132
      Top = 152
      Width = 72
      Height = 21
      Color = clSkyBlue
      TabOrder = 5
      RegStartAddress = '0xE0000D22'
      RegBits = 16
      TextType = ttInt
    end
    object RegEdit25: TRegEdit
      Left = 55
      Top = 152
      Width = 72
      Height = 21
      Color = clInfoBk
      TabOrder = 6
      RegStartAddress = '0xE0000D20'
      RegBits = 16
      TextType = ttInt
    end
    object RegEdit26: TRegEdit
      Left = 287
      Top = 126
      Width = 72
      Height = 21
      Color = clSkyBlue
      TabOrder = 7
      RegStartAddress = '0xE0000D1E'
      RegBits = 16
      TextType = ttInt
    end
    object RegEdit27: TRegEdit
      Left = 209
      Top = 126
      Width = 72
      Height = 21
      Color = clInfoBk
      TabOrder = 8
      RegStartAddress = '0xE0000D1C'
      RegBits = 16
      TextType = ttInt
    end
    object RegEdit28: TRegEdit
      Left = 132
      Top = 126
      Width = 72
      Height = 21
      Color = clSkyBlue
      TabOrder = 9
      RegStartAddress = '0xE0000D1A'
      RegBits = 16
      TextType = ttInt
    end
    object RegEdit29: TRegEdit
      Left = 55
      Top = 126
      Width = 72
      Height = 21
      Color = clInfoBk
      TabOrder = 10
      RegStartAddress = '0xE0000D18'
      RegBits = 16
      TextType = ttInt
    end
    object RegEdit30: TRegEdit
      Left = 287
      Top = 101
      Width = 72
      Height = 21
      Color = clSkyBlue
      TabOrder = 11
      RegStartAddress = '0xE0000D16'
      RegBits = 16
      TextType = ttInt
    end
    object RegEdit31: TRegEdit
      Left = 209
      Top = 101
      Width = 72
      Height = 21
      Color = clInfoBk
      TabOrder = 12
      RegStartAddress = '0xE0000D14'
      RegBits = 16
      TextType = ttInt
    end
    object RegEdit32: TRegEdit
      Left = 132
      Top = 101
      Width = 72
      Height = 21
      Color = clSkyBlue
      TabOrder = 13
      RegStartAddress = '0xE0000D12'
      RegBits = 16
      TextType = ttInt
    end
    object RegEdit33: TRegEdit
      Left = 55
      Top = 101
      Width = 72
      Height = 21
      Color = clInfoBk
      TabOrder = 14
      RegStartAddress = '0xE0000D10'
      RegBits = 16
      TextType = ttInt
    end
    object RegEdit34: TRegEdit
      Left = 287
      Top = 76
      Width = 72
      Height = 21
      Color = clSkyBlue
      TabOrder = 15
      RegStartAddress = '0xE0000D0D'
      RegBits = 16
      TextType = ttInt
    end
    object RegEdit35: TRegEdit
      Left = 209
      Top = 76
      Width = 72
      Height = 21
      Color = clInfoBk
      TabOrder = 16
      RegStartAddress = '0xE0000D0C'
      RegBits = 16
      TextType = ttInt
    end
    object RegEdit36: TRegEdit
      Left = 132
      Top = 76
      Width = 72
      Height = 21
      Color = clSkyBlue
      TabOrder = 17
      RegStartAddress = '0xE0000D0A'
      RegBits = 16
      TextType = ttInt
    end
  end
  object Button5: TButton
    Left = 880
    Top = 320
    Width = 75
    Height = 25
    Caption = ' Refresh All'
    TabOrder = 6
    OnClick = Button5Click
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 0
    Width = 529
    Height = 236
    Caption = 'GroupBox1'
    TabOrder = 0
    object Rim_Le_Cap: TLabel
      Left = 8
      Top = 117
      Width = 24
      Height = 13
      Caption = 'Left: '
    end
    object lb_trackLeft: TLabel
      Left = 48
      Top = 117
      Width = 33
      Height = 13
      AutoSize = False
      Caption = '0'
    end
    object Rim_Dn_Cap: TLabel
      Left = 296
      Top = 203
      Width = 34
      Height = 13
      Caption = 'Down: '
    end
    object lb_trackDown: TLabel
      Left = 344
      Top = 203
      Width = 33
      Height = 13
      AutoSize = False
      Caption = '1080'
    end
    object Rim_Ri_Cap: TLabel
      Left = 432
      Top = 116
      Width = 31
      Height = 13
      Caption = 'Right: '
    end
    object lb_trackRight: TLabel
      Left = 480
      Top = 116
      Width = 33
      Height = 13
      AutoSize = False
      Caption = '1920'
    end
    object lb_trackUp: TLabel
      Left = 328
      Top = 35
      Width = 33
      Height = 13
      AutoSize = False
      Caption = '0'
    end
    object Rim_Up_Cap: TLabel
      Left = 296
      Top = 35
      Width = 20
      Height = 13
      Caption = 'Up: '
    end
    object force_rim_en: TRegCheckBox
      Left = 8
      Top = 32
      Width = 121
      Height = 17
      Caption = 'force_rim_en'
      TabOrder = 0
      OnClick = force_rim_enClick
      RegAddress = '0xE00002A3'
      RegBit = 7
    end
    object Show_Rim_info: TRegCheckBox
      Left = 8
      Top = 56
      Width = 137
      Height = 17
      Caption = 'Show_Rim_info'
      TabOrder = 1
    end
    object CheckBox1: TRegCheckBox
      Left = 8
      Top = 80
      Width = 137
      Height = 17
      Caption = 'Show_Rim'
      TabOrder = 2
      OnClick = CheckBox1Click
      RegAddress = '0xE0000238'
      RegBit = 3
    end
    object Rim_Le_TrackBar: TRegScrollBar
      Left = 98
      Top = 115
      Width = 150
      Height = 17
      Max = 1920
      PageSize = 0
      ParentShowHint = False
      ShowHint = False
      TabOrder = 3
      OnChange = Rim_Le_TrackBarChange
      RegStartAddress = '0xE00002A0'
      RegBits = 11
    end
    object Rim_Ri_TrackBar: TRegScrollBar
      Left = 265
      Top = 115
      Width = 150
      Height = 17
      Max = 1920
      PageSize = 0
      Position = 1920
      TabOrder = 4
      OnChange = Rim_Ri_TrackBarChange
      RegStartAddress = '0xE00002A4'
      RegBits = 11
    end
    object Rim_Up_TrackBar: TRegScrollBar
      Left = 248
      Top = 11
      Width = 17
      Height = 104
      Kind = sbVertical
      Max = 1080
      PageSize = 0
      TabOrder = 5
      OnChange = Rim_Up_TrackBarChange
      RegStartAddress = '0xE00002A1'
      RegBits = 11
      RegStart = 5
    end
    object Rim_Dn_TrackBar: TRegScrollBar
      Left = 248
      Top = 132
      Width = 17
      Height = 97
      Kind = sbVertical
      Max = 1080
      PageSize = 0
      Position = 1080
      TabOrder = 6
      OnChange = Rim_Dn_TrackBarChange
      RegStartAddress = '0xE00002A5'
      RegBits = 11
      RegStart = 5
    end
    object Button7: TButton
      Left = 424
      Top = 192
      Width = 97
      Height = 25
      Caption = 'Show rim info'
      TabOrder = 7
      OnClick = Button7Click
    end
  end
end
