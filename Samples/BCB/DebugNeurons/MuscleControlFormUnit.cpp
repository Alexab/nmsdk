//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MuscleControlFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMuscleControlForm *MuscleControlForm;
//---------------------------------------------------------------------------
__fastcall TMuscleControlForm::TMuscleControlForm(TComponent* Owner)
	: TForm(Owner)
{
 AfferentSource1=AfferentSource2=0;
 Muscle1=Muscle2=0;
 Net=0;

 Generator=0;
 Length1=Length2=0;

 Renshow1Activator=Renshow2Activator=Renshow1Deactivator=Renshow2Deactivator=0;
}
//---------------------------------------------------------------------------
void __fastcall TMuscleControlForm::Afferent1TrackBarChange(TObject *Sender)
{
 AfferentEdit1->Text=FloatToStr(double(Afferent1TrackBar->Position)/100.0);
}
//---------------------------------------------------------------------------
void __fastcall TMuscleControlForm::Afferent2TrackBarChange(TObject *Sender)
{
 AfferentEdit2->Text=FloatToStr(double(Afferent2TrackBar->Position)/100.0);
}
//---------------------------------------------------------------------------
void __fastcall TMuscleControlForm::AfferentEdit1Change(TObject *Sender)
{
 AfferentSource1->Amplitude=StrToFloat(AfferentEdit1->Text);
}
//---------------------------------------------------------------------------
void __fastcall TMuscleControlForm::AfferentEdit2Change(TObject *Sender)
{
 AfferentSource2->Amplitude=StrToFloat(AfferentEdit2->Text);
}
//---------------------------------------------------------------------------
void __fastcall TMuscleControlForm::FBRenshowCheckBox1Click(TObject *Sender)
{
 if(FBRenshowCheckBox1->Checked)
  Net->CreateLink("Renshow1.LTZone",0,
				 "Motoneuron1.PNeuronMembrane.NegChannel.Synapse2",0);
 else
  Net->BreakLink("Renshow1.LTZone",0,
				 "Motoneuron1.PNeuronMembrane.NegChannel.Synapse2",0);
}
//---------------------------------------------------------------------------
void __fastcall TMuscleControlForm::FBRenshowCheckBox2Click(TObject *Sender)
{
 if(FBRenshowCheckBox2->Checked)
  Net->CreateLink("Renshow2.LTZone",0,
				 "Motoneuron2.PNeuronMembrane.NegChannel.Synapse2",0);
 else
  Net->BreakLink("Renshow2.LTZone",0,
				 "Motoneuron2.PNeuronMembrane.NegChannel.Synapse2",0);
}
//---------------------------------------------------------------------------
void __fastcall TMuscleControlForm::MuscleMassTrackBar1Change(TObject *Sender)
{
 MuscleMassEdit1->Text=IntToStr(MuscleMassTrackBar1->Position);
}
//---------------------------------------------------------------------------

void __fastcall TMuscleControlForm::MuscleMassTrackBar2Change(TObject *Sender)
{
 MuscleMassEdit2->Text=IntToStr(MuscleMassTrackBar2->Position);
}
//---------------------------------------------------------------------------

void __fastcall TMuscleControlForm::MuscleMassEdit1Change(TObject *Sender)
{
 Muscle1->Mass=StrToFloat(MuscleMassEdit1->Text);
}
//---------------------------------------------------------------------------

void __fastcall TMuscleControlForm::MuscleMassEdit2Change(TObject *Sender)
{
 Muscle2->Mass=StrToFloat(MuscleMassEdit2->Text);
}
//---------------------------------------------------------------------------

void __fastcall TMuscleControlForm::AfferentEdit3Change(TObject *Sender)
{
 Generator->Frequency=StrToFloat(AfferentEdit3->Text);
}
//---------------------------------------------------------------------------

void __fastcall TMuscleControlForm::Afferent3TrackBarChange(TObject *Sender)
{
 AfferentEdit3->Text=IntToStr(Afferent3TrackBar->Position);
}
//---------------------------------------------------------------------------

void __fastcall TMuscleControlForm::Renshow1ActivatorTrackBarChange(TObject *Sender)

{
 Renshow1ActivatorEdit->Text=IntToStr(Renshow1ActivatorTrackBar->Position);
}
//---------------------------------------------------------------------------

void __fastcall TMuscleControlForm::Renshow2ActivatorTrackBarChange(TObject *Sender)

{
 Renshow2ActivatorEdit->Text=IntToStr(Renshow2ActivatorTrackBar->Position);
}
//---------------------------------------------------------------------------

void __fastcall TMuscleControlForm::Renshow1DeactivatorTrackBarChange(TObject *Sender)

{
 Renshow1DeactivatorEdit->Text=IntToStr(Renshow1DeactivatorTrackBar->Position);
}
//---------------------------------------------------------------------------

void __fastcall TMuscleControlForm::Renshow2DeactivatorTrackBarChange(TObject *Sender)

{
 Renshow2DeactivatorEdit->Text=IntToStr(Renshow2DeactivatorTrackBar->Position);
}
//---------------------------------------------------------------------------

void __fastcall TMuscleControlForm::Renshow1ActivatorEditChange(TObject *Sender)
{
 Renshow1Activator->Frequency=StrToFloat(Renshow1ActivatorEdit->Text);
}
//---------------------------------------------------------------------------

void __fastcall TMuscleControlForm::Renshow1DeactivatorEditChange(TObject *Sender)

{
 Renshow1Deactivator->Frequency=StrToFloat(Renshow1DeactivatorEdit->Text);
}
//---------------------------------------------------------------------------

void __fastcall TMuscleControlForm::Renshow2ActivatorEditChange(TObject *Sender)
{
 Renshow2Activator->Frequency=StrToFloat(Renshow2ActivatorEdit->Text);
}
//---------------------------------------------------------------------------

void __fastcall TMuscleControlForm::Renshow2DeactivatorEditChange(TObject *Sender)

{
 Renshow2Deactivator->Frequency=StrToFloat(Renshow2DeactivatorEdit->Text);
}
//---------------------------------------------------------------------------

void __fastcall TMuscleControlForm::FormHide(TObject *Sender)
{
 //
}
//---------------------------------------------------------------------------

void __fastcall TMuscleControlForm::LengthEdit1Change(TObject *Sender)
{
 //
 Length1->Amplitude=StrToFloat(LengthEdit1->Text);
}
//---------------------------------------------------------------------------

void __fastcall TMuscleControlForm::LengthTrackBar1Change(TObject *Sender)
{
 LengthEdit1->Text=FloatToStr(double(LengthTrackBar1->Position)/100.0);
}
//---------------------------------------------------------------------------

