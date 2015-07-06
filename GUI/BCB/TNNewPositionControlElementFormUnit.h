//---------------------------------------------------------------------------

#ifndef TNNewPositionControlElementFormUnitH
#define TNNewPositionControlElementFormUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TUVisualControllerFormUnit.h"
#include "nmsdk_cpp_initdll.h"
//#include "nmsdk.bcb.h"
#include <Vcl.Grids.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TNNewPositionControlElementForm : public TUVisualControllerForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	TStringGrid *TrainedStateStringGrid;
	TStringGrid *SelectedStateStringGrid;
	TSplitter *Splitter1;
	TButton *TrainPositionButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall SelectedStateStringGridSetEditText(TObject *Sender, int ACol, int ARow,
          const UnicodeString Value);
	void __fastcall TrainPositionButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TNNewPositionControlElementForm(TComponent* Owner);

// Сохраняет параметры интерфейса в xml
virtual void ASaveParameters(RDK::USerStorageXML &xml);

// Загружает параметры интерфейса из xml
virtual void ALoadParameters(RDK::USerStorageXML &xml);


void AUpdateInterface(void);

// Возврат интерфейса в исходное состояние
void AClearInterface(void);


// Создание копии этого компонента
virtual TUVisualControllerForm* New(TComponent *owner=0);
};
//---------------------------------------------------------------------------
extern PACKAGE TNNewPositionControlElementForm *NNewPositionControlElementForm;
//---------------------------------------------------------------------------
#endif
