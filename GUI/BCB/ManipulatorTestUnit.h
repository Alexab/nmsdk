//---------------------------------------------------------------------------

#ifndef ManipulatorTestUnitH
#define ManipulatorTestUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#include "../Deploy/Include/NMSDK.h"
#include "rdk.h"
#include "TUBitmap.h"
#include <ComCtrls.hpp>
#include "Chart.hpp"
#include "Series.hpp"
#include "TeEngine.hpp"
#include "TeeProcs.hpp"
#include <VclTee.TeeGDIPlus.hpp>

using namespace NMSDK;
//---------------------------------------------------------------------------
class TManipulatorTestForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TImage *Image;
	TPanel *Panel2;
	TGroupBox *GroupBox1;
	TLabel *Label2;
	TTrackBar *IIAfferentTrackBar;
	TEdit *IIAfferentEdit;
	TLabel *Label3;
	TTrackBar *IINumAfferentTrackBar;
	TEdit *IINumAfferentEdit;
	TCheckBox *IaCheckBox;
	TCheckBox *IbCheckBox;
	TCheckBox *IICheckBox;
	TCheckBox *ControlVoltageCheckBox;
	TPanel *Panel3;
	TChart *IOChart;
	TBarSeries *Series3;
	TBarSeries *Series1;
	TBarSeries *Series2;
	TBarSeries *Series4;
	TBarSeries *Series5;
	TBarSeries *Series6;
	TPanel *Panel4;
	TTrackBar *MomentTrackBar;
	TProgressBar *MomentProgressBar;
	TEdit *ExtMomentEdit;
	TRadioGroup *RadioGroup1;
	TLabeledEdit *EngineOutputsLabeledEdit;
	TTrackBar *VoltageMulTrackBar;
	TLabeledEdit *VoltageLabeledEdit;
	TEdit *VoltageMulEdit;
	TLabel *Label4;
	TLabel *Label1;
	TLabeledEdit *TimeLabeledEdit;
	TLabel *Label7;
	TTrackBar *TimeDurationTrackBar;
	TEdit *TimeDurationEdit;
	TTrackBar *PACDeactivatorTimeTrackBar;
	TLabel *Label8;
	TEdit *PACDeactivatorTimeEdit;
	TTrackBar *PACActivatorTimeTrackBar;
	TLabel *Label9;
	TEdit *PACActivatorTimeEdit;
	TGroupBox *GroupBox2;
	TButton *OnDeviceButton;
	TButton *OffDeviceButton;
	TCheckBox *EmulatorCheckBox;
	TLabel *Label5;
	TEdit *ComPortEdit;
	TLabel *Label6;
	TEdit *ServoNumberEdit;
	TCheckBox *SwapOutputVoltageDirectionCheckBox;
	TLabeledEdit *ControlDurationLabeledEdit;
	TLabel *Label10;
	TEdit *VdEdit;
	TEdit *VaEdit;
	TLabel *Label11;
	TButton *SendVButton;
	TCheckBox *MulToNumberOfControlElementsCheckBox;
	TComboBox *WorkModeComboBox;
	TLabel *Label12;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall MomentTrackBarChange(TObject *Sender);
	void __fastcall IaCheckBoxClick(TObject *Sender);
	void __fastcall IbCheckBoxClick(TObject *Sender);
	void __fastcall IICheckBoxClick(TObject *Sender);
	void __fastcall IIAfferentTrackBarChange(TObject *Sender);
	void __fastcall IIAfferentEditChange(TObject *Sender);
	void __fastcall IINumAfferentTrackBarChange(TObject *Sender);
	void __fastcall IINumAfferentEditChange(TObject *Sender);
	void __fastcall ControlVoltageCheckBoxClick(TObject *Sender);
	void __fastcall RadioGroup1Click(TObject *Sender);
	void __fastcall VoltageMulTrackBarChange(TObject *Sender);
	void __fastcall EmulatorCheckBoxClick(TObject *Sender);
	void __fastcall SwapOutputVoltageDirectionCheckBoxClick(TObject *Sender);
	void __fastcall ServoNumberEditChange(TObject *Sender);
	void __fastcall TimeDurationTrackBarChange(TObject *Sender);
	void __fastcall PACDeactivatorTimeTrackBarChange(TObject *Sender);
	void __fastcall PACActivatorTimeTrackBarChange(TObject *Sender);
	void __fastcall OnDeviceButtonClick(TObject *Sender);
	void __fastcall OffDeviceButtonClick(TObject *Sender);
	void __fastcall SendVButtonClick(TObject *Sender);
	void __fastcall WorkModeComboBoxSelect(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TManipulatorTestForm(TComponent* Owner);

 NManipulatorSource *Engine;
 NConstGenerator *Source;
 NANet *ControlSystem;

 NPulseGenerator *IIPosAfferent,*IINegAfferent;
 NPulseGenerator *MN1PosControl,*MN1NegControl;

 UGraphics graph;
 UBitmap canvas;
 double length;

 void UpdateInterface(void);

 // Update IO information
 void UpdateIOInformation(void);

 void WriteArrow(UAGraphics &graph, int x,int y,int width,int direction);
};
//---------------------------------------------------------------------------
extern PACKAGE TManipulatorTestForm *ManipulatorTestForm;
//---------------------------------------------------------------------------
#endif
