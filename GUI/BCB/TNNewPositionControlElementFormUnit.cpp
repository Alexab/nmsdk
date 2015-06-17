//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UComponentsListFormUnit.h"
#include "TNNewPositionControlElementFormUnit.h"
#include "nmsdk.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TNNewPositionControlElementForm *NNewPositionControlElementForm;
//---------------------------------------------------------------------------
__fastcall TNNewPositionControlElementForm::TNNewPositionControlElementForm(TComponent* Owner)
	: TUVisualControllerForm(Owner)
{
}

// Сохраняет параметры интерфейса в xml
void TNNewPositionControlElementForm::ASaveParameters(RDK::USerStorageXML &xml)
{

}

// Загружает параметры интерфейса из xml
void TNNewPositionControlElementForm::ALoadParameters(RDK::USerStorageXML &xml)
{

}


void TNNewPositionControlElementForm::AUpdateInterface(void)
{
 try
 {
  RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
  RDK::UEPtr<NMSDK::NNewPositionControlElement> position_control=
	RDK::dynamic_pointer_cast<NMSDK::NNewPositionControlElement>(model->GetComponentL(ComponentControlName));

  int num_motion_elements=position_control->MotionControl->NumMotionElements;
  int num_control_loops=position_control->MotionControl->NumControlLoops;

  // Отображаем состояние генераторов
  std::vector<std::vector<RDK::UNet*> > &left_generators=position_control->LeftGenerators;
  std::vector<std::vector<RDK::UNet*> > &right_generators=position_control->RightGenerators;
  SelectedStateStringGrid->ColCount=num_motion_elements*2+1;
  SelectedStateStringGrid->RowCount=num_control_loops+1;

  if(left_generators.empty() || right_generators.empty())
   return;

  for(int m=0;m<num_control_loops;m++)
  {
   SelectedStateStringGrid->Cells[0][m+1]=String("CL")+m;
   for(int n=0;n<num_motion_elements;n++)
   {
	RDK::UEPtr<NMSDK::NPulseGenerator> gen=dynamic_cast<NMSDK::NPulseGenerator*>(left_generators[m][n]);
	SelectedStateStringGrid->Cells[num_motion_elements-1-n+1][m+1]=FloatToStrF(gen->Frequency,ffFixed,3,3);
	gen=dynamic_cast<NMSDK::NPulseGenerator*>(right_generators[m][n]);
	SelectedStateStringGrid->Cells[n+num_motion_elements+1][m+1]=FloatToStrF(gen->Frequency,ffFixed,3,3);
	SelectedStateStringGrid->Cells[num_motion_elements-1-n+1][0]=String("ML")+n;
	SelectedStateStringGrid->Cells[n+num_motion_elements+1][0]=String("MR")+n;
   }
  }

 // Отображаем состояние наученного слоя
  std::vector<std::vector<NMSDK::NNet*> > &left_neurons=position_control->LeftPostInputNeurons;
  std::vector<std::vector<NMSDK::NNet*> > &right_neurons=position_control->RightPostInputNeurons;

  TrainedStateStringGrid->ColCount=num_motion_elements*2+1;
  TrainedStateStringGrid->RowCount=num_control_loops+1;

  if(left_neurons.empty() || right_neurons.empty())
   return;

  for(int m=0;m<num_control_loops;m++)
  {
   TrainedStateStringGrid->Cells[0][m+1]=String("CL")+m;
   for(int n=0;n<num_motion_elements;n++)
   {
	RDK::UEPtr<NMSDK::NPulseNeuron> gen=dynamic_cast<NMSDK::NPulseNeuron*>(left_neurons[m][n]);
	RDK::UEPtr<NMSDK::NPulseLTZone> ltzone=RDK::dynamic_pointer_cast<NMSDK::NPulseLTZone>(gen->GetComponentL("LTZone"));
	TrainedStateStringGrid->Cells[num_motion_elements-1-n+1][m+1]=FloatToStrF(ltzone->GetOutputData(2).Double[0],ffFixed,3,3);
	gen=dynamic_cast<NMSDK::NPulseNeuron*>(right_neurons[m][n]);
	ltzone=RDK::dynamic_pointer_cast<NMSDK::NPulseLTZone>(gen->GetComponentL("LTZone"));
	TrainedStateStringGrid->Cells[n+num_motion_elements+1][m+1]=FloatToStrF(ltzone->GetOutputData(2).Double[0],ffFixed,3,3);
	TrainedStateStringGrid->Cells[num_motion_elements-1-n+1][0]=String("ML")+n;
	TrainedStateStringGrid->Cells[n+num_motion_elements+1][0]=String("MR")+n;
   }
  }


/*
  int n_left=num_motion_elements-1,n_right=num_motion_elements,m=0,n=0;
  int i=0;
  while(i<neurons.size())
  {
   TrainedStateStringGrid->Cells[0][m+1]=String("CL")+m;

   RDK::UEPtr<NMSDK::NPulseNeuron> gen=dynamic_cast<NMSDK::NPulseNeuron*>(neurons[i]);
   RDK::UEPtr<NMSDK::NPulseLTZone> ltzone=dynamic_pointer_cast<NMSDK::NPulseLTZone>(neurons[i]->GetComponentL("LTZone"));
   TrainedStateStringGrid->Cells[n_left+1][m+1]=FloatToStrF(ltzone->GetOutputData(2).Double[0],ffFixed,3,3);
   TrainedStateStringGrid->Cells[n_left+1][0]=String("ML")+n;
   ++i;
   gen=dynamic_cast<NMSDK::NPulseNeuron*>(neurons[i]);
   ltzone=dynamic_pointer_cast<NMSDK::NPulseLTZone>(neurons[i]->GetComponentL("LTZone"));
   TrainedStateStringGrid->Cells[n_right+1][m+1]=FloatToStrF(ltzone->GetOutputData(2).Double[0],ffFixed,3,3);
   TrainedStateStringGrid->Cells[n_right+1][0]=String("MR")+n;
   ++i;
   m++;
   if(m>=num_control_loops)
   {
    n++;
	m=0;
	--n_left;
    ++n_right;
   }
  }  */
 }
 catch(RDK::UException &exception)
 {

 }
}

// Возврат интерфейса в исходное состояние
void TNNewPositionControlElementForm::AClearInterface(void)
{

}

// Создание копии этого компонента
TUVisualControllerForm* TNNewPositionControlElementForm::New(TComponent *owner)
{
 return new TNNewPositionControlElementForm(owner);
}
//---------------------------------------------------------------------------
void __fastcall TNNewPositionControlElementForm::FormCreate(TObject *Sender)
{
 TUComponentsListFrame::ComponentControllers["NNewPositionControlElement"]=NNewPositionControlElementForm;
}
//---------------------------------------------------------------------------

void __fastcall TNNewPositionControlElementForm::SelectedStateStringGridSetEditText(TObject *Sender,
          int ACol, int ARow, const UnicodeString Value)
{
 try
 {
  RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
  RDK::UEPtr<NMSDK::NNewPositionControlElement> position_control=
	RDK::dynamic_pointer_cast<NMSDK::NNewPositionControlElement>(model->GetComponentL(ComponentControlName));

  std::vector<std::vector<RDK::UNet*> > &left_generators=position_control->LeftGenerators;
  std::vector<std::vector<RDK::UNet*> > &right_generators=position_control->RightGenerators;

  int num_motion_elements=position_control->MotionControl->NumMotionElements;
  int num_control_loops=position_control->MotionControl->NumControlLoops;
  if(ARow <= 0 || ACol<=0 || ACol>num_motion_elements*2 || ARow>num_control_loops)
   return;

  int n=ACol-1;
  int m=ARow-1;
  int k=0;


  RDK::UEPtr<NMSDK::NPulseGenerator> gen=0;
  if(n<num_motion_elements)
   gen=dynamic_cast<NMSDK::NPulseGenerator*>(left_generators[m][num_motion_elements-n-1]);
  else
   gen=dynamic_cast<NMSDK::NPulseGenerator*>(right_generators[m][n-num_motion_elements]);

  try
  {
   gen->Frequency=StrToFloat(SelectedStateStringGrid->Cells[ACol][ARow]);
  }
  catch(EConvertError &ex)
  {

  }
 }
 catch(RDK::UException &exception)
 {

 }
}
//---------------------------------------------------------------------------

void __fastcall TNNewPositionControlElementForm::TrainPositionButtonClick(TObject *Sender)

{
 try
 {
  RDK::UELockPtr<NMSDK::NModel> model=RDK::GetModelLock<NMSDK::NModel>();
  RDK::UEPtr<NMSDK::NNewPositionControlElement> position_control=
	RDK::dynamic_pointer_cast<NMSDK::NNewPositionControlElement>(model->GetComponentL(ComponentControlName));

  position_control->RememberState=true;
 }
 catch(RDK::UException &exception)
 {

 }
}
//---------------------------------------------------------------------------

