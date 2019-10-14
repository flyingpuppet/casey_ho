inherited Form_Range_test: TForm_Range_test
  Left = 284
  Top = 118
  Width = 931
  Height = 588
  Caption = 'Range Test'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 385
    Height = 161
    Caption = 'Condition'
    TabOrder = 0
    object Label1: TLabel
      Left = 128
      Top = 48
      Width = 73
      Height = 13
      AutoSize = False
      Caption = 'H Speed'
    end
    object Label2: TLabel
      Left = 128
      Top = 72
      Width = 73
      Height = 13
      AutoSize = False
      Caption = 'V Speed'
    end
    object Label6: TLabel
      Left = 128
      Top = 104
      Width = 73
      Height = 13
      AutoSize = False
      Caption = 'ME Phase'
    end
    object Label7: TLabel
      Left = 128
      Top = 128
      Width = 73
      Height = 13
      AutoSize = False
      Caption = 'MC Phase'
    end
    object RegCheckBox1: TRegCheckBox
      Left = 24
      Top = 24
      Width = 97
      Height = 17
      Caption = 'Variation on/off'
      TabOrder = 0
      RegAddress = '0xE000053B'
      RegBit = 4
    end
    object RegCheckBox2: TRegCheckBox
      Left = 24
      Top = 40
      Width = 97
      Height = 17
      Caption = 'Logo1 on/off'
      TabOrder = 1
      RegAddress = '0xE000052A'
      RegBit = 3
    end
    object RegCheckBox3: TRegCheckBox
      Left = 24
      Top = 56
      Width = 97
      Height = 17
      Caption = 'Logo2 on/off'
      TabOrder = 2
      RegAddress = '0xE000052A'
      RegBit = 2
    end
    object RegCheckBox4: TRegCheckBox
      Left = 24
      Top = 72
      Width = 97
      Height = 17
      Caption = 'var_off_en'
      TabOrder = 3
      RegAddress = '0xE0000234'
    end
    object RegCheckBox5: TRegCheckBox
      Left = 24
      Top = 88
      Width = 97
      Height = 17
      Caption = 'clear v buffer en'
      TabOrder = 4
      RegAddress = '0xE0000A79'
      RegBit = 7
    end
    object RegCheckBox6: TRegCheckBox
      Left = 128
      Top = 24
      Width = 73
      Height = 17
      Caption = 'IP Pattern'
      TabOrder = 5
      RegAddress = '0xE000013C'
      RegBit = 4
    end
    object RegScrollBar1: TRegScrollBar
      Left = 208
      Top = 24
      Width = 121
      Height = 17
      Max = 7
      PageSize = 0
      TabOrder = 6
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE000013C'
      RegBits = 3
    end
    object RegScrollBar2: TRegScrollBar
      Left = 208
      Top = 48
      Width = 121
      Height = 17
      Max = 255
      PageSize = 0
      TabOrder = 7
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE000014A'
      RegBits = 8
    end
    object RegScrollBar3: TRegScrollBar
      Left = 208
      Top = 72
      Width = 121
      Height = 17
      Max = 255
      PageSize = 0
      TabOrder = 8
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE000014B'
      RegBits = 8
    end
    object RegEdit1: TRegEdit
      Left = 336
      Top = 22
      Width = 33
      Height = 21
      TabOrder = 9
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE000013C'
      RegBits = 3
      TextType = ttInt
    end
    object RegEdit2: TRegEdit
      Left = 336
      Top = 46
      Width = 33
      Height = 21
      TabOrder = 10
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE000014A'
      RegBits = 8
      TextType = ttInt
    end
    object RegEdit3: TRegEdit
      Left = 336
      Top = 70
      Width = 33
      Height = 21
      TabOrder = 11
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE000014B'
      RegBits = 8
      TextType = ttInt
    end
    object RegCheckBox16: TRegCheckBox
      Left = 24
      Top = 104
      Width = 97
      Height = 17
      Caption = 'Pahse Enable'
      TabOrder = 12
      RegAddress = '0xE000030A'
      RegBit = 7
    end
    object RegScrollBar7: TRegScrollBar
      Left = 208
      Top = 104
      Width = 121
      Height = 17
      Max = 255
      PageSize = 0
      TabOrder = 13
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE000030A'
      RegBits = 7
    end
    object RegEdit7: TRegEdit
      Left = 336
      Top = 102
      Width = 33
      Height = 21
      TabOrder = 14
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE000030A'
      RegBits = 7
      TextType = ttInt
    end
    object RegScrollBar8: TRegScrollBar
      Left = 208
      Top = 128
      Width = 121
      Height = 17
      Max = 255
      PageSize = 0
      TabOrder = 15
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE000030B'
      RegBits = 7
    end
    object RegEdit8: TRegEdit
      Left = 336
      Top = 126
      Width = 33
      Height = 21
      TabOrder = 16
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE000030B'
      RegBits = 7
      TextType = ttInt
    end
  end
  object GroupBox2: TGroupBox
    Left = 0
    Top = 168
    Width = 385
    Height = 233
    Caption = 'MC Range'
    TabOrder = 1
    object Label3: TLabel
      Left = 24
      Top = 16
      Width = 65
      Height = 13
      AutoSize = False
      Caption = 'Debug Sel'
    end
    object Label4: TLabel
      Left = 24
      Top = 176
      Width = 57
      Height = 13
      AutoSize = False
      Caption = 'force mvx'
    end
    object Label5: TLabel
      Left = 24
      Top = 200
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'force mvy'
    end
    object RegCheckBox7: TRegCheckBox
      Left = 32
      Top = 112
      Width = 97
      Height = 17
      Caption = 'single pts y'
      TabOrder = 0
      RegAddress = '0xE000022C'
      RegBit = 6
    end
    object RegCheckBox8: TRegCheckBox
      Left = 224
      Top = 112
      Width = 97
      Height = 17
      Caption = 'singal pts c'
      TabOrder = 1
      RegAddress = '0xE000022C'
      RegBit = 7
    end
    object RegCheckBox9: TRegCheckBox
      Left = 32
      Top = 128
      Width = 97
      Height = 17
      Caption = 'show pts y i'
      TabOrder = 2
      RegAddress = '0xE0000239'
    end
    object RegCheckBox10: TRegCheckBox
      Left = 32
      Top = 144
      Width = 97
      Height = 17
      Caption = 'show pts y p'
      TabOrder = 3
      RegAddress = '0xE0000239'
      RegBit = 1
    end
    object RegCheckBox11: TRegCheckBox
      Left = 224
      Top = 128
      Width = 97
      Height = 17
      Caption = 'show pts c i'
      TabOrder = 4
      RegAddress = '0xE000023A'
      RegBit = 2
    end
    object RegCheckBox12: TRegCheckBox
      Left = 224
      Top = 144
      Width = 97
      Height = 17
      Caption = 'show pts c p'
      TabOrder = 5
      RegAddress = '0xE000023A'
      RegBit = 3
    end
    object RegScrollBar4: TRegScrollBar
      Left = 96
      Top = 16
      Width = 185
      Height = 17
      Max = 15
      PageSize = 0
      TabOrder = 6
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE0000236'
      RegBits = 4
      RegStart = 4
    end
    object RegEdit4: TRegEdit
      Left = 288
      Top = 14
      Width = 41
      Height = 21
      TabOrder = 7
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE0000236'
      RegBits = 4
      RegStart = 4
      TextType = ttInt
    end
    object RegScrollBar5: TRegScrollBar
      Tag = 1
      Left = 112
      Top = 176
      Width = 169
      Height = 17
      Max = 1023
      PageSize = 0
      TabOrder = 8
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE000029C'
      RegBits = 10
    end
    object RegEdit5: TRegEdit
      Tag = 1
      Left = 288
      Top = 174
      Width = 41
      Height = 21
      TabOrder = 9
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE000029C'
      RegBits = 10
      TextType = ttInt
    end
    object RegScrollBar6: TRegScrollBar
      Tag = 2
      Left = 112
      Top = 200
      Width = 169
      Height = 17
      Max = 511
      PageSize = 0
      TabOrder = 10
      OnScroll = RegScrollBar1Scroll
      RegStartAddress = '0xE000029E'
      RegBits = 9
    end
    object RegEdit6: TRegEdit
      Tag = 2
      Left = 288
      Top = 198
      Width = 41
      Height = 21
      TabOrder = 11
      OnExit = RegEdit1Exit
      OnKeyPress = RegEdit1KeyPress
      RegStartAddress = '0xE000029E'
      RegBits = 9
      TextType = ttInt
    end
    object RegCheckBox13: TRegCheckBox
      Left = 32
      Top = 88
      Width = 97
      Height = 17
      Caption = 'enable force mv'
      TabOrder = 12
      RegAddress = '0xE000029F'
      RegBit = 7
    end
    object RegCheckBox14: TRegCheckBox
      Left = 80
      Top = 176
      Width = 25
      Height = 17
      Caption = '-'
      TabOrder = 13
      RegAddress = '0xE000029D'
      RegBit = 2
    end
    object RegCheckBox15: TRegCheckBox
      Left = 80
      Top = 200
      Width = 25
      Height = 17
      Caption = '-'
      TabOrder = 14
      RegAddress = '0xE000029F'
      RegBit = 1
    end
    object Edit1: TEdit
      Left = 336
      Top = 174
      Width = 42
      Height = 21
      ReadOnly = True
      TabOrder = 15
    end
    object Edit2: TEdit
      Left = 335
      Top = 198
      Width = 42
      Height = 21
      ReadOnly = True
      TabOrder = 16
    end
    object RegRadioButton1: TRegRadioButton
      Left = 24
      Top = 40
      Width = 113
      Height = 17
      Caption = 'chroma mode up'
      TabOrder = 17
      RegAddress = '0xE0000309'
      RegValue = '0x00003000'
      RegMask = '0x00003000'
    end
    object RegRadioButton2: TRegRadioButton
      Left = 24
      Top = 56
      Width = 113
      Height = 17
      Caption = 'chroma mode down'
      TabOrder = 18
      RegAddress = '0xE0000309'
      RegValue = '0x00002000'
      RegMask = '0x00003000'
    end
    object RegRadioButton3: TRegRadioButton
      Left = 144
      Top = 40
      Width = 113
      Height = 17
      Caption = 'chroma mode normal'
      TabOrder = 19
      RegAddress = '0xE0000309'
      RegValue = '0x00000000'
      RegMask = '0x00003000'
    end
    object RegCheckBox17: TRegCheckBox
      Left = 32
      Top = 72
      Width = 97
      Height = 17
      Caption = 'MC(02):FE[1]'
      TabOrder = 20
      RegAddress = '0xE00002FE'
      RegBit = 1
    end
  end
  object Button1: TButton
    Left = 24
    Top = 408
    Width = 75
    Height = 25
    Caption = 'refresh'
    TabOrder = 2
    OnClick = Button1Click
  end
end
