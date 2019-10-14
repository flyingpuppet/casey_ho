inherited Form_Validation: TForm_Validation
  Left = 160
  Top = 0
  Width = 1156
  Height = 734
  Caption = 'Validation'
  OldCreateOrder = True
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object pl_dock: TPanel
    Left = 0
    Top = 253
    Width = 1148
    Height = 447
    Align = alBottom
    TabOrder = 0
    object pl_left: TPanel
      Left = 1
      Top = 1
      Width = 568
      Height = 445
      Align = alLeft
      TabOrder = 0
    end
    object pl_right: TPanel
      Left = 569
      Top = 1
      Width = 578
      Height = 445
      Align = alClient
      TabOrder = 1
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 1148
    Height = 253
    Align = alClient
    TabOrder = 1
    object GroupBox8: TGroupBox
      Left = 0
      Top = 0
      Width = 361
      Height = 49
      Caption = 'H_Total'
      TabOrder = 0
      object RegLabeledEdit10: TRegLabeledEdit
        Left = 56
        Top = 16
        Width = 65
        Height = 21
        EditLabel.Width = 43
        EditLabel.Height = 13
        EditLabel.Caption = 'FRC_6C '
        LabelPosition = lpLeft
        LabelSpacing = 3
        TabOrder = 0
        RegStartAddress = '0xE000006C'
        RegBits = 12
      end
      object RegLabeledEdit11: TRegLabeledEdit
        Left = 168
        Top = 16
        Width = 65
        Height = 21
        EditLabel.Width = 32
        EditLabel.Height = 13
        EditLabel.Caption = 'IP_0C '
        LabelPosition = lpLeft
        LabelSpacing = 3
        TabOrder = 1
        RegStartAddress = '0xE000010C'
        RegBits = 12
      end
      object RegLabeledEdit12: TRegLabeledEdit
        Left = 288
        Top = 16
        Width = 65
        Height = 21
        EditLabel.Width = 44
        EditLabel.Height = 13
        EditLabel.Caption = 'MMU_50'
        LabelPosition = lpLeft
        LabelSpacing = 3
        TabOrder = 2
        RegStartAddress = '0xE0000B50'
        RegBits = 12
      end
    end
    object GroupBox9: TGroupBox
      Left = 360
      Top = 0
      Width = 361
      Height = 49
      Caption = 'V_Total'
      TabOrder = 1
      object RegLabeledEdit13: TRegLabeledEdit
        Left = 56
        Top = 16
        Width = 65
        Height = 21
        EditLabel.Width = 42
        EditLabel.Height = 13
        EditLabel.Caption = 'FRC_70 '
        LabelPosition = lpLeft
        LabelSpacing = 3
        TabOrder = 0
        RegStartAddress = '0xE0000070'
        RegBits = 12
      end
      object RegLabeledEdit14: TRegLabeledEdit
        Left = 168
        Top = 16
        Width = 65
        Height = 21
        EditLabel.Width = 31
        EditLabel.Height = 13
        EditLabel.Caption = 'IP_10 '
        LabelPosition = lpLeft
        LabelSpacing = 3
        TabOrder = 1
        RegStartAddress = '0xE0000110'
        RegBits = 12
      end
      object RegLabeledEdit15: TRegLabeledEdit
        Left = 288
        Top = 16
        Width = 65
        Height = 21
        EditLabel.Width = 44
        EditLabel.Height = 13
        EditLabel.Caption = 'MMU_54'
        LabelPosition = lpLeft
        LabelSpacing = 3
        TabOrder = 2
        RegStartAddress = '0xE0000B54'
        RegBits = 10
      end
    end
    object GroupBox10: TGroupBox
      Left = 0
      Top = 48
      Width = 249
      Height = 105
      Caption = 'H_Active'
      TabOrder = 2
      object Label17: TLabel
        Left = 8
        Top = 19
        Width = 43
        Height = 13
        Caption = 'FRC_6E '
      end
      object Label18: TLabel
        Left = 5
        Top = 40
        Width = 38
        Height = 13
        Caption = ' IP_0E  '
      end
      object Label19: TLabel
        Left = 8
        Top = 61
        Width = 47
        Height = 13
        Caption = 'MMU_52 '
      end
      object Label20: TLabel
        Left = 8
        Top = 83
        Width = 31
        Height = 13
        Caption = 'IP_94 '
      end
      object RegScrollBar17: TRegScrollBar
        Left = 56
        Top = 16
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 0
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE000006E'
        RegBits = 12
      end
      object RegEdit17: TRegEdit
        Left = 192
        Top = 14
        Width = 41
        Height = 21
        TabOrder = 1
        RegStartAddress = '0xE000006E'
        RegBits = 12
      end
      object RegScrollBar18: TRegScrollBar
        Left = 56
        Top = 37
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 2
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE000010E'
        RegBits = 12
      end
      object RegEdit18: TRegEdit
        Left = 192
        Top = 35
        Width = 41
        Height = 21
        TabOrder = 3
        RegStartAddress = '0xE000010E'
        RegBits = 12
      end
      object RegScrollBar19: TRegScrollBar
        Left = 56
        Top = 58
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 4
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE0000B52'
        RegBits = 12
      end
      object RegEdit19: TRegEdit
        Left = 192
        Top = 56
        Width = 41
        Height = 21
        TabOrder = 5
        RegStartAddress = '0xE0000B52'
        RegBits = 12
      end
      object RegScrollBar20: TRegScrollBar
        Left = 56
        Top = 80
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 6
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE0000194'
        RegBits = 12
      end
      object RegEdit20: TRegEdit
        Left = 192
        Top = 78
        Width = 41
        Height = 21
        TabOrder = 7
        RegStartAddress = '0xE0000194'
        RegBits = 12
      end
    end
    object GroupBox11: TGroupBox
      Left = 248
      Top = 48
      Width = 249
      Height = 105
      Caption = 'V_Active'
      TabOrder = 3
      object Label21: TLabel
        Left = 16
        Top = 19
        Width = 42
        Height = 13
        Caption = 'FRC_72 '
      end
      object Label22: TLabel
        Left = 16
        Top = 40
        Width = 31
        Height = 13
        Caption = 'IP_12 '
      end
      object Label23: TLabel
        Left = 16
        Top = 61
        Width = 47
        Height = 13
        Caption = 'MMU_56 '
      end
      object Label24: TLabel
        Left = 16
        Top = 83
        Width = 31
        Height = 13
        Caption = 'IP_96 '
      end
      object RegScrollBar21: TRegScrollBar
        Left = 64
        Top = 16
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 0
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE0000072'
        RegBits = 12
      end
      object RegEdit21: TRegEdit
        Left = 200
        Top = 14
        Width = 41
        Height = 21
        TabOrder = 1
        RegStartAddress = '0xE0000072'
        RegBits = 12
      end
      object RegScrollBar22: TRegScrollBar
        Left = 64
        Top = 37
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 2
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE0000112'
        RegBits = 12
      end
      object RegEdit22: TRegEdit
        Left = 200
        Top = 35
        Width = 41
        Height = 21
        TabOrder = 3
        RegStartAddress = '0xE0000112'
        RegBits = 12
      end
      object RegScrollBar23: TRegScrollBar
        Left = 64
        Top = 58
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 4
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE0000B56'
        RegBits = 12
      end
      object RegEdit23: TRegEdit
        Left = 200
        Top = 56
        Width = 41
        Height = 21
        TabOrder = 5
        RegStartAddress = '0xE0000B56'
        RegBits = 12
      end
      object RegScrollBar24: TRegScrollBar
        Left = 64
        Top = 80
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 6
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE0000196'
        RegBits = 12
      end
      object RegEdit24: TRegEdit
        Left = 200
        Top = 78
        Width = 41
        Height = 21
        TabOrder = 7
        RegStartAddress = '0xE0000196'
        RegBits = 12
      end
    end
    object Button2: TButton
      Left = 1082
      Top = 56
      Width = 65
      Height = 25
      Caption = 'Refresh'
      TabOrder = 4
      OnClick = Button2Click
    end
    object GroupBox12: TGroupBox
      Left = 720
      Top = 0
      Width = 425
      Height = 49
      Caption = 'Burst Length'
      TabOrder = 5
      object RegLabeledEdit16: TRegLabeledEdit
        Left = 72
        Top = 16
        Width = 65
        Height = 21
        EditLabel.Width = 57
        EditLabel.Height = 13
        EditLabel.Caption = 'MMU_4D y '
        LabelPosition = lpLeft
        LabelSpacing = 3
        TabOrder = 0
        RegStartAddress = '0xE0000B4D'
        RegBits = 7
      end
      object RegLabeledEdit17: TRegLabeledEdit
        Left = 208
        Top = 16
        Width = 65
        Height = 21
        EditLabel.Width = 60
        EditLabel.Height = 13
        EditLabel.Caption = 'MMU_ 4E c '
        LabelPosition = lpLeft
        LabelSpacing = 3
        TabOrder = 1
        RegStartAddress = '0xE0000B4E'
        RegBits = 7
      end
      object RegLabeledEdit18: TRegLabeledEdit
        Left = 344
        Top = 16
        Width = 65
        Height = 21
        EditLabel.Width = 61
        EditLabel.Height = 13
        EditLabel.Caption = 'MMU_4F qy '
        LabelPosition = lpLeft
        LabelSpacing = 3
        TabOrder = 2
        RegStartAddress = '0xE0000B4F'
        RegBits = 6
      end
    end
    object GroupBox13: TGroupBox
      Left = 496
      Top = 48
      Width = 585
      Height = 105
      Caption = 'IP burst+cmd Len'
      TabOrder = 6
      object Label25: TLabel
        Left = 8
        Top = 19
        Width = 54
        Height = 13
        Caption = 'y_burst len '
      end
      object Label26: TLabel
        Left = 8
        Top = 40
        Width = 52
        Height = 13
        Caption = 'c_burst len'
      end
      object Label27: TLabel
        Left = 8
        Top = 61
        Width = 57
        Height = 13
        Caption = 'qy_burst len'
      end
      object Label28: TLabel
        Left = 8
        Top = 83
        Width = 60
        Height = 13
        Caption = 'rqy_burst len'
      end
      object Label1: TLabel
        Left = 290
        Top = 17
        Width = 51
        Height = 13
        Caption = 'y_cmd_len'
      end
      object Label2: TLabel
        Left = 290
        Top = 38
        Width = 55
        Height = 13
        Caption = 'c_burst_len'
      end
      object Label3: TLabel
        Left = 290
        Top = 59
        Width = 54
        Height = 13
        Caption = 'qy_cmd len'
      end
      object Label4: TLabel
        Left = 290
        Top = 81
        Width = 57
        Height = 13
        Caption = 'rqy_cmd len'
      end
      object RegScrollBar25: TRegScrollBar
        Left = 72
        Top = 16
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 0
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE0000108'
        RegBits = 7
      end
      object RegEdit25: TRegEdit
        Left = 208
        Top = 14
        Width = 41
        Height = 21
        TabOrder = 1
        RegStartAddress = '0xE0000108'
        RegBits = 7
      end
      object RegScrollBar26: TRegScrollBar
        Left = 72
        Top = 37
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 2
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE0000109'
        RegBits = 7
      end
      object RegEdit26: TRegEdit
        Left = 208
        Top = 35
        Width = 41
        Height = 21
        TabOrder = 3
        RegStartAddress = '0xE0000109'
        RegBits = 7
      end
      object RegScrollBar27: TRegScrollBar
        Left = 72
        Top = 58
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 4
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE000010A'
        RegBits = 6
      end
      object RegEdit27: TRegEdit
        Left = 208
        Top = 56
        Width = 41
        Height = 21
        TabOrder = 5
        RegStartAddress = '0xE000010A'
        RegBits = 6
      end
      object RegScrollBar28: TRegScrollBar
        Left = 72
        Top = 80
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 6
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE0000106'
        RegBits = 6
      end
      object RegEdit28: TRegEdit
        Left = 208
        Top = 78
        Width = 41
        Height = 21
        TabOrder = 7
        RegStartAddress = '0xE0000106'
        RegBits = 6
      end
      object RegScrollBar1: TRegScrollBar
        Left = 354
        Top = 14
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 8
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE0000104'
        RegBits = 4
      end
      object RegEdit1: TRegEdit
        Left = 490
        Top = 12
        Width = 41
        Height = 21
        TabOrder = 9
        RegStartAddress = '0xE0000104'
        RegBits = 4
      end
      object RegScrollBar2: TRegScrollBar
        Left = 354
        Top = 35
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 10
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE0000104'
        RegBits = 4
        RegStart = 4
      end
      object RegEdit2: TRegEdit
        Left = 490
        Top = 33
        Width = 41
        Height = 21
        TabOrder = 11
        RegStartAddress = '0xE0000104'
        RegBits = 4
        RegStart = 4
      end
      object RegScrollBar3: TRegScrollBar
        Left = 354
        Top = 56
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 12
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE0000105'
        RegBits = 4
      end
      object RegEdit3: TRegEdit
        Left = 490
        Top = 54
        Width = 41
        Height = 21
        TabOrder = 13
        RegStartAddress = '0xE0000105'
        RegBits = 4
      end
      object RegScrollBar4: TRegScrollBar
        Left = 354
        Top = 78
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 14
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE0000105'
        RegBits = 4
        RegStart = 4
      end
      object RegEdit4: TRegEdit
        Left = 490
        Top = 74
        Width = 41
        Height = 21
        TabOrder = 15
        RegStartAddress = '0xE0000105'
        RegBits = 4
        RegStart = 4
      end
    end
    object GroupBox14: TGroupBox
      Left = 0
      Top = 152
      Width = 1081
      Height = 105
      Caption = 'MMU burst+cmd Len'
      TabOrder = 7
      object Label29: TLabel
        Left = 16
        Top = 19
        Width = 70
        Height = 13
        Caption = 'DM0_Burst len'
      end
      object Label30: TLabel
        Left = 16
        Top = 40
        Width = 70
        Height = 13
        Caption = 'DM1_Burst len'
      end
      object Label31: TLabel
        Left = 280
        Top = 19
        Width = 70
        Height = 13
        Caption = 'DM4_Burst len'
      end
      object Label32: TLabel
        Left = 280
        Top = 41
        Width = 70
        Height = 13
        Caption = 'DM5_Burst len'
      end
      object Label5: TLabel
        Left = 544
        Top = 43
        Width = 70
        Height = 13
        Caption = 'DM1_CMD len'
      end
      object Label6: TLabel
        Left = 544
        Top = 64
        Width = 70
        Height = 13
        Caption = 'DM2_CMD len'
      end
      object Label7: TLabel
        Left = 816
        Top = 39
        Width = 70
        Height = 13
        Caption = 'DM5_CMD len'
      end
      object Label8: TLabel
        Left = 816
        Top = 61
        Width = 70
        Height = 13
        Caption = 'DM6_CMD len'
      end
      object Label9: TLabel
        Left = 16
        Top = 62
        Width = 70
        Height = 13
        Caption = 'DM2_Burst len'
      end
      object Label10: TLabel
        Left = 16
        Top = 84
        Width = 70
        Height = 13
        Caption = 'DM3_Burst len'
      end
      object Label11: TLabel
        Left = 280
        Top = 62
        Width = 70
        Height = 13
        Caption = 'DM6_Burst len'
      end
      object Label12: TLabel
        Left = 544
        Top = 20
        Width = 70
        Height = 13
        Caption = 'DM0_CMD len'
      end
      object Label13: TLabel
        Left = 544
        Top = 86
        Width = 70
        Height = 13
        Caption = 'DM3_CMD len'
      end
      object Label14: TLabel
        Left = 816
        Top = 20
        Width = 70
        Height = 13
        Caption = 'DM4_CMD len'
      end
      object RegScrollBar29: TRegScrollBar
        Left = 96
        Top = 16
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 0
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE0000B6C'
        RegBits = 6
      end
      object RegEdit29: TRegEdit
        Left = 232
        Top = 14
        Width = 41
        Height = 21
        TabOrder = 1
        RegStartAddress = '0xE0000B6C'
        RegBits = 6
      end
      object RegScrollBar30: TRegScrollBar
        Left = 96
        Top = 37
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 2
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE0000B6E'
        RegBits = 6
      end
      object RegEdit30: TRegEdit
        Left = 232
        Top = 35
        Width = 41
        Height = 21
        TabOrder = 3
        RegStartAddress = '0xE0000B6E'
        RegBits = 6
      end
      object RegScrollBar31: TRegScrollBar
        Left = 360
        Top = 16
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 4
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE0000B74'
        RegBits = 6
      end
      object RegEdit31: TRegEdit
        Left = 496
        Top = 14
        Width = 41
        Height = 21
        TabOrder = 5
        RegStartAddress = '0xE0000B74'
        RegBits = 6
      end
      object RegScrollBar32: TRegScrollBar
        Left = 360
        Top = 38
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 6
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE0000B76'
        RegBits = 6
      end
      object RegEdit32: TRegEdit
        Left = 496
        Top = 36
        Width = 41
        Height = 21
        TabOrder = 7
        RegStartAddress = '0xE0000B76'
        RegBits = 6
      end
      object RegScrollBar5: TRegScrollBar
        Left = 624
        Top = 39
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 8
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE0000B6F'
        RegBits = 4
      end
      object RegEdit5: TRegEdit
        Left = 760
        Top = 37
        Width = 41
        Height = 21
        TabOrder = 9
        RegStartAddress = '0xE0000B6F'
        RegBits = 4
      end
      object RegScrollBar6: TRegScrollBar
        Left = 624
        Top = 60
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 10
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE0000B71'
        RegBits = 4
      end
      object RegEdit6: TRegEdit
        Left = 760
        Top = 58
        Width = 41
        Height = 21
        TabOrder = 11
        RegStartAddress = '0xE0000B71'
        RegBits = 4
      end
      object RegScrollBar7: TRegScrollBar
        Left = 896
        Top = 39
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 12
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE0000B77'
        RegBits = 4
      end
      object RegEdit7: TRegEdit
        Left = 1032
        Top = 37
        Width = 41
        Height = 21
        TabOrder = 13
        RegStartAddress = '0xE0000B77'
        RegBits = 4
      end
      object RegScrollBar8: TRegScrollBar
        Left = 896
        Top = 61
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 14
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE0000B79'
        RegBits = 4
      end
      object RegEdit8: TRegEdit
        Left = 1032
        Top = 59
        Width = 41
        Height = 21
        TabOrder = 15
        RegStartAddress = '0xE0000B79'
        RegBits = 4
      end
      object RegScrollBar9: TRegScrollBar
        Left = 96
        Top = 59
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 16
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE0000B70'
        RegBits = 6
      end
      object RegEdit9: TRegEdit
        Left = 232
        Top = 57
        Width = 41
        Height = 21
        TabOrder = 17
        RegStartAddress = '0xE0000B70'
        RegBits = 6
      end
      object RegScrollBar10: TRegScrollBar
        Left = 96
        Top = 81
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 18
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE0000B72'
        RegBits = 6
      end
      object RegEdit10: TRegEdit
        Left = 232
        Top = 79
        Width = 41
        Height = 21
        TabOrder = 19
        RegStartAddress = '0xE0000B72'
        RegBits = 6
      end
      object RegScrollBar11: TRegScrollBar
        Left = 360
        Top = 59
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 20
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE0000B78'
        RegBits = 6
      end
      object RegEdit11: TRegEdit
        Left = 496
        Top = 57
        Width = 41
        Height = 21
        TabOrder = 21
        RegStartAddress = '0xE0000B78'
        RegBits = 6
      end
      object RegScrollBar12: TRegScrollBar
        Left = 624
        Top = 17
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 22
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE0000B6D'
        RegBits = 4
      end
      object RegEdit12: TRegEdit
        Left = 760
        Top = 15
        Width = 41
        Height = 21
        TabOrder = 23
        RegStartAddress = '0xE0000B6D'
        RegBits = 4
      end
      object RegScrollBar13: TRegScrollBar
        Left = 624
        Top = 82
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 24
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE0000B73'
        RegBits = 4
      end
      object RegEdit13: TRegEdit
        Left = 760
        Top = 80
        Width = 41
        Height = 21
        TabOrder = 25
        RegStartAddress = '0xE0000B73'
        RegBits = 4
      end
      object RegScrollBar14: TRegScrollBar
        Left = 896
        Top = 17
        Width = 129
        Height = 17
        Max = 2000
        PageSize = 0
        TabOrder = 26
        OnChange = RegScrollBar17Change
        RegStartAddress = '0xE0000B75'
        RegBits = 4
      end
      object RegEdit14: TRegEdit
        Left = 1032
        Top = 15
        Width = 41
        Height = 21
        TabOrder = 27
        RegStartAddress = '0xE0000B75'
        RegBits = 4
      end
    end
  end
end
