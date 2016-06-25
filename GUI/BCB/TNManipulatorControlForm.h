//---------------------------------------------------------------------------

#ifndef TNManipulatorControlFormH
#define TNManipulatorControlFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include "TUVisualControllerFormUnit.h"
#include <Vcl.Grids.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <Web.HTTPApp.hpp>
#include <Web.HTTPProd.hpp>
#include <System.ImageList.hpp>
#include <string>

#include "nmsdk_cpp_initdll.h"
//#include "nmsdk.bcb.h"

//---------------------------------------------------------------------------
class TNManipulatorControlForm : public TUVisualControllerForm
{
__published:	// IDE-managed Components
	TStatusBar *StatusBar1;
	TImageList *ImageList;
	TMainMenu *MainMenu;
	TMenuItem *Communication1;
	TMenuItem *Connect1;
	TMenuItem *Disconnect1;
	TMenuItem *Move1;
	TMenuItem *MoveLeft1;
	TMenuItem *MoveRight1;
	TMenuItem *SelectManipulator1;
	TMenuItem *N1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TTabSheet *TabSheet3;
	TGroupBox *GroupBox1;
	TComboBox *ComPortComboBox;
	TLabel *Label1;
	TRadioButton *DeviceModeRadioButton;
	TRadioButton *EmulatorModeRadioButton;
	TLabel *Label2;
	TComboBox *ControlModeComboBox;
	TGroupBox *GroupBox2;
	TPanel *ComponentSelectionPanel;
	TGroupBox *GroupBox3;
	TButton *ConnectButton;
	TButton *DisconnectButton;
	TButton *ResetButton;
	TMenuItem *Reset1;
	TButton *StartButton;
	TButton *StopButton;
	TMenuItem *Start1;
	TMenuItem *Stop1;
	TGroupBox *GroupBox4;
	TLabel *Время;
	TLabel *Скорость;
	TLabel *Label3;
	TLabel *Label4;
	TButton *Button2;
	TTrackBar *TrackBarTime;
	TTrackBar *TrackBarPWM;
	TComboBox *ComboBoxDir;
	TComboBox *CBoxServoMove;
	TMenuItem *SelectControlSystem1;
	TGroupBox *GroupBox6;
	TPanel *ControlSystemSelectionPanel;
	TGroupBox *GroupBox5;
	TLabel *Label5;
	TLabel *Label6;
	TTrackBar *IIAfferentTrackBar;
	TEdit *IIAfferentEdit;
	TTrackBar *IINumAfferentTrackBar;
	TEdit *IINumAfferentEdit;
	TCheckBox *IaCheckBox;
	TCheckBox *IbCheckBox;
	TCheckBox *IICheckBox;
	TCheckBox *ControlVoltageCheckBox;
	TPanel *Panel1;
	TGroupBox *GroupBox7;
	TGroupBox *GroupBox8;
	TLabel *Label12;
	TEdit *VaEdit;
	TEdit *VdEdit;
	TLabel *Label11;
	TButton *SendVButton;
	TTrackBar *VoltageMulTrackBar;
	TTrackBar *TimeDurationTrackBar;
	TLabel *Label7;
	TLabel *Label9;
	TEdit *VoltageMulEdit;
	TEdit *TimeDurationEdit;
	TCheckBox *MulToNumberOfControlElementsCheckBox;
	TGroupBox *GroupBox10;
	TTrackBar *MomentTrackBar;
	TProgressBar *MomentProgressBar;
	TEdit *ExtMomentEdit;
	TSplitter *Splitter1;
	TCheckBox *CheckBox1;
	TGroupBox *GroupBox11;
	TTrackBar *MovementControlTrackBar;
	TProgressBar *MovementControlProgressBar;
	TEdit *MovementControlEdit;
	TSplitter *Splitter2;
	TCheckBox *HideSecondaryGuiCheckBox;
	TPanel *Panel2;
	TLabel *Label13;
	TTrackBar *PACActivatorTimeTrackBar;
	TEdit *PACActivatorTimeEdit;
	TEdit *PACDeactivatorTimeEdit;
	TTrackBar *PACDeactivatorTimeTrackBar;
	TLabel *Label8;
	TLabel *Label10;
	TTrackBar *PACMultiplicatorTrackBar;
	TEdit *PACMultiplicatorEdit;
	TPanel *Panel3;
	TDrawGrid *DrawGrid;
	TButton *ResetToZeroButton1;
	TButton *ResetToZeroButton2;
	TButton *SaveStatsButton;
	TButton *NewStatsButton;
	void __fastcall Disconnect1Click(TObject *Sender);
	void __fastcall MoveLeft1Click(TObject *Sender);
	void __fastcall MoveRight1Click(TObject *Sender);
	void __fastcall SelectManipulator1Click(TObject *Sender);
	void __fastcall Connect1Click(TObject *Sender);
	void __fastcall DeviceModeRadioButtonClick(TObject *Sender);
	void __fastcall EmulatorModeRadioButtonClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ComponentSelectionPanelDblClick(TObject *Sender);
	void __fastcall ConnectButtonClick(TObject *Sender);
	void __fastcall DisconnectButtonClick(TObject *Sender);
	void __fastcall Reset1Click(TObject *Sender);
	void __fastcall ResetButtonClick(TObject *Sender);
	void __fastcall StartButtonClick(TObject *Sender);
	void __fastcall StopButtonClick(TObject *Sender);
	void __fastcall Start1Click(TObject *Sender);
	void __fastcall Stop1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall SelectControlSystem1Click(TObject *Sender);
	void __fastcall ControlSystemSelectionPanelDblClick(TObject *Sender);
	void __fastcall IaCheckBoxClick(TObject *Sender);
	void __fastcall IIAfferentTrackBarChange(TObject *Sender);
	void __fastcall IINumAfferentTrackBarChange(TObject *Sender);
	void __fastcall IbCheckBoxClick(TObject *Sender);
	void __fastcall IICheckBoxClick(TObject *Sender);
	void __fastcall ControlVoltageCheckBoxClick(TObject *Sender);
	void __fastcall VoltageMulTrackBarChange(TObject *Sender);
	void __fastcall TimeDurationTrackBarChange(TObject *Sender);
	void __fastcall PACDeactivatorTimeTrackBarChange(TObject *Sender);
	void __fastcall PACActivatorTimeTrackBarChange(TObject *Sender);
	void __fastcall SendVButtonClick(TObject *Sender);
	void __fastcall PACMultiplicatorTrackBarChange(TObject *Sender);
	void __fastcall MomentTrackBarChange(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall MovementControlTrackBarChange(TObject *Sender);
	void __fastcall HideSecondaryGuiCheckBoxClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall DrawGridDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
	void __fastcall ResetToZeroButton1Click(TObject *Sender);
	void __fastcall ResetToZeroButton2Click(TObject *Sender);
	void __fastcall SaveStatsButtonClick(TObject *Sender);
	void __fastcall NewStatsButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TNManipulatorControlForm(TComponent* Owner);

std::string ManipulatorName;

std::string ControlSystemName;

RDK::UEPtr<NMSDK::NWPhysicalManipulator> Manipulator;
RDK::UEPtr<NMSDK::UNet> UniversalManipulator;

RDK::UEPtr<NMSDK::NManipulatorSource> Engine;
RDK::UEPtr<NMSDK::NConstGenerator> Source;
RDK::UEPtr<NMSDK::NEngineMotionControl> ControlSystem;

RDK::UEPtr<NMSDK::NPulseGenerator> IIPosAfferent,IINegAfferent;
RDK::UEPtr<NMSDK::NPulseGenerator> MN1PosControl,MN1NegControl;

// Отображаемое изображение
RDK::UBitmap BmpCanvas;
RDK::UGraphics BmpGraphics;

// Разрешение изображения
int CanvasWidth,CanvasHeight;

// Координаты узла звена
double X,Y;

// Угол поворота звена
double Angle;

// Смещение по перемещению при отображении
double Movement;

// Длина звена (пикс)
double Length;

// Константное смещение на постоянный угол при отображении
double ZeroAngle;

// Константное смещение по перемещению при отображении
double ZeroMovement;

// Имя компонента с которого считываем данные
std::string ReadComponentName;

TBitmap *TempBmp;


// Сохраняет параметры интерфейса в xml
virtual void ASaveParameters(RDK::USerStorageXML &xml);

// Загружает параметры интерфейса из xml
virtual void ALoadParameters(RDK::USerStorageXML &xml);

void AUpdateInterface(void);

// Возврат интерфейса в исходное состояние
void AClearInterface(void);

// Считывает данные всех пармаетров из сети и выставляет в соответствующие позиции элементы управления
void LoadInterfaceInfoFromNet(void);

bool ManipulatorCSConnect(const std::string &cs_name, const std::string &man_name);

// Считывает данные из компонента
void ReadComponentData(void);

void ReconnectManipulator(void);
void ReconnectCurrentManipulator(void);



// Создание копии этого компонента
virtual TUVisualControllerForm* New(TComponent *owner=0);

};
//---------------------------------------------------------------------------
extern PACKAGE TNManipulatorControlForm *NManipulatorControlForm;
//---------------------------------------------------------------------------
#endif
