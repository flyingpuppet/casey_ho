inherited Frame_DataPath: TFrame_DataPath
  Width = 549
  Height = 514
  object Panel1: TPanel
    Left = 0
    Top = 96
    Width = 549
    Height = 418
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    object GB_MEY: TGroupBox
      Left = 2
      Top = 131
      Width = 165
      Height = 281
      Caption = 'ME_Y'
      TabOrder = 0
      object CB_MeY_DC_Bypass: TCheckBox
        Tag = 10
        Left = 8
        Top = 16
        Width = 81
        Height = 17
        Caption = 'DC_Bypass'
        TabOrder = 0
        OnClick = CB_MeY_DC_BypassClick
      end
      object CB_MeY_LastLine_Bypass: TCheckBox
        Tag = 20
        Left = 8
        Top = 32
        Width = 105
        Height = 17
        Caption = 'LastLine_Enable'
        TabOrder = 1
        OnClick = CB_MeY_DC_BypassClick
      end
      object GroupBox6: TGroupBox
        Left = 2
        Top = 80
        Width = 87
        Height = 199
        Caption = 'DC_ratio'
        TabOrder = 2
        object RB_MeY_DC_mode0: TRadioButton
          Tag = 30
          Left = 8
          Top = 16
          Width = 75
          Height = 17
          Caption = 'DC_Mode0'
          Checked = True
          TabOrder = 0
          TabStop = True
          OnClick = RB_MeY_DC_mode0Click
        end
        object RB_MeY_DC_mode1: TRadioButton
          Tag = 31
          Left = 8
          Top = 52
          Width = 75
          Height = 17
          Caption = 'DC_Mode1'
          TabOrder = 1
          OnClick = RB_MeY_DC_mode0Click
        end
        object RB_MeY_DC_mode2: TRadioButton
          Tag = 32
          Left = 8
          Top = 88
          Width = 75
          Height = 17
          Caption = 'DC_Mode2'
          TabOrder = 2
          OnClick = RB_MeY_DC_mode0Click
        end
        object RB_MeY_DC_mode3: TRadioButton
          Tag = 33
          Left = 8
          Top = 124
          Width = 75
          Height = 17
          Caption = 'DC_Mode3'
          TabOrder = 3
          OnClick = RB_MeY_DC_mode0Click
        end
        object RB_MeY_DC_mode4: TRadioButton
          Tag = 34
          Left = 8
          Top = 160
          Width = 75
          Height = 17
          Caption = 'DC_Mode4'
          TabOrder = 4
          Visible = False
          OnClick = RB_MeY_DC_mode0Click
        end
      end
      object CB_MeY_Debug: TCheckBox
        Left = 8
        Top = 48
        Width = 89
        Height = 17
        Caption = 'Debug Enable'
        TabOrder = 3
        OnClick = CB_MeY_DebugClick
      end
      object GroupBox8: TGroupBox
        Left = 89
        Top = 80
        Width = 73
        Height = 97
        Caption = 'Error Level'
        TabOrder = 4
        object RB_MeY_Error_0: TRadioButton
          Left = 8
          Top = 16
          Width = 63
          Height = 17
          Caption = 'Level 0'
          Checked = True
          TabOrder = 0
          TabStop = True
          OnClick = RB_MeY_Error_0Click
        end
        object RB_MeY_Error_1: TRadioButton
          Tag = 1
          Left = 8
          Top = 36
          Width = 63
          Height = 17
          Caption = 'Level 1'
          TabOrder = 1
          OnClick = RB_MeY_Error_0Click
        end
        object RB_MeY_Error_2: TRadioButton
          Tag = 2
          Left = 8
          Top = 56
          Width = 63
          Height = 17
          Caption = 'Level 2'
          TabOrder = 2
          OnClick = RB_MeY_Error_0Click
        end
        object RB_MeY_Error_3: TRadioButton
          Tag = 3
          Left = 8
          Top = 76
          Width = 63
          Height = 17
          Caption = 'Level 3'
          TabOrder = 3
          OnClick = RB_MeY_Error_0Click
        end
      end
      object GB_TP: TGroupBox
        Left = 89
        Top = 182
        Width = 74
        Height = 97
        Caption = 'Test Pattern'
        TabOrder = 5
        object RB_MeY_Test_0: TRadioButton
          Left = 8
          Top = 16
          Width = 63
          Height = 17
          Caption = 'Disable'
          Checked = True
          TabOrder = 0
          TabStop = True
          OnClick = RB_MeY_Test_0Click
        end
        object RB_MeY_Test_1: TRadioButton
          Tag = 1
          Left = 8
          Top = 36
          Width = 63
          Height = 17
          Caption = 'Ramp'
          TabOrder = 1
          OnClick = RB_MeY_Test_0Click
        end
        object RB_MeY_Test_2: TRadioButton
          Tag = 2
          Left = 8
          Top = 56
          Width = 63
          Height = 17
          Caption = 'W/B Bar'
          TabOrder = 2
          OnClick = RB_MeY_Test_0Click
        end
        object RB_MeY_Test_3: TRadioButton
          Tag = 3
          Left = 8
          Top = 76
          Width = 63
          Height = 17
          Caption = 'Gray'
          TabOrder = 3
          OnClick = RB_MeY_Test_0Click
        end
      end
    end
    object GB_MCY: TGroupBox
      Left = 167
      Top = 131
      Width = 165
      Height = 281
      Caption = 'MC_Y'
      TabOrder = 1
      object CB_McY_DC_Bypass: TCheckBox
        Tag = 11
        Left = 8
        Top = 16
        Width = 124
        Height = 17
        Caption = 'DC_Bypass'
        TabOrder = 0
        OnClick = CB_MeY_DC_BypassClick
      end
      object CB_McY_LastLine_Bypass: TCheckBox
        Tag = 21
        Left = 8
        Top = 32
        Width = 116
        Height = 17
        Caption = 'LastLine_Enable'
        TabOrder = 1
        OnClick = CB_MeY_DC_BypassClick
      end
      object GroupBox4: TGroupBox
        Left = 2
        Top = 80
        Width = 87
        Height = 199
        Caption = 'DC_ratio'
        TabOrder = 2
        object RB_McY_DC_mode0: TRadioButton
          Tag = 40
          Left = 8
          Top = 16
          Width = 73
          Height = 17
          Caption = 'DC_Mode0'
          Checked = True
          TabOrder = 0
          TabStop = True
          OnClick = RB_MeY_DC_mode0Click
        end
        object RB_McY_DC_mode1: TRadioButton
          Tag = 41
          Left = 8
          Top = 52
          Width = 73
          Height = 17
          Caption = 'DC_Mode1'
          TabOrder = 1
          OnClick = RB_MeY_DC_mode0Click
        end
        object RB_McY_DC_mode2: TRadioButton
          Tag = 42
          Left = 8
          Top = 88
          Width = 73
          Height = 17
          Caption = 'DC_Mode2'
          TabOrder = 2
          OnClick = RB_MeY_DC_mode0Click
        end
        object RB_McY_DC_mode3: TRadioButton
          Tag = 43
          Left = 8
          Top = 124
          Width = 73
          Height = 17
          Caption = 'DC_Mode3'
          TabOrder = 3
          OnClick = RB_MeY_DC_mode0Click
        end
        object RB_McY_DC_mode4: TRadioButton
          Tag = 44
          Left = 8
          Top = 160
          Width = 73
          Height = 17
          Caption = 'DC_Mode4'
          TabOrder = 4
          OnClick = RB_MeY_DC_mode0Click
        end
      end
      object GroupBox9: TGroupBox
        Left = 89
        Top = 80
        Width = 74
        Height = 97
        Caption = 'Error Level'
        TabOrder = 3
        object RB_McY_Error_0: TRadioButton
          Left = 8
          Top = 16
          Width = 64
          Height = 17
          Caption = 'Level 0'
          Checked = True
          TabOrder = 0
          TabStop = True
          OnClick = RB_McY_Error_0Click
        end
        object RB_McY_Error_1: TRadioButton
          Tag = 1
          Left = 8
          Top = 36
          Width = 64
          Height = 17
          Caption = 'Level 1'
          TabOrder = 1
        end
        object RB_McY_Error_2: TRadioButton
          Tag = 2
          Left = 8
          Top = 56
          Width = 64
          Height = 17
          Caption = 'Level 2'
          TabOrder = 2
        end
        object RB_McY_Error_3: TRadioButton
          Tag = 3
          Left = 8
          Top = 76
          Width = 64
          Height = 17
          Caption = 'Level 3'
          TabOrder = 3
        end
      end
      object GroupBox10: TGroupBox
        Left = 89
        Top = 182
        Width = 74
        Height = 97
        Caption = 'Test Pattern'
        TabOrder = 4
        object RB_McY_Test_0: TRadioButton
          Left = 8
          Top = 16
          Width = 64
          Height = 17
          Caption = 'Disable'
          Checked = True
          TabOrder = 0
          TabStop = True
          OnClick = RB_McY_Test_0Click
        end
        object RB_McY_Test_1: TRadioButton
          Tag = 1
          Left = 8
          Top = 36
          Width = 64
          Height = 17
          Caption = 'Ramp'
          TabOrder = 1
          OnClick = RB_McY_Test_0Click
        end
        object RB_McY_Test_2: TRadioButton
          Tag = 2
          Left = 8
          Top = 56
          Width = 64
          Height = 17
          Caption = 'W/B Bar'
          TabOrder = 2
          OnClick = RB_McY_Test_0Click
        end
        object RB_McY_Test_3: TRadioButton
          Tag = 3
          Left = 8
          Top = 76
          Width = 64
          Height = 17
          Caption = 'Gray'
          TabOrder = 3
          OnClick = RB_McY_Test_0Click
        end
      end
      object CB_McY_Debug: TCheckBox
        Tag = 1
        Left = 8
        Top = 48
        Width = 89
        Height = 17
        Caption = 'Debug Enable'
        TabOrder = 5
        OnClick = CB_MeY_DebugClick
      end
    end
    object GB_MCC: TGroupBox
      Left = 332
      Top = 131
      Width = 165
      Height = 281
      Caption = 'MC_C'
      TabOrder = 2
      object CB_McC_DC_Bypass: TCheckBox
        Tag = 12
        Left = 8
        Top = 16
        Width = 124
        Height = 17
        Caption = 'DC_Bypass'
        TabOrder = 0
        OnClick = CB_MeY_DC_BypassClick
      end
      object CB_McC_LastLine_Bypass: TCheckBox
        Tag = 22
        Left = 8
        Top = 32
        Width = 116
        Height = 17
        Caption = 'LastLine_Enable'
        TabOrder = 1
        OnClick = CB_MeY_DC_BypassClick
      end
      object GroupBox7: TGroupBox
        Left = 2
        Top = 80
        Width = 88
        Height = 199
        Caption = 'DC_ratio'
        TabOrder = 2
        object RB_McC_DC_mode0: TRadioButton
          Tag = 50
          Left = 8
          Top = 16
          Width = 78
          Height = 17
          Caption = 'DC_Mode0'
          Checked = True
          TabOrder = 0
          TabStop = True
          OnClick = RB_MeY_DC_mode0Click
        end
        object RB_McC_DC_mode1: TRadioButton
          Tag = 51
          Left = 8
          Top = 52
          Width = 78
          Height = 17
          Caption = 'DC_Mode1'
          TabOrder = 1
          OnClick = RB_MeY_DC_mode0Click
        end
        object RB_McC_DC_mode2: TRadioButton
          Tag = 52
          Left = 8
          Top = 88
          Width = 78
          Height = 17
          Caption = 'DC_Mode2'
          TabOrder = 2
          OnClick = RB_MeY_DC_mode0Click
        end
        object RB_McC_DC_mode3: TRadioButton
          Tag = 53
          Left = 8
          Top = 124
          Width = 78
          Height = 17
          Caption = 'DC_Mode3'
          TabOrder = 3
          OnClick = RB_MeY_DC_mode0Click
        end
        object RB_McC_DC_mode4: TRadioButton
          Tag = 54
          Left = 8
          Top = 160
          Width = 78
          Height = 17
          Caption = 'DC_Mode4'
          TabOrder = 4
          OnClick = RB_MeY_DC_mode0Click
        end
      end
      object GroupBox11: TGroupBox
        Left = 90
        Top = 80
        Width = 73
        Height = 97
        Caption = 'Error Level'
        TabOrder = 3
        object RB_McC_Error_0: TRadioButton
          Left = 8
          Top = 16
          Width = 60
          Height = 17
          Caption = 'Level 0'
          Checked = True
          TabOrder = 0
          TabStop = True
          OnClick = RB_McC_Error_0Click
        end
        object RB_McC_Error_1: TRadioButton
          Tag = 1
          Left = 8
          Top = 36
          Width = 60
          Height = 17
          Caption = 'Level 1'
          TabOrder = 1
          OnClick = RB_McC_Error_0Click
        end
        object RB_McC_Error_2: TRadioButton
          Tag = 2
          Left = 8
          Top = 56
          Width = 60
          Height = 17
          Caption = 'Level 2'
          TabOrder = 2
          OnClick = RB_McC_Error_0Click
        end
        object RB_McC_Error_3: TRadioButton
          Tag = 3
          Left = 8
          Top = 76
          Width = 60
          Height = 17
          Caption = 'Level 3'
          TabOrder = 3
          OnClick = RB_McC_Error_0Click
        end
      end
      object GroupBox12: TGroupBox
        Left = 90
        Top = 182
        Width = 73
        Height = 97
        Caption = 'Test Pattern'
        TabOrder = 4
        object RB_McC_Test_0: TRadioButton
          Left = 8
          Top = 16
          Width = 62
          Height = 17
          Caption = 'Disable'
          Checked = True
          TabOrder = 0
          TabStop = True
          OnClick = RB_McC_Test_0Click
        end
        object RB_McC_Test_1: TRadioButton
          Tag = 1
          Left = 8
          Top = 36
          Width = 62
          Height = 17
          Caption = 'Ramp'
          TabOrder = 1
          OnClick = RB_McC_Test_0Click
        end
        object RB_McC_Test_2: TRadioButton
          Tag = 2
          Left = 8
          Top = 56
          Width = 62
          Height = 17
          Caption = 'W/B Bar'
          TabOrder = 2
          OnClick = RB_McC_Test_0Click
        end
        object RB_McC_Test_3: TRadioButton
          Tag = 3
          Left = 8
          Top = 76
          Width = 62
          Height = 17
          Caption = 'Gray'
          TabOrder = 3
          OnClick = RB_McC_Test_0Click
        end
      end
      object CB_McC_Debug: TCheckBox
        Tag = 2
        Left = 8
        Top = 48
        Width = 89
        Height = 17
        Caption = 'Debug Enable'
        TabOrder = 5
        OnClick = CB_MeY_DebugClick
      end
    end
    object GB_DCMode: TGroupBox
      Left = 10
      Top = -5
      Width = 495
      Height = 57
      Caption = 'ALL DC Mode'
      TabOrder = 3
      Visible = False
      object RadioButton1: TRadioButton
        Left = 8
        Top = 24
        Width = 65
        Height = 17
        Caption = 'Mode 0'
        Checked = True
        TabOrder = 0
        TabStop = True
        OnClick = RadioButton1Click
      end
      object RadioButton2: TRadioButton
        Tag = 1
        Left = 74
        Top = 24
        Width = 96
        Height = 17
        Caption = 'Mode 1'
        TabOrder = 1
        OnClick = RadioButton1Click
      end
      object RadioButton5: TRadioButton
        Tag = 4
        Left = 264
        Top = 24
        Width = 81
        Height = 17
        Caption = 'Mode 4'
        TabOrder = 2
        OnClick = RadioButton1Click
      end
      object RadioButton3: TRadioButton
        Tag = 2
        Left = 140
        Top = 24
        Width = 69
        Height = 17
        Caption = 'Mode 2'
        TabOrder = 3
        OnClick = RadioButton1Click
      end
      object RadioButton4: TRadioButton
        Tag = 3
        Left = 204
        Top = 24
        Width = 59
        Height = 17
        Caption = 'Mode 3'
        TabOrder = 4
        OnClick = RadioButton1Click
      end
      object RadioButton11: TRadioButton
        Tag = 4
        Left = 328
        Top = 24
        Width = 81
        Height = 17
        Caption = 'DC Bypass'
        TabOrder = 5
        OnClick = RadioButton11Click
      end
    end
    object GroupBox3: TGroupBox
      Left = 2
      Top = 67
      Width = 169
      Height = 57
      Caption = 'Format'
      TabOrder = 4
      object rb_PC: TRadioButton
        Left = 24
        Top = 24
        Width = 65
        Height = 17
        Caption = 'PC'
        TabOrder = 0
        OnClick = rb_PCClick
      end
      object rb_VD: TRadioButton
        Tag = 1
        Left = 104
        Top = 24
        Width = 58
        Height = 17
        Caption = 'VD'
        Checked = True
        TabOrder = 1
        TabStop = True
        OnClick = rb_PCClick
      end
    end
    object GroupBox5: TGroupBox
      Left = 226
      Top = 67
      Width = 249
      Height = 57
      Caption = 'Format'
      TabOrder = 5
      object rb_888: TRadioButton
        Left = 8
        Top = 24
        Width = 65
        Height = 17
        Caption = '8 8 8 '
        TabOrder = 0
        OnClick = rb_888Click
      end
      object rb_101010: TRadioButton
        Tag = 1
        Left = 80
        Top = 24
        Width = 65
        Height = 17
        Caption = '10 10 10'
        Checked = True
        TabOrder = 1
        TabStop = True
        OnClick = rb_888Click
      end
      object rb_1088: TRadioButton
        Tag = 2
        Left = 160
        Top = 24
        Width = 65
        Height = 17
        Caption = '10 8 8'
        TabOrder = 2
        OnClick = rb_888Click
      end
    end
    object Button11: TButton
      Left = 98
      Top = 40
      Width = 75
      Height = 25
      Caption = 'pixle swap'
      TabOrder = 6
      OnClick = Button11Click
    end
    object CB_Half: TCheckBox
      Left = 2
      Top = 43
      Width = 89
      Height = 17
      Caption = 'Half Display'
      TabOrder = 7
      OnClick = CB_HalfClick
    end
    object Button1: TButton
      Left = 400
      Top = 40
      Width = 75
      Height = 25
      Caption = 'Refresh'
      TabOrder = 8
      OnClick = Button1Click
    end
  end
end
