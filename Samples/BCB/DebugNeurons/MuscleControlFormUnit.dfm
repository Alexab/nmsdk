object MuscleControlForm: TMuscleControlForm
  Left = 686
  Top = 0
  Caption = 'MuscleControlForm'
  ClientHeight = 469
  ClientWidth = 474
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  OnHide = FormHide
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 474
    Height = 240
    Align = alClient
    TabOrder = 0
    object Panel3: TPanel
      Left = 1
      Top = 1
      Width = 232
      Height = 238
      Align = alLeft
      TabOrder = 0
      object GroupBox1: TGroupBox
        Left = 1
        Top = 1
        Width = 230
        Height = 56
        Align = alTop
        Caption = ' '#1040#1084#1087#1083#1080#1090#1091#1076#1072' '#1072#1092#1092#1077#1088#1077#1090#1085#1086#1075#1086' '#1074#1093#1086#1076#1072' 1'
        TabOrder = 0
        object AfferentEdit1: TEdit
          Left = 176
          Top = 16
          Width = 49
          Height = 21
          TabOrder = 0
          Text = '0'
          OnChange = AfferentEdit1Change
        end
        object Afferent1TrackBar: TTrackBar
          Left = 3
          Top = 16
          Width = 174
          Height = 33
          Max = 100
          TabOrder = 1
          OnChange = Afferent1TrackBarChange
        end
      end
      object GroupBox2: TGroupBox
        Left = 1
        Top = 113
        Width = 230
        Height = 56
        Align = alTop
        Caption = ' '#1063#1072#1089#1090#1086#1090#1072' '#1075#1077#1085#1077#1088#1072#1090#1086#1088#1072', '#1043#1094' '
        TabOrder = 1
        object AfferentEdit3: TEdit
          Left = 176
          Top = 16
          Width = 49
          Height = 21
          TabOrder = 0
          Text = '0'
          OnChange = AfferentEdit3Change
        end
        object Afferent3TrackBar: TTrackBar
          Left = 3
          Top = 17
          Width = 174
          Height = 33
          Max = 300
          TabOrder = 1
          OnChange = Afferent3TrackBarChange
        end
      end
      object GroupBox3: TGroupBox
        Left = 1
        Top = 169
        Width = 230
        Height = 64
        Align = alTop
        Caption = ' '#1054#1057' '#1082#1083#1077#1090#1082#1080' '#1056#1077#1096#1085#1086#1091' '
        TabOrder = 2
        object FBRenshowCheckBox1: TCheckBox
          Left = 16
          Top = 16
          Width = 193
          Height = 17
          Caption = ' '#1054#1057' 1 '#1042#1082#1083
          Checked = True
          State = cbChecked
          TabOrder = 0
          OnClick = FBRenshowCheckBox1Click
        end
        object FBRenshowCheckBox2: TCheckBox
          Left = 16
          Top = 39
          Width = 193
          Height = 17
          Caption = ' '#1054#1057' 2 '#1042#1082#1083
          Checked = True
          State = cbChecked
          TabOrder = 1
          OnClick = FBRenshowCheckBox2Click
        end
      end
      object GroupBox6: TGroupBox
        Left = 1
        Top = 57
        Width = 230
        Height = 56
        Align = alTop
        Caption = ' '#1040#1084#1087#1083#1080#1090#1091#1076#1072' '#1072#1092#1092#1077#1088#1077#1090#1085#1086#1075#1086' '#1074#1093#1086#1076#1072' 2'
        TabOrder = 3
        object AfferentEdit2: TEdit
          Left = 176
          Top = 16
          Width = 49
          Height = 21
          TabOrder = 0
          Text = '0'
          OnChange = AfferentEdit2Change
        end
        object Afferent2TrackBar: TTrackBar
          Left = 3
          Top = 16
          Width = 174
          Height = 33
          Max = 100
          TabOrder = 1
          OnChange = Afferent2TrackBarChange
        end
      end
    end
    object Panel4: TPanel
      Left = 233
      Top = 1
      Width = 240
      Height = 238
      Align = alClient
      TabOrder = 1
      object GroupBox4: TGroupBox
        Left = 1
        Top = 57
        Width = 238
        Height = 56
        Align = alTop
        Caption = ' '#1052#1072#1089#1089#1072' '#1085#1072#1075#1088#1091#1079#1082#1080' '#1084#1099#1096#1094#1099' 2 '
        TabOrder = 0
        object MuscleMassEdit2: TEdit
          Left = 176
          Top = 16
          Width = 49
          Height = 21
          TabOrder = 0
          Text = '1'
          OnChange = MuscleMassEdit2Change
        end
        object MuscleMassTrackBar2: TTrackBar
          Left = 3
          Top = 16
          Width = 174
          Height = 33
          Max = 100
          Min = 1
          Position = 1
          TabOrder = 1
          OnChange = MuscleMassTrackBar2Change
        end
      end
      object GroupBox5: TGroupBox
        Left = 1
        Top = 1
        Width = 238
        Height = 56
        Align = alTop
        Caption = ' '#1052#1072#1089#1089#1072' '#1085#1072#1075#1088#1091#1079#1082#1080' '#1084#1099#1096#1094#1099' 1 '
        TabOrder = 1
        object MuscleMassEdit1: TEdit
          Left = 176
          Top = 16
          Width = 49
          Height = 21
          TabOrder = 0
          Text = '1'
          OnChange = MuscleMassEdit1Change
        end
        object MuscleMassTrackBar1: TTrackBar
          Left = 3
          Top = 16
          Width = 174
          Height = 33
          Max = 100
          Min = 1
          Position = 1
          TabOrder = 1
          OnChange = MuscleMassTrackBar1Change
        end
      end
      object GroupBox11: TGroupBox
        Left = 1
        Top = 113
        Width = 238
        Height = 56
        Align = alTop
        Caption = ' '#1044#1083#1080#1085#1072' '#1084#1099#1096#1094#1099' 1 '
        TabOrder = 2
        object LengthEdit1: TEdit
          Left = 176
          Top = 16
          Width = 49
          Height = 21
          TabOrder = 0
          Text = '0'
          OnChange = LengthEdit1Change
        end
        object LengthTrackBar1: TTrackBar
          Left = 3
          Top = 16
          Width = 174
          Height = 33
          Max = 1000
          Min = 1
          Position = 1
          TabOrder = 1
          OnChange = LengthTrackBar1Change
        end
      end
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 240
    Width = 474
    Height = 229
    Align = alBottom
    TabOrder = 1
    object Panel5: TPanel
      Left = 1
      Top = 1
      Width = 232
      Height = 227
      Align = alLeft
      TabOrder = 0
      object GroupBox7: TGroupBox
        Left = 1
        Top = 169
        Width = 230
        Height = 56
        Align = alTop
        Caption = ' Renshow2Deactivator, '#1043#1094' '
        TabOrder = 0
        object Renshow2DeactivatorEdit: TEdit
          Left = 176
          Top = 16
          Width = 49
          Height = 21
          TabOrder = 0
          Text = '0'
          OnChange = Renshow2DeactivatorEditChange
        end
        object Renshow2DeactivatorTrackBar: TTrackBar
          Left = 3
          Top = 16
          Width = 174
          Height = 33
          Max = 300
          TabOrder = 1
          OnChange = Renshow2DeactivatorTrackBarChange
        end
      end
      object GroupBox8: TGroupBox
        Left = 1
        Top = 1
        Width = 230
        Height = 56
        Align = alTop
        Caption = ' Renshow1Activator, '#1043#1094' '
        TabOrder = 1
        object Renshow1ActivatorEdit: TEdit
          Left = 176
          Top = 16
          Width = 49
          Height = 21
          TabOrder = 0
          Text = '0'
          OnChange = Renshow1ActivatorEditChange
        end
        object Renshow1ActivatorTrackBar: TTrackBar
          Left = 3
          Top = 16
          Width = 174
          Height = 33
          Max = 300
          TabOrder = 1
          OnChange = Renshow1ActivatorTrackBarChange
        end
      end
      object GroupBox9: TGroupBox
        Left = 1
        Top = 113
        Width = 230
        Height = 56
        Align = alTop
        Caption = ' Renshow2Activator, '#1043#1094' '
        TabOrder = 2
        object Renshow2ActivatorEdit: TEdit
          Left = 178
          Top = 16
          Width = 49
          Height = 21
          TabOrder = 0
          Text = '0'
          OnChange = Renshow2ActivatorEditChange
        end
        object Renshow2ActivatorTrackBar: TTrackBar
          Left = 3
          Top = 16
          Width = 174
          Height = 33
          Max = 300
          TabOrder = 1
          OnChange = Renshow2ActivatorTrackBarChange
        end
      end
      object GroupBox10: TGroupBox
        Left = 1
        Top = 57
        Width = 230
        Height = 56
        Align = alTop
        Caption = ' Renshow1Deactivator, '#1043#1094' '
        TabOrder = 3
        object Renshow1DeactivatorEdit: TEdit
          Left = 176
          Top = 16
          Width = 49
          Height = 21
          TabOrder = 0
          Text = '0'
          OnChange = Renshow1DeactivatorEditChange
        end
        object Renshow1DeactivatorTrackBar: TTrackBar
          Left = 3
          Top = 16
          Width = 174
          Height = 33
          Max = 300
          TabOrder = 1
          OnChange = Renshow1DeactivatorTrackBarChange
        end
      end
    end
    object Panel6: TPanel
      Left = 233
      Top = 1
      Width = 240
      Height = 227
      Align = alClient
      TabOrder = 1
    end
  end
end
