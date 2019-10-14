inherited Frame_Debug: TFrame_Debug
  Width = 516
  Height = 468
  object GroupBox13: TGroupBox
    Left = 8
    Top = 8
    Width = 321
    Height = 177
    Caption = 'Debug'
    TabOrder = 0
    object Label4: TLabel
      Left = 16
      Top = 67
      Width = 41
      Height = 13
      AutoSize = False
      Caption = 'sig_sel'
    end
    object Label5: TLabel
      Left = 16
      Top = 91
      Width = 41
      Height = 13
      AutoSize = False
      Caption = 'sig_sel1'
    end
    object Label6: TLabel
      Left = 16
      Top = 115
      Width = 41
      Height = 13
      AutoSize = False
      Caption = 'low sel'
    end
    object Label7: TLabel
      Left = 16
      Top = 139
      Width = 41
      Height = 13
      AutoSize = False
      Caption = 'hign sel'
    end
    object CB_DebugPort: TCheckBox
      Left = 16
      Top = 16
      Width = 121
      Height = 17
      Caption = 'Debug Port Enable'
      TabOrder = 0
      OnClick = CB_DebugPortClick
    end
    object CB_DebugByte: TCheckBox
      Left = 16
      Top = 40
      Width = 121
      Height = 17
      Caption = 'Debug Byte Swap'
      TabOrder = 1
      OnClick = CB_DebugPortClick
    end
    object SB_sig: TScrollBar
      Left = 59
      Top = 66
      Width = 190
      Height = 18
      Max = 255
      PageSize = 0
      TabOrder = 2
      OnScroll = SB_sigScroll
    end
    object Ed_sig: TEdit
      Left = 256
      Top = 64
      Width = 41
      Height = 21
      TabOrder = 3
      Text = '0'
      OnKeyPress = Ed_sigKeyPress
    end
    object SB_sig1: TScrollBar
      Left = 59
      Top = 90
      Width = 190
      Height = 18
      Max = 255
      PageSize = 0
      TabOrder = 4
      OnScroll = SB_sigScroll
    end
    object Ed_sig1: TEdit
      Left = 256
      Top = 88
      Width = 41
      Height = 21
      TabOrder = 5
      Text = '0'
    end
    object SB_low: TScrollBar
      Left = 59
      Top = 114
      Width = 190
      Height = 18
      Max = 127
      PageSize = 0
      TabOrder = 6
      OnScroll = SB_sigScroll
    end
    object Ed_low: TEdit
      Left = 256
      Top = 112
      Width = 41
      Height = 21
      TabOrder = 7
      Text = '0'
    end
    object SB_high: TScrollBar
      Left = 59
      Top = 138
      Width = 190
      Height = 18
      Max = 127
      PageSize = 0
      TabOrder = 8
      OnScroll = SB_sigScroll
    end
    object Ed_high: TEdit
      Left = 256
      Top = 136
      Width = 41
      Height = 21
      TabOrder = 9
      Text = '0'
    end
    object Button12: TButton
      Left = 152
      Top = 24
      Width = 75
      Height = 25
      Caption = 'Debug Enable'
      TabOrder = 10
      OnClick = Button12Click
    end
  end
  object GroupBox14: TGroupBox
    Left = 8
    Top = 192
    Width = 321
    Height = 249
    Caption = 'Bandwidth Flag'
    TabOrder = 1
    object SpeedButton1: TSpeedButton
      Left = 184
      Top = 216
      Width = 81
      Height = 25
      Caption = 'Write 1 Clear'
      OnClick = SpeedButton1Click
    end
    object btn_Refresh: TSpeedButton
      Left = 184
      Top = 184
      Width = 81
      Height = 25
      Caption = 'Refresh'
      OnClick = btn_RefreshClick
    end
    object Label8: TLabel
      Left = 8
      Top = 24
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'ME i y r'
    end
    object Label9: TLabel
      Left = 8
      Top = 56
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'ME p y r'
    end
    object Label10: TLabel
      Left = 8
      Top = 88
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'ME i2 y r'
    end
    object Label11: TLabel
      Left = 8
      Top = 120
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'MC i y r'
    end
    object Label12: TLabel
      Left = 8
      Top = 152
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'MC i c r'
    end
    object Label13: TLabel
      Left = 8
      Top = 184
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'MC p y r'
    end
    object Label14: TLabel
      Left = 8
      Top = 216
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'MC p c r'
    end
    object CB_meiyr_lb: TCheckBox
      Left = 64
      Top = 16
      Width = 81
      Height = 17
      Caption = 'lb wr late'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 0
    end
    object CB_meiyr_pic: TCheckBox
      Left = 64
      Top = 32
      Width = 81
      Height = 17
      Caption = 'pic early end'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 1
    end
    object CB_IPy: TCheckBox
      Left = 184
      Top = 112
      Width = 58
      Height = 17
      Caption = 'IP y'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 2
    end
    object CB_IPcb: TCheckBox
      Left = 184
      Top = 128
      Width = 58
      Height = 17
      Caption = 'IP cb'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 3
    end
    object CB_IPcr: TCheckBox
      Left = 184
      Top = 144
      Width = 58
      Height = 17
      Caption = 'IP cr'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 4
    end
    object CB_IPyrd: TCheckBox
      Left = 184
      Top = 160
      Width = 58
      Height = 17
      Caption = 'IP yrd'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 5
    end
    object CB_mepyr_pic: TCheckBox
      Left = 64
      Top = 64
      Width = 81
      Height = 17
      Caption = 'pic early end'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 6
    end
    object CB_mepyr_lb: TCheckBox
      Left = 64
      Top = 48
      Width = 81
      Height = 17
      Caption = 'lb wr late'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 7
    end
    object CB_mei2yr_pic: TCheckBox
      Left = 64
      Top = 96
      Width = 81
      Height = 17
      Caption = 'pic early end'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 8
    end
    object CB_mei2yr_lb: TCheckBox
      Left = 64
      Top = 80
      Width = 81
      Height = 17
      Caption = 'lb wr late'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 9
    end
    object CB_mciyr_pic: TCheckBox
      Left = 64
      Top = 128
      Width = 81
      Height = 17
      Caption = 'pic early end'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 10
    end
    object CB_mciyr_lb: TCheckBox
      Left = 64
      Top = 112
      Width = 81
      Height = 17
      Caption = 'lb wr late'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 11
    end
    object CB_mcicr_pic: TCheckBox
      Left = 64
      Top = 160
      Width = 81
      Height = 17
      Caption = 'pic early end'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 12
    end
    object CB_mcicr_lb: TCheckBox
      Left = 64
      Top = 144
      Width = 81
      Height = 17
      Caption = 'lb wr late'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 13
    end
    object CB_mcpyr_pic: TCheckBox
      Left = 64
      Top = 192
      Width = 81
      Height = 17
      Caption = 'pic early end'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 14
    end
    object CB_mcpyr_lb: TCheckBox
      Left = 64
      Top = 176
      Width = 81
      Height = 17
      Caption = 'lb wr late'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 15
    end
    object CB_mcpcr_pic: TCheckBox
      Left = 64
      Top = 224
      Width = 81
      Height = 17
      Caption = 'pic early end'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 16
    end
    object CB_mcpcr_lb: TCheckBox
      Left = 64
      Top = 208
      Width = 81
      Height = 17
      Caption = 'lb wr late'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 17
    end
    object CB_MV_ph_wr: TCheckBox
      Left = 184
      Top = 16
      Width = 121
      Height = 17
      Caption = 'MVBUF ip ph pf wr'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 18
    end
    object CB_MV_pi_wr: TCheckBox
      Left = 184
      Top = 32
      Width = 121
      Height = 17
      Caption = 'MVBUF pi wr'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 19
    end
    object CB_MV_pi_rd: TCheckBox
      Left = 184
      Top = 64
      Width = 121
      Height = 17
      Caption = 'MVBUF pi rd'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 20
    end
    object CB_MV_ph_rd: TCheckBox
      Left = 184
      Top = 48
      Width = 121
      Height = 17
      Caption = 'MVBUF ip ph pf rd'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 21
    end
    object CB_MV_ppi_rd: TCheckBox
      Left = 184
      Top = 80
      Width = 121
      Height = 17
      Caption = 'MVBUF ppi rd'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 22
    end
  end
end
