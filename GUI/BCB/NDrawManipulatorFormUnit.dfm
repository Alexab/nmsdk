object NDrawManipulatorForm: TNDrawManipulatorForm
  Left = 0
  Top = 0
  Caption = 'NDrawManipulatorForm'
  ClientHeight = 526
  ClientWidth = 553
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  inline NDrawManipulatorFrame1: TNDrawManipulatorFrame
    Left = 0
    Top = 0
    Width = 553
    Height = 526
    Align = alClient
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    ExplicitWidth = 553
    ExplicitHeight = 526
    inherited Panel3: TPanel
      Width = 553
      Height = 526
      ExplicitWidth = 553
      ExplicitHeight = 526
      inherited Image: TImage
        Width = 551
        Height = 499
        ExplicitLeft = 1
        ExplicitTop = 1
        ExplicitWidth = 551
        ExplicitHeight = 499
      end
      inherited Button1: TButton
        Top = 500
        Width = 551
        ExplicitTop = 500
        ExplicitWidth = 551
      end
    end
  end
end
