object Form_NT72682Updater: TForm_NT72682Updater
  Left = 438
  Top = 24
  Width = 757
  Height = 699
  Caption = 'NT72682 Updater'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl_Container: TPageControl
    Left = 8
    Top = 24
    Width = 737
    Height = 633
    ActivePage = TabSheet_codeDmp310
    TabIndex = 0
    TabOrder = 0
    object TabSheet_codeDmp310: TTabSheet
      Caption = '72310 code dumper'
      ImageIndex = 4
      object Memo_72310_dbg: TMemo
        Left = 8
        Top = 368
        Width = 289
        Height = 209
        ScrollBars = ssVertical
        TabOrder = 7
      end
      object GroupBox_codeDmp310_input: TGroupBox
        Left = 8
        Top = 8
        Width = 713
        Height = 353
        Caption = 'Input files'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        object LabeledEdit_310_subProgram: TLabeledEdit
          Left = 24
          Top = 40
          Width = 561
          Height = 24
          EditLabel.Width = 135
          EditLabel.Height = 16
          EditLabel.Caption = 'Sub-program (SRAM): '
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -13
          EditLabel.Font.Name = 'MS Sans Serif'
          EditLabel.Font.Style = []
          EditLabel.ParentFont = False
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 0
          Text = 
            'F:\WORK\72310_utility_release_gq_modify\72310_utility_release\BI' +
            'N\subprogram.tsim'
        end
        object LabeledEdit_310_subProgramDDR: TLabeledEdit
          Left = 24
          Top = 96
          Width = 561
          Height = 24
          EditLabel.Width = 78
          EditLabel.Height = 16
          EditLabel.Caption = 'Flash (Boot): '
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -13
          EditLabel.Font.Name = 'MS Sans Serif'
          EditLabel.Font.Style = []
          EditLabel.ParentFont = False
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 1
          Text = 
            'F:\WORK\72310_utility_release_gq_modify\72310_utility_release\BI' +
            'N\flashboot.tsim'
        end
        object LabeledEdit_310_FRCmain: TLabeledEdit
          Left = 24
          Top = 208
          Width = 561
          Height = 24
          EditLabel.Width = 99
          EditLabel.Height = 16
          EditLabel.Caption = 'FRC main code: '
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -13
          EditLabel.Font.Name = 'MS Sans Serif'
          EditLabel.Font.Style = []
          EditLabel.ParentFont = False
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 2
          Text = 
            'F:\WORK\72310_utility_release_gq_modify\72310_utility_release\BI' +
            'N\release_DSW.tsim'
        end
        object LabeledEdit_310_dataSRAM: TLabeledEdit
          Left = 24
          Top = 152
          Width = 561
          Height = 24
          EditLabel.Width = 81
          EditLabel.Height = 16
          EditLabel.Caption = 'Flash (writer): '
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -13
          EditLabel.Font.Name = 'MS Sans Serif'
          EditLabel.Font.Style = []
          EditLabel.ParentFont = False
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 3
          Text = 
            'F:\WORK\72310_utility_release_gq_modify\72310_utility_release\BI' +
            'N\flash_writer.tsim'
        end
        object Button_310_subProgramDDR: TButton
          Left = 594
          Top = 95
          Width = 33
          Height = 25
          Caption = '...'
          TabOrder = 4
          OnClick = Button_310_subProgramClick
        end
        object Button_310_dataSRAM: TButton
          Left = 594
          Top = 151
          Width = 33
          Height = 25
          Caption = '...'
          TabOrder = 5
          OnClick = Button_310_subProgramClick
        end
        object LabeledEdit_310_subProgram_offset: TLabeledEdit
          Left = 640
          Top = 40
          Width = 57
          Height = 24
          EditLabel.Width = 40
          EditLabel.Height = 16
          EditLabel.Caption = 'Offset: '
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -13
          EditLabel.Font.Name = 'MS Sans Serif'
          EditLabel.Font.Style = []
          EditLabel.ParentFont = False
          LabelPosition = lpAbove
          LabelSpacing = 3
          ReadOnly = True
          TabOrder = 6
        end
        object LabeledEdit_310_subProgramDDR_offset: TLabeledEdit
          Left = 640
          Top = 96
          Width = 57
          Height = 24
          EditLabel.Width = 40
          EditLabel.Height = 16
          EditLabel.Caption = 'Offset: '
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -13
          EditLabel.Font.Name = 'MS Sans Serif'
          EditLabel.Font.Style = []
          EditLabel.ParentFont = False
          LabelPosition = lpAbove
          LabelSpacing = 3
          ReadOnly = True
          TabOrder = 7
        end
        object LabeledEdit_310_dataSRAM_offset: TLabeledEdit
          Left = 640
          Top = 152
          Width = 57
          Height = 24
          EditLabel.Width = 40
          EditLabel.Height = 16
          EditLabel.Caption = 'Offset: '
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -13
          EditLabel.Font.Name = 'MS Sans Serif'
          EditLabel.Font.Style = []
          EditLabel.ParentFont = False
          LabelPosition = lpAbove
          LabelSpacing = 3
          ReadOnly = True
          TabOrder = 8
        end
        object Button_310_subProgram: TButton
          Left = 594
          Top = 39
          Width = 33
          Height = 25
          Caption = '...'
          TabOrder = 9
          OnClick = Button_310_subProgramClick
        end
        object LabeledEdit_310_FRCmain_offset: TLabeledEdit
          Left = 640
          Top = 208
          Width = 57
          Height = 24
          EditLabel.Width = 40
          EditLabel.Height = 16
          EditLabel.Caption = 'Offset: '
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -13
          EditLabel.Font.Name = 'MS Sans Serif'
          EditLabel.Font.Style = []
          EditLabel.ParentFont = False
          LabelPosition = lpAbove
          LabelSpacing = 3
          ReadOnly = True
          TabOrder = 10
        end
        object LabeledEdit_310_startAddr: TLabeledEdit
          Left = 616
          Top = 320
          Width = 81
          Height = 24
          EditLabel.Width = 100
          EditLabel.Height = 16
          EditLabel.Caption = 'Start Address: 0x'
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 11
          Text = '80001000'
        end
        object LabeledEdit_310_FRC: TLabeledEdit
          Left = 24
          Top = 264
          Width = 561
          Height = 24
          EditLabel.Width = 122
          EditLabel.Height = 16
          EditLabel.Caption = 'FRC register (DDR): '
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -13
          EditLabel.Font.Name = 'MS Sans Serif'
          EditLabel.Font.Style = []
          EditLabel.ParentFont = False
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 12
          Text = 
            'F:\WORK\72310_utility_release_gq_modify\72310_utility_release\BI' +
            'N\FRC.hex'
        end
        object Button_310_FRC: TButton
          Left = 594
          Top = 263
          Width = 33
          Height = 25
          Caption = '...'
          TabOrder = 13
          OnClick = Button_310_subProgramClick
        end
        object LabeledEdit_310_FRC_offset: TLabeledEdit
          Left = 640
          Top = 264
          Width = 57
          Height = 24
          EditLabel.Width = 40
          EditLabel.Height = 16
          EditLabel.Caption = 'Offset: '
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -13
          EditLabel.Font.Name = 'MS Sans Serif'
          EditLabel.Font.Style = []
          EditLabel.ParentFont = False
          LabelPosition = lpAbove
          LabelSpacing = 3
          ReadOnly = True
          TabOrder = 14
        end
        object LabeledEdit_310_FRCstartAddr: TLabeledEdit
          Left = 144
          Top = 296
          Width = 81
          Height = 24
          EditLabel.Width = 120
          EditLabel.Height = 16
          EditLabel.Caption = 'FRC header start: 0x'
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 15
          Text = '80030000'
        end
        object LabeledEdit_310_splitOffset: TLabeledEdit
          Left = 416
          Top = 320
          Width = 57
          Height = 24
          EditLabel.Width = 80
          EditLabel.Height = 16
          EditLabel.Caption = 'Split offset: 0x'
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clWindowText
          EditLabel.Font.Height = -13
          EditLabel.Font.Name = 'MS Sans Serif'
          EditLabel.Font.Style = []
          EditLabel.ParentFont = False
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 16
          Text = '0000'
          Visible = False
        end
        object Button_310_FRCmain: TButton
          Left = 594
          Top = 207
          Width = 33
          Height = 25
          Caption = '...'
          TabOrder = 17
          OnClick = Button_310_subProgramClick
        end
      end
      object Memo_310_dbg: TMemo
        Left = 8
        Top = 368
        Width = 289
        Height = 209
        ScrollBars = ssVertical
        TabOrder = 1
      end
      object Button_310_dmp: TButton
        Left = 608
        Top = 368
        Width = 113
        Height = 25
        Caption = 'Parse and Dump !'
        TabOrder = 2
        OnClick = Button_310_dmpClick
      end
      object LabeledEdit_310_pSize: TLabeledEdit
        Left = 344
        Top = 400
        Width = 65
        Height = 21
        EditLabel.Width = 158
        EditLabel.Height = 16
        EditLabel.Caption = 'Program SRAM size: (dec)'
        EditLabel.Font.Charset = DEFAULT_CHARSET
        EditLabel.Font.Color = clWindowText
        EditLabel.Font.Height = -13
        EditLabel.Font.Name = 'MS Sans Serif'
        EditLabel.Font.Style = []
        EditLabel.ParentFont = False
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 3
        Text = '57344'
      end
      object LabeledEdit_310_dSize: TLabeledEdit
        Left = 344
        Top = 448
        Width = 65
        Height = 21
        EditLabel.Width = 135
        EditLabel.Height = 16
        EditLabel.Caption = 'Data SRAM size: (dec)'
        EditLabel.Font.Charset = DEFAULT_CHARSET
        EditLabel.Font.Color = clWindowText
        EditLabel.Font.Height = -13
        EditLabel.Font.Name = 'MS Sans Serif'
        EditLabel.Font.Style = []
        EditLabel.ParentFont = False
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 4
        Text = '8192'
      end
      object Button_310_cpy: TButton
        Left = 608
        Top = 424
        Width = 75
        Height = 25
        Caption = 'Test copy'
        TabOrder = 5
        OnClick = Button_310_cpyClick
      end
      object Memo_310_tmp: TMemo
        Left = 344
        Top = 488
        Width = 225
        Height = 73
        ScrollBars = ssVertical
        TabOrder = 6
      end
      object LabeledEdit_310_unlock: TLabeledEdit
        Left = 608
        Top = 480
        Width = 49
        Height = 21
        EditLabel.Width = 113
        EditLabel.Height = 16
        EditLabel.Caption = 'Unlock token: (hex)'
        EditLabel.Font.Charset = DEFAULT_CHARSET
        EditLabel.Font.Color = clWindowText
        EditLabel.Font.Height = -13
        EditLabel.Font.Name = 'MS Sans Serif'
        EditLabel.Font.Style = []
        EditLabel.ParentFont = False
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 8
        Text = '7231'
      end
    end
    object TabSheet_312parser: TTabSheet
      Caption = '72312 elf parser'
      ImageIndex = 5
      TabVisible = False
    end
  end
  object ProgressBar_Complete: TProgressBar
    Left = 24
    Top = 640
    Width = 697
    Height = 18
    Min = 0
    Max = 100
    TabOrder = 1
    Visible = False
  end
  object OpenDialog: TOpenDialog
    Left = 565
    Top = 5
  end
  object SaveDialog: TSaveDialog
    Left = 536
    Top = 4
  end
end
