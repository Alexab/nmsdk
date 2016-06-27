//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TNManipulatorControlForm.h"
#include "UComponentsListFormUnit.h"
#include "TUBitmap.h"
//#include "UDrawEngineFormUnit.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TNManipulatorControlForm *NManipulatorControlForm;
//---------------------------------------------------------------------------
__fastcall TNManipulatorControlForm::TNManipulatorControlForm(TComponent* Owner)
	: TUVisualControllerForm(Owner)
{
 BmpGraphics.SetCanvas(&BmpCanvas);
 CanvasWidth=640;
 CanvasHeight=480;
 Length=100;
 X=CanvasWidth/2;
 Y=CanvasHeight/2;
 BmpGraphics.SetPenWidth(4);

 // Константное смещение на постоянный угол при отображении
 ZeroAngle=0;

 ZeroMovement=0;

 Movement=0;
 TempBmp=0;
 Angle=0;
}

void TNManipulatorControlForm::AUpdateInterface(void)
{
 UpdateInterval=100;
 LoadInterfaceInfoFromNet();
 if(ManipulatorName.empty())
 {
  ComponentSelectionPanel->Color=clRed;
  ComponentSelectionPanel->Caption="Double click to select manipulator component";
  GroupBox1->Enabled=false;
  GroupBox3->Enabled=false;
  Caption="Manipulator [Not set]";
 }
 else
 {
  ComponentSelectionPanel->Color=clGreen;
  ComponentSelectionPanel->Caption=ManipulatorName.c_str();
  GroupBox1->Enabled=true;
  GroupBox3->Enabled=true;
  Caption=String("Manipulator [")+ManipulatorName.c_str()+String("]");
 }

 if(ControlSystemName.empty())
 {
  ControlSystemSelectionPanel->Color=clRed;
  ControlSystemSelectionPanel->Caption="Double click to select manipulator component";
  Caption="Manipulator control [Not set]";
 }
 else
 {
  ControlSystemSelectionPanel->Color=clGreen;
  ControlSystemSelectionPanel->Caption=ControlSystemName.c_str();
  Caption=String("Control system [")+ControlSystemName.c_str()+String("]");

  if(Model_CheckLink((ControlSystemName+".Ia_PosIntervalSeparator1").c_str(),0,(ControlSystemName+".MotionElement0.Afferent_Ia2.Receptor").c_str(),0))
   IaCheckBox->Checked=true;
  else
   IaCheckBox->Checked=false;

  if(Model_CheckLink((ControlSystemName+".Ib_PosIntervalSeparator1").c_str(),0,(ControlSystemName+".MotionElement0.Afferent_Ib1.Receptor").c_str(),0))
   IbCheckBox->Checked=true;
  else
   IbCheckBox->Checked=false;

  if(Model_CheckLink((ControlSystemName+".II_PosIntervalSeparator1").c_str(),0,(ControlSystemName+".MotionElement0.Afferent_II1.Receptor").c_str(),0))
   IICheckBox->Checked=true;
  else
   IICheckBox->Checked=false;

  if(Model_CheckLink((ControlSystemName+".Ic_PosIntervalSeparator1").c_str(),0,(ControlSystemName+".MotionElement0.Afferent_Ic1.Receptor").c_str(),0))
   CheckBox1->Checked=true;
  else
   CheckBox1->Checked=false;
  if(Model_CheckLink((ControlSystemName+".Pac").c_str(),0,(ControlSystemName+".NManipulatorInput1").c_str(),0))
   ControlVoltageCheckBox->Checked=true;
  else
   ControlVoltageCheckBox->Checked=false;
 }


 if(Manipulator)
 {
  if(Manipulator->DMReset) // процедура подключения пройдена
  {
   ConnectButton->Enabled=false;
   DisconnectButton->Enabled=true;
   StartButton->Enabled=true;
   StopButton->Enabled=true;
   ResetButton->Enabled=true;
   GroupBox1->Enabled=false;
   TabSheet2->Enabled=true;
  }
  else
  {
   ConnectButton->Enabled=true;
   DisconnectButton->Enabled=false;
   StartButton->Enabled=false;
   StopButton->Enabled=false;
   ResetButton->Enabled=false;
   GroupBox1->Enabled=true;
   TabSheet2->Enabled=false;
  }
 }

 if(ControlSystem)
 {
  int num_motions=ControlSystem->NumMotionElements;
  IINumAfferentTrackBar->Max=num_motions;
  IINumAfferentTrackBar->Enabled=true;
  IIAfferentTrackBar->Enabled=true;
 }
 else
 {
  IINumAfferentTrackBar->Enabled=false;
  IIAfferentTrackBar->Enabled=false;
 }

 ReadComponentData();
 BmpCanvas.SetRes(CanvasWidth,CanvasHeight,RDK::ubmRGB24);
 BmpCanvas.Fill(RDK::UColorT(255,255,255));
 BmpGraphics.SetPenColor(0x00FF0000);
 BmpGraphics.Line(0,Y,CanvasWidth,Y);
 BmpGraphics.Line(X,0,X,CanvasHeight);
 for(int i=0;i<20;i++)
 {
  BmpGraphics.Line(X+i*10,Y-10,X+i*10,Y);
  BmpGraphics.Line(X-i*10,Y-10,X-i*10,Y);
 }
 BmpGraphics.SetPenColor(0x000000FF);
 BmpGraphics.Line(Movement+ZeroMovement+X,Y,Movement+ZeroMovement+X+Length*cos(ZeroAngle+Angle),Y+Length*sin(ZeroAngle+Angle));
 BmpGraphics.Circle(Movement+ZeroMovement+X,Y,10,true);
 BmpCanvas>>TempBmp;
 if(ControlSystem)
 {
  String text;
  text=IntToStr(int(ControlSystem->NumMotionElements));
  text=text+" motion elements";
  TempBmp->Canvas->Font->Size=30;
  TempBmp->Canvas->TextOutA(0,0,text);
  DrawGrid->DefaultColWidth=DrawGrid->ClientWidth;
  DrawGrid->DefaultRowHeight=DrawGrid->ClientHeight;
  DrawGrid->Repaint();
 }

 double value=double(PACMultiplicatorTrackBar->Position);
 PACMultiplicatorEdit->Text=FloatToStrF(value,ffFixed,3,3);

 value=double(PACDeactivatorTimeTrackBar->Position)/double(PACDeactivatorTimeTrackBar->Max);
 PACDeactivatorTimeEdit->Text=FloatToStrF(value,ffFixed,3,3);

 value=double(PACActivatorTimeTrackBar->Position)/double(PACActivatorTimeTrackBar->Max);
 PACActivatorTimeEdit->Text=FloatToStrF(value,ffFixed,3,3);

 if(ControlSystem)
 {
  IIPosAfferent=RDK::dynamic_pointer_cast<NMSDK::NPulseGenerator>(ControlSystem->GetComponentL("IIPosAfferentGenerator"));
  IINegAfferent=RDK::dynamic_pointer_cast<NMSDK::NPulseGenerator>(ControlSystem->GetComponentL("IINegAfferentGenerator"));

  if(IIPosAfferent && IINegAfferent)
  {
   if(IIPosAfferent->Frequency > 0)
   {
	IIAfferentTrackBar->Position=IIPosAfferent->Frequency;
	IIAfferentEdit->Text=FloatToStrF(IIPosAfferent->Frequency,ffFixed,3,3);
   }
   else
   {
	IIAfferentTrackBar->Position=-IINegAfferent->Frequency;
	IIAfferentEdit->Text=FloatToStrF(-IINegAfferent->Frequency,ffFixed,3,3);
   }
  }
 }
 IINumAfferentTrackBarChange(this);

 if(ControlSystem)
 {
  RDK::UEPtr<RDK::UStatistic> stats=ControlSystem->GetComponentL<RDK::UStatistic>("StatisticDoubleMatrix",true);
  if(!stats)
  {
   NewStatsButton->Enabled=false;
   SaveStatsButton->Enabled=false;
  }
  else
  {
   NewStatsButton->Enabled=true;
   SaveStatsButton->Enabled=true;
  }
 }
 else
 {
  NewStatsButton->Enabled=false;
  SaveStatsButton->Enabled=false;
 }

 RDK::UEPtr<NMSDK::NDCEngine> engine=RDK::dynamic_pointer_cast<NMSDK::NDCEngine>(UniversalManipulator);
 double position=0;
 if(engine)
 {
  position=engine->OutMoment*double(MovementControlTrackBar->Max/2.0);
  MovementControlEdit->Text=FloatToStrF(engine->OutMoment,ffFixed,3,3);
 }

 if(position>0)
  MovementControlProgressBar->Position=position;
 else
  MovementControlProgressBar->Position=-position;

}

// Возврат интерфейса в исходное состояние
void TNManipulatorControlForm::AClearInterface(void)
{
 ManipulatorName.clear();

 ControlSystemName.clear();

 Manipulator=0;
 UniversalManipulator=0;

 Engine=0;
 Source=0;
 ControlSystem=0;

 IIPosAfferent=0; IINegAfferent=0;
 MN1PosControl=0; MN1NegControl=0;

 BmpCanvas.SetRes(0,0,BmpCanvas.GetColorModel());

 CanvasWidth=0;
 CanvasHeight=0;

 X=0; Y=0;

 Angle=0;

 Movement=0;

 Length=0;

 ZeroAngle=0;

 ZeroMovement=0;

 ReadComponentName.clear();
}

// Создание копии этого компонента
TUVisualControllerForm* TNManipulatorControlForm::New(TComponent *owner)
{
 return new TNManipulatorControlForm(owner);
}


// Считывает данные всех пармаетров из сети и выставляет в соответствующие позиции элементы управления
void TNManipulatorControlForm::LoadInterfaceInfoFromNet(void)
{
 if(!ControlSystem)
  return;

 int num_ranges=ControlSystem->NumMotionElements;
 bool flag=UpdateInterfaceFlag;
 if(!flag)
  UpdateInterfaceFlag=true;
 try
 {
  RDK::UEPtr<NMSDK::NPac> engine_input=RDK::dynamic_pointer_cast<NMSDK::NPac>(ControlSystem->GetComponent("Pac"));
  if(engine_input)
  {
   PACMultiplicatorTrackBar->Position=fabs(engine_input->Gain[0][0]);
   PACDeactivatorTimeEdit->Text=FloatToStrF(engine_input->Gain[0][0],ffFixed,3,3);
   PACActivatorTimeTrackBar->Position=engine_input->SecretionTC[0][0]*double(PACActivatorTimeTrackBar->Max);
   PACActivatorTimeEdit->Text=FloatToStrF(engine_input->SecretionTC[0][0],ffFixed,3,3);
   PACDeactivatorTimeTrackBar->Position=engine_input->DissociationTC[0][0]*double(PACDeactivatorTimeTrackBar->Max);
   PACDeactivatorTimeEdit->Text=FloatToStrF(engine_input->DissociationTC[0][0],ffFixed,3,3);
  }
 }
 catch(RDK::UContainer::EComponentNameNotExist &exception)
 {

 }
 IINumAfferentTrackBar->Max=num_ranges;

 if(!flag)
  UpdateInterfaceFlag=false;

 if(!Manipulator)
  return;

 if(!flag)
  UpdateInterfaceFlag=true;

 VoltageMulTrackBar->Position=Manipulator->OutputMul*100.0;
 VoltageMulEdit->Text=FloatToStrF(Manipulator->OutputMul,ffFixed,3,3);

 TimeDurationTrackBar->Position=Manipulator->TimeDuration;
 TimeDurationEdit->Text=FloatToStrF(Manipulator->TimeDuration,ffFixed,3,3);

 VaEdit->Text=Manipulator->GetAccumulationStep()*num_ranges;
 VdEdit->Text=Manipulator->GetDissociationStep();

 if(!flag)
  UpdateInterfaceFlag=false;
}

// Сохраняет параметры интерфейса в xml
void TNManipulatorControlForm::ASaveParameters(RDK::USerStorageXML &xml)
{
 xml.SelectNodeForce("Control");
 xml.WriteString("ManipulatorName",ManipulatorName);
 xml.WriteString("ControlSystemName",ControlSystemName);
 xml.SelectUp();
}

// Загружает параметры интерфейса из xml
void TNManipulatorControlForm::ALoadParameters(RDK::USerStorageXML &xml)
{
 ManipulatorName.clear();
 ControlSystemName.clear();

 Manipulator=0;
 UniversalManipulator=0;

 Engine=0;
 Source=0;
 ControlSystem=0;

 IIPosAfferent=0;
 IINegAfferent=0;
 MN1PosControl=0;
 MN1NegControl=0;

 ZeroAngle=0;

 ZeroMovement=0;

 Movement=0;


 xml.SelectNodeForce("Control");
 ManipulatorName=xml.ReadString("ManipulatorName","");
 if(!ManipulatorName.empty())
 {
  UniversalManipulator=RDK::dynamic_pointer_cast<NMSDK::UNet>(GetModel()->GetComponentL(ManipulatorName));
  Manipulator=RDK::dynamic_pointer_cast<NMSDK::NWPhysicalManipulator>(GetModel()->GetComponentL(ManipulatorName));
 }
 if(!UniversalManipulator)
  ManipulatorName="";

 ControlSystemName=xml.ReadString("ControlSystemName","");
 if(!ControlSystemName.empty())
  ControlSystem=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(GetModel()->GetComponentL(ControlSystemName));
 if(!ControlSystem)
  ControlSystemName="";
 else
 {
  ManipulatorCSConnect(ControlSystemName, ManipulatorName);
 }

 xml.SelectUp();

 LoadInterfaceInfoFromNet();

 IINumAfferentTrackBar->Position=0;
 IINumAfferentTrackBarChange(this);
 ResetToZeroButton1Click(this);
 ResetToZeroButton2Click(this);

 UpdateInterval=100;
}



bool TNManipulatorControlForm::ManipulatorCSConnect(const std::string &cs_name, const std::string &man_name)
{
 RDK::UEPtr<RDK::UNet> net=RDK::dynamic_pointer_cast<RDK::UNet>(GetModel());

 bool res=true;
 std::string source_name=cs_name+".NManipulatorSource1";
 if(!cs_name.empty())
 {
 net->BreakConnectorLink(source_name,0);
 net->BreakConnectorLink(source_name,1);
 net->BreakConnectorLink(source_name,2);
 net->BreakConnectorLink(source_name,3);
// RDK::dynamic_pointer_cast<RDK::UConnector>(net->GetComponentL(source_name))->DisconnectAllItems();
 RDK::dynamic_pointer_cast<RDK::UADItem>(net->GetComponentL(cs_name+".NManipulatorInput1"))->DisconnectAll();
 if(man_name == "PendulumAndCart")
 {
  res&=net->CreateLink(man_name,3,source_name,0);
  res&=net->CreateLink(man_name,4,source_name,3);
 }
 else
  res&=net->CreateLink(man_name,0,source_name,0);

 res&=net->CreateLink(man_name,1,source_name,1);
 res&=net->CreateLink(man_name,2,source_name,2);
 res&=net->CreateLink(cs_name+".NManipulatorInput1",0,man_name,0);
 }
 /*
 // Связываем все управляющие элементы
 int motion_elements=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(net->GetComponentL(cs_name))->NumMotionElements;
 int conn_index=1;
 for(int i=0;i<motion_elements;i++)
 {
  res&=net->CreateLink(cs_name+std::string(".MotionElement")+RDK::sntoa(i)
	+".Motoneuron1.LTZone",0,man_name,conn_index++);
  res&=net->CreateLink(cs_name+std::string(".MotionElement")+RDK::sntoa(i)
	+".Motoneuron2.LTZone",0,man_name,conn_index++);
 } */

 ZeroAngle=+3.14/2;
 return res;
}


// Считывает данные из компонента
void TNManipulatorControlForm::ReadComponentData(void)
{
 if(!ControlSystem)
  return;
 ReadComponentName=ManipulatorName;

 Angle=RDK::dynamic_pointer_cast<RDK::UADItem>(GetModel()->GetComponentL(ReadComponentName))->GetOutputData(1).Double[0];

 if(RDK::dynamic_pointer_cast<RDK::UADItem>(GetModel()->GetComponentL(ReadComponentName))->GetNumOutputs()>3)
 {
  Movement=RDK::dynamic_pointer_cast<RDK::UADItem>(GetModel()->GetComponentL(ReadComponentName))->GetOutputData(3).Double[0];
  Movement*=100; // в 1 метре 10 пикселей
 }
}

void TNManipulatorControlForm::ReconnectCurrentManipulator(void)
{
 if(Manipulator)
 {
  Disconnect1Click(this);
//  ManipulatorName="";
 }

// ManipulatorName=UComponentsListForm->ComponentsListFrame1->GetSelectedComponentLongName();
 UniversalManipulator=RDK::dynamic_pointer_cast<RDK::UNet>(GetModel()->GetComponentL(ManipulatorName));
 Manipulator=RDK::dynamic_pointer_cast<NMSDK::NWPhysicalManipulator>(GetModel()->GetComponentL(ManipulatorName));
 if(!UniversalManipulator)
  ManipulatorName="";
 ManipulatorCSConnect(ControlSystemName, ManipulatorName);
}

void TNManipulatorControlForm::ReconnectManipulator(void)
{
 if(Manipulator)
 {
  Disconnect1Click(this);
  ManipulatorName="";
 }

 ManipulatorName=UComponentsListForm->ComponentsListFrame1->GetSelectedComponentLongName();
 UniversalManipulator=RDK::dynamic_pointer_cast<RDK::UNet>(GetModel()->GetComponentL(ManipulatorName));
 Manipulator=RDK::dynamic_pointer_cast<NMSDK::NWPhysicalManipulator>(GetModel()->GetComponentL(ManipulatorName));
 if(!UniversalManipulator)
  ManipulatorName="";
 ManipulatorCSConnect(ControlSystemName, ManipulatorName);
}
//---------------------------------------------------------------------------
void __fastcall TNManipulatorControlForm::Disconnect1Click(TObject *Sender)
{
 if(!Manipulator)
  return;

 Manipulator->UnInitManipulator();
 Manipulator->UnLoadManipulatorDll();
 UpdateInterface();
}
//---------------------------------------------------------------------------
void __fastcall TNManipulatorControlForm::MoveLeft1Click(TObject *Sender)
{
 if(!Manipulator || !Manipulator->DMMoveServo)
  return;

 Manipulator->DMMoveServo(1,1,255,50);
}
//---------------------------------------------------------------------------
void __fastcall TNManipulatorControlForm::MoveRight1Click(TObject *Sender)
{
 if(!Manipulator || !Manipulator->DMMoveServo)
  return;

 Manipulator->DMMoveServo(1,2,255,50);
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::SelectManipulator1Click(TObject *Sender)
{
 if(UComponentsListForm->ShowComponentSelect() != mrOk)
  return;

 ReconnectManipulator();
 UpdateInterface();
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::Connect1Click(TObject *Sender)
{
 if(!Manipulator)
  return;
 Manipulator->WindowHandle=Handle;
 Manipulator->ComPort=StrToInt(ComPortComboBox->Text);
 if(EmulatorModeRadioButton->Checked == true)
  Manipulator->EmulatorMode=true;
 else
  Manipulator->EmulatorMode=false;

 Manipulator->DllManipulatorMode=ControlModeComboBox->ItemIndex;
 Manipulator->LoadManipulatorDll();
 Manipulator->InitManipulator();
 UpdateInterface();
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::DeviceModeRadioButtonClick(TObject *Sender)
{
 ComPortComboBox->Enabled=true;
 EmulatorModeRadioButton->Checked=false;
 ControlModeComboBox->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::EmulatorModeRadioButtonClick(TObject *Sender)

{
 ComPortComboBox->Enabled=false;
 DeviceModeRadioButton->Checked=false;
 ControlModeComboBox->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::FormShow(TObject *Sender)
{
 UpdateInterface();
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::ComponentSelectionPanelDblClick(TObject *Sender)
{
 SelectManipulator1Click(Sender);
// UDrawEngineForm->ReloadNet();
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::ConnectButtonClick(TObject *Sender)
{
 Connect1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::DisconnectButtonClick(TObject *Sender)
{
 Disconnect1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::Reset1Click(TObject *Sender)
{
 if(!Manipulator || !Manipulator->DMReset)
  return;

 Manipulator->DMReset();
 UpdateInterface();
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::ResetButtonClick(TObject *Sender)
{
 Reset1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::StartButtonClick(TObject *Sender)
{
 Start1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::StopButtonClick(TObject *Sender)
{
 Stop1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::Start1Click(TObject *Sender)
{
 if(!Manipulator || !Manipulator->DMStart)
  return;

 Manipulator->DMStart();
 UpdateInterface();
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::Stop1Click(TObject *Sender)
{
 if(!Manipulator || !Manipulator->DMStop)
  return;

 Manipulator->DMStop();
 UpdateInterface();
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::Button2Click(TObject *Sender)
{
 if(!Manipulator || !Manipulator->DMMoveServo)
  return;

 Manipulator->DMMoveServo(CBoxServoMove->ItemIndex, ComboBoxDir->ItemIndex+1, TrackBarPWM->Position, TrackBarTime->Position);
}
//---------------------------------------------------------------------------


void __fastcall TNManipulatorControlForm::FormClose(TObject *Sender, TCloseAction &Action)

{
 Disconnect1Click(Sender);
 Sleep(100);
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::IaCheckBoxClick(TObject *Sender)
{
 if(UpdateInterfaceFlag)
  return;

// bool res=true;
// RDK::UEPtr<NMSDK::UContainer> cont;

 if(!ControlSystem)
  return;

// int num_motions=ControlSystem->NumMotionElements;

 std::vector<bool> act_conts=ControlSystem->ActiveContours;
 if(act_conts.size()<2)
  act_conts.resize(2,0);
 act_conts[1]=(IaCheckBox->Checked)?true:false;
 ControlSystem->ActiveContours=act_conts;
/*
 if(IaCheckBox->Checked)
  {
   for(int i=0;i<num_motions;i++)
   {
	std::string motion=std::string("MotionElement")+RDK::sntoa(i);
	std::string pos_separator=std::string("Ia_PosIntervalSeparator")+RDK::sntoa(i+1);
	std::string neg_separator=std::string("Ia_NegIntervalSeparator")+RDK::sntoa(i+1);
	if(!Model_CheckComponent((ControlSystemName+std::string(".")+motion+".Afferent_Ia1.Receptor").c_str()) ||
	   !Model_CheckComponent((ControlSystemName+std::string(".")+motion+".Afferent_Ia2.Receptor").c_str()))
	 break;
	res&=ControlSystem->BreakLink("AfferentSource1",0,motion+".Afferent_Ia2.Receptor",0);
	res&=ControlSystem->BreakLink("AfferentSource1",0,motion+".Afferent_Ia1.Receptor",0);

	res&=ControlSystem->CreateLink(pos_separator,0,motion+".Afferent_Ia2.Receptor",0);
	res&=ControlSystem->CreateLink(neg_separator,0,motion+".Afferent_Ia1.Receptor",0);
   }
  }
 else
  {
   for(int i=0;i<num_motions;i++)
   {
	std::string motion=std::string("MotionElement")+RDK::sntoa(i);
	std::string pos_separator=std::string("Ia_PosIntervalSeparator")+RDK::sntoa(i+1);
	std::string neg_separator=std::string("Ia_NegIntervalSeparator")+RDK::sntoa(i+1);
	if(!Model_CheckComponent((ControlSystemName+std::string(".")+motion+".Afferent_Ia1.Receptor").c_str()) ||
	   !Model_CheckComponent((ControlSystemName+std::string(".")+motion+".Afferent_Ia2.Receptor").c_str()))
	 break;
	res&=ControlSystem->BreakLink(pos_separator,0,motion+".Afferent_Ia2.Receptor",0);
	res&=ControlSystem->BreakLink(neg_separator,0,motion+".Afferent_Ia1.Receptor",0);

	res&=ControlSystem->CreateLink("AfferentSource1",0,motion+".Afferent_Ia2.Receptor",0);
	res&=ControlSystem->CreateLink("AfferentSource1",0,motion+".Afferent_Ia1.Receptor",0);
   }
  }

 if(!res)
  return;
        */
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::IIAfferentTrackBarChange(TObject *Sender)

{
 if(UpdateInterfaceFlag)
  return;

 if(!ControlSystem)
  return;

 IIPosAfferent=RDK::dynamic_pointer_cast<NMSDK::NPulseGenerator>(ControlSystem->GetComponentL("IIPosAfferentGenerator"));
 IINegAfferent=RDK::dynamic_pointer_cast<NMSDK::NPulseGenerator>(ControlSystem->GetComponentL("IINegAfferentGenerator"));


 if(!IIPosAfferent || !IINegAfferent)
  return;

 if(IIAfferentTrackBar->Position>=0)
 {
  IIPosAfferent->Frequency=IIAfferentTrackBar->Position;
  IINegAfferent->Frequency=0;
  IIAfferentEdit->Text=FloatToStrF(IIPosAfferent->Frequency,ffFixed,3,3);
 }
 else
 {
  IINegAfferent->Frequency=-IIAfferentTrackBar->Position;
  IIPosAfferent->Frequency=0;
  IIAfferentEdit->Text=FloatToStrF(-IINegAfferent->Frequency,ffFixed,3,3);
 }
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::IINumAfferentTrackBarChange(TObject *Sender)

{
 if(UpdateInterfaceFlag)
  return;

 bool res=true;

 if(!ControlSystem)
  return;

 try
 {
  res&=ControlSystem->BreakAllOutgoingLinks("IIPosAfferentGenerator");
  res&=ControlSystem->BreakAllOutgoingLinks("IINegAfferentGenerator");
 for(int i=0;i<IINumAfferentTrackBar->Position;i++)
 {
  // Вариант для отдельного участка мембраны для внешнего управления
  res&=ControlSystem->CreateLink("IIPosAfferentGenerator",0,std::string("MotionElement")+RDK::sntoa(i)+".PostAfferent14.PNeuronMembrane.PosChannel",0);
  res&=ControlSystem->CreateLink("IIPosAfferentGenerator",0,std::string("MotionElement")+RDK::sntoa(i)+".PostAfferent24.PNeuronMembrane.NegChannel",0);
  res&=ControlSystem->CreateLink("IINegAfferentGenerator",0,std::string("MotionElement")+RDK::sntoa(i)+".PostAfferent14.PNeuronMembrane.NegChannel",0);
  res&=ControlSystem->CreateLink("IINegAfferentGenerator",0,std::string("MotionElement")+RDK::sntoa(i)+".PostAfferent24.PNeuronMembrane.PosChannel",0);
 }

 for(int i=IINumAfferentTrackBar->Position;i<IINumAfferentTrackBar->Max;i++)
 {
  // Вариант для отдельного участка мембраны для внешнего управления
  res&=ControlSystem->BreakLink("IIPosAfferentGenerator",0,std::string("MotionElement")+RDK::sntoa(i)+".PostAfferent14.PNeuronMembrane.PosChannel",0);
  res&=ControlSystem->BreakLink("IIPosAfferentGenerator",0,std::string("MotionElement")+RDK::sntoa(i)+".PostAfferent24.PNeuronMembrane.NegChannel",0);
  res&=ControlSystem->BreakLink("IINegAfferentGenerator",0,std::string("MotionElement")+RDK::sntoa(i)+".PostAfferent14.PNeuronMembrane.NegChannel",0);
  res&=ControlSystem->BreakLink("IINegAfferentGenerator",0,std::string("MotionElement")+RDK::sntoa(i)+".PostAfferent24.PNeuronMembrane.PosChannel",0);
 }

 }
 catch(RDK::UContainer::EComponentNameNotExist &exception)
 {

 }
 IINumAfferentEdit->Text=IntToStr(IINumAfferentTrackBar->Position);
 if(!res)
  return;
// UDrawEngineForm->ReloadNet();
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::IbCheckBoxClick(TObject *Sender)
{
 if(UpdateInterfaceFlag)
  return;

 bool res=true;
// RDK::UEPtr<NMSDK::NAContainer> cont;

 if(!ControlSystem)
  return;
 std::vector<bool> act_conts=ControlSystem->ActiveContours;
 if(act_conts.size()<3)
  act_conts.resize(3,0);
 act_conts[2]=(IbCheckBox->Checked)?true:false;
 ControlSystem->ActiveContours=act_conts;

 /*
 int num_motions=ControlSystem->NumMotionElements;
  if(IbCheckBox->Checked)
  {
   for(int i=0;i<num_motions;i++)
   {
	std::string motion=std::string("MotionElement")+RDK::sntoa(i);
	std::string pos_separator=std::string("Ib_PosIntervalSeparator")+RDK::sntoa(i+1);
	std::string neg_separator=std::string("Ib_NegIntervalSeparator")+RDK::sntoa(i+1);

	if(!Model_CheckComponent((ControlSystemName+std::string(".")+motion+".Afferent_Ib1.Receptor").c_str()) ||
	   !Model_CheckComponent((ControlSystemName+std::string(".")+motion+".Afferent_Ib2.Receptor").c_str()))
	 break;

	res&=ControlSystem->BreakLink("AfferentSource1",0,motion+".Afferent_Ib2.Receptor",0);
	res&=ControlSystem->BreakLink("AfferentSource1",0,motion+".Afferent_Ib1.Receptor",0);

	res&=ControlSystem->CreateLink(pos_separator,0,motion+".Afferent_Ib1.Receptor",0);
	res&=ControlSystem->CreateLink(neg_separator,0,motion+".Afferent_Ib2.Receptor",0);
   }
  }
  else
  {
   for(int i=0;i<num_motions;i++)
   {
	std::string motion=std::string("MotionElement")+RDK::sntoa(i);
	std::string pos_separator=std::string("Ib_PosIntervalSeparator")+RDK::sntoa(i+1);
	std::string neg_separator=std::string("Ib_NegIntervalSeparator")+RDK::sntoa(i+1);

	if(!Model_CheckComponent((ControlSystemName+std::string(".")+motion+".Afferent_Ib1.Receptor").c_str()) ||
	   !Model_CheckComponent((ControlSystemName+std::string(".")+motion+".Afferent_Ib2.Receptor").c_str()))
	 break;

	res&=ControlSystem->BreakLink(pos_separator,0,motion+".Afferent_Ib1.Receptor",0);
	res&=ControlSystem->BreakLink(neg_separator,0,motion+".Afferent_Ib2.Receptor",0);

	res&=ControlSystem->CreateLink("AfferentSource1",0,motion+".Afferent_Ib1.Receptor",0);
	res&=ControlSystem->CreateLink("AfferentSource1",0,motion+".Afferent_Ib2.Receptor",0);
   }
  }

 if(!res)
  return;
	   */
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::IICheckBoxClick(TObject *Sender)
{
 if(UpdateInterfaceFlag)
  return;

 bool res=true;
// RDK::UEPtr<NMSDK::NAContainer> cont;

 if(!ControlSystem)
  return;
 std::vector<bool> act_conts=ControlSystem->ActiveContours;
 if(act_conts.size()<1)
  act_conts.resize(1,0);
 act_conts[0]=(IICheckBox->Checked)?true:false;
 ControlSystem->ActiveContours=act_conts;
/*
 int num_motions=ControlSystem->NumMotionElements;

  if(IICheckBox->Checked)
  {
   for(int i=0;i<num_motions;i++)
   {
	std::string motion=std::string("MotionElement")+RDK::sntoa(i);
	std::string pos_separator=std::string("II_PosIntervalSeparator")+RDK::sntoa(i+1);
	std::string neg_separator=std::string("II_NegIntervalSeparator")+RDK::sntoa(i+1);

	if(!Model_CheckComponent((ControlSystemName+std::string(".")+motion+".Afferent_II1.Receptor").c_str()) ||
	   !Model_CheckComponent((ControlSystemName+std::string(".")+motion+".Afferent_II2.Receptor").c_str()))
	 break;

	res&=ControlSystem->BreakLink("AfferentSource1",0,motion+".Afferent_II2.Receptor",0);
	res&=ControlSystem->BreakLink("AfferentSource1",0,motion+".Afferent_II1.Receptor",0);

	res&=ControlSystem->CreateLink(pos_separator,0,motion+".Afferent_II1.Receptor",0);
	res&=ControlSystem->CreateLink(neg_separator,0,motion+".Afferent_II2.Receptor",0);
   }
  }
  else
  {
   for(int i=0;i<num_motions;i++)
   {
	std::string motion=std::string("MotionElement")+RDK::sntoa(i);
	std::string pos_separator=std::string("II_PosIntervalSeparator")+RDK::sntoa(i+1);
	std::string neg_separator=std::string("II_NegIntervalSeparator")+RDK::sntoa(i+1);

	if(!Model_CheckComponent((ControlSystemName+std::string(".")+motion+".Afferent_II1.Receptor").c_str()) ||
	   !Model_CheckComponent((ControlSystemName+std::string(".")+motion+".Afferent_II2.Receptor").c_str()))
	 break;

	res&=ControlSystem->BreakLink(pos_separator,0,motion+".Afferent_II1.Receptor",0);
	res&=ControlSystem->BreakLink(neg_separator,0,motion+".Afferent_II2.Receptor",0);

	res&=ControlSystem->CreateLink("AfferentSource1",0,motion+".Afferent_II2.Receptor",0);
	res&=ControlSystem->CreateLink("AfferentSource1",0,motion+".Afferent_II1.Receptor",0);
   }
  }
 if(!res)
  return;
  */
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::ControlVoltageCheckBoxClick(TObject *Sender)

{
 if(UpdateInterfaceFlag)
  return;

 bool res=true;

 if(!ControlSystem)
  return;

  if(ControlVoltageCheckBox->Checked == false)
  {
   res&=ControlSystem->BreakLink("Pac",0,"NManipulatorInput1",0);

//   res&=ControlSystem->BreakLink("Pac",0,"NManipulatorInputEmulator1",0);
  }
  else
  {
   res&=ControlSystem->CreateLink("Pac",0,"NManipulatorInput1",0);

//   res&=ControlSystem->CreateLink("Pac",0,"NManipulatorInputEmulator1",0);
  }

 if(!res)
  return;
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::SelectControlSystem1Click(TObject *Sender)
{
 if(UComponentsListForm->ShowComponentSelect() != mrOk)
  return;

 ControlSystemName=UComponentsListForm->ComponentsListFrame1->GetSelectedComponentLongName();
 ControlSystem=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(GetModel()->GetComponentL(ControlSystemName));
 if(!ControlSystem)
  ControlSystemName="";

 UpdateInterface();
}
//---------------------------------------------------------------------------


void __fastcall TNManipulatorControlForm::ControlSystemSelectionPanelDblClick(TObject *Sender)
{
 SelectControlSystem1Click(Sender);
 ReconnectCurrentManipulator();
// UDrawEngineForm->UpdateInterface();
}
//---------------------------------------------------------------------------




void __fastcall TNManipulatorControlForm::VoltageMulTrackBarChange(TObject *Sender)

{
 double value=VoltageMulTrackBar->Position/100.0;
 VoltageMulEdit->Text=FloatToStrF(value,ffFixed,3,3);

 if(!Manipulator)
  return;

 Manipulator->OutputMul=value;
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::TimeDurationTrackBarChange(TObject *Sender)

{
 double value=TimeDurationTrackBar->Position;
 TimeDurationEdit->Text=FloatToStrF(value,ffFixed,3,3);

 if(!Manipulator)
  return;

 Manipulator->TimeDuration=value;
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::PACDeactivatorTimeTrackBarChange(TObject *Sender)
{
 if(!ControlSystem || UpdateInterfaceFlag)
  return;
 int num_ranges=ControlSystem->NumMotionElements;
 double value=double(PACDeactivatorTimeTrackBar->Position)/double(PACDeactivatorTimeTrackBar->Max);
 PACDeactivatorTimeEdit->Text=FloatToStrF(value,ffFixed,3,3);

 RDK::UEPtr<NMSDK::NPac> engine_input=RDK::dynamic_pointer_cast<NMSDK::NPac>(ControlSystem->GetComponent("Pac"));
 if(engine_input)
 {
  std::vector<NMSDK::Real> values;

  values.resize(num_ranges*2);
  // Постоянная времени распада медиатора
  for(size_t i=0;i<values.size();i++)
   values[i].assign(1,value);
  engine_input->DissociationTC=values;
 }
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::PACActivatorTimeTrackBarChange(TObject *Sender)

{
 if(!ControlSystem)
  return;
 int num_ranges=ControlSystem->NumMotionElements;
 double value=double(PACActivatorTimeTrackBar->Position)/double(PACActivatorTimeTrackBar->Max);
 PACActivatorTimeEdit->Text=FloatToStrF(value,ffFixed,3,3);

 RDK::UEPtr<NMSDK::NPac> engine_input=RDK::dynamic_pointer_cast<NMSDK::NPac>(ControlSystem->GetComponent("Pac"));
 if(engine_input)
 {
  std::vector<NMSDK::Real> values;

  values.resize(num_ranges*2);
  // Постоянная времени распада медиатора
  for(size_t i=0;i<values.size();i++)
   values[i].assign(1,value);
  engine_input->SecretionTC=values;
 }
}
//---------------------------------------------------------------------------


void __fastcall TNManipulatorControlForm::SendVButtonClick(TObject *Sender)
{
 if(!Manipulator)
  return;

 if(!ControlSystem)
  return;

 int num_ranges=ControlSystem->NumMotionElements;
 Manipulator->SetAccumulationStep(StrToInt(VaEdit->Text)/num_ranges);
 Manipulator->SetDissociationStep(StrToInt(VdEdit->Text));
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::PACMultiplicatorTrackBarChange(TObject *Sender)
{
 if(!ControlSystem || UpdateInterfaceFlag)
  return;
 int num_ranges=ControlSystem->NumMotionElements;
 double value=double(PACMultiplicatorTrackBar->Position);
 PACMultiplicatorEdit->Text=FloatToStrF(value,ffFixed,3,3);

 RDK::UEPtr<NMSDK::NPac> engine_input=RDK::dynamic_pointer_cast<NMSDK::NPac>(ControlSystem->GetComponent("Pac"));
 if(engine_input)
 {
  std::vector<NMSDK::Real> values;

  values.resize(num_ranges*2);
  for(size_t i=0;i<values.size()/2;i++)
   values[i].assign(1,-value);
  for(size_t i=values.size()/2;i<values.size();i++)
   values[i].assign(1,value);
  engine_input->Gain=values;
 }

}
//---------------------------------------------------------------------------


void __fastcall TNManipulatorControlForm::MomentTrackBarChange(TObject *Sender)
{
 if(UpdateInterfaceFlag)
  return;

 if(!ControlSystem)
  return;

 RDK::UEPtr<NMSDK::NManipulatorSource> source=RDK::dynamic_pointer_cast<NMSDK::NManipulatorSource>(ControlSystem->GetComponentL("NManipulatorSource1"));
 RDK::UEPtr<NMSDK::NDCEngine> engine=RDK::dynamic_pointer_cast<NMSDK::NDCEngine>(UniversalManipulator);
 RDK::UEPtr<NMSDK::NPendulumAndCart> engine2=RDK::dynamic_pointer_cast<NMSDK::NPendulumAndCart>(UniversalManipulator);
 double amplitude=double(MomentTrackBar->Position)/double(MomentTrackBar->Max/2.0);
 ExtMomentEdit->Text=FloatToStrF(amplitude,ffFixed,3,3);
 if(engine && source)
 {
  source->Angle=amplitude;
//  engine->OutMoment=amplitude;
 }
 if(engine2)
 {
  engine2->OutXMovement=amplitude;
 }

 if(MomentTrackBar->Position>0)
  MomentProgressBar->Position=MomentTrackBar->Position;
 else
  MomentProgressBar->Position=-MomentTrackBar->Position;
}
//---------------------------------------------------------------------------



void __fastcall TNManipulatorControlForm::CheckBox1Click(TObject *Sender)
{
 if(UpdateInterfaceFlag)
  return;

 bool res=true;
// RDK::UEPtr<NMSDK::NAContainer> cont;

 if(!ControlSystem)
  return;

 if(!Model_CheckComponent((ControlSystemName+std::string(".")+"MotionElement0.Afferent_Ic1.Receptor").c_str()))
  return;
 std::vector<bool> act_conts=ControlSystem->ActiveContours;
 if(act_conts.size()<4)
  act_conts.resize(4,0);
 act_conts[3]=(CheckBox1->Checked)?true:false;
 ControlSystem->ActiveContours=act_conts;
/*
 int num_motions=ControlSystem->NumMotionElements;

  if(CheckBox1->Checked)
  {
   for(int i=0;i<num_motions;i++)
   {
	std::string motion=std::string("MotionElement")+RDK::sntoa(i);
	std::string pos_separator=std::string("Ic_PosIntervalSeparator")+RDK::sntoa(i+1);
	std::string neg_separator=std::string("Ic_NegIntervalSeparator")+RDK::sntoa(i+1);

	if(!Model_CheckComponent((ControlSystemName+std::string(".")+motion+".Afferent_Ic1.Receptor").c_str()) ||
	   !Model_CheckComponent((ControlSystemName+std::string(".")+motion+".Afferent_Ic2.Receptor").c_str()))
	 break;

	res&=ControlSystem->BreakLink("AfferentSource1",0,motion+".Afferent_Ic2.Receptor",0);
	res&=ControlSystem->BreakLink("AfferentSource1",0,motion+".Afferent_Ic1.Receptor",0);

	res&=ControlSystem->CreateLink(pos_separator,0,motion+".Afferent_Ic1.Receptor",0);
	res&=ControlSystem->CreateLink(neg_separator,0,motion+".Afferent_Ic2.Receptor",0);
   }
  }
  else
  {
   for(int i=0;i<num_motions;i++)
   {
	std::string motion=std::string("MotionElement")+RDK::sntoa(i);
	std::string pos_separator=std::string("Ic_PosIntervalSeparator")+RDK::sntoa(i+1);
	std::string neg_separator=std::string("Ic_NegIntervalSeparator")+RDK::sntoa(i+1);

	if(!Model_CheckComponent((ControlSystemName+std::string(".")+motion+".Afferent_Ic1.Receptor").c_str()) ||
	   !Model_CheckComponent((ControlSystemName+std::string(".")+motion+".Afferent_Ic2.Receptor").c_str()))
	 break;

	res&=ControlSystem->BreakLink(pos_separator,0,motion+".Afferent_Ic1.Receptor",0);
	res&=ControlSystem->BreakLink(neg_separator,0,motion+".Afferent_Ic2.Receptor",0);

	res&=ControlSystem->CreateLink("AfferentSource1",0,motion+".Afferent_Ic2.Receptor",0);
	res&=ControlSystem->CreateLink("AfferentSource1",0,motion+".Afferent_Ic1.Receptor",0);
   }
  }
 if(!res)
  return;
		  */

}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::MovementControlTrackBarChange(TObject *Sender)

{
 if(UpdateInterfaceFlag)
  return;

 if(!ControlSystem)
  return;

 RDK::UEPtr<NMSDK::NManipulatorSource> source=RDK::dynamic_pointer_cast<NMSDK::NManipulatorSource>(ControlSystem->GetComponentL("NManipulatorSource1"));
 double amplitude=double(MovementControlTrackBar->Position)/double(MovementControlTrackBar->Max/2.0);
 MovementControlEdit->Text=FloatToStrF(amplitude,ffFixed,3,3);

 RDK::UEPtr<NMSDK::NDCEngine> engine=RDK::dynamic_pointer_cast<NMSDK::NDCEngine>(UniversalManipulator);
 RDK::UEPtr<NMSDK::NPendulumAndCart> engine2=RDK::dynamic_pointer_cast<NMSDK::NPendulumAndCart>(UniversalManipulator);
 RDK::UEPtr<NMSDK::NWPhysicalManipulator> man=RDK::dynamic_pointer_cast<NMSDK::NWPhysicalManipulator>(UniversalManipulator);

 if(source)
 {
  if(engine)
  {
   engine->OutMoment=amplitude;
 //  source->Angle=amplitude;
  }

  if(engine2)
  {
   engine2->ExtrenalMoment=amplitude;
//   source->Movement=amplitude;
  }

 }

 if(MovementControlTrackBar->Position>0)
  MovementControlProgressBar->Position=MovementControlTrackBar->Position;
 else
  MovementControlProgressBar->Position=-MovementControlTrackBar->Position;
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::HideSecondaryGuiCheckBoxClick(TObject *Sender)

{
 if(HideSecondaryGuiCheckBox->Checked)
 {
  GroupBox8->Visible=false;
  Panel2->Visible=false;
  Splitter1->Visible=false;
  Splitter2->Visible=false;
 }
 else
 {
  GroupBox8->Visible=true;
  Panel2->Visible=true;
  Splitter1->Visible=true;
  Splitter2->Visible=true;
 }
 DrawGrid->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::FormCreate(TObject *Sender)
{
 TempBmp=new TBitmap;
 int max_number_of_mc=10;

 TUComponentsListFrame::ComponentControllers["NAslsNewSimplestAfferentBranchedEngineControlPM"]=NManipulatorControlForm;
 for(int i=1;i<max_number_of_mc;i++)
  TUComponentsListFrame::ComponentControllers[std::string("NAslsNewSimplestAfferentBranchedEngineControlPM")+RDK::sntoa(i+1)]=NManipulatorControlForm;

 TUComponentsListFrame::ComponentControllers["NAsfNewSimplestAfferentBranchedEngineControlPM"]=NManipulatorControlForm;
 for(int i=1;i<max_number_of_mc;i++)
  TUComponentsListFrame::ComponentControllers[std::string("NAsfNewSimplestAfferentBranchedEngineControlPM")+RDK::sntoa(i+1)]=NManipulatorControlForm;

 TUComponentsListFrame::ComponentControllers["NAslsNewSimplestAfferentBranchedEngineControl"]=NManipulatorControlForm;
 for(int i=1;i<max_number_of_mc;i++)
  TUComponentsListFrame::ComponentControllers[std::string("NAslsNewSimplestAfferentBranchedEngineControl")+RDK::sntoa(i+1)]=NManipulatorControlForm;

 TUComponentsListFrame::ComponentControllers["NAsfNewSimplestAfferentBranchedEngineControl"]=NManipulatorControlForm;
 for(int i=1;i<max_number_of_mc;i++)
  TUComponentsListFrame::ComponentControllers[std::string("NAsfNewSimplestAfferentBranchedEngineControl")+RDK::sntoa(i+1)]=NManipulatorControlForm;

 TUComponentsListFrame::ComponentControllers["NNewSimplestAfferentBranchedEngineControl"]=NManipulatorControlForm;
 for(int i=1;i<max_number_of_mc;i++)
  TUComponentsListFrame::ComponentControllers[std::string("NNewSimplestAfferentBranchedEngineControl")+RDK::sntoa(i+1)]=NManipulatorControlForm;

 TUComponentsListFrame::ComponentControllers["NSimplestAfferentBranchedEngineControl"]=NManipulatorControlForm;
 for(int i=1;i<max_number_of_mc;i++)
  TUComponentsListFrame::ComponentControllers[std::string("NSimplestAfferentBranchedEngineControl")+RDK::sntoa(i+1)]=NManipulatorControlForm;

 TUComponentsListFrame::ComponentControllers["NSimplestBranchedEngineControl"]=NManipulatorControlForm;
 for(int i=1;i<max_number_of_mc;i++)
  TUComponentsListFrame::ComponentControllers[std::string("NSimplestBranchedEngineControl")+RDK::sntoa(i+1)]=NManipulatorControlForm;

 TUComponentsListFrame::ComponentControllers["NSimplestEngineControl"]=NManipulatorControlForm;
 for(int i=1;i<max_number_of_mc;i++)
  TUComponentsListFrame::ComponentControllers[std::string("NSimplestEngineControl")+RDK::sntoa(i+1)]=NManipulatorControlForm;

 TUComponentsListFrame::ComponentControllers["NContinuesIndRangeBranchedCrosslinksEngineControlRangeAfferent"]=NManipulatorControlForm;
 for(int i=1;i<max_number_of_mc;i++)
  TUComponentsListFrame::ComponentControllers[std::string("NContinuesIndRangeBranchedCrosslinksEngineControlRangeAfferent")+RDK::sntoa(i+1)]=NManipulatorControlForm;

 TUComponentsListFrame::ComponentControllers["NIndRangeBranchedCrosslinksEngineControlRangeAfferent"]=NManipulatorControlForm;
 for(int i=1;i<max_number_of_mc;i++)
  TUComponentsListFrame::ComponentControllers[std::string("NIndRangeBranchedCrosslinksEngineControlRangeAfferent")+RDK::sntoa(i+1)]=NManipulatorControlForm;

 TUComponentsListFrame::ComponentControllers["NIndRangeBranchedEngineControlRangeAfferent"]=NManipulatorControlForm;
 for(int i=1;i<max_number_of_mc;i++)
  TUComponentsListFrame::ComponentControllers[std::string("NIndRangeBranchedEngineControlRangeAfferent")+RDK::sntoa(i+1)]=NManipulatorControlForm;

 TUComponentsListFrame::ComponentControllers["NSimpleBranchedCrosslinksEngineControlRangeAfferent"]=NManipulatorControlForm;
 for(int i=1;i<max_number_of_mc;i++)
  TUComponentsListFrame::ComponentControllers[std::string("NSimpleBranchedCrosslinksEngineControlRangeAfferent")+RDK::sntoa(i+1)]=NManipulatorControlForm;

 TUComponentsListFrame::ComponentControllers["NBranchedCrosslinksEngineControlRangeAfferent"]=NManipulatorControlForm;
 for(int i=1;i<max_number_of_mc;i++)
  TUComponentsListFrame::ComponentControllers[std::string("NBranchedCrosslinksEngineControlRangeAfferent")+RDK::sntoa(i+1)]=NManipulatorControlForm;

 TUComponentsListFrame::ComponentControllers["NSimpleBranchedEngineControlRangeAfferent"]=NManipulatorControlForm;
 for(int i=1;i<max_number_of_mc;i++)
  TUComponentsListFrame::ComponentControllers[std::string("NSimpleBranchedEngineControlRangeAfferent")+RDK::sntoa(i+1)]=NManipulatorControlForm;

 TUComponentsListFrame::ComponentControllers["NBranchedEngineControlRangeAfferent"]=NManipulatorControlForm;
 for(int i=1;i<max_number_of_mc;i++)
  TUComponentsListFrame::ComponentControllers[std::string("NBranchedEngineControlRangeAfferent")+RDK::sntoa(i+1)]=NManipulatorControlForm;

 TUComponentsListFrame::ComponentControllers["NSimpleEngineControlRangeAfferent"]=NManipulatorControlForm;
 for(int i=1;i<max_number_of_mc;i++)
  TUComponentsListFrame::ComponentControllers[std::string("NSimpleEngineControlRangeAfferent")+RDK::sntoa(i+1)]=NManipulatorControlForm;

 TUComponentsListFrame::ComponentControllers["NSimpleEngineControlSignumAfferent"]=NManipulatorControlForm;
 for(int i=1;i<max_number_of_mc;i++)
  TUComponentsListFrame::ComponentControllers[std::string("NSimpleEngineControlSignumAfferent")+RDK::sntoa(i+1)]=NManipulatorControlForm;

 TUComponentsListFrame::ComponentControllers["NEngineControlRangeAfferent"]=NManipulatorControlForm;
 for(int i=1;i<max_number_of_mc;i++)
  TUComponentsListFrame::ComponentControllers[std::string("NEngineControlRangeAfferent")+RDK::sntoa(i+1)]=NManipulatorControlForm;

 TUComponentsListFrame::ComponentControllers["NEngineControlSignumAfferent"]=NManipulatorControlForm;
 for(int i=1;i<max_number_of_mc;i++)
  TUComponentsListFrame::ComponentControllers[std::string("NEngineControlSignumAfferent")+RDK::sntoa(i+1)]=NManipulatorControlForm;

 TUComponentsListFrame::ComponentControllers["NEngineControlSignumAfferent"]=NManipulatorControlForm;
 for(int i=1;i<max_number_of_mc;i++)
  TUComponentsListFrame::ComponentControllers[std::string("NEngineControlSignumAfferent")+RDK::sntoa(i+1)]=NManipulatorControlForm;

}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::FormDestroy(TObject *Sender)
{
 if(TempBmp)
  delete TempBmp;
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::DrawGridDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State)
{
// if(int(Images.size())<=ACol || int(Images[ACol].size())<=ARow)
//  return;

 dynamic_cast<TDrawGrid *>(Sender)->Canvas->
		StretchDraw(Rect, TempBmp);
// if(ShowLegendCheckBox->Checked)
//  dynamic_cast<TDrawGrid *>(Sender)->Canvas->TextOut(Rect.Left,Rect.Top,(std::string(Model_GetComponentLongName(StringIds[ACol][ARow].c_str()))+std::string("[")+RDK::sntoa(ComponentIndexes[ACol][ARow])+"]").c_str());
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::ResetToZeroButton1Click(TObject *Sender)

{
 MovementControlTrackBar->Position=0;
 MovementControlTrackBarChange(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::ResetToZeroButton2Click(TObject *Sender)

{
 MomentTrackBar->Position=0;
 MomentTrackBarChange(Sender);
}
//---------------------------------------------------------------------------





void __fastcall TNManipulatorControlForm::SaveStatsButtonClick(TObject *Sender)
{
 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;

 RDK::UEPtr<NMSDK::NEngineMotionControl> ControlSystem=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(model->GetComponentL(ControlSystemName,true));
 if(!ControlSystem)
  return;

 RDK::UEPtr<RDK::UStatistic> stats=ControlSystem->GetComponentL<RDK::UStatistic>("StatisticDoubleMatrix",true);
 if(!stats)
  return;
 stats->ManualModeSwitch=true;
}
//---------------------------------------------------------------------------

void __fastcall TNManipulatorControlForm::NewStatsButtonClick(TObject *Sender)
{
 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;

 RDK::UEPtr<NMSDK::NEngineMotionControl> ControlSystem=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(model->GetComponentL(ControlSystemName,true));
 if(!ControlSystem)
  return;

 RDK::UEPtr<RDK::UStatistic> stats=ControlSystem->GetComponentL<RDK::UStatistic>("StatisticDoubleMatrix",true);
 if(!stats)
  return;
 stats->ManualModeSwitch=false;
 stats->ManualModeEnabled=true;
 stats->Reset();
}
//---------------------------------------------------------------------------

