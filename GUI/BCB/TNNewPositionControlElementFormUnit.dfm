object NNewPositionControlElementForm: TNNewPositionControlElementForm
  Left = 0
  Top = 0
  Caption = 'NNewPositionControlElementForm'
  ClientHeight = 600
  ClientWidth = 921
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 120
  TextHeight = 17
  object Splitter1: TSplitter
    Left = 0
    Top = 137
    Width = 921
    Height = 20
    Cursor = crVSplit
    Margins.Left = 4
    Margins.Top = 4
    Margins.Right = 4
    Margins.Bottom = 4
    Align = alTop
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 921
    Height = 137
    Margins.Left = 4
    Margins.Top = 4
    Margins.Right = 4
    Margins.Bottom = 4
    Align = alTop
    Caption = ' Current recognized state '
    TabOrder = 0
    object TrainedStateStringGrid: TStringGrid
      Left = 3
      Top = 20
      Width = 915
      Height = 115
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Align = alClient
      DefaultRowHeight = 18
      TabOrder = 0
    end
  end
  object GroupBox2: TGroupBox
    Left = 0
    Top = 157
    Width = 921
    Height = 137
    Margins.Left = 4
    Margins.Top = 4
    Margins.Right = 4
    Margins.Bottom = 4
    Align = alTop
    Caption = ' Current selected state '
    TabOrder = 1
    object SelectedStateStringGrid: TStringGrid
      Left = 3
      Top = 20
      Width = 915
      Height = 115
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Align = alClient
      DefaultRowHeight = 18
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goEditing]
      TabOrder = 0
      OnSetEditText = SelectedStateStringGridSetEditText
    end
  end
  object TrainPositionButton: TButton
    Left = 10
    Top = 302
    Width = 99
    Height = 33
    Margins.Left = 4
    Margins.Top = 4
    Margins.Right = 4
    Margins.Bottom = 4
    Caption = 'Train Position'
    TabOrder = 2
    OnClick = TrainPositionButtonClick
  end
end
