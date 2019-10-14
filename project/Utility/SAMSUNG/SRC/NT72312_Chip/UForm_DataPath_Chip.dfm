inherited Form_DataPath_Chip: TForm_DataPath_Chip
  Caption = 'Form_DataPath_Chip'
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panel1: TPanel
    inherited Button11: TButton
      Visible = False
    end
    inherited CB_Half: TCheckBox
      Visible = False
    end
    inherited GroupBox14: TGroupBox
      inherited RadioButton21: TRadioButton
        Enabled = True
      end
    end
    inherited GB_ReadBack: TGroupBox
      inherited le_Clk: TLabeledEdit
        Left = 157
        Top = 115
        EditLabel.Width = 20
        EditLabel.Caption = 'CLK'
        Text = '150'
      end
    end
    inherited GroupBox15: TGroupBox
      inherited RegCheckBox4: TRegCheckBox
        Width = 249
        Caption = 'Passive Panel Left Image for 2D to3D'
      end
      inherited RegCheckBox5: TRegCheckBox
        Width = 241
        Caption = 'Passive Panel Right image for 2D to 3D'
      end
    end
    inherited btnTest: TButton
      TabOrder = 15
    end
    object Button3: TButton
      Left = 280
      Top = 64
      Width = 97
      Height = 25
      Caption = 'H Scaler setting'
      TabOrder = 13
      OnClick = Button3Click
    end
    object cb_Hscaler: TCheckBox
      Left = 384
      Top = 72
      Width = 81
      Height = 17
      Caption = 'Hx1.5'
      TabOrder = 14
      OnClick = cb_HscalerClick
    end
  end
end
