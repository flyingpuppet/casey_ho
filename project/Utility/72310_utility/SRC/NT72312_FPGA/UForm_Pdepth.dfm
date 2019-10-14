inherited Form_Pdepth: TForm_Pdepth
  Left = 699
  Top = 201
  Caption = 'Form_Pdepth'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  object LE_width: TLabeledEdit
    Left = 167
    Top = 37
    Width = 115
    Height = 21
    EditLabel.Width = 28
    EditLabel.Height = 13
    EditLabel.Caption = 'Width'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 0
  end
  object LE_height: TLabeledEdit
    Left = 167
    Top = 77
    Width = 115
    Height = 21
    EditLabel.Width = 31
    EditLabel.Height = 13
    EditLabel.Caption = 'Height'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 1
  end
  object LE_top: TLabeledEdit
    Left = 39
    Top = 37
    Width = 115
    Height = 21
    EditLabel.Width = 19
    EditLabel.Height = 13
    EditLabel.Caption = 'Top'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 2
  end
  object LE_left: TLabeledEdit
    Left = 39
    Top = 77
    Width = 115
    Height = 21
    EditLabel.Width = 18
    EditLabel.Height = 13
    EditLabel.Caption = 'Left'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 3
  end
  object Button4: TButton
    Left = 39
    Top = 109
    Width = 75
    Height = 25
    Caption = 'ReadImage'
    TabOrder = 4
    OnClick = Button4Click
  end
  object PB: TProgressBar
    Left = 0
    Top = 312
    Width = 474
    Height = 14
    Align = alBottom
    Min = 0
    Max = 100
    TabOrder = 5
  end
  object SaveBitmap: TSaveDialog
    Left = 328
    Top = 32
  end
end
