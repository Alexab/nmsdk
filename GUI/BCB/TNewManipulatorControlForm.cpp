//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TNewManipulatorControlForm.h"
#include "UComponentsListFormUnit.h"
#include "TUBitmap.h"
//#include "UDrawEngineFormUnit.h"

/// Экзепляр класса приложения
extern RDK::UApplication RdkApplication;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TNewManipulatorControlForm *NewManipulatorControlForm;
//---------------------------------------------------------------------------
__fastcall TNewManipulatorControlForm::TNewManipulatorControlForm(TComponent* Owner)
	: TUVisualControllerForm(Owner)
{
 BmpGraphics.SetCanvas(&BmpCanvas);
 CanvasWidth=640;
 CanvasHeight=480;
 Length=100;
 X=CanvasWidth/2;
 Y=CanvasHeight/2;
 BmpGraphics.SetPenWidth(4);
 UpdateInterval = 100;
 // Константное смещение на постоянный угол при отображении
 ZeroAngle=0;

 ZeroMovement=0;

 Movement=0;
 TempBmp=0;
 Angle=0;
 UpdateControlLoopsFlag=false;
}

void TNewManipulatorControlForm::AUpdateInterface(void)
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

  if(Model_CheckLink((ControlSystemName+".Pac").c_str(),0,(ControlSystemName+".NManipulatorInput1").c_str(),0))
   ControlVoltageCheckBox->Checked=true;
  else
   ControlVoltageCheckBox->Checked=false;
 }


 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;

 RDK::UEPtr<NMSDK::NWPhysicalManipulator> Manipulator=RDK::dynamic_pointer_cast<NMSDK::NWPhysicalManipulator>(model->GetComponentL(ManipulatorName,true));
 RDK::UEPtr<NMSDK::NEngineMotionControl> ControlSystem=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(model->GetComponentL(ControlSystemName,true));

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



 ReadComponentData();
 BmpGraphics.SetPenWidth(4);
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

 BmpGraphics.SetPenWidth(2);
 BmpGraphics.SetPenColor(0x00555555);

 for(size_t i=0;i<PosAngles.size();i++)
 {
  BmpGraphics.Line(Movement+ZeroMovement+X,Y,Movement+ZeroMovement+X+Length*cos(ZeroAngle+PosAngles[i]),Y+Length*sin(ZeroAngle+PosAngles[i]));
  BmpGraphics.Line(Movement+ZeroMovement+X,Y,Movement+ZeroMovement+X+Length*cos(ZeroAngle+NegAngles[i]),Y+Length*sin(ZeroAngle+NegAngles[i]));
 }

 BmpGraphics.SetPenWidth(4);
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
  RDK::UEPtr<NMSDK::NPulseGenerator>IIPosAfferent=RDK::dynamic_pointer_cast<NMSDK::NPulseGenerator>(ControlSystem->GetComponentL("IIPosAfferentGenerator",true));
  RDK::UEPtr<NMSDK::NPulseGenerator>IINegAfferent=RDK::dynamic_pointer_cast<NMSDK::NPulseGenerator>(ControlSystem->GetComponentL("IINegAfferentGenerator",true));

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

  NumMotionElementsTrackBar->Position=ControlSystem->NumMotionElements;
  NumMotionElementsEdit->Text=IntToStr(NumMotionElementsTrackBar->Position);

  NumControlLoopsTrackBar->Position=ControlSystem->NumControlLoops;
  NumControlLoopsEdit->Text=IntToStr(NumControlLoopsTrackBar->Position);

  SensorDivisionComboBox->ItemIndex=ControlSystem->AfferentRangeMode;

  BranchModeCheckBox->Checked=ControlSystem->MotoneuronBranchMode;
  RenshowCellsCheckBox->Checked=ControlSystem->RenshowMode;
  if(*ControlSystem->MCAfferentObjectName == "NSimpleAfferentNeuron")
   UseSimpleAfferentsCheckBox->Checked=true;
  else
   UseSimpleAfferentsCheckBox->Checked=false;

  if(*ControlSystem->MCNeuroObjectName == "NNewSynSPNeuron")
   UseNewNeuronsCheckBox->Checked=true;
  else
   UseNewNeuronsCheckBox->Checked=false;


  std::string buffer;
  CurrentContourAmplitudeLabeledEdit->Text=ControlSystem->GetPropertyValue("CurrentContourAmplitude",buffer).c_str();
  CurrentContourAverageLabeledEdit->Text=ControlSystem->GetPropertyValue("CurrentContourAverage",buffer).c_str();
  TransientTimeLabeledEdit->Text=FloatToStrF(ControlSystem->CurrentTransientTime,ffFixed,3,3);
  CurrentTransientStateCheckBox->Checked=ControlSystem->CurrentTransientState;
  InstantAvgSpeedLabeledEdit->Text=FloatToStrF(ControlSystem->InstantAvgSpeed,ffFixed,3,3);

  if((*ControlSystem->UseContourData)[0] == true)
   EnableStructuralAdaptationCheckBox->Checked=true;
  else
   EnableStructuralAdaptationCheckBox->Checked=false;

  if(!TUVisualControllerFrame::CalculationModeFlag)
  {
   MaxAmpLabeledEdit->Text=FloatToStrF((*ControlSystem->DestContourMaxAmplitude)[0],ffFixed,3,3);
   MinAmpLabeledEdit->Text=FloatToStrF((*ControlSystem->DestContourMinAmplitude)[0],ffFixed,3,3);
  }

  if(EnableStructuralAdaptationCheckBox->Checked)
  {
   MaxAmpLabeledEdit->ReadOnly=true;
   MinAmpLabeledEdit->ReadOnly=true;
   MaxAmpLabeledEdit->Color=clBtnFace;
   MinAmpLabeledEdit->Color=clBtnFace;
  }
  else
  {
   MaxAmpLabeledEdit->ReadOnly=false;
   MinAmpLabeledEdit->ReadOnly=false;
   MaxAmpLabeledEdit->Color=clWindow;
   MinAmpLabeledEdit->Color=clWindow;
  }
 }
 IINumAfferentTrackBarChange(this);

 RDK::UEPtr<NMSDK::NDCEngine> engine=RDK::dynamic_pointer_cast<NMSDK::NDCEngine>(model->GetComponentL(ManipulatorName,true));
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

 if (ControlSystem)
 {
  int num_controls=ControlSystem->GetNumControlLoops();
  if(!CalculationModeFlag || UpdateControlLoopsFlag)
  {
   UpdateControlLoopsFlag=false;
   if(ControlSystem->ActiveContours->size() == num_controls)
   {
	if(CheckListBox1->Items->Count != num_controls)
	{
	 CheckListBox1->Items->Clear();
	  for (int i=0; i < num_controls; i++)
	  {
	   CheckListBox1->Items->Add("Afferent"+IntToStr(i+1));
	   CheckListBox1->Checked[i]=(*ControlSystem->ActiveContours)[i];
	  }
	}
	else
	{
	 for (int i=0; i < num_controls; i++)
	 {
	   CheckListBox1->Items->Strings[i]="Afferent"+IntToStr(i+1);
	   if(CheckListBox1->Checked[i] != (*ControlSystem->ActiveContours)[i])
		CheckListBox1->Checked[i]=(*ControlSystem->ActiveContours)[i];
	 }
	}
   }
  }
 }

}

// Возврат интерфейса в исходное состояние
void TNewManipulatorControlForm::AClearInterface(void)
{
 ManipulatorName.clear();

 ControlSystemName.clear();

// Manipulator=0;
// UniversalManipulator=0;

// Engine=0;
// Source=0;
// ControlSystem=0;

// IIPosAfferent=0; IINegAfferent=0;
// MN1PosControl=0; MN1NegControl=0;

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
TUVisualControllerForm* TNewManipulatorControlForm::New(TComponent *owner)
{
 return new TNewManipulatorControlForm(owner);
}


// Считывает данные всех пармаетров из сети и выставляет в соответствующие позиции элементы управления
void TNewManipulatorControlForm::LoadInterfaceInfoFromNet(void)
{
 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 RDK::UEPtr<NMSDK::NWPhysicalManipulator> Manipulator=RDK::dynamic_pointer_cast<NMSDK::NWPhysicalManipulator>(model->GetComponentL(ManipulatorName,true));
 RDK::UEPtr<NMSDK::NEngineMotionControl> ControlSystem=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(model->GetComponentL(ControlSystemName,true));
 if(!ControlSystem)
  return;

 int num_ranges=ControlSystem->NumMotionElements;
 bool flag=UpdateInterfaceFlag;
 RDK::UEPtr<NMSDK::NPac> engine_input=RDK::dynamic_pointer_cast<NMSDK::NPac>(ControlSystem->GetComponent("Pac"));
 if(!flag)
  UpdateInterfaceFlag=true;
 PACMultiplicatorTrackBar->Position=ControlSystem->PacGain;//fabs(engine_input->Gain[0][0]);
 PACDeactivatorTimeEdit->Text=FloatToStrF(engine_input->Gain[0][0],ffFixed,3,3);
 PACActivatorTimeTrackBar->Position=engine_input->SecretionTC[0][0]*double(PACActivatorTimeTrackBar->Max);
 PACActivatorTimeEdit->Text=FloatToStrF(engine_input->SecretionTC[0][0],ffFixed,3,3);
 PACDeactivatorTimeTrackBar->Position=engine_input->DissociationTC[0][0]*double(PACDeactivatorTimeTrackBar->Max);
 PACDeactivatorTimeEdit->Text=FloatToStrF(engine_input->DissociationTC[0][0],ffFixed,3,3);

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
void TNewManipulatorControlForm::ASaveParameters(RDK::USerStorageXML &xml)
{
 xml.SelectNodeForce("Control");
 xml.WriteString("ManipulatorName",ManipulatorName);
 xml.WriteString("ControlSystemName",ControlSystemName);
 xml.SelectUp();
}

// Загружает параметры интерфейса из xml
void TNewManipulatorControlForm::ALoadParameters(RDK::USerStorageXML &xml)
{
 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 ManipulatorName.clear();
 ControlSystemName.clear();

// Manipulator=0;
// UniversalManipulator=0;

// Engine=0;
// Source=0;
// ControlSystem=0;

// IIPosAfferent=0;
// IINegAfferent=0;
// MN1PosControl=0;
// MN1NegControl=0;

 ZeroAngle=0;

 ZeroMovement=0;

 Movement=0;


  xml.SelectNodeForce("Control");
 ManipulatorName=xml.ReadString("ManipulatorName","");
 RDK::UEPtr<NMSDK::UNet> UniversalManipulator;
 RDK::UEPtr<NMSDK::NWPhysicalManipulator> Manipulator;
 if(!ManipulatorName.empty())
 {
  UniversalManipulator=RDK::dynamic_pointer_cast<NMSDK::UNet>(model->GetComponentL(ManipulatorName,true));
  Manipulator=RDK::dynamic_pointer_cast<NMSDK::NWPhysicalManipulator>(model->GetComponentL(ManipulatorName,true));
 }
 if(!UniversalManipulator)
  ManipulatorName="";

 ControlSystemName=xml.ReadString("ControlSystemName","");
 RDK::UEPtr<NMSDK::NEngineMotionControl> ControlSystem;
 if(!ControlSystemName.empty())
  ControlSystem=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(model->GetComponentL(ControlSystemName,true));
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



bool TNewManipulatorControlForm::ManipulatorCSConnect(const std::string &cs_name, const std::string &man_name)
{
 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return false;
 RDK::UEPtr<RDK::UNet> net=RDK::dynamic_pointer_cast<RDK::UNet>(model);

 if(cs_name.empty())
  return true;

 bool res=true;
 std::string source_name=cs_name+".NManipulatorSource1";
// net->BreakConnectorLink(source_name,0);
// net->BreakConnectorLink(source_name,1);
// net->BreakConnectorLink(source_name,2);
// net->BreakConnectorLink(source_name,3);
// net->BreakConnectorLink(source_name,4);
 net->BreakAllOutgoingLinks(man_name);
 // RDK::dynamic_pointer_cast<RDK::UConnector>(net->GetComponentL(source_name))->DisconnectAllItems();
 RDK::dynamic_pointer_cast<RDK::UADItem>(net->GetComponentL(cs_name+".NManipulatorInput1",true))->DisconnectAll();

 res&=net->CreateLink(man_name,0,source_name,0);
 res&=net->CreateLink(man_name,1,source_name,1);
 res&=net->CreateLink(man_name,2,source_name,2);
 if(man_name == "PendulumAndCart")
 {
  res&=net->CreateLink(man_name,3,source_name,3);
  res&=net->CreateLink(man_name,4,source_name,4);
 }

 res&=net->CreateLink(cs_name+".NManipulatorInput1",0,man_name,0);

 RDK::UEPtr<NMSDK::NControlObjectSource> source=net->GetComponentL<NMSDK::NControlObjectSource>(source_name,true);
 if(source)
 {
  std::vector<int> indexes;
  std::vector<double> data_mul;
  std::vector<double> data_shift;
  if(man_name == "PendulumAndCart")
  {
   indexes.resize(5);
   indexes[0]=1;
   indexes[1]=2;
   indexes[2]=0;
   indexes[3]=3;
   indexes[4]=0;
   data_mul.assign(5,1.0);
   data_shift.assign(5,0.0);
  }
  else
  if(man_name == "DCEngine")
  {
   indexes.resize(3);
   indexes[0]=1;
   indexes[1]=2;
   indexes[2]=0;
   data_mul.assign(3,1.0);
   data_shift.assign(3,0.0);
  }

  source->DataIndexes=indexes;
  source->DataMul=data_mul;
  source->DataShift=data_shift;
 }

 ZeroAngle=+3.14/2;
 return res;
}


// Считывает данные из компонента
void TNewManipulatorControlForm::ReadComponentData(void)
{
 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 RDK::UEPtr<NMSDK::NEngineMotionControl> ControlSystem=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(model->GetComponentL(ControlSystemName,true));

 if(!ControlSystem)
  return;
 ReadComponentName=ManipulatorName;

 Angle=RDK::dynamic_pointer_cast<RDK::UADItem>(model->GetComponentL(ReadComponentName))->GetOutputData(1).Double[0];

 if(RDK::dynamic_pointer_cast<RDK::UADItem>(model->GetComponentL(ReadComponentName))->GetNumOutputs()>3)
 {
  Movement=RDK::dynamic_pointer_cast<RDK::UADItem>(model->GetComponentL(ReadComponentName))->GetOutputData(3).Double[0];
  Movement*=100; // в 1 метре 10 пикселей
 }


 PosAngles.assign(ControlSystem->NumMotionElements,0.0);
 NegAngles.assign(ControlSystem->NumMotionElements,0.0);
 for(int i=0;i<ControlSystem->NumMotionElements;i++)
 {
  RDK::UEPtr<NMSDK::NIntervalSeparator> pos_sep=ControlSystem->GetComponentL<NMSDK::NIntervalSeparator>(std::string("PosIntervalSeparator")+RDK::sntoa(i+1)+"1",true);
  RDK::UEPtr<NMSDK::NIntervalSeparator> neg_sep=ControlSystem->GetComponentL<NMSDK::NIntervalSeparator>(std::string("NegIntervalSeparator")+RDK::sntoa(i+1)+"1",true);

  if(pos_sep)
  {
   PosAngles[i]=(*pos_sep->MaxRange)[0];
  }

  if(neg_sep)
  {
   NegAngles[i]=(*neg_sep->MinRange)[0];
  }
 }
}

void TNewManipulatorControlForm::ReconnectCurrentManipulator(void)
{
 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 RDK::UEPtr<NMSDK::NWPhysicalManipulator> Manipulator;
 RDK::UEPtr<NMSDK::UNet> UniversalManipulator;
 if(Manipulator)
 {
  Disconnect1Click(this);
//  ManipulatorName="";
 }

// ManipulatorName=UComponentsListForm->ComponentsListFrame1->GetSelectedComponentLongName();
 UniversalManipulator=RDK::dynamic_pointer_cast<RDK::UNet>(model->GetComponentL(ManipulatorName,true));
 Manipulator=RDK::dynamic_pointer_cast<NMSDK::NWPhysicalManipulator>(model->GetComponentL(ManipulatorName,true));
 if(!UniversalManipulator)
  ManipulatorName="";
 ManipulatorCSConnect(ControlSystemName, ManipulatorName);
}

void TNewManipulatorControlForm::ReconnectManipulator(void)
{
 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 RDK::UEPtr<NMSDK::NWPhysicalManipulator> Manipulator;
 RDK::UEPtr<NMSDK::UNet> UniversalManipulator;
 if(Manipulator)
 {
  Disconnect1Click(this);
  ManipulatorName="";
 }

 ManipulatorName=UComponentsListForm->ComponentsListFrame1->GetSelectedComponentLongName();
 UniversalManipulator=RDK::dynamic_pointer_cast<RDK::UNet>(model->GetComponentL(ManipulatorName,true));
 Manipulator=RDK::dynamic_pointer_cast<NMSDK::NWPhysicalManipulator>(model->GetComponentL(ManipulatorName,true));
 if(!UniversalManipulator)
  ManipulatorName="";
 ManipulatorCSConnect(ControlSystemName, ManipulatorName);
}
//---------------------------------------------------------------------------
void __fastcall TNewManipulatorControlForm::Disconnect1Click(TObject *Sender)
{
 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 RDK::UEPtr<NMSDK::NWPhysicalManipulator> Manipulator;
 RDK::UEPtr<NMSDK::UNet> UniversalManipulator;
 Manipulator=RDK::dynamic_pointer_cast<NMSDK::NWPhysicalManipulator>(model->GetComponentL(ManipulatorName,true));
 if(!Manipulator)
  return;

 Manipulator->UnInitManipulator();
 Manipulator->UnLoadManipulatorDll();
 UpdateInterface();
}
//---------------------------------------------------------------------------
void __fastcall TNewManipulatorControlForm::MoveLeft1Click(TObject *Sender)
{
 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 RDK::UEPtr<NMSDK::NWPhysicalManipulator> Manipulator;
 RDK::UEPtr<NMSDK::UNet> UniversalManipulator;
 Manipulator=RDK::dynamic_pointer_cast<NMSDK::NWPhysicalManipulator>(model->GetComponentL(ManipulatorName,true));
 if(!Manipulator || !Manipulator->DMMoveServo)
  return;

 Manipulator->DMMoveServo(1,1,255,50);
}
//---------------------------------------------------------------------------
void __fastcall TNewManipulatorControlForm::MoveRight1Click(TObject *Sender)
{
 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 RDK::UEPtr<NMSDK::NWPhysicalManipulator> Manipulator;
 RDK::UEPtr<NMSDK::UNet> UniversalManipulator;
 Manipulator=RDK::dynamic_pointer_cast<NMSDK::NWPhysicalManipulator>(model->GetComponentL(ManipulatorName,true));
 if(!Manipulator || !Manipulator->DMMoveServo)
  return;

 Manipulator->DMMoveServo(1,2,255,50);
}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::SelectManipulator1Click(TObject *Sender)
{
 if(UComponentsListForm->ShowComponentSelect() != mrOk)
  return;

 ReconnectManipulator();
 UpdateInterface();
}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::Connect1Click(TObject *Sender)
{
 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 RDK::UEPtr<NMSDK::NWPhysicalManipulator> Manipulator;
 RDK::UEPtr<NMSDK::UNet> UniversalManipulator;
 Manipulator=RDK::dynamic_pointer_cast<NMSDK::NWPhysicalManipulator>(model->GetComponentL(ManipulatorName,true));
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

void __fastcall TNewManipulatorControlForm::DeviceModeRadioButtonClick(TObject *Sender)
{
 ComPortComboBox->Enabled=true;
 EmulatorModeRadioButton->Checked=false;
 ControlModeComboBox->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::EmulatorModeRadioButtonClick(TObject *Sender)

{
 ComPortComboBox->Enabled=false;
 DeviceModeRadioButton->Checked=false;
 ControlModeComboBox->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::FormShow(TObject *Sender)
{
 UpdateInterface();
}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::ComponentSelectionPanelDblClick(TObject *Sender)
{
 SelectManipulator1Click(Sender);
// UDrawEngineForm->ReloadNet();
}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::ConnectButtonClick(TObject *Sender)
{
 Connect1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::DisconnectButtonClick(TObject *Sender)
{
 Disconnect1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::Reset1Click(TObject *Sender)
{
 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 RDK::UEPtr<NMSDK::NWPhysicalManipulator> Manipulator;
 RDK::UEPtr<NMSDK::UNet> UniversalManipulator;
 Manipulator=RDK::dynamic_pointer_cast<NMSDK::NWPhysicalManipulator>(model->GetComponentL(ManipulatorName,true));
 if(!Manipulator || !Manipulator->DMReset)
  return;

 Manipulator->DMReset();
 UpdateInterface();
}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::ResetButtonClick(TObject *Sender)
{
 Reset1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::StartButtonClick(TObject *Sender)
{
 Start1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::StopButtonClick(TObject *Sender)
{
 Stop1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::Start1Click(TObject *Sender)
{
 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 RDK::UEPtr<NMSDK::NWPhysicalManipulator> Manipulator;
 RDK::UEPtr<NMSDK::UNet> UniversalManipulator;
 Manipulator=RDK::dynamic_pointer_cast<NMSDK::NWPhysicalManipulator>(model->GetComponentL(ManipulatorName,true));
 if(!Manipulator || !Manipulator->DMStart)
  return;

 Manipulator->DMStart();
 UpdateInterface();
}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::Stop1Click(TObject *Sender)
{
 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 RDK::UEPtr<NMSDK::NWPhysicalManipulator> Manipulator;
 RDK::UEPtr<NMSDK::UNet> UniversalManipulator;
 Manipulator=RDK::dynamic_pointer_cast<NMSDK::NWPhysicalManipulator>(model->GetComponentL(ManipulatorName,true));
 if(!Manipulator || !Manipulator->DMStop)
  return;

 Manipulator->DMStop();
 UpdateInterface();
}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::Button2Click(TObject *Sender)
{
 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 RDK::UEPtr<NMSDK::NWPhysicalManipulator> Manipulator;
 RDK::UEPtr<NMSDK::UNet> UniversalManipulator;
 Manipulator=RDK::dynamic_pointer_cast<NMSDK::NWPhysicalManipulator>(model->GetComponentL(ManipulatorName,true));
 if(!Manipulator || !Manipulator->DMMoveServo)
  return;

 Manipulator->DMMoveServo(CBoxServoMove->ItemIndex, ComboBoxDir->ItemIndex+1, TrackBarPWM->Position, TrackBarTime->Position);
}
//---------------------------------------------------------------------------


void __fastcall TNewManipulatorControlForm::FormClose(TObject *Sender, TCloseAction &Action)

{
 Disconnect1Click(Sender);
 Sleep(100);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::IIAfferentTrackBarChange(TObject *Sender)

{
 if(UpdateInterfaceFlag)
  return;

 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 RDK::UEPtr<NMSDK::NWPhysicalManipulator> Manipulator;
 RDK::UEPtr<NMSDK::UNet> UniversalManipulator;
 RDK::UEPtr<NMSDK::NEngineMotionControl> ControlSystem;
 Manipulator=RDK::dynamic_pointer_cast<NMSDK::NWPhysicalManipulator>(model->GetComponentL(ManipulatorName,true));
 ControlSystem=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(model->GetComponentL(ControlSystemName,true));
 if(!ControlSystem)
  return;

 RDK::UEPtr<NMSDK::NPulseGenerator> IIPosAfferent=RDK::dynamic_pointer_cast<NMSDK::NPulseGenerator>(ControlSystem->GetComponentL("IIPosAfferentGenerator",true));
 RDK::UEPtr<NMSDK::NPulseGenerator> IINegAfferent=RDK::dynamic_pointer_cast<NMSDK::NPulseGenerator>(ControlSystem->GetComponentL("IINegAfferentGenerator",true));


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

 if(IIAfferentTrackBar->Position<0)
  ControlSystem->SetInternalGeneratorFrequency(0,IINumAfferentTrackBar->Position,0, -IIAfferentTrackBar->Position);
 else
  ControlSystem->SetInternalGeneratorFrequency(1,IINumAfferentTrackBar->Position,0, IIAfferentTrackBar->Position);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::ControlVoltageCheckBoxClick(TObject *Sender)

{
 if(UpdateInterfaceFlag)
  return;

 bool res=true;

 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 RDK::UEPtr<NMSDK::NWPhysicalManipulator> Manipulator;
 RDK::UEPtr<NMSDK::UNet> UniversalManipulator;
 RDK::UEPtr<NMSDK::NEngineMotionControl> ControlSystem;
 Manipulator=RDK::dynamic_pointer_cast<NMSDK::NWPhysicalManipulator>(model->GetComponentL(ManipulatorName,true));
 ControlSystem=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(model->GetComponentL(ControlSystemName,true));
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

void __fastcall TNewManipulatorControlForm::SelectControlSystem1Click(TObject *Sender)
{
 if(UComponentsListForm->ShowComponentSelect() != mrOk)
  return;

 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 ControlSystemName=UComponentsListForm->ComponentsListFrame1->GetSelectedComponentLongName();

 RDK::UEPtr<NMSDK::NEngineMotionControl> ControlSystem;

 ControlSystem=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(model->GetComponentL(ControlSystemName,true));
 if(!ControlSystem)
  ControlSystemName="";

 UpdateInterface();
}
//---------------------------------------------------------------------------


void __fastcall TNewManipulatorControlForm::ControlSystemSelectionPanelDblClick(TObject *Sender)
{
 SelectControlSystem1Click(Sender);
 ReconnectCurrentManipulator();
// UDrawEngineForm->UpdateInterface();
}
//---------------------------------------------------------------------------




void __fastcall TNewManipulatorControlForm::VoltageMulTrackBarChange(TObject *Sender)

{
 double value=VoltageMulTrackBar->Position/100.0;
 VoltageMulEdit->Text=FloatToStrF(value,ffFixed,3,3);

 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 RDK::UEPtr<NMSDK::NWPhysicalManipulator> Manipulator;
 RDK::UEPtr<NMSDK::UNet> UniversalManipulator;
 RDK::UEPtr<NMSDK::NEngineMotionControl> ControlSystem;
 Manipulator=RDK::dynamic_pointer_cast<NMSDK::NWPhysicalManipulator>(model->GetComponentL(ManipulatorName,true));
 ControlSystem=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(model->GetComponentL(ControlSystemName,true));
 if(!Manipulator)
  return;

 Manipulator->OutputMul=value;
}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::TimeDurationTrackBarChange(TObject *Sender)

{
 double value=TimeDurationTrackBar->Position;
 TimeDurationEdit->Text=FloatToStrF(value,ffFixed,3,3);

 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 RDK::UEPtr<NMSDK::NWPhysicalManipulator> Manipulator;
 RDK::UEPtr<NMSDK::UNet> UniversalManipulator;
 RDK::UEPtr<NMSDK::NEngineMotionControl> ControlSystem;
 Manipulator=RDK::dynamic_pointer_cast<NMSDK::NWPhysicalManipulator>(model->GetComponentL(ManipulatorName,true));
 ControlSystem=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(model->GetComponentL(ControlSystemName,true));
 if(!Manipulator)
  return;

 Manipulator->TimeDuration=value;
}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::PACDeactivatorTimeTrackBarChange(TObject *Sender)
{
 if(UpdateInterfaceFlag)
  return;
 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 RDK::UEPtr<NMSDK::NEngineMotionControl> ControlSystem;
 ControlSystem=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(model->GetComponentL(ControlSystemName,true));
 if(!ControlSystem)
  return;
 int num_ranges=ControlSystem->NumMotionElements;
 double value=double(PACDeactivatorTimeTrackBar->Position)/double(PACDeactivatorTimeTrackBar->Max);
 PACDeactivatorTimeEdit->Text=FloatToStrF(value,ffFixed,3,3);
 ControlSystem->PacDissociationTC=value;
/*
 RDK::UEPtr<NMSDK::NPac> engine_input=RDK::dynamic_pointer_cast<NMSDK::NPac>(ControlSystem->GetComponent("Pac"));
 if(engine_input)
 {
  std::vector<NMSDK::Real> values;

  values.resize(num_ranges*2);
  // Постоянная времени распада медиатора
  for(size_t i=0;i<values.size();i++)
   values[i].assign(1,value);
  engine_input->DissociationTC=values;
 }*/
}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::PACActivatorTimeTrackBarChange(TObject *Sender)

{
 if(UpdateInterfaceFlag)
  return;
 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 RDK::UEPtr<NMSDK::NEngineMotionControl> ControlSystem;
 ControlSystem=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(model->GetComponentL(ControlSystemName,true));
 if(!ControlSystem)
  return;
 double value=double(PACActivatorTimeTrackBar->Position)/double(PACActivatorTimeTrackBar->Max);
 PACActivatorTimeEdit->Text=FloatToStrF(value,ffFixed,3,3);

 ControlSystem->PacSecretionTC=value;

/*
 RDK::UEPtr<NMSDK::NPac> engine_input=RDK::dynamic_pointer_cast<NMSDK::NPac>(ControlSystem->GetComponent("Pac"));
 if(engine_input)
 {
  std::vector<NMSDK::Real> values;

  values.resize(num_ranges*2);
  // Постоянная времени распада медиатора
  for(size_t i=0;i<values.size();i++)
   values[i].assign(1,value);
  engine_input->SecretionTC=values;
 }*/
}
//---------------------------------------------------------------------------


void __fastcall TNewManipulatorControlForm::SendVButtonClick(TObject *Sender)
{
 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 RDK::UEPtr<NMSDK::NWPhysicalManipulator> Manipulator;
// RDK::UEPtr<NMSDK::UNet> UniversalManipulator;
 RDK::UEPtr<NMSDK::NEngineMotionControl> ControlSystem;
 Manipulator=RDK::dynamic_pointer_cast<NMSDK::NWPhysicalManipulator>(model->GetComponentL(ManipulatorName,true));
 ControlSystem=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(model->GetComponentL(ControlSystemName,true));
 if(!Manipulator)
  return;

 if(!ControlSystem)
  return;

 int num_ranges=ControlSystem->NumMotionElements;
 Manipulator->SetAccumulationStep(StrToInt(VaEdit->Text)/num_ranges);
 Manipulator->SetDissociationStep(StrToInt(VdEdit->Text));
}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::PACMultiplicatorTrackBarChange(TObject *Sender)
{
 if(UpdateInterfaceFlag)
  return;
 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 RDK::UEPtr<NMSDK::NEngineMotionControl> ControlSystem;
 ControlSystem=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(model->GetComponentL(ControlSystemName,true));
 if(!ControlSystem)
  return;
 double value=double(PACMultiplicatorTrackBar->Position);
 PACMultiplicatorEdit->Text=FloatToStrF(value,ffFixed,3,3);
 ControlSystem->PacGain=value;
/*
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
  */
}
//---------------------------------------------------------------------------


void __fastcall TNewManipulatorControlForm::MomentTrackBarChange(TObject *Sender)
{
 if(UpdateInterfaceFlag)
  return;

 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 RDK::UEPtr<NMSDK::NWPhysicalManipulator> Manipulator;
 RDK::UEPtr<NMSDK::UNet> UniversalManipulator;
 RDK::UEPtr<NMSDK::NEngineMotionControl> ControlSystem;
 Manipulator=RDK::dynamic_pointer_cast<NMSDK::NWPhysicalManipulator>(model->GetComponentL(ManipulatorName,true));
 ControlSystem=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(model->GetComponentL(ControlSystemName,true));
 UniversalManipulator=RDK::dynamic_pointer_cast<NMSDK::UNet>(model->GetComponentL(ManipulatorName,true));
 if(!ControlSystem)
  return;

 RDK::UEPtr<NMSDK::NManipulatorSource> source=RDK::dynamic_pointer_cast<NMSDK::NManipulatorSource>(ControlSystem->GetComponentL("NManipulatorSource1",true));
 RDK::UEPtr<NMSDK::NControlObjectSource> source1=RDK::dynamic_pointer_cast<NMSDK::NControlObjectSource>(ControlSystem->GetComponentL("NManipulatorSource1",true));
 RDK::UEPtr<NMSDK::NDCEngine> engine=RDK::dynamic_pointer_cast<NMSDK::NDCEngine>(UniversalManipulator);
 RDK::UEPtr<NMSDK::NPendulumAndCart> engine2=RDK::dynamic_pointer_cast<NMSDK::NPendulumAndCart>(UniversalManipulator);
 double amplitude=double(MomentTrackBar->Position)/double(MomentTrackBar->Max/2.0);
 ExtMomentEdit->Text=FloatToStrF(amplitude,ffFixed,3,3);
 if(engine && source)
 {
  source->Angle=amplitude;
 }
 if(engine && source1)
 {
  (*source1->DataShift)[0]=amplitude;
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


//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::MovementControlTrackBarChange(TObject *Sender)

{
 if(UpdateInterfaceFlag)
  return;

 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 RDK::UEPtr<NMSDK::NWPhysicalManipulator> Manipulator;
 RDK::UEPtr<NMSDK::UNet> UniversalManipulator;
 RDK::UEPtr<NMSDK::NEngineMotionControl> ControlSystem;
 UniversalManipulator=RDK::dynamic_pointer_cast<NMSDK::UNet>(model->GetComponentL(ManipulatorName,true));
 Manipulator=RDK::dynamic_pointer_cast<NMSDK::NWPhysicalManipulator>(model->GetComponentL(ManipulatorName,true));
 ControlSystem=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(model->GetComponentL(ControlSystemName,true));
 if(!ControlSystem)
  return;

// RDK::UEPtr<NMSDK::NManipulatorSource> source=RDK::dynamic_pointer_cast<NMSDK::NManipulatorSource>(ControlSystem->GetComponentL("NManipulatorSource1"));
// RDK::UEPtr<NMSDK::NControlObjectSource> source1=RDK::dynamic_pointer_cast<NMSDK::NControlObject>(ControlSystem->GetComponentL("NManipulatorSource1"));
 double amplitude=double(MovementControlTrackBar->Position)/double(MovementControlTrackBar->Max/2.0);
 MovementControlEdit->Text=FloatToStrF(amplitude,ffFixed,3,3);

 RDK::UEPtr<NMSDK::NDCEngine> engine=RDK::dynamic_pointer_cast<NMSDK::NDCEngine>(UniversalManipulator);
 RDK::UEPtr<NMSDK::NPendulumAndCart> engine2=RDK::dynamic_pointer_cast<NMSDK::NPendulumAndCart>(UniversalManipulator);
 RDK::UEPtr<NMSDK::NWPhysicalManipulator> man=RDK::dynamic_pointer_cast<NMSDK::NWPhysicalManipulator>(UniversalManipulator);

  if(engine)
  {
   engine->OutMoment=amplitude;
  }

  if(engine2)
  {
   engine2->ExtrenalMoment=amplitude;
  }

 if(MovementControlTrackBar->Position>0)
  MovementControlProgressBar->Position=MovementControlTrackBar->Position;
 else
  MovementControlProgressBar->Position=-MovementControlTrackBar->Position;
}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::HideSecondaryGuiCheckBoxClick(TObject *Sender)

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

void __fastcall TNewManipulatorControlForm::FormCreate(TObject *Sender)
{
 TempBmp=new TBitmap;
 int max_number_of_mc=10;

 TUComponentsListFrame::ComponentControllers["N2AsfNewSimplestAfferentBranchedEngineControl"]=NewManipulatorControlForm;
 TUComponentsListFrame::ComponentControllers["N2AsfSimplestAfferentBranchedEngineControl"]=NewManipulatorControlForm;

}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::FormDestroy(TObject *Sender)
{
 if(TempBmp)
  delete TempBmp;
}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::DrawGridDrawCell(TObject *Sender, int ACol,
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

void __fastcall TNewManipulatorControlForm::ResetToZeroButton1Click(TObject *Sender)

{
 MovementControlTrackBar->Position=0;
 MovementControlTrackBarChange(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::ResetToZeroButton2Click(TObject *Sender)

{
 MomentTrackBar->Position=0;
 MomentTrackBarChange(Sender);
}
//---------------------------------------------------------------------------






void __fastcall TNewManipulatorControlForm::CheckListBox1Click(TObject *Sender)
{
 if(UpdateInterfaceFlag)
  return;

 bool res=true;

 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 RDK::UEPtr<NMSDK::NWPhysicalManipulator> Manipulator;
 RDK::UEPtr<NMSDK::UNet> UniversalManipulator;
 RDK::UEPtr<NMSDK::NEngineMotionControl> ControlSystem;
 Manipulator=RDK::dynamic_pointer_cast<NMSDK::NWPhysicalManipulator>(model->GetComponentL(ManipulatorName,true));
 ControlSystem=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(model->GetComponentL(ControlSystemName,true));
 if(!ControlSystem)
  return;

 std::vector<bool> act_cont;
 act_cont.resize(CheckListBox1->Count);
 for(int i=0;i<CheckListBox1->Count;i++)
  act_cont[i]=CheckListBox1->Checked[i];

 ControlSystem->ActiveContours=act_cont;
}
//---------------------------------------------------------------------------





void __fastcall TNewManipulatorControlForm::ManipDrawButtonClick(TObject *Sender)

{
 NDrawManipulatorForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::SaveStatsButtonClick(TObject *Sender)

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

void __fastcall TNewManipulatorControlForm::NewStatsButtonClick(TObject *Sender)
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


void __fastcall TNewManipulatorControlForm::NumMotionElementsTrackBarChange(TObject *Sender)

{
 if(UpdateInterfaceFlag)
  return;

 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;

 RDK::UEPtr<NMSDK::NEngineMotionControl> ControlSystem=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(model->GetComponentL(ControlSystemName,true));
 if(!ControlSystem)
  return;

 ControlSystem->NumMotionElements=NumMotionElementsTrackBar->Position;
 NumMotionElementsEdit->Text=IntToStr(NumMotionElementsTrackBar->Position);
 UpdateInterface();
}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::IINumAfferentTrackBarChange(TObject *Sender)
{
 if(UpdateInterfaceFlag)
  return;

 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 RDK::UEPtr<NMSDK::NEngineMotionControl> ControlSystem;
 ControlSystem=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(model->GetComponentL(ControlSystemName,true));
 if(!ControlSystem)
  return;

 if(IIAfferentTrackBar->Position<0)
  ControlSystem->ConnectInternalGenerators(0,IINumAfferentTrackBar->Position,0);
 else
  ControlSystem->ConnectInternalGenerators(1,IINumAfferentTrackBar->Position,0);
 IINumAfferentEdit->Text=IntToStr(IINumAfferentTrackBar->Position);
 IIAfferentTrackBarChange(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::BranchModeCheckBoxClick(TObject *Sender)

{
 if(UpdateInterfaceFlag)
  return;

 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 RDK::UEPtr<NMSDK::NEngineMotionControl> ControlSystem;
 ControlSystem=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(model->GetComponentL(ControlSystemName,true));
 if(!ControlSystem)
  return;

 if(BranchModeCheckBox->Checked)
  ControlSystem->MotoneuronBranchMode=1;
 else
  ControlSystem->MotoneuronBranchMode=0;

 ControlSystem->Reset();
 UpdateInterface();
}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::RenshowCellsCheckBoxClick(TObject *Sender)

{
 if(UpdateInterfaceFlag)
  return;

 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 RDK::UEPtr<NMSDK::NEngineMotionControl> ControlSystem;
 ControlSystem=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(model->GetComponentL(ControlSystemName,true));
 if(!ControlSystem)
  return;

 if(RenshowCellsCheckBox->Checked)
  ControlSystem->RenshowMode=1;
 else
  ControlSystem->RenshowMode=0;

 ControlSystem->Reset();
 UpdateInterface();
}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::UseSimpleAfferentsCheckBoxClick(TObject *Sender)

{
 if(UpdateInterfaceFlag)
  return;

 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 RDK::UEPtr<NMSDK::NEngineMotionControl> ControlSystem;
 ControlSystem=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(model->GetComponentL(ControlSystemName,true));
 if(!ControlSystem)
  return;

 if(UseSimpleAfferentsCheckBox->Checked)
  ControlSystem->MCAfferentObjectName= "NSimpleAfferentNeuron";
 else
  ControlSystem->MCAfferentObjectName= "NSAfferentNeuron";

 ControlSystem->Reset();
 UpdateInterface();
}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::UseNewNeuronsCheckBoxClick(TObject *Sender)

{
 if(UpdateInterfaceFlag)
  return;

 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 RDK::UEPtr<NMSDK::NEngineMotionControl> ControlSystem;
 ControlSystem=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(model->GetComponentL(ControlSystemName,true));
 if(!ControlSystem)
  return;

 if(UseNewNeuronsCheckBox->Checked)
  ControlSystem->MCNeuroObjectName= "NNewSynSPNeuron";
 else
  ControlSystem->MCNeuroObjectName= "NSynSPNeuron";

 ControlSystem->Reset();
 UpdateInterface();
}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::EnableStructuralAdaptationCheckBoxClick(TObject *Sender)

{
 if(UpdateInterfaceFlag)
  return;

 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;
 RDK::UEPtr<NMSDK::NEngineMotionControl> ControlSystem;
 ControlSystem=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(model->GetComponentL(ControlSystemName,true));
 if(!ControlSystem)
  return;


 if(EnableStructuralAdaptationCheckBox->Checked)
 {
  try
  {
   (*ControlSystem->DestContourMaxAmplitude)[0]=StrToFloat(MaxAmpLabeledEdit->Text);
   (*ControlSystem->DestContourMinAmplitude)[0]=StrToFloat(MinAmpLabeledEdit->Text);
  }
  catch(EConvertError &ex)
  {

  }
  (*ControlSystem->UseContourData)[0]=true;
 }
 else
  (*ControlSystem->UseContourData)[0]=false;

 UpdateInterface();
}
//---------------------------------------------------------------------------

void __fastcall TNewManipulatorControlForm::NumControlLoopsTrackBarChange(TObject *Sender)

{
 if(UpdateInterfaceFlag)
  return;

 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;

 RDK::UEPtr<NMSDK::NEngineMotionControl> ControlSystem=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(model->GetComponentL(ControlSystemName,true));
 if(!ControlSystem)
  return;

 ControlSystem->NumControlLoops=NumControlLoopsTrackBar->Position;
 NumControlLoopsEdit->Text=IntToStr(NumControlLoopsTrackBar->Position);
 UpdateControlLoopsFlag=true;
 UpdateInterface();

}
//---------------------------------------------------------------------------


void __fastcall TNewManipulatorControlForm::SensorDivisionComboBoxChange(TObject *Sender)

{
 if(UpdateInterfaceFlag)
  return;

 RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
 if(!model)
  return;

 RDK::UEPtr<NMSDK::NEngineMotionControl> ControlSystem=RDK::dynamic_pointer_cast<NMSDK::NEngineMotionControl>(model->GetComponentL(ControlSystemName,true));
 if(!ControlSystem)
  return;
 ControlSystem->AfferentRangeMode=SensorDivisionComboBox->ItemIndex;
 UpdateInterface();
}
//---------------------------------------------------------------------------

