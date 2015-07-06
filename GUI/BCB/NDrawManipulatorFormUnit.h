//---------------------------------------------------------------------------

#ifndef NDrawManipulatorFormUnitH
#define NDrawManipulatorFormUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TUVisualControllerFormUnit.h"
#include "NDrawManipulatorFrameUnit.h"
#include "TUVisualControllerFrameUnit.h"
//---------------------------------------------------------------------------
class TNDrawManipulatorForm : public TUVisualControllerForm
{
__published:	// IDE-managed Components
	TNDrawManipulatorFrame *NDrawManipulatorFrame1;
private:	// User declarations
public:		// User declarations
	__fastcall TNDrawManipulatorForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TNDrawManipulatorForm *NDrawManipulatorForm;
//---------------------------------------------------------------------------
#endif
