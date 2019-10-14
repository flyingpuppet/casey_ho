inherited Form_gauss: TForm_gauss
  Left = 201
  Top = 74
  Width = 1000
  Height = 649
  Caption = 'Gaussion Filter'
  OldCreateOrder = True
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 16
    Width = 89
    Height = 13
    AutoSize = False
    Caption = 'Y Filter'
  end
  object Label2: TLabel
    Left = 8
    Top = 272
    Width = 89
    Height = 13
    AutoSize = False
    Caption = 'X Filter'
  end
  object Label3: TLabel
    Left = 16
    Top = 40
    Width = 89
    Height = 13
    AutoSize = False
    Caption = 'sigma: '
  end
  object Label4: TLabel
    Left = 8
    Top = 296
    Width = 89
    Height = 13
    AutoSize = False
    Caption = 'sigma: '
  end
  object Chart1: TChart
    Left = 152
    Top = 0
    Width = 809
    Height = 250
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Text.Strings = (
      '')
    BottomAxis.LabelsSize = 8
    BottomAxis.LabelStyle = talMark
    LeftAxis.AxisValuesFormat = '#,##0.####'
    Legend.Alignment = laTop
    Legend.LegendStyle = lsValues
    Legend.Visible = False
    TopAxis.AxisValuesFormat = '#,##0.####'
    TopAxis.LabelsOnAxis = False
    TopAxis.LabelStyle = talMark
    View3D = False
    TabOrder = 0
    object Series1: TLineSeries
      HorizAxis = aTopAxis
      Marks.ArrowLength = 8
      Marks.Style = smsLegend
      Marks.Visible = False
      SeriesColor = clRed
      ValueFormat = '#,##0.####'
      Pointer.InflateMargins = False
      Pointer.Style = psRectangle
      Pointer.Visible = False
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
    object Series2: TLineSeries
      HorizAxis = aBothHorizAxis
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clGreen
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = False
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
  end
  object Edit1: TEdit
    Left = 16
    Top = 56
    Width = 121
    Height = 21
    TabOrder = 1
  end
  object Button1: TButton
    Left = 16
    Top = 80
    Width = 75
    Height = 25
    Caption = 'Create Filter'
    TabOrder = 2
    OnClick = Button1Click
  end
  object Edit2: TEdit
    Left = 8
    Top = 312
    Width = 121
    Height = 21
    TabOrder = 3
  end
  object Button2: TButton
    Left = 8
    Top = 336
    Width = 75
    Height = 25
    Caption = 'Create Filter'
    TabOrder = 4
    OnClick = Button2Click
  end
  object Chart2: TChart
    Left = 152
    Top = 296
    Width = 809
    Height = 250
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Text.Strings = (
      '')
    BottomAxis.LabelsSize = 8
    BottomAxis.LabelStyle = talMark
    LeftAxis.AxisValuesFormat = '#,##0.####'
    Legend.Alignment = laTop
    Legend.LegendStyle = lsValues
    Legend.Visible = False
    TopAxis.AxisValuesFormat = '#,##0.####'
    TopAxis.LabelsOnAxis = False
    TopAxis.LabelStyle = talMark
    View3D = False
    TabOrder = 5
    object LineSeries1: TLineSeries
      HorizAxis = aTopAxis
      Marks.ArrowLength = 8
      Marks.Style = smsLegend
      Marks.Visible = False
      SeriesColor = clRed
      ValueFormat = '#,##0.####'
      Pointer.InflateMargins = False
      Pointer.Style = psRectangle
      Pointer.Visible = False
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
    object LineSeries2: TLineSeries
      HorizAxis = aBothHorizAxis
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clGreen
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = False
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
  end
  object Button3: TButton
    Left = 16
    Top = 112
    Width = 75
    Height = 25
    Caption = 'Write'
    TabOrder = 6
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 8
    Top = 368
    Width = 75
    Height = 25
    Caption = 'Write'
    TabOrder = 7
    OnClick = Button4Click
  end
  object Memo1: TMemo
    Left = 152
    Top = 248
    Width = 809
    Height = 41
    TabOrder = 8
  end
  object Memo2: TMemo
    Left = 152
    Top = 544
    Width = 809
    Height = 57
    TabOrder = 9
  end
end
