inherited Form_ME_1: TForm_ME_1
  Left = 241
  Top = 98
  Width = 646
  Height = 628
  Caption = 'ME_1'
  OldCreateOrder = True
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object mv_Page: TPageControl
    Left = 0
    Top = 0
    Width = 638
    Height = 465
    ActivePage = TabSheet2
    Align = alTop
    TabIndex = 1
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'ip'
      object GroupBox1: TGroupBox
        Left = 0
        Top = 8
        Width = 209
        Height = 425
        Caption = 'penalty value'
        TabOrder = 0
        object Label1: TLabel
          Left = 112
          Top = 16
          Width = 41
          Height = 13
          AutoSize = False
          Caption = 'Value'
        end
        object Label2: TLabel
          Left = 160
          Top = 16
          Width = 41
          Height = 13
          AutoSize = False
          Caption = 'Factor'
        end
        object RegLabeledEdit1: TRegLabeledEdit
          Left = 88
          Top = 32
          Width = 69
          Height = 21
          BiDiMode = bdLeftToRight
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.BiDiMode = bdLeftToRight
          EditLabel.Caption = 'penalty_gmv:    '
          EditLabel.ParentBiDiMode = False
          LabelPosition = lpLeft
          LabelSpacing = 3
          ParentBiDiMode = False
          TabOrder = 0
          RegStartAddress = '0xE0000808'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit2: TRegLabeledEdit
          Left = 88
          Top = 56
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 0:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 1
          RegStartAddress = '0xE0000809'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit3: TRegLabeledEdit
          Left = 88
          Top = 80
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 1:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 2
          RegStartAddress = '0xE000080A'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit4: TRegLabeledEdit
          Left = 88
          Top = 104
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 2:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 3
          RegStartAddress = '0xE000080B'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit5: TRegLabeledEdit
          Left = 88
          Top = 128
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 3:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 4
          RegStartAddress = '0xE000080C'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit6: TRegLabeledEdit
          Left = 88
          Top = 152
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 4:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 5
          RegStartAddress = '0xE000080D'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit7: TRegLabeledEdit
          Left = 88
          Top = 176
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 5:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 6
          RegStartAddress = '0xE000080E'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit8: TRegLabeledEdit
          Left = 88
          Top = 200
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 6:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 7
          RegStartAddress = '0xE000080F'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit9: TRegLabeledEdit
          Left = 88
          Top = 224
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 7:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 8
          RegStartAddress = '0xE0000810'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit10: TRegLabeledEdit
          Left = 88
          Top = 248
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 8:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 9
          RegStartAddress = '0xE0000811'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit11: TRegLabeledEdit
          Left = 88
          Top = 272
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 9:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 10
          RegStartAddress = '0xE0000812'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit12: TRegLabeledEdit
          Left = 88
          Top = 296
          Width = 69
          Height = 21
          EditLabel.Width = 76
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_upd 0:  '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 11
          RegStartAddress = '0xE0000813'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit13: TRegLabeledEdit
          Left = 88
          Top = 320
          Width = 69
          Height = 21
          EditLabel.Width = 76
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_upd 1:  '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 12
          RegStartAddress = '0xE0000814'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit14: TRegLabeledEdit
          Left = 88
          Top = 344
          Width = 69
          Height = 21
          EditLabel.Width = 76
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_upd 2:  '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 13
          RegStartAddress = '0xE0000815'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit15: TRegLabeledEdit
          Left = 88
          Top = 368
          Width = 69
          Height = 21
          EditLabel.Width = 76
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_upd 3:  '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 14
          RegStartAddress = '0xE0000816'
          RegBits = 6
          TextType = ttInt
        end
        object RegEdit1: TRegEdit
          Left = 160
          Top = 32
          Width = 36
          Height = 21
          TabOrder = 15
          RegStartAddress = '0xE0000808'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit2: TRegEdit
          Left = 160
          Top = 56
          Width = 36
          Height = 21
          TabOrder = 16
          RegStartAddress = '0xE0000809'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit3: TRegEdit
          Left = 160
          Top = 80
          Width = 36
          Height = 21
          TabOrder = 17
          RegStartAddress = '0xE000080A'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit4: TRegEdit
          Left = 160
          Top = 104
          Width = 36
          Height = 21
          TabOrder = 18
          RegStartAddress = '0xE000080B'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit5: TRegEdit
          Left = 160
          Top = 128
          Width = 36
          Height = 21
          TabOrder = 19
          RegStartAddress = '0xE000080C'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit6: TRegEdit
          Left = 160
          Top = 152
          Width = 36
          Height = 21
          TabOrder = 20
          RegStartAddress = '0xE000080D'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit7: TRegEdit
          Left = 160
          Top = 176
          Width = 36
          Height = 21
          TabOrder = 21
          RegStartAddress = '0xE000080E'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit8: TRegEdit
          Left = 160
          Top = 200
          Width = 36
          Height = 21
          TabOrder = 22
          RegStartAddress = '0xE000080F'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit9: TRegEdit
          Left = 160
          Top = 224
          Width = 36
          Height = 21
          TabOrder = 23
          RegStartAddress = '0xE0000810'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit10: TRegEdit
          Left = 160
          Top = 248
          Width = 36
          Height = 21
          TabOrder = 24
          RegStartAddress = '0xE0000811'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit11: TRegEdit
          Left = 160
          Top = 272
          Width = 36
          Height = 21
          TabOrder = 25
          RegStartAddress = '0xE0000812'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit12: TRegEdit
          Left = 160
          Top = 296
          Width = 36
          Height = 21
          TabOrder = 26
          RegStartAddress = '0xE0000813'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit13: TRegEdit
          Left = 160
          Top = 320
          Width = 36
          Height = 21
          TabOrder = 27
          RegStartAddress = '0xE0000814'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit14: TRegEdit
          Left = 160
          Top = 344
          Width = 36
          Height = 21
          TabOrder = 28
          RegStartAddress = '0xE0000815'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit15: TRegEdit
          Left = 160
          Top = 368
          Width = 36
          Height = 21
          TabOrder = 29
          RegStartAddress = '0xE0000816'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegLabeledEdit16: TRegLabeledEdit
          Left = 88
          Top = 392
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty z:          '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 30
          RegStartAddress = '0xE0000804'
          RegBits = 6
          TextType = ttInt
        end
        object RegEdit42: TRegEdit
          Left = 160
          Top = 392
          Width = 36
          Height = 21
          TabOrder = 31
          RegStartAddress = '0xE0000804'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
      end
      object GroupBox2: TGroupBox
        Left = 216
        Top = 8
        Width = 401
        Height = 425
        Caption = 'Pos'
        TabOrder = 1
        object Label3: TLabel
          Left = 112
          Top = 40
          Width = 33
          Height = 13
          Alignment = taCenter
          AutoSize = False
          Caption = 'X'
        end
        object Label4: TLabel
          Left = 160
          Top = 40
          Width = 32
          Height = 13
          Alignment = taCenter
          AutoSize = False
          Caption = 'Y'
        end
        object Label5: TLabel
          Left = 208
          Top = 40
          Width = 32
          Height = 13
          Alignment = taCenter
          AutoSize = False
          Caption = 'X1'
        end
        object Label6: TLabel
          Left = 256
          Top = 40
          Width = 32
          Height = 13
          Alignment = taCenter
          AutoSize = False
          Caption = 'Y1'
        end
        object Label7: TLabel
          Left = 304
          Top = 40
          Width = 32
          Height = 13
          Alignment = taCenter
          AutoSize = False
          Caption = 'X2'
        end
        object Label8: TLabel
          Left = 352
          Top = 40
          Width = 32
          Height = 13
          Alignment = taCenter
          AutoSize = False
          Caption = 'Y2'
        end
        object RegCheckBox1: TRegCheckBox
          Left = 8
          Top = 32
          Width = 97
          Height = 17
          Caption = 'Enable_gmv'
          TabOrder = 0
          RegAddress = '0xE000081C'
          RegBit = 7
        end
        object RegCheckBox2: TRegCheckBox
          Left = 8
          Top = 56
          Width = 89
          Height = 17
          Caption = 'Enable_upd 0'
          TabOrder = 1
          RegAddress = '0xE000081D'
          RegBit = 4
        end
        object RegCheckBox3: TRegCheckBox
          Left = 8
          Top = 80
          Width = 89
          Height = 17
          Caption = 'Enable_upd 1'
          TabOrder = 2
          RegAddress = '0xE000081D'
          RegBit = 3
        end
        object RegCheckBox4: TRegCheckBox
          Left = 8
          Top = 104
          Width = 89
          Height = 17
          Caption = 'Enable_upd 2'
          TabOrder = 3
          RegAddress = '0xE000081D'
          RegBit = 2
        end
        object RegCheckBox5: TRegCheckBox
          Left = 8
          Top = 128
          Width = 89
          Height = 17
          Caption = 'Enable_upd 3'
          TabOrder = 4
          RegAddress = '0xE000081D'
          RegBit = 1
        end
        object RegEdit16: TRegEdit
          Left = 104
          Top = 56
          Width = 45
          Height = 21
          TabOrder = 5
          RegStartAddress = '0xE0000838'
          RegBits = 3
          RegStart = 3
        end
        object RegEdit17: TRegEdit
          Left = 152
          Top = 56
          Width = 45
          Height = 21
          TabOrder = 6
          RegStartAddress = '0xE000083A'
          RegBits = 3
          RegStart = 3
        end
        object RegEdit18: TRegEdit
          Left = 200
          Top = 56
          Width = 45
          Height = 21
          TabOrder = 7
          RegStartAddress = '0xE000083C'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit19: TRegEdit
          Left = 344
          Top = 56
          Width = 45
          Height = 21
          TabOrder = 8
          RegStartAddress = '0xE0000842'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit20: TRegEdit
          Left = 296
          Top = 56
          Width = 45
          Height = 21
          TabOrder = 9
          RegStartAddress = '0xE0000840'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit21: TRegEdit
          Left = 248
          Top = 56
          Width = 45
          Height = 21
          TabOrder = 10
          RegStartAddress = '0xE000083E'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit22: TRegEdit
          Left = 104
          Top = 80
          Width = 45
          Height = 21
          TabOrder = 11
          RegStartAddress = '0xE0000838'
          RegBits = 3
        end
        object RegEdit23: TRegEdit
          Left = 152
          Top = 80
          Width = 45
          Height = 21
          TabOrder = 12
          RegStartAddress = '0xE000083A'
          RegBits = 3
        end
        object RegEdit24: TRegEdit
          Left = 200
          Top = 80
          Width = 45
          Height = 21
          TabOrder = 13
          RegStartAddress = '0xE000083C'
          RegBits = 4
        end
        object RegEdit25: TRegEdit
          Left = 344
          Top = 80
          Width = 45
          Height = 21
          TabOrder = 14
          RegStartAddress = '0xE0000842'
          RegBits = 4
        end
        object RegEdit26: TRegEdit
          Left = 296
          Top = 80
          Width = 45
          Height = 21
          TabOrder = 15
          RegStartAddress = '0xE0000840'
          RegBits = 4
        end
        object RegEdit27: TRegEdit
          Left = 248
          Top = 80
          Width = 45
          Height = 21
          TabOrder = 16
          RegStartAddress = '0xE000083E'
          RegBits = 4
        end
        object RegEdit28: TRegEdit
          Left = 104
          Top = 104
          Width = 45
          Height = 21
          TabOrder = 17
          RegStartAddress = '0xE0000839'
          RegBits = 3
          RegStart = 3
        end
        object RegEdit29: TRegEdit
          Left = 152
          Top = 104
          Width = 45
          Height = 21
          TabOrder = 18
          RegStartAddress = '0xE000083B'
          RegBits = 3
          RegStart = 3
        end
        object RegEdit30: TRegEdit
          Left = 200
          Top = 104
          Width = 45
          Height = 21
          TabOrder = 19
          RegStartAddress = '0xE000083D'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit31: TRegEdit
          Left = 344
          Top = 104
          Width = 45
          Height = 21
          TabOrder = 20
          RegStartAddress = '0xE0000843'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit32: TRegEdit
          Left = 296
          Top = 104
          Width = 45
          Height = 21
          TabOrder = 21
          RegStartAddress = '0xE0000841'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit33: TRegEdit
          Left = 248
          Top = 104
          Width = 45
          Height = 21
          TabOrder = 22
          RegStartAddress = '0xE000083F'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit34: TRegEdit
          Left = 104
          Top = 128
          Width = 45
          Height = 21
          TabOrder = 23
          RegStartAddress = '0xE0000839'
          RegBits = 3
        end
        object RegEdit35: TRegEdit
          Left = 152
          Top = 128
          Width = 45
          Height = 21
          TabOrder = 24
          RegStartAddress = '0xE000083B'
          RegBits = 3
        end
        object RegEdit36: TRegEdit
          Left = 200
          Top = 128
          Width = 45
          Height = 21
          TabOrder = 25
          RegStartAddress = '0xE000083D'
          RegBits = 4
        end
        object RegEdit37: TRegEdit
          Left = 344
          Top = 128
          Width = 45
          Height = 21
          TabOrder = 26
          RegStartAddress = '0xE0000843'
          RegBits = 4
        end
        object RegEdit38: TRegEdit
          Left = 296
          Top = 128
          Width = 45
          Height = 21
          TabOrder = 27
          RegStartAddress = '0xE0000841'
          RegBits = 4
        end
        object RegEdit39: TRegEdit
          Left = 248
          Top = 128
          Width = 45
          Height = 21
          TabOrder = 28
          RegStartAddress = '0xE000083F'
          RegBits = 4
        end
        object cb_ip_Enmv0: TRegCheckBox
          Left = 8
          Top = 152
          Width = 89
          Height = 17
          Caption = 'Enable_mv 0'
          TabOrder = 29
          RegAddress = '0xE000081C'
          RegBit = 6
        end
        object cb_ip_Enmv1: TRegCheckBox
          Left = 8
          Top = 176
          Width = 89
          Height = 17
          Caption = 'Enable_mv 1'
          TabOrder = 30
          RegAddress = '0xE000081C'
          RegBit = 5
        end
        object cb_ip_Enmv2: TRegCheckBox
          Left = 8
          Top = 200
          Width = 89
          Height = 17
          Caption = 'Enable_mv 2'
          TabOrder = 31
          RegAddress = '0xE000081C'
          RegBit = 4
        end
        object cb_ip_Enmv3: TRegCheckBox
          Left = 8
          Top = 224
          Width = 89
          Height = 17
          Caption = 'Enable_mv 3'
          TabOrder = 32
          RegAddress = '0xE000081C'
          RegBit = 3
        end
        object ed_ip_mv_x0: TRegEdit
          Left = 104
          Top = 152
          Width = 45
          Height = 21
          TabOrder = 33
          RegStartAddress = '0xE0000824'
          RegBits = 3
          RegStart = 3
        end
        object ed_ip_mv_y0: TRegEdit
          Left = 152
          Top = 152
          Width = 45
          Height = 21
          TabOrder = 34
          RegStartAddress = '0xE000082C'
          RegBits = 3
          RegStart = 3
        end
        object ed_ip_mv_x1: TRegEdit
          Left = 104
          Top = 176
          Width = 45
          Height = 21
          TabOrder = 35
          RegStartAddress = '0xE0000824'
          RegBits = 3
        end
        object ed_ip_mv_y1: TRegEdit
          Left = 152
          Top = 176
          Width = 45
          Height = 21
          TabOrder = 36
          RegStartAddress = '0xE000082C'
          RegBits = 3
        end
        object ed_ip_mv_x2: TRegEdit
          Left = 104
          Top = 200
          Width = 45
          Height = 21
          TabOrder = 37
          RegStartAddress = '0xE0000825'
          RegBits = 3
          RegStart = 3
        end
        object ed_ip_mv_y2: TRegEdit
          Left = 152
          Top = 200
          Width = 45
          Height = 21
          TabOrder = 38
          RegStartAddress = '0xE000082D'
          RegBits = 3
          RegStart = 3
        end
        object ed_ip_mv_x3: TRegEdit
          Left = 104
          Top = 224
          Width = 45
          Height = 21
          TabOrder = 39
          RegStartAddress = '0xE0000825'
          RegBits = 3
        end
        object ed_ip_mv_y3: TRegEdit
          Left = 152
          Top = 224
          Width = 45
          Height = 21
          TabOrder = 40
          RegStartAddress = '0xE000082D'
          RegBits = 3
        end
        object cb_ip_Enmv4: TRegCheckBox
          Left = 8
          Top = 248
          Width = 89
          Height = 17
          Caption = 'Enable_mv 4'
          TabOrder = 41
          RegAddress = '0xE000081C'
          RegBit = 2
        end
        object cb_ip_Enmv5: TRegCheckBox
          Left = 8
          Top = 272
          Width = 89
          Height = 17
          Caption = 'Enable_mv 5'
          TabOrder = 42
          RegAddress = '0xE000081C'
          RegBit = 1
        end
        object cb_ip_Enmv6: TRegCheckBox
          Left = 8
          Top = 296
          Width = 89
          Height = 17
          Caption = 'Enable_mv 6'
          TabOrder = 43
          RegAddress = '0xE000081C'
        end
        object cb_ip_Enmv7: TRegCheckBox
          Left = 8
          Top = 320
          Width = 89
          Height = 17
          Caption = 'Enable_mv 7'
          TabOrder = 44
          RegAddress = '0xE000081D'
          RegBit = 7
        end
        object ed_ip_mv_x4: TRegEdit
          Left = 104
          Top = 248
          Width = 45
          Height = 21
          TabOrder = 45
          RegStartAddress = '0xE0000826'
          RegBits = 3
          RegStart = 3
        end
        object ed_ip_mv_y4: TRegEdit
          Left = 152
          Top = 248
          Width = 45
          Height = 21
          TabOrder = 46
          RegStartAddress = '0xE000082E'
          RegBits = 3
          RegStart = 3
        end
        object ed_ip_mv_x5: TRegEdit
          Left = 104
          Top = 272
          Width = 45
          Height = 21
          TabOrder = 47
          RegStartAddress = '0xE0000826'
          RegBits = 3
        end
        object ed_ip_mv_y5: TRegEdit
          Left = 152
          Top = 272
          Width = 45
          Height = 21
          TabOrder = 48
          RegStartAddress = '0xE000082E'
          RegBits = 3
        end
        object ed_ip_mv_x6: TRegEdit
          Left = 104
          Top = 296
          Width = 45
          Height = 21
          TabOrder = 49
          RegStartAddress = '0xE0000827'
          RegBits = 3
          RegStart = 3
        end
        object ed_ip_mv_y6: TRegEdit
          Left = 152
          Top = 296
          Width = 45
          Height = 21
          TabOrder = 50
          RegStartAddress = '0xE000082F'
          RegBits = 3
          RegStart = 3
        end
        object ed_ip_mv_x7: TRegEdit
          Left = 104
          Top = 320
          Width = 45
          Height = 21
          TabOrder = 51
          RegStartAddress = '0xE0000827'
          RegBits = 3
        end
        object ed_ip_mv_y7: TRegEdit
          Left = 152
          Top = 320
          Width = 45
          Height = 21
          TabOrder = 52
          RegStartAddress = '0xE000082F'
          RegBits = 3
        end
        object cb_ip_Enmv8: TRegCheckBox
          Left = 8
          Top = 344
          Width = 89
          Height = 17
          Caption = 'Enable_mv 8'
          TabOrder = 53
          RegAddress = '0xE000081D'
          RegBit = 6
        end
        object cb_ip_Enmv9: TRegCheckBox
          Left = 8
          Top = 368
          Width = 89
          Height = 17
          Caption = 'Enable_mv 9'
          TabOrder = 54
          RegAddress = '0xE000081D'
          RegBit = 5
        end
        object ed_ip_mv_x8: TRegEdit
          Left = 104
          Top = 344
          Width = 45
          Height = 21
          TabOrder = 55
          RegStartAddress = '0xE0000828'
          RegBits = 3
          RegStart = 3
        end
        object ed_ip_mv_y8: TRegEdit
          Left = 152
          Top = 344
          Width = 45
          Height = 21
          TabOrder = 56
          RegStartAddress = '0xE0000830'
          RegBits = 3
          RegStart = 3
        end
        object ed_ip_mv_x9: TRegEdit
          Left = 104
          Top = 368
          Width = 45
          Height = 21
          TabOrder = 57
          RegStartAddress = '0xE0000828'
          RegBits = 3
        end
        object ed_ip_mv_y9: TRegEdit
          Left = 152
          Top = 368
          Width = 45
          Height = 21
          TabOrder = 58
          RegStartAddress = '0xE0000830'
          RegBits = 3
        end
        object ScanGroup: TGroupBox
          Left = 232
          Top = 184
          Width = 137
          Height = 137
          Caption = 'Matrix'
          TabOrder = 59
          object Label9: TLabel
            Left = 32
            Top = 24
            Width = 9
            Height = 13
            Caption = '-2'
          end
          object Label10: TLabel
            Left = 48
            Top = 24
            Width = 9
            Height = 13
            Caption = '-1'
          end
          object Label11: TLabel
            Left = 64
            Top = 24
            Width = 6
            Height = 13
            Caption = '0'
          end
          object Label12: TLabel
            Left = 80
            Top = 24
            Width = 6
            Height = 13
            Caption = '1'
          end
          object Label13: TLabel
            Left = 96
            Top = 24
            Width = 6
            Height = 13
            Caption = '2'
          end
          object Label14: TLabel
            Left = 16
            Top = 40
            Width = 9
            Height = 13
            Caption = '-2'
          end
          object Label15: TLabel
            Left = 16
            Top = 56
            Width = 9
            Height = 13
            Caption = '-1'
          end
          object Label16: TLabel
            Left = 16
            Top = 72
            Width = 6
            Height = 13
            Caption = '0'
          end
          object Label17: TLabel
            Left = 16
            Top = 88
            Width = 6
            Height = 13
            Caption = '1'
          end
          object Label18: TLabel
            Left = 16
            Top = 104
            Width = 6
            Height = 13
            Caption = '2'
          end
          object cb_ip_ma1: TCheckBox
            Left = 32
            Top = 40
            Width = 17
            Height = 17
            TabOrder = 0
            OnClick = cb_ip_ma1Click
          end
          object cb_ip_ma2: TCheckBox
            Tag = 1
            Left = 48
            Top = 40
            Width = 17
            Height = 17
            TabOrder = 1
            OnClick = cb_ip_ma1Click
          end
          object cb_ip_ma3: TCheckBox
            Tag = 2
            Left = 64
            Top = 40
            Width = 17
            Height = 17
            TabOrder = 2
            OnClick = cb_ip_ma1Click
          end
          object cb_ip_ma4: TCheckBox
            Tag = 3
            Left = 80
            Top = 40
            Width = 17
            Height = 17
            TabOrder = 3
            OnClick = cb_ip_ma1Click
          end
          object cb_ip_ma5: TCheckBox
            Tag = 4
            Left = 96
            Top = 40
            Width = 17
            Height = 17
            TabOrder = 4
            OnClick = cb_ip_ma1Click
          end
          object cb_ip_ma6: TCheckBox
            Tag = 5
            Left = 32
            Top = 56
            Width = 17
            Height = 17
            TabOrder = 5
            OnClick = cb_ip_ma1Click
          end
          object cb_ip_ma7: TCheckBox
            Tag = 6
            Left = 48
            Top = 56
            Width = 17
            Height = 17
            TabOrder = 6
            OnClick = cb_ip_ma1Click
          end
          object cb_ip_ma8: TCheckBox
            Tag = 7
            Left = 64
            Top = 56
            Width = 17
            Height = 17
            TabOrder = 7
            OnClick = cb_ip_ma1Click
          end
          object cb_ip_ma9: TCheckBox
            Tag = 8
            Left = 80
            Top = 56
            Width = 17
            Height = 17
            TabOrder = 8
            OnClick = cb_ip_ma1Click
          end
          object cb_ip_ma10: TCheckBox
            Tag = 9
            Left = 96
            Top = 56
            Width = 17
            Height = 17
            TabOrder = 9
            OnClick = cb_ip_ma1Click
          end
          object cb_ip_ma11: TCheckBox
            Tag = 10
            Left = 32
            Top = 72
            Width = 17
            Height = 17
            TabOrder = 10
            OnClick = cb_ip_ma1Click
          end
          object cb_ip_ma12: TCheckBox
            Tag = 11
            Left = 48
            Top = 72
            Width = 17
            Height = 17
            TabOrder = 11
            OnClick = cb_ip_ma1Click
          end
          object cb_ip_ma13: TCheckBox
            Tag = 12
            Left = 64
            Top = 72
            Width = 17
            Height = 17
            TabOrder = 12
            OnClick = cb_ip_ma1Click
          end
          object cb_ip_ma14: TCheckBox
            Tag = 13
            Left = 80
            Top = 72
            Width = 17
            Height = 17
            TabOrder = 13
            OnClick = cb_ip_ma1Click
          end
          object cb_ip_ma15: TCheckBox
            Tag = 14
            Left = 96
            Top = 72
            Width = 17
            Height = 17
            TabOrder = 14
            OnClick = cb_ip_ma1Click
          end
          object cb_ip_ma16: TCheckBox
            Tag = 15
            Left = 32
            Top = 88
            Width = 17
            Height = 17
            TabOrder = 15
            OnClick = cb_ip_ma1Click
          end
          object cb_ip_ma17: TCheckBox
            Tag = 16
            Left = 48
            Top = 88
            Width = 17
            Height = 17
            TabOrder = 16
            OnClick = cb_ip_ma1Click
          end
          object cb_ip_ma18: TCheckBox
            Tag = 17
            Left = 64
            Top = 88
            Width = 17
            Height = 17
            TabOrder = 17
            OnClick = cb_ip_ma1Click
          end
          object cb_ip_ma19: TCheckBox
            Tag = 18
            Left = 80
            Top = 88
            Width = 17
            Height = 17
            TabOrder = 18
            OnClick = cb_ip_ma1Click
          end
          object cb_ip_ma20: TCheckBox
            Tag = 19
            Left = 96
            Top = 88
            Width = 17
            Height = 17
            TabOrder = 19
            OnClick = cb_ip_ma1Click
          end
          object cb_ip_ma21: TCheckBox
            Tag = 20
            Left = 32
            Top = 104
            Width = 17
            Height = 17
            TabOrder = 20
            OnClick = cb_ip_ma1Click
          end
          object cb_ip_ma22: TCheckBox
            Tag = 21
            Left = 48
            Top = 104
            Width = 17
            Height = 17
            TabOrder = 21
            OnClick = cb_ip_ma1Click
          end
          object cb_ip_ma23: TCheckBox
            Tag = 22
            Left = 64
            Top = 104
            Width = 17
            Height = 17
            TabOrder = 22
            OnClick = cb_ip_ma1Click
          end
          object cb_ip_ma24: TCheckBox
            Tag = 23
            Left = 80
            Top = 104
            Width = 17
            Height = 17
            TabOrder = 23
            OnClick = cb_ip_ma1Click
          end
          object cb_ip_ma25: TCheckBox
            Tag = 24
            Left = 96
            Top = 104
            Width = 17
            Height = 17
            TabOrder = 24
            OnClick = cb_ip_ma1Click
          end
        end
        object ScrollBar1: TScrollBar
          Left = 240
          Top = 368
          Width = 121
          Height = 17
          PageSize = 0
          TabOrder = 60
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'pi'
      ImageIndex = 1
      object GroupBox11: TGroupBox
        Left = 0
        Top = 8
        Width = 209
        Height = 425
        Caption = 'penalty value'
        TabOrder = 0
        object Label55: TLabel
          Left = 112
          Top = 16
          Width = 41
          Height = 13
          AutoSize = False
          Caption = 'Value'
        end
        object Label56: TLabel
          Left = 160
          Top = 16
          Width = 41
          Height = 13
          AutoSize = False
          Caption = 'Factor'
        end
        object RegLabeledEdit52: TRegLabeledEdit
          Left = 88
          Top = 32
          Width = 69
          Height = 21
          BiDiMode = bdLeftToRight
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.BiDiMode = bdLeftToRight
          EditLabel.Caption = 'penalty_gmv:    '
          EditLabel.ParentBiDiMode = False
          LabelPosition = lpLeft
          LabelSpacing = 3
          ParentBiDiMode = False
          TabOrder = 0
          RegStartAddress = '0xE0000848'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit53: TRegLabeledEdit
          Left = 88
          Top = 56
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 0:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 1
          RegStartAddress = '0xE0000849'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit54: TRegLabeledEdit
          Left = 88
          Top = 80
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 1:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 2
          RegStartAddress = '0xE000084A'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit55: TRegLabeledEdit
          Left = 88
          Top = 104
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 2:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 3
          RegStartAddress = '0xE000084B'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit56: TRegLabeledEdit
          Left = 88
          Top = 128
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 3:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 4
          RegStartAddress = '0xE000084C'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit57: TRegLabeledEdit
          Left = 88
          Top = 152
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 4:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 5
          RegStartAddress = '0xE000084D'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit58: TRegLabeledEdit
          Left = 88
          Top = 176
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 5:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 6
          RegStartAddress = '0xE000084E'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit59: TRegLabeledEdit
          Left = 88
          Top = 200
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 6:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 7
          RegStartAddress = '0xE000084F'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit60: TRegLabeledEdit
          Left = 88
          Top = 224
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 7:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 8
          RegStartAddress = '0xE0000850'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit61: TRegLabeledEdit
          Left = 88
          Top = 248
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 8:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 9
          RegStartAddress = '0xE0000851'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit62: TRegLabeledEdit
          Left = 88
          Top = 272
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 9:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 10
          RegStartAddress = '0xE0000852'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit63: TRegLabeledEdit
          Left = 88
          Top = 296
          Width = 69
          Height = 21
          EditLabel.Width = 76
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_upd 0:  '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 11
          RegStartAddress = '0xE0000853'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit64: TRegLabeledEdit
          Left = 88
          Top = 320
          Width = 69
          Height = 21
          EditLabel.Width = 76
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_upd 1:  '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 12
          RegStartAddress = '0xE0000854'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit65: TRegLabeledEdit
          Left = 88
          Top = 344
          Width = 69
          Height = 21
          EditLabel.Width = 76
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_upd 2:  '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 13
          RegStartAddress = '0xE0000855'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit66: TRegLabeledEdit
          Left = 88
          Top = 368
          Width = 69
          Height = 21
          EditLabel.Width = 76
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_upd 3:  '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 14
          RegStartAddress = '0xE0000856'
          RegBits = 6
          TextType = ttInt
        end
        object RegEdit181: TRegEdit
          Left = 160
          Top = 32
          Width = 36
          Height = 21
          TabOrder = 15
          RegStartAddress = '0xE0000848'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit182: TRegEdit
          Left = 160
          Top = 56
          Width = 36
          Height = 21
          TabOrder = 16
          RegStartAddress = '0xE0000849'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit183: TRegEdit
          Left = 160
          Top = 80
          Width = 36
          Height = 21
          TabOrder = 17
          RegStartAddress = '0xE000084A'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit184: TRegEdit
          Left = 160
          Top = 104
          Width = 36
          Height = 21
          TabOrder = 18
          RegStartAddress = '0xE000084B'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit185: TRegEdit
          Left = 160
          Top = 128
          Width = 36
          Height = 21
          TabOrder = 19
          RegStartAddress = '0xE000084C'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit186: TRegEdit
          Left = 160
          Top = 152
          Width = 36
          Height = 21
          TabOrder = 20
          RegStartAddress = '0xE000084D'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit187: TRegEdit
          Left = 160
          Top = 176
          Width = 36
          Height = 21
          TabOrder = 21
          RegStartAddress = '0xE000084E'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit188: TRegEdit
          Left = 160
          Top = 200
          Width = 36
          Height = 21
          TabOrder = 22
          RegStartAddress = '0xE000084F'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit189: TRegEdit
          Left = 160
          Top = 224
          Width = 36
          Height = 21
          TabOrder = 23
          RegStartAddress = '0xE0000850'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit190: TRegEdit
          Left = 160
          Top = 248
          Width = 36
          Height = 21
          TabOrder = 24
          RegStartAddress = '0xE0000851'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit191: TRegEdit
          Left = 160
          Top = 272
          Width = 36
          Height = 21
          TabOrder = 25
          RegStartAddress = '0xE0000852'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit192: TRegEdit
          Left = 160
          Top = 296
          Width = 36
          Height = 21
          TabOrder = 26
          RegStartAddress = '0xE0000853'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit193: TRegEdit
          Left = 160
          Top = 320
          Width = 36
          Height = 21
          TabOrder = 27
          RegStartAddress = '0xE0000854'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit194: TRegEdit
          Left = 160
          Top = 344
          Width = 36
          Height = 21
          TabOrder = 28
          RegStartAddress = '0xE0000855'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit195: TRegEdit
          Left = 160
          Top = 368
          Width = 36
          Height = 21
          TabOrder = 29
          RegStartAddress = '0xE0000856'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
      end
      object GroupBox12: TGroupBox
        Left = 216
        Top = 8
        Width = 401
        Height = 425
        Caption = 'Pos'
        TabOrder = 1
        object Label57: TLabel
          Left = 112
          Top = 40
          Width = 33
          Height = 13
          Alignment = taCenter
          AutoSize = False
          Caption = 'X'
        end
        object Label58: TLabel
          Left = 160
          Top = 40
          Width = 32
          Height = 13
          Alignment = taCenter
          AutoSize = False
          Caption = 'Y'
        end
        object Label59: TLabel
          Left = 208
          Top = 40
          Width = 32
          Height = 13
          Alignment = taCenter
          AutoSize = False
          Caption = 'X1'
        end
        object Label60: TLabel
          Left = 256
          Top = 40
          Width = 32
          Height = 13
          Alignment = taCenter
          AutoSize = False
          Caption = 'Y1'
        end
        object Label61: TLabel
          Left = 304
          Top = 40
          Width = 32
          Height = 13
          Alignment = taCenter
          AutoSize = False
          Caption = 'X2'
        end
        object Label62: TLabel
          Left = 352
          Top = 40
          Width = 32
          Height = 13
          Alignment = taCenter
          AutoSize = False
          Caption = 'Y2'
        end
        object RegCheckBox49: TRegCheckBox
          Left = 8
          Top = 32
          Width = 97
          Height = 17
          Caption = 'Enable_gmv'
          TabOrder = 0
          RegAddress = '0xE000085C'
          RegBit = 7
        end
        object RegCheckBox50: TRegCheckBox
          Left = 8
          Top = 56
          Width = 89
          Height = 17
          Caption = 'Enable_upd 0'
          TabOrder = 1
          RegAddress = '0xE000085D'
          RegBit = 4
        end
        object RegCheckBox51: TRegCheckBox
          Left = 8
          Top = 80
          Width = 89
          Height = 17
          Caption = 'Enable_upd 1'
          TabOrder = 2
          RegAddress = '0xE000085D'
          RegBit = 3
        end
        object RegCheckBox52: TRegCheckBox
          Left = 8
          Top = 104
          Width = 89
          Height = 17
          Caption = 'Enable_upd 2'
          TabOrder = 3
          RegAddress = '0xE000085D'
          RegBit = 2
        end
        object RegCheckBox53: TRegCheckBox
          Left = 8
          Top = 128
          Width = 89
          Height = 17
          Caption = 'Enable_upd 3'
          TabOrder = 4
          RegAddress = '0xE000085D'
          RegBit = 1
        end
        object RegEdit197: TRegEdit
          Left = 104
          Top = 56
          Width = 45
          Height = 21
          TabOrder = 5
          RegStartAddress = '0xE0000878'
          RegBits = 3
          RegStart = 3
        end
        object RegEdit198: TRegEdit
          Left = 152
          Top = 56
          Width = 45
          Height = 21
          TabOrder = 6
          RegStartAddress = '0xE000087A'
          RegBits = 3
          RegStart = 3
        end
        object RegEdit199: TRegEdit
          Left = 200
          Top = 56
          Width = 45
          Height = 21
          TabOrder = 7
          RegStartAddress = '0xE000087C'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit200: TRegEdit
          Left = 344
          Top = 56
          Width = 45
          Height = 21
          TabOrder = 8
          RegStartAddress = '0xE0000882'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit201: TRegEdit
          Left = 296
          Top = 56
          Width = 45
          Height = 21
          TabOrder = 9
          RegStartAddress = '0xE0000880'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit202: TRegEdit
          Left = 248
          Top = 56
          Width = 45
          Height = 21
          TabOrder = 10
          RegStartAddress = '0xE000087E'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit203: TRegEdit
          Left = 104
          Top = 80
          Width = 45
          Height = 21
          TabOrder = 11
          RegStartAddress = '0xE0000878'
          RegBits = 3
        end
        object RegEdit204: TRegEdit
          Left = 152
          Top = 80
          Width = 45
          Height = 21
          TabOrder = 12
          RegStartAddress = '0xE000087A'
          RegBits = 3
        end
        object RegEdit205: TRegEdit
          Left = 200
          Top = 80
          Width = 45
          Height = 21
          TabOrder = 13
          RegStartAddress = '0xE000087C'
          RegBits = 4
        end
        object RegEdit206: TRegEdit
          Left = 344
          Top = 80
          Width = 45
          Height = 21
          TabOrder = 14
          RegStartAddress = '0xE0000882'
          RegBits = 4
        end
        object RegEdit207: TRegEdit
          Left = 296
          Top = 80
          Width = 45
          Height = 21
          TabOrder = 15
          RegStartAddress = '0xE0000880'
          RegBits = 4
        end
        object RegEdit208: TRegEdit
          Left = 248
          Top = 80
          Width = 45
          Height = 21
          TabOrder = 16
          RegStartAddress = '0xE000087E'
          RegBits = 4
        end
        object RegEdit209: TRegEdit
          Left = 104
          Top = 104
          Width = 45
          Height = 21
          TabOrder = 17
          RegStartAddress = '0xE0000879'
          RegBits = 3
          RegStart = 3
        end
        object RegEdit210: TRegEdit
          Left = 152
          Top = 104
          Width = 45
          Height = 21
          TabOrder = 18
          RegStartAddress = '0xE000087B'
          RegBits = 3
          RegStart = 3
        end
        object RegEdit211: TRegEdit
          Left = 200
          Top = 104
          Width = 45
          Height = 21
          TabOrder = 19
          RegStartAddress = '0xE000087D'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit212: TRegEdit
          Left = 344
          Top = 104
          Width = 45
          Height = 21
          TabOrder = 20
          RegStartAddress = '0xE0000883'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit213: TRegEdit
          Left = 296
          Top = 104
          Width = 45
          Height = 21
          TabOrder = 21
          RegStartAddress = '0xE0000881'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit214: TRegEdit
          Left = 248
          Top = 104
          Width = 45
          Height = 21
          TabOrder = 22
          RegStartAddress = '0xE000087F'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit215: TRegEdit
          Left = 104
          Top = 128
          Width = 45
          Height = 21
          TabOrder = 23
          RegStartAddress = '0xE0000879'
          RegBits = 3
        end
        object RegEdit216: TRegEdit
          Left = 152
          Top = 128
          Width = 45
          Height = 21
          TabOrder = 24
          RegStartAddress = '0xE000087B'
          RegBits = 3
        end
        object RegEdit217: TRegEdit
          Left = 200
          Top = 128
          Width = 45
          Height = 21
          TabOrder = 25
          RegStartAddress = '0xE000087D'
          RegBits = 4
        end
        object RegEdit218: TRegEdit
          Left = 344
          Top = 128
          Width = 45
          Height = 21
          TabOrder = 26
          RegStartAddress = '0xE0000883'
          RegBits = 4
        end
        object RegEdit219: TRegEdit
          Left = 296
          Top = 128
          Width = 45
          Height = 21
          TabOrder = 27
          RegStartAddress = '0xE0000881'
          RegBits = 4
        end
        object RegEdit220: TRegEdit
          Left = 248
          Top = 128
          Width = 45
          Height = 21
          TabOrder = 28
          RegStartAddress = '0xE000087F'
          RegBits = 4
        end
        object cb_pi_Enmv0: TRegCheckBox
          Left = 8
          Top = 152
          Width = 89
          Height = 17
          Caption = 'Enable_mv 0'
          TabOrder = 29
          RegAddress = '0xE000085C'
          RegBit = 6
        end
        object cb_pi_Enmv1: TRegCheckBox
          Left = 8
          Top = 176
          Width = 89
          Height = 17
          Caption = 'Enable_mv 1'
          TabOrder = 30
          RegAddress = '0xE000085C'
          RegBit = 5
        end
        object cb_pi_Enmv2: TRegCheckBox
          Left = 8
          Top = 200
          Width = 89
          Height = 17
          Caption = 'Enable_mv 2'
          TabOrder = 31
          RegAddress = '0xE000085C'
          RegBit = 4
        end
        object cb_pi_Enmv3: TRegCheckBox
          Left = 8
          Top = 224
          Width = 89
          Height = 17
          Caption = 'Enable_mv 3'
          TabOrder = 32
          RegAddress = '0xE000085C'
          RegBit = 3
        end
        object ed_pi_mv_x0: TRegEdit
          Left = 104
          Top = 152
          Width = 45
          Height = 21
          TabOrder = 33
          RegStartAddress = '0xE0000864'
          RegBits = 3
          RegStart = 3
        end
        object ed_pi_mv_y0: TRegEdit
          Left = 152
          Top = 152
          Width = 45
          Height = 21
          TabOrder = 34
          RegStartAddress = '0xE000086C'
          RegBits = 3
          RegStart = 3
        end
        object ed_pi_mv_x1: TRegEdit
          Left = 104
          Top = 176
          Width = 45
          Height = 21
          TabOrder = 35
          RegStartAddress = '0xE0000864'
          RegBits = 3
        end
        object ed_pi_mv_y1: TRegEdit
          Left = 152
          Top = 176
          Width = 45
          Height = 21
          TabOrder = 36
          RegStartAddress = '0xE000086C'
          RegBits = 3
        end
        object ed_pi_mv_x2: TRegEdit
          Left = 104
          Top = 200
          Width = 45
          Height = 21
          TabOrder = 37
          RegStartAddress = '0xE0000865'
          RegBits = 3
          RegStart = 3
        end
        object ed_pi_mv_y2: TRegEdit
          Left = 152
          Top = 200
          Width = 45
          Height = 21
          TabOrder = 38
          RegStartAddress = '0xE000086D'
          RegBits = 3
          RegStart = 3
        end
        object ed_pi_mv_x3: TRegEdit
          Left = 104
          Top = 224
          Width = 45
          Height = 21
          TabOrder = 39
          RegStartAddress = '0xE0000865'
          RegBits = 3
        end
        object ed_pi_mv_y3: TRegEdit
          Left = 152
          Top = 224
          Width = 45
          Height = 21
          TabOrder = 40
          RegStartAddress = '0xE000086D'
          RegBits = 3
        end
        object cb_pi_Enmv4: TRegCheckBox
          Left = 8
          Top = 248
          Width = 89
          Height = 17
          Caption = 'Enable_mv 4'
          TabOrder = 41
          RegAddress = '0xE000085C'
          RegBit = 2
        end
        object cb_pi_Enmv5: TRegCheckBox
          Left = 8
          Top = 272
          Width = 89
          Height = 17
          Caption = 'Enable_mv 5'
          TabOrder = 42
          RegAddress = '0xE000085C'
          RegBit = 1
        end
        object cb_pi_Enmv6: TRegCheckBox
          Left = 8
          Top = 296
          Width = 89
          Height = 17
          Caption = 'Enable_mv 6'
          TabOrder = 43
          RegAddress = '0xE000085C'
        end
        object cb_pi_Enmv7: TRegCheckBox
          Left = 8
          Top = 320
          Width = 89
          Height = 17
          Caption = 'Enable_mv 7'
          TabOrder = 44
          RegAddress = '0xE000085D'
          RegBit = 7
        end
        object ed_pi_mv_x4: TRegEdit
          Left = 104
          Top = 248
          Width = 45
          Height = 21
          TabOrder = 45
          RegStartAddress = '0xE0000866'
          RegBits = 3
          RegStart = 3
        end
        object ed_pi_mv_y4: TRegEdit
          Left = 152
          Top = 248
          Width = 45
          Height = 21
          TabOrder = 46
          RegStartAddress = '0xE000086E'
          RegBits = 3
          RegStart = 3
        end
        object ed_pi_mv_x5: TRegEdit
          Left = 104
          Top = 272
          Width = 45
          Height = 21
          TabOrder = 47
          RegStartAddress = '0xE0000866'
          RegBits = 3
        end
        object ed_pi_mv_y5: TRegEdit
          Left = 152
          Top = 272
          Width = 45
          Height = 21
          TabOrder = 48
          RegStartAddress = '0xE000086E'
          RegBits = 3
        end
        object ed_pi_mv_x6: TRegEdit
          Left = 104
          Top = 296
          Width = 45
          Height = 21
          TabOrder = 49
          RegStartAddress = '0xE0000867'
          RegBits = 3
          RegStart = 3
        end
        object ed_pi_mv_y6: TRegEdit
          Left = 152
          Top = 296
          Width = 45
          Height = 21
          TabOrder = 50
          RegStartAddress = '0xE000086F'
          RegBits = 3
          RegStart = 3
        end
        object ed_pi_mv_x7: TRegEdit
          Left = 104
          Top = 320
          Width = 45
          Height = 21
          TabOrder = 51
          RegStartAddress = '0xE0000867'
          RegBits = 3
        end
        object ed_pi_mv_y7: TRegEdit
          Left = 152
          Top = 320
          Width = 45
          Height = 21
          TabOrder = 52
          RegStartAddress = '0xE000086F'
          RegBits = 3
        end
        object cb_pi_Enmv8: TRegCheckBox
          Left = 8
          Top = 344
          Width = 89
          Height = 17
          Caption = 'Enable_mv 8'
          TabOrder = 53
          RegAddress = '0xE000085D'
          RegBit = 6
        end
        object cb_pi_Enmv9: TRegCheckBox
          Left = 8
          Top = 368
          Width = 89
          Height = 17
          Caption = 'Enable_mv 9'
          TabOrder = 54
          RegAddress = '0xE000085D'
          RegBit = 5
        end
        object ed_pi_mv_x8: TRegEdit
          Left = 104
          Top = 344
          Width = 45
          Height = 21
          TabOrder = 55
          RegStartAddress = '0xE0000868'
          RegBits = 3
          RegStart = 3
        end
        object ed_pi_mv_y8: TRegEdit
          Left = 152
          Top = 344
          Width = 45
          Height = 21
          TabOrder = 56
          RegStartAddress = '0xE0000870'
          RegBits = 3
          RegStart = 3
        end
        object ed_pi_mv_x9: TRegEdit
          Left = 104
          Top = 368
          Width = 45
          Height = 21
          TabOrder = 57
          RegStartAddress = '0xE0000868'
          RegBits = 3
        end
        object ed_pi_mv_y9: TRegEdit
          Left = 152
          Top = 368
          Width = 45
          Height = 21
          TabOrder = 58
          RegStartAddress = '0xE0000870'
          RegBits = 3
        end
        object GroupBox13: TGroupBox
          Left = 232
          Top = 184
          Width = 137
          Height = 137
          Caption = 'Matrix'
          TabOrder = 59
          object Label63: TLabel
            Left = 32
            Top = 24
            Width = 9
            Height = 13
            Caption = '-2'
          end
          object Label64: TLabel
            Left = 48
            Top = 24
            Width = 9
            Height = 13
            Caption = '-1'
          end
          object Label65: TLabel
            Left = 64
            Top = 24
            Width = 6
            Height = 13
            Caption = '0'
          end
          object Label66: TLabel
            Left = 80
            Top = 24
            Width = 6
            Height = 13
            Caption = '1'
          end
          object Label67: TLabel
            Left = 96
            Top = 24
            Width = 6
            Height = 13
            Caption = '2'
          end
          object Label68: TLabel
            Left = 16
            Top = 40
            Width = 9
            Height = 13
            Caption = '-2'
          end
          object Label69: TLabel
            Left = 16
            Top = 56
            Width = 9
            Height = 13
            Caption = '-1'
          end
          object Label70: TLabel
            Left = 16
            Top = 72
            Width = 6
            Height = 13
            Caption = '0'
          end
          object Label71: TLabel
            Left = 16
            Top = 88
            Width = 6
            Height = 13
            Caption = '1'
          end
          object Label72: TLabel
            Left = 16
            Top = 104
            Width = 6
            Height = 13
            Caption = '2'
          end
          object CheckBox1: TCheckBox
            Left = 32
            Top = 40
            Width = 17
            Height = 17
            TabOrder = 0
            OnClick = cb_ip_ma1Click
          end
          object CheckBox2: TCheckBox
            Tag = 1
            Left = 48
            Top = 40
            Width = 17
            Height = 17
            TabOrder = 1
            OnClick = cb_ip_ma1Click
          end
          object CheckBox3: TCheckBox
            Tag = 2
            Left = 64
            Top = 40
            Width = 17
            Height = 17
            TabOrder = 2
            OnClick = cb_ip_ma1Click
          end
          object CheckBox4: TCheckBox
            Tag = 3
            Left = 80
            Top = 40
            Width = 17
            Height = 17
            TabOrder = 3
            OnClick = cb_ip_ma1Click
          end
          object CheckBox5: TCheckBox
            Tag = 4
            Left = 96
            Top = 40
            Width = 17
            Height = 17
            TabOrder = 4
            OnClick = cb_ip_ma1Click
          end
          object CheckBox7: TCheckBox
            Tag = 5
            Left = 32
            Top = 56
            Width = 17
            Height = 17
            TabOrder = 5
            OnClick = cb_ip_ma1Click
          end
          object CheckBox8: TCheckBox
            Tag = 6
            Left = 48
            Top = 56
            Width = 17
            Height = 17
            TabOrder = 6
            OnClick = cb_ip_ma1Click
          end
          object CheckBox9: TCheckBox
            Tag = 7
            Left = 64
            Top = 56
            Width = 17
            Height = 17
            TabOrder = 7
            OnClick = cb_ip_ma1Click
          end
          object CheckBox10: TCheckBox
            Tag = 8
            Left = 80
            Top = 56
            Width = 17
            Height = 17
            TabOrder = 8
            OnClick = cb_ip_ma1Click
          end
          object CheckBox11: TCheckBox
            Tag = 9
            Left = 96
            Top = 56
            Width = 17
            Height = 17
            TabOrder = 9
            OnClick = cb_ip_ma1Click
          end
          object CheckBox13: TCheckBox
            Tag = 10
            Left = 32
            Top = 72
            Width = 17
            Height = 17
            TabOrder = 10
            OnClick = cb_ip_ma1Click
          end
          object CheckBox14: TCheckBox
            Tag = 11
            Left = 48
            Top = 72
            Width = 17
            Height = 17
            TabOrder = 11
            OnClick = cb_ip_ma1Click
          end
          object CheckBox15: TCheckBox
            Tag = 12
            Left = 64
            Top = 72
            Width = 17
            Height = 17
            TabOrder = 12
            OnClick = cb_ip_ma1Click
          end
          object CheckBox16: TCheckBox
            Tag = 13
            Left = 80
            Top = 72
            Width = 17
            Height = 17
            TabOrder = 13
            OnClick = cb_ip_ma1Click
          end
          object CheckBox17: TCheckBox
            Tag = 14
            Left = 96
            Top = 72
            Width = 17
            Height = 17
            TabOrder = 14
            OnClick = cb_ip_ma1Click
          end
          object CheckBox76: TCheckBox
            Tag = 15
            Left = 32
            Top = 88
            Width = 17
            Height = 17
            TabOrder = 15
            OnClick = cb_ip_ma1Click
          end
          object CheckBox77: TCheckBox
            Tag = 16
            Left = 48
            Top = 88
            Width = 17
            Height = 17
            TabOrder = 16
            OnClick = cb_ip_ma1Click
          end
          object CheckBox78: TCheckBox
            Tag = 17
            Left = 64
            Top = 88
            Width = 17
            Height = 17
            TabOrder = 17
            OnClick = cb_ip_ma1Click
          end
          object CheckBox79: TCheckBox
            Tag = 18
            Left = 80
            Top = 88
            Width = 17
            Height = 17
            TabOrder = 18
            OnClick = cb_ip_ma1Click
          end
          object CheckBox80: TCheckBox
            Tag = 19
            Left = 96
            Top = 88
            Width = 17
            Height = 17
            TabOrder = 19
            OnClick = cb_ip_ma1Click
          end
          object CheckBox81: TCheckBox
            Tag = 20
            Left = 32
            Top = 104
            Width = 17
            Height = 17
            TabOrder = 20
            OnClick = cb_ip_ma1Click
          end
          object CheckBox82: TCheckBox
            Tag = 21
            Left = 48
            Top = 104
            Width = 17
            Height = 17
            TabOrder = 21
            OnClick = cb_ip_ma1Click
          end
          object CheckBox83: TCheckBox
            Tag = 22
            Left = 64
            Top = 104
            Width = 17
            Height = 17
            TabOrder = 22
            OnClick = cb_ip_ma1Click
          end
          object CheckBox84: TCheckBox
            Tag = 23
            Left = 80
            Top = 104
            Width = 17
            Height = 17
            TabOrder = 23
            OnClick = cb_ip_ma1Click
          end
          object CheckBox85: TCheckBox
            Tag = 24
            Left = 96
            Top = 104
            Width = 17
            Height = 17
            TabOrder = 24
            OnClick = cb_ip_ma1Click
          end
        end
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'ph'
      ImageIndex = 2
      object GroupBox5: TGroupBox
        Left = 0
        Top = 8
        Width = 209
        Height = 425
        Caption = 'penalty value'
        TabOrder = 0
        object Label19: TLabel
          Left = 112
          Top = 16
          Width = 41
          Height = 13
          AutoSize = False
          Caption = 'Value'
        end
        object Label20: TLabel
          Left = 160
          Top = 16
          Width = 41
          Height = 13
          AutoSize = False
          Caption = 'Factor'
        end
        object RegLabeledEdit35: TRegLabeledEdit
          Left = 88
          Top = 32
          Width = 69
          Height = 21
          BiDiMode = bdLeftToRight
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.BiDiMode = bdLeftToRight
          EditLabel.Caption = 'penalty_gmv:    '
          EditLabel.ParentBiDiMode = False
          LabelPosition = lpLeft
          LabelSpacing = 3
          ParentBiDiMode = False
          TabOrder = 0
          RegStartAddress = '0xE0000884'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit36: TRegLabeledEdit
          Left = 88
          Top = 56
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 0:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 1
          RegStartAddress = '0xE0000885'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit37: TRegLabeledEdit
          Left = 88
          Top = 80
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 1:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 2
          RegStartAddress = '0xE0000886'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit38: TRegLabeledEdit
          Left = 88
          Top = 104
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 2:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 3
          RegStartAddress = '0xE0000887'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit39: TRegLabeledEdit
          Left = 88
          Top = 128
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 3:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 4
          RegStartAddress = '0xE0000888'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit40: TRegLabeledEdit
          Left = 88
          Top = 152
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 4:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 5
          RegStartAddress = '0xE0000889'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit41: TRegLabeledEdit
          Left = 88
          Top = 176
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 5:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 6
          RegStartAddress = '0xE000088A'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit42: TRegLabeledEdit
          Left = 88
          Top = 200
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 6:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 7
          RegStartAddress = '0xE000088B'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit43: TRegLabeledEdit
          Left = 88
          Top = 224
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 7:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 8
          RegStartAddress = '0xE000088C'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit44: TRegLabeledEdit
          Left = 88
          Top = 248
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 8:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 9
          RegStartAddress = '0xE000088D'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit45: TRegLabeledEdit
          Left = 88
          Top = 272
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 9:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 10
          RegStartAddress = '0xE000088E'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit46: TRegLabeledEdit
          Left = 88
          Top = 296
          Width = 69
          Height = 21
          EditLabel.Width = 76
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_upd 0:  '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 11
          RegStartAddress = '0xE000088F'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit47: TRegLabeledEdit
          Left = 88
          Top = 320
          Width = 69
          Height = 21
          EditLabel.Width = 76
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_upd 1:  '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 12
          RegStartAddress = '0xE0000890'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit48: TRegLabeledEdit
          Left = 88
          Top = 344
          Width = 69
          Height = 21
          EditLabel.Width = 76
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_upd 2:  '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 13
          RegStartAddress = '0xE0000891'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit49: TRegLabeledEdit
          Left = 88
          Top = 368
          Width = 69
          Height = 21
          EditLabel.Width = 76
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_upd 3:  '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 14
          RegStartAddress = '0xE0000892'
          RegBits = 6
          TextType = ttInt
        end
        object RegEdit40: TRegEdit
          Left = 160
          Top = 32
          Width = 36
          Height = 21
          TabOrder = 15
          RegStartAddress = '0xE0000884'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit41: TRegEdit
          Left = 160
          Top = 56
          Width = 36
          Height = 21
          TabOrder = 16
          RegStartAddress = '0xE0000885'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit46: TRegEdit
          Left = 160
          Top = 80
          Width = 36
          Height = 21
          TabOrder = 17
          RegStartAddress = '0xE0000886'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit47: TRegEdit
          Left = 160
          Top = 104
          Width = 36
          Height = 21
          TabOrder = 18
          RegStartAddress = '0xE0000887'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit52: TRegEdit
          Left = 160
          Top = 128
          Width = 36
          Height = 21
          TabOrder = 19
          RegStartAddress = '0xE0000888'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit53: TRegEdit
          Left = 160
          Top = 152
          Width = 36
          Height = 21
          TabOrder = 20
          RegStartAddress = '0xE0000889'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit58: TRegEdit
          Left = 160
          Top = 176
          Width = 36
          Height = 21
          TabOrder = 21
          RegStartAddress = '0xE000088A'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit59: TRegEdit
          Left = 160
          Top = 200
          Width = 36
          Height = 21
          TabOrder = 22
          RegStartAddress = '0xE000088B'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit64: TRegEdit
          Left = 160
          Top = 224
          Width = 36
          Height = 21
          TabOrder = 23
          RegStartAddress = '0xE000088C'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit65: TRegEdit
          Left = 160
          Top = 248
          Width = 36
          Height = 21
          TabOrder = 24
          RegStartAddress = '0xE000088D'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit66: TRegEdit
          Left = 160
          Top = 272
          Width = 36
          Height = 21
          TabOrder = 25
          RegStartAddress = '0xE000088E'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit70: TRegEdit
          Left = 160
          Top = 296
          Width = 36
          Height = 21
          TabOrder = 26
          RegStartAddress = '0xE000088F'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit71: TRegEdit
          Left = 160
          Top = 320
          Width = 36
          Height = 21
          TabOrder = 27
          RegStartAddress = '0xE0000890'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit76: TRegEdit
          Left = 160
          Top = 344
          Width = 36
          Height = 21
          TabOrder = 28
          RegStartAddress = '0xE0000891'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit77: TRegEdit
          Left = 160
          Top = 368
          Width = 36
          Height = 21
          TabOrder = 29
          RegStartAddress = '0xE0000892'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
      end
      object GroupBox6: TGroupBox
        Left = 216
        Top = 8
        Width = 401
        Height = 425
        Caption = 'Pos'
        TabOrder = 1
        object Label21: TLabel
          Left = 112
          Top = 40
          Width = 33
          Height = 13
          Alignment = taCenter
          AutoSize = False
          Caption = 'X'
        end
        object Label22: TLabel
          Left = 160
          Top = 40
          Width = 32
          Height = 13
          Alignment = taCenter
          AutoSize = False
          Caption = 'Y'
        end
        object Label23: TLabel
          Left = 208
          Top = 40
          Width = 32
          Height = 13
          Alignment = taCenter
          AutoSize = False
          Caption = 'X1'
        end
        object Label24: TLabel
          Left = 256
          Top = 40
          Width = 32
          Height = 13
          Alignment = taCenter
          AutoSize = False
          Caption = 'Y1'
        end
        object Label25: TLabel
          Left = 304
          Top = 40
          Width = 32
          Height = 13
          Alignment = taCenter
          AutoSize = False
          Caption = 'X2'
        end
        object Label26: TLabel
          Left = 352
          Top = 40
          Width = 32
          Height = 13
          Alignment = taCenter
          AutoSize = False
          Caption = 'Y2'
        end
        object RegCheckBox19: TRegCheckBox
          Left = 8
          Top = 32
          Width = 97
          Height = 17
          Caption = 'Enable_gmv'
          TabOrder = 0
          RegAddress = '0xE0000898'
          RegBit = 7
        end
        object RegCheckBox20: TRegCheckBox
          Left = 8
          Top = 56
          Width = 89
          Height = 17
          Caption = 'Enable_upd 0'
          TabOrder = 1
          RegAddress = '0xE0000899'
          RegBit = 4
        end
        object RegCheckBox21: TRegCheckBox
          Left = 8
          Top = 80
          Width = 89
          Height = 17
          Caption = 'Enable_upd 1'
          TabOrder = 2
          RegAddress = '0xE0000899'
          RegBit = 3
        end
        object RegCheckBox22: TRegCheckBox
          Left = 8
          Top = 104
          Width = 89
          Height = 17
          Caption = 'Enable_upd 2'
          TabOrder = 3
          RegAddress = '0xE0000899'
          RegBit = 2
        end
        object RegCheckBox23: TRegCheckBox
          Left = 8
          Top = 128
          Width = 89
          Height = 17
          Caption = 'Enable_upd 3'
          TabOrder = 4
          RegAddress = '0xE0000899'
          RegBit = 1
        end
        object RegEdit67: TRegEdit
          Left = 104
          Top = 56
          Width = 45
          Height = 21
          TabOrder = 5
          RegStartAddress = '0xE00008B4'
          RegBits = 3
          RegStart = 3
        end
        object RegEdit68: TRegEdit
          Left = 152
          Top = 56
          Width = 45
          Height = 21
          TabOrder = 6
          RegStartAddress = '0xE00008B6'
          RegBits = 3
          RegStart = 3
        end
        object RegEdit69: TRegEdit
          Left = 200
          Top = 56
          Width = 45
          Height = 21
          TabOrder = 7
          RegStartAddress = '0xE00008B8'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit72: TRegEdit
          Left = 344
          Top = 56
          Width = 45
          Height = 21
          TabOrder = 8
          RegStartAddress = '0xE00008BE'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit73: TRegEdit
          Left = 296
          Top = 56
          Width = 45
          Height = 21
          TabOrder = 9
          RegStartAddress = '0xE00008BC'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit74: TRegEdit
          Left = 248
          Top = 56
          Width = 45
          Height = 21
          TabOrder = 10
          RegStartAddress = '0xE00008BA'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit75: TRegEdit
          Left = 104
          Top = 80
          Width = 45
          Height = 21
          TabOrder = 11
          RegStartAddress = '0xE00008B4'
          RegBits = 3
        end
        object RegEdit78: TRegEdit
          Left = 152
          Top = 80
          Width = 45
          Height = 21
          TabOrder = 12
          RegStartAddress = '0xE00008B6'
          RegBits = 3
        end
        object RegEdit79: TRegEdit
          Left = 200
          Top = 80
          Width = 45
          Height = 21
          TabOrder = 13
          RegStartAddress = '0xE00008B8'
          RegBits = 4
        end
        object RegEdit80: TRegEdit
          Left = 344
          Top = 80
          Width = 45
          Height = 21
          TabOrder = 14
          RegStartAddress = '0xE00008BE'
          RegBits = 4
        end
        object RegEdit81: TRegEdit
          Left = 296
          Top = 80
          Width = 45
          Height = 21
          TabOrder = 15
          RegStartAddress = '0xE00008BC'
          RegBits = 4
        end
        object RegEdit84: TRegEdit
          Left = 248
          Top = 80
          Width = 45
          Height = 21
          TabOrder = 16
          RegStartAddress = '0xE00008BA'
          RegBits = 4
        end
        object RegEdit85: TRegEdit
          Left = 104
          Top = 104
          Width = 45
          Height = 21
          TabOrder = 17
          RegStartAddress = '0xE00008B5'
          RegBits = 3
          RegStart = 3
        end
        object RegEdit86: TRegEdit
          Left = 152
          Top = 104
          Width = 45
          Height = 21
          TabOrder = 18
          RegStartAddress = '0xE00008B7'
          RegBits = 3
          RegStart = 3
        end
        object RegEdit87: TRegEdit
          Left = 200
          Top = 104
          Width = 45
          Height = 21
          TabOrder = 19
          RegStartAddress = '0xE00008B9'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit90: TRegEdit
          Left = 344
          Top = 104
          Width = 45
          Height = 21
          TabOrder = 20
          RegStartAddress = '0xE00008BF'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit91: TRegEdit
          Left = 296
          Top = 104
          Width = 45
          Height = 21
          TabOrder = 21
          RegStartAddress = '0xE00008BD'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit92: TRegEdit
          Left = 248
          Top = 104
          Width = 45
          Height = 21
          TabOrder = 22
          RegStartAddress = '0xE00008BB'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit93: TRegEdit
          Left = 104
          Top = 128
          Width = 45
          Height = 21
          TabOrder = 23
          RegStartAddress = '0xE00008B5'
          RegBits = 3
        end
        object RegEdit96: TRegEdit
          Left = 152
          Top = 128
          Width = 45
          Height = 21
          TabOrder = 24
          RegStartAddress = '0xE00008B7'
          RegBits = 3
        end
        object RegEdit97: TRegEdit
          Left = 200
          Top = 128
          Width = 45
          Height = 21
          TabOrder = 25
          RegStartAddress = '0xE00008B9'
          RegBits = 4
        end
        object RegEdit98: TRegEdit
          Left = 344
          Top = 128
          Width = 45
          Height = 21
          TabOrder = 26
          RegStartAddress = '0xE00008BF'
          RegBits = 4
        end
        object RegEdit99: TRegEdit
          Left = 296
          Top = 128
          Width = 45
          Height = 21
          TabOrder = 27
          RegStartAddress = '0xE00008BD'
          RegBits = 4
        end
        object RegEdit100: TRegEdit
          Left = 248
          Top = 128
          Width = 45
          Height = 21
          TabOrder = 28
          RegStartAddress = '0xE00008BB'
          RegBits = 4
        end
        object cb_ph_Enmv0: TRegCheckBox
          Left = 8
          Top = 152
          Width = 89
          Height = 17
          Caption = 'Enable_mv 0'
          TabOrder = 29
          RegAddress = '0xE0000898'
          RegBit = 6
        end
        object cb_ph_Enmv1: TRegCheckBox
          Left = 8
          Top = 176
          Width = 89
          Height = 17
          Caption = 'Enable_mv 1'
          TabOrder = 30
          RegAddress = '0xE0000898'
          RegBit = 5
        end
        object cb_ph_Enmv2: TRegCheckBox
          Left = 8
          Top = 200
          Width = 89
          Height = 17
          Caption = 'Enable_mv 2'
          TabOrder = 31
          RegAddress = '0xE0000898'
          RegBit = 4
        end
        object cb_ph_Enmv3: TRegCheckBox
          Left = 8
          Top = 224
          Width = 89
          Height = 17
          Caption = 'Enable_mv 3'
          TabOrder = 32
          RegAddress = '0xE0000898'
          RegBit = 3
        end
        object ed_ph_mv_x0: TRegEdit
          Left = 104
          Top = 152
          Width = 45
          Height = 21
          TabOrder = 33
          RegStartAddress = '0xE00008A0'
          RegBits = 3
          RegStart = 3
        end
        object ed_ph_mv_y0: TRegEdit
          Left = 152
          Top = 152
          Width = 45
          Height = 21
          TabOrder = 34
          RegStartAddress = '0xE00008A8'
          RegBits = 3
          RegStart = 3
        end
        object ed_ph_mv_x1: TRegEdit
          Left = 104
          Top = 176
          Width = 45
          Height = 21
          TabOrder = 35
          RegStartAddress = '0xE00008A0'
          RegBits = 3
        end
        object ed_ph_mv_y1: TRegEdit
          Left = 152
          Top = 176
          Width = 45
          Height = 21
          TabOrder = 36
          RegStartAddress = '0xE00008A8'
          RegBits = 3
        end
        object ed_ph_mv_x2: TRegEdit
          Left = 104
          Top = 200
          Width = 45
          Height = 21
          TabOrder = 37
          RegStartAddress = '0xE00008A1'
          RegBits = 3
          RegStart = 3
        end
        object ed_ph_mv_y2: TRegEdit
          Left = 152
          Top = 200
          Width = 45
          Height = 21
          TabOrder = 38
          RegStartAddress = '0xE00008A9'
          RegBits = 3
          RegStart = 3
        end
        object ed_ph_mv_x3: TRegEdit
          Left = 104
          Top = 224
          Width = 45
          Height = 21
          TabOrder = 39
          RegStartAddress = '0xE00008A1'
          RegBits = 3
        end
        object ed_ph_mv_y3: TRegEdit
          Left = 152
          Top = 224
          Width = 45
          Height = 21
          TabOrder = 40
          RegStartAddress = '0xE00008A9'
          RegBits = 3
        end
        object cb_ph_Enmv4: TRegCheckBox
          Left = 8
          Top = 248
          Width = 89
          Height = 17
          Caption = 'Enable_mv 4'
          TabOrder = 41
          RegAddress = '0xE0000898'
          RegBit = 2
        end
        object cb_ph_Enmv5: TRegCheckBox
          Left = 8
          Top = 272
          Width = 89
          Height = 17
          Caption = 'Enable_mv 5'
          TabOrder = 42
          RegAddress = '0xE0000898'
          RegBit = 1
        end
        object cb_ph_Enmv6: TRegCheckBox
          Left = 8
          Top = 296
          Width = 89
          Height = 17
          Caption = 'Enable_mv 6'
          TabOrder = 43
          RegAddress = '0xE0000898'
        end
        object cb_ph_Enmv7: TRegCheckBox
          Left = 8
          Top = 320
          Width = 89
          Height = 17
          Caption = 'Enable_mv 7'
          TabOrder = 44
          RegAddress = '0xE0000899'
          RegBit = 7
        end
        object ed_ph_mv_x4: TRegEdit
          Left = 104
          Top = 248
          Width = 45
          Height = 21
          TabOrder = 45
          RegStartAddress = '0xE00008A2'
          RegBits = 3
          RegStart = 3
        end
        object ed_ph_mv_y4: TRegEdit
          Left = 152
          Top = 248
          Width = 45
          Height = 21
          TabOrder = 46
          RegStartAddress = '0xE00008AA'
          RegBits = 3
          RegStart = 3
        end
        object ed_ph_mv_x5: TRegEdit
          Left = 104
          Top = 272
          Width = 45
          Height = 21
          TabOrder = 47
          RegStartAddress = '0xE00008A2'
          RegBits = 3
        end
        object ed_ph_mv_y5: TRegEdit
          Left = 152
          Top = 272
          Width = 45
          Height = 21
          TabOrder = 48
          RegStartAddress = '0xE00008AA'
          RegBits = 3
        end
        object ed_ph_mv_x6: TRegEdit
          Left = 104
          Top = 296
          Width = 45
          Height = 21
          TabOrder = 49
          RegStartAddress = '0xE00008A3'
          RegBits = 3
          RegStart = 3
        end
        object ed_ph_mv_y6: TRegEdit
          Left = 152
          Top = 296
          Width = 45
          Height = 21
          TabOrder = 50
          RegStartAddress = '0xE00008AB'
          RegBits = 3
          RegStart = 3
        end
        object ed_ph_mv_x7: TRegEdit
          Left = 104
          Top = 320
          Width = 45
          Height = 21
          TabOrder = 51
          RegStartAddress = '0xE00008A3'
          RegBits = 3
        end
        object ed_ph_mv_y7: TRegEdit
          Left = 152
          Top = 320
          Width = 45
          Height = 21
          TabOrder = 52
          RegStartAddress = '0xE00008AB'
          RegBits = 3
        end
        object cb_ph_Enmv8: TRegCheckBox
          Left = 8
          Top = 344
          Width = 89
          Height = 17
          Caption = 'Enable_mv 8'
          TabOrder = 53
          RegAddress = '0xE0000899'
          RegBit = 6
        end
        object cb_ph_Enmv9: TRegCheckBox
          Left = 8
          Top = 368
          Width = 89
          Height = 17
          Caption = 'Enable_mv 9'
          TabOrder = 54
          RegAddress = '0xE0000899'
          RegBit = 5
        end
        object ed_ph_mv_x8: TRegEdit
          Left = 104
          Top = 344
          Width = 45
          Height = 21
          TabOrder = 55
          RegStartAddress = '0xE00008A4'
          RegBits = 3
          RegStart = 3
        end
        object ed_ph_mv_y8: TRegEdit
          Left = 152
          Top = 344
          Width = 45
          Height = 21
          TabOrder = 56
          RegStartAddress = '0xE00008AC'
          RegBits = 3
          RegStart = 3
        end
        object ed_ph_mv_x9: TRegEdit
          Left = 104
          Top = 368
          Width = 45
          Height = 21
          TabOrder = 57
          RegStartAddress = '0xE00008A4'
          RegBits = 3
        end
        object ed_ph_mv_y9: TRegEdit
          Left = 152
          Top = 368
          Width = 45
          Height = 21
          TabOrder = 58
          RegStartAddress = '0xE00008AC'
          RegBits = 3
        end
        object GroupBox7: TGroupBox
          Left = 232
          Top = 184
          Width = 137
          Height = 137
          Caption = 'Matrix'
          TabOrder = 59
          object Label27: TLabel
            Left = 32
            Top = 24
            Width = 9
            Height = 13
            Caption = '-2'
          end
          object Label28: TLabel
            Left = 48
            Top = 24
            Width = 9
            Height = 13
            Caption = '-1'
          end
          object Label29: TLabel
            Left = 64
            Top = 24
            Width = 6
            Height = 13
            Caption = '0'
          end
          object Label30: TLabel
            Left = 80
            Top = 24
            Width = 6
            Height = 13
            Caption = '1'
          end
          object Label31: TLabel
            Left = 96
            Top = 24
            Width = 6
            Height = 13
            Caption = '2'
          end
          object Label32: TLabel
            Left = 16
            Top = 40
            Width = 9
            Height = 13
            Caption = '-2'
          end
          object Label33: TLabel
            Left = 16
            Top = 56
            Width = 9
            Height = 13
            Caption = '-1'
          end
          object Label34: TLabel
            Left = 16
            Top = 72
            Width = 6
            Height = 13
            Caption = '0'
          end
          object Label35: TLabel
            Left = 16
            Top = 88
            Width = 6
            Height = 13
            Caption = '1'
          end
          object Label36: TLabel
            Left = 16
            Top = 104
            Width = 6
            Height = 13
            Caption = '2'
          end
          object CheckBox6: TCheckBox
            Left = 32
            Top = 40
            Width = 17
            Height = 17
            TabOrder = 0
            OnClick = cb_ip_ma1Click
          end
          object CheckBox12: TCheckBox
            Tag = 1
            Left = 48
            Top = 40
            Width = 17
            Height = 17
            TabOrder = 1
            OnClick = cb_ip_ma1Click
          end
          object CheckBox18: TCheckBox
            Tag = 2
            Left = 64
            Top = 40
            Width = 17
            Height = 17
            TabOrder = 2
            OnClick = cb_ip_ma1Click
          end
          object CheckBox24: TCheckBox
            Tag = 3
            Left = 80
            Top = 40
            Width = 17
            Height = 17
            TabOrder = 3
            OnClick = cb_ip_ma1Click
          end
          object CheckBox30: TCheckBox
            Tag = 4
            Left = 96
            Top = 40
            Width = 17
            Height = 17
            TabOrder = 4
            OnClick = cb_ip_ma1Click
          end
          object CheckBox31: TCheckBox
            Tag = 5
            Left = 32
            Top = 56
            Width = 17
            Height = 17
            TabOrder = 5
            OnClick = cb_ip_ma1Click
          end
          object CheckBox32: TCheckBox
            Tag = 6
            Left = 48
            Top = 56
            Width = 17
            Height = 17
            TabOrder = 6
            OnClick = cb_ip_ma1Click
          end
          object CheckBox33: TCheckBox
            Tag = 7
            Left = 64
            Top = 56
            Width = 17
            Height = 17
            TabOrder = 7
            OnClick = cb_ip_ma1Click
          end
          object CheckBox34: TCheckBox
            Tag = 8
            Left = 80
            Top = 56
            Width = 17
            Height = 17
            TabOrder = 8
            OnClick = cb_ip_ma1Click
          end
          object CheckBox35: TCheckBox
            Tag = 9
            Left = 96
            Top = 56
            Width = 17
            Height = 17
            TabOrder = 9
            OnClick = cb_ip_ma1Click
          end
          object CheckBox36: TCheckBox
            Tag = 10
            Left = 32
            Top = 72
            Width = 17
            Height = 17
            TabOrder = 10
            OnClick = cb_ip_ma1Click
          end
          object CheckBox37: TCheckBox
            Tag = 11
            Left = 48
            Top = 72
            Width = 17
            Height = 17
            TabOrder = 11
            OnClick = cb_ip_ma1Click
          end
          object CheckBox38: TCheckBox
            Tag = 12
            Left = 64
            Top = 72
            Width = 17
            Height = 17
            TabOrder = 12
            OnClick = cb_ip_ma1Click
          end
          object CheckBox39: TCheckBox
            Tag = 13
            Left = 80
            Top = 72
            Width = 17
            Height = 17
            TabOrder = 13
            OnClick = cb_ip_ma1Click
          end
          object CheckBox40: TCheckBox
            Tag = 14
            Left = 96
            Top = 72
            Width = 17
            Height = 17
            TabOrder = 14
            OnClick = cb_ip_ma1Click
          end
          object CheckBox41: TCheckBox
            Tag = 15
            Left = 32
            Top = 88
            Width = 17
            Height = 17
            TabOrder = 15
            OnClick = cb_ip_ma1Click
          end
          object CheckBox42: TCheckBox
            Tag = 16
            Left = 48
            Top = 88
            Width = 17
            Height = 17
            TabOrder = 16
            OnClick = cb_ip_ma1Click
          end
          object CheckBox43: TCheckBox
            Tag = 17
            Left = 64
            Top = 88
            Width = 17
            Height = 17
            TabOrder = 17
            OnClick = cb_ip_ma1Click
          end
          object CheckBox44: TCheckBox
            Tag = 18
            Left = 80
            Top = 88
            Width = 17
            Height = 17
            TabOrder = 18
            OnClick = cb_ip_ma1Click
          end
          object CheckBox45: TCheckBox
            Tag = 19
            Left = 96
            Top = 88
            Width = 17
            Height = 17
            TabOrder = 19
            OnClick = cb_ip_ma1Click
          end
          object CheckBox46: TCheckBox
            Tag = 20
            Left = 32
            Top = 104
            Width = 17
            Height = 17
            TabOrder = 20
            OnClick = cb_ip_ma1Click
          end
          object CheckBox47: TCheckBox
            Tag = 21
            Left = 48
            Top = 104
            Width = 17
            Height = 17
            TabOrder = 21
            OnClick = cb_ip_ma1Click
          end
          object CheckBox48: TCheckBox
            Tag = 22
            Left = 64
            Top = 104
            Width = 17
            Height = 17
            TabOrder = 22
            OnClick = cb_ip_ma1Click
          end
          object CheckBox49: TCheckBox
            Tag = 23
            Left = 80
            Top = 104
            Width = 17
            Height = 17
            TabOrder = 23
            OnClick = cb_ip_ma1Click
          end
          object CheckBox50: TCheckBox
            Tag = 24
            Left = 96
            Top = 104
            Width = 17
            Height = 17
            TabOrder = 24
            OnClick = cb_ip_ma1Click
          end
        end
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'pf'
      ImageIndex = 3
      object GroupBox8: TGroupBox
        Left = 0
        Top = 8
        Width = 209
        Height = 425
        Caption = 'penalty value'
        TabOrder = 0
        object Label37: TLabel
          Left = 112
          Top = 16
          Width = 41
          Height = 13
          AutoSize = False
          Caption = 'Value'
        end
        object Label38: TLabel
          Left = 160
          Top = 16
          Width = 41
          Height = 13
          AutoSize = False
          Caption = 'Factor'
        end
        object RegLabeledEdit20: TRegLabeledEdit
          Left = 88
          Top = 32
          Width = 69
          Height = 21
          BiDiMode = bdLeftToRight
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.BiDiMode = bdLeftToRight
          EditLabel.Caption = 'penalty_gmv:    '
          EditLabel.ParentBiDiMode = False
          LabelPosition = lpLeft
          LabelSpacing = 3
          ParentBiDiMode = False
          TabOrder = 0
          RegStartAddress = '0xE00008C0'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit21: TRegLabeledEdit
          Left = 88
          Top = 56
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 0:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 1
          RegStartAddress = '0xE00008C1'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit22: TRegLabeledEdit
          Left = 88
          Top = 80
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 1:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 2
          RegStartAddress = '0xE00008C2'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit23: TRegLabeledEdit
          Left = 88
          Top = 104
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 2:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 3
          RegStartAddress = '0xE00008C3'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit24: TRegLabeledEdit
          Left = 88
          Top = 128
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 3:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 4
          RegStartAddress = '0xE00008C4'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit25: TRegLabeledEdit
          Left = 88
          Top = 152
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 4:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 5
          RegStartAddress = '0xE00008C5'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit26: TRegLabeledEdit
          Left = 88
          Top = 176
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 5:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 6
          RegStartAddress = '0xE00008C6'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit27: TRegLabeledEdit
          Left = 88
          Top = 200
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 6:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 7
          RegStartAddress = '0xE00008C7'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit28: TRegLabeledEdit
          Left = 88
          Top = 224
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 7:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 8
          RegStartAddress = '0xE00008C8'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit29: TRegLabeledEdit
          Left = 88
          Top = 248
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 8:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 9
          RegStartAddress = '0xE00008C9'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit30: TRegLabeledEdit
          Left = 88
          Top = 272
          Width = 69
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_mv 9:   '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 10
          RegStartAddress = '0xE00008CA'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit31: TRegLabeledEdit
          Left = 88
          Top = 296
          Width = 69
          Height = 21
          EditLabel.Width = 76
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_upd 0:  '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 11
          RegStartAddress = '0xE00008CB'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit32: TRegLabeledEdit
          Left = 88
          Top = 320
          Width = 69
          Height = 21
          EditLabel.Width = 76
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_upd 1:  '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 12
          RegStartAddress = '0xE00008CC'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit33: TRegLabeledEdit
          Left = 88
          Top = 344
          Width = 69
          Height = 21
          EditLabel.Width = 76
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_upd 2:  '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 13
          RegStartAddress = '0xE00008CD'
          RegBits = 6
          TextType = ttInt
        end
        object RegLabeledEdit34: TRegLabeledEdit
          Left = 88
          Top = 368
          Width = 69
          Height = 21
          EditLabel.Width = 76
          EditLabel.Height = 13
          EditLabel.Caption = 'penalty_upd 3:  '
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 14
          RegStartAddress = '0xE00008CE'
          RegBits = 6
          TextType = ttInt
        end
        object RegEdit43: TRegEdit
          Left = 160
          Top = 32
          Width = 36
          Height = 21
          TabOrder = 15
          RegStartAddress = '0xE00008C0'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit44: TRegEdit
          Left = 160
          Top = 56
          Width = 36
          Height = 21
          TabOrder = 16
          RegStartAddress = '0xE00008C1'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit45: TRegEdit
          Left = 160
          Top = 80
          Width = 36
          Height = 21
          TabOrder = 17
          RegStartAddress = '0xE00008C2'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit48: TRegEdit
          Left = 160
          Top = 104
          Width = 36
          Height = 21
          TabOrder = 18
          RegStartAddress = '0xE00008C3'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit49: TRegEdit
          Left = 160
          Top = 128
          Width = 36
          Height = 21
          TabOrder = 19
          RegStartAddress = '0xE00008C4'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit50: TRegEdit
          Left = 160
          Top = 152
          Width = 36
          Height = 21
          TabOrder = 20
          RegStartAddress = '0xE00008C5'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit51: TRegEdit
          Left = 160
          Top = 176
          Width = 36
          Height = 21
          TabOrder = 21
          RegStartAddress = '0xE00008C6'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit54: TRegEdit
          Left = 160
          Top = 200
          Width = 36
          Height = 21
          TabOrder = 22
          RegStartAddress = '0xE00008C7'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit55: TRegEdit
          Left = 160
          Top = 224
          Width = 36
          Height = 21
          TabOrder = 23
          RegStartAddress = '0xE00008C8'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit56: TRegEdit
          Left = 160
          Top = 248
          Width = 36
          Height = 21
          TabOrder = 24
          RegStartAddress = '0xE00008C9'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit57: TRegEdit
          Left = 160
          Top = 272
          Width = 36
          Height = 21
          TabOrder = 25
          RegStartAddress = '0xE00008CA'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit60: TRegEdit
          Left = 160
          Top = 296
          Width = 36
          Height = 21
          TabOrder = 26
          RegStartAddress = '0xE00008CB'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit61: TRegEdit
          Left = 160
          Top = 320
          Width = 36
          Height = 21
          TabOrder = 27
          RegStartAddress = '0xE00008CC'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit62: TRegEdit
          Left = 160
          Top = 344
          Width = 36
          Height = 21
          TabOrder = 28
          RegStartAddress = '0xE00008CD'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
        object RegEdit63: TRegEdit
          Left = 160
          Top = 368
          Width = 36
          Height = 21
          TabOrder = 29
          RegStartAddress = '0xE00008CE'
          RegBits = 2
          RegStart = 6
          TextType = ttInt
        end
      end
      object GroupBox9: TGroupBox
        Left = 216
        Top = 8
        Width = 401
        Height = 425
        Caption = 'Pos'
        TabOrder = 1
        object Label39: TLabel
          Left = 112
          Top = 40
          Width = 33
          Height = 13
          Alignment = taCenter
          AutoSize = False
          Caption = 'X'
        end
        object Label40: TLabel
          Left = 160
          Top = 40
          Width = 32
          Height = 13
          Alignment = taCenter
          AutoSize = False
          Caption = 'Y'
        end
        object Label41: TLabel
          Left = 208
          Top = 40
          Width = 32
          Height = 13
          Alignment = taCenter
          AutoSize = False
          Caption = 'X1'
        end
        object Label42: TLabel
          Left = 256
          Top = 40
          Width = 32
          Height = 13
          Alignment = taCenter
          AutoSize = False
          Caption = 'Y1'
        end
        object Label43: TLabel
          Left = 304
          Top = 40
          Width = 32
          Height = 13
          Alignment = taCenter
          AutoSize = False
          Caption = 'X2'
        end
        object Label44: TLabel
          Left = 352
          Top = 40
          Width = 32
          Height = 13
          Alignment = taCenter
          AutoSize = False
          Caption = 'Y2'
        end
        object RegCheckBox34: TRegCheckBox
          Left = 8
          Top = 32
          Width = 97
          Height = 17
          Caption = 'Enable_gmv'
          TabOrder = 0
          RegAddress = '0xE00008D4'
          RegBit = 7
        end
        object RegCheckBox35: TRegCheckBox
          Left = 8
          Top = 56
          Width = 89
          Height = 17
          Caption = 'Enable_upd 0'
          TabOrder = 1
          RegAddress = '0xE00008D5'
          RegBit = 4
        end
        object RegCheckBox36: TRegCheckBox
          Left = 8
          Top = 80
          Width = 89
          Height = 17
          Caption = 'Enable_upd 1'
          TabOrder = 2
          RegAddress = '0xE00008D5'
          RegBit = 3
        end
        object RegCheckBox37: TRegCheckBox
          Left = 8
          Top = 104
          Width = 89
          Height = 17
          Caption = 'Enable_upd 2'
          TabOrder = 3
          RegAddress = '0xE00008D5'
          RegBit = 2
        end
        object RegCheckBox38: TRegCheckBox
          Left = 8
          Top = 128
          Width = 89
          Height = 17
          Caption = 'Enable_upd 3'
          TabOrder = 4
          RegAddress = '0xE00008D5'
          RegBit = 1
        end
        object RegEdit137: TRegEdit
          Left = 104
          Top = 56
          Width = 45
          Height = 21
          TabOrder = 5
          RegStartAddress = '0xE00008F0'
          RegBits = 3
          RegStart = 3
        end
        object RegEdit138: TRegEdit
          Left = 152
          Top = 56
          Width = 45
          Height = 21
          TabOrder = 6
          RegStartAddress = '0xE00008F2'
          RegBits = 3
          RegStart = 3
        end
        object RegEdit139: TRegEdit
          Left = 200
          Top = 56
          Width = 45
          Height = 21
          TabOrder = 7
          RegStartAddress = '0xE00008F4'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit140: TRegEdit
          Left = 344
          Top = 56
          Width = 45
          Height = 21
          TabOrder = 8
          RegStartAddress = '0xE00008FA'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit141: TRegEdit
          Left = 296
          Top = 56
          Width = 45
          Height = 21
          TabOrder = 9
          RegStartAddress = '0xE00008F8'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit142: TRegEdit
          Left = 248
          Top = 56
          Width = 45
          Height = 21
          TabOrder = 10
          RegStartAddress = '0xE00008F6'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit143: TRegEdit
          Left = 104
          Top = 80
          Width = 45
          Height = 21
          TabOrder = 11
          RegStartAddress = '0xE00008F0'
          RegBits = 3
        end
        object RegEdit144: TRegEdit
          Left = 152
          Top = 80
          Width = 45
          Height = 21
          TabOrder = 12
          RegStartAddress = '0xE00008F2'
          RegBits = 3
        end
        object RegEdit145: TRegEdit
          Left = 200
          Top = 80
          Width = 45
          Height = 21
          TabOrder = 13
          RegStartAddress = '0xE00008F4'
          RegBits = 4
        end
        object RegEdit146: TRegEdit
          Left = 344
          Top = 80
          Width = 45
          Height = 21
          TabOrder = 14
          RegStartAddress = '0xE00008FA'
          RegBits = 4
        end
        object RegEdit147: TRegEdit
          Left = 296
          Top = 80
          Width = 45
          Height = 21
          TabOrder = 15
          RegStartAddress = '0xE00008F8'
          RegBits = 4
        end
        object RegEdit148: TRegEdit
          Left = 248
          Top = 80
          Width = 45
          Height = 21
          TabOrder = 16
          RegStartAddress = '0xE00008F6'
          RegBits = 4
        end
        object RegEdit149: TRegEdit
          Left = 104
          Top = 104
          Width = 45
          Height = 21
          TabOrder = 17
          RegStartAddress = '0xE00008F1'
          RegBits = 3
          RegStart = 3
        end
        object RegEdit150: TRegEdit
          Left = 152
          Top = 104
          Width = 45
          Height = 21
          TabOrder = 18
          RegStartAddress = '0xE00008F3'
          RegBits = 3
          RegStart = 3
        end
        object RegEdit151: TRegEdit
          Left = 200
          Top = 104
          Width = 45
          Height = 21
          TabOrder = 19
          RegStartAddress = '0xE00008F5'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit152: TRegEdit
          Left = 344
          Top = 104
          Width = 45
          Height = 21
          TabOrder = 20
          RegStartAddress = '0xE0000FB'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit153: TRegEdit
          Left = 296
          Top = 104
          Width = 45
          Height = 21
          TabOrder = 21
          RegStartAddress = '0xE00008F9'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit154: TRegEdit
          Left = 248
          Top = 104
          Width = 45
          Height = 21
          TabOrder = 22
          RegStartAddress = '0xE00008F7'
          RegBits = 4
          RegStart = 4
        end
        object RegEdit155: TRegEdit
          Left = 104
          Top = 128
          Width = 45
          Height = 21
          TabOrder = 23
          RegStartAddress = '0xE00008F1'
          RegBits = 3
        end
        object RegEdit156: TRegEdit
          Left = 152
          Top = 128
          Width = 45
          Height = 21
          TabOrder = 24
          RegStartAddress = '0xE00008F3'
          RegBits = 3
        end
        object RegEdit157: TRegEdit
          Left = 200
          Top = 128
          Width = 45
          Height = 21
          TabOrder = 25
          RegStartAddress = '0xE00008F5'
          RegBits = 4
        end
        object RegEdit158: TRegEdit
          Left = 344
          Top = 128
          Width = 45
          Height = 21
          TabOrder = 26
          RegStartAddress = '0xE0000FB'
          RegBits = 4
        end
        object RegEdit159: TRegEdit
          Left = 296
          Top = 128
          Width = 45
          Height = 21
          TabOrder = 27
          RegStartAddress = '0xE00008F9'
          RegBits = 4
        end
        object RegEdit160: TRegEdit
          Left = 248
          Top = 128
          Width = 45
          Height = 21
          TabOrder = 28
          RegStartAddress = '0xE00008F7'
          RegBits = 4
        end
        object cb_pf_Enmv0: TRegCheckBox
          Left = 8
          Top = 152
          Width = 89
          Height = 17
          Caption = 'Enable_mv 0'
          TabOrder = 29
          RegAddress = '0xE00008D4'
          RegBit = 6
        end
        object cb_pf_Enmv1: TRegCheckBox
          Left = 8
          Top = 176
          Width = 89
          Height = 17
          Caption = 'Enable_mv 1'
          TabOrder = 30
          RegAddress = '0xE00008D4'
          RegBit = 5
        end
        object cb_pf_Enmv2: TRegCheckBox
          Left = 8
          Top = 200
          Width = 89
          Height = 17
          Caption = 'Enable_mv 2'
          TabOrder = 31
          RegAddress = '0xE00008D4'
          RegBit = 4
        end
        object cb_pf_Enmv3: TRegCheckBox
          Left = 8
          Top = 224
          Width = 89
          Height = 17
          Caption = 'Enable_mv 3'
          TabOrder = 32
          RegAddress = '0xE00008D4'
          RegBit = 3
        end
        object ed_pf_mv_x0: TRegEdit
          Left = 104
          Top = 152
          Width = 45
          Height = 21
          TabOrder = 33
          RegStartAddress = '0xE00008DC'
          RegBits = 3
          RegStart = 3
        end
        object ed_pf_mv_y0: TRegEdit
          Left = 152
          Top = 152
          Width = 45
          Height = 21
          TabOrder = 34
          RegStartAddress = '0xE00008E4'
          RegBits = 3
          RegStart = 3
        end
        object ed_pf_mv_x1: TRegEdit
          Left = 104
          Top = 176
          Width = 45
          Height = 21
          TabOrder = 35
          RegStartAddress = '0xE00008DC'
          RegBits = 3
        end
        object ed_pf_mv_y1: TRegEdit
          Left = 152
          Top = 176
          Width = 45
          Height = 21
          TabOrder = 36
          RegStartAddress = '0xE00008E4'
          RegBits = 3
        end
        object ed_pf_mv_x2: TRegEdit
          Left = 104
          Top = 200
          Width = 45
          Height = 21
          TabOrder = 37
          RegStartAddress = '0xE00008DD'
          RegBits = 3
          RegStart = 3
        end
        object ed_pf_mv_y2: TRegEdit
          Left = 152
          Top = 200
          Width = 45
          Height = 21
          TabOrder = 38
          RegStartAddress = '0xE00008E5'
          RegBits = 3
          RegStart = 3
        end
        object ed_pf_mv_x3: TRegEdit
          Left = 104
          Top = 224
          Width = 45
          Height = 21
          TabOrder = 39
          RegStartAddress = '0xE00008DD'
          RegBits = 3
        end
        object ed_pf_mv_y3: TRegEdit
          Left = 152
          Top = 224
          Width = 45
          Height = 21
          TabOrder = 40
          RegStartAddress = '0xE00008E5'
          RegBits = 3
        end
        object cb_pf_Enmv4: TRegCheckBox
          Left = 8
          Top = 248
          Width = 89
          Height = 17
          Caption = 'Enable_mv 4'
          TabOrder = 41
          RegAddress = '0xE00008D4'
          RegBit = 2
        end
        object cb_pf_Enmv5: TRegCheckBox
          Left = 8
          Top = 272
          Width = 89
          Height = 17
          Caption = 'Enable_mv 5'
          TabOrder = 42
          RegAddress = '0xE00008D4'
          RegBit = 1
        end
        object cb_pf_Enmv6: TRegCheckBox
          Left = 8
          Top = 296
          Width = 89
          Height = 17
          Caption = 'Enable_mv 6'
          TabOrder = 43
          RegAddress = '0xE00008D4'
        end
        object cb_pf_Enmv7: TRegCheckBox
          Left = 8
          Top = 320
          Width = 89
          Height = 17
          Caption = 'Enable_mv 7'
          TabOrder = 44
          RegAddress = '0xE00008D5'
          RegBit = 7
        end
        object ed_pf_mv_x4: TRegEdit
          Left = 104
          Top = 248
          Width = 45
          Height = 21
          TabOrder = 45
          RegStartAddress = '0xE00008DE'
          RegBits = 3
          RegStart = 3
        end
        object ed_pf_mv_y4: TRegEdit
          Left = 152
          Top = 248
          Width = 45
          Height = 21
          TabOrder = 46
          RegStartAddress = '0xE00008E6'
          RegBits = 3
          RegStart = 3
        end
        object ed_pf_mv_x5: TRegEdit
          Left = 104
          Top = 272
          Width = 45
          Height = 21
          TabOrder = 47
          RegStartAddress = '0xE00008DE'
          RegBits = 3
        end
        object ed_pf_mv_y5: TRegEdit
          Left = 152
          Top = 272
          Width = 45
          Height = 21
          TabOrder = 48
          RegStartAddress = '0xE00008E6'
          RegBits = 3
        end
        object ed_pf_mv_x6: TRegEdit
          Left = 104
          Top = 296
          Width = 45
          Height = 21
          TabOrder = 49
          RegStartAddress = '0xE00008DF'
          RegBits = 3
          RegStart = 3
        end
        object ed_pf_mv_y6: TRegEdit
          Left = 152
          Top = 296
          Width = 45
          Height = 21
          TabOrder = 50
          RegStartAddress = '0xE00008E7'
          RegBits = 3
          RegStart = 3
        end
        object ed_pf_mv_x7: TRegEdit
          Left = 104
          Top = 320
          Width = 45
          Height = 21
          TabOrder = 51
          RegStartAddress = '0xE00008DF'
          RegBits = 3
        end
        object ed_pf_mv_y7: TRegEdit
          Left = 152
          Top = 320
          Width = 45
          Height = 21
          TabOrder = 52
          RegStartAddress = '0xE00008E7'
          RegBits = 3
        end
        object cb_pf_Enmv8: TRegCheckBox
          Left = 8
          Top = 344
          Width = 89
          Height = 17
          Caption = 'Enable_mv 8'
          TabOrder = 53
          RegAddress = '0xE00008D5'
          RegBit = 6
        end
        object cb_pf_Enmv9: TRegCheckBox
          Left = 8
          Top = 368
          Width = 89
          Height = 17
          Caption = 'Enable_mv 9'
          TabOrder = 54
          RegAddress = '0xE00008D5'
          RegBit = 5
        end
        object ed_pf_mv_x8: TRegEdit
          Left = 104
          Top = 344
          Width = 45
          Height = 21
          TabOrder = 55
          RegStartAddress = '0xE00008E0'
          RegBits = 3
          RegStart = 3
        end
        object ed_pf_mv_y8: TRegEdit
          Left = 152
          Top = 344
          Width = 45
          Height = 21
          TabOrder = 56
          RegStartAddress = '0xE00008E8'
          RegBits = 3
          RegStart = 3
        end
        object ed_pf_mv_x9: TRegEdit
          Left = 104
          Top = 368
          Width = 45
          Height = 21
          TabOrder = 57
          RegStartAddress = '0xE00008E0'
          RegBits = 3
        end
        object ed_pf_mv_y9: TRegEdit
          Left = 152
          Top = 368
          Width = 45
          Height = 21
          TabOrder = 58
          RegStartAddress = '0xE00008E8'
          RegBits = 3
        end
        object GroupBox10: TGroupBox
          Left = 232
          Top = 184
          Width = 137
          Height = 137
          Caption = 'Matrix'
          TabOrder = 59
          object Label45: TLabel
            Left = 32
            Top = 24
            Width = 9
            Height = 13
            Caption = '-2'
          end
          object Label46: TLabel
            Left = 48
            Top = 24
            Width = 9
            Height = 13
            Caption = '-1'
          end
          object Label47: TLabel
            Left = 64
            Top = 24
            Width = 6
            Height = 13
            Caption = '0'
          end
          object Label48: TLabel
            Left = 80
            Top = 24
            Width = 6
            Height = 13
            Caption = '1'
          end
          object Label49: TLabel
            Left = 96
            Top = 24
            Width = 6
            Height = 13
            Caption = '2'
          end
          object Label50: TLabel
            Left = 16
            Top = 40
            Width = 9
            Height = 13
            Caption = '-2'
          end
          object Label51: TLabel
            Left = 16
            Top = 56
            Width = 9
            Height = 13
            Caption = '-1'
          end
          object Label52: TLabel
            Left = 16
            Top = 72
            Width = 6
            Height = 13
            Caption = '0'
          end
          object Label53: TLabel
            Left = 16
            Top = 88
            Width = 6
            Height = 13
            Caption = '1'
          end
          object Label54: TLabel
            Left = 16
            Top = 104
            Width = 6
            Height = 13
            Caption = '2'
          end
          object CheckBox51: TCheckBox
            Left = 32
            Top = 40
            Width = 17
            Height = 17
            TabOrder = 0
            OnClick = cb_ip_ma1Click
          end
          object CheckBox52: TCheckBox
            Tag = 1
            Left = 48
            Top = 40
            Width = 17
            Height = 17
            TabOrder = 1
            OnClick = cb_ip_ma1Click
          end
          object CheckBox53: TCheckBox
            Tag = 2
            Left = 64
            Top = 40
            Width = 17
            Height = 17
            TabOrder = 2
            OnClick = cb_ip_ma1Click
          end
          object CheckBox54: TCheckBox
            Tag = 3
            Left = 80
            Top = 40
            Width = 17
            Height = 17
            TabOrder = 3
            OnClick = cb_ip_ma1Click
          end
          object CheckBox55: TCheckBox
            Tag = 4
            Left = 96
            Top = 40
            Width = 17
            Height = 17
            TabOrder = 4
            OnClick = cb_ip_ma1Click
          end
          object CheckBox56: TCheckBox
            Tag = 5
            Left = 32
            Top = 56
            Width = 17
            Height = 17
            TabOrder = 5
            OnClick = cb_ip_ma1Click
          end
          object CheckBox57: TCheckBox
            Tag = 6
            Left = 48
            Top = 56
            Width = 17
            Height = 17
            TabOrder = 6
            OnClick = cb_ip_ma1Click
          end
          object CheckBox58: TCheckBox
            Tag = 7
            Left = 64
            Top = 56
            Width = 17
            Height = 17
            TabOrder = 7
            OnClick = cb_ip_ma1Click
          end
          object CheckBox59: TCheckBox
            Tag = 8
            Left = 80
            Top = 56
            Width = 17
            Height = 17
            TabOrder = 8
            OnClick = cb_ip_ma1Click
          end
          object CheckBox60: TCheckBox
            Tag = 9
            Left = 96
            Top = 56
            Width = 17
            Height = 17
            TabOrder = 9
            OnClick = cb_ip_ma1Click
          end
          object CheckBox61: TCheckBox
            Tag = 10
            Left = 32
            Top = 72
            Width = 17
            Height = 17
            TabOrder = 10
            OnClick = cb_ip_ma1Click
          end
          object CheckBox62: TCheckBox
            Tag = 11
            Left = 48
            Top = 72
            Width = 17
            Height = 17
            TabOrder = 11
            OnClick = cb_ip_ma1Click
          end
          object CheckBox63: TCheckBox
            Tag = 12
            Left = 64
            Top = 72
            Width = 17
            Height = 17
            TabOrder = 12
            OnClick = cb_ip_ma1Click
          end
          object CheckBox64: TCheckBox
            Tag = 13
            Left = 80
            Top = 72
            Width = 17
            Height = 17
            TabOrder = 13
            OnClick = cb_ip_ma1Click
          end
          object CheckBox65: TCheckBox
            Tag = 14
            Left = 96
            Top = 72
            Width = 17
            Height = 17
            TabOrder = 14
            OnClick = cb_ip_ma1Click
          end
          object CheckBox66: TCheckBox
            Tag = 15
            Left = 32
            Top = 88
            Width = 17
            Height = 17
            TabOrder = 15
            OnClick = cb_ip_ma1Click
          end
          object CheckBox67: TCheckBox
            Tag = 16
            Left = 48
            Top = 88
            Width = 17
            Height = 17
            TabOrder = 16
            OnClick = cb_ip_ma1Click
          end
          object CheckBox68: TCheckBox
            Tag = 17
            Left = 64
            Top = 88
            Width = 17
            Height = 17
            TabOrder = 17
            OnClick = cb_ip_ma1Click
          end
          object CheckBox69: TCheckBox
            Tag = 18
            Left = 80
            Top = 88
            Width = 17
            Height = 17
            TabOrder = 18
            OnClick = cb_ip_ma1Click
          end
          object CheckBox70: TCheckBox
            Tag = 19
            Left = 96
            Top = 88
            Width = 17
            Height = 17
            TabOrder = 19
            OnClick = cb_ip_ma1Click
          end
          object CheckBox71: TCheckBox
            Tag = 20
            Left = 32
            Top = 104
            Width = 17
            Height = 17
            TabOrder = 20
            OnClick = cb_ip_ma1Click
          end
          object CheckBox72: TCheckBox
            Tag = 21
            Left = 48
            Top = 104
            Width = 17
            Height = 17
            TabOrder = 21
            OnClick = cb_ip_ma1Click
          end
          object CheckBox73: TCheckBox
            Tag = 22
            Left = 64
            Top = 104
            Width = 17
            Height = 17
            TabOrder = 22
            OnClick = cb_ip_ma1Click
          end
          object CheckBox74: TCheckBox
            Tag = 23
            Left = 80
            Top = 104
            Width = 17
            Height = 17
            TabOrder = 23
            OnClick = cb_ip_ma1Click
          end
          object CheckBox75: TCheckBox
            Tag = 24
            Left = 96
            Top = 104
            Width = 17
            Height = 17
            TabOrder = 24
            OnClick = cb_ip_ma1Click
          end
        end
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 465
    Width = 638
    Height = 129
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 1
    object btnScanmv: TButton
      Left = 552
      Top = 16
      Width = 75
      Height = 25
      Caption = 'Scan mv'
      TabOrder = 0
      OnClick = btnScanmvClick
    end
    object btnRefresh: TButton
      Left = 552
      Top = 56
      Width = 75
      Height = 25
      Caption = 'Refresh'
      TabOrder = 1
      OnClick = btnRefreshClick
    end
  end
  object GB_GMV: TGroupBox
    Left = 4
    Top = 472
    Width = 525
    Height = 121
    Caption = 'GMV Invalid'
    TabOrder = 2
    object RegCheckBox16: TRegCheckBox
      Left = 16
      Top = 24
      Width = 97
      Height = 17
      Caption = 'gmv update set'
      TabOrder = 0
      RegAddress = '0xE0000901'
      RegBit = 7
    end
    object RegLabeledEdit17: TRegLabeledEdit
      Left = 128
      Top = 53
      Width = 121
      Height = 21
      EditLabel.Width = 110
      EditLabel.Height = 13
      EditLabel.Caption = 'gmv_dym_invalid_ratio:'
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 1
      RegStartAddress = '0xE0000901'
      RegBits = 7
    end
    object RegLabeledEdit18: TRegLabeledEdit
      Left = 128
      Top = 85
      Width = 121
      Height = 21
      EditLabel.Width = 110
      EditLabel.Height = 13
      EditLabel.Caption = 'gma_invalid_th:            '
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 2
      RegStartAddress = '0xE0000902'
      RegBits = 16
    end
    object RegCheckBox17: TRegCheckBox
      Left = 128
      Top = 24
      Width = 97
      Height = 17
      Caption = 'gmv cnt11 sel'
      TabOrder = 3
      RegAddress = '0xE0000905'
      RegBit = 7
    end
    object RegCheckBox18: TRegCheckBox
      Left = 264
      Top = 24
      Width = 97
      Height = 17
      Caption = 'gmv invalid sel'
      TabOrder = 4
      RegAddress = '0xE0000905'
      RegBit = 6
    end
    object RegLabeledEdit19: TRegLabeledEdit
      Left = 392
      Top = 53
      Width = 121
      Height = 21
      EditLabel.Width = 109
      EditLabel.Height = 13
      EditLabel.Caption = 'gmv_cand_coring_th:  '
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 5
      RegStartAddress = '0xE000090B'
      RegBits = 8
    end
  end
end
