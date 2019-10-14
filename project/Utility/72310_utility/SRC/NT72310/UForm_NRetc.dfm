inherited Form_NRetc: TForm_NRetc
  Left = 274
  Top = 2
  Width = 933
  Height = 737
  Caption = 'LOGO'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 48
    Top = 24
    Width = 137
    Height = 201
    Caption = 'NR_STE_post'
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 16
      Width = 46
      Height = 13
      Caption = 'sum_thd: '
    end
    object Label2: TLabel
      Left = 8
      Top = 168
      Width = 61
      Height = 13
      Caption = 'NR_nb_thd: '
    end
    object Edit1: TRegEdit
      Left = 64
      Top = 16
      Width = 25
      Height = 21
      TabOrder = 0
      Text = '4'
      OnChange = Edit1Change
      RegStartAddress = '0xE0000C03'
      RegBits = 3
      RegStart = 5
      TextType = ttInt
    end
    object CheckBox1: TRegCheckBox
      Left = 8
      Top = 40
      Width = 97
      Height = 17
      Caption = 'line0'
      Checked = True
      State = cbChecked
      TabOrder = 1
      OnClick = CheckBox1Click
      RegAddress = '0xE0000C01'
    end
    object CheckBox2: TRegCheckBox
      Left = 8
      Top = 64
      Width = 97
      Height = 17
      Caption = 'line1'
      Checked = True
      State = cbChecked
      TabOrder = 2
      OnClick = CheckBox2Click
      RegAddress = '0xE0000C01'
      RegBit = 2
    end
    object CheckBox3: TRegCheckBox
      Left = 8
      Top = 88
      Width = 97
      Height = 17
      Caption = 'corner'
      Checked = True
      State = cbChecked
      TabOrder = 3
      OnClick = CheckBox3Click
      RegAddress = '0xE0000C01'
      RegBit = 1
    end
    object RadioButton1: TRegRadioButton
      Left = 8
      Top = 112
      Width = 73
      Height = 17
      Caption = 'LPF_111'
      TabOrder = 4
      OnClick = RadioButton1Click
      RegAddress = '0xE0000C00'
      RegValue = '0x00000000'
      RegMask = '0x00001000'
    end
    object RadioButton2: TRegRadioButton
      Left = 8
      Top = 128
      Width = 73
      Height = 17
      Caption = 'LPF_121'
      TabOrder = 5
      OnClick = RadioButton2Click
      RegAddress = '0xE0000C00'
      RegValue = '0xFFFFFFFF'
      RegMask = '0x00001000'
    end
    object Edit2: TRegEdit
      Left = 72
      Top = 168
      Width = 49
      Height = 21
      TabOrder = 6
      Text = '0'
      OnChange = Edit2Change
      RegStartAddress = '0xE0000C02'
      RegBits = 4
      RegStart = 4
      TextType = ttInt
    end
    object CheckBox9: TRegCheckBox
      Left = 64
      Top = 88
      Width = 57
      Height = 17
      Caption = 'OR_all'
      TabOrder = 7
      OnClick = CheckBox9Click
      RegAddress = '0xE0000C01'
      RegBit = 3
    end
    object CheckBox10: TRegCheckBox
      Left = 8
      Top = 144
      Width = 97
      Height = 17
      Caption = 'center_only'
      Checked = True
      State = cbChecked
      TabOrder = 8
      OnClick = CheckBox10Click
      RegAddress = '0xE0000C03'
      RegBit = 4
    end
  end
  object GroupBox2: TGroupBox
    Left = 48
    Top = 232
    Width = 137
    Height = 393
    Caption = 'NR_iir'
    TabOrder = 1
    object Label3: TLabel
      Left = 8
      Top = 24
      Width = 49
      Height = 13
      Caption = 'pos_step: '
    end
    object Label4: TLabel
      Left = 8
      Top = 48
      Width = 50
      Height = 13
      Caption = 'neg_step: '
    end
    object Label5: TLabel
      Left = 8
      Top = 192
      Width = 56
      Height = 13
      Caption = 'NR_iir_thd: '
    end
    object Label27: TLabel
      Left = 104
      Top = 192
      Width = 11
      Height = 13
      Caption = 'x4'
    end
    object Edit3: TRegEdit
      Left = 56
      Top = 16
      Width = 41
      Height = 21
      TabOrder = 0
      Text = '8'
      RegStartAddress = '0xE0000CA6'
      RegBits = 4
      TextType = ttInt
    end
    object CheckBox4: TRegCheckBox
      Left = 8
      Top = 72
      Width = 65
      Height = 17
      Caption = 'fast_clr'
      TabOrder = 1
      RegAddress = '0xE0000C8E'
      RegBit = 2
    end
    object CheckBox5: TRegCheckBox
      Left = 8
      Top = 96
      Width = 65
      Height = 17
      Caption = 'iir_en'
      TabOrder = 2
      RegAddress = '0xE0000C8E'
      RegBit = 3
    end
    object CheckBox6: TRegCheckBox
      Left = 8
      Top = 120
      Width = 97
      Height = 17
      Caption = 'regional_clr'
      TabOrder = 3
    end
    object CheckBox7: TRegCheckBox
      Left = 8
      Top = 168
      Width = 97
      Height = 17
      Caption = 'frame_clr'
      TabOrder = 4
      OnClick = CheckBox7Click
      RegAddress = '0xE0000C8E'
      RegBit = 1
    end
    object Edit5: TRegEdit
      Left = 64
      Top = 184
      Width = 41
      Height = 21
      TabOrder = 5
      Text = 'F0'
      OnChange = Edit5Change
      RegStartAddress = '0xE0000C8F'
      RegBits = 8
      TextType = ttInt
    end
    object CheckBox8: TRegCheckBox
      Left = 8
      Top = 144
      Width = 97
      Height = 17
      Caption = 'current_out'
      TabOrder = 6
      OnClick = CheckBox8Click
      RegAddress = '0xE0000C8E'
    end
    object Edit4: TRegEdit
      Left = 56
      Top = 40
      Width = 41
      Height = 21
      TabOrder = 7
      Text = '40'
      RegStartAddress = '0xE0000CA7'
      RegBits = 8
      TextType = ttInt
    end
    object GroupBox3: TGroupBox
      Left = 8
      Top = 208
      Width = 121
      Height = 81
      Caption = 'HW vanish'
      TabOrder = 8
      object Label6: TLabel
        Left = 8
        Top = 20
        Width = 43
        Height = 13
        Caption = 'sur_sad: '
      end
      object Label7: TLabel
        Left = 8
        Top = 60
        Width = 59
        Height = 13
        Caption = 'cur-pre sad: '
      end
      object Edit6: TRegEdit
        Left = 64
        Top = 20
        Width = 41
        Height = 21
        TabOrder = 0
        Text = 'Edit6'
        RegStartAddress = '0xE0000CA9'
        RegBits = 8
        TextType = ttInt
      end
      object Edit7: TRegEdit
        Left = 64
        Top = 52
        Width = 41
        Height = 21
        TabOrder = 1
        Text = 'Edit7'
        RegStartAddress = '0xE0000CA8'
        RegBits = 8
        TextType = ttInt
      end
    end
    object GroupBox4: TGroupBox
      Left = 8
      Top = 296
      Width = 121
      Height = 89
      Caption = 'SW vanish'
      TabOrder = 9
    end
  end
  object GroupBox5: TGroupBox
    Left = 192
    Top = 24
    Width = 345
    Height = 281
    Caption = 'NR_readback'
    TabOrder = 2
    object Label8: TLabel
      Left = 16
      Top = 24
      Width = 43
      Height = 13
      Caption = 'regional: '
    end
    object Label10: TLabel
      Left = 16
      Top = 48
      Width = 47
      Height = 13
      Caption = 'region_00'
      OnClick = Label10Click
    end
    object Label11: TLabel
      Left = 96
      Top = 48
      Width = 47
      Height = 13
      Caption = 'region_01'
    end
    object Label12: TLabel
      Left = 176
      Top = 48
      Width = 47
      Height = 13
      Caption = 'region_02'
    end
    object Label13: TLabel
      Left = 256
      Top = 48
      Width = 47
      Height = 13
      Caption = 'region_03'
    end
    object Label14: TLabel
      Tag = 100
      Left = 16
      Top = 64
      Width = 47
      Height = 13
      Caption = 'region_10'
      OnClick = Label14Click
    end
    object Label15: TLabel
      Tag = 100
      Left = 96
      Top = 64
      Width = 47
      Height = 13
      Caption = 'region_11'
      OnClick = Label15Click
    end
    object Label16: TLabel
      Tag = 100
      Left = 176
      Top = 64
      Width = 47
      Height = 13
      Caption = 'region_12'
      OnClick = Label16Click
    end
    object Label17: TLabel
      Tag = 100
      Left = 256
      Top = 64
      Width = 47
      Height = 13
      Caption = 'region_13'
    end
    object Label18: TLabel
      Left = 16
      Top = 80
      Width = 47
      Height = 13
      Caption = 'region_20'
      OnClick = Label18Click
    end
    object Label19: TLabel
      Left = 96
      Top = 80
      Width = 47
      Height = 13
      Caption = 'region_21'
    end
    object Label20: TLabel
      Left = 176
      Top = 80
      Width = 47
      Height = 13
      Caption = 'region_22'
    end
    object Label22: TLabel
      Left = 16
      Top = 216
      Width = 49
      Height = 13
      Caption = 'iir_nr_cnt: '
    end
    object Label23: TLabel
      Left = 16
      Top = 240
      Width = 57
      Height = 13
      Caption = 'cur_nr_cnt: '
    end
    object Label21: TLabel
      Left = 258
      Top = 80
      Width = 47
      Height = 13
      Caption = 'region_23'
    end
    object Label9: TLabel
      Left = 78
      Top = 24
      Width = 41
      Height = 13
      AutoSize = False
      Caption = 'sad'
    end
    object RadioButton4: TRegRadioButton
      Left = 120
      Top = 24
      Width = 97
      Height = 17
      Caption = 'force_read_nr'
      TabOrder = 0
      OnClick = RadioButton4Click
      RegAddress = '0xE0000C8C'
      RegValue = '0x00800000'
      RegMask = '0x00800000'
    end
    object RadioButton5: TRegRadioButton
      Left = 224
      Top = 24
      Width = 97
      Height = 17
      Caption = 'force_read_sad'
      TabOrder = 1
      OnClick = RadioButton5Click
      RegAddress = '0xE0000C8E'
      RegValue = '0'
      RegMask = '0x00800000'
    end
    object RegEdit1: TRegEdit
      Left = 85
      Top = 236
      Width = 108
      Height = 21
      TabOrder = 2
      Text = '8'
      RegStartAddress = '0xE000060C'
      RegBits = 24
      TextType = ttInt
    end
    object RegEdit2: TRegEdit
      Left = 85
      Top = 212
      Width = 108
      Height = 21
      TabOrder = 3
      Text = '8'
      RegStartAddress = '0xE0000C9E'
      RegBits = 16
      TextType = ttInt
    end
    object RegEdit3: TRegEdit
      Left = 13
      Top = 100
      Width = 52
      Height = 21
      TabOrder = 4
      Text = '8'
      RegStartAddress = '0xE0000CAC'
      RegBits = 16
      TextType = ttInt
    end
    object RegEdit4: TRegEdit
      Left = 85
      Top = 100
      Width = 52
      Height = 21
      TabOrder = 5
      Text = '8'
      RegStartAddress = '0xE0000CAE'
      RegBits = 16
      TextType = ttInt
    end
    object RegEdit5: TRegEdit
      Left = 165
      Top = 100
      Width = 68
      Height = 21
      TabOrder = 6
      Text = '8'
      RegStartAddress = '0xE0000CB0'
      RegBits = 16
      TextType = ttInt
    end
    object RegEdit6: TRegEdit
      Left = 253
      Top = 100
      Width = 76
      Height = 21
      TabOrder = 7
      Text = '8'
      RegStartAddress = '0xE0000CB2'
      RegBits = 16
      TextType = ttInt
    end
    object RegEdit7: TRegEdit
      Tag = 100
      Left = 13
      Top = 124
      Width = 52
      Height = 21
      TabOrder = 8
      Text = '8'
      RegStartAddress = '0xE0000CB4'
      RegBits = 16
      TextType = ttInt
    end
    object RegEdit8: TRegEdit
      Tag = 101
      Left = 85
      Top = 124
      Width = 52
      Height = 21
      TabOrder = 9
      Text = '8'
      RegStartAddress = '0xE0000CB4'
      RegBits = 16
      TextType = ttInt
    end
    object RegEdit9: TRegEdit
      Tag = 110
      Left = 165
      Top = 124
      Width = 68
      Height = 21
      TabOrder = 10
      Text = '8'
      RegStartAddress = '0xE0000CB6'
      RegBits = 16
      TextType = ttInt
    end
    object RegEdit10: TRegEdit
      Tag = 111
      Left = 253
      Top = 124
      Width = 76
      Height = 21
      TabOrder = 11
      Text = '8'
      RegStartAddress = '0xE0000CB6'
      RegBits = 16
      TextType = ttInt
    end
    object RegEdit11: TRegEdit
      Left = 13
      Top = 148
      Width = 52
      Height = 21
      TabOrder = 12
      Text = '8'
      RegStartAddress = '0xE0000CB8'
      RegBits = 16
      TextType = ttInt
    end
    object RegEdit12: TRegEdit
      Left = 85
      Top = 148
      Width = 52
      Height = 21
      TabOrder = 13
      Text = '8'
      RegStartAddress = '0xE0000CBA'
      RegBits = 16
      TextType = ttInt
    end
    object RegEdit13: TRegEdit
      Left = 165
      Top = 148
      Width = 68
      Height = 21
      TabOrder = 14
      Text = '8'
      RegStartAddress = '0xE0000CBC'
      RegBits = 16
      TextType = ttInt
    end
    object RegEdit14: TRegEdit
      Left = 253
      Top = 148
      Width = 76
      Height = 21
      TabOrder = 15
      Text = '8'
      RegStartAddress = '0xE0000CBE'
      RegBits = 16
      TextType = ttInt
    end
  end
  object GroupBox6: TGroupBox
    Left = 704
    Top = 216
    Width = 185
    Height = 113
    Caption = 'SAD curve'
    TabOrder = 3
    object nr1_sad_limit: TRegLabeledEdit
      Left = 72
      Top = 80
      Width = 73
      Height = 21
      EditLabel.Width = 61
      EditLabel.Height = 13
      EditLabel.Caption = 'nr1_sad_limit'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 0
      RegStartAddress = '0xE0000C2F'
      RegBits = 4
      TextType = ttInt
    end
    object sad_thd1: TRegLabeledEdit
      Left = 16
      Top = 36
      Width = 49
      Height = 21
      EditLabel.Width = 44
      EditLabel.Height = 13
      EditLabel.Caption = 'sad_thd1'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 1
      OnChange = sad_thd1Change
      RegStartAddress = '0xE0000C58'
      RegBits = 4
      RegStart = 4
      TextType = ttInt
    end
    object sad_thd2: TRegLabeledEdit
      Left = 16
      Top = 76
      Width = 49
      Height = 21
      EditLabel.Width = 44
      EditLabel.Height = 13
      EditLabel.Caption = 'sad_thd2'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 2
      RegStartAddress = '0xE0000C58'
      RegBits = 4
      TextType = ttInt
    end
    object nr0_sad_limit: TRegLabeledEdit
      Left = 72
      Top = 36
      Width = 73
      Height = 21
      EditLabel.Width = 61
      EditLabel.Height = 13
      EditLabel.Caption = 'nr0_sad_limit'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 3
      RegStartAddress = '0xE0000C56'
      RegBits = 4
      RegStart = 4
      TextType = ttInt
    end
  end
  object ME_STE: TGroupBox
    Left = 192
    Top = 312
    Width = 185
    Height = 193
    Caption = 'ME_STE curve'
    TabOrder = 4
    object Label26: TLabel
      Left = 8
      Top = 24
      Width = 91
      Height = 13
      Caption = 'ste_dir: (h,v) = (1,1)'
      OnClick = Label26Click
    end
    object RadioButton6: TRegRadioButton
      Left = 8
      Top = 40
      Width = 81
      Height = 17
      Caption = 'force H ste'
      TabOrder = 0
      OnClick = RadioButton6Click
      RegAddress = '0xE0000C00'
      RegValue = '0xFFFFFFFF'
      RegMask = '0x00004000'
    end
    object RadioButton7: TRegRadioButton
      Left = 88
      Top = 40
      Width = 81
      Height = 17
      Caption = 'force V ste'
      TabOrder = 1
      OnClick = RadioButton7Click
      RegAddress = '0xE0000C00'
      RegValue = '0xFFFFFFFF'
      RegMask = '0x00002000'
    end
    object transi_thd: TRegLabeledEdit
      Left = 8
      Top = 80
      Width = 49
      Height = 21
      EditLabel.Width = 46
      EditLabel.Height = 13
      EditLabel.Caption = 'transi_thd'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 2
      Text = '6'
      OnChange = transi_thdChange
      RegStartAddress = '0xE0000C5E'
      RegBits = 8
      TextType = ttInt
    end
    object ste_thd1: TRegLabeledEdit
      Left = 8
      Top = 120
      Width = 49
      Height = 21
      EditLabel.Width = 41
      EditLabel.Height = 13
      EditLabel.Caption = 'ste_thd1'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 3
      Text = '14'
      RegStartAddress = '0xE0000C5B'
      RegBits = 8
      TextType = ttInt
    end
    object ste_thd2: TRegLabeledEdit
      Left = 64
      Top = 120
      Width = 49
      Height = 21
      EditLabel.Width = 41
      EditLabel.Height = 13
      EditLabel.Caption = 'ste_thd2'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 4
      Text = '20'
      OnChange = ste_thd2Change
      RegStartAddress = '0xE0000C5C'
      RegBits = 8
      TextType = ttInt
    end
    object watershed: TRegLabeledEdit
      Left = 8
      Top = 160
      Width = 49
      Height = 21
      EditLabel.Width = 49
      EditLabel.Height = 13
      EditLabel.Caption = 'watershed'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 5
      Text = '16'
      OnChange = watershedChange
      RegStartAddress = '0xE0000C5A'
      RegBits = 6
      TextType = ttInt
    end
    object weitght: TRegLabeledEdit
      Left = 64
      Top = 160
      Width = 49
      Height = 21
      EditLabel.Width = 34
      EditLabel.Height = 13
      EditLabel.Caption = 'weitght'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 6
      Text = '0.3'
      TextType = ttInt
    end
    object slope2: TRegLabeledEdit
      Left = 120
      Top = 160
      Width = 41
      Height = 21
      EditLabel.Width = 31
      EditLabel.Height = 13
      EditLabel.Caption = 'slope2'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 7
      Text = '2'
      OnChange = slope2Change
      RegStartAddress = '0xE0000C5D'
      RegBits = 6
      RegStart = 4
      TextType = ttInt
    end
    object slope1: TRegLabeledEdit
      Left = 120
      Top = 120
      Width = 41
      Height = 21
      EditLabel.Width = 31
      EditLabel.Height = 13
      EditLabel.Caption = 'slope1'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 8
      Text = '3'
      RegStartAddress = '0xE0000C5D'
      RegBits = 3
      RegStart = 4
      TextType = ttInt
    end
  end
  object action: TGroupBox
    Left = 752
    Top = 384
    Width = 153
    Height = 145
    Caption = 'Action curve'
    TabOrder = 5
    object nr_action: TRegLabeledEdit
      Left = 8
      Top = 32
      Width = 49
      Height = 21
      EditLabel.Width = 44
      EditLabel.Height = 13
      EditLabel.Caption = 'nr_action'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 0
      OnChange = nr_actionChange
      RegStartAddress = '0xE0000C17'
      RegBits = 6
      TextType = ttInt
    end
    object action_thd1: TRegLabeledEdit
      Left = 8
      Top = 72
      Width = 57
      Height = 21
      EditLabel.Width = 56
      EditLabel.Height = 13
      EditLabel.Caption = 'action_thd1'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 1
      RegStartAddress = '0xE0000C13'
      RegBits = 6
      TextType = ttInt
    end
    object action_thd2: TRegLabeledEdit
      Left = 72
      Top = 72
      Width = 57
      Height = 21
      EditLabel.Width = 56
      EditLabel.Height = 13
      EditLabel.Caption = 'action_thd2'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 2
      RegStartAddress = '0xE0000C14'
      RegBits = 6
      TextType = ttInt
    end
    object pos_out: TRegLabeledEdit
      Left = 8
      Top = 112
      Width = 57
      Height = 21
      EditLabel.Width = 38
      EditLabel.Height = 13
      EditLabel.Caption = 'pos_out'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 3
      RegStartAddress = '0xE0000C16'
      RegBits = 6
      TextType = ttInt
    end
    object neg_out: TRegLabeledEdit
      Left = 72
      Top = 112
      Width = 57
      Height = 21
      EditLabel.Width = 39
      EditLabel.Height = 13
      EditLabel.Caption = 'neg_out'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 4
      RegStartAddress = '0xE0000C15'
      RegBits = 6
      TextType = ttInt
    end
  end
  object Smv: TGroupBox
    Left = 392
    Top = 344
    Width = 321
    Height = 169
    Caption = 'Smv'
    TabOrder = 6
    object center: TRegCheckBox
      Left = 8
      Top = 64
      Width = 57
      Height = 17
      Caption = 'center'
      TabOrder = 0
      RegAddress = '0xE0000C32'
      RegBit = 7
    end
    object smv_en: TRegCheckBox
      Left = 8
      Top = 24
      Width = 65
      Height = 17
      Caption = 'smv_en'
      TabOrder = 1
      OnClick = smv_enClick
      RegAddress = '0xE0000C10'
      RegBit = 3
    end
    object smv_clr_step: TRegLabeledEdit
      Left = 80
      Top = 24
      Width = 65
      Height = 21
      EditLabel.Width = 62
      EditLabel.Height = 13
      EditLabel.Caption = 'smv_clr_step'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 2
      OnChange = smv_clr_stepChange
      RegStartAddress = '0xE0000C3F'
      RegBits = 6
      TextType = ttInt
    end
    object v0: TRegLabeledEdit
      Left = 80
      Top = 64
      Width = 25
      Height = 21
      EditLabel.Width = 12
      EditLabel.Height = 13
      EditLabel.Caption = 'v0'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 3
      RegStartAddress = '0xE0000C33'
      RegBits = 8
      TextType = ttInt
    end
    object v1: TRegLabeledEdit
      Left = 104
      Top = 64
      Width = 25
      Height = 21
      EditLabel.Width = 12
      EditLabel.Height = 13
      EditLabel.Caption = 'v1'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 4
      RegStartAddress = '0xE0000C34'
      RegBits = 8
      TextType = ttInt
    end
    object v2: TRegLabeledEdit
      Left = 128
      Top = 64
      Width = 25
      Height = 21
      EditLabel.Width = 12
      EditLabel.Height = 13
      EditLabel.Caption = 'v2'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 5
      RegStartAddress = '0xE0000C35'
      RegBits = 8
      TextType = ttInt
    end
    object v3: TRegLabeledEdit
      Left = 152
      Top = 64
      Width = 25
      Height = 21
      EditLabel.Width = 12
      EditLabel.Height = 13
      EditLabel.Caption = 'v3'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 6
      OnChange = v3Change
      RegStartAddress = '0xE0000C36'
      RegBits = 8
      TextType = ttInt
    end
    object h0: TRegLabeledEdit
      Left = 80
      Top = 104
      Width = 25
      Height = 21
      EditLabel.Width = 12
      EditLabel.Height = 13
      EditLabel.Caption = 'h0'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 7
      RegStartAddress = '0xE0000C37'
      RegBits = 8
      TextType = ttInt
    end
    object h1: TRegLabeledEdit
      Left = 104
      Top = 104
      Width = 25
      Height = 21
      EditLabel.Width = 12
      EditLabel.Height = 13
      EditLabel.Caption = 'h1'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 8
      RegStartAddress = '0xE0000C38'
      RegBits = 8
      TextType = ttInt
    end
    object h2: TRegLabeledEdit
      Left = 128
      Top = 104
      Width = 25
      Height = 21
      EditLabel.Width = 12
      EditLabel.Height = 13
      EditLabel.Caption = 'h2'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 9
      RegStartAddress = '0xE0000C39'
      RegBits = 8
      TextType = ttInt
    end
    object h3: TRegLabeledEdit
      Left = 152
      Top = 104
      Width = 25
      Height = 21
      EditLabel.Width = 12
      EditLabel.Height = 13
      EditLabel.Caption = 'h3'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 10
      RegStartAddress = '0xE0000C3A'
      RegBits = 8
      TextType = ttInt
    end
    object smv_thd: TRegLabeledEdit
      Left = 152
      Top = 24
      Width = 49
      Height = 21
      EditLabel.Width = 40
      EditLabel.Height = 13
      EditLabel.Caption = 'smv_thd'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 11
      RegStartAddress = '0xE0000C31'
      RegBits = 6
      TextType = ttInt
    end
    object zmv_thd: TRegLabeledEdit
      Left = 208
      Top = 24
      Width = 49
      Height = 21
      EditLabel.Width = 40
      EditLabel.Height = 13
      EditLabel.Caption = 'zmv_thd'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 12
      RegStartAddress = '0xE0000C30'
      RegBits = 6
      TextType = ttInt
    end
    object inner_nr0_smv0: TRegCheckBox
      Left = 8
      Top = 136
      Width = 97
      Height = 17
      Caption = 'inner_nr0_smv0'
      TabOrder = 13
      OnClick = inner_nr0_smv0Click
      RegAddress = '0xE0000C11'
    end
    object inner_nr1_smv1: TRegCheckBox
      Left = 112
      Top = 136
      Width = 97
      Height = 17
      Caption = 'inner_nr1_smv1'
      TabOrder = 14
      RegAddress = '0xE0000C11'
      RegBit = 1
    end
    object outer_nr1_smv1: TRegCheckBox
      Left = 216
      Top = 136
      Width = 97
      Height = 17
      Caption = 'outer_nr1_smv1'
      TabOrder = 15
      RegAddress = '0xE0000C11'
      RegBit = 2
    end
  end
  object Pan_clr: TGroupBox
    Left = 192
    Top = 512
    Width = 193
    Height = 129
    Caption = 'Pan_clr'
    TabOrder = 7
    object mv_diff: TRegLabeledEdit
      Left = 8
      Top = 56
      Width = 57
      Height = 21
      EditLabel.Width = 34
      EditLabel.Height = 13
      EditLabel.Caption = 'mv_diff'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 0
      RegStartAddress = '0xE0000C51'
      RegBits = 8
      TextType = ttInt
    end
    object mv_len: TRegLabeledEdit
      Left = 64
      Top = 56
      Width = 57
      Height = 21
      EditLabel.Width = 34
      EditLabel.Height = 13
      EditLabel.Caption = 'mv_len'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 1
      RegStartAddress = '0xE0000C50'
      RegBits = 8
      TextType = ttInt
    end
    object mv_cnt_thd: TRegLabeledEdit
      Left = 120
      Top = 56
      Width = 57
      Height = 21
      EditLabel.Width = 56
      EditLabel.Height = 13
      EditLabel.Caption = 'mv_cnt_thd'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 2
      RegStartAddress = '0xE0000C52'
      RegBits = 6
      TextType = ttInt
    end
    object pan_clr_en: TRegCheckBox
      Left = 8
      Top = 24
      Width = 81
      Height = 17
      Caption = 'pan_clr_en'
      TabOrder = 3
      OnClick = pan_clr_enClick
      RegAddress = '0xE0000C10'
      RegBit = 7
    end
    object nr0_pan_clr_step: TRegLabeledEdit
      Left = 8
      Top = 96
      Width = 81
      Height = 21
      EditLabel.Width = 82
      EditLabel.Height = 13
      EditLabel.Caption = 'nr0_pan_clr_step'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 4
      RegStartAddress = '0xE0000C53'
      RegBits = 6
      TextType = ttInt
    end
    object nr1_pan_clr_step: TRegLabeledEdit
      Left = 96
      Top = 96
      Width = 89
      Height = 21
      EditLabel.Width = 82
      EditLabel.Height = 13
      EditLabel.Caption = 'nr1_pan_clr_step'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 5
      RegStartAddress = '0xE0000CAA'
      RegBits = 6
      TextType = ttInt
    end
  end
  object Outpost: TGroupBox
    Left = 544
    Top = 24
    Width = 97
    Height = 217
    Caption = 'Outpost'
    TabOrder = 8
    object LPF_181: TRegRadioButton
      Left = 8
      Top = 24
      Width = 73
      Height = 17
      Caption = 'LPF_181'
      TabOrder = 0
      OnClick = LPF_181Click
      RegAddress = '0xE0000540'
      RegValue = '0xFFFFFFFF'
      RegMask = '0x00400000'
    end
    object LPF_121: TRegRadioButton
      Left = 8
      Top = 48
      Width = 65
      Height = 17
      Caption = 'LPF_121'
      TabOrder = 1
      OnClick = LPF_121Click
      RegAddress = '0xE0000540'
      RegValue = '0'
      RegMask = '0x00400000'
    end
    object low_bound: TRegLabeledEdit
      Left = 8
      Top = 104
      Width = 65
      Height = 21
      EditLabel.Width = 52
      EditLabel.Height = 13
      EditLabel.Caption = 'low_bound'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 2
      RegStartAddress = '0xE0000546'
      RegBits = 6
      TextType = ttInt
    end
    object slope: TRegLabeledEdit
      Left = 8
      Top = 144
      Width = 65
      Height = 21
      EditLabel.Width = 25
      EditLabel.Height = 13
      EditLabel.Caption = 'slope'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 3
      RegStartAddress = '0xE0000547'
      RegBits = 3
      TextType = ttInt
    end
    object lv_thd: TRegLabeledEdit
      Left = 8
      Top = 184
      Width = 65
      Height = 21
      EditLabel.Width = 29
      EditLabel.Height = 13
      EditLabel.Caption = 'lv_thd'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 4
      RegStartAddress = '0xE000054A'
      RegBits = 3
      TextType = ttInt
    end
    object RegCheckBox1: TRegCheckBox
      Left = 8
      Top = 72
      Width = 81
      Height = 17
      Caption = 'center_only'
      Checked = True
      State = cbChecked
      TabOrder = 5
      OnClick = CheckBox10Click
      RegAddress = '0xE0000542'
      RegBit = 5
    end
  end
  object PTL: TGroupBox
    Left = 648
    Top = 24
    Width = 105
    Height = 153
    Caption = 'PTL'
    TabOrder = 9
    object org: TRegCheckBox
      Left = 8
      Top = 24
      Width = 49
      Height = 17
      Caption = 'org'
      TabOrder = 0
      OnClick = orgClick
      RegAddress = '0xE0000234'
      RegBit = 5
    end
    object OR_all: TRegCheckBox
      Left = 8
      Top = 48
      Width = 65
      Height = 17
      Caption = 'OR_all'
      TabOrder = 1
      RegAddress = '0xE0000234'
      RegBit = 6
    end
    object short_line: TRegCheckBox
      Left = 8
      Top = 72
      Width = 73
      Height = 17
      Caption = 'short_line'
      TabOrder = 2
      RegAddress = '0xE0000237'
    end
    object small_corner: TRegCheckBox
      Left = 8
      Top = 96
      Width = 89
      Height = 17
      Caption = 'small_corner'
      TabOrder = 3
      RegAddress = '0xE0000237'
      RegBit = 1
    end
    object diagonal_line: TRegCheckBox
      Left = 8
      Top = 120
      Width = 89
      Height = 17
      Caption = 'diagonal_line'
      TabOrder = 4
      RegAddress = '0xE0000237'
      RegBit = 2
    end
  end
  object btn_Refresh: TButton
    Left = 456
    Top = 600
    Width = 75
    Height = 25
    Caption = 'Refresh'
    TabOrder = 10
    OnClick = btn_RefreshClick
  end
end
