inherited Form_LoadScript: TForm_LoadScript
  Left = 374
  Top = 113
  Width = 674
  Height = 528
  Caption = 'Script'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  object MemoScript: TMemo
    Left = 0
    Top = 0
    Width = 665
    Height = 433
    TabOrder = 0
  end
  object Button1: TButton
    Left = 32
    Top = 456
    Width = 75
    Height = 25
    Caption = 'Load'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 320
    Top = 456
    Width = 75
    Height = 25
    Caption = 'Execute'
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 128
    Top = 456
    Width = 75
    Height = 25
    Caption = 'Save'
    TabOrder = 3
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 224
    Top = 456
    Width = 75
    Height = 25
    Caption = 'Clear'
    TabOrder = 4
    OnClick = Button4Click
  end
  object OpenScript: TOpenDialog
    Filter = 'TXT|*.txt|ALL|*.*'
    Left = 512
    Top = 32
  end
  object SaveScript: TSaveDialog
    DefaultExt = 'txt'
    Left = 544
    Top = 32
  end
end
