//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "NDrawManipulatorFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "NDrawManipulatorFrameUnit"
#pragma link "TUVisualControllerFrameUnit"
#pragma resource "*.dfm"
TNDrawManipulatorForm *NDrawManipulatorForm;
//---------------------------------------------------------------------------
__fastcall TNDrawManipulatorForm::TNDrawManipulatorForm(TComponent* Owner)
	: TUVisualControllerForm(Owner)
{
}
//---------------------------------------------------------------------------
