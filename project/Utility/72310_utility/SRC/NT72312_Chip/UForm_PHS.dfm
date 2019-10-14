inherited Form_PHS: TForm_PHS
  Left = 396
  Top = 188
  Caption = 'PHS'
  PixelsPerInch = 96
  TextHeight = 13
  object btn_autotiming: TButton
    Left = 32
    Top = 40
    Width = 75
    Height = 25
    Caption = 'Auto Timing'
    TabOrder = 0
    OnClick = btn_autotimingClick
  end
  object le_PHS: TLabeledEdit
    Left = 32
    Top = 96
    Width = 145
    Height = 21
    EditLabel.Width = 66
    EditLabel.Height = 13
    EditLabel.Caption = 'Scaling Ratio:'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 1
    OnKeyPress = le_PHSKeyPress
  end
end
