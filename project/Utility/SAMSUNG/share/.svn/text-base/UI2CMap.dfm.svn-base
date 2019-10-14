object I2CMap: TI2CMap
  Left = 237
  Top = 116
  Width = 934
  Height = 590
  Caption = 'I2CMap'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object ed_Slave: TLabeledEdit
    Left = 88
    Top = 24
    Width = 49
    Height = 21
    EditLabel.Width = 71
    EditLabel.Height = 13
    EditLabel.Caption = 'Slave Address:'
    LabelPosition = lpLeft
    LabelSpacing = 3
    TabOrder = 0
    Text = '0x7C'
    OnKeyPress = ed_SlaveKeyPress
  end
  object ed_Reg: TLabeledEdit
    Left = 88
    Top = 56
    Width = 49
    Height = 21
    EditLabel.Width = 42
    EditLabel.Height = 13
    EditLabel.Caption = 'Register:'
    LabelPosition = lpLeft
    LabelSpacing = 3
    TabOrder = 1
  end
  object ed_Value: TLabeledEdit
    Left = 88
    Top = 88
    Width = 49
    Height = 21
    EditLabel.Width = 30
    EditLabel.Height = 13
    EditLabel.Caption = 'Value:'
    LabelPosition = lpLeft
    LabelSpacing = 3
    TabOrder = 2
  end
  object Button1: TButton
    Left = 176
    Top = 24
    Width = 75
    Height = 25
    Caption = 'Read'
    TabOrder = 3
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 176
    Top = 56
    Width = 75
    Height = 25
    Caption = 'Write'
    TabOrder = 4
    OnClick = Button2Click
  end
  object sg_Regs: TStringGrid
    Left = 340
    Top = 48
    Width = 445
    Height = 449
    ColCount = 17
    DefaultColWidth = 25
    DefaultRowHeight = 25
    RowCount = 17
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected]
    TabOrder = 5
    OnKeyPress = sg_RegsKeyPress
    OnSelectCell = sg_RegsSelectCell
    ColWidths = (
      25
      25
      25
      25
      25
      25
      25
      25
      25
      25
      25
      25
      25
      25
      25
      25
      25)
  end
  object Button3: TButton
    Left = 344
    Top = 16
    Width = 75
    Height = 25
    Caption = 'Read'
    TabOrder = 6
    OnClick = Button3Click
  end
end
