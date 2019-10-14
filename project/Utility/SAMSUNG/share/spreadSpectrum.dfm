object Form_spreadSpectrum: TForm_spreadSpectrum
  Left = 312
  Top = 53
  Width = 765
  Height = 597
  Caption = 'Spread Spectrum'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl_SSC: TPageControl
    Left = 8
    Top = 8
    Width = 745
    Height = 553
    ActivePage = TabSheet_SSC_312
    TabIndex = 0
    TabOrder = 0
    object TabSheet_SSC_312: TTabSheet
      Caption = '72312'
      ImageIndex = 1
      object GroupBox_312SSC_lvds: TGroupBox
        Left = 8
        Top = 292
        Width = 585
        Height = 201
        Caption = 'LVDS Spectrum'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        object LabeledEdit_312_clock_lvds: TLabeledEdit
          Left = 48
          Top = 40
          Width = 65
          Height = 24
          EditLabel.Width = 72
          EditLabel.Height = 16
          EditLabel.Caption = 'Clock (MHz)'
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -13
          EditLabel.Font.Name = 'MS Sans Serif'
          EditLabel.Font.Style = []
          EditLabel.ParentFont = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          LabelPosition = lpAbove
          LabelSpacing = 3
          ParentFont = False
          TabOrder = 0
          Text = '74.25'
          OnKeyPress = LabeledEdit_312_clock_lvdsKeyPress
        end
        object ComboBox_312_mulfac_lvds: TComboBox
          Left = 48
          Top = 136
          Width = 265
          Height = 24
          DropDownCount = 32
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ItemHeight = 16
          ParentFont = False
          TabOrder = 1
          Text = 'ssc_mulfac'
          OnChange = ComboBox_spread_mulfac_lvdsChange
        end
        object Button_312_calculate_lvds: TButton
          Left = 464
          Top = 136
          Width = 75
          Height = 25
          Caption = 'Calculate'
          TabOrder = 2
          Visible = False
        end
        object LabeledEdit_312_ssc_lvds: TLabeledEdit
          Left = 248
          Top = 40
          Width = 65
          Height = 24
          EditLabel.Width = 192
          EditLabel.Height = 16
          EditLabel.Caption = 'Spread spectrum frequency (Hz)'
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -13
          EditLabel.Font.Name = 'MS Sans Serif'
          EditLabel.Font.Style = []
          EditLabel.ParentFont = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          LabelPosition = lpAbove
          LabelSpacing = 3
          ParentFont = False
          TabOrder = 3
          Text = '20000'
          OnKeyPress = LabeledEdit_312_clock_lvdsKeyPress
        end
        object LabeledEdit_312_SSP_lvds: TLabeledEdit
          Left = 464
          Top = 40
          Width = 73
          Height = 24
          EditLabel.Width = 56
          EditLabel.Height = 16
          EditLabel.Caption = 'SSP (%): '
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -13
          EditLabel.Font.Name = 'MS Sans Serif'
          EditLabel.Font.Style = []
          EditLabel.ParentFont = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          LabelPosition = lpLeft
          LabelSpacing = 3
          ParentFont = False
          ReadOnly = True
          TabOrder = 4
          Visible = False
        end
        object LabeledEdit_312_SSPMHz_lvds: TLabeledEdit
          Left = 464
          Top = 88
          Width = 73
          Height = 24
          EditLabel.Width = 71
          EditLabel.Height = 16
          EditLabel.Caption = 'SSP (MHz): '
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -13
          EditLabel.Font.Name = 'MS Sans Serif'
          EditLabel.Font.Style = []
          EditLabel.ParentFont = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          LabelPosition = lpLeft
          LabelSpacing = 3
          ParentFont = False
          ReadOnly = True
          TabOrder = 5
          Visible = False
        end
        object CheckBox_312_enable_lvds: TCheckBox
          Left = 48
          Top = 80
          Width = 97
          Height = 17
          Caption = 'Enable'
          TabOrder = 6
          OnClick = CheckBox_spread_enableClick
        end
        object Button_312_reset_lvds: TButton
          Left = 248
          Top = 80
          Width = 65
          Height = 25
          Caption = 'Reset'
          TabOrder = 7
          OnClick = Button_spread_resetClick
        end
      end
      object GroupBox_312_ssc: TGroupBox
        Left = 8
        Top = 68
        Width = 585
        Height = 201
        Caption = 'DDR Spectrum'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        object LabeledEdit_312_clock: TLabeledEdit
          Left = 48
          Top = 40
          Width = 65
          Height = 24
          EditLabel.Width = 72
          EditLabel.Height = 16
          EditLabel.Caption = 'Clock (MHz)'
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -13
          EditLabel.Font.Name = 'MS Sans Serif'
          EditLabel.Font.Style = []
          EditLabel.ParentFont = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          LabelPosition = lpAbove
          LabelSpacing = 3
          ParentFont = False
          TabOrder = 0
          Text = '450'
          OnKeyPress = LabeledEdit_312_clock_lvdsKeyPress
        end
        object ComboBox_312_mulfac: TComboBox
          Left = 48
          Top = 136
          Width = 265
          Height = 24
          DropDownCount = 32
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ItemHeight = 16
          ParentFont = False
          TabOrder = 1
          Text = 'ssc_mulfac'
          OnChange = ComboBox_spread_mulfac_lvdsChange
        end
        object Button_312_calculate: TButton
          Left = 464
          Top = 136
          Width = 75
          Height = 25
          Caption = 'Calculate'
          TabOrder = 2
          Visible = False
          OnClick = Button_312_calculateClick
        end
        object LabeledEdit_312_ssc: TLabeledEdit
          Left = 248
          Top = 40
          Width = 65
          Height = 24
          EditLabel.Width = 192
          EditLabel.Height = 16
          EditLabel.Caption = 'Spread spectrum frequency (Hz)'
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -13
          EditLabel.Font.Name = 'MS Sans Serif'
          EditLabel.Font.Style = []
          EditLabel.ParentFont = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          LabelPosition = lpAbove
          LabelSpacing = 3
          ParentFont = False
          TabOrder = 3
          Text = '20000'
          OnKeyPress = LabeledEdit_312_clock_lvdsKeyPress
        end
        object LabeledEdit_312_SSP: TLabeledEdit
          Left = 464
          Top = 40
          Width = 73
          Height = 24
          EditLabel.Width = 56
          EditLabel.Height = 16
          EditLabel.Caption = 'SSP (%): '
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -13
          EditLabel.Font.Name = 'MS Sans Serif'
          EditLabel.Font.Style = []
          EditLabel.ParentFont = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          LabelPosition = lpLeft
          LabelSpacing = 3
          ParentFont = False
          ReadOnly = True
          TabOrder = 4
          Visible = False
        end
        object LabeledEdit_312_SSPMHz: TLabeledEdit
          Left = 464
          Top = 88
          Width = 73
          Height = 24
          EditLabel.Width = 71
          EditLabel.Height = 16
          EditLabel.Caption = 'SSP (MHz): '
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -13
          EditLabel.Font.Name = 'MS Sans Serif'
          EditLabel.Font.Style = []
          EditLabel.ParentFont = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          LabelPosition = lpLeft
          LabelSpacing = 3
          ParentFont = False
          ReadOnly = True
          TabOrder = 5
          Visible = False
        end
        object CheckBox_312_enable: TCheckBox
          Left = 48
          Top = 80
          Width = 97
          Height = 17
          Caption = 'Enable'
          TabOrder = 6
          OnClick = CheckBox_spread_enableClick
        end
        object Button_312_reset: TButton
          Left = 248
          Top = 80
          Width = 65
          Height = 25
          Caption = 'Reset'
          TabOrder = 7
          OnClick = Button_spread_resetClick
        end
      end
    end
  end
end
