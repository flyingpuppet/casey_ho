inherited Form_ME_2: TForm_ME_2
  Left = 181
  Top = 69
  Width = 917
  Height = 617
  Caption = 'Form_ME_2'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 369
    Height = 136
    Caption = 'Dynamic zero penalty'
    TabOrder = 0
    object RegCheckBox1: TRegCheckBox
      Left = 16
      Top = 24
      Width = 153
      Height = 17
      Caption = 'dym_zero_penalty_en'
      TabOrder = 0
      RegAddress = '0xE0000913'
      RegBit = 7
    end
    object RegLabeledEdit1: TRegLabeledEdit
      Left = 16
      Top = 56
      Width = 106
      Height = 21
      EditLabel.Width = 64
      EditLabel.Height = 13
      EditLabel.Caption = 'Detail z gain1'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 1
      RegStartAddress = '0xE000090C'
      RegBits = 4
      TextType = ttInt
    end
    object RegLabeledEdit2: TRegLabeledEdit
      Left = 16
      Top = 96
      Width = 106
      Height = 21
      EditLabel.Width = 64
      EditLabel.Height = 13
      EditLabel.Caption = 'Detail z gain2'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 2
      RegStartAddress = '0xE000090C'
      RegBits = 4
      RegStart = 4
      TextType = ttInt
    end
    object RegLabeledEdit3: TRegLabeledEdit
      Left = 128
      Top = 56
      Width = 106
      Height = 21
      EditLabel.Width = 56
      EditLabel.Height = 13
      EditLabel.Caption = 'Sad z gain1'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 3
      RegStartAddress = '0xE0000910'
      RegBits = 4
      TextType = ttInt
    end
    object RegLabeledEdit4: TRegLabeledEdit
      Left = 128
      Top = 96
      Width = 106
      Height = 21
      EditLabel.Width = 56
      EditLabel.Height = 13
      EditLabel.Caption = 'Sad z gain2'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 4
      RegStartAddress = '0xE0000910'
      RegBits = 4
      RegStart = 4
      TextType = ttInt
    end
  end
  object GroupBox2: TGroupBox
    Left = 0
    Top = 136
    Width = 369
    Height = 260
    Caption = 'SAD'
    TabOrder = 1
    object RegCheckBox2: TRegCheckBox
      Left = 152
      Top = 24
      Width = 97
      Height = 17
      Caption = 'wgt_np_sad'
      TabOrder = 0
      RegAddress = '0xE0000A0E'
      RegBit = 7
    end
    object RegCheckBox3: TRegCheckBox
      Left = 248
      Top = 24
      Width = 97
      Height = 17
      Caption = 'san_th_apl_en'
      TabOrder = 1
      RegAddress = '0xE0000A58'
      RegBit = 7
    end
    object RegLabeledEdit5: TRegLabeledEdit
      Left = 16
      Top = 88
      Width = 106
      Height = 21
      EditLabel.Width = 49
      EditLabel.Height = 13
      EditLabel.Caption = 'sad dtl thd'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 2
      RegStartAddress = '0xE0000904'
      RegBits = 8
      TextType = ttInt
    end
    object RegLabeledEdit6: TRegLabeledEdit
      Left = 16
      Top = 128
      Width = 106
      Height = 21
      EditLabel.Width = 54
      EditLabel.Height = 13
      EditLabel.Caption = 'detail gain1'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 3
      RegStartAddress = '0xE0000906'
      RegBits = 4
      TextType = ttInt
    end
    object RegLabeledEdit7: TRegLabeledEdit
      Left = 16
      Top = 168
      Width = 106
      Height = 21
      EditLabel.Width = 52
      EditLabel.Height = 13
      EditLabel.Caption = 'detai gain2'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 4
      RegStartAddress = '0xE0000906'
      RegBits = 4
      RegStart = 4
      TextType = ttInt
    end
    object RegLabeledEdit8: TRegLabeledEdit
      Left = 16
      Top = 208
      Width = 106
      Height = 21
      EditLabel.Width = 54
      EditLabel.Height = 13
      EditLabel.Caption = 'detail gain3'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 5
      RegStartAddress = '0xE0000907'
      RegBits = 4
      TextType = ttInt
    end
    object RegLabeledEdit9: TRegLabeledEdit
      Left = 136
      Top = 88
      Width = 106
      Height = 21
      EditLabel.Width = 65
      EditLabel.Height = 13
      EditLabel.Caption = 'sad th curve1'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 6
      RegStartAddress = '0xE0000915'
      RegBits = 4
      RegStart = 4
      TextType = ttInt
    end
    object RegLabeledEdit10: TRegLabeledEdit
      Left = 136
      Top = 128
      Width = 106
      Height = 21
      EditLabel.Width = 59
      EditLabel.Height = 13
      EditLabel.Caption = 'sad th curve'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 7
      RegStartAddress = '0xE0000915'
      RegBits = 4
      TextType = ttInt
    end
    object RegLabeledEdit11: TRegLabeledEdit
      Left = 136
      Top = 168
      Width = 106
      Height = 21
      EditLabel.Width = 83
      EditLabel.Height = 13
      EditLabel.Caption = 'sad smooth gain1'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 8
      RegStartAddress = '0xE0000918'
      RegBits = 4
      RegStart = 4
      TextType = ttInt
    end
    object RegLabeledEdit12: TRegLabeledEdit
      Left = 136
      Top = 208
      Width = 106
      Height = 21
      EditLabel.Width = 83
      EditLabel.Height = 13
      EditLabel.Caption = 'sad smooth gain2'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 9
      RegStartAddress = '0xE0000918'
      RegBits = 4
      TextType = ttInt
    end
    object RegLabeledEdit13: TRegLabeledEdit
      Left = 256
      Top = 88
      Width = 106
      Height = 21
      EditLabel.Width = 83
      EditLabel.Height = 13
      EditLabel.Caption = 'sad pure detail wt'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 10
      RegStartAddress = '0xE000091C'
      RegBits = 4
      RegStart = 4
      TextType = ttInt
    end
    object RegLabeledEdit14: TRegLabeledEdit
      Left = 256
      Top = 128
      Width = 106
      Height = 21
      EditLabel.Width = 92
      EditLabel.Height = 13
      EditLabel.Caption = 'sad pure smooth wt'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 11
      RegStartAddress = '0xE000091C'
      RegBits = 4
      TextType = ttInt
    end
    object RegLabeledEdit15: TRegLabeledEdit
      Left = 256
      Top = 168
      Width = 106
      Height = 21
      EditLabel.Width = 100
      EditLabel.Height = 13
      EditLabel.Caption = 'sad pure smooth shift'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 12
      RegStartAddress = '0xE000091E'
      RegBits = 3
      RegStart = 4
      TextType = ttInt
    end
    object RegLabeledEdit16: TRegLabeledEdit
      Left = 256
      Top = 208
      Width = 106
      Height = 21
      EditLabel.Width = 56
      EditLabel.Height = 13
      EditLabel.Caption = 'sad_apl_sel'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 13
      RegStartAddress = '0xE0000AFB'
      RegBits = 4
      TextType = ttInt
    end
    object RegLabeledEdit41: TRegLabeledEdit
      Left = 16
      Top = 40
      Width = 106
      Height = 21
      EditLabel.Width = 49
      EditLabel.Height = 13
      EditLabel.Caption = 'OBME Sel'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 14
      RegStartAddress = '0xE0000900'
      RegBits = 8
    end
  end
  object GroupBox3: TGroupBox
    Left = 0
    Top = 400
    Width = 739
    Height = 177
    Caption = 'periodic process'
    TabOrder = 2
    object RegCheckBox4: TRegCheckBox
      Left = 16
      Top = 24
      Width = 97
      Height = 17
      Caption = 'ip periodic en'
      TabOrder = 0
      RegAddress = '0xE0000920'
      RegBit = 7
    end
    object RegCheckBox5: TRegCheckBox
      Left = 16
      Top = 40
      Width = 97
      Height = 17
      Caption = 'pi periodic en'
      TabOrder = 1
      RegAddress = '0xE0000920'
      RegBit = 6
    end
    object RegCheckBox6: TRegCheckBox
      Left = 16
      Top = 56
      Width = 97
      Height = 17
      Caption = 'ph periodic en'
      TabOrder = 2
      RegAddress = '0xE0000920'
      RegBit = 5
    end
    object RegCheckBox7: TRegCheckBox
      Left = 16
      Top = 72
      Width = 97
      Height = 17
      Caption = 'pf periodic en'
      TabOrder = 3
      RegAddress = '0xE0000920'
      RegBit = 4
    end
    object RegCheckBox8: TRegCheckBox
      Left = 16
      Top = 88
      Width = 129
      Height = 17
      Caption = 'ip periodic z rule en'
      TabOrder = 4
      RegAddress = '0xE0000920'
      RegBit = 3
    end
    object RegCheckBox9: TRegCheckBox
      Left = 16
      Top = 104
      Width = 129
      Height = 17
      Caption = 'pi periodic z rule en'
      TabOrder = 5
      RegAddress = '0xE0000920'
      RegBit = 2
    end
    object RegCheckBox10: TRegCheckBox
      Left = 16
      Top = 120
      Width = 121
      Height = 17
      Caption = 'ph periodic z rule en'
      TabOrder = 6
      RegAddress = '0xE0000920'
      RegBit = 1
    end
    object RegCheckBox11: TRegCheckBox
      Left = 16
      Top = 136
      Width = 121
      Height = 17
      Caption = 'pf periodic z rule en'
      TabOrder = 7
      RegAddress = '0xE0000920'
    end
    object RegCheckBox12: TRegCheckBox
      Left = 136
      Top = 24
      Width = 155
      Height = 17
      Caption = 'ip periodic aplsad rule en'
      TabOrder = 8
      RegAddress = '0xE0000922'
      RegBit = 7
    end
    object RegCheckBox13: TRegCheckBox
      Left = 136
      Top = 40
      Width = 155
      Height = 17
      Caption = 'pi periodic aplsad rule en'
      TabOrder = 9
      RegAddress = '0xE0000922'
      RegBit = 6
    end
    object RegCheckBox14: TRegCheckBox
      Left = 136
      Top = 56
      Width = 155
      Height = 17
      Caption = 'ph periodic aplsad rule en'
      TabOrder = 10
      RegAddress = '0xE0000922'
      RegBit = 5
    end
    object RegCheckBox15: TRegCheckBox
      Left = 136
      Top = 72
      Width = 155
      Height = 17
      Caption = 'pf periodic aplsad rule en'
      TabOrder = 11
      RegAddress = '0xE0000922'
      RegBit = 4
    end
    object RegCheckBox16: TRegCheckBox
      Left = 136
      Top = 88
      Width = 155
      Height = 17
      Caption = 'ip periodic use smaller en'
      TabOrder = 12
      RegAddress = '0xE0000922'
      RegBit = 3
    end
    object RegCheckBox17: TRegCheckBox
      Left = 136
      Top = 104
      Width = 155
      Height = 17
      Caption = 'pi periodic use smaller en'
      TabOrder = 13
      RegAddress = '0xE0000922'
      RegBit = 2
    end
    object RegCheckBox18: TRegCheckBox
      Left = 136
      Top = 120
      Width = 155
      Height = 17
      Caption = 'ph periodic use smaller en'
      TabOrder = 14
      RegAddress = '0xE0000922'
      RegBit = 1
    end
    object RegCheckBox19: TRegCheckBox
      Left = 136
      Top = 136
      Width = 155
      Height = 17
      Caption = 'pf periodic use smaller en'
      TabOrder = 15
      RegAddress = '0xE0000922'
    end
    object RegLabeledEdit17: TRegLabeledEdit
      Left = 384
      Top = 16
      Width = 106
      Height = 21
      EditLabel.Width = 66
      EditLabel.Height = 13
      EditLabel.Caption = 'sad similar th2'
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 16
      RegStartAddress = '0xE0000968'
      RegBits = 8
      TextType = ttInt
    end
    object RegLabeledEdit18: TRegLabeledEdit
      Left = 384
      Top = 40
      Width = 106
      Height = 21
      EditLabel.Width = 71
      EditLabel.Height = 13
      EditLabel.Caption = 'ip sad similar th'
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 17
      RegStartAddress = '0xE0000921'
      RegBits = 2
      RegStart = 6
      TextType = ttInt
    end
    object RegLabeledEdit19: TRegLabeledEdit
      Left = 384
      Top = 64
      Width = 106
      Height = 21
      EditLabel.Width = 71
      EditLabel.Height = 13
      EditLabel.Caption = 'pi sad similar th'
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 18
      RegStartAddress = '0xE0000921'
      RegBits = 2
      RegStart = 4
      TextType = ttInt
    end
    object RegLabeledEdit20: TRegLabeledEdit
      Left = 384
      Top = 88
      Width = 106
      Height = 21
      EditLabel.Width = 75
      EditLabel.Height = 13
      EditLabel.Caption = 'ph sad similar th'
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 19
      RegStartAddress = '0xE0000921'
      RegBits = 2
      RegStart = 2
      TextType = ttInt
    end
    object RegLabeledEdit21: TRegLabeledEdit
      Left = 384
      Top = 112
      Width = 106
      Height = 21
      EditLabel.Width = 72
      EditLabel.Height = 13
      EditLabel.Caption = 'pf sad similar th'
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 20
      RegStartAddress = '0xE0000921'
      RegBits = 2
      TextType = ttInt
    end
    object RegLabeledEdit22: TRegLabeledEdit
      Left = 384
      Top = 136
      Width = 106
      Height = 21
      EditLabel.Width = 76
      EditLabel.Height = 13
      EditLabel.Caption = 'ip sad similar diff'
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 21
      RegStartAddress = '0xE0000924'
      RegBits = 8
      TextType = ttInt
    end
    object RegLabeledEdit23: TRegLabeledEdit
      Left = 608
      Top = 16
      Width = 106
      Height = 21
      EditLabel.Width = 76
      EditLabel.Height = 13
      EditLabel.Caption = 'pi sad similar diff'
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 22
      RegStartAddress = '0xE0000925'
      RegBits = 8
      TextType = ttInt
    end
    object RegLabeledEdit24: TRegLabeledEdit
      Left = 608
      Top = 40
      Width = 106
      Height = 21
      EditLabel.Width = 80
      EditLabel.Height = 13
      EditLabel.Caption = 'ph sad similar diff'
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 23
      RegStartAddress = '0xE0000926'
      RegBits = 8
      TextType = ttInt
    end
    object RegLabeledEdit25: TRegLabeledEdit
      Left = 608
      Top = 64
      Width = 106
      Height = 21
      EditLabel.Width = 77
      EditLabel.Height = 13
      EditLabel.Caption = 'pf sad similar diff'
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 24
      RegStartAddress = '0xE0000927'
      RegBits = 8
      TextType = ttInt
    end
    object RegLabeledEdit26: TRegLabeledEdit
      Left = 608
      Top = 88
      Width = 106
      Height = 21
      EditLabel.Width = 89
      EditLabel.Height = 13
      EditLabel.Caption = 'periodic_apl_gain1'
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 25
      RegStartAddress = '0xE0000964'
      RegBits = 4
      TextType = ttInt
    end
    object RegLabeledEdit27: TRegLabeledEdit
      Left = 607
      Top = 112
      Width = 106
      Height = 21
      EditLabel.Width = 89
      EditLabel.Height = 13
      EditLabel.Caption = 'periodic_apl_gain2'
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 26
      RegStartAddress = '0xE0000965'
      RegBits = 4
      RegStart = 4
      TextType = ttInt
    end
    object RegLabeledEdit28: TRegLabeledEdit
      Left = 607
      Top = 136
      Width = 106
      Height = 21
      EditLabel.Width = 89
      EditLabel.Height = 13
      EditLabel.Caption = 'periodic_apl_gain3'
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 27
      RegStartAddress = '0xE0000965'
      RegBits = 4
      TextType = ttInt
    end
  end
  object GroupBox4: TGroupBox
    Left = 369
    Top = 0
    Width = 533
    Height = 396
    Caption = 'ME Sobj'
    TabOrder = 3
    object RegCheckBox20: TRegCheckBox
      Left = 8
      Top = 16
      Width = 97
      Height = 17
      Caption = 'sobj_en'
      TabOrder = 0
      RegAddress = '0xE000094C'
      RegBit = 7
    end
    object RegCheckBox21: TRegCheckBox
      Left = 88
      Top = 16
      Width = 97
      Height = 17
      Caption = 'sobj_r0_en'
      TabOrder = 1
      RegAddress = '0xE000094C'
      RegBit = 6
    end
    object RegCheckBox22: TRegCheckBox
      Left = 168
      Top = 16
      Width = 97
      Height = 17
      Caption = 'sobj_r1_en'
      TabOrder = 2
      RegAddress = '0xE000094C'
      RegBit = 5
    end
    object RegCheckBox23: TRegCheckBox
      Left = 256
      Top = 16
      Width = 97
      Height = 17
      Caption = 'sobj_r2_en'
      TabOrder = 3
      RegAddress = '0xE000094C'
      RegBit = 4
    end
    object GroupBox5: TGroupBox
      Left = 2
      Top = 33
      Width = 529
      Height = 121
      Caption = 'rule 0'
      TabOrder = 4
      object RegCheckBox24: TRegCheckBox
        Left = 128
        Top = 8
        Width = 121
        Height = 17
        Caption = 'sobj_r0_ip_sad_and'
        TabOrder = 0
        RegAddress = '0xE0000953'
        RegBit = 7
      end
      object RegCheckBox25: TRegCheckBox
        Left = 128
        Top = 24
        Width = 113
        Height = 17
        Caption = 'sobj_r0_ip_dtl_and'
        TabOrder = 1
        RegAddress = '0xE0000953'
        RegBit = 6
      end
      object RegLabeledEdit33: TRegLabeledEdit
        Left = 128
        Top = 44
        Width = 106
        Height = 21
        EditLabel.Width = 86
        EditLabel.Height = 13
        EditLabel.Caption = 'sobj_r0_ip_dtl_th: '
        LabelPosition = lpLeft
        LabelSpacing = 3
        TabOrder = 2
        RegStartAddress = '0xE0000953'
        RegBits = 3
        TextType = ttInt
      end
      object RegLabeledEdit34: TRegLabeledEdit
        Left = 128
        Top = 68
        Width = 106
        Height = 21
        EditLabel.Width = 92
        EditLabel.Height = 13
        EditLabel.Caption = 'sobj_r0_ip_sad_th: '
        LabelPosition = lpLeft
        LabelSpacing = 3
        TabOrder = 3
        RegStartAddress = '0xE0000951'
        RegBits = 13
        TextType = ttInt
      end
      object RegLabeledEdit35: TRegLabeledEdit
        Left = 128
        Top = 92
        Width = 106
        Height = 21
        EditLabel.Width = 100
        EditLabel.Height = 13
        EditLabel.Caption = 'sobj_r0_ip_static_th: '
        LabelPosition = lpLeft
        LabelSpacing = 3
        TabOrder = 4
        RegStartAddress = '0xE0000950'
        RegBits = 8
        TextType = ttInt
      end
      object RegLabeledEdit29: TRegLabeledEdit
        Left = 400
        Top = 20
        Width = 106
        Height = 21
        EditLabel.Width = 117
        EditLabel.Height = 13
        EditLabel.Caption = 'sobj_r0_mv_min_diff_th: '
        LabelPosition = lpLeft
        LabelSpacing = 3
        TabOrder = 5
        RegStartAddress = '0xE000095C'
        RegBits = 8
        TextType = ttInt
      end
      object RegLabeledEdit30: TRegLabeledEdit
        Left = 400
        Top = 44
        Width = 106
        Height = 21
        EditLabel.Width = 120
        EditLabel.Height = 13
        EditLabel.Caption = 'sobj_r0_mv_max_diff_th: '
        LabelPosition = lpLeft
        LabelSpacing = 3
        TabOrder = 6
        RegStartAddress = '0xE000095D'
        RegBits = 8
        TextType = ttInt
      end
      object RegLabeledEdit31: TRegLabeledEdit
        Left = 400
        Top = 68
        Width = 106
        Height = 21
        EditLabel.Width = 131
        EditLabel.Height = 13
        EditLabel.Caption = 'sobj_r0_mv_min_similar_th: '
        LabelPosition = lpLeft
        LabelSpacing = 3
        TabOrder = 7
        RegStartAddress = '0xE000095E'
        RegBits = 8
        TextType = ttInt
      end
      object RegLabeledEdit32: TRegLabeledEdit
        Left = 400
        Top = 92
        Width = 106
        Height = 21
        EditLabel.Width = 134
        EditLabel.Height = 13
        EditLabel.Caption = 'sobj_r0_mv_max_similar_th: '
        LabelPosition = lpLeft
        LabelSpacing = 3
        TabOrder = 8
        RegStartAddress = '0xE000095F'
        RegBits = 8
        TextType = ttInt
      end
    end
    object GroupBox6: TGroupBox
      Left = 2
      Top = 153
      Width = 529
      Height = 121
      Caption = 'rule 1'
      TabOrder = 5
      object RegCheckBox26: TRegCheckBox
        Left = 128
        Top = 8
        Width = 121
        Height = 17
        Caption = 'sobj_r1_ip_sad_and'
        TabOrder = 0
        RegAddress = '0xE0000957'
        RegBit = 7
      end
      object RegCheckBox27: TRegCheckBox
        Left = 128
        Top = 24
        Width = 113
        Height = 17
        Caption = 'sobj_r1_ip_dtl_and'
        TabOrder = 1
        RegAddress = '0xE0000957'
        RegBit = 6
      end
      object RegLabeledEdit36: TRegLabeledEdit
        Left = 128
        Top = 44
        Width = 106
        Height = 21
        EditLabel.Width = 86
        EditLabel.Height = 13
        EditLabel.Caption = 'sobj_r1_ip_dtl_th: '
        LabelPosition = lpLeft
        LabelSpacing = 3
        TabOrder = 2
        RegStartAddress = '0xE0000957'
        RegBits = 3
        TextType = ttInt
      end
      object RegLabeledEdit37: TRegLabeledEdit
        Left = 128
        Top = 68
        Width = 106
        Height = 21
        EditLabel.Width = 92
        EditLabel.Height = 13
        EditLabel.Caption = 'sobj_r1_ip_sad_th: '
        LabelPosition = lpLeft
        LabelSpacing = 3
        TabOrder = 3
        RegStartAddress = '0xE0000955'
        RegBits = 13
        TextType = ttInt
      end
      object RegLabeledEdit38: TRegLabeledEdit
        Left = 128
        Top = 92
        Width = 106
        Height = 21
        EditLabel.Width = 100
        EditLabel.Height = 13
        EditLabel.Caption = 'sobj_r1_ip_static_th: '
        LabelPosition = lpLeft
        LabelSpacing = 3
        TabOrder = 4
        RegStartAddress = '0xE0000954'
        RegBits = 8
        TextType = ttInt
      end
      object RegLabeledEdit39: TRegLabeledEdit
        Left = 400
        Top = 20
        Width = 106
        Height = 21
        EditLabel.Width = 116
        EditLabel.Height = 13
        EditLabel.Caption = 'sobj_r1_mv_trend_th_x: '
        LabelPosition = lpLeft
        LabelSpacing = 3
        TabOrder = 5
        RegStartAddress = '0xE0000960'
        RegBits = 8
        TextType = ttInt
      end
      object RegLabeledEdit40: TRegLabeledEdit
        Left = 400
        Top = 44
        Width = 106
        Height = 21
        EditLabel.Width = 127
        EditLabel.Height = 13
        EditLabel.Caption = 'sobj_r1_mv_trend_gain_x: '
        LabelPosition = lpLeft
        LabelSpacing = 3
        TabOrder = 6
        RegStartAddress = '0xE0000961'
        RegBits = 8
        TextType = ttInt
      end
    end
    object GroupBox7: TGroupBox
      Left = 2
      Top = 273
      Width = 529
      Height = 121
      Caption = 'rule 2'
      TabOrder = 6
      object RegCheckBox28: TRegCheckBox
        Left = 128
        Top = 8
        Width = 121
        Height = 17
        Caption = 'sobj_r2_ip_sad_and'
        TabOrder = 0
        RegAddress = '0xE000095B'
        RegBit = 7
      end
      object RegCheckBox29: TRegCheckBox
        Left = 128
        Top = 24
        Width = 113
        Height = 17
        Caption = 'sobj_r2_ip_dtl_and'
        TabOrder = 1
        RegAddress = '0xE000095B'
        RegBit = 6
      end
      object RegLabeledEdit43: TRegLabeledEdit
        Left = 128
        Top = 44
        Width = 106
        Height = 21
        EditLabel.Width = 86
        EditLabel.Height = 13
        EditLabel.Caption = 'sobj_r2_ip_dtl_th: '
        LabelPosition = lpLeft
        LabelSpacing = 3
        TabOrder = 2
        RegStartAddress = '0xE000095B'
        RegBits = 3
        TextType = ttInt
      end
      object RegLabeledEdit44: TRegLabeledEdit
        Left = 128
        Top = 68
        Width = 106
        Height = 21
        EditLabel.Width = 92
        EditLabel.Height = 13
        EditLabel.Caption = 'sobj_r2_ip_sad_th: '
        LabelPosition = lpLeft
        LabelSpacing = 3
        TabOrder = 3
        RegStartAddress = '0xE0000959'
        RegBits = 13
        TextType = ttInt
      end
      object RegLabeledEdit45: TRegLabeledEdit
        Left = 128
        Top = 92
        Width = 106
        Height = 21
        EditLabel.Width = 100
        EditLabel.Height = 13
        EditLabel.Caption = 'sobj_r2_ip_static_th: '
        LabelPosition = lpLeft
        LabelSpacing = 3
        TabOrder = 4
        RegStartAddress = '0xE0000958'
        RegBits = 8
        TextType = ttInt
      end
      object RegLabeledEdit46: TRegLabeledEdit
        Left = 400
        Top = 20
        Width = 106
        Height = 21
        EditLabel.Width = 116
        EditLabel.Height = 13
        EditLabel.Caption = 'sobj_r2_mv_trend_th_y: '
        LabelPosition = lpLeft
        LabelSpacing = 3
        TabOrder = 5
        RegStartAddress = '0xE0000962'
        RegBits = 8
        TextType = ttInt
      end
      object RegLabeledEdit47: TRegLabeledEdit
        Left = 400
        Top = 44
        Width = 106
        Height = 21
        EditLabel.Width = 130
        EditLabel.Height = 13
        EditLabel.Caption = 'sobj_r2_mv_trend_gain_y:  '
        LabelPosition = lpLeft
        LabelSpacing = 3
        TabOrder = 6
        RegStartAddress = '0xE0000963'
        RegBits = 8
        TextType = ttInt
      end
    end
  end
  object btnRefresh: TButton
    Left = 792
    Top = 424
    Width = 75
    Height = 25
    Caption = 'Refresh'
    TabOrder = 4
    OnClick = btnRefreshClick
  end
end
