object NManipulatorControlForm: TNManipulatorControlForm
  Left = 0
  Top = 0
  Caption = 'NManipulatorControlForm'
  ClientHeight = 514
  ClientWidth = 725
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object StatusBar1: TStatusBar
    Left = 0
    Top = 495
    Width = 725
    Height = 19
    Panels = <>
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 725
    Height = 495
    ActivePage = TabSheet3
    Align = alClient
    TabOrder = 1
    object TabSheet1: TTabSheet
      Caption = 'Communication'
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object GroupBox1: TGroupBox
        Left = 0
        Top = 102
        Width = 244
        Height = 365
        Align = alLeft
        Caption = ' Communication options '
        Enabled = False
        TabOrder = 0
        object Label1: TLabel
          Left = 7
          Top = 52
          Width = 61
          Height = 13
          Caption = 'COM port #:'
        end
        object Label2: TLabel
          Left = 19
          Top = 81
          Width = 50
          Height = 13
          Caption = 'Ctrl Mode:'
        end
        object ComPortComboBox: TComboBox
          Left = 78
          Top = 49
          Width = 157
          Height = 21
          Style = csDropDownList
          ItemIndex = 7
          TabOrder = 0
          Text = '7'
          Items.Strings = (
            '0'
            '1'
            '2'
            '3'
            '4'
            '5'
            '6'
            '7'
            '8'
            '9'
            '10'
            '11'
            '12'
            '13'
            '14'
            '15'
            '16'
            '17'
            '18'
            '19'
            '20'
            '21'
            '22'
            '23'
            '24'
            '25'
            '26'
            '27'
            '28'
            '29'
            '30')
        end
        object DeviceModeRadioButton: TRadioButton
          Left = 7
          Top = 25
          Width = 228
          Height = 18
          Caption = 'Device mode'
          Checked = True
          TabOrder = 1
          TabStop = True
          OnClick = DeviceModeRadioButtonClick
        end
        object EmulatorModeRadioButton: TRadioButton
          Left = 3
          Top = 108
          Width = 119
          Height = 18
          Caption = 'Emulator mode'
          TabOrder = 2
          OnClick = EmulatorModeRadioButtonClick
        end
        object ControlModeComboBox: TComboBox
          Left = 78
          Top = 78
          Width = 157
          Height = 21
          Style = csDropDownList
          ItemIndex = 2
          TabOrder = 3
          Text = 'Command mode'
          Items.Strings = (
            'Not set'
            'Test mode'
            'Command mode'
            'Neuro control')
        end
      end
      object GroupBox2: TGroupBox
        Left = 0
        Top = 0
        Width = 717
        Height = 51
        Align = alTop
        Caption = ' Manipulator component name  '
        TabOrder = 1
        object ComponentSelectionPanel: TPanel
          Left = 2
          Top = 15
          Width = 713
          Height = 34
          Align = alClient
          Caption = 'Double click to select control object component '
          Color = clRed
          ParentBackground = False
          TabOrder = 0
          OnDblClick = ComponentSelectionPanelDblClick
        end
      end
      object GroupBox3: TGroupBox
        Left = 244
        Top = 102
        Width = 473
        Height = 365
        Align = alClient
        Caption = ' Communication control '
        Enabled = False
        TabOrder = 2
        DesignSize = (
          473
          365)
        object ConnectButton: TButton
          Left = 6
          Top = 21
          Width = 464
          Height = 26
          Anchors = [akLeft, akTop, akRight]
          Caption = ' Connect '
          TabOrder = 0
          OnClick = ConnectButtonClick
        end
        object DisconnectButton: TButton
          Left = 6
          Top = 54
          Width = 464
          Height = 25
          Anchors = [akLeft, akTop, akRight]
          Caption = ' Disconnect '
          Enabled = False
          TabOrder = 1
          OnClick = DisconnectButtonClick
        end
        object ResetButton: TButton
          Left = 6
          Top = 150
          Width = 464
          Height = 27
          Anchors = [akLeft, akTop, akRight]
          Caption = ' Reset '
          Enabled = False
          TabOrder = 2
          OnClick = ResetButtonClick
        end
        object StartButton: TButton
          Left = 6
          Top = 86
          Width = 464
          Height = 26
          Anchors = [akLeft, akTop, akRight]
          Caption = ' Start '
          Enabled = False
          TabOrder = 3
          OnClick = StartButtonClick
        end
        object StopButton: TButton
          Left = 6
          Top = 118
          Width = 464
          Height = 26
          Anchors = [akLeft, akTop, akRight]
          Caption = ' Stop '
          Enabled = False
          TabOrder = 4
          OnClick = StopButtonClick
        end
      end
      object GroupBox6: TGroupBox
        Left = 0
        Top = 51
        Width = 717
        Height = 51
        Align = alTop
        Caption = ' Control system component name  '
        TabOrder = 3
        object ControlSystemSelectionPanel: TPanel
          Left = 2
          Top = 15
          Width = 713
          Height = 34
          Align = alClient
          Caption = 'Double click to select control system'
          Color = clRed
          ParentBackground = False
          TabOrder = 0
          OnDblClick = ControlSystemSelectionPanelDblClick
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Manual Control'
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object GroupBox4: TGroupBox
        Left = 0
        Top = 0
        Width = 194
        Height = 467
        Align = alLeft
        Caption = ' Servo Control '
        TabOrder = 0
        object Time: TLabel
          Left = 8
          Top = 126
          Width = 22
          Height = 13
          Caption = 'Time'
        end
        object Speed: TLabel
          Left = 8
          Top = 68
          Width = 30
          Height = 13
          Caption = 'Speed'
        end
        object Label3: TLabel
          Left = 58
          Top = 20
          Width = 42
          Height = 13
          Caption = 'Direction'
        end
        object Label4: TLabel
          Left = 7
          Top = 20
          Width = 39
          Height = 13
          Caption = 'Servo #'
        end
        object Button2: TButton
          Left = 4
          Top = 183
          Width = 179
          Height = 27
          Caption = 'Move'
          TabOrder = 0
          OnClick = Button2Click
        end
        object TrackBarTime: TTrackBar
          Left = 0
          Top = 142
          Width = 190
          Height = 35
          Max = 255
          Frequency = 8
          Position = 32
          TabOrder = 1
        end
        object TrackBarPWM: TTrackBar
          Left = 0
          Top = 85
          Width = 190
          Height = 34
          Max = 255
          Frequency = 8
          Position = 128
          TabOrder = 2
        end
        object ComboBoxDir: TComboBox
          Left = 58
          Top = 40
          Width = 124
          Height = 21
          Style = csDropDownList
          ItemIndex = 0
          TabOrder = 3
          Text = 'CV'
          Items.Strings = (
            'CV'
            'CCV')
        end
        object CBoxServoMove: TComboBox
          Left = 7
          Top = 40
          Width = 43
          Height = 21
          Style = csDropDownList
          ItemIndex = 0
          TabOrder = 4
          Text = '0'
          Items.Strings = (
            '0'
            '1')
        end
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Neuro Control'
      ImageIndex = 2
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object GroupBox5: TGroupBox
        Left = 0
        Top = 0
        Width = 210
        Height = 467
        Align = alLeft
        Caption = ' External control '
        TabOrder = 0
        object Label5: TLabel
          Left = 13
          Top = 19
          Width = 163
          Height = 13
          Caption = 'II Afferent ext. control frequency'
        end
        object Label6: TLabel
          Left = 13
          Top = 81
          Width = 174
          Height = 13
          Caption = 'Number of II Afferents ext. controls'
        end
        object IIAfferentTrackBar: TTrackBar
          Left = 4
          Top = 38
          Width = 153
          Height = 29
          Max = 200
          Min = -200
          TabOrder = 0
          OnChange = IIAfferentTrackBarChange
        end
        object IIAfferentEdit: TEdit
          Left = 155
          Top = 38
          Width = 46
          Height = 21
          Color = clBtnFace
          ReadOnly = True
          TabOrder = 1
          Text = '0'
        end
        object IINumAfferentTrackBar: TTrackBar
          Left = 3
          Top = 100
          Width = 153
          Height = 28
          Max = 5
          TabOrder = 2
          OnChange = IINumAfferentTrackBarChange
        end
        object IINumAfferentEdit: TEdit
          Left = 155
          Top = 98
          Width = 46
          Height = 21
          Color = clBtnFace
          ReadOnly = True
          TabOrder = 3
          Text = '0'
        end
        object IaCheckBox: TCheckBox
          Left = 6
          Top = 134
          Width = 188
          Height = 18
          Caption = 'FB by angle speed (Ia) '
          TabOrder = 4
          OnClick = IaCheckBoxClick
        end
        object IbCheckBox: TCheckBox
          Left = 6
          Top = 158
          Width = 188
          Height = 18
          Caption = 'FB by moment (Ib) '
          TabOrder = 5
          OnClick = IbCheckBoxClick
        end
        object IICheckBox: TCheckBox
          Left = 6
          Top = 178
          Width = 195
          Height = 18
          Caption = 'FB by angle (II) '
          Checked = True
          State = cbChecked
          TabOrder = 6
          OnClick = IICheckBoxClick
        end
        object ControlVoltageCheckBox: TCheckBox
          Left = 6
          Top = 218
          Width = 188
          Height = 17
          Caption = 'Control power (U) '
          Checked = True
          State = cbChecked
          TabOrder = 7
          OnClick = ControlVoltageCheckBoxClick
        end
        object GroupBox10: TGroupBox
          Left = 2
          Top = 379
          Width = 206
          Height = 86
          Align = alBottom
          Caption = ' Target position '
          TabOrder = 8
          DesignSize = (
            206
            86)
          object MomentTrackBar: TTrackBar
            Left = 3
            Top = 19
            Width = 124
            Height = 28
            Anchors = [akLeft, akTop, akRight]
            Max = 10000
            Min = -10000
            TabOrder = 0
            OnChange = MomentTrackBarChange
          end
          object MomentProgressBar: TProgressBar
            Left = 14
            Top = 55
            Width = 104
            Height = 19
            Anchors = [akLeft, akTop, akRight]
            Max = 1000
            TabOrder = 1
          end
          object ExtMomentEdit: TEdit
            Left = 125
            Top = 54
            Width = 76
            Height = 21
            Anchors = [akTop, akRight]
            Color = clBtnFace
            ReadOnly = True
            TabOrder = 2
            Text = '0'
          end
          object ResetToZeroButton2: TButton
            Left = 122
            Top = 18
            Width = 80
            Height = 29
            Caption = 'Reset to 0'
            TabOrder = 3
            OnClick = ResetToZeroButton2Click
          end
        end
        object CheckBox1: TCheckBox
          Left = 6
          Top = 197
          Width = 195
          Height = 17
          Caption = 'FB by movement (Ic) '
          Checked = True
          State = cbChecked
          TabOrder = 9
          OnClick = CheckBox1Click
        end
        object GroupBox11: TGroupBox
          Left = 2
          Top = 294
          Width = 206
          Height = 85
          Align = alBottom
          Caption = ' External power  '
          TabOrder = 10
          DesignSize = (
            206
            85)
          object MovementControlTrackBar: TTrackBar
            Left = 6
            Top = 19
            Width = 121
            Height = 28
            Anchors = [akLeft, akTop, akRight]
            Max = 1000
            Min = -1000
            TabOrder = 0
            OnChange = MovementControlTrackBarChange
          end
          object MovementControlProgressBar: TProgressBar
            Left = 14
            Top = 55
            Width = 103
            Height = 19
            Anchors = [akLeft, akTop, akRight]
            Max = 1000
            TabOrder = 1
          end
          object MovementControlEdit: TEdit
            Left = 123
            Top = 54
            Width = 76
            Height = 21
            Anchors = [akTop, akRight]
            Color = clBtnFace
            ReadOnly = True
            TabOrder = 2
            Text = '0'
          end
          object ResetToZeroButton1: TButton
            Left = 122
            Top = 18
            Width = 80
            Height = 29
            Caption = 'Reset to 0'
            TabOrder = 3
            OnClick = ResetToZeroButton1Click
          end
        end
        object HideSecondaryGuiCheckBox: TCheckBox
          Left = 6
          Top = 242
          Width = 198
          Height = 17
          Caption = 'Hide secondary GUI'
          TabOrder = 11
          OnClick = HideSecondaryGuiCheckBoxClick
        end
      end
      object Panel1: TPanel
        Left = 210
        Top = 0
        Width = 507
        Height = 467
        Align = alClient
        TabOrder = 1
        object Splitter1: TSplitter
          Left = 1
          Top = 216
          Width = 505
          Height = 13
          Cursor = crVSplit
          Align = alBottom
          ExplicitTop = 215
        end
        object GroupBox7: TGroupBox
          Left = 1
          Top = 1
          Width = 505
          Height = 215
          Align = alClient
          Caption = ' Visual output '
          DoubleBuffered = False
          ParentDoubleBuffered = False
          TabOrder = 0
          object Splitter2: TSplitter
            Left = 229
            Top = 15
            Width = 9
            Height = 198
            ExplicitTop = 16
            ExplicitHeight = 196
          end
          object Panel2: TPanel
            Left = 2
            Top = 15
            Width = 227
            Height = 198
            Align = alLeft
            TabOrder = 0
            object Label13: TLabel
              Left = 13
              Top = 10
              Width = 130
              Height = 13
              Caption = 'Charge PAC time constant:'
            end
            object Label8: TLabel
              Left = 17
              Top = 57
              Width = 142
              Height = 13
              Caption = 'Discharge PAC time constant:'
            end
            object Label10: TLabel
              Left = 14
              Top = 108
              Width = 69
              Height = 13
              Caption = 'PAC multiplier:'
            end
            object PACActivatorTimeTrackBar: TTrackBar
              Left = 6
              Top = 24
              Width = 147
              Height = 28
              Max = 10000
              Min = 10
              Position = 10
              TabOrder = 0
              OnChange = PACActivatorTimeTrackBarChange
            end
            object PACActivatorTimeEdit: TEdit
              Left = 150
              Top = 26
              Width = 51
              Height = 21
              TabOrder = 1
              Text = '1'
            end
            object PACDeactivatorTimeEdit: TEdit
              Left = 153
              Top = 74
              Width = 50
              Height = 21
              TabOrder = 2
              Text = '1'
            end
            object PACDeactivatorTimeTrackBar: TTrackBar
              Left = 7
              Top = 72
              Width = 148
              Height = 29
              Max = 10000
              Min = 10
              Position = 100
              TabOrder = 3
              OnChange = PACDeactivatorTimeTrackBarChange
            end
            object PACMultiplicatorTrackBar: TTrackBar
              Left = 7
              Top = 122
              Width = 148
              Height = 28
              Max = 1000
              Position = 10
              TabOrder = 4
              OnChange = PACMultiplicatorTrackBarChange
            end
            object PACMultiplicatorEdit: TEdit
              Left = 153
              Top = 125
              Width = 50
              Height = 21
              TabOrder = 5
              Text = '1'
            end
          end
          object Panel3: TPanel
            Left = 238
            Top = 15
            Width = 265
            Height = 198
            Align = alClient
            TabOrder = 1
            object DrawGrid: TDrawGrid
              Left = 1
              Top = 1
              Width = 263
              Height = 196
              Align = alClient
              ColCount = 1
              DoubleBuffered = True
              FixedCols = 0
              RowCount = 1
              FixedRows = 0
              ParentDoubleBuffered = False
              TabOrder = 0
              OnDrawCell = DrawGridDrawCell
            end
          end
        end
        object GroupBox8: TGroupBox
          Left = 1
          Top = 229
          Width = 505
          Height = 237
          Align = alBottom
          Caption = ' Neuro manipulator parameters '
          TabOrder = 1
          object Label12: TLabel
            Left = 14
            Top = 111
            Width = 16
            Height = 13
            Caption = 'Va:'
          end
          object Label11: TLabel
            Left = 96
            Top = 111
            Width = 16
            Height = 13
            Caption = 'Vd:'
          end
          object Label7: TLabel
            Left = 14
            Top = 60
            Width = 174
            Height = 13
            Caption = 'Controller power time duration (ms):'
          end
          object Label9: TLabel
            Left = 13
            Top = 17
            Width = 85
            Height = 13
            Caption = 'Voltage multiplier:'
          end
          object VaEdit: TEdit
            Left = 34
            Top = 108
            Width = 51
            Height = 21
            TabOrder = 0
            Text = '100'
          end
          object VdEdit: TEdit
            Left = 116
            Top = 108
            Width = 50
            Height = 21
            TabOrder = 1
            Text = '5'
          end
          object SendVButton: TButton
            Left = 173
            Top = 106
            Width = 95
            Height = 26
            Caption = #1054#1090#1087#1088#1072#1074#1080#1090#1100
            TabOrder = 2
            OnClick = SendVButtonClick
          end
          object VoltageMulTrackBar: TTrackBar
            Left = 6
            Top = 31
            Width = 147
            Height = 29
            Max = 5000
            Position = 200
            TabOrder = 3
            OnChange = VoltageMulTrackBarChange
          end
          object TimeDurationTrackBar: TTrackBar
            Left = 6
            Top = 75
            Width = 147
            Height = 28
            Max = 256
            Min = 1
            Position = 1
            TabOrder = 4
            OnChange = TimeDurationTrackBarChange
          end
          object VoltageMulEdit: TEdit
            Left = 150
            Top = 34
            Width = 51
            Height = 21
            TabOrder = 5
            Text = '1'
          end
          object TimeDurationEdit: TEdit
            Left = 150
            Top = 78
            Width = 51
            Height = 21
            TabOrder = 6
            Text = '1'
          end
          object MulToNumberOfControlElementsCheckBox: TCheckBox
            Left = 207
            Top = 35
            Width = 52
            Height = 19
            Caption = #1087#1086' N'
            TabOrder = 7
          end
          object SaveStatsButton: TButton
            Left = 15
            Top = 200
            Width = 75
            Height = 25
            Caption = 'Save Stats'
            TabOrder = 8
            OnClick = SaveStatsButtonClick
          end
          object NewStatsButton: TButton
            Left = 96
            Top = 200
            Width = 75
            Height = 25
            Caption = 'New Stats'
            TabOrder = 9
            OnClick = NewStatsButtonClick
          end
        end
      end
    end
  end
  object ImageList: TImageList
    Left = 456
    Top = 8
  end
  object MainMenu: TMainMenu
    Left = 384
    Top = 8
    object Communication1: TMenuItem
      Caption = 'Communication'
      object SelectManipulator1: TMenuItem
        Caption = 'Select Manipulator'
        OnClick = SelectManipulator1Click
      end
      object SelectControlSystem1: TMenuItem
        Caption = 'Select Control System'
        OnClick = SelectControlSystem1Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Connect1: TMenuItem
        Caption = 'Connect'
        OnClick = Connect1Click
      end
      object Disconnect1: TMenuItem
        Caption = 'Disconnect'
        OnClick = Disconnect1Click
      end
      object Start1: TMenuItem
        Caption = 'Start'
        OnClick = Start1Click
      end
      object Stop1: TMenuItem
        Caption = 'Stop'
        OnClick = Stop1Click
      end
      object Reset1: TMenuItem
        Caption = 'Reset'
        OnClick = Reset1Click
      end
    end
    object Move1: TMenuItem
      Caption = 'Move'
      object MoveLeft1: TMenuItem
        Caption = 'Move Left'
        OnClick = MoveLeft1Click
      end
      object MoveRight1: TMenuItem
        Caption = 'Move Right'
        OnClick = MoveRight1Click
      end
    end
  end
end
