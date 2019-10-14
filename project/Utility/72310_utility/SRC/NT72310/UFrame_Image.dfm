inherited Frame_Image: TFrame_Image
  Width = 519
  Height = 589
  object Label1: TLabel
    Left = 8
    Top = 224
    Width = 211
    Height = 13
    Caption = 'lbme_dbg_mvx  mvx   ME3_06[1:0] 05[7:0]   '
  end
  object Label2: TLabel
    Left = 8
    Top = 280
    Width = 220
    Height = 13
    Caption = 'lbme_dbg_mvx  mvy   ME3_07[3:0] 06[7:3]      '
  end
  object Label3: TLabel
    Left = 201
    Top = 240
    Width = 46
    Height = 13
    AutoSize = False
    Caption = '1'
  end
  object Label4: TLabel
    Left = 201
    Top = 296
    Width = 46
    Height = 13
    AutoSize = False
    Caption = '1'
  end
  object Label5: TLabel
    Left = 8
    Top = 320
    Width = 160
    Height = 13
    Caption = 'lbme_dbg_phase  ME3_04[6:0]    '
  end
  object Label6: TLabel
    Left = 8
    Top = 360
    Width = 151
    Height = 13
    Caption = 'lbme_out_sel   ME3_0C[1:0]      '
  end
  object Label7: TLabel
    Left = 8
    Top = 416
    Width = 152
    Height = 13
    Caption = 'lbme_out_sel   ME3_0D[3:0]      '
  end
  object Label8: TLabel
    Left = 201
    Top = 336
    Width = 46
    Height = 13
    AutoSize = False
    Caption = '1'
  end
  object Label9: TLabel
    Left = 201
    Top = 376
    Width = 46
    Height = 13
    AutoSize = False
    Caption = '1'
  end
  object Label10: TLabel
    Left = 201
    Top = 432
    Width = 46
    Height = 13
    AutoSize = False
    Caption = '1'
  end
  object Memo1: TMemo
    Left = 263
    Top = 456
    Width = 105
    Height = 73
    Lines.Strings = (
      'Memo1')
    TabOrder = 0
  end
  object Button6: TButton
    Left = 8
    Top = 544
    Width = 121
    Height = 25
    Caption = 'Read Block Image'
    TabOrder = 1
    OnClick = Button6Click
  end
  object LE_bWidth: TLabeledEdit
    Left = 113
    Top = 477
    Width = 105
    Height = 21
    EditLabel.Width = 66
    EditLabel.Height = 13
    EditLabel.Caption = 'Width(Blocks)'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 2
  end
  object LE_bHeight: TLabeledEdit
    Left = 113
    Top = 517
    Width = 105
    Height = 21
    EditLabel.Width = 69
    EditLabel.Height = 13
    EditLabel.Caption = 'Height(Blocks)'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 3
  end
  object LE_bTop: TLabeledEdit
    Left = 8
    Top = 477
    Width = 103
    Height = 21
    EditLabel.Width = 57
    EditLabel.Height = 13
    EditLabel.Caption = 'Top(Blocks)'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 4
  end
  object LE_bLeft: TLabeledEdit
    Left = 8
    Top = 517
    Width = 103
    Height = 21
    EditLabel.Width = 56
    EditLabel.Height = 13
    EditLabel.Caption = 'Left(Blocks)'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 5
  end
  object CheckBox1: TRegCheckBox
    Left = 8
    Top = 192
    Width = 177
    Height = 17
    Caption = 'lbme_dbg_en ME3_04[7]'
    TabOrder = 6
    OnClick = CheckBox1Click
    RegAddress = '0xE0000A04'
    RegBit = 7
  end
  object CheckBox2: TRegCheckBox
    Left = 8
    Top = 208
    Width = 201
    Height = 17
    Caption = 'lbme_dbg_mvx sign-bit ME3_06[2]'
    TabOrder = 7
    OnClick = CheckBox2Click
    RegAddress = '0xE0000A06'
    RegBit = 2
  end
  object CheckBox3: TRegCheckBox
    Left = 8
    Top = 264
    Width = 185
    Height = 17
    Caption = 'lbme_dbg_mvy sign-bit ME3_07[4]'
    TabOrder = 8
    OnClick = CheckBox3Click
    RegAddress = '0xE0000A07'
    RegBit = 4
  end
  object ScrollBar1: TRegScrollBar
    Tag = 3
    Left = 8
    Top = 240
    Width = 185
    Height = 17
    Max = 1023
    PageSize = 0
    TabOrder = 9
    OnChange = ScrollBar5Change
    OnScroll = ScrollBar1Scroll
    RegStartAddress = '0xE0000A05'
    RegBits = 10
  end
  object ScrollBar2: TRegScrollBar
    Tag = 4
    Left = 8
    Top = 296
    Width = 185
    Height = 17
    Max = 511
    PageSize = 0
    TabOrder = 10
    OnChange = ScrollBar5Change
    RegStartAddress = '0xE0000A06'
    RegBits = 9
    RegStart = 3
  end
  object ScrollBar3: TRegScrollBar
    Tag = 8
    Left = 8
    Top = 336
    Width = 185
    Height = 17
    Max = 127
    PageSize = 0
    TabOrder = 11
    OnChange = ScrollBar5Change
    RegStartAddress = '0xE0000A04'
    RegBits = 7
  end
  object ScrollBar4: TRegScrollBar
    Tag = 9
    Left = 8
    Top = 376
    Width = 185
    Height = 17
    Max = 3
    PageSize = 0
    TabOrder = 12
    OnChange = ScrollBar5Change
    RegStartAddress = '0xE0000A0C'
    RegBits = 2
  end
  object CheckBox4: TRegCheckBox
    Left = 8
    Top = 400
    Width = 177
    Height = 17
    Caption = 'lbme_dm_off  ME3_0D[7]    '
    TabOrder = 13
    OnClick = CheckBox4Click
    RegAddress = '0xE0000A0D'
    RegBit = 7
  end
  object ScrollBar5: TRegScrollBar
    Tag = 10
    Left = 8
    Top = 432
    Width = 185
    Height = 17
    Max = 7
    PageSize = 0
    TabOrder = 14
    OnChange = ScrollBar5Change
    RegStartAddress = '0xE0000A0D'
    RegBits = 4
  end
  object PB: TProgressBar
    Left = 0
    Top = 578
    Width = 519
    Height = 11
    Align = alBottom
    Min = 0
    Max = 100
    TabOrder = 15
  end
  object LE_width: TLabeledEdit
    Left = 382
    Top = 221
    Width = 115
    Height = 21
    EditLabel.Width = 28
    EditLabel.Height = 13
    EditLabel.Caption = 'Width'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 16
  end
  object LE_height: TLabeledEdit
    Left = 382
    Top = 261
    Width = 115
    Height = 21
    EditLabel.Width = 31
    EditLabel.Height = 13
    EditLabel.Caption = 'Height'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 17
  end
  object LE_top: TLabeledEdit
    Left = 263
    Top = 221
    Width = 115
    Height = 21
    EditLabel.Width = 19
    EditLabel.Height = 13
    EditLabel.Caption = 'Top'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 18
  end
  object LE_left: TLabeledEdit
    Left = 263
    Top = 261
    Width = 115
    Height = 21
    EditLabel.Width = 18
    EditLabel.Height = 13
    EditLabel.Caption = 'Left'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 19
  end
  object Button4: TButton
    Left = 263
    Top = 392
    Width = 75
    Height = 25
    Caption = 'ReadImage'
    TabOrder = 20
    OnClick = Button4Click
  end
  object GroupBox1: TGroupBox
    Left = 263
    Top = 296
    Width = 235
    Height = 41
    Caption = 'Pixel bit'
    TabOrder = 21
    object RB_8bit: TRadioButton
      Left = 16
      Top = 16
      Width = 113
      Height = 17
      Caption = '8bit'
      Checked = True
      TabOrder = 0
      TabStop = True
    end
    object RB_10bit: TRadioButton
      Left = 56
      Top = 16
      Width = 113
      Height = 17
      Caption = '10bit'
      TabOrder = 1
    end
  end
  object GroupBox2: TGroupBox
    Left = 263
    Top = 344
    Width = 235
    Height = 41
    Caption = 'Pixel Format'
    TabOrder = 22
    object RB_RGB: TRadioButton
      Left = 16
      Top = 16
      Width = 113
      Height = 17
      Caption = 'RGB'
      Checked = True
      TabOrder = 0
      TabStop = True
    end
    object RB_YCbCr444: TRadioButton
      Left = 72
      Top = 16
      Width = 105
      Height = 17
      Caption = 'YCbCr444'
      TabOrder = 1
    end
    object RB_YCbCr422: TRadioButton
      Left = 152
      Top = 16
      Width = 81
      Height = 17
      Caption = 'YCbCr422'
      TabOrder = 2
    end
  end
  object Button5: TButton
    Left = 343
    Top = 392
    Width = 75
    Height = 25
    Caption = 'WriteImage'
    TabOrder = 23
    OnClick = Button5Click
  end
  object Button9: TButton
    Left = 423
    Top = 392
    Width = 75
    Height = 25
    Caption = 'Read MEY'
    TabOrder = 24
    OnClick = Button9Click
  end
  object CB_Burst: TCheckBox
    Left = 263
    Top = 432
    Width = 97
    Height = 17
    Caption = 'Burst Mode'
    Checked = True
    State = cbChecked
    TabOrder = 25
  end
  object Button1: TButton
    Left = 8
    Top = 136
    Width = 75
    Height = 25
    Caption = 'Refresh'
    TabOrder = 26
    OnClick = Button1Click
  end
  object SaveBitmap: TSaveDialog
    DefaultExt = '.bmp'
    Filter = '*.bmp'
    Left = 696
    Top = 16
  end
end
