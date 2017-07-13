//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ManipulatorTestUnit.h"
#include "MuscleControlFormUnit.h"
#include "SourcesControlFormUnit.h"
#include "MainFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Chart"
#pragma link "Series"
#pragma link "TeEngine"
#pragma link "TeeProcs"
#pragma resource "*.dfm"
TManipulatorTestForm *ManipulatorTestForm;
//---------------------------------------------------------------------------
__fastcall TManipulatorTestForm::TManipulatorTestForm(TComponent* Owner)
	: TForm(Owner),graph(&canvas)
{
 Engine=0;
 Source=0;
 ControlSystem=0;
 IIPosAfferent=IINegAfferent=0;

 MN1PosControl=MN1NegControl=0;


 canvas.SetRes(640,480);

 graph.SetPenWidth(5);
 graph.SetPenColor(UColorT(0x00FF0000));
 length=100;
}
//---------------------------------------------------------------------------
void TManipulatorTestForm::WriteArrow(UAGraphics &graph, int x,int y,int width,int direction)
{
 graph.Line(x,y,width,y);
 if(direction >= 0)
  graph.Triangle(width-5,y-5,width+5,y,width-5,y+5);
 else
  graph.Triangle(x+5,y-5,x-5,y,x+5,y+5);
}

void TManipulatorTestForm::UpdateInterface(void)
{
 canvas.Fill(0xFFFFFFFF);

 if(!Engine)
  return;

 double angle=Engine->GetOutputData(1).Double[0];
 double x1,y1,x2,y2;

 x1=320; y1=240;
 x2=x1+length*cos(angle-M_PI/2.0);
 y2=y1+length*sin(angle-M_PI/2.0);
 graph.SetPenColor(UColorT(0x00AA00FF));
 graph.SetPenPos(x1,y1);
 graph.LineTo(x2,y2);
 graph.Circle(x1,y1,10,true);

 UpdateIOInformation();

 canvas>>Image->Picture->Bitmap;
 Image->Repaint();

 IINumAfferentTrackBar->Max=MainForm->NumMotionElementsComboBox->ItemIndex+1;
}


// Update IO information
void TManipulatorTestForm::UpdateIOInformation(void)
{
 for(int i=0;i<IOChart->SeriesCount();i++)
  IOChart->Series[i]->Clear();

 IOChart->LeftAxis->Minimum=-MainForm->NumMotionElements;
 IOChart->LeftAxis->Maximum=MainForm->NumMotionElements;

 int angle=0,speed=0,moment=0;
 int sep_angle=0,sep_speed=0,sep_moment=0;
 // Receptors
 for(int i=0;i<MainForm->NumMotionElements;i++)
 {
  if(MainForm->receptor[i][0]->GetInputData(size_t(0))->Double[0] > 0)
   ++speed;
  if(MainForm->receptor[i][1]->GetInputData(size_t(0))->Double[0] > 0)
   --speed;

  if(MainForm->receptor[i][2]->GetInputData(size_t(0))->Double[0] > 0)
   ++moment;
  if(MainForm->receptor[i][3]->GetInputData(size_t(0))->Double[0] > 0)
   --moment;

  if(MainForm->receptor[i][4]->GetInputData(size_t(0))->Double[0] > 0)
   ++angle;
  if(MainForm->receptor[i][5]->GetInputData(size_t(0))->Double[0] > 0)
   --angle;
 }

 IOChart->Series[0]->AddXY(0,angle);
 IOChart->Series[1]->AddXY(0,speed);
 IOChart->Series[2]->AddXY(0,moment);

 // Separators
 for(int i=0;i<MainForm->NumMotionElements;i++)
 {
  sep_speed+=MainForm->Separators[i][0]->GetInputData(size_t(0))->Double[0];
  sep_speed+=MainForm->Separators[i][1]->GetInputData(size_t(0))->Double[0];
  sep_moment+=MainForm->Separators[i][2]->GetInputData(size_t(0))->Double[0];
  sep_moment+=MainForm->Separators[i][3]->GetInputData(size_t(0))->Double[0];

  sep_angle+=MainForm->Separators[i][4]->GetInputData(size_t(0))->Double[0];
  sep_angle+=MainForm->Separators[i][5]->GetInputData(size_t(0))->Double[0];
 }

 IOChart->Series[3]->AddXY(0,sep_angle);
 IOChart->Series[4]->AddXY(0,sep_speed);
 IOChart->Series[5]->AddXY(0,sep_moment);


 int y=470;
 int width=100;
 int cs_dir, man_dir;

// cs_dis=1;
// man_dir=0;

 graph.SetPenColor(UColorT(0x000000FF));
 WriteArrow(graph,10,y,width,angle);
 y-=20;
 WriteArrow(graph,10,y,width,sep_angle);
 y-=40;

 graph.SetPenColor(UColorT(0x0000FF00));
 WriteArrow(graph,10,y,width,speed);
 y-=20;
 WriteArrow(graph,10,y,width,sep_speed);
 y-=40;

 graph.SetPenColor(UColorT(0x00FF0000));
 WriteArrow(graph,10,y,width,moment);
 y-=20;
 WriteArrow(graph,10,y,width,sep_moment);
 y-=40;


 y=470;
 graph.SetPenColor(UColorT(0x00000000));
 WriteArrow(graph,620,y,width,Engine->GetOutputData(0).Double[0]);
 y-=20;
 WriteArrow(graph,620,y,width,Engine->GetInputData(unsigned(0))->Double[0]);
 y-=40;

}

//---------------------------------------------------------------------------
void __fastcall TManipulatorTestForm::FormShow(TObject *Sender)
{
 DoubleBuffered=true;
}
//---------------------------------------------------------------------------
void __fastcall TManipulatorTestForm::MomentTrackBarChange(TObject *Sender)
{
 if(Engine && ControlSystem)
 {
  UEPtr<NConstGenerator> generator=dynamic_pointer_cast<NConstGenerator>(ControlSystem->GetComponent("EngineMoment"));
  generator->Amplitude=double(MomentTrackBar->Position)/double(MomentTrackBar->Max/2.0);
  //  Engine->OutMoment=double(MomentTrackBar->Position)/double(MomentTrackBar->Max/2.0);
//  ExtMomentEdit->Text=FloatToStrF(Engine->OutMoment,ffFixed,3,3);
  ExtMomentEdit->Text=FloatToStrF(generator->Amplitude,ffFixed,3,3);
 }

 if(MomentTrackBar->Position>0)
  MomentProgressBar->Position=MomentTrackBar->Position;
 else
  MomentProgressBar->Position=-MomentTrackBar->Position;
}
//---------------------------------------------------------------------------

void __fastcall TManipulatorTestForm::IaCheckBoxClick(TObject *Sender)
{
 bool res;
 NAContainer* cont;

 if(MainForm->AfferentModeComboBox->ItemIndex == 0)
 {
  if(IaCheckBox->Checked)
  {
   res=ControlSystem->BreakLink("AfferentSource1","DataOutput0","MotionElement0.Afferent_Ia2.Receptor","DataInput0");
   res=ControlSystem->BreakLink("AfferentSource1","DataOutput0","MotionElement0.Afferent_Ia1.Receptor","DataInput0");

   res=ControlSystem->CreateLink("Ia_PosSignumSeparator","DataOutput0","MotionElement0.Afferent_Ia2.Receptor","DataInput0");
   res=ControlSystem->CreateLink("Ia_NegSignumSeparator","DataOutput0","MotionElement0.Afferent_Ia1.Receptor","DataInput0");
  }
  else
  {
   res=ControlSystem->BreakLink("Ia_PosSignumSeparator","DataOutput0","MotionElement0.Afferent_Ia2.Receptor","DataInput0");
   res=ControlSystem->BreakLink("Ia_NegSignumSeparator","DataOutput0","MotionElement0.Afferent_Ia1.Receptor","DataInput0");

   res=ControlSystem->CreateLink("AfferentSource1","DataOutput0","MotionElement0.Afferent_Ia2.Receptor","DataInput0");
   res=ControlSystem->CreateLink("AfferentSource1","DataOutput0","MotionElement0.Afferent_Ia1.Receptor","DataInput0");
  }
 }

 if(MainForm->AfferentModeComboBox->ItemIndex > 0)
 {
  int num_motions=MainForm->NumMotionElementsComboBox->ItemIndex+1;
  if(IaCheckBox->Checked)
  {
   for(int i=0;i<num_motions;i++)
   {
	string motion=string("MotionElement")+RDK::sntoa(i);
	string pos_separator=string("Ia_PosIntervalSeparator")+RDK::sntoa(i+1);
	string neg_separator=string("Ia_NegIntervalSeparator")+RDK::sntoa(i+1);

	res=ControlSystem->BreakLink("AfferentSource1","DataOutput0",motion+".Afferent_Ia2.Receptor","DataInput0");
	res=ControlSystem->BreakLink("AfferentSource1","DataOutput0",motion+".Afferent_Ia1.Receptor","DataInput0");

	res=ControlSystem->CreateLink(pos_separator,"DataOutput0",motion+".Afferent_Ia2.Receptor","DataInput0");
	res=ControlSystem->CreateLink(neg_separator,"DataOutput0",motion+".Afferent_Ia1.Receptor","DataInput0");
   }
  }
  else
  {
   for(int i=0;i<num_motions;i++)
   {
	string motion=string("MotionElement")+RDK::sntoa(i);
	string pos_separator=string("Ia_PosIntervalSeparator")+RDK::sntoa(i+1);
	string neg_separator=string("Ia_NegIntervalSeparator")+RDK::sntoa(i+1);

	res=ControlSystem->BreakLink(pos_separator,"DataOutput0",motion+".Afferent_Ia2.Receptor","DataInput0");
	res=ControlSystem->BreakLink(neg_separator,"DataOutput0",motion+".Afferent_Ia1.Receptor","DataInput0");

	res=ControlSystem->CreateLink("AfferentSource1","DataOutput0",motion+".Afferent_Ia2.Receptor","DataInput0");
	res=ControlSystem->CreateLink("AfferentSource1","DataOutput0",motion+".Afferent_Ia1.Receptor","DataInput0");
   }
  }
 }
 if(!res)
  return;
}
//---------------------------------------------------------------------------

void __fastcall TManipulatorTestForm::IbCheckBoxClick(TObject *Sender)
{
 bool res;
 NAContainer* cont;

 if(MainForm->AfferentModeComboBox->ItemIndex == 0)
 {
  if(IbCheckBox->Checked)
  {
   res=ControlSystem->BreakLink("AfferentSource1","DataOutput0","MotionElement0.Afferent_Ib2.Receptor","DataInput0");
   res=ControlSystem->BreakLink("AfferentSource1","DataOutput0","MotionElement0.Afferent_Ib1.Receptor","DataInput0");

   res=ControlSystem->CreateLink("Ib_PosSignumSeparator","DataOutput0","MotionElement0.Afferent_Ib1.Receptor","DataInput0");
   res=ControlSystem->CreateLink("Ib_NegSignumSeparator","DataOutput0","MotionElement0.Afferent_Ib2.Receptor","DataInput0");
  }
  else
  {
   res=ControlSystem->BreakLink("Ib_PosSignumSeparator","DataOutput0","MotionElement0.Afferent_Ib1.Receptor","DataInput0");
   res=ControlSystem->BreakLink("Ib_NegSignumSeparator","DataOutput0","MotionElement0.Afferent_Ib2.Receptor","DataInput0");

   res=ControlSystem->CreateLink("AfferentSource1","DataOutput0","MotionElement0.Afferent_Ib2.Receptor","DataInput0");
   res=ControlSystem->CreateLink("AfferentSource1","DataOutput0","MotionElement0.Afferent_Ib1.Receptor","DataInput0");
  }
 }

 if(MainForm->AfferentModeComboBox->ItemIndex >0)
 {
  int num_motions=MainForm->NumMotionElementsComboBox->ItemIndex+1;
  if(IbCheckBox->Checked)
  {
   for(int i=0;i<num_motions;i++)
   {
	string motion=string("MotionElement")+RDK::sntoa(i);
	string pos_separator=string("Ib_PosIntervalSeparator")+RDK::sntoa(i+1);
	string neg_separator=string("Ib_NegIntervalSeparator")+RDK::sntoa(i+1);

	res=ControlSystem->BreakLink("AfferentSource1","DataOutput0",motion+".Afferent_Ib2.Receptor","DataInput0");
	res=ControlSystem->BreakLink("AfferentSource1","DataOutput0",motion+".Afferent_Ib1.Receptor","DataInput0");

	res=ControlSystem->CreateLink(pos_separator,"DataOutput0",motion+".Afferent_Ib1.Receptor","DataInput0");
	res=ControlSystem->CreateLink(neg_separator,"DataOutput0",motion+".Afferent_Ib2.Receptor","DataInput0");
   }
  }
  else
  {
   for(int i=0;i<num_motions;i++)
   {
	string motion=string("MotionElement")+RDK::sntoa(i);
	string pos_separator=string("Ib_PosIntervalSeparator")+RDK::sntoa(i+1);
	string neg_separator=string("Ib_NegIntervalSeparator")+RDK::sntoa(i+1);

	res=ControlSystem->BreakLink(pos_separator,"DataOutput0",motion+".Afferent_Ib1.Receptor","DataInput0");
	res=ControlSystem->BreakLink(neg_separator,"DataOutput0",motion+".Afferent_Ib2.Receptor","DataInput0");

	res=ControlSystem->CreateLink("AfferentSource1","DataOutput0",motion+".Afferent_Ib1.Receptor","DataInput0");
	res=ControlSystem->CreateLink("AfferentSource1","DataOutput0",motion+".Afferent_Ib2.Receptor","DataInput0");
   }
  }
 }
 if(!res)
  return;
}
//---------------------------------------------------------------------------

void __fastcall TManipulatorTestForm::IICheckBoxClick(TObject *Sender)
{
 bool res=true;
 NADItem* cont;

 if(MainForm->AfferentModeComboBox->ItemIndex == 0)
 {
  if(IICheckBox->Checked)
  {
   res&=ControlSystem->BreakLink("AfferentSource1","DataOutput0","MotionElement0.Afferent_II2.Receptor","DataInput0");
   res&=ControlSystem->BreakLink("AfferentSource1","DataOutput0","MotionElement0.Afferent_II1.Receptor","DataInput0");

   res&=ControlSystem->CreateLink("II_PosSignumSeparator","DataOutput0","MotionElement0.Afferent_II1.Receptor","DataInput0");
   res&=ControlSystem->CreateLink("II_NegSignumSeparator","DataOutput0","MotionElement0.Afferent_II2.Receptor","DataInput0");
  }
  else
  {
   res&=ControlSystem->BreakLink("II_PosSignumSeparator","DataOutput0","MotionElement0.Afferent_II1.Receptor","DataInput0");
   res&=ControlSystem->BreakLink("II_NegSignumSeparator","DataOutput0","MotionElement0.Afferent_II2.Receptor","DataInput0");

   res&=ControlSystem->CreateLink("AfferentSource1","DataOutput0","MotionElement0.Afferent_II2.Receptor","DataInput0");
   res&=ControlSystem->CreateLink("AfferentSource1","DataOutput0","MotionElement0.Afferent_II1.Receptor","DataInput0");
  }
 }

 if(MainForm->AfferentModeComboBox->ItemIndex >0)
 {
  int num_motions=MainForm->NumMotionElementsComboBox->ItemIndex+1;
  if(IICheckBox->Checked)
  {
   for(int i=0;i<num_motions;i++)
   {
	string motion=string("MotionElement")+RDK::sntoa(i);
	string pos_separator=string("II_PosIntervalSeparator")+RDK::sntoa(i+1);
	string neg_separator=string("II_NegIntervalSeparator")+RDK::sntoa(i+1);

	res&=ControlSystem->BreakLink("AfferentSource1","DataOutput0",motion+".Afferent_II2.Receptor","DataInput0");
	res&=ControlSystem->BreakLink("AfferentSource1","DataOutput0",motion+".Afferent_II1.Receptor","DataInput0");

	res&=ControlSystem->CreateLink(pos_separator,"DataOutput0",motion+".Afferent_II1.Receptor","DataInput0");
	res&=ControlSystem->CreateLink(neg_separator,"DataOutput0",motion+".Afferent_II2.Receptor","DataInput0");
   }
  }
  else
  {
   for(int i=0;i<num_motions;i++)
   {
	string motion=string("MotionElement")+RDK::sntoa(i);
	string pos_separator=string("II_PosIntervalSeparator")+RDK::sntoa(i+1);
	string neg_separator=string("II_NegIntervalSeparator")+RDK::sntoa(i+1);

	res&=ControlSystem->BreakLink(pos_separator,"DataOutput0",motion+".Afferent_II1.Receptor","DataInput0");
	res&=ControlSystem->BreakLink(neg_separator,"DataOutput0",motion+".Afferent_II2.Receptor","DataInput0");

	res&=ControlSystem->CreateLink("AfferentSource1","DataOutput0",motion+".Afferent_II2.Receptor","DataInput0");
	res&=ControlSystem->CreateLink("AfferentSource1","DataOutput0",motion+".Afferent_II1.Receptor","DataInput0");
   }
  }
 }
 if(!res)
  return;
}
//---------------------------------------------------------------------------


void __fastcall TManipulatorTestForm::IIAfferentTrackBarChange(TObject *Sender)
{
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

void __fastcall TManipulatorTestForm::IIAfferentEditChange(TObject *Sender)
{
 //
}
//---------------------------------------------------------------------------

void __fastcall TManipulatorTestForm::IINumAfferentTrackBarChange(TObject *Sender)
{
 bool res=true;

 for(int i=0;i<IINumAfferentTrackBar->Position;i++)
 {
  // Вариант для отдельного участка мембраны для внешнего управления
/*  res&=ControlSystem->CreateLink("IIPosAfferentGenerator",0,string("MotionElement")+RDK::sntoa(i)+".PostAfferent14.PNeuronMembrane3.PosChannel.Synapse");
  res&=ControlSystem->CreateLink("IIPosAfferentGenerator",0,string("MotionElement")+RDK::sntoa(i)+".PostAfferent24.PNeuronMembrane3.NegChannel.Synapse");
  res&=ControlSystem->CreateLink("IINegAfferentGenerator",0,string("MotionElement")+RDK::sntoa(i)+".PostAfferent14.PNeuronMembrane3.NegChannel.Synapse2");
  res&=ControlSystem->CreateLink("IINegAfferentGenerator",0,string("MotionElement")+RDK::sntoa(i)+".PostAfferent24.PNeuronMembrane3.PosChannel.Synapse2");
*/

  res&=ControlSystem->CreateLink("IIPosAfferentGenerator","DataOutput0",string("MotionElement")+RDK::sntoa(i)+".PostAfferent14.PNeuronMembrane.PosChannel","");
  res&=ControlSystem->CreateLink("IIPosAfferentGenerator","DataOutput0",string("MotionElement")+RDK::sntoa(i)+".PostAfferent24.PNeuronMembrane.NegChannel","");
  res&=ControlSystem->CreateLink("IINegAfferentGenerator","DataOutput0",string("MotionElement")+RDK::sntoa(i)+".PostAfferent14.PNeuronMembrane.NegChannel","");
  res&=ControlSystem->CreateLink("IINegAfferentGenerator","DataOutput0",string("MotionElement")+RDK::sntoa(i)+".PostAfferent24.PNeuronMembrane.PosChannel","");

//  res&=ControlSystem->CreateLink("IIPosAfferentGenerator",0,string("MotionElement")+RDK::sntoa(i)+".Motoneuron1.PNeuronMembrane2.PosChannel");
//  res&=ControlSystem->CreateLink("IIPosAfferentGenerator",0,string("MotionElement")+RDK::sntoa(i)+".Renshow1.PNeuronMembrane2.PosChannel");

/*
  res&=ControlSystem->CreateLink("IIPosAfferentGenerator",0,string("MotionElement")+RDK::sntoa(i)+".PostAfferent15.PNeuronMembrane.NegChannel.Synapse2");
  res&=ControlSystem->CreateLink("IIPosAfferentGenerator",0,string("MotionElement")+RDK::sntoa(i)+".PostAfferent25.PNeuronMembrane.PosChannel.Synapse2");
  res&=ControlSystem->CreateLink("IINegAfferentGenerator",0,string("MotionElement")+RDK::sntoa(i)+".PostAfferent15.PNeuronMembrane.PosChannel.Synapse3");
  res&=ControlSystem->CreateLink("IINegAfferentGenerator",0,string("MotionElement")+RDK::sntoa(i)+".PostAfferent25.PNeuronMembrane.NegChannel.Synapse3");
*/
 }

 for(int i=IINumAfferentTrackBar->Position;i<IINumAfferentTrackBar->Max;i++)
 {
  // Вариант для отдельного участка мембраны для внешнего управления
/*  res&=ControlSystem->BreakLink("IIPosAfferentGenerator",0,string("MotionElement")+RDK::sntoa(i)+".PostAfferent14.PNeuronMembrane3.PosChannel.Synapse",0);
  res&=ControlSystem->BreakLink("IIPosAfferentGenerator",0,string("MotionElement")+RDK::sntoa(i)+".PostAfferent24.PNeuronMembrane3.NegChannel.Synapse",0);
  res&=ControlSystem->BreakLink("IINegAfferentGenerator",0,string("MotionElement")+RDK::sntoa(i)+".PostAfferent14.PNeuronMembrane3.NegChannel.Synapse2",0);
  res&=ControlSystem->BreakLink("IINegAfferentGenerator",0,string("MotionElement")+RDK::sntoa(i)+".PostAfferent24.PNeuronMembrane3.PosChannel.Synapse2",0);
*/

  res&=ControlSystem->BreakLink("IIPosAfferentGenerator","DataOutput0",string("MotionElement")+RDK::sntoa(i)+".PostAfferent14.PNeuronMembrane.PosChannel","DataInput0");
  res&=ControlSystem->BreakLink("IIPosAfferentGenerator","DataOutput0",string("MotionElement")+RDK::sntoa(i)+".PostAfferent24.PNeuronMembrane.NegChannel","DataInput0");
  res&=ControlSystem->BreakLink("IINegAfferentGenerator","DataOutput0",string("MotionElement")+RDK::sntoa(i)+".PostAfferent14.PNeuronMembrane.NegChannel","DataInput0");
  res&=ControlSystem->BreakLink("IINegAfferentGenerator","DataOutput0",string("MotionElement")+RDK::sntoa(i)+".PostAfferent24.PNeuronMembrane.PosChannel","DataInput0");

/*
  res&=ControlSystem->BreakLink("IIPosAfferentGenerator",0,string("MotionElement")+RDK::sntoa(i)+".PostAfferent15.PNeuronMembrane.NegChannel.Synapse2",0);
  res&=ControlSystem->BreakLink("IIPosAfferentGenerator",0,string("MotionElement")+RDK::sntoa(i)+".PostAfferent25.PNeuronMembrane.PosChannel.Synapse2",0);
  res&=ControlSystem->BreakLink("IINegAfferentGenerator",0,string("MotionElement")+RDK::sntoa(i)+".PostAfferent15.PNeuronMembrane.PosChannel.Synapse3",0);
  res&=ControlSystem->BreakLink("IINegAfferentGenerator",0,string("MotionElement")+RDK::sntoa(i)+".PostAfferent25.PNeuronMembrane.NegChannel.Synapse3",0);
*/
 }

 IINumAfferentEdit->Text=IntToStr(IINumAfferentTrackBar->Position);
 if(!res)
  return;
}
//---------------------------------------------------------------------------

void __fastcall TManipulatorTestForm::IINumAfferentEditChange(TObject *Sender)
{
 //
}
//---------------------------------------------------------------------------

void __fastcall TManipulatorTestForm::ControlVoltageCheckBoxClick(TObject *Sender)

{
 bool res;
 NADItem* cont;
 int num_motions=StrToInt(MainForm->NumMotionElementsComboBox->Items->Strings[MainForm->NumMotionElementsComboBox->ItemIndex]);


  if(ControlVoltageCheckBox->Checked == false)
  {
   res=ControlSystem->BreakLink("Pac","DataOutput0","NManipulatorInput1","DataInput0");

   res=ControlSystem->BreakLink("Pac","DataOutput0","NManipulatorInputEmulator1","DataInput0");
  }
  else
  {
   res=ControlSystem->CreateLink("Pac","DataOutput0","NManipulatorInput1","DataInput0");

   res=ControlSystem->CreateLink("Pac","DataOutput0","NManipulatorInputEmulator1","DataInput0");
  }

 if(!res)
  return;
}
//---------------------------------------------------------------------------

void __fastcall TManipulatorTestForm::RadioGroup1Click(TObject *Sender)
{
 MainForm->Button4Click(Sender);
 NAContainer *cont=0;


 int num_ranges=StrToInt(MainForm->NumMotionElementsComboBox->Items->Strings[MainForm->NumMotionElementsComboBox->ItemIndex]);
 bool res=true;

 if(!ControlSystem)
  return;

if(!RadioGroup1->ItemIndex)
{
 for(int i=0;i<num_ranges;i++)
 {
  res&=ControlSystem->BreakLink("NManipulatorSource1","DataOutput2",
				 string("Ia_PosIntervalSeparator")+RDK::sntoa(i+1),"DataInput0");
  res&=ControlSystem->BreakLink("NManipulatorSource1","DataOutput2",
				 string("Ia_NegIntervalSeparator")+RDK::sntoa(i+1),"DataInput0");
 }

 for(int i=0;i<num_ranges;i++)
 {
  res&=ControlSystem->BreakLink("NManipulatorSource1","DataOutput1",
				 string("II_PosIntervalSeparator")+RDK::sntoa(i+1),"DataInput0");
  res&=ControlSystem->BreakLink("NManipulatorSource1","DataOutput1",
				 string("II_NegIntervalSeparator")+RDK::sntoa(i+1),"DataInput0");
 }

 for(int i=0;i<num_ranges;i++)
 {
  res&=ControlSystem->BreakLink("NManipulatorSource1","DataOutput0",
				 string("Ib_PosIntervalSeparator")+RDK::sntoa(i+1),"DataInput0");
  res&=ControlSystem->BreakLink("NManipulatorSource1","DataOutput0",
				 string("Ib_NegIntervalSeparator")+RDK::sntoa(i+1),"DataInput0");
 }


 for(int i=0;i<num_ranges;i++)
 {
  res&=ControlSystem->CreateLink("NManipulatorSourceEmulator1","DataOutput2",
				 string("Ia_PosIntervalSeparator")+RDK::sntoa(i+1),"DataInput0");
  res&=ControlSystem->CreateLink("NManipulatorSourceEmulator1","DataOutput2",
				 string("Ia_NegIntervalSeparator")+RDK::sntoa(i+1),"DataInput0");
 }

 for(int i=0;i<num_ranges;i++)
 {
  res&=ControlSystem->CreateLink("NManipulatorSourceEmulator1","DataOutput1",
				 string("II_PosIntervalSeparator")+RDK::sntoa(i+1),"DataInput0");
  res&=ControlSystem->CreateLink("NManipulatorSourceEmulator1","DataOutput1",
				 string("II_NegIntervalSeparator")+RDK::sntoa(i+1),"DataInput0");
 }

 for(int i=0;i<num_ranges;i++)
 {
  res&=ControlSystem->CreateLink("NManipulatorSourceEmulator1","DataOutput0",
				 string("Ib_PosIntervalSeparator")+RDK::sntoa(i+1),"DataInput0");
  res&=ControlSystem->CreateLink("NManipulatorSourceEmulator1","DataOutput0",
				 string("Ib_NegIntervalSeparator")+RDK::sntoa(i+1),"DataInput0");
 }

 cont=ControlSystem->GetComponent("NManipulatorSourceEmulator1");
 Engine=(NManipulatorSource*)cont;
}
else
{
 for(int i=0;i<num_ranges;i++)
 {
  res&=ControlSystem->BreakLink("NManipulatorSourceEmulator1","DataOutput2",
				 string("Ia_PosIntervalSeparator")+RDK::sntoa(i+1),"DataInput0");
  res&=ControlSystem->BreakLink("NManipulatorSourceEmulator1","DataOutput2",
				 string("Ia_NegIntervalSeparator")+RDK::sntoa(i+1),"DataInput0");
 }

 for(int i=0;i<num_ranges;i++)
 {
  res&=ControlSystem->BreakLink("NManipulatorSourceEmulator1","DataOutput1",
				 string("II_PosIntervalSeparator")+RDK::sntoa(i+1),"DataInput0");
  res&=ControlSystem->BreakLink("NManipulatorSourceEmulator1","DataOutput1",
				 string("II_NegIntervalSeparator")+RDK::sntoa(i+1),"DataInput0");
 }

 for(int i=0;i<num_ranges;i++)
 {
  res&=ControlSystem->BreakLink("NManipulatorSourceEmulator1","DataOutput0",
				 string("Ib_PosIntervalSeparator")+RDK::sntoa(i+1),"DataInput0");
  res&=ControlSystem->BreakLink("NManipulatorSourceEmulator1","DataOutput0",
                 string("Ib_NegIntervalSeparator")+RDK::sntoa(i+1),"DataInput0");
 }


 for(int i=0;i<num_ranges;i++)
 {
  res&=ControlSystem->CreateLink("NManipulatorSource1","DataOutput2",
				 string("Ia_PosIntervalSeparator")+RDK::sntoa(i+1),"DataInput0");
  res&=ControlSystem->CreateLink("NManipulatorSource1","DataOutput2",
				 string("Ia_NegIntervalSeparator")+RDK::sntoa(i+1),"DataInput0");
 }

 for(int i=0;i<num_ranges;i++)
 {
  res&=ControlSystem->CreateLink("NManipulatorSource1","DataOutput1",
				 string("II_PosIntervalSeparator")+RDK::sntoa(i+1),"DataInput0");
  res&=ControlSystem->CreateLink("NManipulatorSource1","DataOutput1",
				 string("II_NegIntervalSeparator")+RDK::sntoa(i+1),"DataInput0");
 }

 for(int i=0;i<num_ranges;i++)
 {
  res&=ControlSystem->CreateLink("NManipulatorSource1","DataOutput0",
				 string("Ib_PosIntervalSeparator")+RDK::sntoa(i+1),"DataInput0");
  res&=ControlSystem->CreateLink("NManipulatorSource1","DataOutput0",
				 string("Ib_NegIntervalSeparator")+RDK::sntoa(i+1),"DataInput0");
 }
 cont=ControlSystem->GetComponent("NManipulatorSource1");
 Engine=(NManipulatorSource*)cont;
}
}
//---------------------------------------------------------------------------

void __fastcall TManipulatorTestForm::VoltageMulTrackBarChange(TObject *Sender)
{
 double value=VoltageMulTrackBar->Position/100.0;
 VoltageMulEdit->Text=FloatToStrF(value,ffFixed,3,3);
 if(RadioGroup1->ItemIndex != 0)
  {
   UEPtr<NWPhysicalManipulator> engine_input=dynamic_pointer_cast<NWPhysicalManipulator>(ControlSystem->GetComponent("WPhysicalManipulator"));
   if(engine_input)
	engine_input->OutputMul=value;
  }
}
//---------------------------------------------------------------------------

void __fastcall TManipulatorTestForm::EmulatorCheckBoxClick(TObject *Sender)
{
/*
 NWPhysicalManipulator *engine_input=static_cast<NWPhysicalManipulator*>(ControlSystem->GetComponent("WPhysicalManipulator"));
 if(engine_input)
 {
  engine_input->UnInitManipulator();
  engine_input->EmulatorMode=EmulatorCheckBox->Checked;
  engine_input->ComPort=StrToInt(ComPortEdit->Text);
  engine_input->ServoNumber=StrToInt(ServoNumberEdit->Text);
  engine_input->InitManipulator();
 }*/
 OffDeviceButtonClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TManipulatorTestForm::SwapOutputVoltageDirectionCheckBoxClick(TObject *Sender)
{
 UEPtr<NWPhysicalManipulator> engine_input=static_pointer_cast<NWPhysicalManipulator>(ControlSystem->GetComponent("WPhysicalManipulator"));
 if(!engine_input)
  return;

 if(SwapOutputVoltageDirectionCheckBox->Checked == true)
 {
  engine_input->RightDirection=NWPhysicalManipulator::ServoRight;
  engine_input->LeftDirection=NWPhysicalManipulator::ServoLeft;
 }
 else
 {
  engine_input->RightDirection=NWPhysicalManipulator::ServoLeft;
  engine_input->LeftDirection=NWPhysicalManipulator::ServoRight;
 }
}
//---------------------------------------------------------------------------

void __fastcall TManipulatorTestForm::ServoNumberEditChange(TObject *Sender)
{
 UEPtr<NWPhysicalManipulator> engine_input=static_pointer_cast<NWPhysicalManipulator>(ControlSystem->GetComponent("WPhysicalManipulator"));
 if(!engine_input)
  return;

 engine_input->ServoNumber=StrToInt(ServoNumberEdit->Text);
}
//---------------------------------------------------------------------------

void __fastcall TManipulatorTestForm::TimeDurationTrackBarChange(TObject *Sender)

{
 double value=TimeDurationTrackBar->Position;
 TimeDurationEdit->Text=FloatToStrF(value,ffFixed,3,3);
 if(RadioGroup1->ItemIndex != 0)
  {
   UEPtr<NWPhysicalManipulator> engine_input=static_pointer_cast<NWPhysicalManipulator>(ControlSystem->GetComponent("WPhysicalManipulator"));
   if(engine_input)
	engine_input->TimeDuration=value;
  }

}
//---------------------------------------------------------------------------

void __fastcall TManipulatorTestForm::PACDeactivatorTimeTrackBarChange(TObject *Sender)

{
 int num_ranges=StrToInt(MainForm->NumMotionElementsComboBox->Items->Strings[MainForm->NumMotionElementsComboBox->ItemIndex]);
 double value=double(PACDeactivatorTimeTrackBar->Position)/double(PACDeactivatorTimeTrackBar->Max);
 PACDeactivatorTimeEdit->Text=FloatToStrF(value,ffFixed,3,3);

 UEPtr<NPac> engine_input=dynamic_pointer_cast<NPac>(ControlSystem->GetComponent("Pac"));
 if(engine_input)
 {
  vector<Real> values;

  values.resize(num_ranges*2);
  // Постоянная времени распада медиатора
  for(size_t i=0;i<values.size();i++)
   values[i].assign(1,value);
  engine_input->DissociationTC=values;
 }
}
//---------------------------------------------------------------------------

void __fastcall TManipulatorTestForm::PACActivatorTimeTrackBarChange(TObject *Sender)

{
 int num_ranges=StrToInt(MainForm->NumMotionElementsComboBox->Items->Strings[MainForm->NumMotionElementsComboBox->ItemIndex]);
 double value=double(PACActivatorTimeTrackBar->Position)/double(PACActivatorTimeTrackBar->Max);
 PACActivatorTimeEdit->Text=FloatToStrF(value,ffFixed,3,3);

 UEPtr<NPac> engine_input=dynamic_pointer_cast<NPac>(ControlSystem->GetComponent("Pac"));
 if(engine_input)
 {
  vector<Real> values;

  values.resize(num_ranges*2);
  // Постоянная времени распада медиатора
  for(size_t i=0;i<values.size();i++)
   values[i].assign(1,value);
  engine_input->SecretionTC=values;
 }
}
//---------------------------------------------------------------------------

void __fastcall TManipulatorTestForm::OnDeviceButtonClick(TObject *Sender)
{
  RadioGroup1->ItemIndex=1;
 RadioGroup1Click(Sender);
 UEPtr<NWPhysicalManipulator> engine_input=dynamic_pointer_cast<NWPhysicalManipulator>(ControlSystem->GetComponent("WPhysicalManipulator"));
 if(engine_input)
 {
  engine_input->SetActivity(true);
  engine_input->EmulatorMode=EmulatorCheckBox->Checked;
  if(engine_input->EmulatorMode)
   engine_input->SetTimeStep(ControlSystem->GetTimeStep());
  else
   engine_input->SetTimeStep(ControlSystem->GetTimeStep());
//   engine_input->SetTimeStep(100);
  engine_input->ComPort=StrToInt(ComPortEdit->Text);
  engine_input->ServoNumber=StrToInt(ServoNumberEdit->Text);
  engine_input->InitManipulator();
  int num_ranges=StrToInt(MainForm->NumMotionElementsComboBox->Items->Strings[MainForm->NumMotionElementsComboBox->ItemIndex]);
//  if(!engine_input->EmulatorMode)
//   VoltageMulTrackBar->Position=200*num_ranges;
//  else
//   VoltageMulTrackBar->Position=200;

  if(MulToNumberOfControlElementsCheckBox->Checked)
   VoltageMulTrackBar->Position=200*num_ranges;
  else
   VoltageMulTrackBar->Position=200;

  MainForm->Button6Click(Sender);
  OnDeviceButton->Enabled=false;
  OffDeviceButton->Enabled=true;
  MainForm->Button3Click(Sender);
 }

}
//---------------------------------------------------------------------------

void __fastcall TManipulatorTestForm::OffDeviceButtonClick(TObject *Sender)
{
 if(OffDeviceButton->Enabled == false)
  return;

 RadioGroup1->ItemIndex=0;
 RadioGroup1Click(Sender);
 UEPtr<NWPhysicalManipulator> engine_input=dynamic_pointer_cast<NWPhysicalManipulator>(ControlSystem->GetComponent("WPhysicalManipulator"));
 if(engine_input)
 {
  engine_input->UnInitManipulator();
  OnDeviceButton->Enabled=true;
  OffDeviceButton->Enabled=false;
  MainForm->Button4Click(Sender);
  engine_input->SetActivity(false);
 }

}
//---------------------------------------------------------------------------


void __fastcall TManipulatorTestForm::SendVButtonClick(TObject *Sender)
{
 UEPtr<NWPhysicalManipulator> engine_input=dynamic_pointer_cast<NWPhysicalManipulator>(ControlSystem->GetComponent("WPhysicalManipulator"));
 int num_ranges=StrToInt(MainForm->NumMotionElementsComboBox->Items->Strings[MainForm->NumMotionElementsComboBox->ItemIndex]);
 if(engine_input)
 {
  engine_input->SetAccumulationStep(StrToInt(VaEdit->Text)/num_ranges);
  engine_input->SetDissociationStep(StrToInt(VdEdit->Text));
 }
}
//---------------------------------------------------------------------------



void __fastcall TManipulatorTestForm::WorkModeComboBoxSelect(TObject *Sender)
{
 UEPtr<NWPhysicalManipulator> engine_input=dynamic_pointer_cast<NWPhysicalManipulator>(ControlSystem->GetComponent("WPhysicalManipulator"));
 if(engine_input)
 {
  engine_input->DllManipulatorMode=WorkModeComboBox->ItemIndex+2;
  engine_input->DMSetWorkMode(engine_input->DllManipulatorMode);
 }
}
//---------------------------------------------------------------------------

