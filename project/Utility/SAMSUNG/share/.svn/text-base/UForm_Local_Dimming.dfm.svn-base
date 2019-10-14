inherited Form_Local_Dimming: TForm_Local_Dimming
  Left = 128
  Top = -3
  Width = 1113
  Height = 634
  Caption = 'Local Dimming'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 88
    Top = 0
    Width = 1009
    Height = 57
    TabOrder = 0
    object RegCheckBox1: TRegCheckBox
      Left = 40
      Top = 24
      Width = 169
      Height = 17
      Caption = 'Local Dimming Enable'
      TabOrder = 0
      RegAddress = '0xE0080200'
    end
    object RegCheckBox2: TRegCheckBox
      Left = 272
      Top = 24
      Width = 169
      Height = 17
      Caption = 'Global Dimming Enable'
      TabOrder = 1
      RegAddress = '0xE00802E1'
      RegBit = 5
    end
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 56
    Width = 289
    Height = 145
    TabOrder = 1
    object Label1: TLabel
      Left = 40
      Top = 64
      Width = 137
      Height = 13
      AutoSize = False
      Caption = 'ADPS ratio'
    end
    object RegCheckBox3: TRegCheckBox
      Left = 40
      Top = 32
      Width = 169
      Height = 17
      Caption = 'Advanced DSP Mode Enable'
      TabOrder = 0
      RegAddress = '0xE00802E1'
      RegBit = 4
    end
    object RegScrollBar1: TRegScrollBar
      Left = 40
      Top = 88
      Width = 137
      Height = 17
      PageSize = 0
      TabOrder = 1
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE00802E2'
      RegBits = 8
    end
    object RegEdit1: TRegEdit
      Left = 192
      Top = 88
      Width = 41
      Height = 21
      TabOrder = 2
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE00802E2'
      RegBits = 8
      TextType = ttInt
    end
  end
  object GroupBox3: TGroupBox
    Left = 8
    Top = 208
    Width = 289
    Height = 265
    TabOrder = 2
    object Label2: TLabel
      Left = 40
      Top = 48
      Width = 137
      Height = 13
      AutoSize = False
      Caption = 'Local Scene Th'
    end
    object Label3: TLabel
      Left = 40
      Top = 96
      Width = 137
      Height = 13
      AutoSize = False
      Caption = 'Global Scene Th'
    end
    object RegCheckBox4: TRegCheckBox
      Left = 40
      Top = 16
      Width = 169
      Height = 17
      Caption = 'AOS Mode Enable'
      TabOrder = 0
      RegAddress = '0xE00802E1'
      RegBit = 6
    end
    object RegScrollBar2: TRegScrollBar
      Left = 40
      Top = 72
      Width = 137
      Height = 17
      PageSize = 0
      TabOrder = 1
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE00802E7'
      RegBits = 8
    end
    object RegEdit2: TRegEdit
      Left = 192
      Top = 72
      Width = 41
      Height = 21
      TabOrder = 2
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE00802E7'
      RegBits = 8
      TextType = ttInt
    end
    object RegScrollBar3: TRegScrollBar
      Left = 40
      Top = 120
      Width = 137
      Height = 17
      PageSize = 0
      TabOrder = 3
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE00802E8'
      RegBits = 8
    end
    object RegEdit3: TRegEdit
      Left = 192
      Top = 120
      Width = 41
      Height = 21
      TabOrder = 4
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE00802E8'
      RegBits = 8
      TextType = ttInt
    end
    object sb_AOS_TH: TScrollBar
      Left = 40
      Top = 160
      Width = 137
      Height = 17
      Max = 65535
      PageSize = 0
      TabOrder = 5
      OnScroll = sb_AOS_THScroll
    end
    object sb_AOS_PX: TScrollBar
      Left = 40
      Top = 200
      Width = 137
      Height = 17
      Max = 65535
      PageSize = 0
      TabOrder = 6
      OnScroll = sb_AOS_PXScroll
    end
    object ed_AOS_TH: TEdit
      Left = 192
      Top = 160
      Width = 40
      Height = 21
      TabOrder = 7
      OnExit = ed_AOS_THExit
      OnKeyPress = ed_AOS_THKeyPress
    end
    object ed_AOS_PX: TEdit
      Left = 192
      Top = 200
      Width = 40
      Height = 21
      TabOrder = 8
      OnExit = ed_AOS_PXExit
      OnKeyPress = ed_AOS_PXKeyPress
    end
    object re_AOS_TH_H: TRegEdit
      Left = 56
      Top = 224
      Width = 41
      Height = 21
      TabOrder = 9
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE00802E9'
      RegBits = 8
      TextType = ttInt
    end
    object re_AOS_TH_L: TRegEdit
      Left = 96
      Top = 224
      Width = 41
      Height = 21
      TabOrder = 10
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE00802EA'
      RegBits = 8
      TextType = ttInt
    end
    object re_AOS_PX_H: TRegEdit
      Left = 160
      Top = 224
      Width = 41
      Height = 21
      TabOrder = 11
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE00802D0'
      RegBits = 8
      TextType = ttInt
    end
    object re_AOS_PX_L: TRegEdit
      Left = 200
      Top = 224
      Width = 41
      Height = 21
      TabOrder = 12
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE00802D1'
      RegBits = 8
      TextType = ttInt
    end
  end
  object GroupBox4: TGroupBox
    Left = 304
    Top = 56
    Width = 265
    Height = 225
    TabOrder = 3
    object Label4: TLabel
      Left = 40
      Top = 64
      Width = 137
      Height = 13
      AutoSize = False
      Caption = 'DUNAMIC DIFF TH'
    end
    object Label5: TLabel
      Left = 40
      Top = 112
      Width = 137
      Height = 13
      AutoSize = False
      Caption = 'REG MODE SWITCH TH'
    end
    object Label6: TLabel
      Left = 40
      Top = 160
      Width = 137
      Height = 13
      AutoSize = False
      Caption = 'DEBUG MODE'
    end
    object RegCheckBox5: TRegCheckBox
      Left = 40
      Top = 32
      Width = 169
      Height = 17
      Caption = 'Dynamic Mode'
      TabOrder = 0
      RegAddress = '0xE00802E1'
      RegBit = 7
    end
    object RegScrollBar4: TRegScrollBar
      Left = 40
      Top = 88
      Width = 137
      Height = 17
      PageSize = 0
      TabOrder = 1
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE00802EB'
      RegBits = 8
    end
    object RegEdit4: TRegEdit
      Left = 192
      Top = 88
      Width = 41
      Height = 21
      TabOrder = 2
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE00802EB'
      RegBits = 8
      TextType = ttInt
    end
    object RegScrollBar5: TRegScrollBar
      Left = 40
      Top = 136
      Width = 137
      Height = 17
      PageSize = 0
      TabOrder = 3
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE00802E4'
      RegBits = 4
    end
    object RegEdit5: TRegEdit
      Left = 192
      Top = 136
      Width = 41
      Height = 21
      TabOrder = 4
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE00802E4'
      RegBits = 4
      TextType = ttInt
    end
    object RegScrollBar6: TRegScrollBar
      Left = 40
      Top = 184
      Width = 137
      Height = 17
      PageSize = 0
      TabOrder = 5
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE00802E4'
      RegBits = 4
      RegStart = 4
    end
    object RegEdit6: TRegEdit
      Left = 192
      Top = 184
      Width = 41
      Height = 21
      TabOrder = 6
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE00802E4'
      RegBits = 4
      RegStart = 4
      TextType = ttInt
    end
  end
  object GroupBox5: TGroupBox
    Left = 304
    Top = 280
    Width = 265
    Height = 185
    TabOrder = 4
    object Label7: TLabel
      Left = 40
      Top = 64
      Width = 137
      Height = 13
      AutoSize = False
      Caption = 'DOMINATE PAT TH'
    end
    object Label8: TLabel
      Left = 40
      Top = 112
      Width = 137
      Height = 13
      AutoSize = False
      Caption = 'DOMINATE DIFF TH'
    end
    object RegCheckBox6: TRegCheckBox
      Left = 40
      Top = 32
      Width = 169
      Height = 17
      Caption = 'Dominate Mode'
      TabOrder = 0
      RegAddress = '0xE00802EF'
      RegBit = 4
    end
    object RegScrollBar7: TRegScrollBar
      Left = 40
      Top = 88
      Width = 137
      Height = 17
      PageSize = 0
      TabOrder = 1
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE00802ED'
      RegBits = 8
    end
    object RegEdit7: TRegEdit
      Left = 192
      Top = 88
      Width = 41
      Height = 21
      TabOrder = 2
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE00802ED'
      RegBits = 8
      TextType = ttInt
    end
    object RegScrollBar8: TRegScrollBar
      Left = 40
      Top = 136
      Width = 137
      Height = 17
      PageSize = 0
      TabOrder = 3
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE00802F0'
      RegBits = 8
    end
    object RegEdit8: TRegEdit
      Left = 192
      Top = 136
      Width = 41
      Height = 21
      TabOrder = 4
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE00802F0'
      RegBits = 8
      TextType = ttInt
    end
  end
  object GroupBox6: TGroupBox
    Left = 576
    Top = 56
    Width = 265
    Height = 281
    TabOrder = 5
    object Label9: TLabel
      Left = 40
      Top = 64
      Width = 137
      Height = 13
      AutoSize = False
      Caption = 'Duty Statistic Period'
    end
    object Label10: TLabel
      Left = 40
      Top = 112
      Width = 137
      Height = 13
      AutoSize = False
      Caption = 'DUTY STAT REC'
    end
    object Label11: TLabel
      Left = 40
      Top = 160
      Width = 137
      Height = 13
      AutoSize = False
      Caption = 'DUTY SPEED R'
    end
    object Label12: TLabel
      Left = 40
      Top = 208
      Width = 137
      Height = 13
      AutoSize = False
      Caption = 'DUTY SPEED F'
    end
    object RegCheckBox7: TRegCheckBox
      Left = 40
      Top = 32
      Width = 169
      Height = 17
      Caption = 'Duty Statistic Enable'
      TabOrder = 0
      RegAddress = '0xE00802D2'
      RegBit = 7
    end
    object RegScrollBar9: TRegScrollBar
      Left = 40
      Top = 88
      Width = 137
      Height = 17
      PageSize = 0
      TabOrder = 1
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE00802D2'
      RegBits = 3
    end
    object RegEdit9: TRegEdit
      Left = 192
      Top = 88
      Width = 41
      Height = 21
      TabOrder = 2
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE00802D2'
      RegBits = 3
      TextType = ttInt
    end
    object RegScrollBar10: TRegScrollBar
      Left = 40
      Top = 136
      Width = 137
      Height = 17
      PageSize = 0
      TabOrder = 3
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE00802D3'
      RegBits = 8
    end
    object RegEdit10: TRegEdit
      Left = 192
      Top = 136
      Width = 41
      Height = 21
      TabOrder = 4
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE00802D3'
      RegBits = 8
      TextType = ttInt
    end
    object RegScrollBar11: TRegScrollBar
      Left = 40
      Top = 184
      Width = 137
      Height = 17
      PageSize = 0
      TabOrder = 5
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE00802E3'
      RegBits = 3
      RegStart = 4
    end
    object RegEdit11: TRegEdit
      Left = 192
      Top = 184
      Width = 41
      Height = 21
      TabOrder = 6
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE00802E3'
      RegBits = 3
      RegStart = 4
      TextType = ttInt
    end
    object RegScrollBar12: TRegScrollBar
      Left = 40
      Top = 232
      Width = 137
      Height = 17
      PageSize = 0
      TabOrder = 7
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE00802E3'
      RegBits = 3
    end
    object RegEdit12: TRegEdit
      Left = 192
      Top = 232
      Width = 41
      Height = 21
      TabOrder = 8
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE00802E3'
      RegBits = 3
      TextType = ttInt
    end
  end
  object GroupBox7: TGroupBox
    Left = 576
    Top = 336
    Width = 265
    Height = 177
    TabOrder = 6
    object Label13: TLabel
      Left = 40
      Top = 64
      Width = 137
      Height = 13
      AutoSize = False
      Caption = 'MINIMUM DUTY'
    end
    object Label14: TLabel
      Left = 40
      Top = 112
      Width = 137
      Height = 13
      AutoSize = False
      Caption = 'BRIGHTNESS'
    end
    object Label15: TLabel
      Left = 40
      Top = 16
      Width = 137
      Height = 13
      AutoSize = False
      Caption = 'DUTY DEBOUNCE TH'
    end
    object RegScrollBar13: TRegScrollBar
      Left = 40
      Top = 88
      Width = 137
      Height = 17
      PageSize = 0
      TabOrder = 0
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE00802E6'
      RegBits = 8
    end
    object RegEdit13: TRegEdit
      Left = 192
      Top = 88
      Width = 41
      Height = 21
      TabOrder = 1
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE00802E6'
      RegBits = 8
      TextType = ttInt
    end
    object RegScrollBar14: TRegScrollBar
      Left = 40
      Top = 136
      Width = 137
      Height = 17
      PageSize = 0
      TabOrder = 2
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE00802EC'
      RegBits = 8
    end
    object RegEdit14: TRegEdit
      Left = 192
      Top = 136
      Width = 41
      Height = 21
      TabOrder = 3
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE00802EC'
      RegBits = 8
      TextType = ttInt
    end
    object RegScrollBar15: TRegScrollBar
      Left = 40
      Top = 40
      Width = 137
      Height = 17
      PageSize = 0
      TabOrder = 4
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE00802E5'
      RegBits = 8
    end
    object RegEdit15: TRegEdit
      Left = 192
      Top = 40
      Width = 41
      Height = 21
      TabOrder = 5
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE00802E5'
      RegBits = 8
      TextType = ttInt
    end
  end
  object GroupBox8: TGroupBox
    Left = 8
    Top = 480
    Width = 289
    Height = 113
    TabOrder = 7
    object RegCheckBox8: TRegCheckBox
      Left = 40
      Top = 24
      Width = 169
      Height = 17
      Caption = 'DATA SOLD MODE'
      TabOrder = 0
      RegAddress = '0xE00802E1'
    end
    object RegCheckBox9: TRegCheckBox
      Left = 40
      Top = 40
      Width = 169
      Height = 17
      Caption = 'BL SOLD MODE'
      TabOrder = 1
      RegAddress = '0xE00802E1'
      RegBit = 1
    end
    object RegCheckBox10: TRegCheckBox
      Left = 40
      Top = 56
      Width = 169
      Height = 17
      Caption = 'DEMO SOLD MODE'
      TabOrder = 2
      RegAddress = '0xE00802E1'
      RegBit = 2
    end
    object RegCheckBox11: TRegCheckBox
      Left = 40
      Top = 72
      Width = 169
      Height = 17
      Caption = 'PROFILE SOLD MODE'
      TabOrder = 3
      RegAddress = '0xE00802E1'
      RegBit = 3
    end
    object RegCheckBox12: TRegCheckBox
      Left = 40
      Top = 88
      Width = 169
      Height = 17
      Caption = 'AOS TRACKING'
      TabOrder = 4
      RegAddress = '0xE00802EF'
    end
  end
  object GB_DUTY_BLU: TGroupBox
    Left = 840
    Top = 56
    Width = 257
    Height = 273
    Caption = 'DUTY BLU'
    TabOrder = 8
    object RegLabeledEdit1: TRegLabeledEdit
      Left = 96
      Top = 40
      Width = 121
      Height = 21
      EditLabel.Width = 66
      EditLabel.Height = 13
      EditLabel.Caption = 'DUTY BLU0: '
      LabelPosition = lpLeft
      LabelSpacing = 3
      ReadOnly = True
      TabOrder = 0
      RegStartAddress = '0xE0080240'
      RegBits = 10
    end
    object RegLabeledEdit2: TRegLabeledEdit
      Left = 96
      Top = 64
      Width = 121
      Height = 21
      EditLabel.Width = 66
      EditLabel.Height = 13
      EditLabel.Caption = 'DUTY BLU1: '
      LabelPosition = lpLeft
      LabelSpacing = 3
      ReadOnly = True
      TabOrder = 1
      RegStartAddress = '0xE0080240'
      RegBits = 10
      RegStart = 16
    end
    object RegLabeledEdit3: TRegLabeledEdit
      Left = 96
      Top = 88
      Width = 121
      Height = 21
      EditLabel.Width = 66
      EditLabel.Height = 13
      EditLabel.Caption = 'DUTY BLU2: '
      LabelPosition = lpLeft
      LabelSpacing = 3
      ReadOnly = True
      TabOrder = 2
      RegStartAddress = '0xE0080244'
      RegBits = 10
    end
    object RegLabeledEdit4: TRegLabeledEdit
      Left = 96
      Top = 112
      Width = 121
      Height = 21
      EditLabel.Width = 66
      EditLabel.Height = 13
      EditLabel.Caption = 'DUTY BLU3: '
      LabelPosition = lpLeft
      LabelSpacing = 3
      ReadOnly = True
      TabOrder = 3
      RegStartAddress = '0xE0080244'
      RegBits = 10
      RegStart = 16
    end
    object RegLabeledEdit5: TRegLabeledEdit
      Left = 96
      Top = 136
      Width = 121
      Height = 21
      EditLabel.Width = 66
      EditLabel.Height = 13
      EditLabel.Caption = 'DUTY BLU4: '
      LabelPosition = lpLeft
      LabelSpacing = 3
      ReadOnly = True
      TabOrder = 4
      RegStartAddress = '0xE0080248'
      RegBits = 10
    end
    object RegLabeledEdit6: TRegLabeledEdit
      Left = 96
      Top = 160
      Width = 121
      Height = 21
      EditLabel.Width = 66
      EditLabel.Height = 13
      EditLabel.Caption = 'DUTY BLU5: '
      LabelPosition = lpLeft
      LabelSpacing = 3
      ReadOnly = True
      TabOrder = 5
      RegStartAddress = '0xE0080248'
      RegBits = 10
      RegStart = 16
    end
    object RegLabeledEdit7: TRegLabeledEdit
      Left = 96
      Top = 184
      Width = 121
      Height = 21
      EditLabel.Width = 66
      EditLabel.Height = 13
      EditLabel.Caption = 'DUTY BLU6: '
      LabelPosition = lpLeft
      LabelSpacing = 3
      ReadOnly = True
      TabOrder = 6
      RegStartAddress = '0xE008024C'
      RegBits = 10
    end
    object RegLabeledEdit8: TRegLabeledEdit
      Left = 96
      Top = 208
      Width = 121
      Height = 21
      EditLabel.Width = 66
      EditLabel.Height = 13
      EditLabel.Caption = 'DUTY BLU7: '
      LabelPosition = lpLeft
      LabelSpacing = 3
      ReadOnly = True
      TabOrder = 7
      RegStartAddress = '0xE008024C'
      RegBits = 10
      RegStart = 16
    end
    object Button2: TButton
      Left = 96
      Top = 240
      Width = 97
      Height = 25
      Caption = 'Refresh DUTY '
      TabOrder = 8
      OnClick = Button2Click
    end
  end
  object Button1: TButton
    Left = 8
    Top = 24
    Width = 75
    Height = 25
    Caption = 'Rfresh All'
    TabOrder = 9
    OnClick = Button1Click
  end
end
