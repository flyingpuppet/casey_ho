inherited Form_Demo_Chip: TForm_Demo_Chip
  Left = 185
  Top = -7
  Width = 964
  Height = 660
  Caption = 'Form_Demo_Chip'
  OldCreateOrder = True
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label2: TLabel
    Left = 96
    Top = 16
    Width = 49
    Height = 13
    AutoSize = False
    Caption = 'H Start :'
  end
  object Label10: TLabel
    Left = 104
    Top = 24
    Width = 49
    Height = 13
    AutoSize = False
    Caption = 'H Start :'
  end
  object GB_Demo0: TGroupBox
    Left = 0
    Top = 0
    Width = 953
    Height = 73
    Caption = 'Demo Window 0'
    TabOrder = 0
    object Label1: TLabel
      Left = 96
      Top = 17
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'H Start :'
    end
    object Label3: TLabel
      Left = 96
      Top = 40
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'H End :'
    end
    object Label4: TLabel
      Left = 336
      Top = 17
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'V Start :'
    end
    object Label5: TLabel
      Left = 336
      Top = 40
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'V End :'
    end
    object RegCheckBox1: TRegCheckBox
      Left = 12
      Top = 28
      Width = 61
      Height = 17
      Caption = 'Enable'
      TabOrder = 0
      RegAddress = '0xE000025C'
    end
    object RegScrollBar1: TRegScrollBar
      Left = 152
      Top = 16
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 1
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE000025D'
      RegBits = 11
    end
    object RegScrollBar2: TRegScrollBar
      Left = 152
      Top = 40
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 2
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE0000260'
      RegBits = 11
    end
    object RegScrollBar3: TRegScrollBar
      Left = 392
      Top = 16
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 3
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE000025E'
      RegBits = 11
      RegStart = 5
    end
    object RegScrollBar4: TRegScrollBar
      Left = 392
      Top = 40
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 4
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE0000261'
      RegBits = 11
      RegStart = 5
    end
    object RegEdit1: TRegEdit
      Left = 280
      Top = 14
      Width = 41
      Height = 21
      TabOrder = 5
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE000025D'
      RegBits = 11
      TextType = ttInt
    end
    object RegEdit2: TRegEdit
      Left = 280
      Top = 38
      Width = 41
      Height = 21
      TabOrder = 6
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE0000260'
      RegBits = 11
      TextType = ttInt
    end
    object RegEdit3: TRegEdit
      Left = 520
      Top = 14
      Width = 41
      Height = 21
      TabOrder = 7
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE000025E'
      RegBits = 11
      RegStart = 5
      TextType = ttInt
    end
    object RegEdit4: TRegEdit
      Left = 520
      Top = 38
      Width = 41
      Height = 21
      TabOrder = 8
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE0000261'
      RegBits = 11
      RegStart = 5
      TextType = ttInt
    end
    object RadioButton1: TRadioButton
      Left = 592
      Top = 16
      Width = 57
      Height = 17
      Caption = 'Demo L'
      TabOrder = 9
      OnClick = RadioButton33Click
    end
    object RadioButton2: TRadioButton
      Tag = 2
      Left = 592
      Top = 40
      Width = 65
      Height = 17
      Caption = 'Demo T'
      TabOrder = 10
      OnClick = RadioButton33Click
    end
    object RadioButton17: TRadioButton
      Tag = 1
      Left = 664
      Top = 16
      Width = 57
      Height = 17
      Caption = 'Demo R'
      TabOrder = 11
      OnClick = RadioButton33Click
    end
    object RadioButton18: TRadioButton
      Tag = 3
      Left = 664
      Top = 40
      Width = 65
      Height = 17
      Caption = 'Demo B'
      TabOrder = 12
      OnClick = RadioButton33Click
    end
    object RadioButton33: TRadioButton
      Tag = 4
      Left = 736
      Top = 16
      Width = 49
      Height = 17
      Caption = 'Other'
      Checked = True
      TabOrder = 13
      TabStop = True
      OnClick = RadioButton33Click
    end
    object btn_win0: TButton
      Left = 856
      Top = 24
      Width = 75
      Height = 25
      Caption = 'Refresh'
      TabOrder = 14
      OnClick = btn_win0Click
    end
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 72
    Width = 953
    Height = 73
    Caption = 'Demo Window 1'
    TabOrder = 1
    object Label6: TLabel
      Left = 96
      Top = 17
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'H Start :'
    end
    object Label7: TLabel
      Left = 96
      Top = 40
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'H End :'
    end
    object Label8: TLabel
      Left = 336
      Top = 17
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'V Start :'
    end
    object Label9: TLabel
      Left = 336
      Top = 40
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'V End :'
    end
    object RegScrollBar5: TRegScrollBar
      Left = 152
      Top = 16
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 0
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE0000264'
      RegBits = 11
    end
    object RegScrollBar6: TRegScrollBar
      Left = 152
      Top = 40
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 1
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE0000268'
      RegBits = 11
    end
    object RegScrollBar7: TRegScrollBar
      Left = 392
      Top = 16
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 2
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE0000265'
      RegBits = 11
      RegStart = 5
    end
    object RegScrollBar8: TRegScrollBar
      Left = 392
      Top = 40
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 3
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE0000269'
      RegBits = 11
      RegStart = 5
    end
    object RegEdit5: TRegEdit
      Left = 280
      Top = 14
      Width = 41
      Height = 21
      TabOrder = 4
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE0000264'
      RegBits = 11
      TextType = ttInt
    end
    object RegEdit6: TRegEdit
      Left = 280
      Top = 38
      Width = 41
      Height = 21
      TabOrder = 5
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE0000268'
      RegBits = 11
      TextType = ttInt
    end
    object RegEdit7: TRegEdit
      Left = 520
      Top = 14
      Width = 41
      Height = 21
      TabOrder = 6
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE0000265'
      RegBits = 11
      RegStart = 5
      TextType = ttInt
    end
    object RegEdit8: TRegEdit
      Left = 520
      Top = 38
      Width = 41
      Height = 21
      TabOrder = 7
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE0000269'
      RegBits = 11
      RegStart = 5
      TextType = ttInt
    end
    object RegCheckBox2: TRegCheckBox
      Left = 11
      Top = 32
      Width = 62
      Height = 17
      Caption = 'Enable'
      TabOrder = 8
      RegAddress = '0xE000025C'
      RegBit = 1
    end
    object RadioButton3: TRadioButton
      Left = 592
      Top = 16
      Width = 57
      Height = 17
      Caption = 'Demo L'
      TabOrder = 9
      OnClick = RadioButton3Click
    end
    object RadioButton4: TRadioButton
      Tag = 2
      Left = 592
      Top = 40
      Width = 65
      Height = 17
      Caption = 'Demo T'
      TabOrder = 10
      OnClick = RadioButton3Click
    end
    object RadioButton5: TRadioButton
      Tag = 1
      Left = 664
      Top = 16
      Width = 57
      Height = 17
      Caption = 'Demo R'
      TabOrder = 11
      OnClick = RadioButton3Click
    end
    object RadioButton6: TRadioButton
      Tag = 3
      Left = 664
      Top = 40
      Width = 65
      Height = 17
      Caption = 'Demo B'
      TabOrder = 12
      OnClick = RadioButton3Click
    end
    object RadioButton34: TRadioButton
      Tag = 4
      Left = 736
      Top = 16
      Width = 49
      Height = 17
      Caption = 'Other'
      Checked = True
      TabOrder = 13
      TabStop = True
      OnClick = RadioButton3Click
    end
    object btn_win1: TButton
      Left = 856
      Top = 24
      Width = 75
      Height = 25
      Caption = 'Refresh'
      TabOrder = 14
      OnClick = btn_win0Click
    end
  end
  object GroupBox2: TGroupBox
    Left = 0
    Top = 144
    Width = 953
    Height = 73
    Caption = 'Demo Window 2'
    TabOrder = 2
    object Label11: TLabel
      Left = 96
      Top = 17
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'H Start :'
    end
    object Label12: TLabel
      Left = 96
      Top = 40
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'H End :'
    end
    object Label13: TLabel
      Left = 336
      Top = 17
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'V Start :'
    end
    object Label14: TLabel
      Left = 336
      Top = 40
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'V End :'
    end
    object RegScrollBar9: TRegScrollBar
      Left = 152
      Top = 16
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 0
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE000026C'
      RegBits = 11
    end
    object RegScrollBar10: TRegScrollBar
      Left = 152
      Top = 40
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 1
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE0000270'
      RegBits = 11
    end
    object RegScrollBar11: TRegScrollBar
      Left = 392
      Top = 16
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 2
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE000026D'
      RegBits = 11
      RegStart = 5
    end
    object RegScrollBar12: TRegScrollBar
      Left = 392
      Top = 40
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 3
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE0000271'
      RegBits = 11
      RegStart = 5
    end
    object RegEdit9: TRegEdit
      Left = 280
      Top = 14
      Width = 41
      Height = 21
      TabOrder = 4
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE000026C'
      RegBits = 11
      TextType = ttInt
    end
    object RegEdit10: TRegEdit
      Left = 280
      Top = 38
      Width = 41
      Height = 21
      TabOrder = 5
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE0000270'
      RegBits = 11
      TextType = ttInt
    end
    object RegEdit11: TRegEdit
      Left = 520
      Top = 14
      Width = 41
      Height = 21
      TabOrder = 6
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE000026D'
      RegBits = 11
      RegStart = 5
      TextType = ttInt
    end
    object RegEdit12: TRegEdit
      Left = 520
      Top = 38
      Width = 41
      Height = 21
      TabOrder = 7
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE0000271'
      RegBits = 11
      RegStart = 5
      TextType = ttInt
    end
    object RegCheckBox3: TRegCheckBox
      Left = 11
      Top = 32
      Width = 62
      Height = 17
      Caption = 'Enable'
      TabOrder = 8
      RegAddress = '0xE000025C'
      RegBit = 2
    end
    object RadioButton7: TRadioButton
      Left = 592
      Top = 16
      Width = 57
      Height = 17
      Caption = 'Demo L'
      TabOrder = 9
      OnClick = RadioButton7Click
    end
    object RadioButton8: TRadioButton
      Tag = 2
      Left = 592
      Top = 40
      Width = 65
      Height = 17
      Caption = 'Demo T'
      TabOrder = 10
      OnClick = RadioButton7Click
    end
    object RadioButton9: TRadioButton
      Tag = 1
      Left = 664
      Top = 16
      Width = 57
      Height = 17
      Caption = 'Demo R'
      TabOrder = 11
      OnClick = RadioButton7Click
    end
    object RadioButton10: TRadioButton
      Tag = 3
      Left = 664
      Top = 40
      Width = 65
      Height = 17
      Caption = 'Demo B'
      TabOrder = 12
      OnClick = RadioButton7Click
    end
    object RadioButton35: TRadioButton
      Tag = 4
      Left = 736
      Top = 16
      Width = 49
      Height = 17
      Caption = 'Other'
      Checked = True
      TabOrder = 13
      TabStop = True
      OnClick = RadioButton7Click
    end
    object btn_win2: TButton
      Left = 856
      Top = 24
      Width = 75
      Height = 25
      Caption = 'Refresh'
      TabOrder = 14
      OnClick = btn_win0Click
    end
  end
  object GroupBox3: TGroupBox
    Left = 0
    Top = 216
    Width = 953
    Height = 73
    Caption = 'Demo Window 3'
    TabOrder = 3
    object Label15: TLabel
      Left = 96
      Top = 17
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'H Start :'
    end
    object Label16: TLabel
      Left = 96
      Top = 40
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'H End :'
    end
    object Label17: TLabel
      Left = 336
      Top = 17
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'V Start :'
    end
    object Label18: TLabel
      Left = 336
      Top = 40
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'V End :'
    end
    object RegScrollBar13: TRegScrollBar
      Left = 152
      Top = 16
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 0
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE0000274'
      RegBits = 11
    end
    object RegScrollBar14: TRegScrollBar
      Left = 152
      Top = 40
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 1
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE0000278'
      RegBits = 11
    end
    object RegScrollBar15: TRegScrollBar
      Left = 392
      Top = 16
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 2
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE0000275'
      RegBits = 11
      RegStart = 5
    end
    object RegScrollBar16: TRegScrollBar
      Left = 392
      Top = 40
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 3
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE0000279'
      RegBits = 11
      RegStart = 5
    end
    object RegEdit13: TRegEdit
      Left = 280
      Top = 14
      Width = 41
      Height = 21
      TabOrder = 4
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE0000274'
      RegBits = 11
      TextType = ttInt
    end
    object RegEdit14: TRegEdit
      Left = 280
      Top = 38
      Width = 41
      Height = 21
      TabOrder = 5
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE0000278'
      RegBits = 11
      TextType = ttInt
    end
    object RegEdit15: TRegEdit
      Left = 520
      Top = 14
      Width = 41
      Height = 21
      TabOrder = 6
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE0000275'
      RegBits = 11
      RegStart = 5
      TextType = ttInt
    end
    object RegEdit16: TRegEdit
      Left = 520
      Top = 38
      Width = 41
      Height = 21
      TabOrder = 7
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE0000279'
      RegBits = 11
      RegStart = 5
      TextType = ttInt
    end
    object RegCheckBox4: TRegCheckBox
      Left = 11
      Top = 32
      Width = 70
      Height = 17
      Caption = 'Enable'
      TabOrder = 8
      RegAddress = '0xE000025C'
      RegBit = 3
    end
    object RadioButton11: TRadioButton
      Left = 592
      Top = 16
      Width = 57
      Height = 17
      Caption = 'Demo L'
      TabOrder = 9
      OnClick = RadioButton11Click
    end
    object RadioButton12: TRadioButton
      Tag = 2
      Left = 592
      Top = 40
      Width = 65
      Height = 17
      Caption = 'Demo T'
      TabOrder = 10
      OnClick = RadioButton11Click
    end
    object RadioButton13: TRadioButton
      Tag = 1
      Left = 664
      Top = 16
      Width = 57
      Height = 17
      Caption = 'Demo R'
      TabOrder = 11
      OnClick = RadioButton11Click
    end
    object RadioButton14: TRadioButton
      Tag = 3
      Left = 664
      Top = 40
      Width = 65
      Height = 17
      Caption = 'Demo B'
      TabOrder = 12
      OnClick = RadioButton11Click
    end
    object RadioButton36: TRadioButton
      Tag = 4
      Left = 736
      Top = 16
      Width = 49
      Height = 17
      Caption = 'Other'
      Checked = True
      TabOrder = 13
      TabStop = True
      OnClick = RadioButton11Click
    end
    object btn_win3: TButton
      Left = 856
      Top = 24
      Width = 75
      Height = 25
      Caption = 'Refresh'
      TabOrder = 14
      OnClick = btn_win0Click
    end
  end
  object GroupBox4: TGroupBox
    Left = 0
    Top = 288
    Width = 953
    Height = 73
    Caption = 'Demo Window 4'
    TabOrder = 4
    object Label19: TLabel
      Left = 96
      Top = 17
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'H Start :'
    end
    object Label20: TLabel
      Left = 96
      Top = 40
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'H End :'
    end
    object Label21: TLabel
      Left = 336
      Top = 17
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'V Start :'
    end
    object Label22: TLabel
      Left = 336
      Top = 40
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'V End :'
    end
    object RegScrollBar17: TRegScrollBar
      Left = 152
      Top = 16
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 0
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE000027C'
      RegBits = 11
    end
    object RegScrollBar18: TRegScrollBar
      Left = 152
      Top = 40
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 1
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE0000280'
      RegBits = 11
    end
    object RegScrollBar19: TRegScrollBar
      Left = 392
      Top = 16
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 2
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE000027D'
      RegBits = 11
      RegStart = 5
    end
    object RegScrollBar20: TRegScrollBar
      Left = 392
      Top = 40
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 3
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE0000281'
      RegBits = 11
      RegStart = 5
    end
    object RegEdit17: TRegEdit
      Left = 280
      Top = 14
      Width = 41
      Height = 21
      TabOrder = 4
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE000027C'
      RegBits = 11
      TextType = ttInt
    end
    object RegEdit18: TRegEdit
      Left = 280
      Top = 38
      Width = 41
      Height = 21
      TabOrder = 5
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE0000280'
      RegBits = 11
      TextType = ttInt
    end
    object RegEdit19: TRegEdit
      Left = 520
      Top = 14
      Width = 41
      Height = 21
      TabOrder = 6
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE000027D'
      RegBits = 11
      RegStart = 5
      TextType = ttInt
    end
    object RegEdit20: TRegEdit
      Left = 520
      Top = 38
      Width = 41
      Height = 21
      TabOrder = 7
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE0000281'
      RegBits = 11
      RegStart = 5
      TextType = ttInt
    end
    object RegCheckBox5: TRegCheckBox
      Left = 11
      Top = 32
      Width = 62
      Height = 17
      Caption = 'Enable'
      TabOrder = 8
      RegAddress = '0xE000025C'
      RegBit = 4
    end
    object RadioButton15: TRadioButton
      Left = 592
      Top = 16
      Width = 57
      Height = 17
      Caption = 'Demo L'
      TabOrder = 9
      OnClick = RadioButton15Click
    end
    object RadioButton16: TRadioButton
      Tag = 2
      Left = 592
      Top = 40
      Width = 65
      Height = 17
      Caption = 'Demo T'
      TabOrder = 10
      OnClick = RadioButton15Click
    end
    object RadioButton19: TRadioButton
      Tag = 1
      Left = 664
      Top = 16
      Width = 57
      Height = 17
      Caption = 'Demo R'
      TabOrder = 11
      OnClick = RadioButton15Click
    end
    object RadioButton20: TRadioButton
      Tag = 3
      Left = 664
      Top = 40
      Width = 65
      Height = 17
      Caption = 'Demo B'
      TabOrder = 12
      OnClick = RadioButton15Click
    end
    object RadioButton37: TRadioButton
      Tag = 4
      Left = 736
      Top = 16
      Width = 49
      Height = 17
      Caption = 'Other'
      Checked = True
      TabOrder = 13
      TabStop = True
      OnClick = RadioButton15Click
    end
    object btn_win4: TButton
      Left = 856
      Top = 24
      Width = 75
      Height = 25
      Caption = 'Refresh'
      TabOrder = 14
      OnClick = btn_win0Click
    end
  end
  object GroupBox5: TGroupBox
    Left = 0
    Top = 360
    Width = 953
    Height = 73
    Caption = 'Demo Window 5'
    TabOrder = 5
    object Label23: TLabel
      Left = 96
      Top = 17
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'H Start :'
    end
    object Label24: TLabel
      Left = 96
      Top = 40
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'H End :'
    end
    object Label25: TLabel
      Left = 336
      Top = 17
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'V Start :'
    end
    object Label26: TLabel
      Left = 336
      Top = 40
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'V End :'
    end
    object RegScrollBar21: TRegScrollBar
      Left = 152
      Top = 16
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 0
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE0000284'
      RegBits = 11
    end
    object RegScrollBar22: TRegScrollBar
      Left = 152
      Top = 40
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 1
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE0000288'
      RegBits = 11
    end
    object RegScrollBar23: TRegScrollBar
      Left = 392
      Top = 16
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 2
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE0000285'
      RegBits = 11
      RegStart = 5
    end
    object RegScrollBar24: TRegScrollBar
      Left = 392
      Top = 40
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 3
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE0000289'
      RegBits = 11
      RegStart = 5
    end
    object RegEdit21: TRegEdit
      Left = 280
      Top = 14
      Width = 41
      Height = 21
      TabOrder = 4
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE0000284'
      RegBits = 11
      TextType = ttInt
    end
    object RegEdit22: TRegEdit
      Left = 280
      Top = 38
      Width = 41
      Height = 21
      TabOrder = 5
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE0000288'
      RegBits = 11
      TextType = ttInt
    end
    object RegEdit23: TRegEdit
      Left = 520
      Top = 14
      Width = 41
      Height = 21
      TabOrder = 6
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE0000285'
      RegBits = 11
      RegStart = 5
      TextType = ttInt
    end
    object RegEdit24: TRegEdit
      Left = 520
      Top = 38
      Width = 41
      Height = 21
      TabOrder = 7
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE0000289'
      RegBits = 11
      RegStart = 5
      TextType = ttInt
    end
    object RegCheckBox6: TRegCheckBox
      Left = 11
      Top = 32
      Width = 62
      Height = 17
      Caption = 'Enable'
      TabOrder = 8
      RegAddress = '0xE000025C'
      RegBit = 5
    end
    object RadioButton21: TRadioButton
      Left = 592
      Top = 16
      Width = 57
      Height = 17
      Caption = 'Demo L'
      TabOrder = 9
      OnClick = RadioButton21Click
    end
    object RadioButton22: TRadioButton
      Tag = 2
      Left = 592
      Top = 40
      Width = 65
      Height = 17
      Caption = 'Demo T'
      TabOrder = 10
      OnClick = RadioButton21Click
    end
    object RadioButton23: TRadioButton
      Tag = 1
      Left = 664
      Top = 16
      Width = 57
      Height = 17
      Caption = 'Demo R'
      TabOrder = 11
      OnClick = RadioButton21Click
    end
    object RadioButton24: TRadioButton
      Tag = 3
      Left = 664
      Top = 40
      Width = 65
      Height = 17
      Caption = 'Demo B'
      TabOrder = 12
      OnClick = RadioButton21Click
    end
    object RadioButton38: TRadioButton
      Tag = 4
      Left = 736
      Top = 16
      Width = 49
      Height = 17
      Caption = 'Other'
      Checked = True
      TabOrder = 13
      TabStop = True
      OnClick = RadioButton21Click
    end
    object btn_win5: TButton
      Left = 856
      Top = 24
      Width = 75
      Height = 25
      Caption = 'Refresh'
      TabOrder = 14
      OnClick = btn_win0Click
    end
  end
  object GroupBox6: TGroupBox
    Left = 0
    Top = 432
    Width = 953
    Height = 73
    Caption = 'Demo Window 6'
    TabOrder = 6
    object Label27: TLabel
      Left = 96
      Top = 17
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'H Start :'
    end
    object Label28: TLabel
      Left = 96
      Top = 40
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'H End :'
    end
    object Label29: TLabel
      Left = 336
      Top = 17
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'V Start :'
    end
    object Label30: TLabel
      Left = 336
      Top = 40
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'V End :'
    end
    object RegScrollBar25: TRegScrollBar
      Left = 152
      Top = 16
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 0
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE000028C'
      RegBits = 11
    end
    object RegScrollBar26: TRegScrollBar
      Left = 152
      Top = 40
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 1
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE0000290'
      RegBits = 11
    end
    object RegScrollBar27: TRegScrollBar
      Left = 392
      Top = 16
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 2
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE000028D'
      RegBits = 11
      RegStart = 5
    end
    object RegScrollBar28: TRegScrollBar
      Left = 392
      Top = 40
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 3
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE0000291'
      RegBits = 11
      RegStart = 5
    end
    object RegEdit25: TRegEdit
      Left = 280
      Top = 14
      Width = 41
      Height = 21
      TabOrder = 4
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE000028C'
      RegBits = 11
      TextType = ttInt
    end
    object RegEdit26: TRegEdit
      Left = 280
      Top = 38
      Width = 41
      Height = 21
      TabOrder = 5
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE0000290'
      RegBits = 11
      TextType = ttInt
    end
    object RegEdit27: TRegEdit
      Left = 520
      Top = 14
      Width = 41
      Height = 21
      TabOrder = 6
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE000028D'
      RegBits = 11
      RegStart = 5
      TextType = ttInt
    end
    object RegEdit28: TRegEdit
      Left = 520
      Top = 38
      Width = 41
      Height = 21
      TabOrder = 7
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE0000291'
      RegBits = 11
      RegStart = 5
      TextType = ttInt
    end
    object RegCheckBox7: TRegCheckBox
      Left = 11
      Top = 32
      Width = 70
      Height = 17
      Caption = 'Enable'
      TabOrder = 8
      RegAddress = '0xE000025C'
      RegBit = 6
    end
    object RadioButton25: TRadioButton
      Left = 592
      Top = 16
      Width = 57
      Height = 17
      Caption = 'Demo L'
      TabOrder = 9
      OnClick = RadioButton25Click
    end
    object RadioButton26: TRadioButton
      Tag = 2
      Left = 592
      Top = 40
      Width = 65
      Height = 17
      Caption = 'Demo T'
      TabOrder = 10
      OnClick = RadioButton25Click
    end
    object RadioButton27: TRadioButton
      Tag = 1
      Left = 664
      Top = 16
      Width = 57
      Height = 17
      Caption = 'Demo R'
      TabOrder = 11
      OnClick = RadioButton25Click
    end
    object RadioButton28: TRadioButton
      Tag = 3
      Left = 664
      Top = 40
      Width = 65
      Height = 17
      Caption = 'Demo B'
      TabOrder = 12
      OnClick = RadioButton25Click
    end
    object RadioButton39: TRadioButton
      Tag = 4
      Left = 736
      Top = 16
      Width = 49
      Height = 17
      Caption = 'Other'
      Checked = True
      TabOrder = 13
      TabStop = True
      OnClick = RadioButton25Click
    end
    object btn_win6: TButton
      Left = 856
      Top = 24
      Width = 75
      Height = 25
      Caption = 'Refresh'
      TabOrder = 14
      OnClick = btn_win0Click
    end
  end
  object GroupBox7: TGroupBox
    Left = 0
    Top = 504
    Width = 953
    Height = 73
    Caption = 'Demo Window 7'
    TabOrder = 7
    object Label31: TLabel
      Left = 96
      Top = 17
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'H Start :'
    end
    object Label32: TLabel
      Left = 96
      Top = 40
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'H End :'
    end
    object Label33: TLabel
      Left = 336
      Top = 17
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'V Start :'
    end
    object Label34: TLabel
      Left = 336
      Top = 40
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'V End :'
    end
    object RegScrollBar29: TRegScrollBar
      Left = 152
      Top = 16
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 0
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE0000294'
      RegBits = 11
    end
    object RegScrollBar30: TRegScrollBar
      Left = 152
      Top = 40
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 1
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE0000298'
      RegBits = 11
    end
    object RegScrollBar31: TRegScrollBar
      Left = 392
      Top = 16
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 2
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE0000295'
      RegBits = 11
      RegStart = 5
    end
    object RegScrollBar32: TRegScrollBar
      Left = 392
      Top = 40
      Width = 121
      Height = 17
      PageSize = 0
      TabOrder = 3
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE0000299'
      RegBits = 11
      RegStart = 5
    end
    object RegEdit29: TRegEdit
      Left = 280
      Top = 14
      Width = 41
      Height = 21
      TabOrder = 4
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE0000294'
      RegBits = 11
      TextType = ttInt
    end
    object RegEdit30: TRegEdit
      Left = 280
      Top = 38
      Width = 41
      Height = 21
      TabOrder = 5
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE0000298'
      RegBits = 11
      TextType = ttInt
    end
    object RegEdit31: TRegEdit
      Left = 520
      Top = 14
      Width = 41
      Height = 21
      TabOrder = 6
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE0000295'
      RegBits = 11
      RegStart = 5
      TextType = ttInt
    end
    object RegEdit32: TRegEdit
      Left = 520
      Top = 38
      Width = 41
      Height = 21
      TabOrder = 7
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE0000299'
      RegBits = 11
      RegStart = 5
      TextType = ttInt
    end
    object RegCheckBox8: TRegCheckBox
      Left = 11
      Top = 32
      Width = 62
      Height = 17
      Caption = 'Enable'
      TabOrder = 8
      RegAddress = '0xE000025C'
      RegBit = 7
    end
    object RadioButton29: TRadioButton
      Left = 592
      Top = 16
      Width = 57
      Height = 17
      Caption = 'Demo L'
      TabOrder = 9
      OnClick = RadioButton29Click
    end
    object RadioButton30: TRadioButton
      Tag = 2
      Left = 592
      Top = 40
      Width = 65
      Height = 17
      Caption = 'Demo T'
      TabOrder = 10
      OnClick = RadioButton29Click
    end
    object RadioButton31: TRadioButton
      Tag = 1
      Left = 664
      Top = 16
      Width = 57
      Height = 17
      Caption = 'Demo R'
      TabOrder = 11
      OnClick = RadioButton29Click
    end
    object RadioButton32: TRadioButton
      Tag = 3
      Left = 664
      Top = 40
      Width = 65
      Height = 17
      Caption = 'Demo B'
      TabOrder = 12
      OnClick = RadioButton29Click
    end
    object RadioButton40: TRadioButton
      Tag = 4
      Left = 736
      Top = 16
      Width = 49
      Height = 17
      Caption = 'Other'
      Checked = True
      TabOrder = 13
      TabStop = True
      OnClick = RadioButton29Click
    end
    object btn_win7: TButton
      Left = 856
      Top = 24
      Width = 75
      Height = 25
      Caption = 'Refresh'
      TabOrder = 14
      OnClick = btn_win0Click
    end
  end
  object Button1: TButton
    Left = 24
    Top = 592
    Width = 75
    Height = 25
    Caption = 'Refresh'
    TabOrder = 8
    OnClick = Button1Click
  end
end
