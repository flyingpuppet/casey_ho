inherited Form_DataPath_Chip: TForm_DataPath_Chip
  Caption = 'Form_DataPath_Chip'
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panel1: TPanel
    inherited GroupBox14: TGroupBox
      inherited RadioButton21: TRadioButton
        Enabled = True
      end
    end
    inherited GB_ReadBack: TGroupBox
      inherited le_Clk: TLabeledEdit
        Text = '150'
      end
    end
    object Button3: TButton
      Left = 280
      Top = 64
      Width = 97
      Height = 25
      Caption = 'H Scaler setting'
      TabOrder = 30
      OnClick = Button3Click
    end
    object cb_Hscaler: TCheckBox
      Left = 384
      Top = 72
      Width = 81
      Height = 17
      Caption = 'Hx1.5'
      TabOrder = 31
      OnClick = cb_HscalerClick
    end
  end
end
