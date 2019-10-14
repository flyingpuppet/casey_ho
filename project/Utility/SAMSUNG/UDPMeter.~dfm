inherited Form_DPMeter: TForm_DPMeter
  Left = 279
  Top = 196
  Height = 224
  Caption = 'Color Meter'
  OldCreateOrder = True
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object gb_ColorMeter: TGroupBox
    Left = 1
    Top = 8
    Width = 233
    Height = 137
    Caption = 'OUTPUT Meter 0'
    TabOrder = 0
    object Label5: TLabel
      Left = 24
      Top = 42
      Width = 16
      Height = 13
      Caption = 'X : '
    end
    object Label6: TLabel
      Left = 24
      Top = 65
      Width = 16
      Height = 13
      Caption = 'Y : '
    end
    object rcb_Cur0: TRegCheckBox
      Tag = 1
      Left = 8
      Top = 16
      Width = 97
      Height = 17
      Caption = 'Cursor 0 Enable'
      TabOrder = 0
      RegAddress = '0xE00E0F77'
      RegBit = 7
    end
    object RegScrollBar1: TRegScrollBar
      Left = 48
      Top = 40
      Width = 137
      Height = 17
      Max = 1919
      PageSize = 0
      TabOrder = 1
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE00E0F70'
      RegBits = 11
      UserDefineMargin = True
    end
    object RegEdit1: TRegEdit
      Left = 184
      Top = 38
      Width = 41
      Height = 21
      TabOrder = 2
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE00E0F70'
      RegBits = 11
      TextType = ttInt
    end
    object RegEdit2: TRegEdit
      Left = 184
      Top = 62
      Width = 41
      Height = 21
      TabOrder = 3
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE00E0F70'
      RegBits = 11
      RegStart = 16
      TextType = ttInt
    end
    object RegScrollBar2: TRegScrollBar
      Left = 48
      Top = 64
      Width = 137
      Height = 17
      Max = 1079
      PageSize = 0
      TabOrder = 4
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE00E0F70'
      RegBits = 11
      RegStart = 16
      UserDefineMargin = True
    end
    object rle_R0: TRegLabeledEdit
      Tag = 2
      Left = 48
      Top = 96
      Width = 41
      Height = 21
      EditLabel.Width = 11
      EditLabel.Height = 13
      EditLabel.Caption = 'R:'
      LabelPosition = lpLeft
      LabelSpacing = 3
      ReadOnly = True
      TabOrder = 5
      RegStartAddress = '0xE00E0F76'
      RegBits = 8
      TextType = ttInt
    end
    object rle_G0: TRegLabeledEdit
      Tag = 1
      Left = 121
      Top = 96
      Width = 40
      Height = 21
      EditLabel.Width = 14
      EditLabel.Height = 13
      EditLabel.Caption = 'G :'
      LabelPosition = lpLeft
      LabelSpacing = 3
      ReadOnly = True
      TabOrder = 6
      RegStartAddress = '0xE00E0F75'
      RegBits = 8
      TextType = ttInt
    end
    object rle_B0: TRegLabeledEdit
      Left = 186
      Top = 96
      Width = 39
      Height = 21
      EditLabel.Width = 13
      EditLabel.Height = 13
      EditLabel.Caption = 'B :'
      LabelPosition = lpLeft
      LabelSpacing = 3
      ReadOnly = True
      TabOrder = 7
      RegStartAddress = '0xE00E0F74'
      RegBits = 8
      TextType = ttInt
    end
  end
  object GroupBox1: TGroupBox
    Left = 256
    Top = 232
    Width = 249
    Height = 137
    Caption = 'Input Pattern'
    TabOrder = 1
    Visible = False
    object Label1: TLabel
      Left = 24
      Top = 42
      Width = 14
      Height = 13
      Caption = 'R: '
      Visible = False
    end
    object Label2: TLabel
      Left = 24
      Top = 66
      Width = 17
      Height = 13
      Caption = 'G : '
      Visible = False
    end
    object Label4: TLabel
      Left = 24
      Top = 90
      Width = 16
      Height = 13
      Caption = 'B : '
      Visible = False
    end
    object RegScrollBar3: TRegScrollBar
      Left = 48
      Top = 40
      Width = 137
      Height = 17
      PageSize = 0
      TabOrder = 0
      Visible = False
      OnScroll = RegScrollBar3Scroll
      RegStartAddress = '0xE0000140'
      RegBits = 8
    end
    object RegEdit3: TRegEdit
      Left = 184
      Top = 38
      Width = 49
      Height = 21
      TabOrder = 1
      Visible = False
      OnExit = RegEdit3Exit
      OnKeyPress = RegEdit3KeyPress
      RegStartAddress = '0xE00E0070'
      RegBits = 11
      TextType = ttInt
    end
    object RegEdit4: TRegEdit
      Tag = 1
      Left = 184
      Top = 62
      Width = 49
      Height = 21
      TabOrder = 2
      Visible = False
      OnExit = RegEdit3Exit
      OnKeyPress = RegEdit3KeyPress
      RegStartAddress = '0xE00E0070'
      RegBits = 11
      TextType = ttInt
    end
    object RegScrollBar4: TRegScrollBar
      Tag = 1
      Left = 48
      Top = 64
      Width = 137
      Height = 17
      PageSize = 0
      TabOrder = 3
      Visible = False
      OnScroll = RegScrollBar3Scroll
      RegStartAddress = '0xE0000140'
      RegBits = 8
      RegStart = 8
    end
    object cb_IPPattern: TCheckBox
      Left = 16
      Top = 16
      Width = 97
      Height = 17
      Caption = 'Pattern Enable'
      TabOrder = 4
      Visible = False
      OnClick = cb_IPPatternClick
    end
    object RegScrollBar5: TRegScrollBar
      Tag = 2
      Left = 48
      Top = 88
      Width = 137
      Height = 17
      PageSize = 0
      TabOrder = 5
      Visible = False
      OnScroll = RegScrollBar3Scroll
      RegStartAddress = '0xE0000140'
      RegBits = 8
      RegStart = 16
    end
    object RegEdit5: TRegEdit
      Tag = 2
      Left = 184
      Top = 86
      Width = 49
      Height = 21
      TabOrder = 6
      Visible = False
      OnExit = RegEdit3Exit
      OnKeyPress = RegEdit3KeyPress
      RegStartAddress = '0xE00E0070'
      RegBits = 11
      TextType = ttInt
    end
  end
  object GroupBox2: TGroupBox
    Left = 233
    Top = 8
    Width = 233
    Height = 137
    Caption = 'OUTPUT Meter 1'
    TabOrder = 2
    object Label7: TLabel
      Left = 24
      Top = 42
      Width = 16
      Height = 13
      Caption = 'X : '
    end
    object Label8: TLabel
      Left = 24
      Top = 65
      Width = 16
      Height = 13
      Caption = 'Y : '
    end
    object rcb_Cur1: TRegCheckBox
      Tag = 1
      Left = 8
      Top = 16
      Width = 97
      Height = 17
      Caption = 'Cursor 1 Enable'
      TabOrder = 0
      RegAddress = '0xE00E0F7F'
      RegBit = 7
    end
    object RegScrollBar6: TRegScrollBar
      Tag = 1
      Left = 48
      Top = 40
      Width = 137
      Height = 17
      Max = 1919
      PageSize = 0
      TabOrder = 1
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE00E0F78'
      RegBits = 11
      UserDefineMargin = True
    end
    object RegEdit6: TRegEdit
      Tag = 1
      Left = 184
      Top = 38
      Width = 41
      Height = 21
      TabOrder = 2
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE00E0F78'
      RegBits = 11
      TextType = ttInt
    end
    object RegEdit7: TRegEdit
      Tag = 1
      Left = 184
      Top = 62
      Width = 41
      Height = 21
      TabOrder = 3
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE00E0F78'
      RegBits = 11
      RegStart = 16
      TextType = ttInt
    end
    object RegScrollBar7: TRegScrollBar
      Tag = 1
      Left = 48
      Top = 64
      Width = 137
      Height = 17
      Max = 1079
      PageSize = 0
      TabOrder = 4
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE00E0F78'
      RegBits = 11
      RegStart = 16
      UserDefineMargin = True
    end
    object rle_R1: TRegLabeledEdit
      Tag = 6
      Left = 48
      Top = 96
      Width = 41
      Height = 21
      EditLabel.Width = 11
      EditLabel.Height = 13
      EditLabel.Caption = 'R:'
      LabelPosition = lpLeft
      LabelSpacing = 3
      ReadOnly = True
      TabOrder = 5
      RegStartAddress = '0xE00E0F7E'
      RegBits = 8
      TextType = ttInt
    end
    object rle_G1: TRegLabeledEdit
      Tag = 5
      Left = 121
      Top = 96
      Width = 40
      Height = 21
      EditLabel.Width = 14
      EditLabel.Height = 13
      EditLabel.Caption = 'G :'
      LabelPosition = lpLeft
      LabelSpacing = 3
      ReadOnly = True
      TabOrder = 6
      RegStartAddress = '0xE00E0F7D'
      RegBits = 8
      TextType = ttInt
    end
    object rle_B1: TRegLabeledEdit
      Tag = 4
      Left = 186
      Top = 96
      Width = 39
      Height = 21
      EditLabel.Width = 13
      EditLabel.Height = 13
      EditLabel.Caption = 'B :'
      LabelPosition = lpLeft
      LabelSpacing = 3
      ReadOnly = True
      TabOrder = 7
      RegStartAddress = '0xE00E0F7C'
      RegBits = 8
      TextType = ttInt
    end
  end
  object Button1: TButton
    Left = 32
    Top = 152
    Width = 75
    Height = 25
    Caption = 'Refresh'
    TabOrder = 3
    OnClick = Button1Click
  end
end
