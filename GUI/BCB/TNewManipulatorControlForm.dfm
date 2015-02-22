object NewManipulatorControlForm: TNewManipulatorControlForm
  Left = 0
  Top = 0
  Caption = 'NewManipulatorControlForm'
  ClientHeight = 643
  ClientWidth = 906
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 17
  object StatusBar1: TStatusBar
    Left = 0
    Top = 624
    Width = 906
    Height = 19
    Margins.Left = 4
    Margins.Top = 4
    Margins.Right = 4
    Margins.Bottom = 4
    Panels = <>
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 906
    Height = 624
    Margins.Left = 4
    Margins.Top = 4
    Margins.Right = 4
    Margins.Bottom = 4
    ActivePage = TabSheet3
    Align = alClient
    TabOrder = 1
    object TabSheet1: TTabSheet
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Caption = 'Communication'
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object GroupBox1: TGroupBox
        Left = 0
        Top = 128
        Width = 305
        Height = 464
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Align = alLeft
        Caption = ' Communication options '
        Enabled = False
        TabOrder = 0
        object Label1: TLabel
          Left = 9
          Top = 65
          Width = 78
          Height = 17
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Caption = 'COM port #:'
        end
        object Label2: TLabel
          Left = 24
          Top = 101
          Width = 63
          Height = 17
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Caption = 'Ctrl Mode:'
        end
        object ComPortComboBox: TComboBox
          Left = 97
          Top = 61
          Width = 197
          Height = 25
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
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
          Left = 9
          Top = 31
          Width = 285
          Height = 23
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Caption = 'Device mode'
          Checked = True
          TabOrder = 1
          TabStop = True
          OnClick = DeviceModeRadioButtonClick
        end
        object EmulatorModeRadioButton: TRadioButton
          Left = 4
          Top = 135
          Width = 148
          Height = 22
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Caption = 'Emulator mode'
          TabOrder = 2
          OnClick = EmulatorModeRadioButtonClick
        end
        object ControlModeComboBox: TComboBox
          Left = 97
          Top = 97
          Width = 197
          Height = 25
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
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
        Width = 898
        Height = 64
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Align = alTop
        Caption = ' Manipulator component name  '
        TabOrder = 1
        object ComponentSelectionPanel: TPanel
          Left = 2
          Top = 19
          Width = 894
          Height = 43
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Align = alClient
          Caption = 'Double click to select control object component '
          Color = clRed
          ParentBackground = False
          TabOrder = 0
          OnDblClick = ComponentSelectionPanelDblClick
        end
      end
      object GroupBox3: TGroupBox
        Left = 305
        Top = 128
        Width = 593
        Height = 464
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Align = alClient
        Caption = ' Communication control '
        Enabled = False
        TabOrder = 2
        DesignSize = (
          593
          464)
        object ConnectButton: TButton
          Left = 8
          Top = 26
          Width = 579
          Height = 33
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Anchors = [akLeft, akTop, akRight]
          Caption = ' Connect '
          TabOrder = 0
          OnClick = ConnectButtonClick
        end
        object DisconnectButton: TButton
          Left = 8
          Top = 67
          Width = 579
          Height = 32
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Anchors = [akLeft, akTop, akRight]
          Caption = ' Disconnect '
          Enabled = False
          TabOrder = 1
          OnClick = DisconnectButtonClick
        end
        object ResetButton: TButton
          Left = 8
          Top = 188
          Width = 579
          Height = 33
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Anchors = [akLeft, akTop, akRight]
          Caption = ' Reset '
          Enabled = False
          TabOrder = 2
          OnClick = ResetButtonClick
        end
        object StartButton: TButton
          Left = 8
          Top = 107
          Width = 579
          Height = 33
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Anchors = [akLeft, akTop, akRight]
          Caption = ' Start '
          Enabled = False
          TabOrder = 3
          OnClick = StartButtonClick
        end
        object StopButton: TButton
          Left = 8
          Top = 148
          Width = 579
          Height = 32
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Anchors = [akLeft, akTop, akRight]
          Caption = ' Stop '
          Enabled = False
          TabOrder = 4
          OnClick = StopButtonClick
        end
      end
      object GroupBox6: TGroupBox
        Left = 0
        Top = 64
        Width = 898
        Height = 64
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Align = alTop
        Caption = ' Control system component name  '
        TabOrder = 3
        object ControlSystemSelectionPanel: TPanel
          Left = 2
          Top = 19
          Width = 894
          Height = 43
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
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
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Caption = 'Manual Control'
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object GroupBox4: TGroupBox
        Left = 0
        Top = 0
        Width = 242
        Height = 592
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Align = alLeft
        Caption = ' Servo Control '
        TabOrder = 0
        object Время: TLabel
          Left = 10
          Top = 157
          Width = 29
          Height = 17
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Caption = 'Time'
        end
        object Скорость: TLabel
          Left = 10
          Top = 85
          Width = 38
          Height = 17
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Caption = 'Speed'
        end
        object Label3: TLabel
          Left = 72
          Top = 25
          Width = 54
          Height = 17
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Caption = 'Direction'
        end
        object Label4: TLabel
          Left = 9
          Top = 25
          Width = 50
          Height = 17
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Caption = 'Servo #'
        end
        object Button2: TButton
          Left = 5
          Top = 229
          Width = 224
          Height = 33
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Caption = 'Move'
          TabOrder = 0
          OnClick = Button2Click
        end
        object TrackBarTime: TTrackBar
          Left = 0
          Top = 178
          Width = 238
          Height = 43
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Max = 255
          Frequency = 8
          Position = 32
          TabOrder = 1
        end
        object TrackBarPWM: TTrackBar
          Left = 0
          Top = 106
          Width = 238
          Height = 43
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Max = 255
          Frequency = 8
          Position = 128
          TabOrder = 2
        end
        object ComboBoxDir: TComboBox
          Left = 72
          Top = 50
          Width = 156
          Height = 25
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Style = csDropDownList
          ItemIndex = 0
          TabOrder = 3
          Text = 'CV'
          Items.Strings = (
            'CV'
            'CCV')
        end
        object CBoxServoMove: TComboBox
          Left = 9
          Top = 50
          Width = 54
          Height = 25
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
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
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Caption = 'Neuro Control'
      ImageIndex = 2
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object GroupBox5: TGroupBox
        Left = 0
        Top = 0
        Width = 263
        Height = 592
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Align = alLeft
        Caption = ' External control '
        TabOrder = 0
        object Label5: TLabel
          Left = 16
          Top = 24
          Width = 201
          Height = 17
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Caption = 'II Afferent ext. control frequency'
        end
        object Label6: TLabel
          Left = 16
          Top = 101
          Width = 216
          Height = 17
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Caption = 'Number of II Afferents ext. controls'
        end
        object IIAfferentTrackBar: TTrackBar
          Left = 5
          Top = 48
          Width = 191
          Height = 36
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Max = 200
          Min = -200
          TabOrder = 0
          OnChange = IIAfferentTrackBarChange
        end
        object IIAfferentEdit: TEdit
          Left = 194
          Top = 48
          Width = 57
          Height = 25
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Color = clBtnFace
          ReadOnly = True
          TabOrder = 1
          Text = '0'
        end
        object IINumAfferentTrackBar: TTrackBar
          Left = 3
          Top = 122
          Width = 191
          Height = 35
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Max = 5
          TabOrder = 2
          OnChange = IINumAfferentTrackBarChange
        end
        object IINumAfferentEdit: TEdit
          Left = 194
          Top = 122
          Width = 57
          Height = 25
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Color = clBtnFace
          ReadOnly = True
          TabOrder = 3
          Text = '0'
        end
        object ControlVoltageCheckBox: TCheckBox
          Left = 16
          Top = 299
          Width = 239
          Height = 23
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Caption = 'Control power (U) '
          Checked = True
          State = cbChecked
          TabOrder = 4
          OnClick = ControlVoltageCheckBoxClick
        end
        object GroupBox10: TGroupBox
          Left = 2
          Top = 483
          Width = 259
          Height = 107
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Align = alBottom
          Caption = ' Target position '
          TabOrder = 5
          DesignSize = (
            259
            107)
          object MomentTrackBar: TTrackBar
            Left = 4
            Top = 24
            Width = 154
            Height = 35
            Margins.Left = 4
            Margins.Top = 4
            Margins.Right = 4
            Margins.Bottom = 4
            Anchors = [akLeft, akTop, akRight]
            Max = 10000
            Min = -10000
            TabOrder = 0
            OnChange = MomentTrackBarChange
          end
          object MomentProgressBar: TProgressBar
            Left = 17
            Top = 69
            Width = 130
            Height = 23
            Margins.Left = 4
            Margins.Top = 4
            Margins.Right = 4
            Margins.Bottom = 4
            Anchors = [akLeft, akTop, akRight]
            Max = 1000
            TabOrder = 1
          end
          object ExtMomentEdit: TEdit
            Left = 155
            Top = 67
            Width = 95
            Height = 25
            Margins.Left = 4
            Margins.Top = 4
            Margins.Right = 4
            Margins.Bottom = 4
            Anchors = [akTop, akRight]
            Color = clBtnFace
            ReadOnly = True
            TabOrder = 2
            Text = '0'
          end
          object ResetToZeroButton2: TButton
            Left = 153
            Top = 22
            Width = 99
            Height = 37
            Margins.Left = 4
            Margins.Top = 4
            Margins.Right = 4
            Margins.Bottom = 4
            Caption = 'Reset to 0'
            TabOrder = 3
            OnClick = ResetToZeroButton2Click
          end
        end
        object GroupBox11: TGroupBox
          Left = 2
          Top = 376
          Width = 259
          Height = 107
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Align = alBottom
          Caption = ' External power  '
          TabOrder = 6
          DesignSize = (
            259
            107)
          object MovementControlTrackBar: TTrackBar
            Left = 7
            Top = 24
            Width = 153
            Height = 35
            Margins.Left = 4
            Margins.Top = 4
            Margins.Right = 4
            Margins.Bottom = 4
            Anchors = [akLeft, akTop, akRight]
            Max = 1000
            Min = -1000
            TabOrder = 0
            OnChange = MovementControlTrackBarChange
          end
          object MovementControlProgressBar: TProgressBar
            Left = 17
            Top = 69
            Width = 130
            Height = 23
            Margins.Left = 4
            Margins.Top = 4
            Margins.Right = 4
            Margins.Bottom = 4
            Anchors = [akLeft, akTop, akRight]
            Max = 1000
            TabOrder = 1
          end
          object MovementControlEdit: TEdit
            Left = 155
            Top = 67
            Width = 95
            Height = 25
            Margins.Left = 4
            Margins.Top = 4
            Margins.Right = 4
            Margins.Bottom = 4
            Anchors = [akTop, akRight]
            Color = clBtnFace
            ReadOnly = True
            TabOrder = 2
            Text = '0'
          end
          object ResetToZeroButton1: TButton
            Left = 153
            Top = 22
            Width = 99
            Height = 37
            Margins.Left = 4
            Margins.Top = 4
            Margins.Right = 4
            Margins.Bottom = 4
            Caption = 'Reset to 0'
            TabOrder = 3
            OnClick = ResetToZeroButton1Click
          end
        end
        object HideSecondaryGuiCheckBox: TCheckBox
          Left = 16
          Top = 330
          Width = 247
          Height = 22
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Caption = 'Hide secondary GUI'
          TabOrder = 7
          OnClick = HideSecondaryGuiCheckBoxClick
        end
        object CheckListBox1: TCheckListBox
          Left = 16
          Top = 165
          Width = 239
          Height = 127
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          ItemHeight = 17
          TabOrder = 8
          OnClick = CheckListBox1Click
        end
      end
      object Panel1: TPanel
        Left = 263
        Top = 0
        Width = 635
        Height = 592
        Margins.Left = 4
        Margins.Top = 4
        Margins.Right = 4
        Margins.Bottom = 4
        Align = alClient
        TabOrder = 1
        object Splitter1: TSplitter
          Left = 1
          Top = 279
          Width = 633
          Height = 16
          Cursor = crVSplit
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Align = alBottom
          ExplicitTop = 269
          ExplicitWidth = 631
        end
        object GroupBox7: TGroupBox
          Left = 1
          Top = 1
          Width = 633
          Height = 278
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Align = alClient
          Caption = ' Visual output '
          DoubleBuffered = False
          ParentDoubleBuffered = False
          TabOrder = 0
          object Splitter2: TSplitter
            Left = 285
            Top = 19
            Width = 11
            Height = 257
            Margins.Left = 4
            Margins.Top = 4
            Margins.Right = 4
            Margins.Bottom = 4
            ExplicitLeft = 286
            ExplicitTop = 20
            ExplicitHeight = 245
          end
          object Panel2: TPanel
            Left = 2
            Top = 19
            Width = 283
            Height = 257
            Margins.Left = 4
            Margins.Top = 4
            Margins.Right = 4
            Margins.Bottom = 4
            Align = alLeft
            TabOrder = 0
            object Label13: TLabel
              Left = 16
              Top = 12
              Width = 166
              Height = 17
              Margins.Left = 4
              Margins.Top = 4
              Margins.Right = 4
              Margins.Bottom = 4
              Caption = 'Charge PAC time constant:'
            end
            object Label8: TLabel
              Left = 21
              Top = 71
              Width = 182
              Height = 17
              Margins.Left = 4
              Margins.Top = 4
              Margins.Right = 4
              Margins.Bottom = 4
              Caption = 'Discharge PAC time constant:'
            end
            object Label10: TLabel
              Left = 18
              Top = 135
              Width = 87
              Height = 17
              Margins.Left = 4
              Margins.Top = 4
              Margins.Right = 4
              Margins.Bottom = 4
              Caption = 'PAC multiplier:'
            end
            object PACActivatorTimeTrackBar: TTrackBar
              Left = 7
              Top = 30
              Width = 184
              Height = 35
              Margins.Left = 4
              Margins.Top = 4
              Margins.Right = 4
              Margins.Bottom = 4
              Max = 10000
              Min = 10
              Position = 10
              TabOrder = 0
              OnChange = PACActivatorTimeTrackBarChange
            end
            object PACActivatorTimeEdit: TEdit
              Left = 188
              Top = 33
              Width = 63
              Height = 25
              Margins.Left = 4
              Margins.Top = 4
              Margins.Right = 4
              Margins.Bottom = 4
              TabOrder = 1
              Text = '1'
            end
            object PACDeactivatorTimeEdit: TEdit
              Left = 191
              Top = 93
              Width = 63
              Height = 25
              Margins.Left = 4
              Margins.Top = 4
              Margins.Right = 4
              Margins.Bottom = 4
              TabOrder = 2
              Text = '1'
            end
            object PACDeactivatorTimeTrackBar: TTrackBar
              Left = 9
              Top = 90
              Width = 185
              Height = 36
              Margins.Left = 4
              Margins.Top = 4
              Margins.Right = 4
              Margins.Bottom = 4
              Max = 10000
              Min = 10
              Position = 100
              TabOrder = 3
              OnChange = PACDeactivatorTimeTrackBarChange
            end
            object PACMultiplicatorTrackBar: TTrackBar
              Left = 9
              Top = 152
              Width = 185
              Height = 35
              Margins.Left = 4
              Margins.Top = 4
              Margins.Right = 4
              Margins.Bottom = 4
              Max = 1000
              Position = 10
              TabOrder = 4
              OnChange = PACMultiplicatorTrackBarChange
            end
            object PACMultiplicatorEdit: TEdit
              Left = 191
              Top = 156
              Width = 63
              Height = 25
              Margins.Left = 4
              Margins.Top = 4
              Margins.Right = 4
              Margins.Bottom = 4
              TabOrder = 5
              Text = '1'
            end
          end
          object Panel3: TPanel
            Left = 296
            Top = 19
            Width = 335
            Height = 257
            Margins.Left = 4
            Margins.Top = 4
            Margins.Right = 4
            Margins.Bottom = 4
            Align = alClient
            TabOrder = 1
            object DrawGrid: TDrawGrid
              Left = 1
              Top = 1
              Width = 333
              Height = 255
              Margins.Left = 4
              Margins.Top = 4
              Margins.Right = 4
              Margins.Bottom = 4
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
          Top = 295
          Width = 633
          Height = 296
          Margins.Left = 4
          Margins.Top = 4
          Margins.Right = 4
          Margins.Bottom = 4
          Align = alBottom
          Caption = ' Neuro manipulator parameters '
          TabOrder = 1
          object Label12: TLabel
            Left = 18
            Top = 139
            Width = 20
            Height = 17
            Margins.Left = 4
            Margins.Top = 4
            Margins.Right = 4
            Margins.Bottom = 4
            Caption = 'Va:'
          end
          object Label11: TLabel
            Left = 120
            Top = 139
            Width = 21
            Height = 17
            Margins.Left = 4
            Margins.Top = 4
            Margins.Right = 4
            Margins.Bottom = 4
            Caption = 'Vd:'
          end
          object Label7: TLabel
            Left = 18
            Top = 75
            Width = 223
            Height = 17
            Margins.Left = 4
            Margins.Top = 4
            Margins.Right = 4
            Margins.Bottom = 4
            Caption = 'Controller power time duration (ms):'
          end
          object Label9: TLabel
            Left = 16
            Top = 21
            Width = 107
            Height = 17
            Margins.Left = 4
            Margins.Top = 4
            Margins.Right = 4
            Margins.Bottom = 4
            Caption = 'Voltage multiplier:'
          end
          object VaEdit: TEdit
            Left = 43
            Top = 135
            Width = 63
            Height = 25
            Margins.Left = 4
            Margins.Top = 4
            Margins.Right = 4
            Margins.Bottom = 4
            TabOrder = 0
            Text = '100'
          end
          object VdEdit: TEdit
            Left = 145
            Top = 135
            Width = 63
            Height = 25
            Margins.Left = 4
            Margins.Top = 4
            Margins.Right = 4
            Margins.Bottom = 4
            TabOrder = 1
            Text = '5'
          end
          object SendVButton: TButton
            Left = 216
            Top = 132
            Width = 119
            Height = 33
            Margins.Left = 4
            Margins.Top = 4
            Margins.Right = 4
            Margins.Bottom = 4
            Caption = #1054#1090#1087#1088#1072#1074#1080#1090#1100
            TabOrder = 2
            OnClick = SendVButtonClick
          end
          object VoltageMulTrackBar: TTrackBar
            Left = 7
            Top = 39
            Width = 184
            Height = 36
            Margins.Left = 4
            Margins.Top = 4
            Margins.Right = 4
            Margins.Bottom = 4
            Max = 5000
            Position = 200
            TabOrder = 3
            OnChange = VoltageMulTrackBarChange
          end
          object TimeDurationTrackBar: TTrackBar
            Left = 7
            Top = 94
            Width = 184
            Height = 35
            Margins.Left = 4
            Margins.Top = 4
            Margins.Right = 4
            Margins.Bottom = 4
            Max = 256
            Min = 1
            Position = 1
            TabOrder = 4
            OnChange = TimeDurationTrackBarChange
          end
          object VoltageMulEdit: TEdit
            Left = 188
            Top = 42
            Width = 63
            Height = 25
            Margins.Left = 4
            Margins.Top = 4
            Margins.Right = 4
            Margins.Bottom = 4
            TabOrder = 5
            Text = '1'
          end
          object TimeDurationEdit: TEdit
            Left = 188
            Top = 97
            Width = 63
            Height = 25
            Margins.Left = 4
            Margins.Top = 4
            Margins.Right = 4
            Margins.Bottom = 4
            TabOrder = 6
            Text = '1'
          end
          object MulToNumberOfControlElementsCheckBox: TCheckBox
            Left = 259
            Top = 44
            Width = 65
            Height = 23
            Margins.Left = 4
            Margins.Top = 4
            Margins.Right = 4
            Margins.Bottom = 4
            Caption = #1087#1086' N'
            TabOrder = 7
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
