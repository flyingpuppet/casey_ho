inherited Frame_DDR: TFrame_DDR
  Width = 576
  Height = 635
  object Memo1: TMemo
    Left = 72
    Top = 552
    Width = 209
    Height = 65
    TabOrder = 7
    Visible = False
  end
  object Stg_DDR: TStringGrid
    Left = 9
    Top = 122
    Width = 472
    Height = 455
    ColCount = 17
    DefaultColWidth = 25
    DefaultRowHeight = 25
    RowCount = 17
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #23435#20307
    Font.Style = []
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 0
    OnKeyPress = Stg_DDRKeyPress
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
  object BtnDDRLoad: TButton
    Left = 264
    Top = 53
    Width = 73
    Height = 25
    Caption = 'Load'
    TabOrder = 1
    OnClick = BtnDDRLoadClick
  end
  object BtnDDRRead: TButton
    Left = 176
    Top = 53
    Width = 73
    Height = 25
    Caption = 'Read'
    TabOrder = 2
    OnClick = BtnDDRReadClick
  end
  object LE_StartAdd: TLabeledEdit
    Left = 8
    Top = 93
    Width = 161
    Height = 21
    EditLabel.Width = 63
    EditLabel.Height = 13
    EditLabel.Caption = 'Start addr: 0x'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 3
  end
  object LE_MemoLength: TLabeledEdit
    Left = 8
    Top = 53
    Width = 161
    Height = 21
    EditLabel.Width = 68
    EditLabel.Height = 13
    EditLabel.Caption = 'Length:(Bytes)'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 4
  end
  object BtnDDRSave: TButton
    Left = 264
    Top = 90
    Width = 73
    Height = 25
    Caption = 'Save'
    TabOrder = 5
    OnClick = BtnDDRSaveClick
  end
  object BtnDDRWrite: TButton
    Left = 176
    Top = 90
    Width = 73
    Height = 25
    Caption = 'Write'
    TabOrder = 6
    OnClick = BtnDDRWriteClick
  end
  object PB: TProgressBar
    Left = 0
    Top = 618
    Width = 576
    Height = 17
    Align = alBottom
    Min = 0
    Max = 100
    TabOrder = 8
  end
  object OpenDialog: TOpenDialog
    Left = 64
    Top = 48
  end
  object SaveDialog: TSaveDialog
    Left = 104
    Top = 48
  end
end
