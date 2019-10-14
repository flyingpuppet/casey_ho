inherited Frame_BWMeasure_312FPGA: TFrame_BWMeasure_312FPGA
  Width = 502
  Height = 589
  object Lines: TLabel
    Left = 344
    Top = 8
    Width = 49
    Height = 13
    AutoSize = False
    Caption = 'Lines'
  end
  object Label1: TLabel
    Left = 344
    Top = 32
    Width = 57
    Height = 13
    AutoSize = False
    Caption = 'Start Line'
  end
  object Label2: TLabel
    Left = 344
    Top = 56
    Width = 57
    Height = 13
    AutoSize = False
    Caption = 'End Line'
  end
  object Label7: TLabel
    Left = 16
    Top = 8
    Width = 42
    Height = 13
    Caption = 'Meter 0  '
  end
  object Label8: TLabel
    Left = 16
    Top = 32
    Width = 42
    Height = 13
    Caption = 'Meter 1  '
  end
  object Label9: TLabel
    Left = 16
    Top = 56
    Width = 42
    Height = 13
    Caption = 'Meter 2  '
  end
  object Label10: TLabel
    Left = 16
    Top = 80
    Width = 42
    Height = 13
    Caption = 'Meter 3  '
  end
  object Label11: TLabel
    Left = 16
    Top = 104
    Width = 42
    Height = 13
    Caption = 'Meter 4  '
  end
  object Label12: TLabel
    Left = 16
    Top = 128
    Width = 42
    Height = 13
    Caption = 'Meter 5  '
  end
  object Label13: TLabel
    Left = 16
    Top = 152
    Width = 42
    Height = 13
    Caption = 'Meter 6  '
  end
  object Label14: TLabel
    Left = 16
    Top = 176
    Width = 42
    Height = 13
    Caption = 'Meter 7  '
  end
  object clb_Agents: TCheckListBox
    Left = 304
    Top = 16
    Width = 200
    Height = 297
    ItemHeight = 13
    Items.Strings = (
      'me_i_y_r'
      'me_p_y_r'
      'me_i2_y_r'
      'me_mv1_w '
      'me_mv1_r '
      'me_pi_v_w'
      'me_pi_v_r'
      'me_ppi_v_r'
      'mc_i_y_r(dp_y_r)'
      'mc_i_c_r(dp_cb_r)'
      'mc_p_y_r'
      'mc_p_c_r(dp_cr_r@444)'
      'ip_y_w'
      'ip_c_w(ip_cb_w@444)'
      'ip_qy_w(Q_pixel_y||ip_cr_w@444)'
      'ip_fdet_r'
      'ip_logo_w'
      'ip_logo_r'
      'logo_mask_w'
      'logo_mask_r'
      'vdp_r'
      'vdp_w')
    TabOrder = 13
    Visible = False
    OnClick = clb_AgentsClick
    OnExit = clb_AgentsExit
  end
  object Button1: TButton
    Left = 392
    Top = 120
    Width = 105
    Height = 25
    Caption = 'Measure IP BW'
    TabOrder = 0
    OnClick = Button1Click
  end
  object memo_out: TMemo
    Left = 0
    Top = 488
    Width = 502
    Height = 84
    Align = alBottom
    ScrollBars = ssVertical
    TabOrder = 1
  end
  object Button2: TButton
    Left = 392
    Top = 148
    Width = 105
    Height = 25
    Caption = 'Measure ME BW'
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 392
    Top = 176
    Width = 105
    Height = 25
    Caption = 'Measure MC BW'
    TabOrder = 3
    OnClick = Button3Click
  end
  object PB_BW: TProgressBar
    Left = 0
    Top = 572
    Width = 502
    Height = 17
    Align = alBottom
    Min = 0
    Max = 100
    TabOrder = 4
  end
  object GB_Mode: TGroupBox
    Left = 8
    Top = 200
    Width = 289
    Height = 105
    Caption = 'Mode'
    TabOrder = 5
    object Label3: TLabel
      Left = 8
      Top = 24
      Width = 65
      Height = 13
      AutoSize = False
      Caption = 'Rx  Sync'
    end
    object Label4: TLabel
      Left = 8
      Top = 40
      Width = 65
      Height = 13
      AutoSize = False
      Caption = 'Tx VSync'
    end
    object Label5: TLabel
      Left = 8
      Top = 56
      Width = 65
      Height = 13
      AutoSize = False
      Caption = 'Tx MC_Start'
    end
    object Label6: TLabel
      Left = 8
      Top = 72
      Width = 65
      Height = 13
      AutoSize = False
      Caption = 'Tx Me_init'
    end
    object GB_IP: TGroupBox
      Left = 121
      Top = 8
      Width = 49
      Height = 89
      Caption = 'IP'
      TabOrder = 0
      object RB_IP_0: TRadioButton
        Left = 8
        Top = 16
        Width = 35
        Height = 17
        Caption = '0'
        Checked = True
        TabOrder = 0
        TabStop = True
        OnClick = RB_IP_0Click
      end
      object RB_IP_1: TRadioButton
        Tag = 1
        Left = 8
        Top = 32
        Width = 35
        Height = 17
        Caption = '1'
        TabOrder = 1
        OnClick = RB_IP_0Click
      end
      object RB_IP_2: TRadioButton
        Tag = 2
        Left = 8
        Top = 48
        Width = 35
        Height = 17
        Caption = '2'
        TabOrder = 2
        OnClick = RB_IP_0Click
      end
      object RB_IP_3: TRadioButton
        Tag = 3
        Left = 8
        Top = 64
        Width = 35
        Height = 17
        Caption = '3'
        TabOrder = 3
        OnClick = RB_IP_0Click
      end
    end
    object GP_ME: TGroupBox
      Left = 177
      Top = 8
      Width = 49
      Height = 89
      Caption = 'ME'
      TabOrder = 1
      object RB_ME_0: TRadioButton
        Left = 8
        Top = 16
        Width = 35
        Height = 17
        Caption = '0'
        Checked = True
        TabOrder = 0
        TabStop = True
        OnClick = RB_ME_0Click
      end
      object RB_ME_1: TRadioButton
        Tag = 1
        Left = 8
        Top = 32
        Width = 35
        Height = 17
        Caption = '1'
        TabOrder = 1
        OnClick = RB_ME_0Click
      end
      object RB_ME_2: TRadioButton
        Tag = 2
        Left = 8
        Top = 48
        Width = 35
        Height = 17
        Caption = '2'
        TabOrder = 2
        OnClick = RB_ME_0Click
      end
      object RB_ME_3: TRadioButton
        Tag = 3
        Left = 8
        Top = 64
        Width = 35
        Height = 17
        Caption = '3'
        TabOrder = 3
        OnClick = RB_ME_0Click
      end
    end
    object GB_MC: TGroupBox
      Left = 233
      Top = 8
      Width = 49
      Height = 89
      Caption = 'MC'
      TabOrder = 2
      object RB_MC_0: TRadioButton
        Left = 8
        Top = 16
        Width = 35
        Height = 17
        Caption = '0'
        Checked = True
        TabOrder = 0
        TabStop = True
        OnClick = RB_MC_0Click
      end
      object RB_MC_1: TRadioButton
        Tag = 1
        Left = 8
        Top = 32
        Width = 35
        Height = 17
        Caption = '1'
        TabOrder = 1
        OnClick = RB_MC_0Click
      end
      object RB_MC_2: TRadioButton
        Tag = 2
        Left = 8
        Top = 48
        Width = 35
        Height = 17
        Caption = '2'
        TabOrder = 2
        OnClick = RB_MC_0Click
      end
      object RB_MC_3: TRadioButton
        Tag = 3
        Left = 8
        Top = 64
        Width = 35
        Height = 17
        Caption = '3'
        TabOrder = 3
        OnClick = RB_MC_0Click
      end
    end
    object RB_all_0: TRadioButton
      Left = 73
      Top = 24
      Width = 35
      Height = 17
      Caption = '0'
      Checked = True
      TabOrder = 3
      TabStop = True
      OnClick = RB_all_0Click
    end
    object RB_all_1: TRadioButton
      Tag = 1
      Left = 73
      Top = 40
      Width = 35
      Height = 17
      Caption = '1'
      TabOrder = 4
      OnClick = RB_all_0Click
    end
    object RB_all_2: TRadioButton
      Tag = 2
      Left = 73
      Top = 56
      Width = 35
      Height = 17
      Caption = '2'
      TabOrder = 5
      OnClick = RB_all_0Click
    end
    object RB_all_3: TRadioButton
      Tag = 3
      Left = 73
      Top = 72
      Width = 35
      Height = 17
      Caption = '3'
      TabOrder = 6
      OnClick = RB_all_0Click
    end
  end
  object CB_Lines: TComboBox
    Left = 400
    Top = 8
    Width = 96
    Height = 21
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 6
    Text = '1'
    OnChange = CB_LinesChange
    Items.Strings = (
      '1'
      '2'
      '3'
      '4'
      '5'
      '6'
      '7'
      '8')
  end
  object Ed_Start: TEdit
    Left = 400
    Top = 32
    Width = 96
    Height = 21
    TabOrder = 7
    Text = '0'
    OnChange = Ed_StartChange
  end
  object Ed_End: TEdit
    Left = 400
    Top = 56
    Width = 96
    Height = 21
    TabOrder = 8
    Text = '1125'
    OnChange = Ed_EndChange
  end
  object btn_AllBW: TButton
    Left = 392
    Top = 88
    Width = 105
    Height = 25
    Caption = 'All BW'
    TabOrder = 9
    OnClick = btn_AllBWClick
  end
  object Button4: TButton
    Left = 392
    Top = 232
    Width = 105
    Height = 25
    Caption = 'Free Measure'
    TabOrder = 10
    OnClick = Button4Click
  end
  object CheckPanel: TPanel
    Left = 264
    Top = 0
    Width = 41
    Height = 201
    BevelOuter = bvNone
    TabOrder = 11
    object CheckBox1: TCheckBox
      Left = 8
      Top = 8
      Width = 25
      Height = 17
      Checked = True
      State = cbChecked
      TabOrder = 0
      OnClick = CheckBox1Click
    end
    object CheckBox2: TCheckBox
      Tag = 1
      Left = 8
      Top = 32
      Width = 25
      Height = 17
      Checked = True
      State = cbChecked
      TabOrder = 1
      OnClick = CheckBox1Click
    end
    object CheckBox3: TCheckBox
      Tag = 2
      Left = 8
      Top = 56
      Width = 25
      Height = 17
      Checked = True
      State = cbChecked
      TabOrder = 2
      OnClick = CheckBox1Click
    end
    object CheckBox4: TCheckBox
      Tag = 3
      Left = 8
      Top = 80
      Width = 25
      Height = 17
      Checked = True
      State = cbChecked
      TabOrder = 3
      OnClick = CheckBox1Click
    end
    object CheckBox5: TCheckBox
      Tag = 4
      Left = 8
      Top = 104
      Width = 25
      Height = 17
      Checked = True
      State = cbChecked
      TabOrder = 4
      OnClick = CheckBox1Click
    end
    object CheckBox6: TCheckBox
      Tag = 5
      Left = 8
      Top = 128
      Width = 25
      Height = 17
      Checked = True
      State = cbChecked
      TabOrder = 5
      OnClick = CheckBox1Click
    end
    object CheckBox7: TCheckBox
      Tag = 6
      Left = 8
      Top = 152
      Width = 25
      Height = 17
      Checked = True
      State = cbChecked
      TabOrder = 6
      OnClick = CheckBox1Click
    end
    object CheckBox8: TCheckBox
      Tag = 7
      Left = 8
      Top = 176
      Width = 25
      Height = 17
      Checked = True
      State = cbChecked
      TabOrder = 7
      OnClick = CheckBox1Click
    end
  end
  object btnTotal: TButton
    Left = 392
    Top = 264
    Width = 105
    Height = 25
    Caption = 'Total'
    TabOrder = 12
    OnClick = btnTotalClick
  end
  object Edit1: TEdit
    Left = 64
    Top = 5
    Width = 201
    Height = 21
    TabOrder = 14
    OnEnter = Edit1Enter
    OnExit = Edit1Exit
  end
  object Edit2: TEdit
    Tag = 1
    Left = 64
    Top = 29
    Width = 201
    Height = 21
    TabOrder = 15
    OnEnter = Edit1Enter
    OnExit = Edit1Exit
  end
  object Edit3: TEdit
    Tag = 2
    Left = 64
    Top = 53
    Width = 201
    Height = 21
    TabOrder = 16
    OnEnter = Edit1Enter
    OnExit = Edit1Exit
  end
  object Edit4: TEdit
    Tag = 3
    Left = 64
    Top = 77
    Width = 201
    Height = 21
    TabOrder = 17
    OnEnter = Edit1Enter
    OnExit = Edit1Exit
  end
  object Edit5: TEdit
    Tag = 4
    Left = 64
    Top = 101
    Width = 201
    Height = 21
    TabOrder = 18
    OnEnter = Edit1Enter
    OnExit = Edit1Exit
  end
  object Edit6: TEdit
    Tag = 5
    Left = 64
    Top = 125
    Width = 201
    Height = 21
    TabOrder = 19
    OnEnter = Edit1Enter
    OnExit = Edit1Exit
  end
  object Edit7: TEdit
    Tag = 6
    Left = 64
    Top = 149
    Width = 201
    Height = 21
    TabOrder = 20
    OnEnter = Edit1Enter
    OnExit = Edit1Exit
  end
  object Edit8: TEdit
    Tag = 7
    Left = 64
    Top = 173
    Width = 201
    Height = 21
    TabOrder = 21
    OnEnter = Edit1Enter
    OnExit = Edit1Exit
  end
  object cb_Band: TCheckBox
    Left = 8
    Top = 312
    Width = 97
    Height = 17
    Caption = 'Calc bandwidth'
    TabOrder = 22
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 336
    Width = 497
    Height = 145
    Caption = 'AXI BW Meter'
    TabOrder = 23
    object BitBtn1: TBitBtn
      Left = 328
      Top = 16
      Width = 41
      Height = 25
      Hint = 'Insert'
      Caption = 'Add'
      TabOrder = 0
      OnClick = BitBtn1Click
    end
    object Button5: TButton
      Left = 384
      Top = 112
      Width = 105
      Height = 25
      Caption = 'Free Measure'
      TabOrder = 1
      OnClick = Button5Click
    end
    object MemoAXI: TListBox
      Left = 0
      Top = 16
      Width = 329
      Height = 126
      ItemHeight = 13
      TabOrder = 2
    end
    object BitBtn2: TBitBtn
      Left = 328
      Top = 40
      Width = 41
      Height = 25
      Hint = 'Insert'
      Caption = 'Del'
      TabOrder = 3
      OnClick = BitBtn2Click
    end
  end
  object SaveDialog1: TSaveDialog
    Left = 640
    Top = 8
  end
  object OpenDialog1: TOpenDialog
    Left = 584
    Top = 32
  end
end
