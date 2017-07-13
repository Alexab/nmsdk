object ManipulatorTestForm: TManipulatorTestForm
  Left = 0
  Top = 0
  Caption = #1052#1072#1085#1080#1087#1091#1083#1103#1090#1086#1088
  ClientHeight = 617
  ClientWidth = 647
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Image: TImage
    Left = 0
    Top = 0
    Width = 448
    Height = 217
    Align = alClient
    Center = True
    IncrementalDisplay = True
    Proportional = True
    ExplicitLeft = 128
    ExplicitTop = 56
    ExplicitWidth = 105
    ExplicitHeight = 105
  end
  object Panel1: TPanel
    Left = 0
    Top = 217
    Width = 647
    Height = 400
    Align = alBottom
    TabOrder = 0
    object Panel3: TPanel
      Left = 448
      Top = 1
      Width = 198
      Height = 398
      Align = alClient
      TabOrder = 0
      object IOChart: TChart
        Left = 1
        Top = 1
        Width = 196
        Height = 396
        Legend.Alignment = laBottom
        Title.Text.Strings = (
          'TChart')
        Title.Visible = False
        LeftAxis.Automatic = False
        LeftAxis.AutomaticMaximum = False
        LeftAxis.AutomaticMinimum = False
        LeftAxis.ExactDateTime = False
        LeftAxis.Increment = 1.000000000000000000
        LeftAxis.LabelsSeparation = 0
        LeftAxis.Maximum = 606.150000000000000000
        View3D = False
        Align = alClient
        TabOrder = 0
        DefaultCanvas = 'TGDIPlusCanvas'
        ColorPaletteIndex = 13
        object Series3: TBarSeries
          Title = 'RAngle'
          Shadow.Color = 8618883
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Bar'
          YValues.Order = loNone
          Data = {
            00060000000000000000887D400000000000E080400000000000508440000000
            00001C81400000000000C07C400000000000588140}
        end
        object Series1: TBarSeries
          Title = 'RSpeed'
          Shadow.Color = 8750469
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Bar'
          YValues.Order = loNone
        end
        object Series2: TBarSeries
          SeriesColor = clBlue
          Title = 'RMoment'
          Shadow.Color = 8618883
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Bar'
          YValues.Order = loNone
        end
        object Series4: TBarSeries
          SeriesColor = 8421631
          Title = 'SAngle'
          Shadow.Color = 8618883
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Bar'
          YValues.Order = loNone
        end
        object Series5: TBarSeries
          SeriesColor = clLime
          Title = 'SSpeed'
          Shadow.Color = 8618883
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Bar'
          YValues.Order = loNone
        end
        object Series6: TBarSeries
          SeriesColor = 16744448
          Title = 'SMoment'
          Shadow.Color = 8684676
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Bar'
          YValues.Order = loNone
        end
      end
    end
    object Panel4: TPanel
      Left = 1
      Top = 1
      Width = 447
      Height = 398
      Align = alLeft
      TabOrder = 1
      object Label4: TLabel
        Left = 12
        Top = 74
        Width = 127
        Height = 13
        Caption = #1052#1085#1086#1078#1080#1090#1077#1083#1100' '#1085#1072#1087#1088#1103#1078#1077#1085#1080#1103':'
      end
      object Label1: TLabel
        Left = 13
        Top = 4
        Width = 38
        Height = 13
        Caption = #1052#1086#1084#1077#1085#1090
      end
      object Label7: TLabel
        Left = 14
        Top = 115
        Width = 97
        Height = 13
        Caption = #1042#1088#1077#1084#1103' '#1091#1087#1088#1072#1074#1083#1077#1085#1080#1103':'
      end
      object Label8: TLabel
        Left = 14
        Top = 163
        Width = 145
        Height = 13
        Caption = #1055#1086#1089#1090'. '#1074#1088#1077#1084#1077#1085#1080' '#1088#1072#1079#1088#1103#1076#1072' PAC:'
      end
      object Label9: TLabel
        Left = 16
        Top = 211
        Width = 139
        Height = 13
        Caption = #1055#1086#1089#1090'. '#1074#1088#1077#1084#1077#1085#1080' '#1079#1072#1088#1103#1076#1072' PAC:'
      end
      object Label12: TLabel
        Left = 14
        Top = 257
        Width = 77
        Height = 13
        Caption = #1056#1077#1078#1080#1084' '#1088#1072#1073#1086#1090#1099':'
      end
      object MomentTrackBar: TTrackBar
        Left = 5
        Top = 18
        Width = 340
        Height = 27
        Max = 1000
        Min = -1000
        TabOrder = 0
        OnChange = MomentTrackBarChange
      end
      object MomentProgressBar: TProgressBar
        Left = 13
        Top = 53
        Width = 245
        Height = 17
        Max = 1000
        TabOrder = 1
      end
      object ExtMomentEdit: TEdit
        Left = 264
        Top = 51
        Width = 73
        Height = 21
        Color = clBtnFace
        ReadOnly = True
        TabOrder = 2
        Text = '0'
      end
      object RadioGroup1: TRadioGroup
        Left = 343
        Top = 13
        Width = 98
        Height = 59
        Caption = ' '#1054#1059
        Enabled = False
        ItemIndex = 0
        Items.Strings = (
          #1052#1086#1076#1077#1083#1100
          #1052#1072#1085#1080#1087#1091#1083#1103#1090#1086#1088)
        TabOrder = 3
        OnClick = RadioGroup1Click
      end
      object EngineOutputsLabeledEdit: TLabeledEdit
        Left = 7
        Top = 321
        Width = 199
        Height = 21
        EditLabel.Width = 98
        EditLabel.Height = 13
        EditLabel.Caption = #1042#1099#1093#1086#1076#1099' '#1076#1074#1080#1075#1072#1090#1077#1083#1103
        TabOrder = 4
      end
      object VoltageMulTrackBar: TTrackBar
        Left = 5
        Top = 88
        Width = 141
        Height = 27
        Max = 5000
        Position = 200
        TabOrder = 5
        OnChange = VoltageMulTrackBarChange
      end
      object VoltageLabeledEdit: TLabeledEdit
        Left = 212
        Top = 321
        Width = 108
        Height = 21
        EditLabel.Width = 63
        EditLabel.Height = 13
        EditLabel.Caption = #1053#1072#1087#1088#1103#1078#1077#1085#1080#1077
        TabOrder = 6
      end
      object VoltageMulEdit: TEdit
        Left = 144
        Top = 90
        Width = 48
        Height = 21
        TabOrder = 7
        Text = '1'
      end
      object TimeLabeledEdit: TLabeledEdit
        Left = 7
        Top = 361
        Width = 434
        Height = 21
        EditLabel.Width = 98
        EditLabel.Height = 13
        EditLabel.Caption = #1042#1099#1093#1086#1076#1099' '#1076#1074#1080#1075#1072#1090#1077#1083#1103
        TabOrder = 8
      end
      object TimeDurationTrackBar: TTrackBar
        Left = 5
        Top = 130
        Width = 141
        Height = 27
        Max = 256
        Min = 1
        Position = 1
        TabOrder = 9
        OnChange = TimeDurationTrackBarChange
      end
      object TimeDurationEdit: TEdit
        Left = 144
        Top = 132
        Width = 48
        Height = 21
        TabOrder = 10
        Text = '1'
      end
      object PACDeactivatorTimeTrackBar: TTrackBar
        Left = 5
        Top = 178
        Width = 141
        Height = 27
        Max = 10000
        Min = 10
        Position = 100
        TabOrder = 11
        OnChange = PACDeactivatorTimeTrackBarChange
      end
      object PACDeactivatorTimeEdit: TEdit
        Left = 144
        Top = 180
        Width = 48
        Height = 21
        TabOrder = 12
        Text = '1'
      end
      object PACActivatorTimeTrackBar: TTrackBar
        Left = 7
        Top = 226
        Width = 141
        Height = 27
        Max = 10000
        Min = 10
        Position = 10
        TabOrder = 13
        OnChange = PACActivatorTimeTrackBarChange
      end
      object PACActivatorTimeEdit: TEdit
        Left = 146
        Top = 228
        Width = 48
        Height = 21
        TabOrder = 14
        Text = '1'
      end
      object GroupBox2: TGroupBox
        Left = 264
        Top = 74
        Width = 178
        Height = 231
        Caption = ' '#1059#1087#1088#1072#1074#1083#1077#1085#1080#1077' '#1091#1089#1090#1088#1086#1081#1089#1090#1074#1086#1084' '
        TabOrder = 15
        object Label5: TLabel
          Left = 3
          Top = 22
          Width = 27
          Height = 13
          Caption = 'COM:'
        end
        object Label6: TLabel
          Left = 3
          Top = 46
          Width = 32
          Height = 13
          Caption = 'Servo:'
        end
        object Label10: TLabel
          Left = 11
          Top = 204
          Width = 16
          Height = 13
          Caption = 'Vd:'
        end
        object Label11: TLabel
          Left = 11
          Top = 180
          Width = 16
          Height = 13
          Caption = 'Va:'
        end
        object OnDeviceButton: TButton
          Left = 3
          Top = 70
          Width = 172
          Height = 25
          Caption = #1042#1082#1083#1102#1095#1080#1090#1100
          TabOrder = 0
          OnClick = OnDeviceButtonClick
        end
        object OffDeviceButton: TButton
          Left = 3
          Top = 101
          Width = 172
          Height = 25
          Caption = #1054#1090#1082#1083#1102#1095#1080#1090#1100
          Enabled = False
          TabOrder = 1
          OnClick = OffDeviceButtonClick
        end
        object EmulatorCheckBox: TCheckBox
          Left = 6
          Top = 127
          Width = 145
          Height = 17
          Caption = #1069#1084#1091#1083#1103#1094#1080#1103' '#1084#1072#1085#1080#1087#1091#1083#1103#1090#1086#1088#1072
          Checked = True
          State = cbChecked
          TabOrder = 2
          OnClick = EmulatorCheckBoxClick
        end
        object ComPortEdit: TEdit
          Left = 36
          Top = 19
          Width = 48
          Height = 21
          TabOrder = 3
          Text = '7'
        end
        object ServoNumberEdit: TEdit
          Left = 36
          Top = 43
          Width = 48
          Height = 21
          TabOrder = 4
          Text = '1'
          OnChange = ServoNumberEditChange
        end
        object SwapOutputVoltageDirectionCheckBox: TCheckBox
          Left = 6
          Top = 148
          Width = 160
          Height = 17
          Caption = #1057#1084#1077#1085#1080#1090#1100' '#1079#1085#1072#1082' '#1091#1087#1088#1072#1074#1083#1077#1085#1080#1103
          TabOrder = 5
          OnClick = SwapOutputVoltageDirectionCheckBoxClick
        end
        object VdEdit: TEdit
          Left = 30
          Top = 201
          Width = 48
          Height = 21
          TabOrder = 6
          Text = '5'
          OnChange = ServoNumberEditChange
        end
        object VaEdit: TEdit
          Left = 30
          Top = 177
          Width = 48
          Height = 21
          TabOrder = 7
          Text = '100'
        end
        object SendVButton: TButton
          Left = 84
          Top = 179
          Width = 91
          Height = 42
          Caption = #1054#1090#1087#1088#1072#1074#1080#1090#1100
          TabOrder = 8
          OnClick = SendVButtonClick
        end
      end
      object ControlDurationLabeledEdit: TLabeledEdit
        Left = 326
        Top = 321
        Width = 108
        Height = 21
        EditLabel.Width = 93
        EditLabel.Height = 13
        EditLabel.Caption = #1042#1088#1077#1084#1103' '#1091#1087#1088#1072#1074#1083#1077#1085#1080#1103
        TabOrder = 16
      end
      object MulToNumberOfControlElementsCheckBox: TCheckBox
        Left = 198
        Top = 92
        Width = 50
        Height = 17
        Caption = #1087#1086' N'
        TabOrder = 17
      end
      object WorkModeComboBox: TComboBox
        Left = 14
        Top = 272
        Width = 178
        Height = 21
        ItemIndex = 0
        TabOrder = 18
        Text = #1050#1086#1084#1072#1085#1076#1085#1099#1081
        OnSelect = WorkModeComboBoxSelect
        Items.Strings = (
          #1050#1086#1084#1072#1085#1076#1085#1099#1081
          #1053#1077#1081#1088#1086)
      end
    end
  end
  object Panel2: TPanel
    Left = 448
    Top = 0
    Width = 199
    Height = 217
    Align = alRight
    TabOrder = 1
    object GroupBox1: TGroupBox
      Left = 1
      Top = 1
      Width = 197
      Height = 215
      Align = alClient
      Caption = ' '#1042#1085#1077#1096#1085#1077#1077' '#1091#1087#1088#1072#1074#1083#1077#1085#1080#1077' '
      TabOrder = 0
      DesignSize = (
        197
        215)
      object Label2: TLabel
        Left = 12
        Top = 18
        Width = 163
        Height = 13
        Caption = 'II Afferent ext. control frequency'
      end
      object Label3: TLabel
        Left = 12
        Top = 77
        Width = 174
        Height = 13
        Caption = 'Number of II Afferents ext. controls'
      end
      object IIAfferentTrackBar: TTrackBar
        Left = 2
        Top = 37
        Width = 146
        Height = 27
        Anchors = [akLeft, akTop, akRight]
        Max = 200
        Min = -200
        TabOrder = 0
        OnChange = IIAfferentTrackBarChange
      end
      object IIAfferentEdit: TEdit
        Left = 148
        Top = 37
        Width = 44
        Height = 21
        Anchors = [akTop, akRight]
        Color = clBtnFace
        ReadOnly = True
        TabOrder = 1
        Text = '0'
        OnChange = IIAfferentEditChange
      end
      object IINumAfferentTrackBar: TTrackBar
        Left = 2
        Top = 93
        Width = 146
        Height = 27
        Anchors = [akLeft, akTop, akRight]
        Max = 5
        TabOrder = 2
        OnChange = IINumAfferentTrackBarChange
      end
      object IINumAfferentEdit: TEdit
        Left = 148
        Top = 93
        Width = 44
        Height = 21
        Anchors = [akTop, akRight]
        Color = clBtnFace
        ReadOnly = True
        TabOrder = 3
        Text = '0'
        OnChange = IINumAfferentEditChange
      end
      object IaCheckBox: TCheckBox
        Left = 5
        Top = 129
        Width = 305
        Height = 17
        Caption = #1054#1057' '#1087#1086' '#1091#1075#1083#1086#1074#1086#1081' '#1089#1082#1086#1088#1086#1089#1090#1080' (Ia) '
        Checked = True
        State = cbChecked
        TabOrder = 4
        OnClick = IaCheckBoxClick
      end
      object IbCheckBox: TCheckBox
        Left = 5
        Top = 150
        Width = 305
        Height = 17
        Caption = #1054#1057' '#1087#1086' '#1082#1088#1091#1090#1103#1097#1077#1084#1091' '#1084#1086#1084#1077#1085#1090#1091' (Ib) '
        TabOrder = 5
        OnClick = IbCheckBoxClick
      end
      object IICheckBox: TCheckBox
        Left = 5
        Top = 170
        Width = 305
        Height = 17
        Caption = #1054#1057' '#1087#1086' '#1091#1075#1083#1091' (II) '
        Checked = True
        State = cbChecked
        TabOrder = 6
        OnClick = IICheckBoxClick
      end
      object ControlVoltageCheckBox: TCheckBox
        Left = 5
        Top = 193
        Width = 181
        Height = 17
        Caption = #1059#1087#1088#1072#1074#1083#1103#1102#1097#1077#1077' '#1074#1086#1079#1076#1077#1081#1089#1090#1074#1080#1077' (U) '
        Checked = True
        State = cbChecked
        TabOrder = 7
        OnClick = ControlVoltageCheckBoxClick
      end
    end
  end
end
