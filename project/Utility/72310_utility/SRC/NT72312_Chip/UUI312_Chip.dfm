inherited Form_UI312_Chip: TForm_UI312_Chip
  Left = 422
  Top = 137
  Width = 499
  Height = 531
  Caption = 'UI'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  object rg_Input_Format: TRadioGroup
    Left = 8
    Top = 88
    Width = 129
    Height = 105
    Caption = 'Input Format'
    ItemIndex = 0
    Items.Strings = (
      'Input_2D'
      'Input_3D_L/R'
      'Input_3D_TB'
      'Input_3D_SBS')
    TabOrder = 0
    OnClick = rg_Input_FormatClick
  end
  object rg_Output_Format: TRadioGroup
    Left = 136
    Top = 88
    Width = 129
    Height = 105
    Caption = 'Output Format'
    ItemIndex = 0
    Items.Strings = (
      'Output_2D'
      'Output_3D_PR'
      'Output_3D_SG'
      'Output_3D_SG_SS')
    TabOrder = 1
    OnClick = rg_Output_FormatClick
  end
  object rg_Input_Mode: TRadioGroup
    Left = 8
    Top = 48
    Width = 257
    Height = 41
    Caption = 'Input Mode'
    Columns = 2
    ItemIndex = 0
    Items.Strings = (
      'VD'
      'PC')
    TabOrder = 2
    OnClick = rg_Input_ModeClick
  end
  object rg_SwapLR: TRadioGroup
    Left = 8
    Top = 192
    Width = 257
    Height = 41
    Caption = 'Swap LR'
    Columns = 2
    ItemIndex = 0
    Items.Strings = (
      'L_To_R'
      'R_To_L')
    TabOrder = 3
    OnClick = rg_SwapLRClick
  end
  object gb_depth: TGroupBox
    Left = 8
    Top = 232
    Width = 257
    Height = 113
    Caption = '2D To 3D'
    TabOrder = 4
    object Label1: TLabel
      Left = 24
      Top = 20
      Width = 73
      Height = 13
      AutoSize = False
      Caption = 'Depth Level'
    end
    object Label2: TLabel
      Left = 24
      Top = 68
      Width = 73
      Height = 13
      AutoSize = False
      Caption = 'Disparity Level'
    end
    object tb_Depth: TTrackBar
      Left = 99
      Top = 16
      Width = 150
      Height = 45
      Orientation = trHorizontal
      Frequency = 1
      Position = 0
      SelEnd = 0
      SelStart = 0
      TabOrder = 0
      TickMarks = tmBottomRight
      TickStyle = tsAuto
      OnChange = tb_DepthChange
    end
    object tb_Disparity: TTrackBar
      Left = 99
      Top = 64
      Width = 150
      Height = 45
      Orientation = trHorizontal
      Frequency = 1
      Position = 0
      SelEnd = 0
      SelStart = 0
      TabOrder = 1
      TickMarks = tmBottomRight
      TickStyle = tsAuto
      OnChange = tb_DisparityChange
    end
  end
  object rcb_Mute: TRegCheckBox
    Left = 16
    Top = 16
    Width = 97
    Height = 17
    Caption = 'Mute Video'
    TabOrder = 5
    RegAddress = '0x9F02004E'
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 345
    Width = 257
    Height = 113
    Caption = 'FRC'
    TabOrder = 6
    object Label3: TLabel
      Left = 24
      Top = 20
      Width = 73
      Height = 13
      AutoSize = False
      Caption = 'FRC Level'
    end
    object Label4: TLabel
      Left = 24
      Top = 68
      Width = 81
      Height = 13
      AutoSize = False
      Caption = 'DeJudder Level'
    end
    object tb_FRC: TTrackBar
      Left = 99
      Top = 16
      Width = 150
      Height = 45
      Orientation = trHorizontal
      Frequency = 1
      Position = 0
      SelEnd = 0
      SelStart = 0
      TabOrder = 0
      TickMarks = tmBottomRight
      TickStyle = tsAuto
      OnChange = tb_FRCChange
    end
    object tb_Dejudder: TTrackBar
      Left = 99
      Top = 64
      Width = 150
      Height = 45
      Orientation = trHorizontal
      Frequency = 1
      Position = 0
      SelEnd = 0
      SelStart = 0
      TabOrder = 1
      TickMarks = tmBottomRight
      TickStyle = tsAuto
      OnChange = tb_DejudderChange
    end
  end
  object Button1: TButton
    Left = 8
    Top = 464
    Width = 75
    Height = 25
    Caption = 'Refresh'
    TabOrder = 7
    OnClick = Button1Click
  end
  object GroupBox2: TGroupBox
    Left = 272
    Top = 48
    Width = 209
    Height = 145
    Caption = 'PWM'
    TabOrder = 8
    object rle_PWM_Freq: TRegLabeledEdit
      Left = 80
      Top = 32
      Width = 121
      Height = 21
      EditLabel.Width = 57
      EditLabel.Height = 13
      EditLabel.Caption = 'PWM Freq: '
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 0
      RegStartAddress = '0x9F020055'
      RegBits = 8
    end
    object rle_PWM_Duty: TRegLabeledEdit
      Left = 80
      Top = 72
      Width = 121
      Height = 21
      EditLabel.Width = 58
      EditLabel.Height = 13
      EditLabel.Caption = 'PWM Duty: '
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 1
      RegStartAddress = '0x9F020056'
      RegBits = 16
    end
  end
  object rle_Test_Pattern: TRegLabeledEdit
    Left = 200
    Top = 16
    Width = 121
    Height = 21
    EditLabel.Width = 64
    EditLabel.Height = 13
    EditLabel.Caption = 'Test Pattern: '
    LabelPosition = lpLeft
    LabelSpacing = 3
    TabOrder = 9
    RegStartAddress = '0x9F020054'
    RegBits = 8
  end
  object Button2: TButton
    Left = 352
    Top = 16
    Width = 75
    Height = 25
    Caption = 'Button2'
    TabOrder = 10
  end
end
